#include <stdio.h>

#include "sampling2.h"
#include "regfile.h"
#include "terminal.h"
#include "interpreter.h"

int main(){
	printf("---- BEGIN MICROCONTROLLER SIMULATOR ----\n");
	
	initialize_terminal();
	
	RegFile_init();
	RegFile_new_SampleRegister(20, 20);
	
	for(int i = 0; i<100; i++)
		RegFile_write_SampleRegister(0);
	
	while(!exit_flag)
		loop_terminal();
	/*SampleRegister_plot(GlobalRegFile.registers[0],1,1);
	printf("\n----\n");
	SampleRegister_plot(GlobalRegFile.registers[0],2,1);
	printf("\n----\n");
	SampleRegister_plot(GlobalRegFile.registers[0],5,1);*/
	//printf("\n----\n");
	
	printf("---- END MICROCONTROLLER SIMULATOR ----\n");
	/*
	token tokens[MAX_NUM_TOKENS];
	
	char buffer[MAX_BUFFER_LENGTH] = "Hello this is a test";
	
	uint8_t token_num = tokens_from_buffer(buffer, tokens);
	printf("Num tokens=%d\n",token_num);
	
	for(uint8_t i = 0; i<token_num; i++){
		printf("tok[%d]= %s\n",i,tokens[i]);
	}*/
	
	return 0;
}