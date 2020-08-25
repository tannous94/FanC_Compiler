%{
	#include "hw3_output.hpp"
	#include "parser.hpp"
	#include "parser.tab.hpp"
	using namespace output;
%}

%option yylineno
%option noyywrap

lf              \x0A
cr              \x0D
crlf            ({cr}{lf})
newLine         ({crlf}|{cr}|{lf})
whitespace		([ \t\r\n])
relation		("<"|">"|"<="|">=")
equality  		("=="|"!=")
binopmul		[*/]
binopadd		[+-]
id				([a-zA-Z][a-zA-Z0-9]*)
num				(0|([1-9][0-9]*))
comment			("//")[^\r\n]*[\r|\n|\r\n]?
string			(\"([^\n\r\"\\]|\\[rnt"\\])+\")
b				("b")
spaces			({newLine}|{whitespace})
byte_type		({num}{spaces}*{b})

%%

"void"			{ return VOID; }
"int"			{ return INT; }
"byte"			{ return BYTE; }
{byte_type}		{
				int len = 0;
				char *str = yytext;
				while(*str >= '0' && *str <= '9') {
					len++;
					str++;
				}
				char tmp[len+1];
				for(int i = 0; i < len; i++) {
					tmp[i] = yytext[i];
				}
				tmp[len] = '\0';
				yylval.token_data = new TokenData(tmp); 
				return NUM_B;
				}

"bool"			{ return BOOL; }
"enum"			{ return ENUM; }
"and"			{ return AND; }
"or"			{ return OR; }
"not"			{ return NOT; }
"true"			{ return TRUE; }
"false"			{ return FALSE; }
"return"		{ return RETURN; }
"if"			{ return IF; }
"else"			{ return ELSE; }
"while"			{ return WHILE; }
"break"			{ return BREAK; }
"continue"		{ return CONTINUE; }
";"				{ return SC; }
","				{ return COMMA; }
"("				{ return LPAREN; }
")"				{ return RPAREN; }
"{"				{ return LBRACE; }
"}"				{ return RBRACE; }
"="				{ return ASSIGN; }
{binopmul}		{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return BINOPMUL;
				}
{binopadd}		{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return BINOPADD; 
				}
{relation}		{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return RELATION; 
				}
{equality}		{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return EQUALITY; 
				}
{id}			{ 
					yylval.id_data = new IdData(strdup(yytext)); 
					return ID; 
				}
{num}			{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return NUM; 
				}
{string}		{ 
					yylval.token_data = new TokenData(strdup(yytext));
					return STRING; 
				}
{comment}		{ }
{whitespace}	{ }
<<EOF>>			{ return EF; }
.				{ 
					errorLex(yylineno);
					exit(0);
				}

%%
