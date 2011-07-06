/* A Bison parser, made from sql.bison
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse SMADparse
#define yylex SMADlex
#define yyerror SMADerror
#define yylval SMADlval
#define yychar SMADchar
#define yydebug SMADdebug
#define yynerrs SMADnerrs
# define	NUM	257
# define	STRING	258
# define	FUNC	259
# define	LIT_STR	260
# define	LIT_STR_PARSE	261
# define	SELECT	262
# define	INSERT	263
# define	UPDATE	264
# define	DELETE	265
# define	CREATE	266
# define	TABLE	267
# define	AND	268
# define	NOT	269
# define	OR	270
# define	FROM	271
# define	WHERE	272
# define	INTO	273
# define	VALUES	274
# define	SET	275
# define	ORDER	276
# define	BY	277
# define	AS	278
# define	IN	279
# define	NULLX	280
# define	LIKE	281
# define	IS	282
# define	SHUTDOWN	283
# define	ALL	284
# define	DISTINCT	285
# define	INT	286
# define	DOUBLE	287
# define	CHAR	288
# define	TEXT	289
# define	ASC	290
# define	DESC	291
# define	GROUP	292
# define	LIMIT	293
# define	BETWEEN	294
# define	TOK_NEQUAL	295
# define	TOK_GE	296
# define	TOK_LE	297
# define	TOK_EXIT	298
# define	NEG	299
# define	UMINUS	300

#line 1 "sql.bison"

// developer: faisal
//
// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal
//
// Provides the SQL Grammar

// GRAMMAR PARSER (developer: Faisal@Nasim.org)
// $Id: sql.bison,v 1.1 2003/07/22 00:18:53 faisal Exp faisal $

#include <Base.hpp>
#include <Field.hpp>
#include <Table.h>
#include <Database.h>
#include <Statement.hpp>
#include <Function.hpp>
#include <Column.hpp>
#include <Connector.hpp>

extern Statement* st;
extern DataBase* db;

#line 30 "sql.bison"
#ifndef YYSTYPE
typedef union {
	double					val;
	char				*	str;
	Table				*	tableptr;
	Column				*	colptr;
	Function			*	funcptr;
	TreeExpr			*	exprtree;
	SQLassign			*	assignexpr;
	SQLexpr				*	searchexpr;
	SQLsearch			*	searchptr;
	SQLnewfield			*	fielddef;
	SQLList<Column>		*	fieldlist;
	SQLList<Table*>		*	tablelist;
	SQLList<SQLsearch>	*	searchlist;
	SQLList<TreeExpr*>	*	exprlist;
	SQLList<SQLassign*>	*	assignlist;
	SQLList<SQLnewfield*>*	tabledef;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		160
#define	YYFLAG		-32768
#define	YYNTBASE	62

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 300 ? yytranslate[x] : 97)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    56,    49,     2,
      59,    60,    54,    52,    45,    53,    61,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    46,    47,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    50,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    57,
      58
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     8,    10,    12,    14,    16,
      18,    20,    22,    24,    26,    28,    29,    31,    33,    43,
      54,    60,    67,    74,    79,    81,    82,    85,    86,    89,
      90,    94,    96,   100,   103,   106,   107,   109,   111,   112,
     116,   118,   120,   124,   126,   130,   133,   135,   137,   139,
     141,   142,   146,   150,   155,   160,   164,   166,   170,   174,
     178,   182,   186,   190,   194,   200,   204,   208,   212,   216,
     220,   223,   227,   229,   231,   233,   235,   237,   241,   243,
     247,   251,   253,   257,   259,   263,   268,   270,   272,   274
};
static const short yyrhs[] =
{
      63,     0,     0,    63,    64,     0,    65,     0,    66,     0,
      68,     0,    69,     0,    70,     0,    71,     0,    72,     0,
      73,     0,    44,     0,    89,     0,    54,     0,     0,    30,
       0,    31,     0,     8,    67,    89,    17,    82,    74,    76,
      80,    75,     0,     9,    19,    81,    59,    89,    60,    20,
      59,    89,    60,     0,     9,    19,    81,    21,    90,     0,
      10,    81,    21,    90,    18,    86,     0,    12,    13,     4,
      59,    83,    60,     0,    11,    17,    81,    74,     0,    29,
       0,     0,    18,    86,     0,     0,    39,     3,     0,     0,
      22,    23,    77,     0,    78,     0,    77,    45,    78,     0,
      32,    79,     0,    92,    79,     0,     0,    36,     0,    37,
       0,     0,    38,    23,    93,     0,    95,     0,    81,     0,
      82,    45,    81,     0,    84,     0,    83,    45,    84,     0,
       4,    85,     0,    32,     0,    33,     0,    34,     0,    35,
       0,     0,    86,    14,    86,     0,    86,    16,    86,     0,
      86,    14,    15,    86,     0,    86,    16,    15,    86,     0,
      59,    86,    60,     0,    87,     0,    88,    46,    88,     0,
      88,    41,    88,     0,    88,    47,    88,     0,    88,    48,
      88,     0,    88,    42,    88,     0,    88,    43,    88,     0,
      88,    25,    89,     0,    88,    40,    88,    14,    88,     0,
      88,    52,    88,     0,    88,    53,    88,     0,    88,    54,
      88,     0,    88,    55,    88,     0,    88,    56,    88,     0,
      53,    88,     0,    59,    88,    60,     0,     3,     0,    96,
       0,    92,     0,    94,     0,    88,     0,    89,    45,    88,
       0,    91,     0,    90,    45,    91,     0,    92,    46,    88,
       0,     4,     0,     4,    61,     4,     0,    92,     0,    93,
      45,    92,     0,     4,    59,    89,    60,     0,     4,     0,
      96,     0,     7,     0,     6,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    86,    90,    91,    94,    96,   100,   102,   103,   104,
     105,   108,   110,   113,   115,   118,   120,   121,   125,   142,
     146,   152,   158,   168,   176,   180,   182,   185,   186,   189,
     190,   193,   195,   198,   200,   203,   205,   206,   209,   210,
     213,   217,   219,   222,   224,   227,   231,   233,   234,   235,
     238,   240,   241,   242,   243,   244,   245,   252,   254,   255,
     256,   257,   258,   259,   260,   263,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   277,   279,   282,   284,
     287,   291,   293,   296,   298,   301,   305,   307,   310,   312
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUM", "STRING", "FUNC", "LIT_STR", 
  "LIT_STR_PARSE", "SELECT", "INSERT", "UPDATE", "DELETE", "CREATE", 
  "TABLE", "AND", "NOT", "OR", "FROM", "WHERE", "INTO", "VALUES", "SET", 
  "ORDER", "BY", "AS", "IN", "NULLX", "LIKE", "IS", "SHUTDOWN", "ALL", 
  "DISTINCT", "INT", "DOUBLE", "CHAR", "TEXT", "ASC", "DESC", "GROUP", 
  "LIMIT", "BETWEEN", "TOK_NEQUAL", "TOK_GE", "TOK_LE", "TOK_EXIT", "','", 
  "'='", "'>'", "'<'", "'&'", "'|'", "'^'", "'+'", "'-'", "'*'", "'/'", 
  "'%'", "NEG", "UMINUS", "'('", "')'", "'.'", "language", 
  "main_statements", "statement", "SQLstatement", "internal_function", 
  "opt_all_distinct", "select_statement", "insert_statement", 
  "update_statement", "create_statement", "delete_statement", 
  "shutdown_statement", "opt_where_clause", "opt_limit_clause", 
  "opt_order_by_clause", "ordering_spec_commalist", "ordering_spec", 
  "opt_asc_desc", "opt_group_by_clause", "table_name_add", "tables_list", 
  "table_definition", "field_definition", "field_type", 
  "search_conditions", "search_expr", "scalar_exp", 
  "scalar_exp_commalist", "scalar_exp_assignlist", "scalar_exp_assign", 
  "column_ref", "column_ref_commalist", "function_ref", "exp_literal", 
  "str", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    66,    66,    97,    97,    67,    67,    67,    68,    69,
      69,    70,    71,    72,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    79,    80,    80,
      81,    82,    82,    83,    83,    84,    85,    85,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    90,    90,
      91,    92,    92,    93,    93,    94,    95,    95,    96,    96
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     9,    10,
       5,     6,     6,     4,     1,     0,     2,     0,     2,     0,
       3,     1,     3,     2,     2,     0,     1,     1,     0,     3,
       1,     1,     3,     1,     3,     2,     1,     1,     1,     1,
       0,     3,     3,     4,     4,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     5,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     1,     3,     1,     3,
       3,     1,     3,     1,     3,     4,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       2,     1,    15,     0,     0,     0,     0,    24,    12,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    16,    17,
       0,     0,    86,    89,    88,     0,    40,    87,     0,     0,
      72,    81,     0,     0,    76,     0,    74,    75,    73,     0,
       0,    25,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,     0,    78,     0,
      50,    23,     0,     0,    82,    71,    65,    66,    67,    68,
      69,    41,    25,    77,    20,     0,    50,     0,     0,    50,
      26,    56,     0,     0,     0,    43,    85,     0,    29,     0,
      21,    79,    80,     0,     0,    50,    50,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    47,    48,    49,    45,
       0,    22,    42,     0,    38,     0,    55,    50,    51,    50,
      52,    63,     0,    58,    61,    62,    57,    59,    60,    44,
       0,     0,    27,     0,    53,    54,     0,    35,    30,    31,
      35,     0,     0,    18,     0,    64,    36,    37,    33,     0,
      34,    83,    39,    28,    19,    32,     0,    84,     0,     0,
       0
};

static const short yydefgoto[] =
{
     158,     1,     9,    10,    11,    20,    12,    13,    14,    15,
      16,    17,    61,   143,   114,   138,   139,   148,   132,    25,
      72,    84,    85,   109,    80,    81,    82,    35,    57,    58,
      36,   152,    37,    26,    38
};

static const short yypact[] =
{
  -32768,   111,    43,   -16,    60,     3,    24,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      45,    60,-32768,-32768,-32768,    21,-32768,-32768,    60,    58,
  -32768,    29,    45,    45,   143,     8,-32768,-32768,-32768,     1,
      83,    78,    42,    45,    99,-32768,   134,    45,    45,    45,
      45,    45,    60,    45,    83,    45,    48,   -13,-32768,    66,
      65,-32768,   107,   -24,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,     0,   143,    69,   -21,    65,    83,    45,    65,
      81,-32768,   129,   109,    16,-32768,-32768,    60,    93,   106,
      81,-32768,   143,   -10,   105,     4,    40,    45,    45,    45,
      45,    45,    45,    45,    45,-32768,-32768,-32768,-32768,-32768,
     107,-32768,-32768,   102,    90,    72,-32768,    65,-32768,    65,
  -32768,    92,    80,   143,   143,   143,   143,   143,   143,-32768,
      22,   115,   100,    45,-32768,-32768,    45,    71,   104,-32768,
      71,    83,   147,-32768,    25,   143,-32768,-32768,-32768,    22,
  -32768,-32768,   117,-32768,-32768,-32768,    83,-32768,   156,   163,
  -32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    94,-32768,-32768,-32768,    15,    27,-32768,   -12,
  -32768,-32768,    63,-32768,    10,-32768,   -20,   -41,   114,    97,
     -39,-32768,-32768,-32768,    13
};


#define	YYLAST		199


static const short yytable[] =
{
      34,    59,    63,    21,    95,    76,    96,    30,    31,    39,
      23,    24,    45,    46,    75,    59,    41,    27,    60,   117,
      28,    53,    54,    34,    53,    52,    56,    66,    67,    68,
      69,    70,    77,    73,    27,    34,    86,    29,    59,    89,
      71,    27,    40,    30,    31,    87,    23,    24,    30,    31,
     116,    23,    24,    53,   137,   119,   121,    32,    92,    94,
      55,   110,    42,    79,    22,    27,    23,    24,    30,    31,
      53,    23,    24,    18,    19,   112,   111,    34,   122,   123,
     124,   125,   126,   127,   128,   154,    90,    56,    43,    93,
      44,   140,   144,    32,   136,    95,    60,    96,    32,    79,
      27,    62,   151,    64,    33,   118,   120,   146,   147,    44,
     140,    83,    78,    34,    77,   113,   145,   157,    32,     2,
       3,     4,     5,     6,    79,   130,   115,   134,   131,   135,
      97,   133,    47,    48,    49,    50,    51,    53,   141,   142,
       7,   105,   106,   107,   108,    98,    99,   100,   101,   149,
     153,   102,   103,   104,    97,     8,   159,    47,    48,    49,
      50,    51,   156,   160,   155,    65,    88,   150,    74,    98,
      99,   100,   101,   129,    91,   102,   103,   104,     0,     0,
       0,    47,    48,    49,    50,    51,    47,    48,    49,    50,
      51,     0,     0,     0,    65,    47,    48,    49,    50,    51
};

static const short yycheck[] =
{
      20,    40,    43,    19,    14,    18,    16,     3,     4,    21,
       6,     7,    32,    33,    55,    54,    28,     4,    18,    15,
      17,    45,    21,    43,    45,    17,     4,    47,    48,    49,
      50,    51,    45,    53,    21,    55,    60,    13,    77,    60,
      52,    28,    21,     3,     4,    45,     6,     7,     3,     4,
      60,     6,     7,    45,    32,    15,    97,    53,    78,    79,
      59,    45,     4,    59,     4,    52,     6,     7,     3,     4,
      45,     6,     7,    30,    31,    87,    60,    97,    98,    99,
     100,   101,   102,   103,   104,    60,    76,     4,    59,    79,
      61,   130,   133,    53,    14,    14,    18,    16,    53,    59,
      87,    59,   141,     4,    59,    95,    96,    36,    37,    61,
     149,     4,    46,   133,    45,    22,   136,   156,    53,     8,
       9,    10,    11,    12,    59,    23,    20,   117,    38,   119,
      25,    59,    52,    53,    54,    55,    56,    45,    23,    39,
      29,    32,    33,    34,    35,    40,    41,    42,    43,    45,
       3,    46,    47,    48,    25,    44,     0,    52,    53,    54,
      55,    56,    45,     0,   149,    60,    72,   140,    54,    40,
      41,    42,    43,   110,    77,    46,    47,    48,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    60,    52,    53,    54,    55,    56
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

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
  register const char *yys = yystr;

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
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 11:
#line 109 "sql.bison"
{ exit ( (int) 0 ); ;
    break;}
case 12:
#line 110 "sql.bison"
{ exit ( (int) 0 ); ;
    break;}
case 13:
#line 114 "sql.bison"
{;
    break;}
case 18:
#line 132 "sql.bison"
{
		st->tables = yyvsp[-4].tablelist;
		st->fields = yyvsp[-6].exprlist;
		//st.search=$6;

		//( Table* table , SQLList <SQLexpr*>* lst , SQLList<Column*>* fields , SQLList<SQLsearch*>* search );
		SMADdbConnector::SelectRecord ( st->tables->at(0) , yyvsp[-6].exprlist , st->fieldlist , st->search , st->output );
	;
    break;}
case 19:
#line 144 "sql.bison"
{ /* SMADdbConnector::InsertRecord ()  */ ;
    break;}
case 20:
#line 147 "sql.bison"
{
		SMADdbConnector::InsertRecord ( yyvsp[-2].tableptr , yyvsp[0].assignlist );
	;
    break;}
case 22:
#line 160 "sql.bison"
{
		if ( SMADdbConnector::CreateTable ( db , yyvsp[-3].str , yyvsp[-1].tabledef ) )
		{
			cerr << "SERVER> TABLE ALREADY EXISTED... NOT CREATED\n";
		}
	;
    break;}
case 23:
#line 171 "sql.bison"
{
		SMADdbConnector::DeleteRecord ( yyvsp[-1].tableptr , st->search )
	;
    break;}
case 24:
#line 177 "sql.bison"
{;
    break;}
case 25:
#line 181 "sql.bison"
{yyval.searchlist=NULL;
    break;}
case 26:
#line 182 "sql.bison"
{ yyval.searchlist = yyvsp[0].searchlist; ;
    break;}
case 28:
#line 186 "sql.bison"
{;
    break;}
case 33:
#line 199 "sql.bison"
{;
    break;}
case 34:
#line 200 "sql.bison"
{;
    break;}
case 40:
#line 214 "sql.bison"
{ yyval.tableptr = db->GetTable ( yyvsp[0].str ); ;
    break;}
case 41:
#line 218 "sql.bison"
{ yyval.tablelist = new SQLList<Table*>; yyval.tablelist->push (yyvsp[0].tableptr); ;
    break;}
case 42:
#line 219 "sql.bison"
{ yyval.tablelist->push (yyvsp[0].tableptr); ;
    break;}
case 43:
#line 223 "sql.bison"
{ yyval.tabledef = new SQLList<SQLnewfield*>; yyval.tabledef->push (yyvsp[0].fielddef); ;
    break;}
case 44:
#line 224 "sql.bison"
{ yyval.tabledef->push ( yyvsp[0].fielddef ); ;
    break;}
case 45:
#line 228 "sql.bison"
{ yyval.fielddef = new SQLnewfield ( static_cast <int> (yyvsp[0].val) , yyvsp[-1].str ); ;
    break;}
case 46:
#line 232 "sql.bison"
{ yyval.val = TYPE_INTEGER;	;
    break;}
case 47:
#line 233 "sql.bison"
{ yyval.val = TYPE_DOUBLE;		;
    break;}
case 48:
#line 234 "sql.bison"
{ yyval.val = TYPE_SMALLCHAR;	;
    break;}
case 49:
#line 235 "sql.bison"
{ yyval.val = TYPE_TEXT;		;
    break;}
case 50:
#line 239 "sql.bison"
{;
    break;}
case 51:
#line 240 "sql.bison"
{ st->search->push (new SQLsearch(1,0,0)); ;
    break;}
case 52:
#line 241 "sql.bison"
{ st->search->push (new SQLsearch(2,0,0)); ;
    break;}
case 53:
#line 242 "sql.bison"
{ st->search->push (new SQLsearch(3,0,0)); ;
    break;}
case 54:
#line 243 "sql.bison"
{ st->search->push (new SQLsearch(4,0,0)); ;
    break;}
case 55:
#line 244 "sql.bison"
{ yyval.searchlist = yyvsp[-1].searchlist; ;
    break;}
case 56:
#line 245 "sql.bison"
{
		//$$ = new SQLList<SQLsearch*>;
		yyvsp[0].searchptr->type = 0;
		st->search->push (yyvsp[0].searchptr);
	;
    break;}
case 57:
#line 253 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'='); ;
    break;}
case 58:
#line 254 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'!'); ;
    break;}
case 59:
#line 255 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'>'); ;
    break;}
case 60:
#line 256 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'<'); ;
    break;}
case 61:
#line 257 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'G'); ;
    break;}
case 62:
#line 258 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprtree,'L'); ;
    break;}
case 63:
#line 259 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-2].exprtree,yyvsp[0].exprlist,'I'); ;
    break;}
case 64:
#line 260 "sql.bison"
{ yyval.searchptr = new SQLsearch (0,yyvsp[-4].exprtree,yyvsp[-2].exprtree,'B'); ;
    break;}
case 65:
#line 264 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'+') , yyvsp[-2].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 66:
#line 265 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'-') , yyvsp[-2].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 67:
#line 266 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'*') , yyvsp[-2].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 68:
#line 267 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'/') , yyvsp[-2].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 69:
#line 268 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'%') , yyvsp[-2].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 70:
#line 269 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (1,0,'_') , yyvsp[0].exprtree , yyvsp[0].exprtree ); ;
    break;}
case 71:
#line 270 "sql.bison"
{ yyval.exprtree = yyvsp[-1].exprtree; ;
    break;}
case 72:
#line 271 "sql.bison"
{ yyval.exprtree = new TreeExpr ( new SQLexpr (0, (int) yyvsp[0].val) ); ;
    break;}
case 73:
#line 272 "sql.bison"
{ SQLexpr* e = new SQLexpr(); e->type=0; e->subtype=2; e->ptr=yyvsp[0].str; yyval.exprtree = new TreeExpr (e); ;
    break;}
case 74:
#line 273 "sql.bison"
{ SQLexpr* e = new SQLexpr (2,10); e->ptr = yyvsp[0].colptr; yyval.exprtree = new TreeExpr (e); ;
    break;}
case 75:
#line 274 "sql.bison"
{ SQLexpr* e = new SQLexpr (3,10); e->ptr = yyvsp[0].funcptr; yyval.exprtree = new TreeExpr (e); ;
    break;}
case 76:
#line 278 "sql.bison"
{ yyval.exprlist = new SQLList<TreeExpr*>; yyval.exprlist->push (yyvsp[0].exprtree); ;
    break;}
case 77:
#line 279 "sql.bison"
{ yyval.exprlist->push (yyvsp[0].exprtree); ;
    break;}
case 78:
#line 283 "sql.bison"
{ yyval.assignlist = new SQLList<SQLassign*>; yyval.assignlist->push (yyvsp[0].assignexpr); ;
    break;}
case 79:
#line 284 "sql.bison"
{ yyval.assignlist->push (yyvsp[0].assignexpr); ;
    break;}
case 80:
#line 288 "sql.bison"
{ yyval.assignexpr = new SQLassign ( yyvsp[-2].colptr , yyvsp[0].exprtree ); ;
    break;}
case 81:
#line 292 "sql.bison"
{ Column* C = new Column (db,NULL,yyvsp[0].str); st->fieldlist->push(C); yyval.colptr = C; ;
    break;}
case 82:
#line 293 "sql.bison"
{ Column* C = new Column (db,db->GetTable (yyvsp[-2].str),yyvsp[0].str); st->fieldlist->push(C); yyval.colptr = C; ;
    break;}
case 83:
#line 297 "sql.bison"
{;
    break;}
case 84:
#line 298 "sql.bison"
{;
    break;}
case 85:
#line 302 "sql.bison"
{ yyval.funcptr = new Function(yyvsp[-3].str,yyvsp[-1].exprlist); ;
    break;}
case 88:
#line 311 "sql.bison"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 89:
#line 312 "sql.bison"
{ yyval.str = yyvsp[0].str; ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 315 "sql.bison"

