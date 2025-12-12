/****************************************
 * C-Project 6 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char s_new[MAX_LINE_LENGTH + 1] ={0};
	int i = 0;
	for (char *s2 = s; *s2; s2++){
		if(*s2 == '/' && *(s2+1) == '/'){
			break;
		} else if(isspace(*s2) == 0){
			s_new[i++] = *s2;
		}
	}
	strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions){
	char line[MAX_LINE_LENGTH];
//	char inst_type;
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	instruction instr;
	add_predefined_symbols();
	char tmp_line[MAX_LINE_LENGTH];
	while(fgets(line, sizeof(line), file)){
		line_num++;
		if(instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		if(line[0] == '\0'){
			continue;
		}
		//Logic to determine command type
		else if(is_Atype(line) == 1){
			if(!parse_A_instruction(line, &instr.a)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.type = a_type;
//			inst_type = 'A';
//			printf("%u: %c  %s\n", instr_num, inst_type, line);
			instructions[instr_num] = instr;
			instr_num++;
			if(instr.a.is_addr){
				printf("A: %d\n", instr.a.hack_addr);
			}else{
				printf("A: %s\n", instr.a.label);
			}
		}else if(is_label(line) == 1){
//			inst_type = 'L';
			char label[MAX_LINE_LENGTH];
			extract_label(line, label);
			if(isalpha(label[0]) == 0){
				exit_program(EXIT_INVALID_LABEL, line_num, label);
			}else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
			}
			strcpy(line, label);
			symtable_insert(line, instr_num);
		}else if(is_Ctype(line) == 1){
//			inst_type = 'C';
//			printf("%u: %c  %s\n", instr_num, inst_type, line);
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.c);
			if(instr.c.comp == -1){
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}else if(instr.c.jmp == -1){
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}else if(instr.c.dest == -1){
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			instr.type = c_type;
			instructions[instr_num] = instr;
			instr_num++;
			printf("C: d=%d, c=%d, j=%d\n", instr.c.dest, instr.c.comp, instr.c.jmp);
		}
//		printf("%c  %s\n", inst_type, line);
    }
	return instr_num;
	
}

bool is_Atype(const char *line){
	if(line[0] == '@'){
		return true;
	}else{
		return false;
	}
}

bool is_label(const char *line){
	if(line[0] == '(' && line[strlen(line)-1] == ')'){
		return true;
	}else{
		return false;
	}
}

bool is_Ctype(const char *line){
	//Considering process of elimination prior, any that don't pass the above tests should be Ctype
	return true;
}

char *extract_label(const char *line, char* label){
	char temp[MAX_LINE_LENGTH] = "";
	int i = 1;
	while(i < strlen(line) - 1){
		temp[i-1] = line[i];
		i++;
	}
	temp[i-1] = '\0';
	strcpy(label, temp);
	return label;
}

void add_predefined_symbols(){
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		predefined_symbol sym = predefined_symbols[i];
		symtable_insert(sym.name, sym.address);
	}
}


bool parse_A_instruction(const char *line, a_instruction *instr){
	char* s = malloc(strlen(line));
	strcpy(s, line+1);
	char* s_end = NULL;
	long result = strtol(s, &s_end, 10);
	if(s == s_end){
		instr->label = malloc(strlen(line+1)+1);
		strcpy(instr->label, s);
		instr->is_addr = false;
	} else if(*s_end != 0){
		return false;
	} else{
		instr->hack_addr = result;
		instr->is_addr = true;
	}
	free(s);
	return true;
}

void parse_C_instruction(const char *line, c_instruction *instr) {
	char copy[MAX_LINE_LENGTH];
    strcpy(copy, line);

	char *temp = strtok(copy, ";");
	char *jump = strtok(NULL, "\n");
	char *dest = strtok(temp, "=");
	char *comp = strtok(NULL, "\n");
	if (comp == NULL) {
		comp = dest;
        dest = NULL;
    }
    int a = 0;
    instr->jmp  = str_to_jumpid(jump);
    instr->dest = str_to_destid(dest);
    instr->comp = str_to_compid(comp, &a);
    instr->a = a;
}

void assemble(const char* file_name, instruction* instructions, int instr_num){
	//Open/create file for writing
	char temp[40];
	strcpy(temp, file_name);
	char* file = temp;
	strcat(file, ".hack");
	printf("Opening file for writing: %s\n", file);
	FILE *fout = fopen(file, "w+");
    if(fout == NULL){ 
        exit_program(EXIT_CANNOT_OPEN_FILE, file);
    }
	opcode curr;
	int avail_addr = 16;
	for(int i = 0; i < instr_num; i++){
		if(instructions[i].type == a_type){
			if(instructions[i].a.is_addr == true){ //A-type Address
//				printf("Debug: A-type address\n");
				curr = instructions[i].a.hack_addr;
			}else{ // A-type Label
//				printf("Debug: A-type Label: %s\n", instructions[i].a.label);
				struct Symbol *a = (symtable_find(instructions[i].a.label));
				if(a!=NULL){
					curr = a->addr;
				}else{
//					printf("Label not found in symbol table. Inserting: %s\n",instructions[i].a.label);
					curr = avail_addr;
					symtable_insert(instructions[i].a.label, avail_addr);
					avail_addr++;
				}

			}
		}else{ //C-type
//			printf("C-type instruction\n");
			curr = instruction_to_opcode(instructions[i].c);
			
		}
		//fprints, prevents hanging empty line at the end
		if(i != 0){
			fprintf(fout, "\n");
			printf("\n");
		}
		fprintf(fout, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", OPCODE_TO_BINARY(curr));
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", OPCODE_TO_BINARY(curr));
	}





	//Close file pointer
	fclose(fout);
}

opcode instruction_to_opcode(c_instruction instr){
	opcode op = 0;
	op = (7 << 13);
	op |= instr.a << 12;
    op |= instr.comp << 6;
    op |= instr.dest << 3;
    op |= instr.jmp;
	return op;
}