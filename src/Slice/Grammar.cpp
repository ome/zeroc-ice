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

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse slice_parse
#define yylex   slice_lex
#define yyerror slice_error
#define yylval  slice_lval
#define yychar  slice_char
#define yydebug slice_debug
#define yynerrs slice_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ICE_MODULE = 258,
     ICE_CLASS = 259,
     ICE_INTERFACE = 260,
     ICE_EXCEPTION = 261,
     ICE_STRUCT = 262,
     ICE_SEQUENCE = 263,
     ICE_DICTIONARY = 264,
     ICE_ENUM = 265,
     ICE_OUT = 266,
     ICE_EXTENDS = 267,
     ICE_IMPLEMENTS = 268,
     ICE_THROWS = 269,
     ICE_VOID = 270,
     ICE_BYTE = 271,
     ICE_BOOL = 272,
     ICE_SHORT = 273,
     ICE_INT = 274,
     ICE_LONG = 275,
     ICE_FLOAT = 276,
     ICE_DOUBLE = 277,
     ICE_STRING = 278,
     ICE_OBJECT = 279,
     ICE_LOCAL_OBJECT = 280,
     ICE_LOCAL = 281,
     ICE_CONST = 282,
     ICE_FALSE = 283,
     ICE_TRUE = 284,
     ICE_NONMUTATING = 285,
     ICE_IDEMPOTENT = 286,
     ICE_SCOPE_DELIMITER = 287,
     ICE_IDENTIFIER = 288,
     ICE_STRING_LITERAL = 289,
     ICE_INTEGER_LITERAL = 290,
     ICE_FLOATING_POINT_LITERAL = 291,
     ICE_IDENT_OP = 292,
     ICE_KEYWORD_OP = 293,
     ICE_METADATA_OPEN = 294,
     ICE_METADATA_CLOSE = 295,
     ICE_GLOBAL_METADATA_OPEN = 296,
     ICE_GLOBAL_METADATA_CLOSE = 297,
     BAD_CHAR = 298
   };
#endif
#define ICE_MODULE 258
#define ICE_CLASS 259
#define ICE_INTERFACE 260
#define ICE_EXCEPTION 261
#define ICE_STRUCT 262
#define ICE_SEQUENCE 263
#define ICE_DICTIONARY 264
#define ICE_ENUM 265
#define ICE_OUT 266
#define ICE_EXTENDS 267
#define ICE_IMPLEMENTS 268
#define ICE_THROWS 269
#define ICE_VOID 270
#define ICE_BYTE 271
#define ICE_BOOL 272
#define ICE_SHORT 273
#define ICE_INT 274
#define ICE_LONG 275
#define ICE_FLOAT 276
#define ICE_DOUBLE 277
#define ICE_STRING 278
#define ICE_OBJECT 279
#define ICE_LOCAL_OBJECT 280
#define ICE_LOCAL 281
#define ICE_CONST 282
#define ICE_FALSE 283
#define ICE_TRUE 284
#define ICE_NONMUTATING 285
#define ICE_IDEMPOTENT 286
#define ICE_SCOPE_DELIMITER 287
#define ICE_IDENTIFIER 288
#define ICE_STRING_LITERAL 289
#define ICE_INTEGER_LITERAL 290
#define ICE_FLOATING_POINT_LITERAL 291
#define ICE_IDENT_OP 292
#define ICE_KEYWORD_OP 293
#define ICE_METADATA_OPEN 294
#define ICE_METADATA_CLOSE 295
#define ICE_GLOBAL_METADATA_OPEN 296
#define ICE_GLOBAL_METADATA_CLOSE 297
#define BAD_CHAR 298




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

#include <Slice/GrammarUtil.h>
#include <IceUtil/UUID.h>

#ifdef _MSC_VER
// I get these warnings from some bison versions:
// warning C4102: 'yyoverflowlab' : unreferenced label
#   pragma warning( disable : 4102 )
// warning C4065: switch statement contains 'default' but no 'case' labels
#   pragma warning( disable : 4065 )
#endif

using namespace std;
using namespace Slice;

void
slice_error(const char* s)
{
    // yacc and recent versions of Bison use "syntax error" instead
    // of "parse error".

    if (strcmp(s, "parse error") == 0)
    {
	unit->error("syntax error");
    }
    else
    {
	unit->error(s);
    }
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
#line 225 "Grammar.tab.c"

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   784

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  67
/* YYNRULES -- Number of rules. */
#define YYNRULES  183
/* YYNRULES -- Number of states. */
#define YYNSTATES  266

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,    51,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      49,    52,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     9,    13,    14,    15,    19,    20,
      26,    27,    32,    35,    36,    38,    40,    42,    44,    46,
      48,    50,    52,    54,    56,    58,    60,    62,    63,    70,
      73,    76,    79,    80,    88,    91,    92,    97,   101,   104,
     105,   108,   110,   113,   116,   119,   120,   127,   132,   136,
     139,   140,   142,   145,   148,   151,   152,   161,   164,   165,
     168,   169,   174,   178,   181,   182,   184,   187,   189,   191,
     193,   196,   200,   204,   207,   211,   215,   216,   222,   223,
     229,   231,   233,   236,   239,   242,   243,   251,   255,   257,
     259,   262,   263,   268,   272,   275,   276,   278,   282,   284,
     286,   288,   296,   304,   315,   326,   329,   332,   333,   340,
     344,   346,   348,   350,   351,   353,   354,   355,   359,   365,
     370,   377,   381,   387,   390,   391,   393,   396,   400,   402,
     404,   406,   408,   410,   412,   414,   416,   418,   421,   423,
     425,   428,   431,   433,   437,   439,   441,   442,   444,   446,
     448,   450,   452,   454,   461,   467,   469,   471,   473,   475,
     477,   479,   481,   483,   485,   487,   489,   491,   493,   495,
     497,   499,   501,   503,   505,   507,   509,   511,   513,   515,
     517,   519,   521,   523
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      54,     0,    -1,    57,    -1,    41,   115,    42,    -1,    39,
     115,    40,    -1,    -1,    -1,    55,    58,    57,    -1,    -1,
      56,    61,    59,    44,    57,    -1,    -1,     1,    44,    60,
      57,    -1,    56,    61,    -1,    -1,    62,    -1,    79,    -1,
      80,    -1,    93,    -1,    94,    -1,    65,    -1,    66,    -1,
      73,    -1,    74,    -1,   102,    -1,   103,    -1,   105,    -1,
     118,    -1,    -1,     3,    33,    63,    45,    57,    46,    -1,
       6,    33,    -1,     6,   119,    -1,   116,    64,    -1,    -1,
     116,    64,    68,    67,    45,    69,    46,    -1,    12,   112,
      -1,    -1,    56,    71,    44,    69,    -1,     1,    44,    69,
      -1,    56,    71,    -1,    -1,   113,    33,    -1,    85,    -1,
       7,    33,    -1,     7,   119,    -1,   116,    72,    -1,    -1,
     116,    72,    75,    45,    76,    46,    -1,    56,    77,    44,
      76,    -1,     1,    44,    76,    -1,    56,    77,    -1,    -1,
      85,    -1,     4,    33,    -1,     4,   119,    -1,   116,    78,
      -1,    -1,   116,    78,    82,    83,    81,    45,    84,    46,
      -1,    12,   112,    -1,    -1,    13,    96,    -1,    -1,    56,
      91,    44,    84,    -1,     1,    44,    84,    -1,    56,    91,
      -1,    -1,    70,    -1,   113,   119,    -1,   113,    -1,   113,
      -1,    15,    -1,    86,    37,    -1,    30,    86,    37,    -1,
      31,    86,    37,    -1,    86,    38,    -1,    30,    86,    38,
      -1,    31,    86,    38,    -1,    -1,    87,   110,    47,    89,
     111,    -1,    -1,    87,     1,    47,    90,   111,    -1,    85,
      -1,    88,    -1,     5,    33,    -1,     5,   119,    -1,   116,
      92,    -1,    -1,   116,    92,    97,    95,    45,    98,    46,
      -1,   112,    48,    96,    -1,   112,    -1,    24,    -1,    12,
      96,    -1,    -1,    56,    99,    44,    98,    -1,     1,    44,
      98,    -1,    56,    99,    -1,    -1,    88,    -1,   101,    48,
     100,    -1,   101,    -1,   112,    -1,   119,    -1,   116,     8,
      49,    56,   113,    50,    33,    -1,   116,     8,    49,    56,
     113,    50,   119,    -1,   116,     9,    49,    56,   113,    48,
      56,   113,    50,    33,    -1,   116,     9,    49,    56,   113,
      48,    56,   113,    50,   119,    -1,    10,    33,    -1,    10,
     119,    -1,    -1,   116,   104,   106,    45,   107,    46,    -1,
     108,    48,   107,    -1,   108,    -1,    33,    -1,   119,    -1,
      -1,    11,    -1,    -1,    -1,   109,    56,    70,    -1,   110,
      48,   109,    56,    70,    -1,   109,    56,   113,   119,    -1,
     110,    48,   109,    56,   113,   119,    -1,   109,    56,   113,
      -1,   110,    48,   109,    56,   113,    -1,    14,   100,    -1,
      -1,    33,    -1,    32,    33,    -1,   112,    32,    33,    -1,
      16,    -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    24,    51,
      -1,    25,    -1,   112,    -1,   112,    51,    -1,    34,   114,
      -1,    34,    -1,   115,    48,   114,    -1,   114,    -1,    26,
      -1,    -1,    35,    -1,    36,    -1,   112,    -1,    34,    -1,
      28,    -1,    29,    -1,    27,    56,   113,    33,    52,   117,
      -1,    27,    56,   113,    52,   117,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,
      -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    30,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   104,   104,   112,   121,   126,   135,   134,   144,   143,
     155,   154,   159,   164,   171,   175,   179,   183,   187,   191,
     195,   199,   203,   207,   211,   215,   219,   229,   228,   261,
     265,   276,   287,   286,   313,   322,   330,   339,   342,   347,
     354,   367,   373,   377,   388,   399,   398,   434,   443,   446,
     451,   458,   464,   468,   479,   493,   492,   532,   567,   575,
     580,   588,   597,   600,   605,   612,   635,   657,   683,   684,
     693,   717,   758,   782,   806,   830,   860,   859,   882,   881,
     904,   905,   911,   915,   926,   941,   940,   975,  1010,  1045,
    1055,  1060,  1068,  1077,  1080,  1085,  1092,  1098,  1105,  1117,
    1129,  1140,  1149,  1164,  1175,  1192,  1196,  1208,  1207,  1235,
    1241,  1249,  1261,  1269,  1278,  1285,  1296,  1298,  1316,  1334,
    1346,  1358,  1369,  1385,  1390,  1398,  1401,  1407,  1420,  1424,
    1428,  1432,  1436,  1440,  1444,  1448,  1452,  1456,  1460,  1464,
    1483,  1524,  1530,  1538,  1545,  1557,  1564,  1574,  1584,  1594,
    1623,  1631,  1639,  1652,  1660,  1674,  1677,  1680,  1683,  1686,
    1689,  1692,  1695,  1698,  1701,  1704,  1707,  1710,  1713,  1716,
    1719,  1722,  1725,  1728,  1731,  1734,  1737,  1740,  1743,  1746,
    1749,  1752,  1755,  1758
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ICE_MODULE", "ICE_CLASS",
  "ICE_INTERFACE", "ICE_EXCEPTION", "ICE_STRUCT", "ICE_SEQUENCE",
  "ICE_DICTIONARY", "ICE_ENUM", "ICE_OUT", "ICE_EXTENDS", "ICE_IMPLEMENTS",
  "ICE_THROWS", "ICE_VOID", "ICE_BYTE", "ICE_BOOL", "ICE_SHORT", "ICE_INT",
  "ICE_LONG", "ICE_FLOAT", "ICE_DOUBLE", "ICE_STRING", "ICE_OBJECT",
  "ICE_LOCAL_OBJECT", "ICE_LOCAL", "ICE_CONST", "ICE_FALSE", "ICE_TRUE",
  "ICE_NONMUTATING", "ICE_IDEMPOTENT", "ICE_SCOPE_DELIMITER",
  "ICE_IDENTIFIER", "ICE_STRING_LITERAL", "ICE_INTEGER_LITERAL",
  "ICE_FLOATING_POINT_LITERAL", "ICE_IDENT_OP", "ICE_KEYWORD_OP",
  "ICE_METADATA_OPEN", "ICE_METADATA_CLOSE", "ICE_GLOBAL_METADATA_OPEN",
  "ICE_GLOBAL_METADATA_CLOSE", "BAD_CHAR", "';'", "'{'", "'}'", "')'",
  "','", "'<'", "'>'", "'*'", "'='", "$accept", "start",
  "global_meta_data", "meta_data", "definitions", "@1", "@2", "@3",
  "definition", "module_def", "@4", "exception_id", "exception_decl",
  "exception_def", "@5", "exception_extends", "exception_exports",
  "type_id", "exception_export", "struct_id", "struct_decl", "struct_def",
  "@6", "struct_exports", "struct_export", "class_id", "class_decl",
  "class_def", "@7", "class_extends", "implements", "class_exports",
  "data_member", "return_type", "operation_preamble", "operation", "@8",
  "@9", "class_export", "interface_id", "interface_decl", "interface_def",
  "@10", "interface_list", "interface_extends", "interface_exports",
  "interface_export", "exception_list", "exception", "sequence_def",
  "dictionary_def", "enum_id", "enum_def", "@11", "enumerator_list",
  "enumerator", "out_qualifier", "parameters", "throws", "scoped_name",
  "type", "string_literal", "string_list", "local_qualifier",
  "const_initializer", "const_def", "keyword", 0
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
     295,   296,   297,   298,    59,   123,   125,    41,    44,    60,
      62,    42,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    53,    54,    55,    56,    56,    58,    57,    59,    57,
      60,    57,    57,    57,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    63,    62,    64,
      64,    65,    67,    66,    68,    68,    69,    69,    69,    69,
      70,    71,    72,    72,    73,    75,    74,    76,    76,    76,
      76,    77,    78,    78,    79,    81,    80,    82,    82,    83,
      83,    84,    84,    84,    84,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    89,    88,    90,    88,
      91,    91,    92,    92,    93,    95,    94,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   106,   105,   107,
     107,   108,   108,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   118,   118,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     3,     0,     0,     3,     0,     5,
       0,     4,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     2,
       2,     2,     0,     7,     2,     0,     4,     3,     2,     0,
       2,     1,     2,     2,     2,     0,     6,     4,     3,     2,
       0,     1,     2,     2,     2,     0,     8,     2,     0,     2,
       0,     4,     3,     2,     0,     1,     2,     1,     1,     1,
       2,     3,     3,     2,     3,     3,     0,     5,     0,     5,
       1,     1,     2,     2,     2,     0,     7,     3,     1,     1,
       2,     0,     4,     3,     2,     0,     1,     3,     1,     1,
       1,     7,     7,    10,    10,     2,     2,     0,     6,     3,
       1,     1,     1,     0,     1,     0,     0,     3,     5,     4,
       6,     3,     5,     2,     0,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     3,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     6,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     6,   146,     2,    10,   142,
     144,     0,     0,     1,     0,     0,   145,     5,    12,    14,
      19,    20,    21,    22,    15,    16,    17,    18,    23,    24,
      25,     0,    26,     0,   141,     4,     0,     3,     7,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      44,    54,    84,   107,    11,   143,     0,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   138,     0,   125,   139,
       0,     0,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,    52,    53,    82,    83,    29,    30,    42,    43,     5,
       5,   105,   106,     0,    32,     0,     0,    60,     0,    85,
       0,     0,   137,   126,     0,   140,     0,     0,     9,     0,
       0,    34,     0,     0,    57,     0,    55,    89,    90,    88,
       0,   113,     0,   127,     0,   151,   152,   150,   147,   148,
     149,   154,     0,     0,     0,     0,     0,     0,    59,     0,
       0,     0,   111,     0,   110,   112,    28,   153,     0,     5,
       0,     0,     0,     0,    65,    49,    51,    67,    46,     0,
      87,     0,     0,     0,   108,   113,   101,   102,     0,     0,
      38,    41,    33,    48,     0,    40,    66,     0,     0,     0,
       0,    69,     0,     0,     0,     0,    96,    94,    68,    86,
     109,     0,    37,     0,    47,     0,    80,    81,    63,    67,
      56,    93,     0,     0,    70,    73,     0,   114,     5,     0,
       0,     0,    36,    62,     0,    71,    74,    72,    75,    78,
       0,    76,   115,    92,   103,   104,    61,   124,   117,   121,
     124,     5,     0,    79,   119,    77,     0,   123,    98,    99,
     100,   118,   122,     0,   120,    97
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     4,     5,     6,     7,    14,    41,    33,    18,    19,
      56,    49,    20,    21,   132,   114,   172,   174,   190,    50,
      22,    23,   115,   157,   175,    51,    24,    25,   159,   117,
     136,   199,   176,   204,   205,   206,   250,   247,   218,    52,
      26,    27,   140,   138,   119,   183,   207,   257,   258,    28,
      29,    53,    30,   120,   163,   164,   228,   229,   253,    69,
     208,    10,    11,    31,   151,    32,   165
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const short yypact[] =
{
     341,   -22,     2,     2,    61,  -179,     7,  -179,  -179,     2,
    -179,   -21,   -18,  -179,    76,    34,  -179,    60,    29,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,   119,  -179,    76,  -179,  -179,     2,  -179,  -179,  -179,
     751,    77,   447,   478,   509,   540,    55,    58,   571,    -8,
      75,   -10,     9,  -179,  -179,  -179,    85,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,    82,  -179,   101,  -179,    36,
      37,    76,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    60,
      60,  -179,  -179,    32,  -179,    90,    32,   123,    39,  -179,
      93,   330,  -179,  -179,   106,  -179,    89,    62,  -179,   751,
     751,   110,    98,   168,   110,    39,  -179,  -179,  -179,   -19,
     100,   602,   103,  -179,    62,  -179,  -179,  -179,  -179,  -179,
     110,  -179,    96,   102,   286,   107,   751,   108,  -179,   112,
      39,   220,  -179,   109,   105,  -179,  -179,  -179,   633,    60,
     114,   751,   115,   168,  -179,   116,  -179,   664,  -179,   253,
    -179,   121,   714,   117,  -179,   602,  -179,  -179,   751,   286,
     122,  -179,  -179,  -179,   168,  -179,  -179,   124,   714,   125,
     220,  -179,   733,   733,    63,    27,  -179,   126,  -179,  -179,
    -179,   128,  -179,   286,  -179,   253,  -179,  -179,   129,   380,
    -179,  -179,    72,    74,  -179,  -179,   120,  -179,    60,    66,
     220,   695,  -179,  -179,   253,  -179,  -179,  -179,  -179,  -179,
     751,  -179,   164,  -179,  -179,  -179,  -179,   162,  -179,   664,
     162,    60,   416,  -179,  -179,  -179,   751,  -179,   131,   110,
    -179,  -179,   664,   416,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -179,  -179,  -179,   -17,   -13,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -172,  -178,  -179,  -179,
    -179,  -179,  -179,  -155,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -146,  -156,   -84,  -179,    -3,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -103,  -179,  -175,  -179,   -83,  -179,  -179,
    -179,  -179,  -179,  -179,    -4,  -179,   -45,  -179,   -51,  -104,
     -24,    17,   199,  -179,    59,  -179,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -117
static const short yytable[] =
{
      40,    38,   116,   -58,   113,   102,   104,   106,   108,   131,
      15,   112,   134,   124,   139,   191,    70,   212,   193,    35,
      54,   118,     8,   150,    37,   221,    34,    36,   226,   160,
      36,   139,   158,    16,    17,   -58,     9,   -35,   227,   214,
     150,   232,   216,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,    55,   -91,   243,   139,   180,   128,  -115,
    -115,    13,   248,   137,    67,    68,  -115,    39,   124,   233,
     126,    67,    68,    -8,  -116,  -116,   -13,     1,   261,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,   125,   246,   127,
     145,   146,   129,   130,    67,    68,   147,   148,   149,     2,
     224,   225,    -5,    -5,   109,   152,   153,   110,   142,   235,
     236,   237,   238,   241,   242,     2,   156,     3,   222,   223,
     -45,    71,   -13,    42,    43,    44,    45,    46,    47,    48,
     121,   187,   177,   122,   123,   133,   135,   171,   141,   143,
     196,   144,   124,   154,   182,   161,   168,   177,   259,   166,
     169,   173,   188,   185,   178,   184,   156,   179,   189,   259,
     194,   192,   198,   209,   211,   200,   213,   239,   215,   155,
     230,   220,   171,   234,   219,   227,   252,   156,   231,   263,
     265,   210,   196,   182,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,   245,   217,   171,   251,   198,   255,
      -5,    -5,    12,   167,     0,     0,     0,     2,     0,     0,
       0,   240,   254,   182,   -50,   260,   249,   198,     0,     0,
       0,   181,     0,     0,     0,   264,   260,     0,     0,     0,
       0,     0,   262,     0,   256,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,
      -5,    -5,    -5,    -5,   197,     0,     0,     0,     0,     2,
       0,     0,     0,     0,     0,     0,   -95,     0,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,     0,
       0,     0,     0,    -5,    -5,    -5,    -5,   170,     0,     0,
       0,     0,     2,     0,     0,     0,     0,     0,     0,   -64,
       0,     0,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,     0,     0,    -5,    -5,
       0,     0,     0,     0,     0,     2,     0,     0,     0,     0,
       0,     1,   -39,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,   -13,     1,     0,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,    -5,    -5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    -5,    -5,     2,
       0,     3,     0,     0,     0,     0,   -13,     0,     0,     0,
       2,     0,     3,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     0,   195,     0,     0,     0,   -68,   -68,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    67,    68,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       0,   103,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     0,   105,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     0,   107,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,     0,   111,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,   162,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,     0,   186,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,     0,   195,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     0,   244,   201,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       0,     0,     0,     0,   202,   203,    67,    68,   201,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
       0,     0,     0,     0,     0,    67,    68,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,    67,    68
};

static const short yycheck[] =
{
      17,    14,    12,    13,    12,    42,    43,    44,    45,   113,
       3,    48,   116,    32,   118,   171,    40,   189,   173,    40,
      33,    12,    44,   127,    42,   200,     9,    48,     1,    48,
      48,   135,   135,    26,    27,    45,    34,    45,    11,   194,
     144,   213,   198,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    36,    45,   230,   160,   160,    71,    32,
      33,     0,   240,    24,    32,    33,    39,    33,    32,   215,
      33,    32,    33,    44,    47,    48,     0,     1,   256,     3,
       4,     5,     6,     7,     8,     9,    10,    51,   234,    52,
      28,    29,   109,   110,    32,    33,    34,    35,    36,    39,
      37,    38,    26,    27,    49,   129,   130,    49,   121,    37,
      38,    37,    38,    47,    48,    39,   133,    41,   202,   203,
      45,    44,    46,     4,     5,     6,     7,     8,     9,    10,
      45,   168,   156,    51,    33,    45,    13,   154,    45,    33,
     177,    52,    32,    45,   161,    45,    50,   171,   252,    46,
      48,    44,   169,    48,    46,    46,   173,    45,    44,   263,
      44,    46,   179,    46,   188,    44,    44,    47,    44,     1,
      44,    46,   189,    44,   198,    11,    14,   194,    50,    48,
     263,   185,   219,   200,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   231,   198,   213,   242,   215,   250,
      32,    33,     3,   144,    -1,    -1,    -1,    39,    -1,    -1,
      -1,   228,   249,   230,    46,   252,   240,   234,    -1,    -1,
      -1,     1,    -1,    -1,    -1,   262,   263,    -1,    -1,    -1,
      -1,    -1,   256,    -1,   251,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,     1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,     1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,     1,    46,     3,     4,     5,     6,     7,     8,     9,
      10,     0,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    39,
      -1,    41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      39,    -1,    41,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    -1,    37,    38,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    39,    41,    54,    55,    56,    57,    44,    34,
     114,   115,   115,     0,    58,     3,    26,    27,    61,    62,
      65,    66,    73,    74,    79,    80,    93,    94,   102,   103,
     105,   116,   118,    60,   114,    40,    48,    42,    57,    33,
      56,    59,     4,     5,     6,     7,     8,     9,    10,    64,
      72,    78,    92,   104,    57,   114,    63,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    32,    33,   112,
     113,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    33,   119,    33,   119,    33,   119,    33,   119,    49,
      49,    33,   119,    12,    68,    75,    12,    82,    12,    97,
     106,    45,    51,    33,    32,    51,    33,    52,    57,    56,
      56,   112,    67,    45,   112,    13,    83,    24,    96,   112,
      95,    45,    57,    33,    52,    28,    29,    34,    35,    36,
     112,   117,   113,   113,    45,     1,    56,    76,    96,    81,
      48,    45,    33,   107,   108,   119,    46,   117,    50,    48,
       1,    56,    69,    44,    70,    77,    85,   113,    46,    45,
      96,     1,    56,    98,    46,    48,    33,   119,    56,    44,
      71,    85,    46,    76,    44,    33,   119,     1,    56,    84,
      44,    15,    30,    31,    86,    87,    88,    99,   113,    46,
     107,   113,    69,    44,    76,    44,    85,    88,    91,   113,
      46,    98,    86,    86,    37,    38,     1,    11,   109,   110,
      44,    50,    69,    84,    44,    37,    38,    37,    38,    47,
      56,    47,    48,    98,    33,   119,    84,    90,    70,   113,
      89,   109,    14,   111,   119,   111,    56,   100,   101,   112,
     119,    70,   113,    48,   119,   100
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
#line 105 "Grammar.y"
    {
;}
    break;

  case 3:
#line 113 "Grammar.y"
    {
    yyval = yyvsp[-1];
;}
    break;

  case 4:
#line 122 "Grammar.y"
    {
    yyval = yyvsp[-1];
;}
    break;

  case 5:
#line 126 "Grammar.y"
    {
    yyval = new StringListTok;
;}
    break;

  case 6:
#line 135 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[0]);
    if(!metaData->v.empty())
    {
        unit->addGlobalMetaData(metaData->v);
    }
;}
    break;

  case 8:
#line 144 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-1]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[0]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
    unit->setSeenDefinition();
;}
    break;

  case 10:
#line 155 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 12:
#line 160 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 13:
#line 164 "Grammar.y"
    {
;}
    break;

  case 14:
#line 172 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ModulePtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 15:
#line 176 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 16:
#line 180 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 17:
#line 184 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 18:
#line 188 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 19:
#line 192 "Grammar.y"
    {
    assert(yyvsp[0] == 0);
;}
    break;

  case 20:
#line 196 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ExceptionPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 21:
#line 200 "Grammar.y"
    {
    assert(yyvsp[0] == 0);
;}
    break;

  case 22:
#line 204 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || StructPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 23:
#line 208 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || SequencePtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 24:
#line 212 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || DictionaryPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 25:
#line 216 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || EnumPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 26:
#line 220 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ConstPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 27:
#line 229 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ModulePtr module = cont->createModule(ident->v);
    if(module)
    {
	cont->checkIntroduced(ident->v, module);
	unit->pushContainer(module);
	yyval = module;
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 28:
#line 245 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
	yyval = yyvsp[-3];
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 29:
#line 262 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 30:
#line 266 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = yyvsp[0];
;}
    break;

  case 31:
#line 277 "Grammar.y"
    {
    unit->error("exceptions cannot be forward declared");
    yyval = 0;
;}
    break;

  case 32:
#line 287 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-1]);
    ExceptionPtr base = ExceptionPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ExceptionPtr ex = cont->createException(ident->v, base, local->v);
    if(ex)
    {
	cont->checkIntroduced(ident->v, ex);
	unit->pushContainer(ex);
    }
    yyval = ex;
;}
    break;

  case 33:
#line 301 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
    }
    yyval = yyvsp[-3];
;}
    break;

  case 34:
#line 314 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ContainedPtr contained = cont->lookupException(scoped->v);
    cont->checkIntroduced(scoped->v);
    yyval = contained;
;}
    break;

  case 35:
#line 322 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 36:
#line 331 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;}
    break;

  case 37:
#line 340 "Grammar.y"
    {
;}
    break;

  case 38:
#line 343 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 39:
#line 347 "Grammar.y"
    {
;}
    break;

  case 40:
#line 355 "Grammar.y"
    {
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypeStringTokPtr typestring = new TypeStringTok;
    typestring->v = make_pair(type, ident->v);
    yyval = typestring;
;}
    break;

  case 42:
#line 374 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 43:
#line 378 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as struct name");
    yyval = yyvsp[0];
;}
    break;

  case 44:
#line 389 "Grammar.y"
    {
    unit->error("structs cannot be forward declared");
    yyval = 0;
;}
    break;

  case 45:
#line 399 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    StructPtr st = cont->createStruct(ident->v, local->v);
    if(st)
    {
	cont->checkIntroduced(ident->v, st);
	unit->pushContainer(st);
    }
    yyval = st;
;}
    break;

  case 46:
#line 412 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
    }
    yyval = yyvsp[-3];

    //
    // Empty structures are not allowed
    //
    StructPtr st = StructPtr::dynamicCast(yyval);
    assert(st);
    if(st->dataMembers().empty())
    {
    	unit->error("struct `" + st->name() + "' must have at least one member");
    }
;}
    break;

  case 47:
#line 435 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;}
    break;

  case 48:
#line 444 "Grammar.y"
    {
;}
    break;

  case 49:
#line 447 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 50:
#line 451 "Grammar.y"
    {
;}
    break;

  case 52:
#line 465 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 53:
#line 469 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as class name");
    yyval = yyvsp[0];
;}
    break;

  case 54:
#line 480 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, false, local->v);
    yyval = cl;
;}
    break;

  case 55:
#line 493 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-3]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    ClassDefPtr base = ClassDefPtr::dynamicCast(yyvsp[-1]);
    ClassListTokPtr bases = ClassListTokPtr::dynamicCast(yyvsp[0]);
    if(base)
    {
	bases->v.push_front(base);
    }
    ClassDefPtr cl = cont->createClassDef(ident->v, false, bases->v, local->v);
    if(cl)
    {
	cont->checkIntroduced(ident->v, cl);
	unit->pushContainer(cl);
	yyval = cl;
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 56:
#line 516 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
	yyval = yyvsp[-3];
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 57:
#line 533 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    yyval = 0;
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl)
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not a class";
	    unit->error(msg);
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg);
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		yyval = def;
	    }
	}
    }
;}
    break;

  case 58:
#line 567 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 59:
#line 576 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 60:
#line 580 "Grammar.y"
    {
    yyval = new ClassListTok;
;}
    break;

  case 61:
#line 589 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;}
    break;

  case 62:
#line 598 "Grammar.y"
    {
;}
    break;

  case 63:
#line 601 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 64:
#line 605 "Grammar.y"
    {
;}
    break;

  case 65:
#line 613 "Grammar.y"
    {
    TypePtr type = TypeStringTokPtr::dynamicCast(yyvsp[0])->v.first;
    string name = TypeStringTokPtr::dynamicCast(yyvsp[0])->v.second;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    DataMemberPtr dm;
    if(cl)
    {
	dm = cl->createDataMember(name, type);
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	dm = st->createDataMember(name, type);
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	dm = ex->createDataMember(name, type);
    }
    unit->currentContainer()->checkIntroduced(name, dm);
    yyval = dm;
;}
    break;

  case 66:
#line 636 "Grammar.y"
    {
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	yyval = cl->createDataMember(name, type);
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	yyval = st->createDataMember(name, type);
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	yyval = ex->createDataMember(name, type);
    }
    assert(yyval);
    unit->error("keyword `" + name + "' cannot be used as data member name");
;}
    break;

  case 67:
#line 658 "Grammar.y"
    {
    TypePtr type = TypePtr::dynamicCast(yyvsp[0]);
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
        yyval = cl->createDataMember(IceUtil::generateUUID(), type);
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	yyval = st->createDataMember(IceUtil::generateUUID(), type);
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	yyval = ex->createDataMember(IceUtil::generateUUID(), type);
    }
    assert(yyval);
    unit->error("missing data member name");
;}
    break;

  case 69:
#line 685 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 70:
#line 694 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    yyval = op;
	}
	else
	{
	    yyval = 0;
	}
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 71:
#line 718 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    static bool firstWarning = true;  
	    
	    string msg = "the keyword 'nonmutating' is deprecated";
	    if(firstWarning)
	    {
		msg += ";\n";
		msg += "You should use instead 'idempotent' plus:\n";
		msg += " - Freeze metadata ([\"freeze:read\"], [\"freeze:write\"]) if you implement your objects with a Freeze evictor\n";
		msg += " - [\"nonmutating\"], if you need to maintain compatibility with operations that expect ";
		msg += "'Nonmutating' as operation-mode. With this metadata, the generated code sends ";
		msg += "'Nonmutating' instead of 'Idempotent'\n";
		msg += " - [\"cpp:const\"], to get a const member function on the generated C++ servant base class";

		firstWarning = false;
	    }
	    
	    unit->warning(msg); 
	    yyval = op;
	}
	else
	{
	    yyval = 0;
	}
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 72:
#line 759 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    yyval = op;
	}
	else
	{
	    yyval = 0;
	}
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 73:
#line 783 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    yyval = op;
	}
	else
	{
	    yyval = 0;
	}
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 74:
#line 807 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    yyval = op;
	}
	else
	{
	    yyval = 0;
	}
    }
    else
    {
    	yyval = 0;
    }
;}
    break;

  case 75:
#line 831 "Grammar.y"
    {
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    yyval = op;
	}
	else
	{
	    return 0;
	}
    }
    else
    {
    	yyval = 0;
    }
;}
    break;

  case 76:
#line 860 "Grammar.y"
    {
    if(yyvsp[-2])
    {
	unit->popContainer();
	yyval = yyvsp[-2];
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 77:
#line 872 "Grammar.y"
    {
    OperationPtr op = OperationPtr::dynamicCast(yyvsp[-1]);
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v);
    }
;}
    break;

  case 78:
#line 882 "Grammar.y"
    {
    if(yyvsp[-2])
    {
	unit->popContainer();
    }
    yyerrok;
;}
    break;

  case 79:
#line 890 "Grammar.y"
    {
    OperationPtr op = OperationPtr::dynamicCast(yyvsp[-1]);
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v);
    }
;}
    break;

  case 82:
#line 912 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 83:
#line 916 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as interface name");
    yyval = yyvsp[0];
;}
    break;

  case 84:
#line 927 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, true, local->v);
    cont->checkIntroduced(ident->v, cl);
    yyval = cl;
;}
    break;

  case 85:
#line 941 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-1]);
    ContainerPtr cont = unit->currentContainer();
    ClassListTokPtr bases = ClassListTokPtr::dynamicCast(yyvsp[0]);
    ClassDefPtr cl = cont->createClassDef(ident->v, true, bases->v, local->v);
    if(cl)
    {
	cont->checkIntroduced(ident->v, cl);
	unit->pushContainer(cl);
	yyval = cl;
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 86:
#line 959 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
	yyval = yyvsp[-3];
    }
    else
    {
	yyval = 0;
    }
;}
    break;

  case 87:
#line 976 "Grammar.y"
    {
    ClassListTokPtr intfs = ClassListTokPtr::dynamicCast(yyvsp[0]);
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl || !cl->isInterface())
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not an interface";
	    unit->error(msg);
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg);
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		intfs->v.push_front(def);
	    }
	}
    }
    yyval = intfs;
;}
    break;

  case 88:
#line 1011 "Grammar.y"
    {
    ClassListTokPtr intfs = new ClassListTok;
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl || !cl->isInterface())
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not an interface";
	    unit->error(msg);
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg);
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		intfs->v.push_front(def);
	    }
	}
    }
    yyval = intfs;
;}
    break;

  case 89:
#line 1046 "Grammar.y"
    {
    unit->error("illegal inheritance from type Object");
    yyval = new ClassListTok;
;}
    break;

  case 90:
#line 1056 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 91:
#line 1060 "Grammar.y"
    {
    yyval = new ClassListTok;
;}
    break;

  case 92:
#line 1069 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;}
    break;

  case 93:
#line 1078 "Grammar.y"
    {
;}
    break;

  case 94:
#line 1081 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 95:
#line 1085 "Grammar.y"
    {
;}
    break;

  case 97:
#line 1099 "Grammar.y"
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[-2]);
    ExceptionListTokPtr exceptionList = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;}
    break;

  case 98:
#line 1106 "Grammar.y"
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[0]);
    ExceptionListTokPtr exceptionList = new ExceptionListTok;
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;}
    break;

  case 99:
#line 1118 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ExceptionPtr exception = cont->lookupException(scoped->v);
    if(!exception)
    {
	exception = cont->createException(IceUtil::generateUUID(), 0, false);
    }
    cont->checkIntroduced(scoped->v, exception);
    yyval = exception;
;}
    break;

  case 100:
#line 1130 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = unit->currentContainer()->createException(IceUtil::generateUUID(), 0, false);
;}
    break;

  case 101:
#line 1141 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-6]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, metaData->v, local->v);
;}
    break;

  case 102:
#line 1150 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-6]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, metaData->v, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as sequence name");
;}
    break;

  case 103:
#line 1165 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-9]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr keyMetaData = StringListTokPtr::dynamicCast(yyvsp[-6]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-5]);
    StringListTokPtr valueMetaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, keyMetaData->v, valueType, valueMetaData->v, local->v);
;}
    break;

  case 104:
#line 1176 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-9]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr keyMetaData = StringListTokPtr::dynamicCast(yyvsp[-6]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-5]);
    StringListTokPtr valueMetaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, keyMetaData->v, valueType, valueMetaData->v, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as dictionary name");
;}
    break;

  case 105:
#line 1193 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 106:
#line 1197 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumeration name");
    yyval = yyvsp[0];
;}
    break;

  case 107:
#line 1208 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    EnumPtr en = cont->createEnum(ident->v, local->v);
    cont->checkIntroduced(ident->v, en);
    yyval = en;
;}
    break;

  case 108:
#line 1217 "Grammar.y"
    {
    EnumPtr en = EnumPtr::dynamicCast(yyvsp[-3]);
    if(en)
    {
	EnumeratorListTokPtr enumerators = EnumeratorListTokPtr::dynamicCast(yyvsp[-1]);
	if(enumerators->v.empty())
	{
	    unit->error("enum `" + en->name() + "' must have at least one enumerator");
	}
	en->setEnumerators(enumerators->v);
    }
    yyval = yyvsp[-3];
;}
    break;

  case 109:
#line 1236 "Grammar.y"
    {
    EnumeratorListTokPtr ens = EnumeratorListTokPtr::dynamicCast(yyvsp[-2]);
    ens->v.splice(ens->v.end(), EnumeratorListTokPtr::dynamicCast(yyvsp[0])->v);
    yyval = ens;
;}
    break;

  case 110:
#line 1242 "Grammar.y"
    {
;}
    break;

  case 111:
#line 1250 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    ContainerPtr cont = unit->currentContainer();
    EnumeratorPtr en = cont->createEnumerator(ident->v);
    if(en)
    {
	ens->v.push_front(en);
    }
    yyval = ens;
;}
    break;

  case 112:
#line 1262 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumerator");
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;}
    break;

  case 113:
#line 1269 "Grammar.y"
    {
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;}
    break;

  case 114:
#line 1279 "Grammar.y"
    {
    BoolTokPtr out = new BoolTok;
    out->v = true;
    yyval = out;
;}
    break;

  case 115:
#line 1285 "Grammar.y"
    {
    BoolTokPtr out = new BoolTok;
    out->v = false;
    yyval = out;
;}
    break;

  case 116:
#line 1296 "Grammar.y"
    {
;}
    break;

  case 117:
#line 1299 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
        StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-1]);
        if(!metaData->v.empty())
        {
            pd->setMetaData(metaData->v);
        }
    }
;}
    break;

  case 118:
#line 1317 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
        StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-1]);
        if(!metaData->v.empty())
        {
            pd->setMetaData(metaData->v);
        }
    }
;}
    break;

  case 119:
#line 1335 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(ident->v, type, isOutParam->v);
	unit->error("keyword `" + ident->v + "' cannot be used as parameter name");
    }
;}
    break;

  case 120:
#line 1347 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(ident->v, type, isOutParam->v);
	unit->error("keyword `" + ident->v + "' cannot be used as parameter name");
    }
;}
    break;

  case 121:
#line 1359 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[0]);
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(IceUtil::generateUUID(), type, isOutParam->v);
	unit->error("missing parameter name");
    }
;}
    break;

  case 122:
#line 1370 "Grammar.y"
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[0]);
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(IceUtil::generateUUID(), type, isOutParam->v);
	unit->error("missing parameter name");
    }
;}
    break;

  case 123:
#line 1386 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 124:
#line 1390 "Grammar.y"
    {
    yyval = new ExceptionListTok;
;}
    break;

  case 125:
#line 1399 "Grammar.y"
    {
;}
    break;

  case 126:
#line 1402 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ident->v = "::" + ident->v;
    yyval = ident;
;}
    break;

  case 127:
#line 1408 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    scoped->v += "::";
    scoped->v += ident->v;
    yyval = scoped;
;}
    break;

  case 128:
#line 1421 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindByte);
;}
    break;

  case 129:
#line 1425 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindBool);
;}
    break;

  case 130:
#line 1429 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindShort);
;}
    break;

  case 131:
#line 1433 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindInt);
;}
    break;

  case 132:
#line 1437 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindLong);
;}
    break;

  case 133:
#line 1441 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindFloat);
;}
    break;

  case 134:
#line 1445 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindDouble);
;}
    break;

  case 135:
#line 1449 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindString);
;}
    break;

  case 136:
#line 1453 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindObject);
;}
    break;

  case 137:
#line 1457 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindObjectProxy);
;}
    break;

  case 138:
#line 1461 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindLocalObject);
;}
    break;

  case 139:
#line 1465 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    if(cont)
    {
	TypeList types = cont->lookupType(scoped->v);
	if(types.empty())
	{
	    YYERROR; // Can't continue, jump to next yyerrok
	}
	cont->checkIntroduced(scoped->v);
	yyval = types.front();
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 140:
#line 1484 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-1]);
    ContainerPtr cont = unit->currentContainer();
    if(cont)
    {
	TypeList types = cont->lookupType(scoped->v);
	if(types.empty())
	{
	    YYERROR; // Can't continue, jump to next yyerrok
	}
	for(TypeList::iterator p = types.begin(); p != types.end(); ++p)
	{
	    ClassDeclPtr cl = ClassDeclPtr::dynamicCast(*p);
	    if(!cl)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' must be class or interface";
		unit->error(msg);
		YYERROR; // Can't continue, jump to next yyerrok
	    }
	    cont->checkIntroduced(scoped->v);
	    if(cl->isLocal())
	    {
		unit->error("cannot create proxy for " + cl->kindOf() + " `" + cl->name() + "'");
	    }
	    *p = new Proxy(cl);
	}
	yyval = types.front();
    }
    else
    {
        yyval = 0;
    }
;}
    break;

  case 141:
#line 1525 "Grammar.y"
    {
    StringTokPtr str1 = StringTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr str2 = StringTokPtr::dynamicCast(yyvsp[0]);
    str1->v += str2->v;
;}
    break;

  case 142:
#line 1531 "Grammar.y"
    {
;}
    break;

  case 143:
#line 1539 "Grammar.y"
    {
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr stringList = StringListTokPtr::dynamicCast(yyvsp[-2]);
    stringList->v.push_back(str->v);
    yyval = stringList;
;}
    break;

  case 144:
#line 1546 "Grammar.y"
    {
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr stringList = new StringListTok;
    stringList->v.push_back(str->v);
    yyval = stringList;
;}
    break;

  case 145:
#line 1558 "Grammar.y"
    {
    BoolTokPtr local = new BoolTok;
    local->v = true;
    yyval = local;
;}
    break;

  case 146:
#line 1564 "Grammar.y"
    {
    BoolTokPtr local = new BoolTok;
    local->v = false;
    yyval = local;
;}
    break;

  case 147:
#line 1575 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindLong);
    IntegerTokPtr intVal = IntegerTokPtr::dynamicCast(yyvsp[0]);
    ostringstream sstr;
    sstr << intVal->v;
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, sstr.str());
    yyval = basestring;
;}
    break;

  case 148:
#line 1585 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindDouble);
    FloatingTokPtr floatVal = FloatingTokPtr::dynamicCast(yyvsp[0]);
    ostringstream sstr;
    sstr << floatVal->v;
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, sstr.str());
    yyval = basestring;
;}
    break;

  case 149:
#line 1595 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    ContainedList cl = unit->currentContainer()->lookupContained(scoped->v);
    if(cl.empty())
    {
    	basestring->v = pair<SyntaxTreeBasePtr,string>(TypePtr(0), scoped->v);
    }
    else
    {
	EnumeratorPtr enumerator = EnumeratorPtr::dynamicCast(cl.front());
	if(!enumerator)
	{
	    string msg = "illegal initializer: `" + scoped->v + "' is a";
	    static const string vowels = "aeiou";
	    string kindOf = cl.front()->kindOf();
	    if(vowels.find_first_of(kindOf[0]) != string::npos)
	    {
	    	msg += "n";
	    }
	    msg += " " + kindOf;
	    unit->error(msg);
	}
	unit->currentContainer()->checkIntroduced(scoped->v, enumerator);
	basestring->v = pair<SyntaxTreeBasePtr,string>(enumerator, scoped->v);
    }
    yyval = basestring;
;}
    break;

  case 150:
#line 1624 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindString);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 151:
#line 1632 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 152:
#line 1640 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 153:
#line 1653 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-4]);
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-3]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    yyval = unit->currentContainer()->createConst(ident->v, const_type, metaData->v, value->v.first, value->v.second);
;}
    break;

  case 154:
#line 1661 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("missing constant name");
    yyval = unit->currentContainer()->createConst(IceUtil::generateUUID(), const_type, metaData->v, value->v.first,
    					       value->v.second);
;}
    break;

  case 155:
#line 1675 "Grammar.y"
    {
;}
    break;

  case 156:
#line 1678 "Grammar.y"
    {
;}
    break;

  case 157:
#line 1681 "Grammar.y"
    {
;}
    break;

  case 158:
#line 1684 "Grammar.y"
    {
;}
    break;

  case 159:
#line 1687 "Grammar.y"
    {
;}
    break;

  case 160:
#line 1690 "Grammar.y"
    {
;}
    break;

  case 161:
#line 1693 "Grammar.y"
    {
;}
    break;

  case 162:
#line 1696 "Grammar.y"
    {
;}
    break;

  case 163:
#line 1699 "Grammar.y"
    {
;}
    break;

  case 164:
#line 1702 "Grammar.y"
    {
;}
    break;

  case 165:
#line 1705 "Grammar.y"
    {
;}
    break;

  case 166:
#line 1708 "Grammar.y"
    {
;}
    break;

  case 167:
#line 1711 "Grammar.y"
    {
;}
    break;

  case 168:
#line 1714 "Grammar.y"
    {
;}
    break;

  case 169:
#line 1717 "Grammar.y"
    {
;}
    break;

  case 170:
#line 1720 "Grammar.y"
    {
;}
    break;

  case 171:
#line 1723 "Grammar.y"
    {
;}
    break;

  case 172:
#line 1726 "Grammar.y"
    {
;}
    break;

  case 173:
#line 1729 "Grammar.y"
    {
;}
    break;

  case 174:
#line 1732 "Grammar.y"
    {
;}
    break;

  case 175:
#line 1735 "Grammar.y"
    {
;}
    break;

  case 176:
#line 1738 "Grammar.y"
    {
;}
    break;

  case 177:
#line 1741 "Grammar.y"
    {
;}
    break;

  case 178:
#line 1744 "Grammar.y"
    {
;}
    break;

  case 179:
#line 1747 "Grammar.y"
    {
;}
    break;

  case 180:
#line 1750 "Grammar.y"
    {
;}
    break;

  case 181:
#line 1753 "Grammar.y"
    {
;}
    break;

  case 182:
#line 1756 "Grammar.y"
    {
;}
    break;

  case 183:
#line 1759 "Grammar.y"
    {
;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 3393 "Grammar.tab.c"

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


#line 1763 "Grammar.y"


