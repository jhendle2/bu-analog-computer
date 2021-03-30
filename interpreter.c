#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "interpreter.h"

#include "terminal.h"
#include "regfile.h"

// Empty every token
static void clean_tokens(token tokens[MAX_NUM_TOKENS]){
	for(uint8_t i = 0; i<MAX_NUM_TOKENS; i++){
		tokens[i][0] = 0;
	}
}

uint8_t tokens_from_buffer(char buffer[MAX_BUFFER_LENGTH], token tokens[MAX_NUM_TOKENS]){
	clean_tokens(tokens);
	
	uint8_t token_index = 0;
	uint8_t temp_token_index = 0;
	token temp_token;
	for(uint8_t i = 0; i<MAX_BUFFER_LENGTH; i++){
		char bufc = buffer[i];
		if(token_index >= MAX_NUM_TOKENS) break;
		
		if(temp_token_index >= MAX_TOKEN_LENGTH ||
		bufc == ' ' || bufc == '\t' || bufc == '\n' || bufc == '\r' || bufc == '\0'){
			temp_token[temp_token_index] = 0;
			strcpy(tokens[token_index++],temp_token);
			temp_token_index = 0;
		}
		else{
			temp_token[temp_token_index++] = bufc;
		}
		
		if(bufc == '\0' || bufc == '\n' || bufc == '\r') break;
	}
	
	return token_index;
}

void execute_command(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
	token command;
	strcpy(command,tokens[0]);
	
	if(strcmp(command,"scale")==0) command_scale(tokens, num_tokens);
	else if(strcmp(command,"plot")==0) command_plot(tokens, num_tokens);
	else if(strcmp(command,"preg")==0) command_print_register(tokens, num_tokens);
	else if(strcmp(command,"clear")==0) command_clear_register(tokens, num_tokens);
	else if(strcmp(command,"exit")==0) exit_flag = true;
}

/*********************************/
/** Commands **/

// scale y 0 t 1
void command_scale(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
	if(tokens[1][0] == 'y'){
		if(tokens[2][0] != 't'){
			y_scale = (double)(atoi(tokens[2]));
		}
		
		if(num_tokens < 4) return;
		
		if(tokens[3][0] == 't'){
			t_scale = (double)(atoi(tokens[4]));
		}
	}
	else if(tokens[1][0] == 't'){
		if(tokens[2][0] != 'y'){
			t_scale = (double)(atoi(tokens[2]));
		}
		
		if(num_tokens < 4) return;
		
		if(tokens[3][0] == 'y'){
			y_scale = (double)(atoi(tokens[4]));
		}
	}
	
	printf(">> Set plot scales: time=%d, amplitude=%d\n",t_scale,y_scale);
}

void command_print_register(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
	if(num_tokens < 2){
		printf("!! Error: Invalid syntax. Too few tokens.\n");
		return;
	}
	
	/* PUT MORE PROTECTIONS HERE */
	uint8_t reg_id = atoi(tokens[1]);
	if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
		printf("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
		return;
	}
	print_SampleRegister(GlobalRegFile.registers[reg_id]);
}

void command_clear_register(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
	if(num_tokens < 2){
		printf("!! Error: Invalid syntax. Too few tokens.\n");
		return;
	}
	
	/* PUT MORE PROTECTIONS HERE */
	uint8_t reg_id = atoi(tokens[1]);
	if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
		printf("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
		return;
	}
	RegFile_clear(reg_id);
}

void command_plot(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
	if(num_tokens < 2){
		printf("!! Error: Invalid syntax. Too few tokens.\n");
		return;
	}
	
	/* PUT MORE PROTECTIONS HERE */
	uint8_t reg_id = atoi(tokens[1]);
	if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
		printf("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
		return;
	}
	SampleRegister_plot(GlobalRegFile.registers[reg_id]);	
}