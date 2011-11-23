/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
     ICE_GRID_REGISTRY = 262,
     ICE_GRID_SERVER = 263,
     ICE_GRID_ADAPTER = 264,
     ICE_GRID_PING = 265,
     ICE_GRID_LOAD = 266,
     ICE_GRID_ADD = 267,
     ICE_GRID_REMOVE = 268,
     ICE_GRID_LIST = 269,
     ICE_GRID_SHUTDOWN = 270,
     ICE_GRID_STRING = 271,
     ICE_GRID_START = 272,
     ICE_GRID_STOP = 273,
     ICE_GRID_PATCH = 274,
     ICE_GRID_SIGNAL = 275,
     ICE_GRID_STDOUT = 276,
     ICE_GRID_STDERR = 277,
     ICE_GRID_DESCRIBE = 278,
     ICE_GRID_STATE = 279,
     ICE_GRID_PID = 280,
     ICE_GRID_ENDPOINTS = 281,
     ICE_GRID_ACTIVATION = 282,
     ICE_GRID_OBJECT = 283,
     ICE_GRID_FIND = 284,
     ICE_GRID_SHOW = 285,
     ICE_GRID_COPYING = 286,
     ICE_GRID_WARRANTY = 287,
     ICE_GRID_DIFF = 288,
     ICE_GRID_UPDATE = 289,
     ICE_GRID_INSTANTIATE = 290,
     ICE_GRID_TEMPLATE = 291,
     ICE_GRID_SERVICE = 292,
     ICE_GRID_ENABLE = 293,
     ICE_GRID_DISABLE = 294
   };
#endif
#define ICE_GRID_HELP 258
#define ICE_GRID_EXIT 259
#define ICE_GRID_APPLICATION 260
#define ICE_GRID_NODE 261
#define ICE_GRID_REGISTRY 262
#define ICE_GRID_SERVER 263
#define ICE_GRID_ADAPTER 264
#define ICE_GRID_PING 265
#define ICE_GRID_LOAD 266
#define ICE_GRID_ADD 267
#define ICE_GRID_REMOVE 268
#define ICE_GRID_LIST 269
#define ICE_GRID_SHUTDOWN 270
#define ICE_GRID_STRING 271
#define ICE_GRID_START 272
#define ICE_GRID_STOP 273
#define ICE_GRID_PATCH 274
#define ICE_GRID_SIGNAL 275
#define ICE_GRID_STDOUT 276
#define ICE_GRID_STDERR 277
#define ICE_GRID_DESCRIBE 278
#define ICE_GRID_STATE 279
#define ICE_GRID_PID 280
#define ICE_GRID_ENDPOINTS 281
#define ICE_GRID_ACTIVATION 282
#define ICE_GRID_OBJECT 283
#define ICE_GRID_FIND 284
#define ICE_GRID_SHOW 285
#define ICE_GRID_COPYING 286
#define ICE_GRID_WARRANTY 287
#define ICE_GRID_DIFF 288
#define ICE_GRID_UPDATE 289
#define ICE_GRID_INSTANTIATE 290
#define ICE_GRID_TEMPLATE 291
#define ICE_GRID_SERVICE 292
#define ICE_GRID_ENABLE 293
#define ICE_GRID_DISABLE 294




/* Copy the first part of user declarations.  */
#line 1 "Grammar.y"


// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
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


/* Line 214 of yacc.c.  */
#line 199 "Grammar.tab.c"

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
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
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
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   339

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  8
/* YYNRULES -- Number of rules. */
#define YYNRULES  123
/* YYNRULES -- Number of states. */
#define YYNSTATES  285

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     6,    10,    13,    14,    17,    21,
      25,    29,    33,    37,    41,    46,    51,    55,    59,    63,
      67,    71,    75,    80,    85,    88,    93,    98,   103,   108,
     113,   118,   123,   128,   133,   138,   143,   148,   154,   160,
     166,   172,   178,   184,   188,   193,   198,   203,   208,   213,
     218,   223,   228,   232,   237,   242,   247,   252,   257,   262,
     267,   272,   276,   281,   286,   291,   296,   301,   306,   311,
     316,   321,   326,   331,   336,   341,   346,   351,   356,   361,
     366,   371,   376,   381,   386,   391,   396,   401,   406,   410,
     415,   420,   425,   430,   435,   440,   444,   449,   454,   459,
     464,   469,   474,   479,   484,   489,   493,   497,   501,   505,
     509,   513,   517,   521,   525,   528,   531,   533,   536,   539,
     542,   545,   547,   550
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      42,     0,    -1,    43,    -1,    -1,    43,    44,    45,    -1,
      44,    45,    -1,    -1,     3,    40,    -1,     3,     5,    40,
      -1,     3,     6,    40,    -1,     3,     7,    40,    -1,     3,
       8,    40,    -1,     3,     9,    40,    -1,     3,    28,    40,
      -1,     3,     8,    36,    40,    -1,     3,    37,    36,    40,
      -1,     5,     3,    40,    -1,     6,     3,    40,    -1,     7,
       3,    40,    -1,     8,     3,    40,    -1,     9,     3,    40,
      -1,    28,     3,    40,    -1,     8,    36,     3,    40,    -1,
      37,    36,     3,    40,    -1,     4,    40,    -1,     5,    12,
      48,    40,    -1,     5,    12,     3,    40,    -1,     5,    13,
      48,    40,    -1,     5,    13,     3,    40,    -1,     5,    33,
      48,    40,    -1,     5,    33,     3,    40,    -1,     5,    34,
      48,    40,    -1,     5,    34,     3,    40,    -1,     5,    23,
      48,    40,    -1,     5,    23,     3,    40,    -1,     5,    19,
      48,    40,    -1,     5,    19,     3,    40,    -1,     8,    36,
      23,    48,    40,    -1,     8,    36,    23,     3,    40,    -1,
       8,    36,    35,    48,    40,    -1,     8,    36,    35,     3,
      40,    -1,    37,    36,    23,    48,    40,    -1,    37,    36,
      23,     3,    40,    -1,     5,    14,    40,    -1,     6,    23,
      48,    40,    -1,     6,    23,     3,    40,    -1,     6,    10,
      48,    40,    -1,     6,    10,     3,    40,    -1,     6,    11,
      48,    40,    -1,     6,    11,     3,    40,    -1,     6,    15,
      48,    40,    -1,     6,    15,     3,    40,    -1,     6,    14,
      40,    -1,     6,    30,    46,    40,    -1,     6,    30,     3,
      40,    -1,     7,    23,    48,    40,    -1,     7,    23,     3,
      40,    -1,     7,    10,    48,    40,    -1,     7,    10,     3,
      40,    -1,     7,    15,    48,    40,    -1,     7,    15,     3,
      40,    -1,     7,    14,    40,    -1,     7,    30,    46,    40,
      -1,     7,    30,     3,    40,    -1,     8,    13,    48,    40,
      -1,     8,    13,     3,    40,    -1,     8,    23,    48,    40,
      -1,     8,    23,     3,    40,    -1,     8,    17,    48,    40,
      -1,     8,    17,     3,    40,    -1,     8,    18,    48,    40,
      -1,     8,    18,     3,    40,    -1,     8,    19,    48,    40,
      -1,     8,    19,     3,    40,    -1,     8,    20,    48,    40,
      -1,     8,    20,     3,    40,    -1,     8,    21,    48,    40,
      -1,     8,    21,     3,    40,    -1,     8,    22,    48,    40,
      -1,     8,    22,     3,    40,    -1,     8,    24,    48,    40,
      -1,     8,    24,     3,    40,    -1,     8,    25,    48,    40,
      -1,     8,    25,     3,    40,    -1,     8,    38,    48,    40,
      -1,     8,    38,     3,    40,    -1,     8,    39,    48,    40,
      -1,     8,    39,     3,    40,    -1,     8,    14,    40,    -1,
       8,    30,    46,    40,    -1,     8,    30,     3,    40,    -1,
       9,    26,    48,    40,    -1,     9,    26,     3,    40,    -1,
       9,    13,    48,    40,    -1,     9,    13,     3,    40,    -1,
       9,    14,    40,    -1,    28,    12,    48,    40,    -1,    28,
      12,     3,    40,    -1,    28,    13,    48,    40,    -1,    28,
      13,     3,    40,    -1,    28,    29,    48,    40,    -1,    28,
      29,     3,    40,    -1,    28,    14,    48,    40,    -1,    28,
      23,    48,    40,    -1,    28,    23,     3,    40,    -1,    30,
      31,    40,    -1,    30,    32,    40,    -1,     5,    48,    40,
      -1,     8,    48,    40,    -1,     6,    48,    40,    -1,     7,
      48,    40,    -1,    37,    48,    40,    -1,    28,    48,    40,
      -1,     9,    48,    40,    -1,    47,    40,    -1,     1,    40,
      -1,    40,    -1,    16,    47,    -1,    47,    22,    -1,    47,
      21,    -1,    16,    47,    -1,    16,    -1,    16,    48,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    80,    80,    84,    91,    94,   101,   109,   113,   117,
     121,   125,   129,   133,   137,   141,   145,   149,   153,   157,
     161,   165,   169,   173,   177,   181,   185,   189,   193,   197,
     201,   205,   209,   213,   217,   221,   225,   229,   233,   237,
     241,   245,   249,   253,   257,   261,   265,   269,   273,   277,
     281,   285,   289,   293,   297,   301,   305,   309,   313,   317,
     321,   325,   329,   333,   337,   341,   345,   349,   353,   357,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     401,   405,   409,   413,   417,   421,   425,   429,   433,   437,
     441,   445,   449,   453,   457,   461,   465,   469,   473,   477,
     481,   485,   489,   493,   497,   501,   505,   509,   522,   535,
     548,   561,   572,   585,   598,   603,   607,   616,   621,   626,
     636,   641,   650,   656
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ICE_GRID_HELP", "ICE_GRID_EXIT",
  "ICE_GRID_APPLICATION", "ICE_GRID_NODE", "ICE_GRID_REGISTRY",
  "ICE_GRID_SERVER", "ICE_GRID_ADAPTER", "ICE_GRID_PING", "ICE_GRID_LOAD",
  "ICE_GRID_ADD", "ICE_GRID_REMOVE", "ICE_GRID_LIST", "ICE_GRID_SHUTDOWN",
  "ICE_GRID_STRING", "ICE_GRID_START", "ICE_GRID_STOP", "ICE_GRID_PATCH",
  "ICE_GRID_SIGNAL", "ICE_GRID_STDOUT", "ICE_GRID_STDERR",
  "ICE_GRID_DESCRIBE", "ICE_GRID_STATE", "ICE_GRID_PID",
  "ICE_GRID_ENDPOINTS", "ICE_GRID_ACTIVATION", "ICE_GRID_OBJECT",
  "ICE_GRID_FIND", "ICE_GRID_SHOW", "ICE_GRID_COPYING",
  "ICE_GRID_WARRANTY", "ICE_GRID_DIFF", "ICE_GRID_UPDATE",
  "ICE_GRID_INSTANTIATE", "ICE_GRID_TEMPLATE", "ICE_GRID_SERVICE",
  "ICE_GRID_ENABLE", "ICE_GRID_DISABLE", "';'", "$accept", "start",
  "commands", "checkInterrupted", "command", "strings_and_log_filename",
  "strings", "optional_strings", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    41,    42,    42,    43,    43,    44,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    46,    46,    46,
      47,    47,    48,    48
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     3,     2,     0,     2,     3,     3,
       3,     3,     3,     3,     4,     4,     3,     3,     3,     3,
       3,     3,     4,     4,     2,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     5,     5,     5,
       5,     5,     5,     3,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     4,
       4,     4,     4,     4,     4,     3,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     2,     2,     2,
       2,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       6,     0,     6,     0,     1,     0,     0,     0,     0,   123,
     123,   123,   123,   123,   121,   123,     0,   123,   116,     5,
       0,     4,   115,     0,     0,     0,     0,     0,     0,     0,
       7,    24,     0,   123,   123,     0,   123,   123,   123,   123,
     123,     0,     0,   123,   123,     0,   123,   123,     0,     0,
       0,   123,     0,   123,   123,     0,     0,     0,   123,     0,
     123,   123,   123,   123,   123,   123,   123,   123,   123,     0,
       0,   123,   123,     0,     0,   123,     0,   123,     0,   120,
       0,   123,   123,   123,   123,   123,     0,     0,     0,     0,
       0,   114,     8,     9,    10,     0,    11,    12,    13,     0,
      16,     0,     0,     0,     0,    43,   122,     0,     0,     0,
       0,     0,     0,     0,     0,   107,    17,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,   121,     0,     0,
     109,    18,     0,     0,    61,     0,     0,     0,     0,     0,
       0,   110,    19,     0,     0,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   123,     0,
       0,     0,     0,   108,    20,     0,     0,    95,     0,     0,
     113,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   105,   106,     0,   123,   111,    14,    15,    26,
      25,    28,    27,    36,    35,    34,    33,    30,    29,    32,
      31,    47,    46,    49,    48,    51,    50,    45,    44,    54,
     120,    53,   119,   118,    58,    57,    60,    59,    56,    55,
      63,    62,    65,    64,    69,    68,    71,    70,    73,    72,
      75,    74,    77,    76,    79,    78,    67,    66,    81,    80,
      83,    82,    90,    89,    22,     0,     0,     0,     0,    85,
      84,    87,    86,    94,    93,    92,    91,    97,    96,    99,
      98,   102,   104,   103,   101,   100,    23,     0,     0,    38,
      37,    40,    39,    42,    41
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     2,     3,    19,   128,   129,    41
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -45
static const short yypact[] =
{
      13,    35,    38,    75,   -45,    75,    -1,    80,     2,   147,
     161,   179,   113,     5,    29,   184,   -15,    -4,   -45,   -45,
       9,   -45,   -45,    23,    26,    52,   -26,    55,    59,    68,
     -45,   -45,    78,     6,    43,    79,   105,    44,    61,    90,
      91,    82,    83,    93,    94,    84,    95,    97,    98,    85,
      99,   137,   104,   138,   139,   153,   106,   107,   162,   108,
     170,   176,   185,   187,   196,   201,   202,   203,   205,   207,
      67,   208,   211,   122,   127,   212,   128,   213,   134,   -45,
     143,   217,   219,   105,   222,   223,   194,   197,   200,    17,
     206,   -45,   -45,   -45,   -45,   209,   -45,   -45,   -45,   210,
     -45,   214,   215,   216,   218,   -45,   -45,   220,   221,   224,
     225,   226,   230,   231,   232,   -45,   -45,   233,   234,   235,
     236,   -45,   237,   238,   239,   240,   241,    29,   242,    47,
     -45,   -45,   243,   244,   -45,   245,   246,   247,   248,   249,
     250,   -45,   -45,   251,   252,   -45,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   227,   228,   274,
     275,   276,   277,   -45,   -45,   278,   279,   -45,   280,   281,
     -45,   -45,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   -45,   -45,   -45,   291,   229,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     292,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   293,   294,   295,   296,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   297,   298,   -45,
     -45,   -45,   -45,   -45,   -45
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -45,   -45,   -45,   337,   140,   -44,     1,   -10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -118
static const short yytable[] =
{
      49,    56,    73,    78,    20,    86,    20,    90,    74,   101,
      95,   140,    36,    -3,    96,    79,    87,    88,    75,    76,
     194,    36,    36,   102,   104,   165,   106,   108,   110,   112,
     114,    77,    89,   118,   120,     4,   123,   125,    -2,    22,
     195,   133,    31,   136,   138,    14,   103,   107,   144,    91,
     147,   149,   151,   153,   155,   157,   159,   161,   163,    36,
      36,   170,   172,    92,   109,   176,    93,   179,   222,   223,
     166,   183,   185,   186,   188,   190,     6,    36,     7,     8,
       9,    10,    11,    12,    13,    23,    24,    25,    26,    27,
     167,    14,    94,   111,   113,    97,   117,   119,   122,    98,
     124,   126,   168,    15,    99,    16,    36,    36,    28,    36,
      36,    36,    17,    36,   127,    18,    57,    29,   100,   105,
      30,    36,   115,   116,   121,   130,    58,    59,   220,    36,
      60,    61,    62,    63,    64,    65,    66,    67,    68,   131,
     132,   135,   137,    69,   134,    21,   141,   142,   145,    70,
      32,    71,    72,    36,    36,    36,   139,   256,   258,    33,
      34,    35,   173,    36,    42,   143,    37,   174,   177,   127,
      38,    43,    44,   146,   180,    45,    46,    36,    36,   148,
      39,    40,    50,   181,    47,   278,    36,    80,   150,    51,
     152,    48,    36,    52,    53,    36,    81,    82,    83,   154,
      36,    36,    54,    36,   156,   158,   160,    84,   162,    55,
     164,   169,    36,    85,   171,   175,   178,    36,    36,    36,
     182,    36,   184,   127,    36,   187,   189,    36,    36,    36,
     255,   257,   277,    36,   191,    36,     0,   192,    36,    36,
     193,     0,     0,    36,    36,    36,   196,     0,     0,   197,
     198,     0,     0,     0,   199,   200,   201,     0,   202,     0,
     203,   204,     0,     0,   205,   206,   207,     0,     0,     0,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   221,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,  -117,   279,   280,   281,   282,   283,   284,     5
};

static const short yycheck[] =
{
      10,    11,    12,    13,     3,    15,     5,    17,     3,     3,
      36,    55,    16,     0,    40,    14,    31,    32,    13,    14,
       3,    16,    16,    33,    34,    69,    36,    37,    38,    39,
      40,    26,    36,    43,    44,     0,    46,    47,     0,    40,
      23,    51,    40,    53,    54,    16,     3,     3,    58,    40,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    16,
      16,    71,    72,    40,     3,    75,    40,    77,    21,    22,
       3,    81,    82,    83,    84,    85,     1,    16,     3,     4,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
      23,    16,    40,     3,     3,    40,     3,     3,     3,    40,
       3,     3,    35,    28,    36,    30,    16,    16,    28,    16,
      16,    16,    37,    16,    16,    40,     3,    37,    40,    40,
      40,    16,    40,    40,    40,    40,    13,    14,   127,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    40,
       3,     3,     3,    30,    40,     5,    40,    40,    40,    36,
       3,    38,    39,    16,    16,    16,     3,   167,   168,    12,
      13,    14,    40,    16,     3,     3,    19,    40,    40,    16,
      23,    10,    11,     3,    40,    14,    15,    16,    16,     3,
      33,    34,     3,    40,    23,   195,    16,     3,     3,    10,
       3,    30,    16,    14,    15,    16,    12,    13,    14,     3,
      16,    16,    23,    16,     3,     3,     3,    23,     3,    30,
       3,     3,    16,    29,     3,     3,     3,    16,    16,    16,
       3,    16,     3,    16,    16,     3,     3,    16,    16,    16,
       3,     3,     3,    16,    40,    16,    -1,    40,    16,    16,
      40,    -1,    -1,    16,    16,    16,    40,    -1,    -1,    40,
      40,    -1,    -1,    -1,    40,    40,    40,    -1,    40,    -1,
      40,    40,    -1,    -1,    40,    40,    40,    -1,    -1,    -1,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,     2
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    42,    43,    44,     0,    44,     1,     3,     4,     5,
       6,     7,     8,     9,    16,    28,    30,    37,    40,    45,
      47,    45,    40,     5,     6,     7,     8,     9,    28,    37,
      40,    40,     3,    12,    13,    14,    16,    19,    23,    33,
      34,    48,     3,    10,    11,    14,    15,    23,    30,    48,
       3,    10,    14,    15,    23,    30,    48,     3,    13,    14,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    30,
      36,    38,    39,    48,     3,    13,    14,    26,    48,    47,
       3,    12,    13,    14,    23,    29,    48,    31,    32,    36,
      48,    40,    40,    40,    40,    36,    40,    40,    40,    36,
      40,     3,    48,     3,    48,    40,    48,     3,    48,     3,
      48,     3,    48,     3,    48,    40,    40,     3,    48,     3,
      48,    40,     3,    48,     3,    48,     3,    16,    46,    47,
      40,    40,     3,    48,    40,     3,    48,     3,    48,     3,
      46,    40,    40,     3,    48,    40,     3,    48,     3,    48,
       3,    48,     3,    48,     3,    48,     3,    48,     3,    48,
       3,    48,     3,    48,     3,    46,     3,    23,    35,     3,
      48,     3,    48,    40,    40,     3,    48,    40,     3,    48,
      40,    40,     3,    48,     3,    48,    48,     3,    48,     3,
      48,    40,    40,    40,     3,    23,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      47,    40,    21,    22,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,     3,    48,     3,    48,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,     3,    48,    40,
      40,    40,    40,    40,    40
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

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

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
	short *yyss1 = yyss;


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
	short *yyss1 = yyss;
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
#line 81 "Grammar.y"
    {
;}
    break;

  case 3:
#line 84 "Grammar.y"
    {
;}
    break;

  case 4:
#line 92 "Grammar.y"
    {
;}
    break;

  case 5:
#line 95 "Grammar.y"
    {
;}
    break;

  case 6:
#line 101 "Grammar.y"
    {
    parser->checkInterrupted();
;}
    break;

  case 7:
#line 110 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 8:
#line 114 "Grammar.y"
    {
    parser->usage("application");
;}
    break;

  case 9:
#line 118 "Grammar.y"
    {
    parser->usage("node");
;}
    break;

  case 10:
#line 122 "Grammar.y"
    {
    parser->usage("registry");
;}
    break;

  case 11:
#line 126 "Grammar.y"
    {
    parser->usage("server");
;}
    break;

  case 12:
#line 130 "Grammar.y"
    {
    parser->usage("adapter");
;}
    break;

  case 13:
#line 134 "Grammar.y"
    {
    parser->usage("object");
;}
    break;

  case 14:
#line 138 "Grammar.y"
    {
    parser->usage("server template");
;}
    break;

  case 15:
#line 142 "Grammar.y"
    {
    parser->usage("servcice template");
;}
    break;

  case 16:
#line 146 "Grammar.y"
    {
    parser->usage("application");
;}
    break;

  case 17:
#line 150 "Grammar.y"
    {
    parser->usage("node");
;}
    break;

  case 18:
#line 154 "Grammar.y"
    {
    parser->usage("registry");
;}
    break;

  case 19:
#line 158 "Grammar.y"
    {
    parser->usage("server");
;}
    break;

  case 20:
#line 162 "Grammar.y"
    {
    parser->usage("adapter");
;}
    break;

  case 21:
#line 166 "Grammar.y"
    {
    parser->usage("object");
;}
    break;

  case 22:
#line 170 "Grammar.y"
    {
    parser->usage("server template");
;}
    break;

  case 23:
#line 174 "Grammar.y"
    {
    parser->usage("service template");
;}
    break;

  case 24:
#line 178 "Grammar.y"
    {
    return 0;
;}
    break;

  case 25:
#line 182 "Grammar.y"
    {
    parser->addApplication(yyvsp[-1]);
;}
    break;

  case 26:
#line 186 "Grammar.y"
    {
    parser->usage("application", "add");
;}
    break;

  case 27:
#line 190 "Grammar.y"
    {
    parser->removeApplication(yyvsp[-1]);
;}
    break;

  case 28:
#line 194 "Grammar.y"
    {
    parser->usage("application", "remove");
;}
    break;

  case 29:
#line 198 "Grammar.y"
    {
    parser->diffApplication(yyvsp[-1]);
;}
    break;

  case 30:
#line 202 "Grammar.y"
    {
    parser->usage("application", "diff");
;}
    break;

  case 31:
#line 206 "Grammar.y"
    {
    parser->updateApplication(yyvsp[-1]);
;}
    break;

  case 32:
#line 210 "Grammar.y"
    {
    parser->usage("application", "update");
;}
    break;

  case 33:
#line 214 "Grammar.y"
    {
    parser->describeApplication(yyvsp[-1]);
;}
    break;

  case 34:
#line 218 "Grammar.y"
    {
    parser->usage("application", "describe");
;}
    break;

  case 35:
#line 222 "Grammar.y"
    {
    parser->patchApplication(yyvsp[-1]);
;}
    break;

  case 36:
#line 226 "Grammar.y"
    {
    parser->usage("application", "patch");
;}
    break;

  case 37:
#line 230 "Grammar.y"
    {
    parser->describeServerTemplate(yyvsp[-1]);
;}
    break;

  case 38:
#line 234 "Grammar.y"
    {
    parser->usage("server template", "describe");
;}
    break;

  case 39:
#line 238 "Grammar.y"
    {
    parser->instantiateServerTemplate(yyvsp[-1]);
;}
    break;

  case 40:
#line 242 "Grammar.y"
    {
    parser->usage("server template", "instantiate");
;}
    break;

  case 41:
#line 246 "Grammar.y"
    {
    parser->describeServiceTemplate(yyvsp[-1]);
;}
    break;

  case 42:
#line 250 "Grammar.y"
    {
    parser->usage("service template", "describe");
;}
    break;

  case 43:
#line 254 "Grammar.y"
    {
    parser->listAllApplications();
;}
    break;

  case 44:
#line 258 "Grammar.y"
    {
    parser->describeNode(yyvsp[-1]);
;}
    break;

  case 45:
#line 262 "Grammar.y"
    {
    parser->usage("node", "describe");
;}
    break;

  case 46:
#line 266 "Grammar.y"
    {
    parser->pingNode(yyvsp[-1]);
;}
    break;

  case 47:
#line 270 "Grammar.y"
    {
    parser->usage("node", "ping");
;}
    break;

  case 48:
#line 274 "Grammar.y"
    {
    parser->printLoadNode(yyvsp[-1]);
;}
    break;

  case 49:
#line 278 "Grammar.y"
    {
    parser->usage("node", "lost");
;}
    break;

  case 50:
#line 282 "Grammar.y"
    {
    parser->shutdownNode(yyvsp[-1]);
;}
    break;

  case 51:
#line 286 "Grammar.y"
    {
    parser->usage("node", "shutdown");
;}
    break;

  case 52:
#line 290 "Grammar.y"
    {
    parser->listAllNodes();
;}
    break;

  case 53:
#line 294 "Grammar.y"
    {
    parser->showFile("node", yyvsp[-1]);
;}
    break;

  case 54:
#line 298 "Grammar.y"
    {
    parser->usage("node", "show");
;}
    break;

  case 55:
#line 302 "Grammar.y"
    {
    parser->describeRegistry(yyvsp[-1]);
;}
    break;

  case 56:
#line 306 "Grammar.y"
    {
    parser->usage("registry", "describe");
;}
    break;

  case 57:
#line 310 "Grammar.y"
    {
    parser->pingRegistry(yyvsp[-1]);
;}
    break;

  case 58:
#line 314 "Grammar.y"
    {
    parser->usage("registry", "ping");
;}
    break;

  case 59:
#line 318 "Grammar.y"
    {
    parser->shutdownRegistry(yyvsp[-1]);
;}
    break;

  case 60:
#line 322 "Grammar.y"
    {
    parser->usage("registry", "shutdown");
;}
    break;

  case 61:
#line 326 "Grammar.y"
    {
    parser->listAllRegistries();
;}
    break;

  case 62:
#line 330 "Grammar.y"
    {
    parser->showFile("registry", yyvsp[-1]);
;}
    break;

  case 63:
#line 334 "Grammar.y"
    {
    parser->usage("registry", "show");
;}
    break;

  case 64:
#line 338 "Grammar.y"
    {
    parser->removeServer(yyvsp[-1]);
;}
    break;

  case 65:
#line 342 "Grammar.y"
    {
    parser->usage("server", "remove");
;}
    break;

  case 66:
#line 346 "Grammar.y"
    {
    parser->describeServer(yyvsp[-1]);
;}
    break;

  case 67:
#line 350 "Grammar.y"
    {
    parser->usage("server", "describe");
;}
    break;

  case 68:
#line 354 "Grammar.y"
    {
    parser->startServer(yyvsp[-1]);
;}
    break;

  case 69:
#line 358 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 70:
#line 362 "Grammar.y"
    {
    parser->stopServer(yyvsp[-1]);
;}
    break;

  case 71:
#line 366 "Grammar.y"
    {
    parser->usage("server", "stop");
;}
    break;

  case 72:
#line 370 "Grammar.y"
    {
    parser->patchServer(yyvsp[-1]);
;}
    break;

  case 73:
#line 374 "Grammar.y"
    {
    parser->usage("server", "patch");
;}
    break;

  case 74:
#line 378 "Grammar.y"
    {
    parser->signalServer(yyvsp[-1]);
;}
    break;

  case 75:
#line 382 "Grammar.y"
    {
    parser->usage("server", "signal");
;}
    break;

  case 76:
#line 386 "Grammar.y"
    {
    parser->writeMessage(yyvsp[-1], 1);
;}
    break;

  case 77:
#line 390 "Grammar.y"
    {
    parser->usage("server", "stdout");
;}
    break;

  case 78:
#line 394 "Grammar.y"
    {
    parser->writeMessage(yyvsp[-1], 2);
;}
    break;

  case 79:
#line 398 "Grammar.y"
    {
    parser->usage("server", "stderr");
;}
    break;

  case 80:
#line 402 "Grammar.y"
    {
    parser->stateServer(yyvsp[-1]);
;}
    break;

  case 81:
#line 406 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 82:
#line 410 "Grammar.y"
    {
    parser->pidServer(yyvsp[-1]);
;}
    break;

  case 83:
#line 414 "Grammar.y"
    {
    parser->usage("server", "pid");
;}
    break;

  case 84:
#line 418 "Grammar.y"
    {
    parser->enableServer(yyvsp[-1], true);
;}
    break;

  case 85:
#line 422 "Grammar.y"
    {
    parser->usage("server", "enable");
;}
    break;

  case 86:
#line 426 "Grammar.y"
    {
    parser->enableServer(yyvsp[-1], false);
;}
    break;

  case 87:
#line 430 "Grammar.y"
    {
    parser->usage("server", "disable");
;}
    break;

  case 88:
#line 434 "Grammar.y"
    {
    parser->listAllServers();
;}
    break;

  case 89:
#line 438 "Grammar.y"
    {
    parser->showFile("server", yyvsp[-1]);
;}
    break;

  case 90:
#line 442 "Grammar.y"
    {
    parser->usage("server", "show");
;}
    break;

  case 91:
#line 446 "Grammar.y"
    {
    parser->endpointsAdapter(yyvsp[-1]);
;}
    break;

  case 92:
#line 450 "Grammar.y"
    {
    parser->usage("adapter", "endpoints");
;}
    break;

  case 93:
#line 454 "Grammar.y"
    {
    parser->removeAdapter(yyvsp[-1]);
;}
    break;

  case 94:
#line 458 "Grammar.y"
    {
    parser->usage("adapter", "remove");
;}
    break;

  case 95:
#line 462 "Grammar.y"
    {
    parser->listAllAdapters();
;}
    break;

  case 96:
#line 466 "Grammar.y"
    {
    parser->addObject(yyvsp[-1]);
;}
    break;

  case 97:
#line 470 "Grammar.y"
    {
    parser->usage("object", "add");
;}
    break;

  case 98:
#line 474 "Grammar.y"
    {
    parser->removeObject(yyvsp[-1]);
;}
    break;

  case 99:
#line 478 "Grammar.y"
    {
    parser->usage("object", "remove");
;}
    break;

  case 100:
#line 482 "Grammar.y"
    {
    parser->findObject(yyvsp[-1]);
;}
    break;

  case 101:
#line 486 "Grammar.y"
    {
    parser->usage("object", "find");
;}
    break;

  case 102:
#line 490 "Grammar.y"
    {
    parser->listObject(yyvsp[-1]);
;}
    break;

  case 103:
#line 494 "Grammar.y"
    {
    parser->describeObject(yyvsp[-1]);
;}
    break;

  case 104:
#line 498 "Grammar.y"
    {
    parser->usage("object", "describe");
;}
    break;

  case 105:
#line 502 "Grammar.y"
    {
    parser->showCopying();
;}
    break;

  case 106:
#line 506 "Grammar.y"
    {
    parser->showWarranty();
;}
    break;

  case 107:
#line 510 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `application' (use `help application'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `application " + yyvsp[-1].front() + "' (use `help application'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 108:
#line 523 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `server' (use `help server'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `server " + yyvsp[-1].front() + "' (use `help server'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 109:
#line 536 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `node' (use `help node'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `node " + yyvsp[-1].front() + "' (use `help node'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 110:
#line 549 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `registry' (use `help registry'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `registry " + yyvsp[-1].front() + "' (use `help registry'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 111:
#line 562 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->invalidCommand("invalid command `service' ");
    }
    else
    {
	parser->invalidCommand("invalid command: `service " + yyvsp[-1].front() + "'");
    }
;}
    break;

  case 112:
#line 573 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `object' (use `help object'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `object " + yyvsp[-1].front() + "' (use `help object'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 113:
#line 586 "Grammar.y"
    {
    if(yyvsp[-1].empty())
    {
	parser->error("invalid command `adapter' (use `help adapter'\n"
		      "to get the list of available commands)");
    }
    else
    {
	parser->error("invalid command: `adapter " + yyvsp[-1].front() + "' (use `help adapter'\n"
		      "to get the list of available commands)");
    }
;}
    break;

  case 114:
#line 599 "Grammar.y"
    {
    parser->error("invalid command `" + yyvsp[-1].front() + "' (use `help'\n"
		  "to get the list of available commands)");
;}
    break;

  case 115:
#line 604 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 116:
#line 608 "Grammar.y"
    {
;}
    break;

  case 117:
#line 617 "Grammar.y"
    {
    yyval = yyvsp[0];
    yyval.push_front(yyvsp[-1].front());
;}
    break;

  case 118:
#line 622 "Grammar.y"
    {
    yyval = yyvsp[-1];
    yyval.push_back("stderr");
;}
    break;

  case 119:
#line 627 "Grammar.y"
    {
    yyval = yyvsp[-1];
    yyval.push_back("stdout");
;}
    break;

  case 120:
#line 637 "Grammar.y"
    {
    yyval = yyvsp[0];
    yyval.push_front(yyvsp[-1].front());
;}
    break;

  case 121:
#line 642 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 122:
#line 651 "Grammar.y"
    {
    yyval = yyvsp[0];
    yyval.push_front(yyvsp[-1].front());
;}
    break;

  case 123:
#line 656 "Grammar.y"
    {
    yyval = YYSTYPE()
;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2256 "Grammar.tab.c"

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
      /* If just tried and failed to reuse lookahead token after an
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
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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


#line 661 "Grammar.y"


