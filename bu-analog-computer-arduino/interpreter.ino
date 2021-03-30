//#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "interpreter.hpp"

#include "terminal.hpp"
#include "regfile.hpp"

// Empty every token
static void clean_tokens(struct token tokens[MAX_NUM_TOKENS]){
  for(uint8_t i = 0; i<MAX_NUM_TOKENS; i++){
    tokens[i].str[0] = 0;
  }
}

uint8_t tokens_from_buffer(char buf[MAX_BUFFER_LENGTH],struct token tokens[MAX_NUM_TOKENS]){
  clean_tokens(tokens);
  
  uint8_t token_index = 0;
  uint8_t temp_token_index = 0;
  struct token temp_token;
  for(uint8_t i = 0; i<MAX_BUFFER_LENGTH; i++){
    char bufc = buf[i];
    if(token_index >= MAX_NUM_TOKENS) break;
    
    if(temp_token_index >= MAX_TOKEN_LENGTH ||
    bufc == ' ' || bufc == '\t' || bufc == '\n' || bufc == '\r' || bufc == '\0'){
      temp_token.str[temp_token_index] = 0;
      strcpy(tokens[token_index++].str,temp_token.str);
      temp_token_index = 0;
    }
    else{
      temp_token.str[temp_token_index++] = bufc;
    }
    
    if(bufc == '\0' || bufc == '\n' || bufc == '\r') break;
  }
  
  return token_index;
}

void execute_command(struct token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
  struct token command;
  strcpy(command.str,tokens[0].str);
  
  if(strcmp(command.str,"scale")==0) command_scale(tokens, num_tokens);
  else if(strcmp(command.str,"plot")==0) command_plot(tokens, num_tokens);
  else if(strcmp(command.str,"preg")==0) command_print_register(tokens, num_tokens);
  else if(strcmp(command.str,"clear")==0) command_clear_register(tokens, num_tokens);
  else if(strcmp(command.str,"exit")==0) exit_flag = true;
}

/*********************************/
/** Commands **/

// scale y 0 t 1
void command_scale(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
  if(tokens[1].str[0] == 'y'){
    if(tokens[2].str[0] != 't'){
      y_scale = (double)(atoi(tokens[2].str));
    }
    
    if(num_tokens < 4) return;
    
    if(tokens[3].str[0] == 't'){
      t_scale = (double)(atoi(tokens[4].str));
    }
  }
  else if(tokens[1].str[0] == 't'){
    if(tokens[2].str[0] != 'y'){
      t_scale = (double)(atoi(tokens[2].str));
    }
    
    if(num_tokens < 4) return;
    
    if(tokens[3].str[0] == 'y'){
      y_scale = (double)(atoi(tokens[4].str));
    }
  }
  
  Serial.print(">> Set plot scales: time=%d, amplitude=%d");
  Serial.print(t_scale);
  Serial.println(y_scale);
}

void command_print_register(struct token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
  if(num_tokens < 2){
    Serial.print("!! Error: Invalid syntax. Too few tokens.\n");
    return;
  }
  
  /* PUT MORE PROTECTIONS HERE */
  uint8_t reg_id = atoi(tokens[1].str);
  if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
    Serial.print("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
    return;
  }
  print_SampleRegister(GlobalRegFile.registers[reg_id]);
}

void command_clear_register(struct token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
  if(num_tokens < 2){
    Serial.print("!! Error: Invalid syntax. Too few tokens.\n");
    return;
  }
  
  /* PUT MORE PROTECTIONS HERE */
  uint8_t reg_id = atoi(tokens[1].str);
  if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
    Serial.print("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
    return;
  }
  RegFile_clear(reg_id);
}

void command_plot(struct token tokens[MAX_NUM_TOKENS], uint8_t num_tokens){
  if(num_tokens < 2){
    Serial.print("!! Error: Invalid syntax. Too few tokens.\n");
    return;
  }
  
  /* PUT MORE PROTECTIONS HERE */
  uint8_t reg_id = atoi(tokens[1].str);
  if(reg_id > MAX_NUM_REGISTERS || reg_id < 0){
    Serial.print("!! Error: Register ID out of bounds. Must be a value between 0 and 20.\n");
    return;
  }
  SampleRegister_plot(GlobalRegFile.registers[reg_id]); 
}
