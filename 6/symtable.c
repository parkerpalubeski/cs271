/****************************************
 * C-Project 6 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/

#include "symtable.h"

struct Symbol* hashArray[SYMBOL_TABLE_SIZE] = {0};

unsigned int hash(const char *str){
    unsigned long hash = 5381;
    unsigned char c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash %= SYMBOL_TABLE_SIZE;
}

void symtable_insert(char* name, hack_addr addr){
    struct Symbol *sym = (struct Symbol*)malloc(sizeof(struct Symbol));
    sym->addr = addr;
    sym->name = strdup(name);
    unsigned int hashIndex = hash(name) % SYMBOL_TABLE_SIZE;
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL){
        hashIndex++;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    hashArray[hashIndex] = sym;
}

struct Symbol *symtable_find(char* name){
    int hashIndex = hash(name);
    while(hashArray[hashIndex] != NULL){
        if(strcmp(hashArray[hashIndex]->name, name)== 0){
            return hashArray[hashIndex];
        }
        hashIndex++;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

void symtable_display_table(){
    int i = 0;
    for(i = 0; i < SYMBOL_TABLE_SIZE; i++){
        if(hashArray[i] != NULL){
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}

void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
} 