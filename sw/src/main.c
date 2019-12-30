/*
===============================================================================
 Name        : main.c
 Author      : Olli Usenius
 Version     :
 Copyright   : $(copyright)
 Description :
===============================================================================
*/


#include "main.h"
#include "messages.h"
#include "pin_mappings.h"
#include "can_fsb.h"

#include <uv_utilities.h>
#include <uv_rtos.h>
#include <string.h>
#include <uv_eeprom.h>
#include <uv_wdt.h>

dev_st dev = {};
static bool initialized = false;
#define this ((dev_st*) &dev)



void gpio_callback(uv_gpios_e gpio);
void can1_callback(void *user_ptr, uv_can_message_st* msg);


void gpio_callback(uv_gpios_e gpio) {
	uv_mcp2515_int(&this->mcp2515);
}

void can1_callback(void *user_ptr, uv_can_message_st* msg) {
	// forward CAN1 messages to CAN2
	if (uv_mcp2515_send(&this->mcp2515, msg) != ERR_NONE) {
		uv_can_msg_st m;
		uv_mcp2515_tx_pop(&this->mcp2515, &m);
		uv_mcp2515_send(&this->mcp2515, msg);
	}
}



void init(dev_st* me) {
	// load non-volatile data
	if (uv_memory_load(MEMORY_APP_PARAMS)) {

		this->dither_ampl = DITHER_AMPL_DEF;
		this->dither_freq = DITHER_FREQ_DEF;

		steer_conf_reset(&this->steer_conf);
		drive_conf_reset(&this->drive_conf);
		cabrot_conf_reset(&this->cabrot_conf);
		telescope_conf_reset(&this->telescope_conf);


		// initialize non-volatile memory to default settings
		uv_memory_save();
	}
	// initialize outputs

	this->total_current = 0;

	this->fsb.door_sw1 = 0;
	this->fsb.door_sw2 = 0;
	this->fsb.seat_sw = 0;
	this->fsb.emcy = 0;
	this->fsb.ignkey_state = FSB_IGNKEY_STATE_OFF;

	this->hcu.left_foot_state = HCU_FOOT_DOWN;
	this->hcu.right_foot_state = HCU_FOOT_DOWN;
	this->hcu.implement = HCU_IMPLEMENT_UW180S;

	steer_init(&this->steer, &this->steer_conf);
	drive_init(&this->drive, &this->drive_conf);
	cabrot_init(&this->cabrot, &this->cabrot_conf);
	telescope_init(&this->telescope, &this->telescope_conf);

	pedal_init(&this->pedal);

	uv_terminal_init(terminal_commands, commands_size());

	uv_eeprom_read(&this->assembly, sizeof(this->assembly), ASSEMBLY_EEPROM_ADDR);
	this->assembly_write = 0;
	if (this->assembly.gears_installed > CCU_GEAR_COUNT) {
		this->assembly.gears_installed = CCU_GEAR_COUNT;
		this->assembly_write = 1;
	}
	else if (this->assembly.gears_installed == 0) {
		this->assembly.gears_installed = 1;
		this->assembly_write = 1;
	}
	else {

	}


	uv_gpio_init_output(MCP2515_RESET, true);

	uv_gpio_interrupt_init(&gpio_callback);
	if (uv_mcp2515_init(&this->mcp2515, SPI0, SPI_SLAVE0,
			MCP2515_INT, uv_memory_get_can_baudrate())) {
		uv_terminal_enable();
		printf("MCP2515 init failed\n");

	}

	uv_output_init(&this->boom_vdd, BOOM_VDD_SENSE, BOOM_VDD_OUT, VN5E01_CURRENT_AMPL_UA,
			BOOM_VDD_MAX_CURRENT, BOOM_VDD_FAULT_CURRENT, BOOM_VDD_AVG_COUNT,
			CCU_EMCY_BOOM_VDD_OVERLOAD, CCU_EMCY_BOOM_VDD_FAULT);
	uv_output_set(&this->boom_vdd, OUTPUT_STATE_ON);


	// configure CAN1 to receive all messages
	uv_can_config_rx_message(CONFIG_CANOPEN_CHANNEL, 0x0, 0, CAN_STD);
	uv_canopen_set_can_callback(&can1_callback);
	uv_canopen_set_state(CANOPEN_OPERATIONAL);

	initialized = true;
}



void solenoid_step(void* me) {

	// wait until solenoid structures have been initialized
	while (!initialized) {
		uv_rtos_task_delay(1);
	}

	while (true) {
		uint32_t step_ms = 2;

		steer_solenoid_step(&this->steer, step_ms);
		drive_solenoid_step(&this->drive, step_ms);
		cabrot_solenoid_step(&this->cabrot, step_ms);
		telescope_solenoid_step(&this->telescope, step_ms);

		uv_rtos_task_delay(step_ms);
	}
}

void mcp2515_step(void *me) {
	while (!initialized) {
		uv_rtos_task_delay(1);
	}

	while (true) {
		uint32_t step_ms = 2;

		uv_can_msg_st msg;

		while (uv_mcp2515_receive(&this->mcp2515, &msg) == ERR_NONE) {
			uv_can_send(CONFIG_CANOPEN_CHANNEL, &msg);
		}

		uv_rtos_task_delay(step_ms);
	}
}

void step(void* me) {

	init(this);

	while (true) {
		unsigned int step_ms = 20;
		// update watchdog timer value to prevent a hard reset
		 uv_wdt_update();

		// terminal step function
		uv_terminal_step();

		if (this->assembly_write) {
			uv_eeprom_write(&this->assembly, sizeof(this->assembly), ASSEMBLY_EEPROM_ADDR);
			this->assembly_write = 0;
		}

		this->total_current = abs(steer_get_current(&this->steer)) +
				abs(drive_get_current1(&this->drive)) +
				abs(drive_get_current2(&this->drive)) +
				abs(drive_get_current3(&this->drive)) +
				abs(drive_get_brake_current(&this->drive)) +
				abs(drive_get_gear3_current(&this->drive)) +
				abs(cabrot_get_current(&this->cabrot)) +
				abs(telescope_get_current(&this->telescope));

		pedal_step(&this->pedal);

		// set driving input from pedal
		drive_set_request(&this->drive, pedal_get_request(&this->pedal));
		steer_step(&this->steer, step_ms);
		drive_step(&this->drive, step_ms);
		cabrot_step(&this->cabrot, step_ms);
		telescope_step(&this->telescope, step_ms);

		uv_output_set_state(&this->boom_vdd,
				(this->hcu.implement == HCU_IMPLEMENT_UW180S) ?
						OUTPUT_STATE_ON : OUTPUT_STATE_OFF);
		uv_output_step(&this->boom_vdd, step_ms);

		// if keypad heartbeat messages are not received, input from that keypad is set to zero
		if (uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID)) {
		}
		if (uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID)) {
		}
		if (uv_canopen_heartbeat_producer_is_expired(PEDAL_NODE_ID)) {
			pedal_set_lost(&this->pedal, true);
		}
		else {
			pedal_set_lost(&this->pedal, false);
		}

		// outputs are disables if FSB is not found, ignition key is not in ON state,
		// or emergency switch is pressed
		if (uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID) ||
				uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID) ||
				uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID) ||
				(this->fsb.ignkey_state != FSB_IGNKEY_STATE_ON) ||
				this->fsb.emcy ||
				!this->fsb.seat_sw ||
				!this->fsb.door_sw1 ||
				!this->fsb.door_sw2) {
			// disable all outputs
			steer_disable(&this->steer);
			drive_disable(&this->drive);
			cabrot_disable(&this->cabrot);
			telescope_disable(&this->telescope);
			// boom VDD is disabled only because of ignkey or emcy switch
			uv_output_set_enabled(&this->boom_vdd,
					(!this->fsb.emcy &&
					(this->fsb.ignkey_state == FSB_IGNKEY_STATE_ON)));
		}
		else {
			// enable outputs
			steer_enable(&this->steer);
			drive_enable(&this->drive);
			cabrot_enable(&this->cabrot);
			telescope_enable(&this->telescope);
			uv_output_enable(&this->boom_vdd);
		}

		uv_rtos_task_delay(step_ms);
	}
}






int main(void) {

	// init the watchdog timer
//	uw_wdt_init(5);

	uv_init(&dev);


	uv_rtos_task_create(&mcp2515_step, "mcp2515", UV_RTOS_MIN_STACK_SIZE * 2,
			&dev, UV_RTOS_IDLE_PRIORITY + 2, NULL);

	uv_rtos_task_create(&solenoid_step, "solenoid", UV_RTOS_MIN_STACK_SIZE * 3,
			&dev, UV_RTOS_IDLE_PRIORITY + 3, NULL);

	// step task has to be the biggest since it is responsible for input handling
	// and stopping the movements
	uv_rtos_task_create(&step, "step", UV_RTOS_MIN_STACK_SIZE * 3,
			&dev, UV_RTOS_IDLE_PRIORITY + 4, NULL);


	uv_rtos_start_scheduler();


    // Enter an infinite loop
	// never should end up here
    while(1) {
    	printf("scheduler returned\r");
    }
    return 0;
}
