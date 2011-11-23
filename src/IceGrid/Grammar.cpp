/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ICE_GRID_HELP = 258,
     ICE_GRID_EXIT = 259,
     ICE_GRID_APPLICATION = 260,
     ICE_GRID_NODE = 261,
     ICE_GRID_SERVER = 262,
     ICE_GRID_ADAPTER = 263,
     ICE_GRID_PING = 264,
     ICE_GRID_LOAD = 265,
     ICE_GRID_ADD = 266,
     ICE_GRID_REMOVE = 267,
     ICE_GRID_LIST = 268,
     ICE_GRID_SHUTDOWN = 269,
     ICE_GRID_STRING = 270,
     ICE_GRID_START = 271,
     ICE_GRID_STOP = 272,
     ICE_GRID_PATCH = 273,
     ICE_GRID_SIGNAL = 274,
     ICE_GRID_STDOUT = 275,
     ICE_GRID_STDERR = 276,
     ICE_GRID_DESCRIBE = 277,
     ICE_GRID_STATE = 278,
     ICE_GRID_PID = 279,
     ICE_GRID_ENDPOINTS = 280,
     ICE_GRID_ACTIVATION = 281,
     ICE_GRID_OBJECT = 282,
     ICE_GRID_FIND = 283,
     ICE_GRID_SHOW = 284,
     ICE_GRID_COPYING = 285,
     ICE_GRID_WARRANTY = 286,
     ICE_GRID_DIFF = 287,
     ICE_GRID_UPDATE = 288,
     ICE_GRID_INSTANTIATE = 289,
     ICE_GRID_TEMPLATE = 290,
     ICE_GRID_SERVICE = 291,
     ICE_GRID_ENABLE = 292,
     ICE_GRID_DISABLE = 293
   };
#endif
#define ICE_GRID_HELP 258
#define ICE_GRID_EXIT 259
#define ICE_GRID_APPLICATION 260
#define ICE_GRID_NODE 261
#define ICE_GRID_SERVER 262
#define ICE_GRID_ADAPTER 263
#define ICE_GRID_PING 264
#define ICE_GRID_LOAD 265
#define ICE_GRID_ADD 266
#define ICE_GRID_REMOVE 267
#define ICE_GRID_LIST 268
#define ICE_GRID_SHUTDOWN 269
#define ICE_GRID_STRING 270
#define ICE_GRID_START 271
#define ICE_GRID_STOP 272
#define ICE_GRID_PATCH 273
#define ICE_GRID_SIGNAL 274
#define ICE_GRID_STDOUT 275
#define ICE_GRID_STDERR 276
#define ICE_GRID_DESCRIBE 277
#define ICE_GRID_STATE 278
#define ICE_GRID_PID 279
#define ICE_GRID_ENDPOINTS 280
#define ICE_GRID_ACTIVATION 281
#define ICE_GRID_OBJECT 282
#define ICE_GRID_FIND 283
#define ICE_GRID_SHOW 284
#define ICE_GRID_COPYING 285
#define ICE_GRID_WARRANTY 286
#define ICE_GRID_DIFF 287
#define ICE_GRID_UPDATE 288
#define ICE_GRID_INSTANTIATE 289
#define ICE_GRID_TEMPLATE 290
#define ICE_GRID_SERVICE 291
#define ICE_GRID_ENABLE 292
#define ICE_GRID_DISABLE 293




/* Copy the first part of user declarations.  */
#line 1 "Grammar.y"


// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IceGrid/Parser.h>

#ifdef _MSC_VER
// I get these warnings from some bison versions:
// warning C4102: 'yyoverflowlab' : unreferenced label
#   pragma warning( disable : 4102 )
// warning C4065: switch statement contains 'default' but no 'case' labels
#   pragma warning( disable : 4065 )
#endif

using namespace std;
using namespace Ice;
using namespace IceGrid;

void
yyerror(const char* s)
{
    parser->invalidCommand(s);
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 197 "Grammar.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
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
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   165

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  6
/* YYNRULES -- Number of rules. */
#define YYNRULES  59
/* YYNRULES -- Number of states. */
#define YYNSTATES  150

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    17,    22,
      27,    32,    37,    42,    47,    53,    59,    65,    69,    74,
      79,    84,    89,    93,    98,   103,   108,   113,   118,   123,
     128,   133,   138,   143,   148,   153,   157,   162,   167,   171,
     176,   181,   186,   191,   196,   199,   203,   207,   211,   215,
     219,   223,   227,   231,   234,   237,   239,   242,   244,   247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      41,     0,    -1,    42,    -1,    -1,    42,    43,    -1,    43,
      -1,     3,    39,    -1,     4,    39,    -1,     5,    11,    45,
      39,    -1,     5,    12,    45,    39,    -1,     5,    32,    45,
      39,    -1,     5,    33,    45,    39,    -1,     5,    22,    45,
      39,    -1,     5,    18,    45,    39,    -1,     7,    35,    22,
      45,    39,    -1,     7,    35,    34,    45,    39,    -1,    36,
      35,    22,    45,    39,    -1,     5,    13,    39,    -1,     6,
      22,    45,    39,    -1,     6,     9,    45,    39,    -1,     6,
      10,    45,    39,    -1,     6,    14,    45,    39,    -1,     6,
      13,    39,    -1,     7,    12,    45,    39,    -1,     7,    22,
      45,    39,    -1,     7,    16,    45,    39,    -1,     7,    17,
      45,    39,    -1,     7,    18,    45,    39,    -1,     7,    19,
      45,    39,    -1,     7,    20,    45,    39,    -1,     7,    21,
      45,    39,    -1,     7,    23,    45,    39,    -1,     7,    24,
      45,    39,    -1,     7,    37,    45,    39,    -1,     7,    38,
      45,    39,    -1,     7,    13,    39,    -1,     8,    25,    45,
      39,    -1,     8,    12,    45,    39,    -1,     8,    13,    39,
      -1,    27,    11,    45,    39,    -1,    27,    12,    45,    39,
      -1,    27,    28,    45,    39,    -1,    27,    13,    45,    39,
      -1,    27,    22,    45,    39,    -1,    14,    39,    -1,    29,
      30,    39,    -1,    29,    31,    39,    -1,     5,    45,    39,
      -1,     7,    45,    39,    -1,     6,    45,    39,    -1,    36,
      45,    39,    -1,    27,    45,    39,    -1,     8,    45,    39,
      -1,    44,    39,    -1,     1,    39,    -1,    39,    -1,    15,
      44,    -1,    15,    -1,    15,    45,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    79,    79,    83,    90,    93,   101,   105,   109,   113,
     117,   121,   125,   129,   133,   137,   141,   145,   149,   153,
     157,   161,   165,   169,   173,   177,   181,   185,   189,   193,
     197,   201,   205,   209,   213,   217,   221,   225,   229,   233,
     237,   241,   245,   249,   253,   257,   261,   265,   276,   287,
     298,   309,   320,   331,   335,   339,   347,   352,   361,   367
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ICE_GRID_HELP", "ICE_GRID_EXIT",
  "ICE_GRID_APPLICATION", "ICE_GRID_NODE", "ICE_GRID_SERVER",
  "ICE_GRID_ADAPTER", "ICE_GRID_PING", "ICE_GRID_LOAD", "ICE_GRID_ADD",
  "ICE_GRID_REMOVE", "ICE_GRID_LIST", "ICE_GRID_SHUTDOWN",
  "ICE_GRID_STRING", "ICE_GRID_START", "ICE_GRID_STOP", "ICE_GRID_PATCH",
  "ICE_GRID_SIGNAL", "ICE_GRID_STDOUT", "ICE_GRID_STDERR",
  "ICE_GRID_DESCRIBE", "ICE_GRID_STATE", "ICE_GRID_PID",
  "ICE_GRID_ENDPOINTS", "ICE_GRID_ACTIVATION", "ICE_GRID_OBJECT",
  "ICE_GRID_FIND", "ICE_GRID_SHOW", "ICE_GRID_COPYING",
  "ICE_GRID_WARRANTY", "ICE_GRID_DIFF", "ICE_GRID_UPDATE",
  "ICE_GRID_INSTANTIATE", "ICE_GRID_TEMPLATE", "ICE_GRID_SERVICE",
  "ICE_GRID_ENABLE", "ICE_GRID_DISABLE", "';'", "$accept", "start",
  "commands", "command", "strings", "optional_strings", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    45
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     2,     4,     4,
       4,     4,     4,     4,     5,     5,     5,     3,     4,     4,
       4,     4,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     4,     4,     3,     4,
       4,     4,     4,     4,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     2,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,    59,    59,    59,    59,     0,    57,
      59,     0,    59,    55,     0,     0,     5,     0,    54,     6,
       7,    59,    59,     0,    59,    59,    59,    59,    59,     0,
      59,    59,     0,    59,    59,     0,    59,     0,    59,    59,
      59,    59,    59,    59,    59,    59,    59,     0,    59,    59,
       0,    59,     0,    59,     0,    44,    56,    59,    59,    59,
      59,    59,     0,     0,     0,     0,     0,     1,     4,    53,
       0,     0,    17,    58,     0,     0,     0,     0,    47,     0,
       0,    22,     0,     0,    49,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    59,     0,     0,
      48,     0,    38,     0,    52,     0,     0,     0,     0,     0,
      51,    45,    46,    59,    50,     8,     9,    13,    12,    10,
      11,    19,    20,    21,    18,    23,    25,    26,    27,    28,
      29,    30,    24,    31,    32,     0,     0,    33,    34,    37,
      36,    39,    40,    42,    43,    41,     0,    14,    15,    16
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    14,    15,    16,    17,    29
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -34
static const short int yypact[] =
{
      57,   -33,   -29,   -28,   112,   137,    98,    70,   -27,    -2,
     126,   -22,   -11,   -34,    14,    73,   -34,   -21,   -34,   -34,
     -34,    12,    12,    -9,    12,    12,    12,    12,    12,    -7,
      12,    12,     3,    12,    12,     6,    12,     8,    12,    12,
      12,    12,    12,    12,    12,    12,    12,   -19,    12,    12,
      10,    12,    11,    12,    20,   -34,   -34,    12,    12,    12,
      12,    12,    27,    28,    29,    47,    31,   -34,   -34,   -34,
      36,    50,   -34,   -34,    51,    55,    58,    59,   -34,    60,
      62,   -34,    64,    65,   -34,    66,   -34,    67,    68,    87,
      89,    90,    92,    93,   101,   103,    12,    12,   104,   110,
     -34,   114,   -34,   116,   -34,   117,   118,   119,   121,   122,
     -34,   -34,   -34,    12,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   123,   124,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   125,   -34,   -34,   -34
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -34,   -34,   -34,   150,    42,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const short int yytable[] =
{
      35,    50,    54,    96,    24,    62,    18,    66,    63,    64,
      19,    20,    55,     9,    67,    97,    70,    71,    69,    73,
      74,    75,    76,    77,    65,    79,    80,    24,    82,    83,
      72,    85,    78,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    81,    98,    99,    84,   101,    86,   103,   100,
     102,    56,   105,   106,   107,   108,   109,    -3,     1,   104,
       2,     3,     4,     5,     6,     7,   110,   111,   112,   113,
     114,     8,     9,    -2,     1,   115,     2,     3,     4,     5,
       6,     7,    51,    52,    10,    24,    11,     8,     9,   116,
     117,   135,   136,    12,   118,    53,    13,   119,   120,   121,
      10,   122,    11,   123,   124,   125,   126,   127,   146,    12,
      36,    37,    13,    24,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    21,    22,    23,   128,    24,   129,   130,
      25,   131,   132,    47,    26,    48,    49,    57,    58,    59,
     133,    24,   134,   137,    27,    28,    30,    31,    60,   138,
      32,    33,    24,   139,    61,   140,   141,   142,   143,    34,
     144,   145,   147,   148,   149,    68
};

static const unsigned char yycheck[] =
{
       5,     6,     7,    22,    15,    10,    39,    12,    30,    31,
      39,    39,    39,    15,     0,    34,    21,    22,    39,    24,
      25,    26,    27,    28,    35,    30,    31,    15,    33,    34,
      39,    36,    39,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    39,    48,    49,    39,    51,    39,    53,    39,
      39,     9,    57,    58,    59,    60,    61,     0,     1,    39,
       3,     4,     5,     6,     7,     8,    39,    39,    39,    22,
      39,    14,    15,     0,     1,    39,     3,     4,     5,     6,
       7,     8,    12,    13,    27,    15,    29,    14,    15,    39,
      39,    96,    97,    36,    39,    25,    39,    39,    39,    39,
      27,    39,    29,    39,    39,    39,    39,    39,   113,    36,
      12,    13,    39,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    11,    12,    13,    39,    15,    39,    39,
      18,    39,    39,    35,    22,    37,    38,    11,    12,    13,
      39,    15,    39,    39,    32,    33,     9,    10,    22,    39,
      13,    14,    15,    39,    28,    39,    39,    39,    39,    22,
      39,    39,    39,    39,    39,    15
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,    14,    15,
      27,    29,    36,    39,    41,    42,    43,    44,    39,    39,
      39,    11,    12,    13,    15,    18,    22,    32,    33,    45,
       9,    10,    13,    14,    22,    45,    12,    13,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    35,    37,    38,
      45,    12,    13,    25,    45,    39,    44,    11,    12,    13,
      22,    28,    45,    30,    31,    35,    45,     0,    43,    39,
      45,    45,    39,    45,    45,    45,    45,    45,    39,    45,
      45,    39,    45,    45,    39,    45,    39,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    22,    34,    45,    45,
      39,    45,    39,    45,    39,    45,    45,    45,    45,    45,
      39,    39,    39,    22,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    45,    45,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    45,    39,    39,    39
};

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
    { 								\
      yyerror ("syntax error: cannot back up");\
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
      yysymprint (stderr, 					\
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
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
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

#endif /* !YYERROR_VERBOSE */



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

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
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
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



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


  yyvsp[0] = yylval;

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
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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
        case 2:
#line 80 "Grammar.y"
    {
;}
    break;

  case 3:
#line 83 "Grammar.y"
    {
;}
    break;

  case 4:
#line 91 "Grammar.y"
    {
;}
    break;

  case 5:
#line 94 "Grammar.y"
    {
;}
    break;

  case 6:
#line 102 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 7:
#line 106 "Grammar.y"
    {
    return 0;
;}
    break;

  case 8:
#line 110 "Grammar.y"
    {
    parser->addApplication((yyvsp[-1]));
;}
    break;

  case 9:
#line 114 "Grammar.y"
    {
    parser->removeApplication((yyvsp[-1]));
;}
    break;

  case 10:
#line 118 "Grammar.y"
    {
    parser->diffApplication((yyvsp[-1]));
;}
    break;

  case 11:
#line 122 "Grammar.y"
    {
    parser->updateApplication((yyvsp[-1]));
;}
    break;

  case 12:
#line 126 "Grammar.y"
    {
    parser->describeApplication((yyvsp[-1]));
;}
    break;

  case 13:
#line 130 "Grammar.y"
    {
    parser->patchApplication((yyvsp[-1]));
;}
    break;

  case 14:
#line 134 "Grammar.y"
    {
    parser->describeServerTemplate((yyvsp[-1]));
;}
    break;

  case 15:
#line 138 "Grammar.y"
    {
    parser->instantiateServerTemplate((yyvsp[-1]));
;}
    break;

  case 16:
#line 142 "Grammar.y"
    {
    parser->describeServiceTemplate((yyvsp[-1]));
;}
    break;

  case 17:
#line 146 "Grammar.y"
    {
    parser->listAllApplications();
;}
    break;

  case 18:
#line 150 "Grammar.y"
    {
    parser->describeNode((yyvsp[-1]));
;}
    break;

  case 19:
#line 154 "Grammar.y"
    {
    parser->pingNode((yyvsp[-1]));
;}
    break;

  case 20:
#line 158 "Grammar.y"
    {
    parser->printLoadNode((yyvsp[-1]));
;}
    break;

  case 21:
#line 162 "Grammar.y"
    {
    parser->shutdownNode((yyvsp[-1]));
;}
    break;

  case 22:
#line 166 "Grammar.y"
    {
    parser->listAllNodes();
;}
    break;

  case 23:
#line 170 "Grammar.y"
    {
    parser->removeServer((yyvsp[-1]));
;}
    break;

  case 24:
#line 174 "Grammar.y"
    {
    parser->describeServer((yyvsp[-1]));
;}
    break;

  case 25:
#line 178 "Grammar.y"
    {
    parser->startServer((yyvsp[-1]));
;}
    break;

  case 26:
#line 182 "Grammar.y"
    {
    parser->stopServer((yyvsp[-1]));
;}
    break;

  case 27:
#line 186 "Grammar.y"
    {
    parser->patchServer((yyvsp[-1]));
;}
    break;

  case 28:
#line 190 "Grammar.y"
    {
    parser->signalServer((yyvsp[-1]));
;}
    break;

  case 29:
#line 194 "Grammar.y"
    {
    parser->writeMessage((yyvsp[-1]), 1);
;}
    break;

  case 30:
#line 198 "Grammar.y"
    {
    parser->writeMessage((yyvsp[-1]), 2);
;}
    break;

  case 31:
#line 202 "Grammar.y"
    {
    parser->stateServer((yyvsp[-1]));
;}
    break;

  case 32:
#line 206 "Grammar.y"
    {
    parser->pidServer((yyvsp[-1]));
;}
    break;

  case 33:
#line 210 "Grammar.y"
    {
    parser->enableServer((yyvsp[-1]), true);
;}
    break;

  case 34:
#line 214 "Grammar.y"
    {
    parser->enableServer((yyvsp[-1]), false);
;}
    break;

  case 35:
#line 218 "Grammar.y"
    {
    parser->listAllServers();
;}
    break;

  case 36:
#line 222 "Grammar.y"
    {
    parser->endpointsAdapter((yyvsp[-1]));
;}
    break;

  case 37:
#line 226 "Grammar.y"
    {
    parser->removeAdapter((yyvsp[-1]));
;}
    break;

  case 38:
#line 230 "Grammar.y"
    {
    parser->listAllAdapters();
;}
    break;

  case 39:
#line 234 "Grammar.y"
    {
    parser->addObject((yyvsp[-1]));
;}
    break;

  case 40:
#line 238 "Grammar.y"
    {
    parser->removeObject((yyvsp[-1]));
;}
    break;

  case 41:
#line 242 "Grammar.y"
    {
    parser->findObject((yyvsp[-1]));
;}
    break;

  case 42:
#line 246 "Grammar.y"
    {
    parser->listObject((yyvsp[-1]));
;}
    break;

  case 43:
#line 250 "Grammar.y"
    {
    parser->describeObject((yyvsp[-1]));
;}
    break;

  case 44:
#line 254 "Grammar.y"
    {
    parser->shutdown();
;}
    break;

  case 45:
#line 258 "Grammar.y"
    {
    parser->showCopying();
;}
    break;

  case 46:
#line 262 "Grammar.y"
    {
    parser->showWarranty();
;}
    break;

  case 47:
#line 266 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `application'");
    }
    else
    {
	parser->invalidCommand("invalid command: `application " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 48:
#line 277 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `server'");
    }
    else
    {
	parser->invalidCommand("invalid command: `server " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 49:
#line 288 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `node'");
    }
    else
    {
	parser->invalidCommand("invalid command: `node " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 50:
#line 299 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `service'");
    }
    else
    {
	parser->invalidCommand("invalid command: `service " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 51:
#line 310 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `object'");
    }
    else
    {
	parser->invalidCommand("invalid command: `object " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 52:
#line 321 "Grammar.y"
    {
    if((yyvsp[-1]).empty())
    {
	parser->invalidCommand("invalid command `adapter'");
    }
    else
    {
	parser->invalidCommand("invalid command: `adapter " + (yyvsp[-1]).front() + "'");
    }
;}
    break;

  case 53:
#line 332 "Grammar.y"
    {
    parser->invalidCommand("invalid command `" + (yyvsp[-1]).front() + "'");
;}
    break;

  case 54:
#line 336 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 55:
#line 340 "Grammar.y"
    {
;}
    break;

  case 56:
#line 348 "Grammar.y"
    {
    (yyval) = (yyvsp[0]);
    (yyval).push_front((yyvsp[-1]).front());
;}
    break;

  case 57:
#line 353 "Grammar.y"
    {
    (yyval) = (yyvsp[0]);
;}
    break;

  case 58:
#line 362 "Grammar.y"
    {
    (yyval) = (yyvsp[0]);
    (yyval).push_front((yyvsp[-1]).front());
;}
    break;

  case 59:
#line 367 "Grammar.y"
    {
    (yyval) = YYSTYPE()
;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 1672 "Grammar.tab.c"

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
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 372 "Grammar.y"


