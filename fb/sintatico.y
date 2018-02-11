%{
    #include <string.h>
    #include <stdio.h>
	#include <symbolTable.h>
	#include <codeGeneration.h>

    void yyerror(char*);
    int yylex();

    extern SymTable table;

    char s_decs[256];

%}

%union {
    int integer;
	struct code_t
	{
		char str[1024];
		int op;
	} c;
    // char str[256];
    double real;
}




%type <c> programa declaracoes declaracao bloco
%type <c> declaracao_inteiro declaracao_float declaracao_string
%type <c> comandos comando comando_escrita comando_leitura

%token <c> VAR ID NUM LITERAL_STR INT FLOAT STR WRITE READ WRITELN IF THEN

%left '+' '-'
%left '*' '/'

%%


programa: declaracoes bloco  {
		
		fprintf(out_file, "%s", $1.str);
		dumpCodeDeclarationEnd();
		fprintf(out_file, "%s", $2.str);
	}
;


declaracoes: declaracao declaracoes  {

		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}

	| %empty { $$.str[0] = '\0'; }
;


declaracao: declaracao_inteiro { strcpy($$.str, $1.str); }
	| declaracao_float { strcpy($$.str, $1.str); }
	| declaracao_string { strcpy($$.str, $1.str); }
;


declaracao_inteiro: VAR ID ':' INT '=' NUM ';'  {
	
		addSymTable(&table, $2.str, INTEGER, $6.str);
		makeCodeDeclaration($$.str, $2.str, INTEGER, $6.str);
	}

	| VAR ID ':' INT ';'  {
		
		addSymTable(&table, $2.str, INTEGER, NULL);
		makeCodeDeclaration($$.str, $2.str, INTEGER, NULL);
	}
;


declaracao_float: VAR ID ':' FLOAT '=' NUM ';'  {

		addSymTable(&table, $2.str, REAL, $6.str);
		makeCodeDeclaration($$.str, $2.str, REAL, $6.str);
	}

	| VAR ID ':' FLOAT ';'  {

		addSymTable(&table, $2.str, REAL, NULL);
		makeCodeDeclaration($$.str, $2.str, REAL, NULL);
	}
;


declaracao_string: VAR ID ':' STR'=' LITERAL_STR ';'  {

		addSymTable(&table, $2.str, STRING, $6.str);
		makeCodeDeclaration($$.str, $2.str, STRING, $6.str);
	}

	| VAR ID ':' STR ';'  {

		addSymTable(&table, $2.str, STRING, NULL);
		makeCodeDeclaration($$.str, $2.str, STRING, NULL);
	}
;


bloco : '{' comandos '}'  {

		strcpy($$.str, $2.str);
	}
;


comandos : comando comandos  {

		sprintf($$.str + strlen($$.str), "%s", $2.str);
	}

	| %empty { $$.str[0] = '\0'; }
;


comando: comando_escrita      { strcpy($$.str, $1.str); }
	| comando_leitura         { strcpy($$.str, $1.str); }
;


comando_leitura: READ ID ';'  {
		
		makeCodeRead($$.str, $2.str);
	}
;


comando_escrita: WRITE ID ';'  {

		makeCodeWrite($$.str, $2.str, 0);
	}
	| WRITELN ID ';'  {

		makeCodeWrite($$.str, $2.str, 1);
	}
;



/*
comando_atribuicao: ID '=' expressao_numerica ';' {
		// printf("Expressao booleana\n");
		makeCodeAssignment($1, $3);
		
	}
	// | ID '=' expressao_booleana ';' {
	// 	// printf("Expressao booleana\n");
	// 	makeCodeAssignment($1, $3);
		
	// }
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


*/


%%

void yyerror(char *s)
{
   fprintf(stderr, "Error: %s", s);
   fprintf(stderr, "\n");
}

