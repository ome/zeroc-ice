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
     ICE_GLOBAL_METADATA_CLOSE = 297
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

#include <Slice/GrammarUtil.h>
#include <IceUtil/UUID.h>

#ifdef _WIN32
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
#line 223 "Grammar.tab.c"

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
#define YYLAST   755

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  67
/* YYNRULES -- Number of rules. */
#define YYNRULES  183
/* YYNRULES -- Number of states. */
#define YYNSTATES  262

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,    50,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      48,    51,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
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
     286,   288,   295,   302,   311,   320,   323,   326,   327,   334,
     338,   340,   342,   344,   345,   347,   348,   349,   353,   359,
     364,   371,   375,   381,   384,   385,   387,   390,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   415,   417,
     419,   422,   425,   427,   431,   433,   435,   436,   438,   440,
     442,   444,   446,   448,   454,   459,   461,   463,   465,   467,
     469,   471,   473,   475,   477,   479,   481,   483,   485,   487,
     489,   491,   493,   495,   497,   499,   501,   503,   505,   507,
     509,   511,   513,   515
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      53,     0,    -1,    56,    -1,    41,   114,    42,    -1,    39,
     114,    40,    -1,    -1,    -1,    54,    57,    56,    -1,    -1,
      55,    60,    58,    43,    56,    -1,    -1,     1,    43,    59,
      56,    -1,    55,    60,    -1,    -1,    61,    -1,    78,    -1,
      79,    -1,    92,    -1,    93,    -1,    64,    -1,    65,    -1,
      72,    -1,    73,    -1,   101,    -1,   102,    -1,   104,    -1,
     117,    -1,    -1,     3,    33,    62,    44,    56,    45,    -1,
       6,    33,    -1,     6,   118,    -1,   115,    63,    -1,    -1,
     115,    63,    67,    66,    44,    68,    45,    -1,    12,   111,
      -1,    -1,    55,    70,    43,    68,    -1,     1,    43,    68,
      -1,    55,    70,    -1,    -1,   112,    33,    -1,    84,    -1,
       7,    33,    -1,     7,   118,    -1,   115,    71,    -1,    -1,
     115,    71,    74,    44,    75,    45,    -1,    55,    76,    43,
      75,    -1,     1,    43,    75,    -1,    55,    76,    -1,    -1,
      84,    -1,     4,    33,    -1,     4,   118,    -1,   115,    77,
      -1,    -1,   115,    77,    81,    82,    80,    44,    83,    45,
      -1,    12,   111,    -1,    -1,    13,    95,    -1,    -1,    55,
      90,    43,    83,    -1,     1,    43,    83,    -1,    55,    90,
      -1,    -1,    69,    -1,   112,   118,    -1,   112,    -1,   112,
      -1,    15,    -1,    85,    37,    -1,    30,    85,    37,    -1,
      31,    85,    37,    -1,    85,    38,    -1,    30,    85,    38,
      -1,    31,    85,    38,    -1,    -1,    86,   109,    46,    88,
     110,    -1,    -1,    86,     1,    46,    89,   110,    -1,    84,
      -1,    87,    -1,     5,    33,    -1,     5,   118,    -1,   115,
      91,    -1,    -1,   115,    91,    96,    94,    44,    97,    45,
      -1,   111,    47,    95,    -1,   111,    -1,    24,    -1,    12,
      95,    -1,    -1,    55,    98,    43,    97,    -1,     1,    43,
      97,    -1,    55,    98,    -1,    -1,    87,    -1,   100,    47,
      99,    -1,   100,    -1,   111,    -1,   118,    -1,   115,     8,
      48,   112,    49,    33,    -1,   115,     8,    48,   112,    49,
     118,    -1,   115,     9,    48,   112,    47,   112,    49,    33,
      -1,   115,     9,    48,   112,    47,   112,    49,   118,    -1,
      10,    33,    -1,    10,   118,    -1,    -1,   115,   103,   105,
      44,   106,    45,    -1,   107,    47,   106,    -1,   107,    -1,
      33,    -1,   118,    -1,    -1,    11,    -1,    -1,    -1,   108,
      55,    69,    -1,   109,    47,   108,    55,    69,    -1,   108,
      55,   112,   118,    -1,   109,    47,   108,    55,   112,   118,
      -1,   108,    55,   112,    -1,   109,    47,   108,    55,   112,
      -1,    14,    99,    -1,    -1,    33,    -1,    32,    33,    -1,
     111,    32,    33,    -1,    16,    -1,    17,    -1,    18,    -1,
      19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    24,    50,    -1,    25,    -1,   111,    -1,   111,
      50,    -1,    34,   113,    -1,    34,    -1,   113,    47,   114,
      -1,   113,    -1,    26,    -1,    -1,    35,    -1,    36,    -1,
     111,    -1,    34,    -1,    28,    -1,    29,    -1,    27,   112,
      33,    51,   116,    -1,    27,   112,    51,   116,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,     7,    -1,     8,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,    18,
      -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,
      -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   102,   102,   110,   119,   124,   133,   132,   142,   141,
     153,   152,   157,   162,   169,   173,   177,   181,   185,   189,
     193,   197,   201,   205,   209,   213,   217,   227,   226,   259,
     263,   274,   285,   284,   311,   320,   328,   337,   340,   345,
     352,   365,   371,   375,   386,   397,   396,   432,   441,   444,
     449,   456,   462,   466,   477,   491,   490,   530,   565,   573,
     578,   586,   595,   598,   603,   610,   633,   655,   681,   682,
     691,   715,   739,   763,   787,   811,   841,   840,   863,   862,
     885,   886,   892,   896,   907,   922,   921,   956,   991,  1026,
    1036,  1041,  1049,  1058,  1061,  1066,  1073,  1079,  1086,  1098,
    1110,  1121,  1129,  1143,  1152,  1167,  1171,  1183,  1182,  1210,
    1216,  1224,  1236,  1244,  1253,  1260,  1271,  1273,  1291,  1309,
    1321,  1333,  1344,  1360,  1365,  1373,  1376,  1382,  1395,  1399,
    1403,  1407,  1411,  1415,  1419,  1423,  1427,  1431,  1435,  1439,
    1458,  1499,  1505,  1513,  1520,  1532,  1539,  1549,  1559,  1569,
    1598,  1606,  1614,  1627,  1634,  1646,  1649,  1652,  1655,  1658,
    1661,  1664,  1667,  1670,  1673,  1676,  1679,  1682,  1685,  1688,
    1691,  1694,  1697,  1700,  1703,  1706,  1709,  1712,  1715,  1718,
    1721,  1724,  1727,  1730
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
  "ICE_GLOBAL_METADATA_CLOSE", "';'", "'{'", "'}'", "')'", "','", "'<'",
  "'>'", "'*'", "'='", "$accept", "start", "global_meta_data", "meta_data",
  "definitions", "@1", "@2", "@3", "definition", "module_def", "@4",
  "exception_id", "exception_decl", "exception_def", "@5",
  "exception_extends", "exception_exports", "type_id", "exception_export",
  "struct_id", "struct_decl", "struct_def", "@6", "struct_exports",
  "struct_export", "class_id", "class_decl", "class_def", "@7",
  "class_extends", "implements", "class_exports", "data_member",
  "return_type", "operation_preamble", "operation", "@8", "@9",
  "class_export", "interface_id", "interface_decl", "interface_def", "@10",
  "interface_list", "interface_extends", "interface_exports",
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
     295,   296,   297,    59,   123,   125,    41,    44,    60,    62,
      42,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    52,    53,    54,    55,    55,    57,    56,    58,    56,
      59,    56,    56,    56,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    62,    61,    63,
      63,    64,    66,    65,    67,    67,    68,    68,    68,    68,
      69,    70,    71,    71,    72,    74,    73,    75,    75,    75,
      75,    76,    77,    77,    78,    80,    79,    81,    81,    82,
      82,    83,    83,    83,    83,    84,    84,    84,    85,    85,
      86,    86,    86,    86,    86,    86,    88,    87,    89,    87,
      90,    90,    91,    91,    92,    94,    93,    95,    95,    95,
      96,    96,    97,    97,    97,    97,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   105,   104,   106,
     106,   107,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   111,   111,   111,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118
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
       1,     6,     6,     8,     8,     2,     2,     0,     6,     3,
       1,     1,     1,     0,     1,     0,     0,     3,     5,     4,
       6,     3,     5,     2,     0,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     3,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     5,     4,     1,     1,     1,     1,     1,
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
     144,     0,     0,     1,     0,     0,   145,     0,    12,    14,
      19,    20,    21,    22,    15,    16,    17,    18,    23,    24,
      25,     0,    26,     0,   141,     0,     4,     3,     7,    27,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   138,
       0,   125,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    44,    54,    84,   107,    11,   143,     0,
     137,   126,     0,   140,     0,     0,     0,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,    52,    53,    82,    83,
      29,    30,    42,    43,     0,     0,   105,   106,     0,    32,
       0,     0,    60,     0,    85,     0,     0,   127,     0,   151,
     152,   150,   147,   148,   149,   154,     9,     0,     0,    34,
       0,     0,    57,     0,    55,    89,    90,    88,     0,   113,
       0,   153,     0,     0,     0,     0,     0,     0,    59,     0,
       0,     0,   111,     0,   110,   112,    28,   101,   102,     0,
       0,     0,     0,     0,    65,    49,    51,    67,    46,     0,
      87,     0,     0,     0,   108,   113,     0,     0,    38,    41,
      33,    48,     0,    40,    66,     0,     0,     0,     0,    69,
       0,     0,     0,     0,    96,    94,    68,    86,   109,   103,
     104,    37,     0,    47,     0,    80,    81,    63,    67,    56,
      93,     0,     0,    70,    73,     0,   114,     5,     0,     0,
      36,    62,     0,    71,    74,    72,    75,    78,     0,    76,
     115,    92,    61,   124,   117,   121,   124,     5,     0,    79,
     119,    77,     0,   123,    98,    99,   100,   118,   122,     0,
     120,    97
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     4,     5,     6,     7,    14,    54,    33,    18,    19,
      69,    62,    20,    21,   140,   119,   172,   174,   188,    63,
      22,    23,   120,   157,   175,    64,    24,    25,   159,   122,
     144,   197,   176,   202,   203,   204,   246,   243,   217,    65,
      26,    27,   148,   146,   124,   183,   205,   253,   254,    28,
      29,    66,    30,   125,   163,   164,   227,   228,   249,    52,
     206,    10,    11,    31,   135,    32,   165
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -181
static const short yypact[] =
{
     331,   -14,     8,     8,    31,  -181,    37,  -181,  -181,     8,
     -10,    51,    19,  -181,    12,    68,  -181,   722,    61,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,   193,  -181,    12,  -181,     8,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,    59,  -181,
      80,  -181,    -2,    29,    64,   437,   468,   499,   530,    71,
      73,   561,    -1,    90,    -3,    11,  -181,  -181,  -181,    93,
    -181,  -181,    84,  -181,    87,    94,    12,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,   722,   722,  -181,  -181,     3,  -181,
     106,     3,   138,    57,  -181,   108,    69,  -181,    94,  -181,
    -181,  -181,  -181,  -181,   121,  -181,  -181,   109,   112,   121,
     111,   258,   121,    57,  -181,  -181,  -181,    56,   116,   592,
     117,  -181,   623,   722,   288,   118,   722,   119,  -181,   122,
      57,   192,  -181,   123,   120,  -181,  -181,  -181,  -181,   126,
     129,   722,   128,   258,  -181,   133,  -181,   654,  -181,   225,
    -181,   134,   329,   135,  -181,   592,   685,   288,   139,  -181,
    -181,  -181,   258,  -181,  -181,   140,   329,   136,   192,  -181,
     704,   704,    45,   124,  -181,   141,  -181,  -181,  -181,  -181,
    -181,  -181,   288,  -181,   225,  -181,  -181,   143,   370,  -181,
    -181,    74,    78,  -181,  -181,   132,  -181,   130,    47,   192,
    -181,  -181,   225,  -181,  -181,  -181,  -181,  -181,   722,  -181,
     176,  -181,  -181,   174,  -181,   654,   174,   130,   406,  -181,
    -181,  -181,   722,  -181,   142,   121,  -181,  -181,   654,   406,
    -181,  -181
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -181,  -181,  -181,  -127,    -8,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -180,  -146,  -181,  -181,
    -181,  -181,  -181,  -147,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -148,  -138,   -69,  -181,    -6,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,   -93,  -181,  -170,  -181,   -68,  -181,  -181,
    -181,  -181,  -181,  -181,     9,  -181,   -44,  -181,   -42,   -74,
     -17,   209,    21,  -181,    91,  -181,   -53
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -117
static const short yytable[] =
{
      53,   134,   107,   109,   111,   113,    38,   211,   117,   121,
     -58,   118,   -13,     1,   156,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,   123,    12,    67,   191,   171,   220,     8,
      72,    13,   230,   189,   182,    50,    51,    35,    -5,    -5,
      15,   -58,     9,   -35,   139,   213,   156,   142,    73,   147,
     158,     2,   196,     3,   134,   -91,    68,   -13,   215,   241,
     171,    37,    74,    16,    17,   156,   231,   180,   136,   147,
       1,   182,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      75,   145,   223,   224,   242,   171,   147,   196,    72,    50,
      51,    36,   244,   239,   240,    -5,    -5,   137,   138,   168,
     238,    39,   182,   160,    -8,   196,   257,    76,     2,    70,
       3,   233,   234,    71,   -13,   235,   236,   127,   150,   114,
     252,   115,   129,   130,   194,   225,    50,    51,   131,   132,
     133,   221,   222,   210,   -45,   226,   169,   126,   128,   177,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
     141,   143,   149,    72,   177,   154,  -115,  -115,   152,   153,
     161,   173,   166,  -115,   178,   194,   179,   185,   184,     2,
    -116,  -116,   187,   190,   255,   186,   192,   198,   237,   218,
     207,   219,   212,   214,   229,   255,   232,   226,   248,   259,
     216,   261,   250,   181,   208,   256,   247,    55,    56,    57,
      58,    59,    60,    61,   251,   260,   256,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    34,   151,
       0,   245,    -5,    -5,    -5,    -5,   195,     0,     0,     0,
       0,     2,     0,     0,     0,   258,     0,   -95,     0,     0,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,     0,     0,     0,     0,    -5,    -5,    -5,    -5,   155,
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
     -64,     0,     0,     0,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,     0,     0,     0,     0,     0,   170,
      -5,    -5,     0,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     0,   -50,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,     0,     0,     0,     0,     0,     0,
      -5,    -5,     0,     0,     0,     0,     0,     2,     0,     0,
       0,   -13,     1,   -39,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,   199,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     0,     0,    -5,    -5,   200,
     201,    50,    51,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     3,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,     0,   193,     0,     0,     0,   -68,   -68,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    50,    51,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     0,
     106,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,   108,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,   110,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,     0,   112,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,     0,   116,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,   162,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,   167,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,     0,   193,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,   209,   199,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,     0,     0,    50,    51,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,     0,     0,
       0,     0,     0,     0,    50,    51
};

static const short yycheck[] =
{
      17,    75,    55,    56,    57,    58,    14,   187,    61,    12,
      13,    12,     0,     1,   141,     3,     4,     5,     6,     7,
       8,     9,    10,    12,     3,    33,   173,   154,   198,    43,
      32,     0,   212,   171,   161,    32,    33,    47,    26,    27,
       3,    44,    34,    44,   118,   192,   173,   121,    50,   123,
     143,    39,   179,    41,   128,    44,    35,    45,   196,   229,
     187,    42,    33,    26,    27,   192,   214,   160,    76,   143,
       1,   198,     3,     4,     5,     6,     7,     8,     9,    10,
      51,    24,    37,    38,   232,   212,   160,   214,    32,    32,
      33,    40,   238,    46,    47,    26,    27,   114,   115,   152,
     227,    33,   229,    47,    43,   232,   252,    43,    39,    50,
      41,    37,    38,    33,    45,    37,    38,    33,   126,    48,
     247,    48,    28,    29,   177,     1,    32,    33,    34,    35,
      36,   200,   201,   186,    44,    11,   153,    44,    51,   156,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      44,    13,    44,    32,   171,    44,    32,    33,    49,    47,
      44,    43,    45,    39,    45,   218,    44,    47,    45,    39,
      46,    47,    43,    45,   248,    49,    43,    43,    46,   196,
      45,    45,    43,    43,    43,   259,    43,    11,    14,    47,
     196,   259,   245,     1,   185,   248,   240,     4,     5,     6,
       7,     8,     9,    10,   246,   258,   259,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     9,   128,
      -1,   238,    30,    31,    32,    33,     1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,   252,    -1,    45,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    32,    33,     1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,     1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,     0,     1,    45,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    26,    27,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,    39,    41,    53,    54,    55,    56,    43,    34,
     113,   114,   114,     0,    57,     3,    26,    27,    60,    61,
      64,    65,    72,    73,    78,    79,    92,    93,   101,   102,
     104,   115,   117,    59,   113,    47,    40,    42,    56,    33,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      32,    33,   111,   112,    58,     4,     5,     6,     7,     8,
       9,    10,    63,    71,    77,    91,   103,    56,   114,    62,
      50,    33,    32,    50,    33,    51,    43,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    33,   118,    33,   118,
      33,   118,    33,   118,    48,    48,    33,   118,    12,    67,
      74,    12,    81,    12,    96,   105,    44,    33,    51,    28,
      29,    34,    35,    36,   111,   116,    56,   112,   112,   111,
      66,    44,   111,    13,    82,    24,    95,   111,    94,    44,
      56,   116,    49,    47,    44,     1,    55,    75,    95,    80,
      47,    44,    33,   106,   107,   118,    45,    33,   118,   112,
       1,    55,    68,    43,    69,    76,    84,   112,    45,    44,
      95,     1,    55,    97,    45,    47,    49,    43,    70,    84,
      45,    75,    43,    33,   118,     1,    55,    83,    43,    15,
      30,    31,    85,    86,    87,    98,   112,    45,   106,    33,
     118,    68,    43,    75,    43,    84,    87,    90,   112,    45,
      97,    85,    85,    37,    38,     1,    11,   108,   109,    43,
      68,    83,    43,    37,    38,    37,    38,    46,    55,    46,
      47,    97,    83,    89,    69,   112,    88,   108,    14,   110,
     118,   110,    55,    99,   100,   111,   118,    69,   112,    47,
     118,    99
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
#line 103 "Grammar.y"
    {
;}
    break;

  case 3:
#line 111 "Grammar.y"
    {
    yyval = yyvsp[-1];
;}
    break;

  case 4:
#line 120 "Grammar.y"
    {
    yyval = yyvsp[-1];
;}
    break;

  case 5:
#line 124 "Grammar.y"
    {
    yyval = new StringListTok;
;}
    break;

  case 6:
#line 133 "Grammar.y"
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[0]);
    if(!metaData->v.empty())
    {
        unit->setGlobalMetaData(metaData->v);
    }
;}
    break;

  case 8:
#line 142 "Grammar.y"
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
#line 153 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 12:
#line 158 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 13:
#line 162 "Grammar.y"
    {
;}
    break;

  case 14:
#line 170 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ModulePtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 15:
#line 174 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 16:
#line 178 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 17:
#line 182 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 18:
#line 186 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 19:
#line 190 "Grammar.y"
    {
    assert(yyvsp[0] == 0);
;}
    break;

  case 20:
#line 194 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ExceptionPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 21:
#line 198 "Grammar.y"
    {
    assert(yyvsp[0] == 0);
;}
    break;

  case 22:
#line 202 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || StructPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 23:
#line 206 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || SequencePtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 24:
#line 210 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || DictionaryPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 25:
#line 214 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || EnumPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 26:
#line 218 "Grammar.y"
    {
    assert(yyvsp[0] == 0 || ConstPtr::dynamicCast(yyvsp[0]));
;}
    break;

  case 27:
#line 227 "Grammar.y"
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
#line 243 "Grammar.y"
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
#line 260 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 30:
#line 264 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = yyvsp[0];
;}
    break;

  case 31:
#line 275 "Grammar.y"
    {
    unit->error("exceptions cannot be forward declared");
    yyval = 0;
;}
    break;

  case 32:
#line 285 "Grammar.y"
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
#line 299 "Grammar.y"
    {
    if(yyvsp[-3])
    {
	unit->popContainer();
    }
    yyval = yyvsp[-3];
;}
    break;

  case 34:
#line 312 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ContainedPtr contained = cont->lookupException(scoped->v);
    cont->checkIntroduced(scoped->v);
    yyval = contained;
;}
    break;

  case 35:
#line 320 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 36:
#line 329 "Grammar.y"
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
#line 338 "Grammar.y"
    {
;}
    break;

  case 38:
#line 341 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 39:
#line 345 "Grammar.y"
    {
;}
    break;

  case 40:
#line 353 "Grammar.y"
    {
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypeStringTokPtr typestring = new TypeStringTok;
    typestring->v = make_pair(type, ident->v);
    yyval = typestring;
;}
    break;

  case 42:
#line 372 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 43:
#line 376 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as struct name");
    yyval = yyvsp[0];
;}
    break;

  case 44:
#line 387 "Grammar.y"
    {
    unit->error("structs cannot be forward declared");
    yyval = 0;
;}
    break;

  case 45:
#line 397 "Grammar.y"
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
#line 410 "Grammar.y"
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
#line 433 "Grammar.y"
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
#line 442 "Grammar.y"
    {
;}
    break;

  case 49:
#line 445 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 50:
#line 449 "Grammar.y"
    {
;}
    break;

  case 52:
#line 463 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 53:
#line 467 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as class name");
    yyval = yyvsp[0];
;}
    break;

  case 54:
#line 478 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, false, local->v);
    yyval = cl;
;}
    break;

  case 55:
#line 491 "Grammar.y"
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
#line 514 "Grammar.y"
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
#line 531 "Grammar.y"
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
#line 565 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 59:
#line 574 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 60:
#line 578 "Grammar.y"
    {
    yyval = new ClassListTok;
;}
    break;

  case 61:
#line 587 "Grammar.y"
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
#line 596 "Grammar.y"
    {
;}
    break;

  case 63:
#line 599 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 64:
#line 603 "Grammar.y"
    {
;}
    break;

  case 65:
#line 611 "Grammar.y"
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
#line 634 "Grammar.y"
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
#line 656 "Grammar.y"
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
#line 683 "Grammar.y"
    {
    yyval = 0;
;}
    break;

  case 70:
#line 692 "Grammar.y"
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
#line 716 "Grammar.y"
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
#line 740 "Grammar.y"
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
#line 764 "Grammar.y"
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
#line 788 "Grammar.y"
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
#line 812 "Grammar.y"
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
#line 841 "Grammar.y"
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
#line 853 "Grammar.y"
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
#line 863 "Grammar.y"
    {
    if(yyvsp[-2])
    {
	unit->popContainer();
    }
    yyerrok;
;}
    break;

  case 79:
#line 871 "Grammar.y"
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
#line 893 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 83:
#line 897 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as interface name");
    yyval = yyvsp[0];
;}
    break;

  case 84:
#line 908 "Grammar.y"
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
#line 922 "Grammar.y"
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
#line 940 "Grammar.y"
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
#line 957 "Grammar.y"
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
#line 992 "Grammar.y"
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
#line 1027 "Grammar.y"
    {
    unit->error("illegal inheritance from type Object");
    yyval = new ClassListTok;
;}
    break;

  case 90:
#line 1037 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 91:
#line 1041 "Grammar.y"
    {
    yyval = new ClassListTok;
;}
    break;

  case 92:
#line 1050 "Grammar.y"
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
#line 1059 "Grammar.y"
    {
;}
    break;

  case 94:
#line 1062 "Grammar.y"
    {
    unit->error("`;' missing after definition");
;}
    break;

  case 95:
#line 1066 "Grammar.y"
    {
;}
    break;

  case 97:
#line 1080 "Grammar.y"
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[-2]);
    ExceptionListTokPtr exceptionList = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;}
    break;

  case 98:
#line 1087 "Grammar.y"
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[0]);
    ExceptionListTokPtr exceptionList = new ExceptionListTok;
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;}
    break;

  case 99:
#line 1099 "Grammar.y"
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
#line 1111 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = unit->currentContainer()->createException(IceUtil::generateUUID(), 0, false);
;}
    break;

  case 101:
#line 1122 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
;}
    break;

  case 102:
#line 1130 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as sequence name");
;}
    break;

  case 103:
#line 1144 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-7]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-4]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, valueType, local->v);
;}
    break;

  case 104:
#line 1153 "Grammar.y"
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-7]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-4]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, valueType, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as dictionary name");
;}
    break;

  case 105:
#line 1168 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 106:
#line 1172 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumeration name");
    yyval = yyvsp[0];
;}
    break;

  case 107:
#line 1183 "Grammar.y"
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
#line 1192 "Grammar.y"
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
#line 1211 "Grammar.y"
    {
    EnumeratorListTokPtr ens = EnumeratorListTokPtr::dynamicCast(yyvsp[-2]);
    ens->v.splice(ens->v.end(), EnumeratorListTokPtr::dynamicCast(yyvsp[0])->v);
    yyval = ens;
;}
    break;

  case 110:
#line 1217 "Grammar.y"
    {
;}
    break;

  case 111:
#line 1225 "Grammar.y"
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
#line 1237 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumerator");
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;}
    break;

  case 113:
#line 1244 "Grammar.y"
    {
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;}
    break;

  case 114:
#line 1254 "Grammar.y"
    {
    BoolTokPtr out = new BoolTok;
    out->v = true;
    yyval = out;
;}
    break;

  case 115:
#line 1260 "Grammar.y"
    {
    BoolTokPtr out = new BoolTok;
    out->v = false;
    yyval = out;
;}
    break;

  case 116:
#line 1271 "Grammar.y"
    {
;}
    break;

  case 117:
#line 1274 "Grammar.y"
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
#line 1292 "Grammar.y"
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
#line 1310 "Grammar.y"
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
#line 1322 "Grammar.y"
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
#line 1334 "Grammar.y"
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
#line 1345 "Grammar.y"
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
#line 1361 "Grammar.y"
    {
    yyval = yyvsp[0];
;}
    break;

  case 124:
#line 1365 "Grammar.y"
    {
    yyval = new ExceptionListTok;
;}
    break;

  case 125:
#line 1374 "Grammar.y"
    {
;}
    break;

  case 126:
#line 1377 "Grammar.y"
    {
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ident->v = "::" + ident->v;
    yyval = ident;
;}
    break;

  case 127:
#line 1383 "Grammar.y"
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    scoped->v += "::";
    scoped->v += ident->v;
    yyval = scoped;
;}
    break;

  case 128:
#line 1396 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindByte);
;}
    break;

  case 129:
#line 1400 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindBool);
;}
    break;

  case 130:
#line 1404 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindShort);
;}
    break;

  case 131:
#line 1408 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindInt);
;}
    break;

  case 132:
#line 1412 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindLong);
;}
    break;

  case 133:
#line 1416 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindFloat);
;}
    break;

  case 134:
#line 1420 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindDouble);
;}
    break;

  case 135:
#line 1424 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindString);
;}
    break;

  case 136:
#line 1428 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindObject);
;}
    break;

  case 137:
#line 1432 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindObjectProxy);
;}
    break;

  case 138:
#line 1436 "Grammar.y"
    {
    yyval = unit->builtin(Builtin::KindLocalObject);
;}
    break;

  case 139:
#line 1440 "Grammar.y"
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
#line 1459 "Grammar.y"
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
#line 1500 "Grammar.y"
    {
    StringTokPtr str1 = StringTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr str2 = StringTokPtr::dynamicCast(yyvsp[0]);
    str1->v += str2->v;
;}
    break;

  case 142:
#line 1506 "Grammar.y"
    {
;}
    break;

  case 143:
#line 1514 "Grammar.y"
    {
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringListTokPtr stringList = StringListTokPtr::dynamicCast(yyvsp[0]);
    stringList->v.push_back(str->v);
    yyval = stringList;
;}
    break;

  case 144:
#line 1521 "Grammar.y"
    {
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr stringList = new StringListTok;
    stringList->v.push_back(str->v);
    yyval = stringList;
;}
    break;

  case 145:
#line 1533 "Grammar.y"
    {
    BoolTokPtr local = new BoolTok;
    local->v = true;
    yyval = local;
;}
    break;

  case 146:
#line 1539 "Grammar.y"
    {
    BoolTokPtr local = new BoolTok;
    local->v = false;
    yyval = local;
;}
    break;

  case 147:
#line 1550 "Grammar.y"
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
#line 1560 "Grammar.y"
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
#line 1570 "Grammar.y"
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
#line 1599 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindString);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 151:
#line 1607 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 152:
#line 1615 "Grammar.y"
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;}
    break;

  case 153:
#line 1628 "Grammar.y"
    {
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-3]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    yyval = unit->currentContainer()->createConst(ident->v, const_type, value->v.first, value->v.second);
;}
    break;

  case 154:
#line 1635 "Grammar.y"
    {
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("missing constant name");
    yyval = unit->currentContainer()->createConst(IceUtil::generateUUID(), const_type, value->v.first, value->v.second);
;}
    break;

  case 155:
#line 1647 "Grammar.y"
    {
;}
    break;

  case 156:
#line 1650 "Grammar.y"
    {
;}
    break;

  case 157:
#line 1653 "Grammar.y"
    {
;}
    break;

  case 158:
#line 1656 "Grammar.y"
    {
;}
    break;

  case 159:
#line 1659 "Grammar.y"
    {
;}
    break;

  case 160:
#line 1662 "Grammar.y"
    {
;}
    break;

  case 161:
#line 1665 "Grammar.y"
    {
;}
    break;

  case 162:
#line 1668 "Grammar.y"
    {
;}
    break;

  case 163:
#line 1671 "Grammar.y"
    {
;}
    break;

  case 164:
#line 1674 "Grammar.y"
    {
;}
    break;

  case 165:
#line 1677 "Grammar.y"
    {
;}
    break;

  case 166:
#line 1680 "Grammar.y"
    {
;}
    break;

  case 167:
#line 1683 "Grammar.y"
    {
;}
    break;

  case 168:
#line 1686 "Grammar.y"
    {
;}
    break;

  case 169:
#line 1689 "Grammar.y"
    {
;}
    break;

  case 170:
#line 1692 "Grammar.y"
    {
;}
    break;

  case 171:
#line 1695 "Grammar.y"
    {
;}
    break;

  case 172:
#line 1698 "Grammar.y"
    {
;}
    break;

  case 173:
#line 1701 "Grammar.y"
    {
;}
    break;

  case 174:
#line 1704 "Grammar.y"
    {
;}
    break;

  case 175:
#line 1707 "Grammar.y"
    {
;}
    break;

  case 176:
#line 1710 "Grammar.y"
    {
;}
    break;

  case 177:
#line 1713 "Grammar.y"
    {
;}
    break;

  case 178:
#line 1716 "Grammar.y"
    {
;}
    break;

  case 179:
#line 1719 "Grammar.y"
    {
;}
    break;

  case 180:
#line 1722 "Grammar.y"
    {
;}
    break;

  case 181:
#line 1725 "Grammar.y"
    {
;}
    break;

  case 182:
#line 1728 "Grammar.y"
    {
;}
    break;

  case 183:
#line 1731 "Grammar.y"
    {
;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 3358 "Grammar.tab.c"

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


#line 1735 "Grammar.y"


