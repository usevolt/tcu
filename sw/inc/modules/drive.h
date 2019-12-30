/* 
 * This file is part of the uv_hal distribution (www.usevolt.fi).
 * Copyright (c) 2017 Usevolt Oy.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef INC_MODULES_DRIVE_H_
#define INC_MODULES_DRIVE_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"
#include "can_ccu.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st gear_conf[CCU_GEAR_COUNT];
	struct {
		int8_t f;
		int8_t b;
	} comp;
} drive_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void drive_conf_reset(drive_conf_st *this);


#define DRIVE_FOOT_DOWN_DELAY_MS		1000

typedef struct {
	// input module from the CAN-bus
	input_st input;

	// output for only 1st gear
	uv_dual_solenoid_output_st out1;

	// output for all other gears
	uv_dual_solenoid_output_st out2;

	// output for back driving on CM & LM
	uv_dual_solenoid_output_st out3;

	// inhibit delay for sending emcy messages when driving foot down
	uv_delay_st foot_down_emcy_delay;

	// output for brake
	uv_output_st brake;

	// output for gear3
	uv_output_st gear3;

	ccu_gear_e gear;
	input_st gear_req;

	// request for 4wd drive on first gear to HCU
	uv_output_state_e d4wd_req;

	ccu_cabdir_e cabdir;

	drive_conf_st *conf;

} drive_st;


/// @brief: Initializes the module
void drive_init(drive_st *this, drive_conf_st *conf_ptr);


/// @brief: Step function
void drive_step(drive_st *this, uint16_t step_ms);


static inline int16_t drive_get_current1(drive_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out1);
}

static inline int16_t drive_get_current2(drive_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out2);
}

static inline int16_t drive_get_current3(drive_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out3);
}

static inline int16_t drive_get_brake_current(drive_st *this) {
	return uv_output_get_current(&this->brake);
}

static inline int16_t drive_get_gear3_current(drive_st *this) {
	return uv_output_get_current(&this->gear3);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void drive_solenoid_step(drive_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out1, step_ms);
	uv_dual_solenoid_output_step(&this->out2, step_ms);
	uv_dual_solenoid_output_step(&this->out3, step_ms);
	uv_output_step(&this->brake, step_ms);
	uv_output_step(&this->gear3, step_ms);
}


static inline void drive_set_request(drive_st *this, int8_t value) {
	this->input.request = value;
}


/// @brief: Disables the boom fold module
static inline void drive_disable(drive_st *this) {
	uv_dual_solenoid_output_disable(&this->out1);
	uv_dual_solenoid_output_disable(&this->out2);
	uv_dual_solenoid_output_disable(&this->out3);
	uv_output_disable(&this->brake);
	uv_output_disable(&this->gear3);
	this->input.request = 0;
}


/// @brief: Enables the boom fold module
static inline void drive_enable(drive_st *this) {
	uv_dual_solenoid_output_enable(&this->out1);
	uv_dual_solenoid_output_enable(&this->out2);
	uv_dual_solenoid_output_enable(&this->out3);
	uv_output_enable(&this->brake);
	uv_output_enable(&this->gear3);
}



#endif /* INC_MODULES_DRIVE_H_ */
