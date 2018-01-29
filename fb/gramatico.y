%{
    #include <string.h>
    #include <stdio.h>
	#include <symbolTable.h>

    void yyerror(char*);
    int yylex();

    SymTable table;

%}

%union {
    char str[30];
    int integer;
    double real;
}

%token <str> ID NUM VAR INT FLOAT

%type <str> programa declaracoes bloco declaracao declaracao_inteiro declaracao_float 
%type <str> comandos comando comando_atribuicao

%%


programa: declaracoes bloco 
          ;

declaracoes: declaracao declaracoes
		| { $$[0] = 0;}
		;

declaracao: declaracao_inteiro | declaracao_float


declaracao_inteiro: VAR ID ':' INT '=' NUM ';'  {
	
		addSymTable(&table, $2, INTEGER, $6);
	}

	| VAR ID ':' INT ';'  {
		
		addSymTable(&table, $2, INTEGER, NULL);
	}
;

declaracao_float: VAR ID ':' FLOAT '=' NUM ';'  {

		addSymTable(&table, $2, REAL, $6);
	}

	| VAR ID ':' FLOAT ';'  {

		addSymTable(&table, $2, REAL, NULL);
	}
;

bloco : comandos

comandos : comando comandos 
		| 									{ $$[0] = 0; }
		; 

comando : comando_atribuicao

comando_atribuicao: ID '=' NUM ';'{
		// strcpy($$,$2);
		printf("Atribuicao");
	}

%%

void yyerror(char *s)
{
   fprintf(stderr, "Error: ");
   fprintf(stderr, s);
   fprintf(stderr, "\n");
}

