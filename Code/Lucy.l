%{
	#include "y.tab.h"
	#include<string.h>
%}
identifier 		[a-zA-Z_][a-zA-Z0-9_]*
digit 			[0-9]
int 			{digit}+
float 			{digit}*"."{digit}{1,7}
double 			{digit}*"."{digit}{8,}
char 			['][^'][']
string 			(["]([^"])*["])|([']([^'])*['])
boolean 		true|false
singleComment	\/\/.*
multiComment	"/*"([^*]|[*][^/])*"*/"

%%
"int" 			{return INT;}
"long" 			{return LONG;}
"float" 		{return FLOAT;}
"double" 		{return DOUBLE;}
"char" 			{return CHAR;}
"string" 		{return STRING;}
"boolean" 		{return BOOLEAN;}
"void" 			{return VOID;}

"if" 			{return IF;}
"elif"			{return ELIF;}
"else" 			{return ELSE;}
"for" 			{return FOR;}
"while" 		{return WHILE;}

"break" 		{return BREAK;}
"continue" 		{return CONTINUE;}
"switch"		{return SWITCH;}
"return"		{return RETURN;}
"default" 		{return DEFAULT;}
"case" 			{return CASE;}
"main"			{return MAIN;}

"++" 			{return INCREMENT;}
"--" 			{return DECREMENT;}
"**" 			{return POWER;}

"<==>"			{return SWAP;}

"=" 			{return ASSIGN;}
"+="			{return PLUS_EQUAL;}
"-=" 			{return MINUS_EQUAL;}
"*="			{return MULTIPLY_EQUAL;}
"/=" 			{return DIVIDE_EQUAL;}
"%=" 			{return MODULO_EQUAL;}

"+"				{return PLUS;}
"-"				{return MINUS;}
"*"				{return MULTIPLY;}
"/"				{return DIVIDE;}
"%"				{return MODULO;}
"!"				{return EXCLAIMATION;}

"&&" 			{return AND;}
"||" 			{return OR;}

"&"				{return BIT_AND;}
"|"				{return BIT_OR;}
"^"				{return BIT_XOR;}
"~" 			{return BIT_NOT;}
"<<" 			{return L_SHIFT;}
">>" 			{return R_SHIFT;}

"==" 			{return EQUAL;}
"!=" 			{return NOT_EQUAL;}
"<=" 			{return LESS_EQUAL;}
">=" 			{return GREAT_EQUAL;}
"<"				{return LESS_THEN;}
">"				{return GREAT_THEN;}

"("				{return ROUNDOPEN;}
")"				{return ROUNDCLOSE;}
"{"				{return CURLYOPEN;}
"}"				{return CURLYCLOSE;}
"["				{return SQUAREOPEN;}
"]"				{return SQUARECLOSE;}

":" 			{return COLON;}
";" 			{return SEMICOLON;}
"?" 			{return QUESTIONMARK;}
"." 			{return DOT;}
"," 			{return COMMA;}
"\\" 			{return BSLASH;}
\n				{return NEW_LINE;}

"print" 		{return PRINT;}

{int}			{yylval.ival = atoi(yytext);return INT_VAL;}
{float}			{yylval.fval = (float)atof(yytext);return FLOAT_VAL;}
{double}		{yylval.dval = atof(yytext);return DOUBLE_VAL;}
{char}			{yylval.cval = yytext[1];return CHAR_VAL;}
{string}		{char* str = strdup(yytext);int n = strlen(yytext); str[n-1] = '\0'; yylval.strval = str+1;return STRING_VAL;}
{boolean} 		{yylval.bval = strcmp(yytext,"true")?0:1;return BOOLEAN_VAL;}
{identifier}	{yylval.id = strdup(yytext);return ID;}

{singleComment}			/* ignore single line comments */
{multiComment}			/* ignore multiComments */

\r                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;


%%
int yywrap(void)
{
return 0;
}

int yyerror(char *errormsg)
{
fprintf(stderr,"%s\n", ""/*errormsg*/);
exit(1);
}