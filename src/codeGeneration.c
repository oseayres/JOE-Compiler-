

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


void makeCodeAssignment(char *value, char *valueReal)
{   
    SymTableEntry *ret;
    ret = findSymTable(&table,value);

    if(ret == NULL)
    {
        // not found in table
    }else
    {
        if(ret->type == INTEGER)
        {
            fprintf(out_file, "pop rbx\n");
            // fprintf(out_file, "mov rbx, %s\n",valueReal);
            fprintf(out_file, "mov [%s], rbx\n", ret->identifier);


        }
        else
        {
            printf("SOU um compilador burro e nao sei somar float ou string\n");
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
        if(ret->type == INTEGER)
        {
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


void makeCodeRead(char *id)
{
    SymTableEntry *ret;
    ret = findSymTable(&table,id);


    if(ret == NULL)
    {

    }
    else
    {
        if(ret->type == INTEGER){
            fprintf(out_file, "mov rdi, fmt_d\n");
            fprintf(out_file, "mov rsi, %s\n", ret->identifier);
        }else if(ret->type == REAL)
        {
            fprintf(out_file, "mov rdi, fmt_f\n");
            fprintf(out_file, "mov rsi, %s\n", ret->identifier);
        }else
        {
            fprintf(out_file, "mov rdi, fmt_s\n");
             fprintf(out_file, "mov rsi, %s\n", ret->identifier);
        }

       
        fprintf(out_file, "mov rax, 0\n");
        fprintf(out_file, "call scanf\n");

    }

}

void makeCodeWriteln(char *id)
{
    SymTableEntry *ret;
    ret = findSymTable(&table,id);

    if(ret == NULL)
    {

    }else
    {
        if(ret->type == INTEGER)
        {
            fprintf(out_file, "mov rdi, fmt_dln\n");
            fprintf(out_file, "mov rsi, [%s]\n", ret->identifier);
        }else if(ret->type == REAL)
        {
            fprintf(out_file, "mov rdi, fmt_fln\n");
            fprintf(out_file, "mov rsi, [%s]\n", ret->identifier);
        }else
        {
            fprintf(out_file, "mov rdi, fmt_sln\n");
             fprintf(out_file, "mov rsi, %s\n", ret->identifier);
        }

       
        fprintf(out_file, "mov rax, 0\n");
        fprintf(out_file, "call printf\n");

    }

}


void makeCodeStack(char *id)
{
    fprintf(out_file, "mov rax,%s\n",id );
    fprintf(out_file, "push rax\n");
}

void makeCodeAdd()
{
    fprintf(out_file, "pop rax\n");
    fprintf(out_file, "pop rbx\n");
    fprintf(out_file, "add rbx,rax\n");
    fprintf(out_file, "push rbx\n");
}

void makeCodeSub()
{   
    fprintf(out_file, "pop rax\n");
    fprintf(out_file, "pop rbx\n");
    fprintf(out_file, "sub rbx,rax\n");
    fprintf(out_file, "push rbx\n");

}

void makeCodeMul()
{
    fprintf(out_file, "pop rax\n");
    fprintf(out_file, "pop rbx\n");
    fprintf(out_file, "imul rbx,rax\n");
    fprintf(out_file, "push rbx\n");

}


