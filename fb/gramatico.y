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
    char str[256];
    int integer;
    double real;
}

%token <str> ID NUM VAR LITERAL_STR INT FLOAT STR WRITE READ WRITELN READLN IF THEN

%type <str> programa declaracoes bloco declaracao declaracao_inteiro declaracao_float declaracao_string 
%type <str> comandos comando comando_atribuicao comando_escrita dec comando_leitura comando_escritaln
%type <str> expressao_numerica termo fator comando_se expressao_booleana operador_relacional
%left '+' '-'
%left '*' '/'

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

bloco : '{' comandos '}'  {
		 $$[0] = 0;

	}
;

comandos : comando comandos
		| 									{ $$[0] = 0; }
		;

comando : comando_atribuicao { $$[0] = 0; }

	| comando_escrita | comando_leitura  | comando_escritaln | comando_se
;

comando_atribuicao: ID '=' expressao_numerica ';' {
		printf("Expressao booleana\n");
		makeCodeAssignment($1, $3);
		
	} |
	ID '=' expressao_booleana ';' {
		printf("Expressao booleana\n");
		makeCodeAssignment($1, $3);
		
	}
;

comando_se: IF '(' expressao_booleana ')' THEN bloco {
		strcpy($$,$1);
		makeCodeJump($3);
	}
;

expressao_booleana:  ID operador_relacional ID {
		
		//strcpy($$,$2);
		makeCodeComp($1,$2,$3);

	}
;

operador_relacional: '<' {
		char p[2];
		p[0] = '<';
		p[1] = '\0';
		strcpy($$,p);
	} 
	| '>'{
		char p[2];
		p[0] = '<';
		p[1]  = '\0';
		strcpy($$,p);
	}
;
expressao_numerica: termo{
		strcpy($$,$1);
	}
	| expressao_numerica '+' expressao_numerica {

		makeCodeAdd();
	}
	| expressao_numerica '-' expressao_numerica{
		makeCodeSub();
	}
	| termo '*' fator {
		makeCodeMul();
	}


;



termo: NUM {

		strcpy($$,$1);
		makeCodeStack($$);
	}
	| ID {
		strcpy($$,$1);
		makeCodeStack($$);	
	}
;

fator: NUM {
		strcpy($$,$1);
		makeCodeStack($$);
	}
	| ID {
		strcpy($$,$1);
	}
	| '(' expressao_numerica ')'{
		// printf("expressao numerica\n");
		strcpy($$,$2);
	}
;

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


comando_escritaln: WRITELN ID ';'  {
		makeCodeWriteln($2);
		$$[0] = 0;
	}
;




%%

void yyerror(char *s)
{
   fprintf(stderr, "Error: %s", s);
   fprintf(stderr, "\n");
}

