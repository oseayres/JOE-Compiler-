%{
	#include <string.h>
	#include <stdio.h>
	#include <y.tab.h>
	void yyerror(char *); 
%}

ws [ \t\n]
letter [A-Za-z]
digit [0-9]

%%

"var"	{
	// printf("Lexic: var found\n");
	strcpy(yylval.str, yytext);
	return VAR;
}

"int"	{
	// printf("Lexic: int found\n");
	strcpy(yylval.str, yytext);
	return INT;
}

"float" {
	strcpy(yylval.str, yytext);
	return FLOAT;
}


{digit}+  {
	strcpy(yylval.str, yytext);
	return NUM;
}

{digit}+"."{digit}+ {
	strcpy(yylval.str, yytext);
	return NUM;
}

{letter}({letter}|{digit}|_)*	{
	
	strcpy(yylval.str, yytext);
	return ID;
}

[;:=] {
	// printf("Lexic: %c found\n", *yytext);
	// strcpy(yylval.str, yytext);
	return *yytext;
}


{ws}           { }

. { yyerror("invalid character"); }

%%

int yywrap (void)
{
 	return 1;
}