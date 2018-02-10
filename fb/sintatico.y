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
    int integer;
	struct code_t
	{
		char str[256];
		int op;
	} c;
    // char str[256];
    double real;
}

%token <c.str> ID NUM VAR LITERAL_STR INT FLOAT STR WRITE READ WRITELN IF THEN

%type <c.str> programa declaracoes bloco declaracao declaracao_inteiro declaracao_float declaracao_string 
%type <c.str> comandos comando comando_atribuicao comando_escrita dec comando_leitura comando_escritaln
%type <c.str> expressao_numerica termo fator comando_se
%type <c> expressao_booleana operador_relacional

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
		// printf("Expressao booleana\n");
		makeCodeAssignment($1, $3);
		
	}
	// | ID '=' expressao_booleana ';' {
	// 	// printf("Expressao booleana\n");
	// 	makeCodeAssignment($1, $3);
		
	// }
;

comando_se: IF '(' expressao_booleana ')' THEN  {
		strcpy($$,$1);
		makeCodeIf(NULL, $3.str, $3.op, NULL);
		printf("\n[\n%s\n]\n\n", $3.str);
	}
;




expressao_booleana: ID operador_relacional ID {
		
		$$.op = $2.op;
		makeCodeComp($$.str, $1, $3);

	}
;

operador_relacional: '<'  {
		
		$$.str[0] = '\0';
		$$.op = -4;
	}

	| '>'  {
		$$.str[0] = '\0';
		$$.op = -3;
	}
;
expressao_numerica: termo{
		strcpy($$,$1);
	}
	| expressao_numerica '+' expressao_numerica {

		makeCodeAdd();
	}
	| expressao_numerica '-' expressao_numerica {
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

