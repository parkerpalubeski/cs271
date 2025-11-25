/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *c);
bool is_label(const char *c);
bool is_Ctype(const char *c);

char *extract_label(const char *line, char* label);

void add_predefined_symbols();

#endif