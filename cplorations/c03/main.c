/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] PARKER PALUBESKI
 * [TERM] FALL 2025
 * 
 ****************************************/

#define MAX_LINE_LENGTH 200
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[]){
    //Exercise 2
    if(argc != 2){
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //Exercise 3
    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){
        perror("Unable to open file!");
        exit(EXIT_FAILURE);
    }
    //Exercise 4
    char out_file[50];
    out_file[0] = '\0';
    strcpy(out_file, argv[1]);
    strcat(out_file, ".echo");
    FILE *fout = fopen(out_file, "w+");
    //Exercise 5
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;

    while(fgets(line, sizeof(line), fin)){
        line_num++;
        printf("[%04d] %s", line_num, line);
        fprintf(fout, "%s", line);
    }
    //Exercise 6
    fclose(fin);
    fclose(fout);
    return 0;
}