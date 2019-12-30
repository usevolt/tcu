

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



#include "pedal.h"
#include <uv_canopen.h>



// raw adc values for fault limits
#define PEDAL_HAL_DEF				0x8000
#define PEDAL_FAULT_MIN				0x2000
#define PEDAL_FAULT_MAX				0xF000


// values for hal sensor delta (hal2 - hal1)
#define PEDAL_MIDDLE_OFFSET			0x2000
#define PEDAL_VALUE_MAX				0xCD00
#define MOVING_AVG_COUNT			100
#define PEDAL_HYSTERESIS			0x1000

void pedal_init(pedal_st *this) {
	this->hal[0] = PEDAL_HAL_DEF;
	this->hal[1] = PEDAL_HAL_DEF;
	this->request = 0;
	this->state = PEDAL_STATE_OK;
	uv_moving_aver_init(&this->avg[0], 100);
	uv_hysteresis_init(&this->hys_min[0], PEDAL_FAULT_MIN, PEDAL_HYSTERESIS, true);
	uv_hysteresis_init(&this->hys_max[0], PEDAL_FAULT_MAX, PEDAL_HYSTERESIS, false);
	uv_moving_aver_init(&this->avg[1], 100);
	uv_hysteresis_init(&this->hys_min[1], PEDAL_FAULT_MIN, PEDAL_HYSTERESIS, true);
	uv_hysteresis_init(&this->hys_max[1], PEDAL_FAULT_MAX, PEDAL_HYSTERESIS, false);
}

void pedal_step(pedal_st *this) {
	if (this->state == PEDAL_STATE_LOST) {
		pedal_init(this);
	}
	else {
		for (uint8_t i = 0; i < 2; i++) {
			uv_moving_aver_step(&this->avg[i], this->hal[i]);
			uv_hysteresis_step(&this->hys_min[i], uv_moving_aver_get_val(&this->avg[i]));
			uv_hysteresis_step(&this->hys_max[i], uv_moving_aver_get_val(&this->avg[i]));

			if (uv_hysteresis_get_output(&this->hys_max[i]) ||
					uv_hysteresis_get_output(&this->hys_min[i])) {
				if (this->state != PEDAL_STATE_FAULT) {
					uv_canopen_emcy_send(CANOPEN_EMCY_DEVICE_SPECIFIC, CCU_EMCY_PEDAL_FAULT);
				}
				this->state = PEDAL_STATE_FAULT;
				break;
			}
		}
		if (this->state == PEDAL_STATE_OK) {

			int32_t rel;
			int32_t hal = this->hal[1] - this->hal[0];

			if (hal > PEDAL_MIDDLE_OFFSET / 2) {
				rel = uv_reli(hal, PEDAL_MIDDLE_OFFSET / 2, PEDAL_VALUE_MAX);
				if (rel < 0) {
					rel = 0;
				}
				else if (rel > 1000) {
					rel = 1000;
				}
				else {
				}
				rel = rel * rel / 1000;
				rel = 500 + rel / 2;
			}
			else if (hal < - PEDAL_MIDDLE_OFFSET / 2) {
				rel = uv_reli(hal, - PEDAL_MIDDLE_OFFSET / 2, - PEDAL_VALUE_MAX);
				if (rel < 0) {
					rel = 0;
				}
				else if (rel > 1000) {
					rel = 1000;
				}
				else {
				}
				rel = 1000 - (rel * rel / 1000);
				rel = rel / 2;
			}
			else {
				rel = 500;
			}
			if (rel > 1000) {
				rel = 1000;
			}
			else if (rel < 0) {
				rel = 0;
			}
			else {

			}
			this->request = uv_lerpi(rel, INT8_MIN, INT8_MAX);
		}
		else {
			this->request = 0;
		}

	}
}














