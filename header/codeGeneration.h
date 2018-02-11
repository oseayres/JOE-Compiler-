

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>

// Tamanho de um string nao inicializada
#define STRING_SIZE 256

#define JUMPS_ARRAY_OFFSET 4
extern char jumps[10][4];


extern FILE* out_file;

void makeLabel(char* out_label);
void dumpCodeDeclarationEnd();
void makeCodeWrite(char* dest, char *id, int ln);
void makeCodeRead(char* dest, char *id);

void makeCodeDeclaration(char* dest, char* identifier, Type type, char* value);


void makeCodeAssignment(char *value, char *valueReal);
void makeCodeStack(char *id);
void makeCodeAdd();	
void makeCodeSub();
void makeCodeMul();
void makeCodeComp(char* dest, char* id, char* id2);
void makeCodeIf(char* dest, char* expr_code, int expr_jump, char* block_code);

#endif

