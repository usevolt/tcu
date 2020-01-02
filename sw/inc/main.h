/*
 * main.h
 *
 *  Created on: Apr 26, 2015
 *      Author: usevolt
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <uv_memory.h>
#include <uv_filters.h>
#include <uv_output.h>
#include <uv_dual_solenoid_output.h>
#include "can_fsb.h"
#include "drive.h"
#include "telescope.h"


#define VND5050_CURRENT_AMPL_UA		1619
#define VN5E01_CURRENT_AMPL_UA		5600

#define DITHER_AMPL_DEF				0
#define DITHER_FREQ_DEF				50

#define SOLENOID_MAX_CURRENT		4000
#define SOLENOID_FAULT_CURRENT		5000


/// @brief: main data structure.
/// This struct can be save to non-volatile flash memory with
/// a terminal commmand 'save'.
typedef struct _dev_st {

	uint16_t total_current;

	drive_st drive;
	telescope_st telescope;

	uv_output_st boom_vdd;

	struct {
		fsb_ignkey_states_e ignkey_state;
		uint8_t emcy;
		uint8_t seat_sw;
		uint8_t door_sw1;
		uint8_t door_sw2;
	} fsb;

	// non-volatile data start
	uv_data_start_t data_start;

	uint16_t dither_freq;
	int16_t dither_ampl;

	drive_conf_st drive_conf;
	telescope_conf_st telescope_conf;

	uv_data_end_t data_end;

} dev_st;


extern dev_st dev;


void step(void* me);

void init(dev_st* me);






#endif /* MAIN_H_ */
