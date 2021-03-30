#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdint.h>

#define MAX_TOKEN_LENGTH 16
#define MAX_NUM_TOKENS 8
#define MAX_BUFFER_LENGTH 128

typedef char token[MAX_TOKEN_LENGTH];

// Fills a token array with all tokens and returns number of tokens
uint8_t tokens_from_buffer(char buffer[MAX_BUFFER_LENGTH], token tokens[MAX_NUM_TOKENS]);

void execute_command(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens);

/** Commands **/

// Sets the t_scale and y_scale of the plotter
void command_scale(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens);

void command_print_register(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens);

void command_plot(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens);
void command_clear_register(token tokens[MAX_NUM_TOKENS], uint8_t num_tokens);



#endif