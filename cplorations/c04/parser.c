/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/
#include "parser.h"

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
	while(fgets(line, sizeof(line), file)){
		strip(line);
		if(line[0] == '\0'){
			continue;
		}
		printf("%s\n", line);
    }
}