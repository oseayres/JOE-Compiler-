

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <codeGeneration.h>





void makeCodeDeclaration(char* identifier, Type type, char* value)
{
    if (type == INTEGER)
    {
        if (value == NULL)
        	fprintf(out_file, "%s: dd 0\n", identifier);

        else
        {
        	int x = atoi(value);
        	fprintf(out_file, "%s: dd %d\n", identifier, x);
        }
    }

    else if (type == REAL)
    {
    	if (value == NULL)
        	fprintf(out_file, "%s: dq 0 \n", identifier);

        else
        {
          	double x = atof(value);
        	fprintf(out_file, "%s: dq %f\n", identifier, x);
        }
    }

    else if (type == STRING)
    {
    	if (value == NULL)
        	fprintf(out_file, "%s: db 0 \n", identifier);

        else
        {
          	fprintf(out_file, "%s: db %s, 0\n", identifier, value);
        }
    }
}

void makeCodeEndDeclaration()
{
    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\nmain:\n");
    

}

void makeCodeWrite(char *id)
{
    SymTableEntry *ret;
    ret = findSymTable(&table,id);

    if(ret == NULL)
    {

    }else
    {
        if(ret->type == INTEGER){
            fprintf(out_file, "mov rdi, fmt_d\n");
            fprintf(out_file, "mov rsi, [%s]\n", ret->identifier);
        }else if(ret->type == REAL)
        {
            fprintf(out_file, "mov rdi, fmt_f\n");
            fprintf(out_file, "mov rsi, [%s]\n", ret->identifier);
        }else
        {
            fprintf(out_file, "mov rdi, fmt_s\n");
             fprintf(out_file, "mov rsi, %s\n", ret->identifier);
        }

       
        fprintf(out_file, "mov rax, 0\n");
        fprintf(out_file, "call printf\n");

    }

}