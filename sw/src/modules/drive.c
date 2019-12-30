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
	this->gear_conf[CCU_GEAR_1].acc = DUAL_SOLENOID_ACC_MAX;
	this->gear_conf[CCU_GEAR_1].dec = DUAL_SOLENOID_DEC_MAX;
	this->gear_conf[CCU_GEAR_1].invert = false;
	this->gear_conf[CCU_GEAR_1].assembly_invert = false;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1500;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 500;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1500;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 500;

	this->gear_conf[CCU_GEAR_2].acc = 30;
	this->gear_conf[CCU_GEAR_2].dec = 25;
	this->gear_conf[CCU_GEAR_2].invert = false;
	this->gear_conf[CCU_GEAR_2].assembly_invert = false;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1500;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 500;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1500;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 500;

	this->gear_conf[CCU_GEAR_3].acc = 30;
	this->gear_conf[CCU_GEAR_3].dec = 0;
	this->gear_conf[CCU_GEAR_3].invert = false;
	this->gear_conf[CCU_GEAR_3].assembly_invert = false;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1500;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 500;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1500;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 500;

	this->comp.f = 0;
	this->comp.b = 0;
}


void drive_init(drive_st *this, drive_conf_st *conf_ptr) {
	input_init(&this->input);
	input_init(&this->gear_req);
	this->conf = conf_ptr;
	this->gear = CCU_GEAR_1;
	this->d4wd_req = OUTPUT_STATE_OFF;
	this->cabdir = CCU_CABDIR_FORWARD;

	if (this->conf->comp.b > 100 ||
			this->conf->comp.b < -100) {
		this->conf->comp.b = 0;
	}
	if (this->conf->comp.f > 100 ||
			this->conf->comp.f < -100) {
		this->conf->comp.f = 0;
	}

	uv_delay_init(&this->foot_down_emcy_delay, DRIVE_FOOT_DOWN_DELAY_MS);

	uv_dual_solenoid_output_init(&this->out1, &this->conf->gear_conf[this->gear], DRIVE1_PWMA,
			DRIVE1_PWMB, DRIVE1_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE1_OVERLOAD_A, CCU_EMCY_DRIVE1_OVERLOAD_B,
			CCU_EMCY_DRIVE1_FAULT_A, CCU_EMCY_DRIVE1_FAULT_B);
	uv_dual_solenoid_output_init(&this->out2, &this->conf->gear_conf[this->gear], DRIVE2_PWMA,
			DRIVE2_PWMB, DRIVE2_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE2_OVERLOAD_A, CCU_EMCY_DRIVE2_OVERLOAD_B,
			CCU_EMCY_DRIVE2_FAULT_A, CCU_EMCY_DRIVE2_FAULT_B);
	uv_dual_solenoid_output_init(&this->out3, &this->conf->gear_conf[this->gear], DRIVE3_PWMA,
			DRIVE3_PWMB, DRIVE3_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE3_OVERLOAD_A, CCU_EMCY_DRIVE3_OVERLOAD_B,
			CCU_EMCY_DRIVE3_FAULT_A, CCU_EMCY_DRIVE3_FAULT_B);
	uv_output_init(&this->brake, BRAKE_SENSE, BRAKE_OUT, VND5050_CURRENT_AMPL_UA,
			4000, 5000, 50, CCU_EMCY_BRAKE_OVERLOAD, CCU_EMCY_BRAKE_FAULT);
	uv_output_init(&this->gear3, GEAR3_SENSE, GEAR3_OUT, VN5E01_CURRENT_AMPL_UA,
			8000, 12000, 50, CCU_EMCY_GEAR3_OVERLOAD, CCU_EMCY_GEAR3_FAULT);

}


void drive_step(drive_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);
	input_step(&this->gear_req, step_ms);

	uv_dual_solenoid_output_set_conf(&this->out1, &this->conf->gear_conf[this->gear]);
	uv_dual_solenoid_output_set_conf(&this->out2, &this->conf->gear_conf[this->gear]);
	uv_dual_solenoid_output_set_conf(&this->out3, &this->conf->gear_conf[this->gear]);

	uv_delay(&this->foot_down_emcy_delay, step_ms);

	int8_t g = input_pressed(&this->gear_req);
	// increase gear
	if (g > 0) {
		if (this->gear < dev.assembly.gears_installed - 1) {
			this->gear++;
		}
		else {
			this->gear = CCU_GEAR_1;
		}
	}
	// decrease gear
	else if (g < 0) {
		if (this->gear != CCU_GEAR_1) {
			this->gear--;
		}
		else {
			this->gear = dev.assembly.gears_installed - 1;
		}
	}
	else {

	}

	// prevent driving when legs are down
	if ((dev.hcu.left_foot_state == HCU_FOOT_DOWN) ||
			(dev.hcu.right_foot_state == HCU_FOOT_DOWN)) {

		if (input_get_request(&this->input, &this->conf->gear_conf[this->gear]) &&
				uv_delay_has_ended(&this->foot_down_emcy_delay)) {

			uv_canopen_emcy_send(CANOPEN_EMCY_DEVICE_SPECIFIC,
					(dev.hcu.left_foot_state == HCU_FOOT_DOWN) ?
							CCU_EMCY_DRIVING_LEFT_FOOT_DOWN :
							CCU_EMCY_DRIVING_RIGHT_FOOT_DOWN);
			uv_delay_init(&this->foot_down_emcy_delay, DRIVE_FOOT_DOWN_DELAY_MS);
		}
		uv_dual_solenoid_output_set(&this->out1, 0);
		uv_dual_solenoid_output_set(&this->out2, 0);
		uv_dual_solenoid_output_set(&this->out3, 0);
	}
	else {
		// invert driving direction if the cab is rotated
		int16_t req = input_get_request(&this->input, &this->conf->gear_conf[this->gear]);
		if (req == 0) {
			// cab dir is updated only when driving is stopped
			this->cabdir = cabrot_get_dir(&dev.cabrot);
		}
		else {
			req *= (this->cabdir == CCU_CABDIR_BACKWARD) ? -1 : 1;
		}

		// driving normally
		uv_dual_solenoid_output_set(&this->out1, req);

		// 2nd output is used only with 2nd and 3rd gears
		uv_dual_solenoid_output_set(&this->out2,
				(this->gear < uv_mini(CCU_GEAR_2, dev.assembly.gears_installed - 1)) ? 0 : req);

		// 3rd output is used only on first gear (4wd on LM & CM),
		// when the loading space telescope is not moving
		//
		// 1st gear assembly invertion determines the direction of current for 1st valve
		// 3rd output controls the back wheels, thus apply the compensation
		//
		// apply the drive compensation
		int16_t backreq = req;
		backreq += backreq * ((backreq > 0) ? this->conf->comp.f : this->conf->comp.b) / 200;
		if (backreq > 1000) {
			backreq = 1000;
		}
		else if (backreq < -1000) {
			backreq = -1000;
		}
		else {

		}
		uv_dual_solenoid_output_set(&this->out3,
				(this->gear == CCU_GEAR_1 &&
						(dev.assembly.backsteer_installed ||
								telescope_get_current(&dev.telescope) == 0)) ?
								((this->conf->gear_conf[0].assembly_invert) ? -backreq : backreq) : 0);
	}

	// 4WD drive on first gear
	if (uv_dual_solenoid_output_get_current(&this->out1)) {
		if (this->conf->gear_conf[1].assembly_invert) {
			this->d4wd_req = (this->gear == CCU_GEAR_1) ? OUTPUT_STATE_ON : OUTPUT_STATE_OFF;
		}
		else {
			this->d4wd_req = (this->gear != CCU_GEAR_1) ? OUTPUT_STATE_ON : OUTPUT_STATE_OFF;
		}
	}
	else {
		this->d4wd_req = OUTPUT_STATE_OFF;
	}
	// if loading space telescope is moving,
	// d4wd is always ON to make sure the wheels can rotate freely
	// Note: On UW LM telescope output is used to control back steering,
	// thus assembly.telescope_installed has to be checked
	if (dev.assembly.telescope_installed && telescope_get_current(&dev.telescope)) {
		this->d4wd_req = OUTPUT_STATE_ON;
	}
	// trigger the PDO transmission right away
	if (input_pressed(&this->input)) {
		uv_canopen_pdo_mapping_update(CCU_D4WD_REQ_INDEX, CCU_D4WD_REQ_SUBINDEX);
	}

	// enable brake when driving
	uv_output_set_state(&this->brake,
			(uv_dual_solenoid_output_get_current(&this->out1) ||
					uv_dual_solenoid_output_get_current(&this->out2)) ?
							OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

	// control gear3 valve when driving with 3rd gear
	uv_output_state_e onstate = (this->conf->gear_conf[2].assembly_invert) ?
			OUTPUT_STATE_ON : OUTPUT_STATE_OFF;
	uv_output_state_e offstate = (onstate == OUTPUT_STATE_ON) ?
			OUTPUT_STATE_OFF : OUTPUT_STATE_ON;
	if (uv_dual_solenoid_output_get_current(&this->out1) == 0 &&
			uv_dual_solenoid_output_get_current(&this->out2) == 0) {
		uv_output_set_state(&this->gear3, OUTPUT_STATE_OFF);
	}
	else {
		uv_output_set_state(&this->gear3,
				(this->gear == CCU_GEAR_2) ? onstate : offstate);
	}

}

