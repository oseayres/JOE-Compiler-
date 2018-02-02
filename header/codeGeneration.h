

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>


extern FILE* out_file;

void makeCodeDeclaration(char* identifier, Type type, char* value);
void makeCodeWrite(char *id);
void makeCodeEndDeclaration();
void makeCodeRead(char *id);




#endif

