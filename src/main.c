
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


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("No input file\n");
        return 1;
    }

    initSymTable(&table);


    FILE* teclado = stdin;
    stdin = fopen(argv[1], "r");
    
    yyparse();
    
    printSymTable(&table);
    fclose(stdin);



    return 0;
}



