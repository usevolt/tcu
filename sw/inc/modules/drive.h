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
#include "can_ccu.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st drive_conf;
	struct {
		int8_t f;
		int8_t b;
	} comp;
} drive_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void drive_conf_reset(drive_conf_st *this);


#define DRIVE_FOOT_DOWN_DELAY_MS		1000

typedef struct {
	int8_t request;
	int8_t d4wd_request;
	int8_t d4wd_req2;
	// indicates that driving is always disabled and d4wd is active always
	bool drive_disabled;

	// output for only 1st gear
	uv_dual_solenoid_output_st out1;

	uv_dual_solenoid_output_st out2;

	uv_output_st d4wd;

	ccu_gear_e gear;

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

static inline void drive_set_d4wd_req(drive_st *this, int8_t req) {
	this->d4wd_req2 = req;
}

static inline void drive_set_drive_disabled(drive_st *this, bool value) {
	this->drive_disabled = value;
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void drive_solenoid_step(drive_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out1, step_ms);
	uv_dual_solenoid_output_step(&this->out2, step_ms);
	uv_output_step(&this->d4wd, step_ms);
}


static inline void drive_set_request(drive_st *this, int8_t value) {
	this->request = value;
}


/// @brief: Disables the boom fold module
static inline void drive_disable(drive_st *this) {
	uv_dual_solenoid_output_disable(&this->out1);
	uv_dual_solenoid_output_disable(&this->out2);
	this->request = 0;
}


/// @brief: Enables the boom fold module
static inline void drive_enable(drive_st *this) {
	uv_dual_solenoid_output_enable(&this->out1);
	uv_dual_solenoid_output_enable(&this->out2);
}



#endif /* INC_MODULES_DRIVE_H_ */
