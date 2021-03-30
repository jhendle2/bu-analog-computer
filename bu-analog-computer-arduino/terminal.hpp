/** --- RegFile for the ShieldBuddy ---
- Written by Jonah Hendler and Ashley Granieri
- Last Updated: 2/18/2021
**/

#ifndef TERMINAL_H
#define TERMINAL_H

  #include <stdbool.h>
  #include "sampling.hpp"

  #define ARDUINO_BAUDRATE 9600 // Wire.begin(), Pins 20 and 21 (or 6 and 7) --> Wire.setwirepins()

  void initialize_terminal();

  /* Plot a SampleRegister, + Scale = Bigger, - Scale = Smaller */
  void SampleRegister_plot(SampleRegister sr);

  bool exit_flag;
  int8_t t_scale, y_scale;

  void loop_terminal();

#endif
