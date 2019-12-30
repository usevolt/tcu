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


#ifndef INC_PEDAL_H_
#define INC_PEDAL_H_


/// @file: Defines the pedal structure

#include <uv_utilities.h>
#include <uv_filters.h>

typedef enum {
	PEDAL_STATE_OK = 0,
	PEDAL_STATE_LOST,
	PEDAL_STATE_FAULT
} pedal_states_e;

typedef struct {
	uint16_t hal[2];
	int8_t req[2];
	int8_t request;
	pedal_states_e state;
	uv_moving_aver_st avg[2];
	uv_hysteresis_st hys_min[2];
	uv_hysteresis_st hys_max[2];
} pedal_st;

void pedal_init(pedal_st *this);

void pedal_step(pedal_st *this);

/// @brief: Returns the input request from pedal
static inline int8_t pedal_get_request(pedal_st *this) {
	return this->request;
}

/// @brief: Sets the pedal state
static inline void pedal_set_lost(pedal_st *this, bool value) {
	if (value) {
		this->state = PEDAL_STATE_LOST;
	}
	else {
		if (this->state == PEDAL_STATE_LOST) {
			this->state = PEDAL_STATE_OK;
		}
	}
}

#endif /* INC_PEDAL_H_ */
