/*
 * uw_messages.h
 *
 *  Created on: Jan 27, 2015
 *      Author: usenius
 */

#ifndef GSM_MESSAGES_H_
#define GSM_MESSAGES_H_

#include <uv_reset.h>
#include <stdint.h>
#include <uv_terminal.h>
#include <uv_canopen.h>




int obj_dict_len();



/// @brief: Lists all gsm commands
typedef enum {
	CMD_STAT = 0,
	CMD_SET,
	CMD_COUNT
} gsm_commands_e;


// define of commands variable declared in gsm_messages.c
extern const uv_command_st terminal_commands[];
unsigned int commands_size(void);


#endif /* GSM_MESSAGES_H_ */
