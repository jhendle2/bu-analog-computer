#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "sampling2.h"
#include "sample.h"
#include "regfile.h"

#include "analog_signals.h"

static bool RegFile_valid_register(uint8_t reg_id){
	return (reg_id < GlobalRegFile.num_registers); // Should really throw an error of some kind...	
}

void RegFile_init(){
	GlobalRegFile.num_registers = 0;
	
	for(int i = 0; i<MAX_NUM_REGISTERS; i++){
		GlobalRegFile.registers[i] = new_SampleRegister(i, 0, 0);
	}
}

void RegFile_new_SampleRegister(uint16_t num_samples, uint16_t time_sampled){
	uint8_t last_register = GlobalRegFile.num_registers;
	
	if(last_register >= MAX_NUM_REGISTERS) return;
	GlobalRegFile.registers[last_register] = new_SampleRegister(last_register, num_samples, time_sampled);
	
	GlobalRegFile.num_registers++;
}

void RegFile_init_SampleRegister(uint8_t reg_id, uint16_t num_samples, uint16_t time_sampled){
	GlobalRegFile.registers[reg_id] = new_SampleRegister(reg_id, num_samples, time_sampled);
}

void RegFile_clear(uint8_t reg_id){
	for(uint8_t i = 0; i<MAX_NUM_SAMPLES; i++){
		GlobalRegFile.registers[reg_id].samples[i] = 0;	
	}
}

SampleRegister RegFile_read_SampleRegister(uint8_t reg_id){
	if(!RegFile_valid_register(reg_id)) reg_id = 0;
	return GlobalRegFile.registers[reg_id];
}

bool RegFile_write_SampleRegister(uint8_t reg_id){
	Sample read_sample = receive_from_adc0(); // Grab sample from pins
	//printf("READ_SAMPLE=%d\n",read_sample);
	
	if(!RegFile_valid_register(reg_id)) return false;
	bool result = add_Sample(&GlobalRegFile.registers[reg_id], read_sample);
	
	return result;
}