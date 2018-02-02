%{
    #include <string.h>
    #include <stdio.h>
	#include <symbolTable.h>
	#include <codeGeneration.h>

    void yyerror(char*);
    int yylex();

    extern SymTable table;

%}

%union {
    char str[32];
    int integer;
    double real;
}

%token <str> ID NUM VAR LITERAL_STR INT FLOAT STR WRITE READ

%type <str> programa declaracoes bloco declaracao declaracao_inteiro declaracao_float declaracao_string 
%type <str> comandos comando comando_atribuicao comando_escrita dec comando_leitura

%%


programa: dec bloco 
          ;

dec: declaracoes {
		makeCodeEndDeclaration();
	 	$$[0] = 0; 
	}
;
declaracoes: declaracao declaracoes
		| { $$[0] = 0;}
		;

declaracao: declaracao_inteiro | declaracao_float | declaracao_string


declaracao_inteiro: VAR ID ':' INT '=' NUM ';'  {
	
		addSymTable(&table, $2, INTEGER, $6);
		makeCodeDeclaration($2, INTEGER, $6);
	}

	| VAR ID ':' INT ';'  {
		
		addSymTable(&table, $2, INTEGER, NULL);
		makeCodeDeclaration($2, INTEGER, NULL);
	}
;

declaracao_float: VAR ID ':' FLOAT '=' NUM ';'  {

		addSymTable(&table, $2, REAL, $6);
		makeCodeDeclaration($2, REAL, $6);
	}

	| VAR ID ':' FLOAT ';'  {

		addSymTable(&table, $2, REAL, NULL);
		makeCodeDeclaration($2, REAL, NULL);
	}
;

declaracao_string: VAR ID ':' STR'=' LITERAL_STR ';'  {

		addSymTable(&table, $2, STRING, $6);
		makeCodeDeclaration($2, STRING, $6);
	}

	| VAR ID ':' STR ';'  {

		addSymTable(&table, $2, STRING, "");
		makeCodeDeclaration($2, STRING, "");
	}
;

bloco : '{' comandos '}'  { $$[0] = 0; }
;

comandos : comando comandos
		| 									{ $$[0] = 0; }
		;

comando : comando_atribuicao { $$[0] = 0; }

	| comando_escrita | comando_leitura
;

comando_atribuicao: ID '=' NUM ';'{
		// strcpy($$,$2);
		printf("Atribuicao");
	}

comando_escrita: WRITE ID ';'  {
		makeCodeWrite($2);
		$$[0] = 0;
	}
;

comando_leitura: READ ID ';'{
		makeCodeRead($2);
		$$[0] = 0;
	}
;



%%

void yyerror(char *s)
{
   fprintf(stderr, "Error: %s", s);
   fprintf(stderr, "\n");
}

