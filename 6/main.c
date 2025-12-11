/****************************************
 * C-Project 6 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/

#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        // incorrect number of arguments
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
    } 
    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){ 
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }
    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
	int instr_num = parse(fin, instructions);
    assemble(argv[1], instructions, instr_num);
//    symtable_print_labels();
    free(instructions);
    //Line to prevent warning until project is completed
	fclose(fin);
}


