%{
	#include <string.h>
	#include <stdio.h>
	#include <y.tab.h>
	void yyerror(char *); 
%}

ws [ \t\n]
letter [A-Za-z]
digit [0-9]
quotes ['\"']
text_str [^'\"']


%%

"//".*\n  {}

"var"	{
	// printf("Lexic: var found\n");
	strcpy(yylval.c.str, yytext);
	return VAR;
}

"int"	{
	// printf("Lexic: int found\n");
	strcpy(yylval.c.str, yytext);
	return INT;
}

"float" {
	strcpy(yylval.c.str, yytext);
	return FLOAT;
}

"string" {
	strcpy(yylval.c.str, yytext);
	return STR;
}

"write" {
	strcpy(yylval.c.str, yytext);
	return WRITE;

}

"do" {
	strcpy(yylval.c.str, yytext);
	return DO;
}


"read" {
	strcpy(yylval.c.str,yytext);
	return READ;
}

"writeln" {
	strcpy(yylval.c.str, yytext);
	return WRITELN;

}

"if" {
	strcpy(yylval.c.str, yytext);
	return IF;
}

"then" {
	strcpy(yylval.c.str, yytext);
	return THEN;
}

"else" {
	strcpy(yylval.c.str, yytext);
	return ELSE;
}

"while" {
	strcpy(yylval.c.str, yytext);
	return WHILE;
}


"<="  {
	yylval.c.str[0] = '\0';
	return LE;
}

">="  {
	yylval.c.str[0] = '\0';
	return GE;
}

"=="  {
	yylval.c.str[0] = '\0';
	return EQ;
}

"!="  {
	yylval.c.str[0] = '\0';
	return NE;
}


{digit}+  {
	strcpy(yylval.c.str, yytext);
	return NUM;
}

{digit}+"."{digit}+ {
	strcpy(yylval.c.str, yytext);
	return NUM;
}

{letter}({letter}|{digit}|_)*	{
	
	strcpy(yylval.c.str, yytext);
	return ID;
}

{quotes}{text_str}*{quotes}  {
	strcpy(yylval.c.str, yytext);
	return LITERAL_STR;
}




[-;:={}+*()<>/%] {
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
