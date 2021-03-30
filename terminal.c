#include <stdio.h>

#include "sample.h"
#include "sampling2.h"
#include "terminal.h"
#include "interpreter.h"

/***********************************/
/** Plotting **/

void initialize_terminal(){
	exit_flag = false;
	t_scale = 1.0;
	y_scale = 1.0;
}

/* Find the lowest value in a SampleRegister */
static Sample min_Sample(SampleRegister sr){
	Sample lowest_value = 0;
	
	for(uint16_t i = 0; i<sr.num_samples; i++){
		Sample s = sr.samples[i];
		if(s<lowest_value) lowest_value = s;
	}
	
	return lowest_value;
}

/* Find the highest value in a SampleRegister */
static Sample max_Sample(SampleRegister sr){
	Sample highest_value = 0;
	
	for(uint16_t i = 0; i<sr.num_samples; i++){
		Sample s = sr.samples[i];
		if(s>highest_value) highest_value = s;
	}
	
	return highest_value;
}

void SampleRegister_plot(SampleRegister sr){
	uint16_t t_min = 0, t_max = sr.num_samples;
	Sample y_min = min_Sample(sr), y_max = max_Sample(sr); // Doesn't do anything rn

	double t_scale_double = 1.0;
	if(t_scale > 0) t_scale_double = 1.0/(double)(t_scale);
	else if(t_scale < 0) t_scale_double = (double)(-t_scale);	

	double y_scale_double = 1.0;
	if(y_scale > 0) y_scale_double = (double)(y_scale);
	else if(y_scale < 0) y_scale_double = 1.0/(double)(-y_scale);

	for(double i = t_min; i<t_max; i+=t_scale_double){
		uint8_t sample_index = (uint8_t)(i);
		Sample s = sr.samples[sample_index];
		s = (Sample)((double)(s) * y_scale_double);
		printf("%4d|",sample_index);
		for(int16_t y = 0; y<s; y++){
			printf(".");
		}printf("#\n");
	}
}

/***********************************/
/** Kernel **/

void loop_terminal(){
	token tokens[MAX_NUM_TOKENS];
	
	char buffer[MAX_BUFFER_LENGTH];
	printf("ANCOM>");
	fgets(buffer, MAX_BUFFER_LENGTH, stdin);
	
	uint8_t num_tokens = tokens_from_buffer(buffer, tokens);
	
	execute_command(tokens, num_tokens);
}
