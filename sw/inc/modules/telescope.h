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


#ifndef INC_MODULES_TELESCOPE_H_
#define INC_MODULES_TELESCOPE_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st out_conf;
} telescope_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void telescope_conf_reset(telescope_conf_st *this);


#define TELESCOPE_REQ_DELAY_MS			100


typedef struct {
	int8_t request;

	uv_delay_st req_delay;
	uv_dual_solenoid_output_st out;

	telescope_conf_st *conf;

} telescope_st;


/// @brief: Initializes the module
void telescope_init(telescope_st *this, telescope_conf_st *conf_ptr);


/// @brief: Step function
void telescope_step(telescope_st *this, uint16_t step_ms);


static inline int16_t telescope_get_current(telescope_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
void telescope_solenoid_step(telescope_st *this, uint16_t step_ms);




/// @brief: Disables the boom fold module
static inline void telescope_disable(telescope_st *this) {
	uv_dual_solenoid_output_disable(&this->out);
	this->request = 0;
}


/// @brief: Enables the boom fold module
static inline void telescope_enable(telescope_st *this) {
	uv_dual_solenoid_output_enable(&this->out);
}



#endif /* INC_MODULES_TELESCOPE_H_ */
