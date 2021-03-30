#ifndef SAMPLING_H
#define SAMPLING_H

#include <stdint.h>
#include <stdbool.h>

#include "sample.h"

/***********************************/

SampleRegister new_SampleRegister(uint8_t reg_id, uint16_t num_samples, uint16_t time_sampled);

/***********************************/

bool add_Sample(SampleRegister* sr, Sample s);

/***********************************/

/** TODO: REMOVE **/
void print_SampleRegister(SampleRegister sr);

#endif
