
/**
	
	UNIVERSIDADE FEDERAL DE MATO GROSSO
    CAMPUS UNIVERSITÁRIO DO ARAGUAIA
    INSTITUTO DE CIÊNCIAS EXATAS E DA TERRA
    CURSO DE BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO
    
    Disciplina:
    Docente:
    Discentes:
    
    Trabalho

**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <y.tab.h>

extern SymTable table;
FILE* out_file = NULL;


int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        printf("No input file\n");
        return 1;
    }

    if (strcmp(argv[2], "-o") != 0)
        return 1;

    out_file = fopen(argv[3], "w");
    fprintf(out_file, "extern printf\n");
    fprintf(out_file, "section .data\n");
    
    
    initSymTable(&table);


    FILE* teclado = stdin;
    stdin = fopen(argv[1], "r");
    
    yyparse();
    
    printSymTable(&table);

    fclose(out_file);
    fclose(stdin);

    return 0;
}



