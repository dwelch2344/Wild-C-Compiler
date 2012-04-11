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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "wildc.y"

#pragma warning( disable:4013; disable:4996; disable:4716 )

/* name: wildc.y
   This code implements a parser and translator for the wildc language
   
   build: bison -l -d wildc.y
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wildc.h"

struct symbolDef symtab[NSYMS];
DType tmpFnCallParms[NESTCALLDEPTH][NTMPCALLPARMS];
char currentContext[MAX_IDENT_LEN+1];
char genedLabel[MAX_IDENT_LEN+1];
int fnParmIdx = 0;
int tmpFnCallParmIdx[NESTCALLDEPTH] = {0};
int tmpFnCallDepth = -1;
int labelIndex = 0;


int _isDebug = 0; // is a debug run
char myBuffer[100000];
char paramBuffer[100000];
int localIndex = 0;
int tabIndex = 0;
int globals = 0;
char className[50];


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 196 of yacc.c.  */
#line 187 "wildc.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 199 "wildc.tab.c"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   390

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  37
/* YYNRULES -- Number of rules. */
#define YYNRULES  85
/* YYNRULES -- Number of states. */
#define YYNSTATES  173

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,    34,    33,    43,    32,    44,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      28,     2,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     9,    10,    11,    12,    14,    15,    17,
      20,    24,    27,    29,    31,    33,    35,    37,    41,    43,
      46,    47,    48,    49,    64,    66,    68,    70,    72,    74,
      78,    81,    83,    84,    86,    89,    91,    94,    96,   101,
     106,   107,   113,   118,   119,   120,   132,   137,   138,   148,
     153,   157,   161,   165,   175,   179,   183,   187,   191,   195,
     199,   203,   207,   211,   215,   219,   223,   227,   229,   231,
     233,   235,   237,   239,   243,   250,   255,   264,   270,   271,
     272,   275,   276,   278,   282,   284
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    47,    50,    48,    56,    49,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    52,    -1,    51,    52,    -1,
      53,     3,    36,    -1,    54,    55,    -1,    54,    -1,     7,
      -1,     8,    -1,     9,    -1,    10,    -1,    37,     4,    38,
      -1,    57,    -1,    56,    57,    -1,    -1,    -1,    -1,    28,
      61,    29,     3,    58,    39,    62,    40,    59,    41,    65,
      60,    67,    42,    -1,    11,    -1,    54,    -1,    11,    -1,
      63,    -1,    64,    -1,    63,    43,    64,    -1,    54,     3,
      -1,    66,    -1,    -1,    52,    -1,    66,    52,    -1,    72,
      -1,    67,    72,    -1,     3,    -1,     3,    37,    76,    38,
      -1,    13,    39,    76,    40,    -1,    -1,    15,    70,    39,
      76,    40,    -1,    68,    12,    76,    36,    -1,    -1,    -1,
      68,    39,    76,    73,    43,    76,    74,    40,    12,    76,
      36,    -1,    69,    41,    67,    42,    -1,    -1,    69,    41,
      67,    42,    75,    14,    41,    67,    42,    -1,    71,    41,
      67,    42,    -1,    16,    68,    36,    -1,    17,    81,    36,
      -1,    23,    76,    36,    -1,    39,    11,    40,     3,    77,
      39,    78,    40,    36,    -1,    76,    33,    76,    -1,    76,
      32,    76,    -1,    76,    34,    76,    -1,    76,    35,    76,
      -1,    76,    25,    76,    -1,    76,    24,    76,    -1,    76,
      27,    76,    -1,    76,    26,    76,    -1,    76,    28,    76,
      -1,    76,    29,    76,    -1,    76,    31,    76,    -1,    76,
      30,    76,    -1,    39,    76,    40,    -1,     4,    -1,     5,
      -1,     6,    -1,    18,    -1,    19,    -1,    68,    -1,    68,
      44,    20,    -1,    68,    44,    21,    39,    76,    40,    -1,
      21,    39,    76,    40,    -1,    68,    44,    22,    39,    76,
      43,    76,    40,    -1,     3,    77,    39,    78,    40,    -1,
      -1,    -1,    79,    80,    -1,    -1,    76,    -1,    80,    43,
      76,    -1,    76,    -1,    81,    43,    76,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    86,    86,    90,   103,   132,   138,   142,   147,   149,
     154,   177,   183,   192,   194,   196,   198,   203,   212,   214,
     220,   231,   248,   219,   294,   298,   305,   309,   320,   324,
     333,   344,   405,   465,   470,   480,   484,   491,   513,   554,
     579,   591,   610,   659,   670,   658,   683,   690,   689,   702,
     710,   783,   787,   809,   884,   901,   912,   923,   934,   970,
    1006,  1027,  1050,  1065,  1079,  1099,  1119,  1123,  1128,  1134,
    1141,  1147,  1153,  1176,  1189,  1215,  1226,  1245,  1282,  1288,
    1288,  1292,  1298,  1302,  1309,  1315
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INT_CONST", "FLOAT_CONST",
  "STRING_CONST", "INT", "FLOAT", "STRING", "BOOL", "VOID", "ASSIGN", "IF",
  "ELSE", "WHILE", "INPUT", "PRINT", "TRUE", "FALSE", "LENGTH", "CHAR",
  "SUBSTR", "RETURN", "OR", "AND", "NOT_EQUALS", "EQUALS", "'<'", "'>'",
  "GTE", "LTE", "'-'", "'+'", "'*'", "'/'", "';'", "'['", "']'", "'('",
  "')'", "'{'", "'}'", "','", "'.'", "$accept", "wildc_start", "init_sys",
  "mid_process", "finish_up", "global_defs", "data_definitions",
  "data_def", "data_type_def", "data_type", "array_declaration",
  "function_defs", "function_def", "@1", "@2", "@3", "return_type",
  "function_parameters", "fn_parameter_list", "function_parameter",
  "local_defs", "local_definitions", "function_statements", "data_ref",
  "if_test", "gen_while_labels", "while_test", "function_statement", "@4",
  "@5", "@6", "expression", "inc_function_call_depth",
  "function_call_parameters", "@7", "function_call_list", "print_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    60,    62,
     283,   284,    45,    43,    42,    47,    59,    91,    93,    40,
      41,   123,   125,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    46,    47,    48,    49,    50,    50,    51,    51,
      52,    53,    53,    54,    54,    54,    54,    55,    56,    56,
      58,    59,    60,    57,    61,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      70,    71,    72,    73,    74,    72,    72,    75,    72,    72,
      72,    72,    72,    72,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    79,
      78,    78,    80,    80,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     5,     0,     0,     0,     1,     0,     1,     2,
       3,     2,     1,     1,     1,     1,     1,     3,     1,     2,
       0,     0,     0,    14,     1,     1,     1,     1,     1,     3,
       2,     1,     0,     1,     2,     1,     2,     1,     4,     4,
       0,     5,     4,     0,     0,    11,     4,     0,     9,     4,
       3,     3,     3,     9,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     3,     6,     4,     8,     5,     0,     0,
       2,     0,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     7,     1,    13,    14,    15,    16,     4,     6,
       8,     0,    12,     0,     9,     0,     0,    11,     0,     5,
      18,    10,     0,    24,    25,     0,     2,    19,    17,     0,
      20,     0,     0,    26,     0,     0,    27,    28,    30,    21,
       0,     0,    29,    32,    33,    22,    31,     0,    34,    37,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,    37,    67,    68,    69,    70,
      71,     0,     0,    72,    84,     0,     0,     0,    23,    36,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,    52,     0,     0,    43,
       0,     0,    38,    39,     0,    79,     0,    66,    73,     0,
       0,    59,    58,    61,    60,    62,    63,    65,    64,    55,
      54,    56,    57,    85,    78,    42,     0,    46,    49,    41,
       0,     0,    75,     0,     0,     0,     0,     0,    77,    82,
      80,     0,     0,    79,    44,     0,     0,    74,     0,     0,
       0,     0,    83,     0,     0,     0,     0,    76,    53,     0,
      48,     0,    45
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,    13,    26,     8,     9,    10,    11,    12,
      17,    19,    20,    31,    41,    47,    25,    35,    36,    37,
      45,    46,    56,    73,    58,    63,    59,    60,   136,   160,
     147,    74,    88,   140,   141,   150,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const short int yypact[] =
{
     -82,    15,    11,   -82,   -82,   -82,   -82,   -82,   -82,    11,
     -82,    13,   -14,     6,   -82,     3,    38,   -82,    18,     6,
     -82,   -82,     5,   -82,   -82,    27,   -82,   -82,   -82,    56,
     -82,    21,    66,   -82,    76,    29,    47,   -82,   -82,   -82,
      11,    50,   -82,    11,   -82,   -82,    11,   157,   -82,    63,
      73,   -82,    89,   132,   132,   104,    55,    -8,    75,    77,
     -82,   132,   132,    83,    87,    74,   -82,   -82,   -82,   -82,
     -82,    85,   132,    82,   334,   -26,   295,    91,   -82,   -82,
     132,   132,   157,   157,   280,   178,   132,   -82,    88,   132,
     195,    45,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   -82,   132,   -82,   141,   308,   334,
      86,   117,   -82,   -82,   212,   105,   229,   -82,   -82,   107,
     108,   345,   355,    53,    53,    72,    72,    72,    72,   -23,
     -23,   -82,   -82,   334,   -82,   -82,   109,   134,   -82,   -82,
     114,   132,   -82,   132,   132,   116,   132,   143,   -82,   334,
     115,   246,   158,   105,   334,   120,   132,   -82,   132,   122,
     123,   157,   334,   263,   128,   154,   126,   -82,   -82,   132,
     -82,   321,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -82,   -82,   -82,   -82,   -82,   -82,   -82,    -6,   -82,   -10,
     -82,   -82,   148,   -82,   -82,   -82,   -82,   -82,   -82,   129,
     -82,   -82,   -81,   -47,   -82,   -82,   -82,   -49,   -82,   -82,
     -82,   -48,    41,    23,   -82,   -82,   -82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -82
static const short int yytable[] =
{
      57,   110,   111,    14,    80,    64,    76,    79,    24,    57,
     104,   102,   103,    84,    85,     3,    15,   105,     4,     5,
       6,     7,    34,    16,    90,     4,     5,     6,     7,    23,
      34,    81,   108,   109,    18,    57,    57,    44,   114,    21,
      48,   116,    22,    28,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,    29,   133,    49,    30,
      32,    79,    79,    57,    57,   118,   119,   120,    50,    39,
      51,    52,    53,     4,     5,     6,     7,    33,    54,    38,
     166,    96,    97,    98,    99,   100,   101,   102,   103,    49,
      40,    43,    49,   149,    55,   151,   152,    78,   154,    50,
      61,    51,    52,    53,   100,   101,   102,   103,   162,    54,
     163,    61,    62,   -78,    57,    77,    82,    79,    83,    57,
      49,   171,    86,    87,    89,    55,    91,   115,   137,    49,
      50,   107,    51,    52,    53,    65,    66,    67,    68,    50,
      54,    51,    52,    53,   134,   -81,   143,   144,   -47,    54,
      69,    70,   146,    71,   148,   153,    55,   155,   156,   138,
      49,   161,   164,   165,   168,    55,   169,    27,   170,    42,
      50,    72,    51,    52,    53,   145,   159,     0,     0,     0,
      54,     0,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,    55,     0,     0,     0,
       0,   158,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   113,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,   117,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,   139,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,   142,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,   157,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,   167,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,   112,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   106,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   135,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   172,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103
};

static const short int yycheck[] =
{
      47,    82,    83,     9,    12,    52,    54,    56,    18,    56,
      36,    34,    35,    61,    62,     0,     3,    43,     7,     8,
       9,    10,    32,    37,    72,     7,     8,     9,    10,    11,
      40,    39,    80,    81,    28,    82,    83,    43,    86,    36,
      46,    89,     4,    38,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    29,   105,     3,     3,
      39,   110,   111,   110,   111,    20,    21,    22,    13,    40,
      15,    16,    17,     7,     8,     9,    10,    11,    23,     3,
     161,    28,    29,    30,    31,    32,    33,    34,    35,     3,
      43,    41,     3,   141,    39,   143,   144,    42,   146,    13,
      37,    15,    16,    17,    32,    33,    34,    35,   156,    23,
     158,    37,    39,    39,   161,    11,    41,   166,    41,   166,
       3,   169,    39,    36,    39,    39,    44,    39,    42,     3,
      13,    40,    15,    16,    17,     3,     4,     5,     6,    13,
      23,    15,    16,    17,     3,    40,    39,    39,    14,    23,
      18,    19,    43,    21,    40,    39,    39,    14,    43,    42,
       3,    41,    40,    40,    36,    39,    12,    19,    42,    40,
      13,    39,    15,    16,    17,   134,   153,    -1,    -1,    -1,
      23,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    43,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    46,    47,     0,     7,     8,     9,    10,    50,    51,
      52,    53,    54,    48,    52,     3,    37,    55,    28,    56,
      57,    36,     4,    11,    54,    61,    49,    57,    38,    29,
       3,    58,    39,    11,    54,    62,    63,    64,     3,    40,
      43,    59,    64,    41,    52,    65,    66,    60,    52,     3,
      13,    15,    16,    17,    23,    39,    67,    68,    69,    71,
      72,    37,    39,    70,    68,     3,     4,     5,     6,    18,
      19,    21,    39,    68,    76,    81,    76,    11,    42,    72,
      12,    39,    41,    41,    76,    76,    39,    36,    77,    39,
      76,    44,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    43,    36,    40,    76,    76,
      67,    67,    38,    40,    76,    39,    76,    40,    20,    21,
      22,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,     3,    36,    73,    42,    42,    40,
      78,    79,    40,    39,    39,    77,    43,    75,    40,    76,
      80,    76,    76,    39,    76,    14,    43,    40,    43,    78,
      74,    41,    76,    76,    40,    40,    67,    40,    36,    12,
      42,    76,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 90 "wildc.y"
    {
			strcpy( currentContext, "@global" );
			printf(".assembly %s {} \n", className);	
			printf(".assembly extern mscorlib {} \n\n");
			
			
			printf(".class public %s extends [mscorlib]System.Object{ \n\n", className);
			globals = 1;
			
		;}
    break;

  case 4:
#line 103 "wildc.y"
    {			
			int n, i;
			globals = 0;
				/* output the MSIL code to make the program class with globals as public static class variables */
				/* add the .cctor() method if global array variables need to be created */
				/* all the functions will be static methods of this class */
			printf("\t.method private hidebysig specialname rtspecialname static void .cctor() cil managed{\n");
			
			for ( i=0; i<NSYMS; i++ ){
				if ( symtab[i].name[0] == "/0"){
					break;
				}
				if ( symtab[i].isArray && strcmp(symtab[i].context, "@global") == 0){
					printf("\t\t ldc.i4 %i \n", symtab[i].arrayMax);
					printf("\t\t newarr %s \n\n", enumType(symtab[i].type));
					printf("\t\t stsfld %s[] %s::%s \n\n", enumType(symtab[i].type), 
						className, symtab[i].name);
				}
			}
			printf("\t\t ret \n");
			printf("\t}\n");
		
			
			tabIndex++;
			
		;}
    break;

  case 5:
#line 132 "wildc.y"
    {
			printf("\n} // end of class");
		;}
    break;

  case 6:
#line 139 "wildc.y"
    {
			
		;}
    break;

  case 7:
#line 142 "wildc.y"
    {
			/* no global defs */
		;}
    break;

  case 8:
#line 148 "wildc.y"
    { ;}
    break;

  case 9:
#line 150 "wildc.y"
    { ;}
    break;

  case 10:
#line 155 "wildc.y"
    {
			setSymbol( currentContext, (yyvsp[-1].str), (yyvsp[-2].datDefType).type, (yyvsp[-2].datDefType).isArray ? (yyvsp[-2].datDefType).arrayMax : 0, FALSE_ );
			
			if(globals != 1)
				sprintf(myBuffer, "[%d] ", getLocalIndex());
			else
				sprintf(myBuffer, ".field public static ", getLocalIndex());
			
			sprintf(myBuffer, "%s %s", myBuffer, enumType((yyvsp[-2].datDefType).type));
			// if array, output the []
			if((yyvsp[-2].datDefType).isArray) sprintf(myBuffer, "%s[]", myBuffer);
			sprintf(myBuffer, "%s %s", myBuffer, (yyvsp[-1].str));
			
			if(globals == 1){
				printf("\t%s\n", myBuffer);
			}else{
				(yyval.str) = _strdup(myBuffer);
			}
		;}
    break;

  case 11:
#line 178 "wildc.y"
    {
			(yyval.datDefType).type = (yyvsp[-1].dtype);
			(yyval.datDefType).isArray = TRUE_;
			(yyval.datDefType).arrayMax = (yyvsp[0].ival);
		;}
    break;

  case 12:
#line 184 "wildc.y"
    {
			(yyval.datDefType).type = (yyvsp[0].dtype);
			(yyval.datDefType).isArray = FALSE_;
			(yyval.datDefType).arrayMax = 0;
		;}
    break;

  case 13:
#line 193 "wildc.y"
    { (yyval.dtype) = int_; ;}
    break;

  case 14:
#line 195 "wildc.y"
    { (yyval.dtype) = float_; ;}
    break;

  case 15:
#line 197 "wildc.y"
    { (yyval.dtype) = string_; ;}
    break;

  case 16:
#line 199 "wildc.y"
    { (yyval.dtype) = bool_; ;}
    break;

  case 17:
#line 204 "wildc.y"
    {
			(yyval.ival) = atoi((yyvsp[-1].str));
			if ( (yyval.ival) <= 0 )
				yyerror( "data array declaration of %d must be greater than 0", (yyval.ival) );
		;}
    break;

  case 18:
#line 213 "wildc.y"
    { ;}
    break;

  case 19:
#line 215 "wildc.y"
    { ;}
    break;

  case 20:
#line 220 "wildc.y"
    {
			setSymbol( "@global", (yyvsp[0].str), func_, 0, FALSE_ ); // add method to global 
			setFuncRetType( (yyvsp[0].str), (yyvsp[-2].dtype) ); // set return type
			strcpy( currentContext, (yyvsp[0].str) ); // switch context to method
			
			printf("%s.method public static %s %s( ",getTabs(tabIndex), enumType((yyvsp[-2].dtype)), (yyvsp[0].str));
			
			sprintf( currentContext, "%s",  (yyvsp[0].str));
			
			localIndex = 0;
			
		;}
    break;

  case 21:
#line 231 "wildc.y"
    {
			
			//! Parameters
			/* output the MSIL top code for this function with the parms etc. */
			//! Output the opening signature line for the method. (ex: line 76 in objprimes.il)
			//! also includes the opening brace ({), and the .entrypoint (if main)
			printf(" ) cil managed{ \n\n");
			//! increment tabs
			tabIndex++;
			if( strcmp(currentContext, "main") == 0 ){
				printf("%s.entrypoint\n", getTabs(tabIndex));
				
			}
			printf("%s.maxstack 8\n\n", getTabs(tabIndex));
			
		;}
    break;

  case 22:
#line 248 "wildc.y"
    {
			//! This is handled lower at local_defs -> local_definitions
		;}
    break;

  case 23:
#line 252 "wildc.y"
    {
			//! THIS is where everything is happening
			/* all the function statements have now generated code; if we did not do a "return" in the function we need to generate a */
			/* return here, at the end of the function.  If the function expects to return a value, we must put something on the stack */
			/* for the calling function to use; a (void) call will have to pop this default value or the stack won't be empty at the end */
			/* of the program. */
			
			if ( (yyvsp[-12].dtype) != void_ ){
				printf("\n%s // if no return value was specified \n", getTabs(tabIndex));
				switch( (yyvsp[-12].dtype) )
				{
				case int_:
					/* create MSIL code to push 0 */
					printf("%s ldc.i4 0\n", getTabs(tabIndex));
					break;
				case float_:
					/* create MSIL code to push 0.0 */
					printf("%s ldc.r4 0.0\n", getTabs(tabIndex));
					break;
				case string_:
					/* create MSIL code to push "" */
					printf("%s ldstr \"\"\n", getTabs(tabIndex));
					break;
				case bool_:
					printf("%s ldc.i4 0\n", getTabs(tabIndex));
					/* create MSIL code to push "false" */
					break;
				default:
					yyerror( "illegal return type of %d for function %s", (yyvsp[-12].dtype), (yyvsp[-10].str) );
					break;
				}
			}
			printf("%s ret\n", getTabs(tabIndex));
			tabIndex--;
			printf("%s}\n\n", getTabs(tabIndex));
			/* output MSIL to do a function return */
			/* output MSIL code to end the function */
			
		;}
    break;

  case 24:
#line 295 "wildc.y"
    {
			(yyval.dtype) = void_;
		;}
    break;

  case 25:
#line 299 "wildc.y"
    {
			(yyval.dtype) = (yyvsp[0].dtype);
		;}
    break;

  case 26:
#line 306 "wildc.y"
    {
			;
		;}
    break;

  case 27:
#line 310 "wildc.y"
    {
			
			//! prints the parameters, unless void
			printf("%s", (yyvsp[0].str));
			
			sprintf( paramBuffer, ""); //! clear the buffer
		;}
    break;

  case 28:
#line 321 "wildc.y"
    {
			sprintf( paramBuffer, "%s", (yyvsp[0].str)); //! Set the first param
		;}
    break;

  case 29:
#line 325 "wildc.y"
    {
			
			sprintf( paramBuffer, "%s, %s", paramBuffer, (yyvsp[0].str));
			(yyval.str) = _strdup(paramBuffer); //! happens on each param iteration, thus the use of the buffer
		;}
    break;

  case 30:
#line 334 "wildc.y"
    {
			char buff[100];
			setSymbol( currentContext, (yyvsp[0].str), (yyvsp[-1].dtype), 0, TRUE_ );
			
			sprintf( buff, "%s %s", enumType((yyvsp[-1].dtype)), (yyvsp[0].str)); 
			(yyval.str) = _strdup(buff);
		;}
    break;

  case 31:
#line 345 "wildc.y"
    {
			int n, i, params;
			struct symbolDef *symbPtr;
			
				printf("%s.locals init(%s", getTabs(tabIndex), (yyvsp[0].str));
				//! be sure to clear the buffer
				sprintf(myBuffer, "");
				
				if(localIndex > 0) printf(",");
				
				for(i=2; i<6;i++){
					printf("\n\t\t\t [%d] %s _%s,", localIndex++, enumType(i), enumType(i));
				}
				printf("\n\t\t\t [%d] int32 _index", localIndex++);
				
				symbPtr = getSymbol( "@global", currentContext );
				
				if ( !symbPtr )
					yyerror( "function %s does not exist (yet) in symbol table", currentContext );
				
				//! create variables to store the parameters in
				for(n = 1; n <= symbPtr->fnNumParams; n++){
					for ( i=0; i<NSYMS; i++ ){
						if ( symtab[i].name[0] == "/0"){
							break;
						}
						if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
							printf(",\n\t\t\t [%i] %s %s", localIndex++, enumType(symtab[i].type), symtab[i].name);
						}
					}
				}
				printf(")\n\n"); // end of locals
				
				
				//! now we need to store the parameters in their variables
				for(n = 1; n <= symbPtr->fnNumParams; n++){
					for ( i=0; i<NSYMS; i++ ){
						if ( symtab[i].name[0] == "/0"){
							break;
						}
						if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
							printf("%s ldarg %s\n", getTabs(tabIndex), symtab[i].name);
							printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
						}
					}
				}
				
				//! now we need to initialize any arrays
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isArray && strcmp(symtab[i].context, currentContext) == 0){
						printf("%s ldc.i4 %i\n", getTabs(tabIndex), symtab[i].arrayMax);
						printf("%s newarr %s\n", getTabs(tabIndex), enumType(symtab[i].type));
						printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
						
					}
				}
		;}
    break;

  case 32:
#line 405 "wildc.y"
    {
			
			//! still need to have the temps / parameters
			int n, i, params;
			struct symbolDef *symbPtr;
			printf("%s.locals init( ", getTabs(tabIndex));

			if(localIndex > 0) printf(",");
			for(i=2; i<6;i++){
				printf("\n\t\t\t [%d] %s _%s,", localIndex++, enumType(i), enumType(i));
			}
			printf("\n\t\t\t [%d] int32 _index", localIndex++);
			
			symbPtr = getSymbol( "@global", currentContext );
			
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", currentContext );
			
			//! create variables to store the parameters in
			for(n = 1; n <= symbPtr->fnNumParams; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
						printf(",\n\t\t\t [%i] %s %s", localIndex++, enumType(symtab[i].type), symtab[i].name);
					}
				}
			}
			printf(")\n\n"); // end of locals
					
			
			//! now we need to store the parameters in their variables
			for(n = 1; n <= symbPtr->fnNumParams; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
						printf("%s ldarg %s\n", getTabs(tabIndex), symtab[i].name);
						printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
					}
				}
			}
			
			//! now we need to initialize any arrays
			for ( i=0; i<NSYMS; i++ ){
				if ( symtab[i].name[0] == "/0"){
					break;
				}
				if ( symtab[i].isArray && strcmp(symtab[i].context, currentContext) == 0){
					printf("%s ldc.i4 %i\n", getTabs(tabIndex), symtab[i].arrayMax);
					printf("%s newarr %s\n", getTabs(tabIndex), enumType(symtab[i].type));
					printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
				}
			}
		;}
    break;

  case 33:
#line 466 "wildc.y"
    {
			
			(yyval.str) = (yyvsp[0].str);
		;}
    break;

  case 34:
#line 471 "wildc.y"
    {
			//! push the next definition onto the buffer
			sprintf( myBuffer, "%s,\n\t\t\t %s", (yyvsp[-1].str), (yyvsp[0].str));
			(yyval.str) = _strdup(myBuffer);
			sprintf( myBuffer, "");
		;}
    break;

  case 35:
#line 481 "wildc.y"
    {
			;
		;}
    break;

  case 36:
#line 485 "wildc.y"
    {
			;
		;}
    break;

  case 37:
#line 492 "wildc.y"
    {
			struct symbolDef *symb;
			char holder [500];
			symb = getSymbol( currentContext, (yyvsp[0].str) );
			if ( !symb )
			{
				symb = getSymbol( "@global", (yyvsp[0].str) );
				if ( !symb )
				{
					yyerror( "identifier %s not defined in program", (yyvsp[0].str) );
				}
			}
			
			;	/* make MSIL code to push ID identifier on the stack according to its type in symb->type */
			//! get the type. Context can change how u push it on the stack
			//! Need to store the reference for when we come back out of data_ref and expression, 
			//!		so we will just have the identifier and the new value
			
			(yyval.datRefType).symbPtr = symb;
			(yyval.datRefType).isArrayRef = FALSE_;
		;}
    break;

  case 38:
#line 514 "wildc.y"
    {
		struct symbolDef *symb;
		
			symb = getSymbol( currentContext, (yyvsp[-3].str) );
			if ( !symb )
			{
				symb = getSymbol( "@global", (yyvsp[-3].str) );
				if ( !symb )
				{
					yyerror( "identifier %s not defined in program\n", (yyvsp[-3].str) );
				}
				if ( !symb->isArray )
					yyerror( "%s is not an array but is being referenced as an array element", (yyvsp[-3].str) );
				
				printf("%s stloc _int32 \t\t// temp store index\n", getTabs(tabIndex));
				printf("%s ldsfld %s[] %s::%s \n", getTabs(tabIndex), enumType(symb->type), className, symb->name);
				printf("%s ldloc _int32 \t\t// reload index\n", getTabs(tabIndex));
				
			}else{
			
				if ( !symb->isArray )
					yyerror( "%s is not an array but is being referenced as an array element", (yyvsp[-3].str) );
		
				(yyval.datRefType).symbPtr = symb;
				(yyval.datRefType).isArrayRef = TRUE_;
				
				//! store the array expression in the temp
				
					
				
				printf("%s stloc _int32 \t\t// temp store index\n", getTabs(tabIndex));
				printf("%s ldloc %s \t\t// array\n", getTabs(tabIndex), (yyvsp[-3].str));
				printf("%s ldloc _int32 \t\t// index\n", getTabs(tabIndex), enumType(symb->type));
			}
			(yyval.datRefType).symbPtr = symb;
			(yyval.datRefType).isArrayRef = TRUE_;
		;}
    break;

  case 39:
#line 555 "wildc.y"
    {
		char *label;
		
			/* if $3 is bool_ or can be converted to bool_ then create MSIL code to do so, else yyerror */
			if((yyvsp[-1].dtype) != bool_){
				if((yyvsp[-1].dtype) == int_ || (yyvsp[-1].dtype) == float_){
					printf("%s conv.i4 \t\t// Convert to boolean\n", getTabs(tabIndex));
				}else{
					yyerror("if_	 requires boolean");
				}
			}
			/* create 2 labels; use 1 for if and 2 for if/else */
			//label = generateLabel();
			strcpy((yyval.labDefType).label1, generateLabel());
			strcpy((yyval.labDefType).label2, generateLabel());
			//label = generateLabel();
			
			
			printf("%s brfalse %s \t// branch to if_else_false or if_exit \n", getTabs(tabIndex), (yyval.labDefType).label1);
			/* create MSIL code to test if stack is not True_ and br to label $$.label1 if not */
		;}
    break;

  case 40:
#line 579 "wildc.y"
    {
		char *label;
		
			/* create 2 labels */
			strcpy( (yyval.labDefType).label1, generateLabel());
			strcpy( (yyval.labDefType).label2, generateLabel());
			
			/* create MSIL code to output label $$.label1: */
			printf("%s: \t\t\t // while_return \n", (yyval.labDefType).label1);
		;}
    break;

  case 41:
#line 592 "wildc.y"
    {
			/* if $4 is bool_ or can be converted to bool_ then create MSIL code to do so, else yyerror */
			/* create MSIL code to test if stack is not True_ and br to label $2.label2 if not */
			if((yyvsp[-1].dtype) != bool_){
				if((yyvsp[-1].dtype) == int_ || (yyvsp[-1].dtype) == float_){
					printf("%s conv.i4 \t\t// Convert to boolean\n", getTabs(tabIndex));
				}else{
					yyerror("while_test requires boolean");
				}
			}
			//! eval of bool already happened
			printf("%s brfalse %s \t\t// branch while_exit \n", getTabs(tabIndex), (yyvsp[-3].labDefType).label2);
			strcpy( (yyval.labDefType).label1, (yyvsp[-3].labDefType).label1 );
			strcpy( (yyval.labDefType).label2, (yyvsp[-3].labDefType).label2 );
		;}
    break;

  case 42:
#line 611 "wildc.y"
    {
			if ( (yyvsp[-3].datRefType).symbPtr->isArray && !(yyvsp[-3].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[-3].datRefType).symbPtr->name );
			
			/* look at type in data_ref and type of "expression"; if they are compatible do store or 'stelem' */
			/* if expression can be converted to $1 type then create code to do the conversion before the store or stelem */
			if( !(yyvsp[-3].datRefType).symbPtr->isArray){
				// Not an array
				if( (yyvsp[-3].datRefType).symbPtr->type != (yyvsp[-1].dtype)){
					int b = 1;
					if( (yyvsp[-3].datRefType).symbPtr->type == int_ ){
						// Ints 
						if((yyvsp[-1].dtype) == float_){
							b = 1;
						}
					}else if( (yyvsp[-3].datRefType).symbPtr->type == float_ ){
						// Floats
						if( (yyvsp[-1].dtype) == int_ ){
							printf( "%s conv.r4 \t\t//Converting int to float \n ", getTabs(tabIndex));
							b = 0;
						}else{
							b = 1;
						}
					}
					if(b == 1) 
						yyerror("Cannot cast %s to (%s) variable '%s'!", 
								enumType((yyvsp[-1].dtype)), enumType((yyvsp[-3].datRefType).symbPtr->type), (yyvsp[-3].datRefType).symbPtr->name);  
				}
				if(strcmp((yyvsp[-3].datRefType).symbPtr->context, "@global")){
					printf("%s stloc %s \n", getTabs(tabIndex), (yyvsp[-3].datRefType).symbPtr->name);
				}else{
					printf("%s stsfld %s %s::%s\n", getTabs(tabIndex), 	enumType((yyvsp[-3].datRefType).symbPtr->type),
						className, (yyvsp[-3].datRefType).symbPtr->name);
				}
			}else{
				//! the array and index are already on the stack
				//! the value to be stored is on the stack too! just store it
				printf("%s // the value above this line will be stored in the array \n", getTabs(tabIndex));
				printf("%s stelem %s \n\n", getTabs(tabIndex), enumType((yyvsp[-3].datRefType).symbPtr->type));
				/*if($1.symbPtr->type==string_ || $1.symbPtr->type==bool_)
					printf("%s stelem.ref \n\n", getTabs(tabIndex));
				else
					printf("%s stelem.%s \n\n", getTabs(tabIndex), primType($1.symbPtr->type));
				*/
			}
			
		;}
    break;

  case 43:
#line 659 "wildc.y"
    {
			//! then skip this one
			if ( (yyvsp[-2].datRefType).symbPtr->isArray && !(yyvsp[-2].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[-2].datRefType).symbPtr->name );
			
			;	/* if $1 is not a string_ then yyerror (maybe consider converting to string_) */
				/* if $3 is not int type but can be converted to int then do it here, else yyerror */
				/* create MSIL to check if top of stack ($3) < 0 then throw error */
				/* create MSIL to check if len( $1 ) <= $3 then throw error */
		;}
    break;

  case 44:
#line 670 "wildc.y"
    {
			;	/* if $6 is not int type but can be converted to int then do it here, else yyerror */
				/* create MSIL to check if top of stack ($3) < 0 then throw error */
				/* create MSIL to check if $3 data + $6 data > len( $1 )+1 then throw error */
		;}
    break;

  case 45:
#line 676 "wildc.y"
    {
			;	/* if $10 is not string type but can be converted to string then do it here, else yyerror */
				/* create code for:
					a) if $3 == 0, $1 := $10 + $1.substring( $3+$6, to the end )
					b) if $3 != 0, $1 := $1.substring( 0, $3 ) + $10 + $1.substring( $3+$6, to the end )
				*/	
		;}
    break;

  case 46:
#line 684 "wildc.y"
    {
			
			;	/* create MSIL code to output label $1.label1: */
			printf("%s: \t\t\t// if_exit \n", (yyvsp[-3].labDefType).label1);
		;}
    break;

  case 47:
#line 690 "wildc.y"
    {
			/* create MSIL code to br to label $1.label2 */
			printf("%s br %s \t\t// branch to if_else_exit \n", getTabs(tabIndex), (yyvsp[-3].labDefType).label2);
			/* create MSIL code to output label $1.label1: */
			
			printf("%s: \t\t\t// if_else_false \n", (yyvsp[-3].labDefType).label1);
		;}
    break;

  case 48:
#line 698 "wildc.y"
    {
			;	/* create MSIL code to output label $1.label2: */
			printf("%s: \t\t\t// if_else_exit  \n", (yyvsp[-8].labDefType).label2);
		;}
    break;

  case 49:
#line 703 "wildc.y"
    {
			;	/* create MSIL code to br to label $1.label1 */
				/* create MSIL code to output label $1.label2: */
				
			printf("%s br %s \n", getTabs(tabIndex), (yyvsp[-3].labDefType).label1);
			printf("%s: \t\t\t// while_exit  \n", (yyvsp[-3].labDefType).label2);			
		;}
    break;

  case 50:
#line 711 "wildc.y"
    {
			char* after_notEmpty;
			char* not_true;
			char* after_compare;
			
			if ( (yyvsp[-1].datRefType).symbPtr->isArray && !(yyvsp[-1].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[-1].datRefType).symbPtr->name );
			
			//! Display & catch input
			if(_isDebug == 1){
				printf("%s ldstr \"(%s): \" \n", getTabs(tabIndex), 
					enumType((yyvsp[-1].datRefType).symbPtr->type));
				printf("%s call void [mscorlib]System.Console::Write(string) \n", getTabs(tabIndex));
			}
			printf("%s call string [mscorlib]System.Console::ReadLine() \n", 
				getTabs(tabIndex), (yyvsp[-1].datRefType).symbPtr->name);
			
			after_notEmpty = generateLabel();
			printf("%s dup \n", getTabs(tabIndex));
			printf("%s callvirt instance int32 [mscorlib]System.String::get_Length() \n", getTabs(tabIndex));
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			printf("%s bgt %s\n\n", getTabs(tabIndex), after_notEmpty);
			printf("%s pop \t\t// pop the empty input\n", getTabs(tabIndex), after_notEmpty);
			printf("%s ldstr \"0\" \n", getTabs(tabIndex));
			printf("%s: \t\t\t// label after_notEmpty \n", after_notEmpty);
			switch((yyvsp[-1].datRefType).symbPtr->type){
				case string_:
					// don't need to cast it at all
					break;
					
				case int_:
					printf("%s call int32 [mscorlib]System.Int32::Parse(string) \n", getTabs(tabIndex));
					break;
					
				case float_:
					printf("%s call float32 [mscorlib]System.Single::Parse(string) \n", getTabs(tabIndex));
					break;
					
				case bool_:
					
					
					// the hard one. push 
					
					// set to lowercase
					printf("%s callvirt instance string [mscorlib]System.String::ToLower() \n", 
						getTabs(tabIndex));
			
					printf("%s ldstr \"true\" \t\t// 't' for comparison \n", getTabs(tabIndex));
					printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(string) \t\t// compare strings \n", getTabs(tabIndex));
					// we now have a 0 only if it was some variation of "true". Get labels
					not_true = generateLabel();
					after_compare = generateLabel();
					// we'll jump below if it's not 0, otherwise set it to 0
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s bne.un %s \t\t// branch not_true \n", getTabs(tabIndex), not_true);
						// it's true, so push a 1
						printf("%s ldc.i4 1 \n", getTabs(tabIndex));
						printf("%s br %s // branch after_compare \n", getTabs(tabIndex), after_compare);
					// else
						// it's false
						printf("%s: \t\t\t// not_true label \n", not_true);
						printf("%s ldc.i4 0 \n", getTabs(tabIndex));
						
					printf("%s: \t\t\t// after_compare label  \n", after_compare);
					break;
										
				default:
					yyerror("Could not cast input to datatype %s", enumType((yyvsp[-1].datRefType).symbPtr->type));
					break;
			}
			printf("%s stloc %s \n", getTabs(tabIndex), (yyvsp[-1].datRefType).symbPtr->name);
		;}
    break;

  case 51:
#line 784 "wildc.y"
    {
			;	/* code generation happens in print_list */
		;}
    break;

  case 52:
#line 788 "wildc.y"
    {
		struct symbolDef *symbPtr;

			symbPtr = getSymbol( "@global", currentContext );
			if ( !symbPtr )
				yyerror( "internal fault: function %s can't be found in symbol table", currentContext );
				
			if ( symbPtr->fnRetType == void_ )
				yyerror( "function %s has a return type of VOID so an expression cannot be returned", currentContext );
			
			if ( symbPtr->fnRetType == (yyvsp[-1].dtype) ){
				//! don't need to load it from storage
				printf("%s ret \n", getTabs(tabIndex));
			}else{
				yyerror( "function %s has a return type of '%s', not '%s'", currentContext, enumType(symbPtr->fnRetType), enumType((yyvsp[-1].dtype)) );
			}
			/* see if $2 (a type) is compatible with symbPtr->fnRetType; if they are the same type then just output MSIL to return */
			/* (the return value is already on the stack); if type $2 can be converted to symbPtr->fnRetType then output MSIL code */
			/* to do the translation and then output a return; else error */
		
		;}
    break;

  case 53:
#line 810 "wildc.y"
    {
			struct symbolDef *symbPtr;
			int params, n, i, depth;
			symbPtr = getSymbol( "@global", (yyvsp[-5].str) );
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", (yyvsp[-5].str) );
			
			if ( symbPtr->type != func_ )
				yyerror( "%s is not a function ", (yyvsp[-5].str) );
				
			
			/* notice that functions have to be defined before they are used */
			/* write code to confirm fn parameters for ID correspond to tmpFnCallParms in number and type else yyerror */
			/* i.e., confirm fn parameters for ID correspond to the tmpFnCallParmIdx[$5] types in tmpFnCallParms[$5] produced in function_call_list else yyerror */
			/* create code to call fn with parameters */
			/* if we called a function that returned a value that is on the stack remove it or the stack will not be empty when we end */
			
			
			params = symbPtr->fnNumParams;
			tmpFnCallParmIdx[(yyvsp[-4].ival)]--;
			for(n = params; n > 0; n--){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[i] == "/0"){
						break;
					}
					
					if ( symtab[i].isParam && symtab[i].paramSeq == n && !strcmp(symtab[i].context, (yyvsp[-5].str)) ){

						if(tmpFnCallParms[(yyvsp[-4].ival)][ tmpFnCallParmIdx[(yyvsp[-4].ival)]-- ] != symtab[i].type)
							yyerror("Incorrect parameters passed to method. (%s:%s)",
								symtab[i].context, symtab[i].name);
								
						
						break;
					}
				}
			}
			// we're all good. call it
			
			
			printf("%s call %s %s::%s( ", getTabs(tabIndex), enumType(symbPtr->fnRetType),
				className, (yyvsp[-5].str));		
			for(n = 1; n <= params; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[i] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && !strcmp(symtab[i].context, (yyvsp[-5].str)) ){
						printf("%s", enumType(symtab[i].type));
						if(params > n) printf(", ");
					}
				}
			}
			printf(" )\n\n");
			
			
			if ( symbPtr->fnRetType != void_ )
				switch( symbPtr->fnRetType )
				{
				case int_:
				case float_:
				case string_:
				case bool_:
					printf("%s pop\n", getTabs(tabIndex));
					break;
				default:
					yyerror( "illegal return type of %d for function %s", symbPtr->fnRetType, (yyvsp[-5].str) );
					break;
				}
			tmpFnCallDepth--;
		;}
    break;

  case 54:
#line 885 "wildc.y"
    {
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '+' operation */
			//$$ = compatible type;
			//! Check to make sure it happens. Cast if possible or error as necessary.
			
			// Set the return type
			int i = isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype));
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			// All good. Set the expression type and output
			printf("%s add \n", getTabs(tabIndex));
			(yyval.dtype) = i;
		;}
    break;

  case 55:
#line 902 "wildc.y"
    {
			int i = isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype));		
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			// All good. Set the expression type and output
			printf("%s sub \n", getTabs(tabIndex));
			(yyval.dtype) = i;
		;}
    break;

  case 56:
#line 913 "wildc.y"
    {
			int i = isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype));
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			// All good. Set the expression type and output
			printf("%s mul \n", getTabs(tabIndex));
			(yyval.dtype) = i;
		;}
    break;

  case 57:
#line 924 "wildc.y"
    {
			int i = isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype));
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			// All good. Set the expression type and output
			printf("%s div \n", getTabs(tabIndex));
			(yyval.dtype) = i;
		;}
    break;

  case 58:
#line 935 "wildc.y"
    {
			
			char* trueLabel;
			char* afterLabel;
			/* confirm types are bool_ or can be casted to bool_, else yyerror */
			/* gen code to do AND operation */
			if( (yyvsp[-2].dtype) != bool_ && (yyvsp[0].dtype) != bool_)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			//! both expressions should have pushed a one, so we if add the stack and whats on the stack isn't 2, its false
			printf("%s add \n", getTabs(tabIndex));
			
			//! push 2 onto stack for comparison
			printf("%s ldc.i4 2 \n", getTabs(tabIndex));
			
			//! generate labels
			trueLabel = generateLabel();
			afterLabel = generateLabel();
			
			//! branch to trueLabel if stack is >= 2
			printf("%s bge %s \t//&& branch if true \n\n", getTabs(tabIndex), trueLabel);
			
				//! if your here, it's not >=2; push 0 for false, then branch to afterLabel
				printf("%s ldc.i4 0 \t//&& push false \n", getTabs(tabIndex));
				printf("%s br %s \n", getTabs(tabIndex), afterLabel);
				
				//! print the true label, then generate the one
				printf("%s: \t\t//&& TRUE LABEL \n", trueLabel);
				printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			
			//! print after label, then be done
			printf("%s: \t\t//&& AFTER LABEL\n", afterLabel);
			(yyval.dtype) = bool_;
		;}
    break;

  case 59:
#line 971 "wildc.y"
    {
			
			char* trueLabel;
			char* afterLabel;
			/* confirm types are bool_ or can be casted to bool_, else yyerror */
			/* gen code to do || operation */
			if( (yyvsp[-2].dtype) != bool_ && (yyvsp[0].dtype) != bool_)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			//! both expressions should have pushed a one, so we if add the stack and whats on the stack isn't 2, its false
			printf("%s add \n", getTabs(tabIndex));
			
			//! push 0 onto stack for comparison
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			
			//! generate labels
			trueLabel = generateLabel();
			afterLabel = generateLabel();
			
			//! branch to trueLabel if stack is > 0
			printf("%s bgt %s \t//|| branch if true \n\n", getTabs(tabIndex), trueLabel);
			
				//! if your here, it's not >=2; push 0 for false, then branch to afterLabel
				printf("%s ldc.i4 0 \t//|| push false \n", getTabs(tabIndex));
				printf("%s br %s \n", getTabs(tabIndex), afterLabel);
				
				//! print the true label, then generate the one
				printf("%s: \t\t//|| TRUE LABEL \n", trueLabel);
				printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			
			//! print after label, then be done
			printf("%s: \t\t//|| AFTER LABEL\n", afterLabel);
			(yyval.dtype) = bool_;
		;}
    break;

  case 60:
#line 1007 "wildc.y"
    {
			(yyval.dtype) = bool_;
			// start here
			if((yyvsp[-2].dtype) == string_ && (yyvsp[0].dtype) != bool_){
				printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(%s)\n", 
					getTabs(tabIndex), enumType((yyvsp[0].dtype)));
				// if they're equal, we get 0, so then we just compare 0 to 0 to get true	
				printf("%s ldc.i4 0", getTabs(tabIndex));
			}else if((yyvsp[-2].dtype) != (yyvsp[0].dtype)){
				if(isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype)) == -1){
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s ldc.i4 1 \n", getTabs(tabIndex));
				}
			}
			printf("%s ceq \t// Are they equal \n", getTabs(tabIndex));
			
			
		;}
    break;

  case 61:
#line 1028 "wildc.y"
    {
			(yyval.dtype) = bool_;
			// start here
			if((yyvsp[-2].dtype) == string_ && (yyvsp[0].dtype) != bool_){
				printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(%s)\n", 
					getTabs(tabIndex), enumType((yyvsp[0].dtype)));
				// if they're equal, we get 0, so then we just compare 0 to 0 to get true	
				printf("%s ldc.i4 0", getTabs(tabIndex));
			}else if((yyvsp[-2].dtype) != (yyvsp[0].dtype)){
				if(isIntAndFloat((yyvsp[-2].dtype), (yyvsp[0].dtype)) == -1){
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s ldc.i4 1 \n", getTabs(tabIndex));
				}
			}
			printf("%s ceq \t// Are they equal? \n", getTabs(tabIndex));
			//! if they're equal, we have a true on the stack. So if we compare with a false, we'll get the right answer
			printf("%s ldc.i4 0 \t// 0 for comparing our answer \n", getTabs(tabIndex));
			
			printf("%s ceq \t// Invert our answer \n", getTabs(tabIndex));
		;}
    break;

  case 62:
#line 1051 "wildc.y"
    {
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '<' */
			if( ((yyvsp[-2].dtype) != int_ && (yyvsp[-2].dtype) != float_) ||
				((yyvsp[0].dtype) != int_ && (yyvsp[0].dtype) != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			// Convert the top item ($3) to the second item($1)'s type
			if((yyvsp[-2].dtype) != (yyvsp[0].dtype)) 
				printf("%s conv.%s \t\t//convert to other type \n", getTabs(tabIndex), primType((yyvsp[-2].dtype)));
			
			printf("%s clt \t\t//tos+1 < tos \n", getTabs(tabIndex));
			(yyval.dtype) = bool_;
		;}
    break;

  case 63:
#line 1066 "wildc.y"
    {
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '>' */
			if( ((yyvsp[-2].dtype) != int_ && (yyvsp[-2].dtype) != float_) ||
				((yyvsp[0].dtype) != int_ && (yyvsp[0].dtype) != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			if((yyvsp[-2].dtype) != (yyvsp[0].dtype)) 
				printf("%s conv.%s \t\t//convert to other type \n", getTabs(tabIndex), primType((yyvsp[-2].dtype)));
				
			printf("%s cgt \t\t//tos+1 < tos \n", getTabs(tabIndex));
			(yyval.dtype) = bool_;
		;}
    break;

  case 64:
#line 1080 "wildc.y"
    {
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do LTE */
			if( ((yyvsp[-2].dtype) != int_ && (yyvsp[-2].dtype) != float_) ||
				((yyvsp[0].dtype) != int_ && (yyvsp[0].dtype) != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			if((yyvsp[-2].dtype) != (yyvsp[0].dtype)) 
				printf("%s conv.%s //convert to other type \n", getTabs(tabIndex), primType((yyvsp[-2].dtype)));
				
			// subtract them
			printf("%s sub \n", getTabs(tabIndex));
			
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			// if result < 0, it's true
			printf("%s clt \n", getTabs(tabIndex));
			
			(yyval.dtype) = bool_;
		;}
    break;

  case 65:
#line 1100 "wildc.y"
    {
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do GTE */
			if( ((yyvsp[-2].dtype) != int_ && (yyvsp[-2].dtype) != float_) ||
				((yyvsp[0].dtype) != int_ && (yyvsp[0].dtype) != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType((yyvsp[-2].dtype)),enumType((yyvsp[0].dtype)));
			
			if((yyvsp[-2].dtype) != (yyvsp[0].dtype)) 
				printf("%s conv.%s //convert to other type \n", getTabs(tabIndex), primType((yyvsp[-2].dtype)));
				
			// subtract them
			printf("%s sub \n", getTabs(tabIndex));
			
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			// if result > 0, it's true
			printf("%s cgt \n", getTabs(tabIndex));
			
			(yyval.dtype) = bool_;
		;}
    break;

  case 66:
#line 1120 "wildc.y"
    {
			(yyval.dtype) = (yyvsp[-1].dtype);
		;}
    break;

  case 67:
#line 1124 "wildc.y"
    {
			printf("%s ldc.i4 %s \n", getTabs(tabIndex), (yyvsp[0].str));
			(yyval.dtype) = int_;
		;}
    break;

  case 68:
#line 1129 "wildc.y"
    {
			/* push $1 */
			printf("%s ldc.r4 %s \n", getTabs(tabIndex), (yyvsp[0].str));
			(yyval.dtype) = float_;
		;}
    break;

  case 69:
#line 1135 "wildc.y"
    {
			/* push $1 */
			printf("%s ldstr \"%s\" \n", getTabs(tabIndex), (yyvsp[0].str));
			
			(yyval.dtype) = string_;
		;}
    break;

  case 70:
#line 1142 "wildc.y"
    {
			/* push boolean true */
			printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			(yyval.dtype) = bool_;
		;}
    break;

  case 71:
#line 1148 "wildc.y"
    {
			/* push boolean false */
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			(yyval.dtype) = bool_;
		;}
    break;

  case 72:
#line 1154 "wildc.y"
    {
			//! if array, but not ref'd as array, error
			if ( (yyvsp[0].datRefType).symbPtr->isArray && !(yyvsp[0].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[0].datRefType).symbPtr->name );
			
			
			//! Push the variable's contents onto the stack
			if( (yyvsp[0].datRefType).symbPtr->isArray){
				printf("%s ldelem %s\n", getTabs(tabIndex), enumType((yyvsp[0].datRefType).symbPtr->type));
			}else{
				if( strcmp((yyvsp[0].datRefType).symbPtr->context, "@global")){
					printf("%s ldloc %s \n", getTabs(tabIndex), (yyvsp[0].datRefType).symbPtr->name);
				}else{
					printf("%s ldsfld %s %s::%s \n", getTabs(tabIndex), 
						enumType((yyvsp[0].datRefType).symbPtr->type), className, (yyvsp[0].datRefType).symbPtr->name);
				}
			}
			
			
			/* push '$1' */
			(yyval.dtype) = (yyvsp[0].datRefType).symbPtr->type;
		;}
    break;

  case 73:
#line 1177 "wildc.y"
    {			
			if ( (yyvsp[-2].datRefType).symbPtr->isArray && !( (yyvsp[-2].datRefType).isArrayRef ))
				printf("%s ldc.i4 %i \n", getTabs(tabIndex), (yyvsp[-2].datRefType).symbPtr->arrayMax);
			else if ( (yyvsp[-2].datRefType).symbPtr->type == string_ ){
				printf("%s ldloc %s \n", getTabs(tabIndex), (yyvsp[-2].datRefType).symbPtr->name);
				printf("%s callvirt instance int32 [mscorlib]System.String::get_Length() \n", getTabs(tabIndex));
			}
			else
				yyerror( "identifier %s is not an array name or a string", (yyvsp[-2].datRefType).symbPtr->name );
				
			(yyval.dtype) = int_;
		;}
    break;

  case 74:
#line 1190 "wildc.y"
    {
			if ( (yyvsp[-5].datRefType).symbPtr->isArray && !(yyvsp[-5].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[-5].datRefType).symbPtr->name );
			
			if ( (yyvsp[-1].dtype) != int_ )
			{
				if((yyvsp[-1].dtype) == float_ )
					printf("%s conv.i4 \n", getTabs(tabIndex));
				else
					yyerror( "function CHAR requires int; Cannot convert %s (%s) ",
						(yyvsp[-5].datRefType).symbPtr->name, enumType((yyvsp[-5].datRefType).symbPtr->type) );
				
			}
			// expression should be on there
			printf("%s stloc _int32 \n", getTabs(tabIndex));
			
			printf("%s ldloc %s \n", getTabs(tabIndex), (yyvsp[-5].datRefType).symbPtr->name);
			printf("%s callvirt instance char[] [mscorlib]System.String::ToCharArray() \n", getTabs(tabIndex));
			// now we have a character array on the stack
			printf("%s ldloc _int32 \t\t// the character to get\n", getTabs(tabIndex));
			printf("%s ldelem.u2 \t\t// load the character\n", getTabs(tabIndex));
			printf("%s call int32 [mscorlib]System.Convert::ToInt32(char)\n", getTabs(tabIndex));
			
			(yyval.dtype) = int_;
		;}
    break;

  case 75:
#line 1216 "wildc.y"
    {
			if ( (yyvsp[-1].dtype) != int_ )
			{
				;	/* see if $3 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			
			;	/* create code to push the string consisting of the single ASCII character of value $3 on stack */
			
			(yyval.dtype) = string_;
		;}
    break;

  case 76:
#line 1227 "wildc.y"
    {
			if ( (yyvsp[-7].datRefType).symbPtr->isArray && !(yyvsp[-7].datRefType).isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", (yyvsp[-7].datRefType).symbPtr->name );
			
			if ( (yyvsp[-3].dtype) != int_ )
			{
				;	/* see if $5 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			if ( (yyvsp[-1].dtype) != int_ )
			{
				;	/* see if $7 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			
			;	/* create code to push string $1.substring( $5, $7 ) on stack */
				/* make sure the .NET method used will throw an exsception if $5 to $7 is outside of $1 */
				
			(yyval.dtype) = string_;
		;}
    break;

  case 77:
#line 1246 "wildc.y"
    {
		struct symbolDef *symbPtr;
		int i, n;
		int params;
			symbPtr = getSymbol( "@global", (yyvsp[-4].str) );
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", (yyvsp[-4].str) );
				
			/* confirm fn parameters for ID correspond to the tmpFnCallParmIdx[$2] types in tmpFnCallParms[$2] produced in function_call_list else yyerror */
			/* confirm fn return type not VOID else yyerror */
			/* create code to call fn with parameters (they are already on the stack) */
			
			//! this needs to be passed the return value, then the parameter list inside of the ()			
			printf("%s call %s %s::%s(", getTabs(tabIndex), 
				enumType(symbPtr->fnRetType), className, symbPtr->name);

			params = symbPtr->fnNumParams;
			for(n = 1; n <= params; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, (yyvsp[-4].str)) == 0){
						if(n != 1) printf(",");
						printf(" %s", enumType(symtab[i].type));
					}
				}
			}
			printf(" ) \n");
			
			tmpFnCallDepth--;
			(yyval.dtype) = symbPtr->fnRetType;
		;}
    break;

  case 78:
#line 1282 "wildc.y"
    {
			(yyval.ival) = ++tmpFnCallDepth;
		;}
    break;

  case 79:
#line 1288 "wildc.y"
    {
			tmpFnCallParmIdx[ tmpFnCallDepth ] = 0;
		;}
    break;

  case 81:
#line 1292 "wildc.y"
    {
			tmpFnCallParmIdx[ tmpFnCallDepth ] = 0;	/* no parameters to function */
		;}
    break;

  case 82:
#line 1299 "wildc.y"
    {
			tmpFnCallParms[ tmpFnCallDepth ][ tmpFnCallParmIdx[ tmpFnCallDepth ]++ ] = (yyvsp[0].dtype);
		;}
    break;

  case 83:
#line 1303 "wildc.y"
    {
			tmpFnCallParms[ tmpFnCallDepth ][ tmpFnCallParmIdx[ tmpFnCallDepth ]++ ] = (yyvsp[0].dtype);
		;}
    break;

  case 84:
#line 1310 "wildc.y"
    {
			;	/* output code to print and pop data type $1, which is on the stack */
			printf("%s call void [mscorlib]System.Console::Write(%s) \n", getTabs(tabIndex), enumType((yyvsp[0].dtype)));
			
		;}
    break;

  case 85:
#line 1316 "wildc.y"
    {
			;	/* output code to print and pop data type $3, which is on the stack */
			printf("%s call void [mscorlib]System.Console::Write(%s) \n", getTabs(tabIndex), enumType((yyvsp[0].dtype)));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2793 "wildc.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1322 "wildc.y"


// arrayMax == 0 for non-array or fn or fn parameter
// fnNumParams will define the number of parameters if symbol is a fn
// paramSeq will define the sequence of parameters to a fn
int setSymbol( char *context, char *symbol, DType type, unsigned int arrayMax, boolean isparam ){
	int i;
	struct symbolDef *func;

	if ( isparam && ( arrayMax != 0 ))
		yyerror( "internal fault: symbol %s in context %s can't be declared an array and a parameter", symbol, context );
	if ( isparam && ( type < int_ || type > bool_ ))
		yyerror( "internal fault: symbol %s in context %s being set as type other than int, float, string, or bool", symbol, context );
		
	for ( i=0; i<NSYMS; i++ )
		if ( symtab[i].name[0] != '\0' )
		{
			if ( !strcmp( symtab[i].context, context ) && !strcmp( symtab[i].name, symbol ))
				yyerror( "identifier %s already defined in context %s\n", symbol, context );
		}

	if ( strlen( context ) > MAX_IDENT_LEN )
		yyerror( "context name %s has exceeded compiler max length of %d", context, MAX_IDENT_LEN );
		
	if ( strlen( symbol ) > MAX_IDENT_LEN )
		yyerror( "symbol name %s has exceeded compiler max length of %d", symbol, MAX_IDENT_LEN );
		
	for ( i=0; i<NSYMS; i++ )
		if ( symtab[i].name[0] == '\0' )
		{
			strcpy( symtab[i].context, context );
			strcpy( symtab[i].name, symbol );
			symtab[i].type = type;
			if ( arrayMax )
			{
				symtab[i].isArray = TRUE_;
				symtab[i].arrayMax = arrayMax;
			}
			else
			{
				symtab[i].isArray = FALSE_;
				symtab[i].arrayMax = 0;
			}
			symtab[i].isParam = isparam;
			if ( isparam )
			{
				func = getSymbol( "@global", context );
				if ( !func )
					yyerror( "internal fault: function %s not in symbol table when setting parameter %s in symbol table", context, symbol );
				func->fnNumParams++;
				symtab[i].paramSeq = func->fnNumParams;
			}
			else
				symtab[i].paramSeq = 0;
			symtab[i].fnNumParams = 0;
			symtab[i].fnRetType = unknown_;
			return 1;
		}

	yyerror( "symbol table is full; identifier %s can't be defined in context %s", symbol, context );

}


int setFuncRetType( char *fnName, DType retType ){
	struct symbolDef *fnPtr;

	fnPtr = getSymbol( "@global", fnName );
	if ( !fnPtr )
		yyerror( "function %s does not exist (yet) in symbol table", fnName );

	if ( fnPtr->fnRetType != unknown_ )
		yyerror( "function %s already has a return type set in symbol table", fnName );
		
	fnPtr->fnRetType = retType;
	return 1;
}


struct symbolDef *getSymbol( char *context, char *symbol ){
	int i;
	for ( i=0; i<NSYMS; i++ )
		if ( !strcmp( context, symtab[i].context ) && !strcmp( symbol, symtab[i].name ))
			return symtab+i;
	
	return NULL;	
}


char *generateLabel( void ){
	sprintf( genedLabel, "label%d", labelIndex++ );
	return _strdup(genedLabel);
}

char *enumType(DType type){
	switch(type){
		case 1:
			return "void";
			break;
		case 2:
			// Int
			return "int32";
			break;
		case 3:
			// float
			return "float32";
			break;
		case 4:
			return "string";
			// String
			break;
		case 5:
			// bool
			return "bool";
			break;
			
		default:
			return "unknown";
	}
}

char *primType(DType type){
	switch(type){
		case 1:
			return "";
			break;
		case 2:
			// Int
			return "i4";
			break;
		case 3:
			// float
			return "r4";
			break;
		case 4:
			return "string";
			// String
			break;
		case 5:
			// bool
			return "i4";
			break;
			
		default:
			return "unknown";
	}
}
char *systemType(DType type){
	switch(type){
		case 2:
			// Int
			return "System.Int32";
			break;
		case 3:
			// float
			return "System.Single";
			break;
		case 4:
			return "System.String";
			// String
			break;
		case 5:
			// bool
			return "System.Boolean";
			break;
			
		default:
			return "unknown";
	}
}
char *getTabs(int count){
	int i=0;
	char tabBuffer[255];
	if(count > 0){
		sprintf(tabBuffer, "\t");
		i++;
	}
	while(i < count){
		sprintf(tabBuffer, "%s\t", tabBuffer);
		i++;
	}
	return _strdup(tabBuffer);
}

void debug(char *output){
	if(_isDebug == 1)
		printf("\n\t// Debug: %s\n", output);
}
void main(){
	sprintf(className, "myclass");
	yyparse();
}
int getLocalIndex(){
	return localIndex++;
}

int isIntAndFloat(DType val1, DType val2){
		if(val1 == val2 && val1 == int_)
			return int_;
		
		if(val1 == val2 && val1 == float_)
			return float_;			
		if(val1 == float_ && val2 == int_){
			printf("%s conv.r4 // Cast int to double\n", getTabs(tabIndex));
			return float_;			
		}
		if(val1 == int_ && val2 == float_){

			printf("%s stloc _float32 // temp store \n", getTabs(tabIndex));
			printf("%s conv.r4 // Cast int to double\n", getTabs(tabIndex));
			printf("%s ldloc _float32 // load temp \n", getTabs(tabIndex));
			return float_;
		}
		return -1;
}
