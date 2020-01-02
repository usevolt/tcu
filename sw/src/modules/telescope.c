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





#include "telescope.h"
#include "can_tcu.h"
#include "main.h"
#include "pin_mappings.h"
#include "drive.h"


void telescope_conf_reset(telescope_conf_st *this) {
	this->out_conf.acc = 20;
	this->out_conf.dec = 50;
	this->out_conf.invert = true;
	this->out_conf.assembly_invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1200;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 500;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1200;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 500;
}


void telescope_init(telescope_st *this, telescope_conf_st *conf_ptr) {
	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, TELESCOPE_PWMA,
			TELESCOPE_PWMB, TELESCOPE_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_TELESCOPE_OVERLOAD_A, CCU_EMCY_TELESCOPE_OVERLOAD_B,
			CCU_EMCY_TELESCOPE_FAULT_A, CCU_EMCY_TELESCOPE_FAULT_B);
	uv_delay_init(&this->req_delay, TELESCOPE_REQ_DELAY_MS);
}


void telescope_step(telescope_st *this, uint16_t step_ms) {
	int32_t req = (int32_t) this->request * 1000 / INT8_MAX;

	if (req > 1000) {
		req = 1000;
	}
	else if (req < -1000) {
		req = -1000;
	}
	else {

	}

	// make sure that d4wd request is ON, so that wheels can rotate freely
	drive_set_d4wd_req(&dev.drive, req);

	uv_dual_solenoid_output_set(&this->out, req);

	if (uv_delay(&this->req_delay, step_ms) ||
			uv_delay_has_ended(&this->req_delay)) {
		this->request = 0;
	}
}



void telescope_solenoid_step(telescope_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out, step_ms);
}
