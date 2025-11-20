/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/

#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

struct Symbol{
    char* name;
    hack_addr addr;
};

unsigned int hash(const char *str);
struct Symbol *symtable_find(char* name);
void symtable_insert(char* name, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif