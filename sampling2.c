#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "sample.h"
#include "sampling2.h"

/***********************************/
/**Static Functions**/

/* Empty an array of samples */
static void clean_samples(Sample* samples, uint16_t num_samples){
	for(uint16_t i = 0; i<num_samples; i++){
		samples[i] = 0;
	}
}

/* If there is room left to put another sample */
static bool has_sample_room(SampleRegister sr){
	uint16_t num_samples = sr.num_samples;
	uint16_t last_index = sr.last_index;
	
	return (last_index < num_samples);
}

/***********************************/
/**Function Definitions**/

/* Generates a new SampeRegister */
SampleRegister new_SampleRegister(uint8_t reg_id, uint16_t num_samples, uint16_t time_sampled){
	SampleRegister sr;
	
	sr.reg_id = reg_id;
	sr.num_samples = (num_samples <= MAX_NUM_SAMPLES) ? num_samples : MAX_NUM_SAMPLES; // So we don't overflow samples
	sr.time_sampled = time_sampled;
	
	sr.dirty = false;
	sr.last_index = 0;
	
	clean_samples(sr.samples, sr.num_samples); // So we have a nice clean sample array
	
	return sr;
}

/* Adds a sample at the next available index in the SampleRegister */
/* True if successful, else false */
bool add_Sample(SampleRegister* sr, Sample s){
	if(!has_sample_room(*sr)) return false; // No more room --> false
	
	//printf("RECEIVED_SAMPLE=%d\n",s);
	
	uint16_t last_index = sr->last_index;
	sr->samples[last_index] = s;
	sr->last_index++;
	
	return true;
}

/***********************************/
/** Functions for Testing (TODO: REMOVE) **/

void print_SampleRegister(SampleRegister sr){
	printf("--SampleRegister[%d]: num_samples=%d, time_sampled=%d, is_dirty=%s, last_index=%d\n", sr.reg_id, sr.num_samples, sr.time_sampled, sr.dirty?"YES":"NO", sr.last_index);
	for(int16_t i = 0; i<sr.num_samples; i++){
		printf("%4d : %d\n",i,sr.samples[i]);
	}
	printf("----\n");
}

/*int main(){
	SampleRegister sr = new_SampleRegister(0, 20, 0);
	
	for(int i = 0; i<100; i++){
		add_Sample(&sr,i);
	}
	
	print_SampleRegister(sr);
	return 0;
}*/