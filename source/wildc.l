%{
#pragma warning( disable:4267; disable:4244; disable:4013 )

/* name: wildc.l
   This code implements a scanner for the wildc language
   
   build: flex -L wildc.l
   //!
	   don't forget to set the __STDC__ under *project*>properties>c/c++>Preprossor>Preprocessor definitions (append __STDC__)
	   REMEMBER! A piece at a time.
	   In production rules, each production executes before the current production's rule runs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "wildc.h"
#include "wildc.tab.h"

static int Line=1, Position=1;

%}

%option noyywrap

WhiteSpace		[ \t]
Variable		[A-Za-z][A-Za-z0-9_]*
Integer			[0-9]+
Floating		([0-9]*\.[0-9]+)
String			\"[^\"\n]*\"

%%

{Integer}	{	/* return the double floating number */
				Position += strlen( yytext );
				yylval.str = _strdup( yytext );
				return INT_CONST;
			}
	
{Floating}	{	/* return the double floating number */
				Position += strlen( yytext );
				yylval.str = _strdup( yytext );
				return FLOAT_CONST;
			}
	
{WhiteSpace}	Position++;	/* ignore whitespace */

{Variable}	{	/* return symbol pointer */
				Position += strlen( yytext );
				if ( !strcmp( yytext, "int" ))
					return INT;
				if ( !strcmp( yytext, "float" ))
					return FLOAT;
				if ( !strcmp( yytext, "string" ))
					return STRING;
				if ( !strcmp( yytext, "bool" ))
					return BOOL;
				if ( !strcmp( yytext, "void" ))
					return VOID;
				if ( !strcmp( yytext, "if" ))
					return IF;
				if ( !strcmp( yytext, "else" ))
					return ELSE;
				if ( !strcmp( yytext, "while" ))
					return WHILE;
				if ( !strcmp( yytext, "input" ))
					return INPUT;
				if ( !strcmp( yytext, "print" ))
					return PRINT;
				if ( !strcmp( yytext, "true" ))
					return TRUE;
				if ( !strcmp( yytext, "false" ))
					return FALSE;
				if ( !strcmp( yytext, "length" ))
					return LENGTH;
				if ( !strcmp( yytext, "char" ))
					return CHAR;
				if ( !strcmp( yytext, "substr" ))
					return SUBSTR;
				if ( !strcmp( yytext, "return" ))
					return RETURN;
				yylval.str = _strdup( yytext );
				return ID;
				}
	
{String}	{	/* return a string */
				Position += strlen( yytext );
				yylval.str = _strdup( yytext+1 );
				yylval.str[ strlen(yylval.str)-1 ] = '\0';
				return STRING_CONST;
			}

"||"		{ Position += 2; return OR; }
"&&"		{ Position += 2; return AND; }
"=="		{ Position += 2; return EQUALS; }
"!="		{ Position += 2; return NOT_EQUALS; }
"<="		{ Position += 2; return LTE; }
">="		{ Position += 2; return GTE; }
":="		{ Position += 2; return ASSIGN; }
	
\n			{
				Line++;
				Position=1;
			}

.			{
				Position++;
				return yytext[0];
			}

%%

void yyerror(char *string,...)
{

	va_list ap;

	va_start(ap, string);

	fprintf(stdout, ERROR_MESSAGE, Line, Position);
	vfprintf(stdout, string, ap);
	fprintf(stdout, "\n");
	va_end(ap);
	printf("\n\nPress enter to exit");
	getchar();
	exit(1);

}
