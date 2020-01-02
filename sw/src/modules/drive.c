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





#include "drive.h"
#include "can_ccu.h"
#include "main.h"
#include "pin_mappings.h"


void drive_conf_reset(drive_conf_st *this) {
	this->drive_conf.acc = DUAL_SOLENOID_ACC_MAX;
	this->drive_conf.dec = DUAL_SOLENOID_DEC_MAX;
	this->drive_conf.invert = false;
	this->drive_conf.assembly_invert = false;
	this->drive_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1500;
	this->drive_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 500;
	this->drive_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1500;
	this->drive_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 500;

	this->comp.f = 0;
	this->comp.b = 0;
}


void drive_init(drive_st *this, drive_conf_st *conf_ptr) {
	this->request = 0;
	this->d4wd_request = 0;
	this->d4wd_req2 = 0;
	this->conf = conf_ptr;
	this->gear = CCU_GEAR_1;

	if (this->conf->comp.b > 100 ||
			this->conf->comp.b < -100) {
		this->conf->comp.b = 0;
	}
	if (this->conf->comp.f > 100 ||
			this->conf->comp.f < -100) {
		this->conf->comp.f = 0;
	}

	uv_dual_solenoid_output_init(&this->out1, &this->conf->drive_conf, DRIVE1_PWMA,
			DRIVE1_PWMB, DRIVE1_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE1_OVERLOAD_A, CCU_EMCY_DRIVE1_OVERLOAD_B,
			CCU_EMCY_DRIVE1_FAULT_A, CCU_EMCY_DRIVE1_FAULT_B);
	uv_dual_solenoid_output_init(&this->out2, &this->conf->drive_conf, DRIVE2_PWMA,
			DRIVE2_PWMB, DRIVE2_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE2_OVERLOAD_A, CCU_EMCY_DRIVE2_OVERLOAD_B,
			CCU_EMCY_DRIVE2_FAULT_A, CCU_EMCY_DRIVE2_FAULT_B);
	uv_output_init(&this->d4wd, D4WD_SENSE, D4WD_OUT, VN5E01_CURRENT_AMPL_UA, 8000, 12000,
			10, TCU_EMCY_D4WD_OVERLOAD, TCU_EMCY_D4WD_FAULT);

}


void drive_step(drive_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_set_conf(&this->out1, &this->conf->drive_conf);
	uv_dual_solenoid_output_set_conf(&this->out2, &this->conf->drive_conf);

	int32_t req = (int32_t) this->request * 1000 / INT8_MAX;
	if (req > 1000) {
		req = 1000;
	}
	else if (req < -1000) {
		req = -1000;
	}
	else {

	}

	if (this->d4wd_request || this->d4wd_req2) {
		uv_output_set(&this->d4wd, OUTPUT_STATE_ON);
		// make sure driving is disabled when telescope request is active
		req = 0;
	}
	else {
		if (this->gear == CCU_GEAR_1) {
			uv_output_set(&this->d4wd, OUTPUT_STATE_OFF);
		}
		else {
			uv_output_set(&this->d4wd, (this->request != 0) ?
					OUTPUT_STATE_ON : OUTPUT_STATE_OFF);
			req = 0;
		}
	}

	uv_dual_solenoid_output_set(&this->out1, req);
	uv_dual_solenoid_output_set(&this->out2,
			(this->conf->drive_conf.assembly_invert) ? -req : req);

}

