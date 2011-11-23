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
#define YYLAST   1982

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  7
/* YYNRULES -- Number of rules. */
#define YYNRULES  145
/* YYNRULES -- Number of states. */
#define YYNSTATES  304

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
       0,     0,     3,     5,     6,    10,    13,    14,    17,    20,
      25,    30,    35,    40,    45,    50,    55,    60,    65,    70,
      75,    80,    85,    90,    96,   102,   108,   114,   120,   126,
     131,   136,   141,   146,   151,   156,   161,   166,   171,   176,
     181,   186,   191,   196,   201,   206,   211,   216,   221,   226,
     231,   236,   241,   246,   251,   256,   261,   266,   271,   276,
     281,   286,   291,   296,   301,   306,   311,   316,   321,   326,
     331,   336,   341,   346,   351,   356,   361,   366,   371,   376,
     381,   386,   391,   396,   401,   406,   411,   416,   421,   426,
     431,   436,   441,   446,   451,   456,   460,   464,   468,   472,
     476,   480,   485,   489,   493,   496,   498,   501,   504,   508,
     512,   513,   515,   517,   519,   521,   523,   525,   527,   529,
     531,   533,   535,   537,   539,   541,   543,   545,   547,   549,
     551,   553,   555,   557,   559,   561,   563,   565,   567,   569,
     571,   573,   575,   577,   579,   581
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      42,     0,    -1,    43,    -1,    -1,    43,    44,    45,    -1,
      44,    45,    -1,    -1,     3,    40,    -1,     4,    40,    -1,
       5,    12,    46,    40,    -1,     5,    12,     3,    40,    -1,
       5,    13,    46,    40,    -1,     5,    13,     3,    40,    -1,
       5,    33,    46,    40,    -1,     5,    33,     3,    40,    -1,
       5,    34,    46,    40,    -1,     5,    34,     3,    40,    -1,
       5,    23,    46,    40,    -1,     5,    23,     3,    40,    -1,
       5,    19,    46,    40,    -1,     5,    19,     3,    40,    -1,
       5,    14,    46,    40,    -1,     5,    14,     3,    40,    -1,
       8,    36,    23,    46,    40,    -1,     8,    36,    23,     3,
      40,    -1,     8,    36,    35,    46,    40,    -1,     8,    36,
      35,     3,    40,    -1,    37,    36,    23,    46,    40,    -1,
      37,    36,    23,     3,    40,    -1,     6,    23,    46,    40,
      -1,     6,    23,     3,    40,    -1,     6,    10,    46,    40,
      -1,     6,    10,     3,    40,    -1,     6,    11,    46,    40,
      -1,     6,    11,     3,    40,    -1,     6,    15,    46,    40,
      -1,     6,    15,     3,    40,    -1,     6,    14,    46,    40,
      -1,     6,    14,     3,    40,    -1,     6,    30,    46,    40,
      -1,     6,    30,     3,    40,    -1,     7,    23,    46,    40,
      -1,     7,    23,     3,    40,    -1,     7,    10,    46,    40,
      -1,     7,    10,     3,    40,    -1,     7,    15,    46,    40,
      -1,     7,    15,     3,    40,    -1,     7,    14,    46,    40,
      -1,     7,    14,     3,    40,    -1,     7,    30,    46,    40,
      -1,     7,    30,     3,    40,    -1,     8,    13,    46,    40,
      -1,     8,    13,     3,    40,    -1,     8,    23,    46,    40,
      -1,     8,    23,     3,    40,    -1,     8,    17,    46,    40,
      -1,     8,    17,     3,    40,    -1,     8,    18,    46,    40,
      -1,     8,    18,     3,    40,    -1,     8,    19,    46,    40,
      -1,     8,    19,     3,    40,    -1,     8,    20,    46,    40,
      -1,     8,    20,     3,    40,    -1,     8,    21,    46,    40,
      -1,     8,    21,     3,    40,    -1,     8,    22,    46,    40,
      -1,     8,    22,     3,    40,    -1,     8,    24,    46,    40,
      -1,     8,    24,     3,    40,    -1,     8,    25,    46,    40,
      -1,     8,    25,     3,    40,    -1,     8,    38,    46,    40,
      -1,     8,    38,     3,    40,    -1,     8,    39,    46,    40,
      -1,     8,    39,     3,    40,    -1,     8,    14,    46,    40,
      -1,     8,    14,     3,    40,    -1,     8,    30,    46,    40,
      -1,     8,    30,     3,    40,    -1,     9,    26,    46,    40,
      -1,     9,    26,     3,    40,    -1,     9,    13,    46,    40,
      -1,     9,    13,     3,    40,    -1,     9,    14,    46,    40,
      -1,     9,    14,     3,    40,    -1,    28,    12,    46,    40,
      -1,    28,    12,     3,    40,    -1,    28,    13,    46,    40,
      -1,    28,    13,     3,    40,    -1,    28,    29,    46,    40,
      -1,    28,    29,     3,    40,    -1,    28,    14,    46,    40,
      -1,    28,    14,     3,    40,    -1,    28,    23,    46,    40,
      -1,    28,    23,     3,    40,    -1,    30,    31,    40,    -1,
      30,    32,    40,    -1,     3,    47,    40,    -1,     3,    16,
      40,    -1,     3,     1,    40,    -1,    47,     3,    40,    -1,
      47,    16,     1,    40,    -1,    47,     1,    40,    -1,    16,
       1,    40,    -1,     1,    40,    -1,    40,    -1,    16,    46,
      -1,    47,    46,    -1,    16,     3,    46,    -1,    47,     3,
      46,    -1,    -1,     4,    -1,     5,    -1,     6,    -1,     7,
      -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    17,    -1,    18,
      -1,    19,    -1,    20,    -1,    23,    -1,    24,    -1,    25,
      -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    22,
      -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    85,    85,    89,    96,    99,   106,   114,   118,   122,
     126,   130,   134,   138,   142,   146,   150,   154,   158,   162,
     166,   170,   174,   178,   182,   186,   190,   194,   198,   202,
     206,   210,   214,   218,   222,   226,   230,   234,   238,   242,
     246,   250,   254,   258,   262,   266,   270,   274,   278,   282,
     286,   290,   294,   298,   302,   306,   310,   314,   318,   322,
     326,   330,   334,   338,   342,   346,   350,   354,   358,   362,
     366,   370,   374,   378,   382,   386,   390,   394,   398,   402,
     406,   410,   414,   418,   422,   426,   430,   434,   438,   442,
     446,   450,   454,   458,   462,   466,   470,   474,   478,   482,
     486,   490,   496,   501,   506,   510,   519,   524,   529,   535,
     542,   550,   553,   556,   559,   562,   565,   568,   571,   574,
     577,   580,   583,   586,   589,   592,   595,   598,   601,   604,
     607,   610,   613,   616,   619,   622,   625,   628,   631,   634,
     637,   640,   643,   646,   649,   652
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
  "commands", "checkInterrupted", "command", "strings", "keyword", 0
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
      45,    45,    45,    45,    45,    45,    46,    46,    46,    46,
      46,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     3,     2,     0,     2,     2,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     5,     5,     5,     5,     5,     5,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     4,     3,     3,     2,     1,     2,     2,     3,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       6,     0,     6,     0,     1,     0,     0,     0,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   123,   124,   125,   126,   145,   144,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   105,     5,     0,     4,   104,     0,
     111,   112,   113,   114,   115,   116,     0,   132,   134,   141,
       7,     0,     8,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,     0,   110,   110,   110,   110,   110,     0,
     110,   110,   110,   110,   110,     0,     0,     0,     0,     0,
       0,    99,    98,    97,     0,   110,     0,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
      96,   110,   102,   100,     0,    10,   110,   106,     9,   110,
     107,    12,    11,    22,    21,    20,    19,    18,    17,    14,
      13,    16,    15,    32,    31,    34,    33,    38,    37,    36,
      35,    30,    29,    40,    39,    44,    43,    48,    47,    46,
      45,    42,    41,    50,    49,    52,    51,    76,    75,    56,
      55,    58,    57,    60,    59,    62,    61,    64,    63,    66,
      65,    54,    53,    68,    67,    70,    69,    78,    77,     0,
       0,     0,     0,    72,    71,    74,    73,    82,    81,    84,
      83,    80,    79,    86,    85,    88,    87,    92,    91,    94,
      93,    90,    89,     0,     0,   101,   108,   109,    24,    23,
      26,    25,    28,    27
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,     3,    45,   116,   117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const short yypact[] =
{
      35,    43,    45,    51,   -65,    51,     9,   142,    10,   107,
    1874,  1876,    79,   118,   -65,   -65,   -65,   -65,   -65,   -65,
      94,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,    93,   -65,    16,   -65,   -65,   -65,   -65,   -65,
     -65,    58,   -65,   -65,   -65,   -65,   122,   -65,   -65,    68,
     -65,   -65,   -65,   -65,   -65,   -65,    70,   -65,   -65,   -65,
     -65,    71,   -65,   180,   217,   254,   291,   328,   365,   402,
     439,   476,   513,   550,   587,   624,   661,   698,   735,   772,
     809,   846,   883,   920,   957,   994,  1031,  1068,  1105,  1142,
    1179,  1216,  1253,     6,  1290,  1327,  1364,  1401,  1438,    74,
    1475,  1512,  1549,  1586,  1623,    84,    87,   105,    89,    95,
     132,   -65,   -65,   -65,    96,  1660,    99,  1697,  1847,  1852,
    1853,  1854,  1855,  1856,  1858,  1860,  1861,  1862,  1863,  1865,
    1867,  1868,  1869,  1870,  1871,  1872,  1873,  1875,  1877,  1878,
    1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1888,
    1889,  1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,
    1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,
    1909,  1910,  1911,  1912,  1913,  1914,  1734,  1771,  1915,  1916,
    1917,  1918,  1919,  1920,  1921,  1922,  1923,  1924,   -65,  1925,
    1926,  1927,  1928,  1929,  1930,  1931,  1932,  1933,  1934,   -65,
     -65,  1808,   -65,   -65,  1935,   -65,  1844,   -65,   -65,  1844,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,  1936,
    1937,  1938,  1939,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,  1940,  1941,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -65,   -65,   -65,  1980,   129,   -64,    39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const short yytable[] =
{
     119,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     139,   141,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   167,   169,   171,   173,   175,   176,
     179,   181,   183,   185,   187,    -3,   190,   192,   194,   196,
     198,   177,    46,     4,    46,    -2,    61,   105,   106,    48,
      62,   207,     6,   210,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    81,    82,   107,    99,    83,    84,    85,    86,
      87,    88,    89,    90,    91,   100,   101,   102,   111,    92,
     112,   113,   270,   272,   188,    93,   103,    94,    95,    63,
      64,    65,   104,   108,   199,   109,    66,   200,   201,   202,
      67,    96,    97,   204,    47,   203,   205,   294,   110,   208,
      68,    69,   296,    49,    98,   297,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    17,    18,    19,    56,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      57,    33,    58,    35,    36,    37,    38,    39,    40,    59,
      42,    43,    60,   114,    50,    51,    52,    53,    54,    55,
      14,    15,    16,    17,    18,    19,   115,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    57,    33,
      58,    35,    36,    37,    38,    39,    40,    59,    42,    43,
     118,    50,    51,    52,    53,    54,    55,    14,    15,    16,
      17,    18,    19,   115,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    57,    33,    58,    35,    36,
      37,    38,    39,    40,    59,    42,    43,   120,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,   122,    50,    51,    52,    53,    54,
      55,    14,    15,    16,    17,    18,    19,   115,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    57,
      33,    58,    35,    36,    37,    38,    39,    40,    59,    42,
      43,   124,    50,    51,    52,    53,    54,    55,    14,    15,
      16,    17,    18,    19,   115,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    33,    58,    35,
      36,    37,    38,    39,    40,    59,    42,    43,   126,    50,
      51,    52,    53,    54,    55,    14,    15,    16,    17,    18,
      19,   115,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    57,    33,    58,    35,    36,    37,    38,
      39,    40,    59,    42,    43,   128,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    17,    18,    19,   115,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      57,    33,    58,    35,    36,    37,    38,    39,    40,    59,
      42,    43,   130,    50,    51,    52,    53,    54,    55,    14,
      15,    16,    17,    18,    19,   115,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    57,    33,    58,
      35,    36,    37,    38,    39,    40,    59,    42,    43,   132,
      50,    51,    52,    53,    54,    55,    14,    15,    16,    17,
      18,    19,   115,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    57,    33,    58,    35,    36,    37,
      38,    39,    40,    59,    42,    43,   134,    50,    51,    52,
      53,    54,    55,    14,    15,    16,    17,    18,    19,   115,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    57,    33,    58,    35,    36,    37,    38,    39,    40,
      59,    42,    43,   136,    50,    51,    52,    53,    54,    55,
      14,    15,    16,    17,    18,    19,   115,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    57,    33,
      58,    35,    36,    37,    38,    39,    40,    59,    42,    43,
     138,    50,    51,    52,    53,    54,    55,    14,    15,    16,
      17,    18,    19,   115,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    57,    33,    58,    35,    36,
      37,    38,    39,    40,    59,    42,    43,   140,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,   142,    50,    51,    52,    53,    54,
      55,    14,    15,    16,    17,    18,    19,   115,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    57,
      33,    58,    35,    36,    37,    38,    39,    40,    59,    42,
      43,   144,    50,    51,    52,    53,    54,    55,    14,    15,
      16,    17,    18,    19,   115,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    33,    58,    35,
      36,    37,    38,    39,    40,    59,    42,    43,   146,    50,
      51,    52,    53,    54,    55,    14,    15,    16,    17,    18,
      19,   115,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    57,    33,    58,    35,    36,    37,    38,
      39,    40,    59,    42,    43,   148,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    17,    18,    19,   115,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      57,    33,    58,    35,    36,    37,    38,    39,    40,    59,
      42,    43,   150,    50,    51,    52,    53,    54,    55,    14,
      15,    16,    17,    18,    19,   115,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    57,    33,    58,
      35,    36,    37,    38,    39,    40,    59,    42,    43,   152,
      50,    51,    52,    53,    54,    55,    14,    15,    16,    17,
      18,    19,   115,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    57,    33,    58,    35,    36,    37,
      38,    39,    40,    59,    42,    43,   154,    50,    51,    52,
      53,    54,    55,    14,    15,    16,    17,    18,    19,   115,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    57,    33,    58,    35,    36,    37,    38,    39,    40,
      59,    42,    43,   156,    50,    51,    52,    53,    54,    55,
      14,    15,    16,    17,    18,    19,   115,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    57,    33,
      58,    35,    36,    37,    38,    39,    40,    59,    42,    43,
     158,    50,    51,    52,    53,    54,    55,    14,    15,    16,
      17,    18,    19,   115,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    57,    33,    58,    35,    36,
      37,    38,    39,    40,    59,    42,    43,   160,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,   162,    50,    51,    52,    53,    54,
      55,    14,    15,    16,    17,    18,    19,   115,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    57,
      33,    58,    35,    36,    37,    38,    39,    40,    59,    42,
      43,   164,    50,    51,    52,    53,    54,    55,    14,    15,
      16,    17,    18,    19,   115,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    33,    58,    35,
      36,    37,    38,    39,    40,    59,    42,    43,   166,    50,
      51,    52,    53,    54,    55,    14,    15,    16,    17,    18,
      19,   115,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    57,    33,    58,    35,    36,    37,    38,
      39,    40,    59,    42,    43,   168,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    17,    18,    19,   115,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      57,    33,    58,    35,    36,    37,    38,    39,    40,    59,
      42,    43,   170,    50,    51,    52,    53,    54,    55,    14,
      15,    16,    17,    18,    19,   115,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    57,    33,    58,
      35,    36,    37,    38,    39,    40,    59,    42,    43,   172,
      50,    51,    52,    53,    54,    55,    14,    15,    16,    17,
      18,    19,   115,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    57,    33,    58,    35,    36,    37,
      38,    39,    40,    59,    42,    43,   174,    50,    51,    52,
      53,    54,    55,    14,    15,    16,    17,    18,    19,   115,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    57,    33,    58,    35,    36,    37,    38,    39,    40,
      59,    42,    43,   178,    50,    51,    52,    53,    54,    55,
      14,    15,    16,    17,    18,    19,   115,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    57,    33,
      58,    35,    36,    37,    38,    39,    40,    59,    42,    43,
     180,    50,    51,    52,    53,    54,    55,    14,    15,    16,
      17,    18,    19,   115,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    57,    33,    58,    35,    36,
      37,    38,    39,    40,    59,    42,    43,   182,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,   184,    50,    51,    52,    53,    54,
      55,    14,    15,    16,    17,    18,    19,   115,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    57,
      33,    58,    35,    36,    37,    38,    39,    40,    59,    42,
      43,   186,    50,    51,    52,    53,    54,    55,    14,    15,
      16,    17,    18,    19,   115,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    33,    58,    35,
      36,    37,    38,    39,    40,    59,    42,    43,   189,    50,
      51,    52,    53,    54,    55,    14,    15,    16,    17,    18,
      19,   115,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    57,    33,    58,    35,    36,    37,    38,
      39,    40,    59,    42,    43,   191,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    17,    18,    19,   115,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      57,    33,    58,    35,    36,    37,    38,    39,    40,    59,
      42,    43,   193,    50,    51,    52,    53,    54,    55,    14,
      15,    16,    17,    18,    19,   115,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    57,    33,    58,
      35,    36,    37,    38,    39,    40,    59,    42,    43,   195,
      50,    51,    52,    53,    54,    55,    14,    15,    16,    17,
      18,    19,   115,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    57,    33,    58,    35,    36,    37,
      38,    39,    40,    59,    42,    43,   197,    50,    51,    52,
      53,    54,    55,    14,    15,    16,    17,    18,    19,   115,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    57,    33,    58,    35,    36,    37,    38,    39,    40,
      59,    42,    43,   206,    50,    51,    52,    53,    54,    55,
      14,    15,    16,    17,    18,    19,   115,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    57,    33,
      58,    35,    36,    37,    38,    39,    40,    59,    42,    43,
     209,    50,    51,    52,    53,    54,    55,    14,    15,    16,
      17,    18,    19,   115,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    57,    33,    58,    35,    36,
      37,    38,    39,    40,    59,    42,    43,   269,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,   271,    50,    51,    52,    53,    54,
      55,    14,    15,    16,    17,    18,    19,   115,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    57,
      33,    58,    35,    36,    37,    38,    39,    40,    59,    42,
      43,   293,    50,    51,    52,    53,    54,    55,    14,    15,
      16,    17,    18,    19,   115,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    33,    58,    35,
      36,    37,    38,    39,    40,    59,    42,    43,    50,    51,
      52,    53,    54,    55,    14,    15,    16,    17,    18,    19,
     115,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    57,    33,    58,    35,    36,    37,    38,    39,
      40,    59,    42,    43,    70,    71,    76,   211,    72,    73,
      77,    78,   212,   213,   214,   215,   216,    74,   217,    79,
     218,   219,   220,   221,    75,   222,    80,   223,   224,   225,
     226,   227,   228,   229,     0,   230,     0,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   295,   298,   299,   300,   301,
     302,   303,     5
};

static const short yycheck[] =
{
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    23,
      94,    95,    96,    97,    98,     0,   100,   101,   102,   103,
     104,    35,     3,     0,     5,     0,     7,    31,    32,    40,
      40,   115,     1,   117,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    13,    14,    36,     1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    12,    13,    14,    40,    30,
      40,    40,   176,   177,    40,    36,    23,    38,    39,    12,
      13,    14,    29,     1,    40,     3,    19,    40,    23,    40,
      23,    13,    14,     1,     5,    40,    40,   201,    16,    40,
      33,    34,   206,     1,    26,   209,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    10,    11,    10,    40,    14,    15,
      14,    15,    40,    40,    40,    40,    40,    23,    40,    23,
      40,    40,    40,    40,    30,    40,    30,    40,    40,    40,
      40,    40,    40,    40,    -1,    40,    -1,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,     2
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    42,    43,    44,     0,    44,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    45,    47,    45,    40,     1,
       4,     5,     6,     7,     8,     9,    16,    28,    30,    37,
      40,    47,    40,    12,    13,    14,    19,    23,    33,    34,
      10,    11,    14,    15,    23,    30,    10,    14,    15,    23,
      30,    13,    14,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    30,    36,    38,    39,    13,    14,    26,     1,
      12,    13,    14,    23,    29,    31,    32,    36,     1,     3,
      16,    40,    40,    40,     3,    16,    46,    47,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,     3,    46,
       3,    46,     3,    46,     3,    46,    23,    35,     3,    46,
       3,    46,     3,    46,     3,    46,     3,    46,    40,     3,
      46,     3,    46,     3,    46,     3,    46,     3,    46,    40,
      40,    23,    40,    40,     1,    40,     3,    46,    40,     3,
      46,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,     3,
      46,     3,    46,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,     3,    46,    40,    46,    46,    40,    40,
      40,    40,    40,    40
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
#line 86 "Grammar.y"
    {
;}
    break;

  case 3:
#line 89 "Grammar.y"
    {
;}
    break;

  case 4:
#line 97 "Grammar.y"
    {
;}
    break;

  case 5:
#line 100 "Grammar.y"
    {
;}
    break;

  case 6:
#line 106 "Grammar.y"
    {
    parser->checkInterrupted();
;}
    break;

  case 7:
#line 115 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 8:
#line 119 "Grammar.y"
    {
    return 0;
;}
    break;

  case 9:
#line 123 "Grammar.y"
    {
    parser->addApplication(yyvsp[-1]);
;}
    break;

  case 10:
#line 127 "Grammar.y"
    {
    parser->usage("application", "add");
;}
    break;

  case 11:
#line 131 "Grammar.y"
    {
    parser->removeApplication(yyvsp[-1]);
;}
    break;

  case 12:
#line 135 "Grammar.y"
    {
    parser->usage("application", "remove");
;}
    break;

  case 13:
#line 139 "Grammar.y"
    {
    parser->diffApplication(yyvsp[-1]);
;}
    break;

  case 14:
#line 143 "Grammar.y"
    {
    parser->usage("application", "diff");
;}
    break;

  case 15:
#line 147 "Grammar.y"
    {
    parser->updateApplication(yyvsp[-1]);
;}
    break;

  case 16:
#line 151 "Grammar.y"
    {
    parser->usage("application", "update");
;}
    break;

  case 17:
#line 155 "Grammar.y"
    {
    parser->describeApplication(yyvsp[-1]);
;}
    break;

  case 18:
#line 159 "Grammar.y"
    {
    parser->usage("application", "describe");
;}
    break;

  case 19:
#line 163 "Grammar.y"
    {
    parser->patchApplication(yyvsp[-1]);
;}
    break;

  case 20:
#line 167 "Grammar.y"
    {
    parser->usage("application", "patch");
;}
    break;

  case 21:
#line 171 "Grammar.y"
    {
    parser->listAllApplications(yyvsp[-1]);
;}
    break;

  case 22:
#line 175 "Grammar.y"
    {
    parser->usage("application", "list");
;}
    break;

  case 23:
#line 179 "Grammar.y"
    {
    parser->describeServerTemplate(yyvsp[-1]);
;}
    break;

  case 24:
#line 183 "Grammar.y"
    {
    parser->usage("server template", "describe");
;}
    break;

  case 25:
#line 187 "Grammar.y"
    {
    parser->instantiateServerTemplate(yyvsp[-1]);
;}
    break;

  case 26:
#line 191 "Grammar.y"
    {
    parser->usage("server template", "instantiate");
;}
    break;

  case 27:
#line 195 "Grammar.y"
    {
    parser->describeServiceTemplate(yyvsp[-1]);
;}
    break;

  case 28:
#line 199 "Grammar.y"
    {
    parser->usage("service template", "describe");
;}
    break;

  case 29:
#line 203 "Grammar.y"
    {
    parser->describeNode(yyvsp[-1]);
;}
    break;

  case 30:
#line 207 "Grammar.y"
    {
    parser->usage("node", "describe");
;}
    break;

  case 31:
#line 211 "Grammar.y"
    {
    parser->pingNode(yyvsp[-1]);
;}
    break;

  case 32:
#line 215 "Grammar.y"
    {
    parser->usage("node", "ping");
;}
    break;

  case 33:
#line 219 "Grammar.y"
    {
    parser->printLoadNode(yyvsp[-1]);
;}
    break;

  case 34:
#line 223 "Grammar.y"
    {
    parser->usage("node", "lost");
;}
    break;

  case 35:
#line 227 "Grammar.y"
    {
    parser->shutdownNode(yyvsp[-1]);
;}
    break;

  case 36:
#line 231 "Grammar.y"
    {
    parser->usage("node", "shutdown");
;}
    break;

  case 37:
#line 235 "Grammar.y"
    {
    parser->listAllNodes(yyvsp[-1]);
;}
    break;

  case 38:
#line 239 "Grammar.y"
    {
    parser->usage("node", "list");
;}
    break;

  case 39:
#line 243 "Grammar.y"
    {
    parser->showFile("node", yyvsp[-1]);
;}
    break;

  case 40:
#line 247 "Grammar.y"
    {
    parser->usage("node", "show");
;}
    break;

  case 41:
#line 251 "Grammar.y"
    {
    parser->describeRegistry(yyvsp[-1]);
;}
    break;

  case 42:
#line 255 "Grammar.y"
    {
    parser->usage("registry", "describe");
;}
    break;

  case 43:
#line 259 "Grammar.y"
    {
    parser->pingRegistry(yyvsp[-1]);
;}
    break;

  case 44:
#line 263 "Grammar.y"
    {
    parser->usage("registry", "ping");
;}
    break;

  case 45:
#line 267 "Grammar.y"
    {
    parser->shutdownRegistry(yyvsp[-1]);
;}
    break;

  case 46:
#line 271 "Grammar.y"
    {
    parser->usage("registry", "shutdown");
;}
    break;

  case 47:
#line 275 "Grammar.y"
    {
    parser->listAllRegistries(yyvsp[-1]);
;}
    break;

  case 48:
#line 279 "Grammar.y"
    {
    parser->usage("registry", "list");
;}
    break;

  case 49:
#line 283 "Grammar.y"
    {
    parser->showFile("registry", yyvsp[-1]);
;}
    break;

  case 50:
#line 287 "Grammar.y"
    {
    parser->usage("registry", "show");
;}
    break;

  case 51:
#line 291 "Grammar.y"
    {
    parser->removeServer(yyvsp[-1]);
;}
    break;

  case 52:
#line 295 "Grammar.y"
    {
    parser->usage("server", "remove");
;}
    break;

  case 53:
#line 299 "Grammar.y"
    {
    parser->describeServer(yyvsp[-1]);
;}
    break;

  case 54:
#line 303 "Grammar.y"
    {
    parser->usage("server", "describe");
;}
    break;

  case 55:
#line 307 "Grammar.y"
    {
    parser->startServer(yyvsp[-1]);
;}
    break;

  case 56:
#line 311 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 57:
#line 315 "Grammar.y"
    {
    parser->stopServer(yyvsp[-1]);
;}
    break;

  case 58:
#line 319 "Grammar.y"
    {
    parser->usage("server", "stop");
;}
    break;

  case 59:
#line 323 "Grammar.y"
    {
    parser->patchServer(yyvsp[-1]);
;}
    break;

  case 60:
#line 327 "Grammar.y"
    {
    parser->usage("server", "patch");
;}
    break;

  case 61:
#line 331 "Grammar.y"
    {
    parser->signalServer(yyvsp[-1]);
;}
    break;

  case 62:
#line 335 "Grammar.y"
    {
    parser->usage("server", "signal");
;}
    break;

  case 63:
#line 339 "Grammar.y"
    {
    parser->writeMessage(yyvsp[-1], 1);
;}
    break;

  case 64:
#line 343 "Grammar.y"
    {
    parser->usage("server", "stdout");
;}
    break;

  case 65:
#line 347 "Grammar.y"
    {
    parser->writeMessage(yyvsp[-1], 2);
;}
    break;

  case 66:
#line 351 "Grammar.y"
    {
    parser->usage("server", "stderr");
;}
    break;

  case 67:
#line 355 "Grammar.y"
    {
    parser->stateServer(yyvsp[-1]);
;}
    break;

  case 68:
#line 359 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 69:
#line 363 "Grammar.y"
    {
    parser->pidServer(yyvsp[-1]);
;}
    break;

  case 70:
#line 367 "Grammar.y"
    {
    parser->usage("server", "pid");
;}
    break;

  case 71:
#line 371 "Grammar.y"
    {
    parser->enableServer(yyvsp[-1], true);
;}
    break;

  case 72:
#line 375 "Grammar.y"
    {
    parser->usage("server", "enable");
;}
    break;

  case 73:
#line 379 "Grammar.y"
    {
    parser->enableServer(yyvsp[-1], false);
;}
    break;

  case 74:
#line 383 "Grammar.y"
    {
    parser->usage("server", "disable");
;}
    break;

  case 75:
#line 387 "Grammar.y"
    {
    parser->listAllServers(yyvsp[-1]);
;}
    break;

  case 76:
#line 391 "Grammar.y"
    {
    parser->usage("server", "list");
;}
    break;

  case 77:
#line 395 "Grammar.y"
    {
    parser->showFile("server", yyvsp[-1]);
;}
    break;

  case 78:
#line 399 "Grammar.y"
    {
    parser->usage("server", "show");
;}
    break;

  case 79:
#line 403 "Grammar.y"
    {
    parser->endpointsAdapter(yyvsp[-1]);
;}
    break;

  case 80:
#line 407 "Grammar.y"
    {
    parser->usage("adapter", "endpoints");
;}
    break;

  case 81:
#line 411 "Grammar.y"
    {
    parser->removeAdapter(yyvsp[-1]);
;}
    break;

  case 82:
#line 415 "Grammar.y"
    {
    parser->usage("adapter", "remove");
;}
    break;

  case 83:
#line 419 "Grammar.y"
    {
    parser->listAllAdapters(yyvsp[-1]);
;}
    break;

  case 84:
#line 423 "Grammar.y"
    {
    parser->usage("adapter", "list");
;}
    break;

  case 85:
#line 427 "Grammar.y"
    {
    parser->addObject(yyvsp[-1]);
;}
    break;

  case 86:
#line 431 "Grammar.y"
    {
    parser->usage("object", "add");
;}
    break;

  case 87:
#line 435 "Grammar.y"
    {
    parser->removeObject(yyvsp[-1]);
;}
    break;

  case 88:
#line 439 "Grammar.y"
    {
    parser->usage("object", "remove");
;}
    break;

  case 89:
#line 443 "Grammar.y"
    {
    parser->findObject(yyvsp[-1]);
;}
    break;

  case 90:
#line 447 "Grammar.y"
    {
    parser->usage("object", "find");
;}
    break;

  case 91:
#line 451 "Grammar.y"
    {
    parser->listObject(yyvsp[-1]);
;}
    break;

  case 92:
#line 455 "Grammar.y"
    {
    parser->usage("object", "list");
;}
    break;

  case 93:
#line 459 "Grammar.y"
    {
    parser->describeObject(yyvsp[-1]);
;}
    break;

  case 94:
#line 463 "Grammar.y"
    {
    parser->usage("object", "describe");
;}
    break;

  case 95:
#line 467 "Grammar.y"
    {
    parser->showCopying();
;}
    break;

  case 96:
#line 471 "Grammar.y"
    {
    parser->showWarranty();
;}
    break;

  case 97:
#line 475 "Grammar.y"
    {
    parser->usage(yyvsp[-1].front());
;}
    break;

  case 98:
#line 479 "Grammar.y"
    {
    parser->usage(yyvsp[-1].front());
;}
    break;

  case 99:
#line 483 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 100:
#line 487 "Grammar.y"
    {
    parser->usage(yyvsp[-2].front());
;}
    break;

  case 101:
#line 491 "Grammar.y"
    {
    yyvsp[-3].push_back(yyvsp[-2].front());
    parser->invalidCommand(yyvsp[-3]);
    yyerrok;
;}
    break;

  case 102:
#line 497 "Grammar.y"
    {
    parser->invalidCommand(yyvsp[-2]);
    yyerrok;
;}
    break;

  case 103:
#line 502 "Grammar.y"
    {
    parser->invalidCommand(yyvsp[-2]);
    yyerrok;
;}
    break;

  case 104:
#line 507 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 105:
#line 511 "Grammar.y"
    {
;}
    break;

  case 106:
#line 520 "Grammar.y"
    {
    yyval = yyvsp[0];
    yyval.push_front(yyvsp[-1].front());
;}
    break;

  case 107:
#line 525 "Grammar.y"
    {
    yyval = yyvsp[0];
    yyval.push_front(yyvsp[-1].front());
;}
    break;

  case 108:
#line 530 "Grammar.y"
    {
    yyval = yyvsp[-1];
    yyval.push_front("help");
    yyval.push_front(yyvsp[-2].front());
;}
    break;

  case 109:
#line 536 "Grammar.y"
    {
    yyval = yyvsp[-1];
    yyval.push_front("help");
    yyval.push_front(yyvsp[-2].front());
;}
    break;

  case 110:
#line 542 "Grammar.y"
    {
    yyval = YYSTYPE();
;}
    break;

  case 111:
#line 551 "Grammar.y"
    {
;}
    break;

  case 112:
#line 554 "Grammar.y"
    {
;}
    break;

  case 113:
#line 557 "Grammar.y"
    {
;}
    break;

  case 114:
#line 560 "Grammar.y"
    {
;}
    break;

  case 115:
#line 563 "Grammar.y"
    {
;}
    break;

  case 116:
#line 566 "Grammar.y"
    {
;}
    break;

  case 117:
#line 569 "Grammar.y"
    {
;}
    break;

  case 118:
#line 572 "Grammar.y"
    {
;}
    break;

  case 119:
#line 575 "Grammar.y"
    {
;}
    break;

  case 120:
#line 578 "Grammar.y"
    {
;}
    break;

  case 121:
#line 581 "Grammar.y"
    {
;}
    break;

  case 122:
#line 584 "Grammar.y"
    {
;}
    break;

  case 123:
#line 587 "Grammar.y"
    {
;}
    break;

  case 124:
#line 590 "Grammar.y"
    {
;}
    break;

  case 125:
#line 593 "Grammar.y"
    {
;}
    break;

  case 126:
#line 596 "Grammar.y"
    {
;}
    break;

  case 127:
#line 599 "Grammar.y"
    {
;}
    break;

  case 128:
#line 602 "Grammar.y"
    {
;}
    break;

  case 129:
#line 605 "Grammar.y"
    {
;}
    break;

  case 130:
#line 608 "Grammar.y"
    {
;}
    break;

  case 131:
#line 611 "Grammar.y"
    {
;}
    break;

  case 132:
#line 614 "Grammar.y"
    {
;}
    break;

  case 133:
#line 617 "Grammar.y"
    {
;}
    break;

  case 134:
#line 620 "Grammar.y"
    {
;}
    break;

  case 135:
#line 623 "Grammar.y"
    {
;}
    break;

  case 136:
#line 626 "Grammar.y"
    {
;}
    break;

  case 137:
#line 629 "Grammar.y"
    {
;}
    break;

  case 138:
#line 632 "Grammar.y"
    {
;}
    break;

  case 139:
#line 635 "Grammar.y"
    {
;}
    break;

  case 140:
#line 638 "Grammar.y"
    {
;}
    break;

  case 141:
#line 641 "Grammar.y"
    {
;}
    break;

  case 142:
#line 644 "Grammar.y"
    {
;}
    break;

  case 143:
#line 647 "Grammar.y"
    {
;}
    break;

  case 144:
#line 650 "Grammar.y"
    {
;}
    break;

  case 145:
#line 653 "Grammar.y"
    {
;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2664 "Grammar.tab.c"

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



