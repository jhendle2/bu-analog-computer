#include "analog_signals.h"
#include "sample.h"

#include <math.h>

Sample receive_from_adc0(){
	static int out = 1;
	uint16_t val = (int)(5.0*sin(M_PI * (double)(out) / 4.0) + 5.0);
	out++;
	return val;
}
Sample receive_from_adc1(){
	return 11;
}