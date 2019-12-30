/*
 * uw_messages.c
 *
 *  Created on: Feb 19, 2015
 *      Author: usenius
 */


#include "main.h"
#include "messages.h"
#include "can_esb.h"
#include "can_fsb.h"
#include "can_csb.h"
#include "can_ccu.h"
#include "can_tcu.h"
#include "pin_mappings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uv_timer.h>
#include <uv_utilities.h>
#include <uv_eeprom.h>

extern dev_st dev;
#define this (&dev)




canopen_object_st obj_dict[] = {
		{
				.main_index = TCU_TOTAL_CURRENT_INDEX,
				.sub_index = TCU_TOTAL_CURRENT_SUBINDEX,
				.type = TCU_TOTAL_CURRENT_TYPE,
				.permissions = TCU_TOTAL_CURRENT_PERMISSIONS,
				.data_ptr = &this->total_current
		},
		{
				.main_index = TCU_DRIVE_REQ_INDEX,
				.sub_index = TCU_DRIVE_REQ_SUBINDEX,
				.type = TCU_DRIVE_REQ_TYPE,
				.permissions = TCU_DRIVE_REQ_PERMISSIONS,
				.data_ptr = &this->drive.input.request
		},
		{
				.main_index = TCU_DRIVE_PARAM_INDEX,
				.sub_index = TCU_DRIVE_PARAM_ARRAY_MAX_SIZE,
				.type = TCU_DRIVE_PARAM_TYPE,
				.permissions = TCU_DRIVE_PARAM_PERMISSIONS,
				.data_ptr = &this->drive_conf
		},
		{
				.main_index = TCU_DRIVE_CURRENT1_INDEX,
				.sub_index = TCU_DRIVE_CURRENT1_SUBINDEX,
				.type = TCU_DRIVE_CURRENT1_TYPE,
				.permissions = TCU_DRIVE_CURRENT1_PERMISSIONS,
				.data_ptr = &this->drive.out1.current_ma
		},
		{
				.main_index = TCU_DRIVE_CURRENT2_INDEX,
				.sub_index = TCU_DRIVE_CURRENT2_SUBINDEX,
				.type = TCU_DRIVE_CURRENT2_TYPE,
				.permissions = TCU_DRIVE_CURRENT2_PERMISSIONS,
				.data_ptr = &this->drive.out2.current_ma
		},
		{
				.main_index = TCU_DRIVE_CURRENT3_INDEX,
				.sub_index = TCU_DRIVE_CURRENT3_SUBINDEX,
				.type = TCU_DRIVE_CURRENT3_TYPE,
				.permissions = TCU_DRIVE_CURRENT3_PERMISSIONS,
				.data_ptr = &this->drive.out3.current_ma
		},




		{
				.main_index = TCU_CCU_INDEX_OFFSET + CCU_GEAR_INDEX,
				.sub_index = CCU_GEAR_SUBINDEX,
				.type = CCU_GEAR_TYPE,
				.permissions = CCU_GEAR_PERMISSIONS,
				.data_ptr = &this->drive.gear
		},
		{
				.main_index = TCU_FSB_INDEX_OFFSET + FSB_IGNKEY_INDEX,
				.sub_index = FSB_IGNKEY_SUBINDEX,
				.type = FSB_IGNKEY_TYPE,
				.permissions = FSB_IGNKEY_PERMISSIONS,
				.data_ptr = &this->fsb.ignkey_state
		},
		{
				.main_index = TCU_FSB_INDEX_OFFSET + FSB_EMCY_INDEX,
				.sub_index = FSB_EMCY_SUBINDEX,
				.type = FSB_EMCY_TYPE,
				.permissions = FSB_EMCY_PERMISSIONS,
				.data_ptr = &this->fsb.emcy
		},
		{
				.main_index = TCU_FSB_INDEX_OFFSET + FSB_DOORSW1_INDEX,
				.sub_index = FSB_DOORSW1_SUBINDEX,
				.type = FSB_DOORSW1_TYPE,
				.permissions = FSB_DOORSW1_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw1
		},
		{
				.main_index = TCU_FSB_INDEX_OFFSET + FSB_DOORSW2_INDEX,
				.sub_index = FSB_DOORSW2_SUBINDEX,
				.type = FSB_DOORSW2_TYPE,
				.permissions = FSB_DOORSW2_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw2
		},
		{
				.main_index = TCU_FSB_INDEX_OFFSET + FSB_SEATSW_INDEX,
				.sub_index = FSB_SEATSW_SUBINDEX,
				.type = FSB_SEATSW_TYPE,
				.permissions = FSB_SEATSW_PERMISSIONS,
				.data_ptr = &this->fsb.seat_sw
		}
};

int obj_dict_len() {
	return sizeof(obj_dict) / sizeof(canopen_object_st);
}

void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);

const uv_command_st terminal_commands[] = {
		{
				.id = CMD_STAT,
				.str = "stat",
				.instructions = "Displays the system status information.\n"
						"Usage: stat",
				.callback = &stat_callb
		},
		{
				.id = CMD_SET,
				.str = "set",
				.instructions = "Sets the configurations for output modules.\n"
						"Usage: set <\"str\"/\"g1\"/\"g2\"/\"g3\"/\"cabrot\"/\"telescope\"> "
						"<\"maxa\"/\"maxb\"/\"mina\"/\"minb\"/\"acc\"/\"dec\"/\"invert\">"
						"<value>",
				.callback = &set_callb
		}
};




unsigned int commands_size(void) {
	return sizeof(terminal_commands) / sizeof(uv_command_st);
}




static void stat_output(uv_dual_solenoid_output_st *output, const char *name) {
	printf("%s solenoid states: %u %u, current: %i mA\n",
			name, uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_A),
			uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_B),
			uv_dual_solenoid_output_get_current(output));
}


void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	printf("SYSTEM STATUS:\n");
	printf("Total current: %u mA\n", (unsigned int) this->total_current);
	printf("Gear: %u\n", this->drive.gear + 1);
	stat_output(&this->drive.out1, "Drive 1");
	stat_output(&this->drive.out2, "Drive 2");
	stat_output(&this->drive.out3, "Drive 3");
	printf("Pedal: state: %u, hal1: %i hal2: %i request: %i\n",
			this->pedal.state, this->pedal.req[0], this->pedal.req[1], this->pedal.request);
	printf("emcy: %u, seat sw: %u, ignkey state: %u, fsb heartbeat expired: %u\n",
			this->fsb.emcy, this->fsb.seat_sw, this->fsb.ignkey_state,
			uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID));
}

void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if ((args < 1) || (argv[0].type != ARG_STRING)) {
		printf("Give module name as an argument.\n");
	}
	else {
		uv_dual_solenoid_output_conf_st *conf = NULL;
		const char *str = argv[0].str;

		if (strcmp(str, "g1") == 0) {
			conf = &this->drive_conf.gear_conf[TCU_GEAR_1];
		}
		else if (strcmp(str, "g2") == 0) {
			conf = &this->drive_conf.gear_conf[TCU_GEAR_2];
		}
		else if (strcmp(str, "g3") == 0) {
			conf = &this->drive_conf.gear_conf[TCU_GEAR_3];
		}
		else {
			printf("Unknown module '%s'\n", str);
		}

		if (conf) {
			if (args > 2) {
				if ((argv[1].type == ARG_STRING) &&
					(argv[2].type == ARG_INTEGER)) {
					const char *s = argv[1].str;
					int16_t value = argv[2].number;
					if (strcmp(s, "maxa") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = value;
					}
					else if (strcmp(s, "mina") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = value;
					}
					else if (strcmp(s, "maxb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = value;
					}
					else if (strcmp(s, "minb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = value;
					}
					else if (strcmp(s, "acc") == 0) {
						conf->acc = value;
					}
					else if (strcmp(s, "dec") == 0) {
						conf->dec = value;
					}
					else if (strcmp(s, "invert") == 0) {
						conf->invert = (bool) value;
					}
					else if (strcmp(s, "assinv") == 0) {
						conf->assembly_invert = (bool) value;
					}
					else {
						printf("Unknown parameter '%s'\n", s);
					}
				}
				else {
					printf("Wrong type of arguments. Arguments has to be:\n"
							"   String, string and integer.\n");
				}
			}
			printf("%s parameters:\n"
					"   Max Speed A: %u\n"
					"   Min Speed A: %u\n"
					"   Max Speed B: %u\n"
					"   Min Speed B: %u\n"
					"   Acceleration: %u\n"
					"   Deceleration: %u\n"
					"   Invert: %u\n"
					"   Assembly Invert: %u\n",
					str,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma,
					conf->acc,
					conf->dec,
					conf->invert,
					conf->assembly_invert);
		}
	}
}



