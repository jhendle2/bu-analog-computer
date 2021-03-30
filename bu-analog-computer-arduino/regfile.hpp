/** --- RegFile for the ShieldBuddy ---
- Written by Jonah Hendler and Ashley Granieri
- Last Updated: 2/18/2021
**/

#ifndef REGFILE_H
#define REGFILE_H

  #include <stdint.h>
  #include <stdbool.h>
  
  #include "sample.hpp"
  #include "sampling.hpp"
  
  #define MAX_NUM_REGISTERS 21 // How many SampleRegisters we can have in the RegFile
  
  typedef struct RegFile{
    
    uint8_t num_registers; // How many SampleRegisters we have
    SampleRegister registers[MAX_NUM_REGISTERS]; // SampleRegisters
    
  } RegFile;
  
  RegFile GlobalRegFile; // The main RegFile for the entire Analog Computer
  
  void RegFile_init(); // Initialize the GlobalRegFile
  
  void RegFile_new_SampleRegister(uint16_t num_samples, uint16_t time_sampled); // Create the next available SampleRegister in GlobalRegFile
  
  void RegFile_clear(uint8_t reg_id);
  
  void RegFile_init_SampleRegister(uint8_t reg_id, uint16_t num_samples, uint16_t time_sampled); // Initialize our a SampleRegister in the GlobalRegFile

  SampleRegister RegFile_read_SampleRegister(uint8_t reg_id); // Read a register from the RegFile

  bool RegFile_write_SampleRegister(uint8_t reg_id);  // Read from ReadAD0/1() and write into SampleRegister with reg_id
  
#endif
