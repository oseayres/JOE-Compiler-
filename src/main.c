
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


FILE* out_file = NULL;


SymTable table;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("JOE: nenhum arquivo de entrada\n");
        return 1;
    }

    if (argc >= 4 && strcmp(argv[2], "-o") == 0)
        out_file = fopen(argv[3], "w");
    else
    {
        int i, n = strlen(argv[1]);
        char s[n + 10];
        for (i = 0; i < (n + 10); i++)
            s[i] = '\0';
        for (i = n - 1; i >= 0 && argv[1][i] != '.'; i--){}

        if (i == -1)
        {
            fprintf(stderr, "JOE: Extensao do arquivo de entrada incorreta\n");
            return 0;
        }

        strncpy(s, argv[1], i);
        printf("{%s}\n", s);
        strcat(s, ".asm");
        printf("{%s}\n", s);
        out_file = fopen(s, "w");
    }


    fprintf(out_file, "extern printf\n");
    fprintf(out_file, "extern scanf\n");
    fprintf(out_file, "section .data\n");
    fprintf(out_file, "fmt_d: db \"%%d\", 0\n");
    fprintf(out_file, "fmt_dln: db \"%%d\", 10, 0\n");
    fprintf(out_file, "fmt_f: db \"%%f\", 0\n");
    fprintf(out_file, "fmt_fln: db \"%%f\", 10, 0\n");
    fprintf(out_file, "fmt_s: db \"%%s\", 0\n");
    fprintf(out_file, "fmt_sln: db \"%%s\", 10, 0\n");
    
    
    
    initSymTable(&table);


    FILE* teclado = stdin;
    stdin = fopen(argv[1], "r");
    
    yyparse();
      

    fprintf(out_file, "mov rax,0\n");  
    fprintf(out_file, "ret\n");


    // printSymTable(&table);

    fclose(out_file);
    fclose(stdin);

    return 0;
}



