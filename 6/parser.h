/****************************************
 * C-Project 6 for CS 271
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
#include "symtable.h"

#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_INSTRUCTION_COUNT 30000

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

bool is_Atype(const char *c);
bool is_label(const char *c);
bool is_Ctype(const char *c);

char *extract_label(const char *line, char* label);

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type{
    invalid = -1,
    a_type,
    c_type,
};

typedef struct c_instruction{
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jmp:4;
}c_instruction;

typedef struct a_instruction{
    union{
        char* label;
        uint16_t hack_addr;
    };
    bool is_addr;
}a_instruction;

typedef struct instruction{
    union{
        a_instruction a;
        c_instruction c;
    };
    enum instr_type type;
}instruction;


int parse(FILE * file, instruction *instructions);

void add_predefined_symbols();

bool parse_A_instruction(const char *line,  a_instruction *instr);

void parse_C_instruction(const char *line, c_instruction *instr);

void assemble(const char* file_name, instruction* instructions, int instr_num);

#endif