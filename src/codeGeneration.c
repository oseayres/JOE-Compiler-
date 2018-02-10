

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <codeGeneration.h>


void makeLabel(char* out_label)
{
    static int label_count = 0;
    strcpy(out_label, "label");
    
    char s[10];
    sprintf(s, "%d", label_count);
    strcat(out_label, s);

    label_count++;

    printf("Label gerado: {%s}\n", out_label);
}


void dumpDeclarationEndCode()
{
    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\nmain:\n");
}


void makeCodeDeclaration(char* dest, char* identifier, Type type, char* value)
{
    if (type == INTEGER)
    {
        if (value == NULL)
        	sprintf(dest, "%s: dq 0\n", identifier);

        else
        {
        	int x = atoi(value);
            sprintf(dest, "%s: dq %d\n", identifier, x);
        }
    }

    // else if (type == REAL)
    // {
    // 	if (value == NULL)
    //     	fprintf(out_file, "%s: dq 0 \n", identifier);

    //     else
    //     {
    //       	double x = atof(value);
    //     	fprintf(out_file, "%s: dq %f\n", identifier, x);
    //     }
    // }

    // else if (type == STRING)
    // {
    // 	if (value == NULL)
    //     	fprintf(out_file, "%s: db 0 \n", identifier);

    //     else
    //     {
    //       	fprintf(out_file, "%s: db %s, 0\n", identifier, value);
    //     }
    // }
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


void makeCodeComp(char* dest, char* id, char* id2)
{
    SymTableEntry *ret;
    SymTableEntry *ret2;
    ret = findSymTable(&table,id);
    ret2 = findSymTable(&table,id2);

    if(ret == NULL || ret2 == NULL)
    {

    }else
    {
        sprintf(dest, "mov rbx, [%s]\n", ret->identifier);
        sprintf(dest + strlen(dest), "mov rax, [%s]\n", ret2->identifier);
        sprintf(dest + strlen(dest), "cmp rbx, rax\n");


        // fprintf(out_file, "mov rbx,[%s]\n",ret->identifier);
        // fprintf(out_file, "mov rax,[%s]\n",ret2->identifier);
        // fprintf(out_file, "cmp rbx,rax\n");
    }
}

void makeCodeIf(char* dest, char* expr_code, int expr_jump, char* block_code)
{
    char label[16];
    makeLabel(label);

    if (dest == NULL)
    {
        fprintf(out_file, "%s\n", expr_code);
        fprintf(out_file, "%s %s\n", jumps[expr_jump + JUMPS_ARRAY_OFFSET],
            label);

        // Fazendo o cadigo de uma atribuição
        fprintf(out_file, "mov rbx, 1234\n");
        fprintf(out_file, "mov [jesus], rbx\n");


        fprintf(out_file, "%s:\n", label);
    }
}
