/** --- Digital Signals between the ShieldBuddy and Analog Components ---
- Written by Jonah Hendler and Ashley Granieri
- Last Updated: 2/18/2021
**/

#ifndef DIGITAL_SIGNALS_H
#define DIGITAL_SIGNALS_H

	// Digital Pins
	#define DAC0 DAQ0	// 14-bit resolution, name subject to change
	#define DAC1 DAQ1	// 14-bit resolution, name subject to change

	void send_to_dac0(uint16_t data);
	void send_to_dac1(uint16_t data);
	
	/*********************************/
	
	#define TRIGGER ??? // 1-bit Trigger for analog components

	void activate_trigger();
	void deactive_trigger();

#endif