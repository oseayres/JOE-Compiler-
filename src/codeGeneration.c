

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <codeGeneration.h>

// Labels para os jumps
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


// Codigo para declaracao de variaveis
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

    else if (type == REAL)
    {
    	if (value == NULL)
            sprintf(dest, "%s: dq 0\n", identifier);

        else
        {
          	double x = atof(value);
            sprintf(dest, "%s: dq %f\n", identifier, x);
        }
    }

    else if (type == STRING)
    {
    	if (value == NULL)
            sprintf(dest, "%s: times %d db 0 \n", identifier, STRING_SIZE);

        else
        {
            sprintf(dest, "%s: db %s, 0\n", identifier, value);
        }
    }
}


// Termino da secao de dados e comeco da secao de codigo
void dumpCodeDeclarationEnd()
{
    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\nmain:\n");
}


// Codigo para leitura (scanf)
void makeCodeRead(char* dest, char *id)
{
    SymTableEntry* ret = findSymTable(&table,id);
    
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized\n", id);
        return;
    }

    if (ret->type == INTEGER)
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_d\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    else if (ret->type == REAL)
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_f\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    else
    {
        sprintf(dest + strlen(dest), "mov rdi,fmt_s\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

   
    sprintf(dest + strlen(dest), "mov rax,0\n");
    sprintf(dest + strlen(dest), "call scanf\n");

}


// Codigo para escrita (printf)
void makeCodeWrite(char* dest, char *id, int ln)
{
    SymTableEntry* ret = findSymTable(&table,id);
    
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized\n", id);
        return;
    }

    if (ret->type == INTEGER)
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_dln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_d\n");
        sprintf(dest + strlen(dest), "mov rsi,[%s]\n", ret->identifier);
    }

    else if (ret->type == REAL)
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_fln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_f\n");
        sprintf(dest + strlen(dest), "mov rsi,[%s]\n", ret->identifier);
    }

    else
    {
        if (ln) sprintf(dest + strlen(dest), "mov rdi,fmt_sln\n");
        else sprintf(dest + strlen(dest), "mov rdi,fmt_s\n");
        sprintf(dest + strlen(dest), "mov rsi,%s\n", ret->identifier);
    }

    sprintf(dest + strlen(dest), "mov rax,0\n");
    sprintf(dest + strlen(dest), "call printf\n");

}



void makeCodeAssignment(char* dest, char* id, char* expr)
{   
    SymTableEntry* ret = findSymTable(&table, id);
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized\n", id);
        return;
    }

 
    if (ret->type == INTEGER)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "pop rbx\n");
        sprintf(dest + strlen(dest), "mov [%s],rbx\n", ret->identifier);
    }

    else
    {
        fprintf(stderr, "Unsuported operation envolving string or float\n");
    }


}





int makeCodeLoad(char* dest, char* id, int ref)
{
    dest[0] = '\0';

    if (ref == 0)
    {
        sprintf(dest + strlen(dest), "mov rbx,%s\n", id);
        sprintf(dest + strlen(dest), "push rbx\n");
        return 1;
    }

    SymTableEntry* ret = findSymTable(&table, id);

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized\n", id);
        return 0;
    }

    if (ret->type == INTEGER || ret->type == REAL)
        sprintf(dest + strlen(dest), "mov rbx,[%s]\n", ret->identifier);
    else
        sprintf(dest + strlen(dest), "mov rbx,%s\n", ret->identifier);
    
    sprintf(dest + strlen(dest), "push rbx\n");
    return 1;
}


void makeCodeAdd(char* dest, char* value)
{
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "add rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}


void makeCodeSub(char* dest, char* value)
{   
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "sub rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");

}

void makeCodeMul(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop rcx\npop rbx\nimul rbx,rcx\npush rbx\n");
}


void makeCodeDiv(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rax\n");
}


void makeCodeMod(char* dest, char* value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rdx\n");
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
