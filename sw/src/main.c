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





void init(dev_st* me) {
	// load non-volatile data
	if (uv_memory_load(MEMORY_APP_PARAMS)) {

		this->dither_ampl = DITHER_AMPL_DEF;
		this->dither_freq = DITHER_FREQ_DEF;

		drive_conf_reset(&this->drive_conf);
		telescope_conf_reset(&this->telescope_conf);

		// initialize non-volatile memory to default settings
		uv_memory_save();
	}
	uv_terminal_init(terminal_commands, commands_size());

	this->total_current = 0;
	this->fsb.door_sw1 = 0;
	this->fsb.door_sw2 = 0;
	this->fsb.seat_sw = 0;
	this->fsb.emcy = 0;
	this->fsb.ignkey_state = FSB_IGNKEY_STATE_OFF;

	drive_init(&this->drive, &this->drive_conf);
	telescope_init(&this->telescope, &this->telescope_conf);

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

		drive_solenoid_step(&this->drive, step_ms);
		telescope_solenoid_step(&this->telescope, step_ms);

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

		this->total_current =
				abs(drive_get_current1(&this->drive)) +
				abs(drive_get_current2(&this->drive)) +
				abs(telescope_get_current(&this->telescope));

		drive_step(&this->drive, step_ms);
		telescope_step(&this->telescope, step_ms);

		// outputs are disables if FSB is not found, ignition key is not in ON state,
		// or emergency switch is pressed
		if (uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID) ||
			uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID) ||
				(this->fsb.ignkey_state != FSB_IGNKEY_STATE_ON) ||
				this->fsb.emcy ||
				!this->fsb.seat_sw ||
				!this->fsb.door_sw1 ||
				!this->fsb.door_sw2) {
			// disable all outputs
			drive_disable(&this->drive);
			telescope_disable(&this->telescope);
		}
		else {
			// enable outputs
			drive_enable(&this->drive);
			telescope_enable(&this->telescope);
		}

		uv_rtos_task_delay(step_ms);
	}
}






int main(void) {

	uv_init(&dev);


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
