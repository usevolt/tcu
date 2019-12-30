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


#ifndef INC_INPUT_H_
#define INC_INPUT_H_


#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>

/// @brief: Module which converts raw variable input into pressed, released, etc actions

/// @brief: If request was active for shorter time than this, consider it as a click
#define INPUT_CLICK_DELAY_MS			60
/// @brief: Value which has to be exceeded in order to produce a click
#define INPUT_CLICK_VALUE				100

typedef struct {
	// input request
	int8_t request;

	int8_t last_request;

	int8_t pressed;
	int8_t released;
	int8_t clicked;

	bool click_possible;
	int32_t click_delay;

} input_st;


void input_init(input_st *this);

void input_step(input_st *this, uint16_t step_ms);

///  @brief: Returns 1 or -1 if positive or negative direction was pressed
static inline int8_t input_pressed(input_st *this) {
	return this->pressed;
}

///  @brief: Returns 1 or -1 if positive or negative direction was released
static inline int8_t input_released(input_st *this) {
	return this->released;
}

///  @brief: Returns 1 or -1 if positive or negative direction was clicked
static inline int8_t input_clicked(input_st *this) {
	return this->clicked;
}

/// @brief: Returns the input request in scale of -1000 ... 1000
int32_t input_get_request(input_st *this, uv_dual_solenoid_output_conf_st *conf);

#endif /* INC_INPUT_H_ */
