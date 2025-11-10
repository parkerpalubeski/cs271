/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH+2

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

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

struct c_instruction{
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jmp: 3;
};

struct a_instruction{
    union{
        char* label;
    } hack_addr;
    bool is_addr;
};

struct instruction{
    union{
        struct a_instruction a;
        struct c_instruction c;
    };
    enum instr_type type;
};