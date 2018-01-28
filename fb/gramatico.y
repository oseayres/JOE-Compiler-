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
													printf("to aqui\n");
													SymTableEntry entry;
													strcpy(entry.identifier, $2);
													addSymTable(&table, &entry);
													printSymTable(&table);
                                	            // strcpy($$, $2);
                            	                // printf("Nome da variavel: {%s}\n", $2);
                        	                    // printf("valor: {%d}\n", $6);
                    	                    }
                  | VAR ID ':' INT ';'	{
                  	// strcpy($$, $2);
                   //  printf("Nome da variavel: {%s}\n", $2);
                  }
                  ;

declaracao_float: VAR ID ':' FLOAT '=' NUM ';'{
							// strcpy($$,$2);
							// printf("Nome da variavel: {%s}\n",$2);
							// printf("valor: {%f}\n",$6);
				}
				| VAR ID ':' FLOAT ';'{
					// strcpy($$,$2);
					// printf("Nome da variavel: {%s}\n",$2);
				}

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

