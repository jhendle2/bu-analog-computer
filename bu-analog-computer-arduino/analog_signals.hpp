/** --- Analog Signals between the ShieldBuddy and Analog Components ---
- Written by Jonah Hendler and Ashley Granieri
- Last Updated: 2/18/2021
**/

#ifndef ANALOG_SIGNALS_H
#define ANALOG_SIGNALS_H

  #include <stdint.h>
  #include "sample.hpp"

  // Analog Pins
  #define ADC0 ADQ0 // 14-bit resolution, name subject to change
  #define ADC1 ADQ1 // 14-bit resolution, name subject to change

  Sample receive_from_adc0();
  Sample receive_from_adc1();

#endif
