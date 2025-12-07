/****************************************
 * C-ploration 9 for CS 271
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
void parse(FILE * file){
	char line[MAX_LINE_LENGTH];
//	char inst_type;
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	struct instruction instr;
	add_predefined_symbols();
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
			instr_num++;
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
			instr_num++;
		}
//		printf("%c  %s\n", inst_type, line);
    }
	
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


bool parse_A_instruction(const char *line, struct a_instruction *instr){
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
	return true;
}

void parse_C_instruction(const char *line, struct c_instruction *instr){
	char* temp = strtok(line, ";");
	char* dest = strtok(line, "=");
	char* jump = strtok(NULL, " ");
	
}