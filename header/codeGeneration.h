

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>


extern FILE* out_file;

void makeCodeDeclaration(char* identifier, Type type, char* value);
void makeCodeWrite(char *id);
void makeCodeEndDeclaration();
void makeCodeRead(char *id);
void makeCodeWriteln(char *id);
void makeCodeReadln(char *id);
void makeCodeAssignment(char *value, char *valueReal);
void makeCodeStack(char *id);
void makeCodeAdd();
void makeCodeSub();
void makeCodeMul();

#endif

