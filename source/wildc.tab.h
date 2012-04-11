/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INT_CONST = 259,
     FLOAT_CONST = 260,
     STRING_CONST = 261,
     INT = 262,
     FLOAT = 263,
     STRING = 264,
     BOOL = 265,
     VOID = 266,
     ASSIGN = 267,
     IF = 268,
     ELSE = 269,
     WHILE = 270,
     INPUT = 271,
     PRINT = 272,
     TRUE = 273,
     FALSE = 274,
     LENGTH = 275,
     CHAR = 276,
     SUBSTR = 277,
     RETURN = 278,
     OR = 279,
     AND = 280,
     NOT_EQUALS = 281,
     EQUALS = 282,
     GTE = 283,
     LTE = 284
   };
#endif
/* Tokens.  */
#define ID 258
#define INT_CONST 259
#define FLOAT_CONST 260
#define STRING_CONST 261
#define INT 262
#define FLOAT 263
#define STRING 264
#define BOOL 265
#define VOID 266
#define ASSIGN 267
#define IF 268
#define ELSE 269
#define WHILE 270
#define INPUT 271
#define PRINT 272
#define TRUE 273
#define FALSE 274
#define LENGTH 275
#define CHAR 276
#define SUBSTR 277
#define RETURN 278
#define OR 279
#define AND 280
#define NOT_EQUALS 281
#define EQUALS 282
#define GTE 283
#define LTE 284




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 35 "wildc.y"
typedef union YYSTYPE {
	DType				dtype;
	int					ival;
	char				*str;
	char				pBuffer[500];
	struct dataDef		datDefType;
	struct dataRef		datRefType;
	struct labelDef		labDefType;
	
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 107 "wildc.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



