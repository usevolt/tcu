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



#include "input.h"


void input_init(input_st *this) {
	this->pressed = 0;
	this->released = 0;
	this->clicked = 0;
	this->request = 0;
	this->last_request = 0;
	this->click_possible = false;
}

void input_step(input_st *this, uint16_t step_ms) {
	int8_t req = this->request;

	this->clicked = 0;
	this->pressed = 0;
	this->released = 0;

	// pressed
	if (req && !this->last_request) {
			this->pressed = (req > 0) ? 1  : -1;
			this->click_delay = INPUT_CLICK_DELAY_MS;
	}
	// released
	else if (!req && this->last_request) {
		this->released = (this->last_request > 0) ? 1 : -1;
		this->click_possible = false;
		if ((this->click_delay > 0) && (this->click_possible)) {
			this->clicked = (this->last_request > 0) ? 1 : -1;
		}
	}
	else {
		// is down
		if (req) {
			if (abs(req) > INPUT_CLICK_VALUE) {
				this->click_possible = true;
			}
			if (this->click_delay > 0) {
				this->click_delay -= step_ms;
			}
		}
		// is up
		else {

		}
	}



	this->last_request = req;
}



int32_t input_get_request(input_st *this, uv_dual_solenoid_output_conf_st *conf) {
	int32_t ret = 0;
	if (this->request != 0) {
		int32_t rel = uv_reli(this->request, INT8_MIN, INT8_MAX);
		ret = uv_lerpi(rel, -1000, 1000);
		if (ret > 1000) {
			ret = 1000;
		}
		else if (ret < -1000) {
			ret = -1000;
		}
		else {

		}
		ret *= (conf->invert) ? -1 : 1;
	}
	return ret;
}
