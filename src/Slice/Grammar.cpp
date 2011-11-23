/* A Bison parser, made from Grammar.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse slice_parse
#define yylex slice_lex
#define yyerror slice_error
#define yylval slice_lval
#define yychar slice_char
#define yydebug slice_debug
#define yynerrs slice_nerrs
# define	ICE_MODULE	257
# define	ICE_CLASS	258
# define	ICE_INTERFACE	259
# define	ICE_EXCEPTION	260
# define	ICE_STRUCT	261
# define	ICE_SEQUENCE	262
# define	ICE_DICTIONARY	263
# define	ICE_ENUM	264
# define	ICE_OUT	265
# define	ICE_EXTENDS	266
# define	ICE_IMPLEMENTS	267
# define	ICE_THROWS	268
# define	ICE_VOID	269
# define	ICE_BYTE	270
# define	ICE_BOOL	271
# define	ICE_SHORT	272
# define	ICE_INT	273
# define	ICE_LONG	274
# define	ICE_FLOAT	275
# define	ICE_DOUBLE	276
# define	ICE_STRING	277
# define	ICE_OBJECT	278
# define	ICE_LOCAL_OBJECT	279
# define	ICE_LOCAL	280
# define	ICE_CONST	281
# define	ICE_FALSE	282
# define	ICE_TRUE	283
# define	ICE_NONMUTATING	284
# define	ICE_IDEMPOTENT	285
# define	ICE_SCOPE_DELIMITER	286
# define	ICE_IDENTIFIER	287
# define	ICE_STRING_LITERAL	288
# define	ICE_INTEGER_LITERAL	289
# define	ICE_FLOATING_POINT_LITERAL	290
# define	ICE_IDENT_OP	291
# define	ICE_KEYWORD_OP	292
# define	ICE_METADATA_OPEN	293
# define	ICE_METADATA_CLOSE	294
# define	ICE_GLOBAL_METADATA_OPEN	295
# define	ICE_GLOBAL_METADATA_CLOSE	296

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

#ifndef YYSTYPE
# define YYSTYPE int
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		262
#define	YYFLAG		-32768
#define	YYNTBASE	52

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 296 ? yytranslate[x] : 118)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     6,    10,    11,    12,    16,    17,    23,
      24,    29,    32,    33,    35,    37,    39,    41,    43,    45,
      47,    49,    51,    53,    55,    57,    59,    60,    67,    70,
      73,    76,    77,    85,    88,    89,    94,    98,   101,   102,
     105,   107,   110,   113,   116,   117,   124,   129,   133,   136,
     137,   139,   142,   145,   148,   149,   158,   161,   162,   165,
     166,   171,   175,   178,   179,   181,   184,   186,   188,   190,
     193,   197,   201,   204,   208,   212,   213,   219,   220,   226,
     228,   230,   233,   236,   239,   240,   248,   252,   254,   256,
     259,   260,   265,   269,   272,   273,   275,   279,   281,   283,
     285,   292,   299,   308,   317,   320,   323,   324,   331,   335,
     337,   339,   341,   342,   344,   345,   346,   350,   356,   361,
     368,   372,   378,   381,   382,   384,   387,   391,   393,   395,
     397,   399,   401,   403,   405,   407,   409,   412,   414,   416,
     419,   422,   424,   428,   430,   432,   433,   435,   437,   439,
     441,   443,   445,   451,   456,   458,   460,   462,   464,   466,
     468,   470,   472,   474,   476,   478,   480,   482,   484,   486,
     488,   490,   492,   494,   496,   498,   500,   502,   504,   506,
     508,   510,   512
};
static const short yyrhs[] =
{
      55,     0,    41,   113,    42,     0,    39,   113,    40,     0,
       0,     0,    53,    56,    55,     0,     0,    54,    59,    57,
      43,    55,     0,     0,     1,    43,    58,    55,     0,    54,
      59,     0,     0,    60,     0,    77,     0,    78,     0,    91,
       0,    92,     0,    63,     0,    64,     0,    71,     0,    72,
       0,   100,     0,   101,     0,   103,     0,   116,     0,     0,
       3,    33,    61,    44,    55,    45,     0,     6,    33,     0,
       6,   117,     0,   114,    62,     0,     0,   114,    62,    66,
      65,    44,    67,    45,     0,    12,   110,     0,     0,    54,
      69,    43,    67,     0,     1,    43,    67,     0,    54,    69,
       0,     0,   111,    33,     0,    83,     0,     7,    33,     0,
       7,   117,     0,   114,    70,     0,     0,   114,    70,    73,
      44,    74,    45,     0,    54,    75,    43,    74,     0,     1,
      43,    74,     0,    54,    75,     0,     0,    83,     0,     4,
      33,     0,     4,   117,     0,   114,    76,     0,     0,   114,
      76,    80,    81,    79,    44,    82,    45,     0,    12,   110,
       0,     0,    13,    94,     0,     0,    54,    89,    43,    82,
       0,     1,    43,    82,     0,    54,    89,     0,     0,    68,
       0,   111,   117,     0,   111,     0,   111,     0,    15,     0,
      84,    37,     0,    30,    84,    37,     0,    31,    84,    37,
       0,    84,    38,     0,    30,    84,    38,     0,    31,    84,
      38,     0,     0,    85,   108,    46,    87,   109,     0,     0,
      85,     1,    46,    88,   109,     0,    83,     0,    86,     0,
       5,    33,     0,     5,   117,     0,   114,    90,     0,     0,
     114,    90,    95,    93,    44,    96,    45,     0,   110,    47,
      94,     0,   110,     0,    24,     0,    12,    94,     0,     0,
      54,    97,    43,    96,     0,     1,    43,    96,     0,    54,
      97,     0,     0,    86,     0,    99,    47,    98,     0,    99,
       0,   110,     0,   117,     0,   114,     8,    48,   111,    49,
      33,     0,   114,     8,    48,   111,    49,   117,     0,   114,
       9,    48,   111,    47,   111,    49,    33,     0,   114,     9,
      48,   111,    47,   111,    49,   117,     0,    10,    33,     0,
      10,   117,     0,     0,   114,   102,   104,    44,   105,    45,
       0,   106,    47,   105,     0,   106,     0,    33,     0,   117,
       0,     0,    11,     0,     0,     0,   107,    54,    68,     0,
     108,    47,   107,    54,    68,     0,   107,    54,   111,   117,
       0,   108,    47,   107,    54,   111,   117,     0,   107,    54,
     111,     0,   108,    47,   107,    54,   111,     0,    14,    98,
       0,     0,    33,     0,    32,    33,     0,   110,    32,    33,
       0,    16,     0,    17,     0,    18,     0,    19,     0,    20,
       0,    21,     0,    22,     0,    23,     0,    24,     0,    24,
      50,     0,    25,     0,   110,     0,   110,    50,     0,    34,
     112,     0,    34,     0,   112,    47,   113,     0,   112,     0,
      26,     0,     0,    35,     0,    36,     0,   110,     0,    34,
       0,    28,     0,    29,     0,    27,   111,    33,    51,   115,
       0,    27,   111,    51,   115,     0,     3,     0,     4,     0,
       5,     0,     6,     0,     7,     0,     8,     0,     9,     0,
      10,     0,    11,     0,    12,     0,    13,     0,    14,     0,
      15,     0,    16,     0,    17,     0,    18,     0,    19,     0,
      20,     0,    21,     0,    22,     0,    23,     0,    24,     0,
      25,     0,    26,     0,    27,     0,    28,     0,    29,     0,
      30,     0,    31,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   102,   110,   119,   123,   132,   132,   141,   141,   152,
     152,   157,   161,   169,   173,   177,   181,   185,   189,   193,
     197,   201,   205,   209,   213,   217,   226,   226,   259,   263,
     274,   284,   284,   311,   319,   328,   337,   340,   344,   352,
     365,   371,   375,   386,   396,   396,   432,   441,   444,   448,
     456,   462,   466,   477,   490,   490,   530,   564,   573,   577,
     586,   595,   598,   602,   610,   633,   655,   681,   682,   691,
     715,   739,   763,   787,   811,   840,   840,   862,   862,   885,
     886,   892,   896,   907,   921,   921,   956,   991,  1026,  1036,
    1040,  1049,  1058,  1061,  1065,  1073,  1079,  1086,  1098,  1110,
    1121,  1129,  1143,  1152,  1167,  1171,  1182,  1182,  1210,  1216,
    1224,  1236,  1243,  1253,  1259,  1270,  1273,  1291,  1309,  1321,
    1333,  1344,  1360,  1364,  1373,  1376,  1382,  1395,  1399,  1403,
    1407,  1411,  1415,  1419,  1423,  1427,  1431,  1435,  1439,  1458,
    1499,  1505,  1513,  1520,  1532,  1538,  1549,  1559,  1569,  1598,
    1606,  1614,  1627,  1634,  1646,  1649,  1652,  1655,  1658,  1661,
    1664,  1667,  1670,  1673,  1676,  1679,  1682,  1685,  1688,  1691,
    1694,  1697,  1700,  1703,  1706,  1709,  1712,  1715,  1718,  1721,
    1724,  1727,  1730
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "ICE_MODULE", "ICE_CLASS", "ICE_INTERFACE", 
  "ICE_EXCEPTION", "ICE_STRUCT", "ICE_SEQUENCE", "ICE_DICTIONARY", 
  "ICE_ENUM", "ICE_OUT", "ICE_EXTENDS", "ICE_IMPLEMENTS", "ICE_THROWS", 
  "ICE_VOID", "ICE_BYTE", "ICE_BOOL", "ICE_SHORT", "ICE_INT", "ICE_LONG", 
  "ICE_FLOAT", "ICE_DOUBLE", "ICE_STRING", "ICE_OBJECT", 
  "ICE_LOCAL_OBJECT", "ICE_LOCAL", "ICE_CONST", "ICE_FALSE", "ICE_TRUE", 
  "ICE_NONMUTATING", "ICE_IDEMPOTENT", "ICE_SCOPE_DELIMITER", 
  "ICE_IDENTIFIER", "ICE_STRING_LITERAL", "ICE_INTEGER_LITERAL", 
  "ICE_FLOATING_POINT_LITERAL", "ICE_IDENT_OP", "ICE_KEYWORD_OP", 
  "ICE_METADATA_OPEN", "ICE_METADATA_CLOSE", "ICE_GLOBAL_METADATA_OPEN", 
  "ICE_GLOBAL_METADATA_CLOSE", "';'", "'{'", "'}'", "')'", "','", "'<'", 
  "'>'", "'*'", "'='", "start", "global_meta_data", "meta_data", 
  "definitions", "@1", "@2", "@3", "definition", "module_def", "@4", 
  "exception_id", "exception_decl", "exception_def", "@5", 
  "exception_extends", "exception_exports", "type_id", "exception_export", 
  "struct_id", "struct_decl", "struct_def", "@6", "struct_exports", 
  "struct_export", "class_id", "class_decl", "class_def", "@7", 
  "class_extends", "implements", "class_exports", "data_member", 
  "return_type", "operation_preamble", "operation", "@8", "@9", 
  "class_export", "interface_id", "interface_decl", "interface_def", 
  "@10", "interface_list", "interface_extends", "interface_exports", 
  "interface_export", "exception_list", "exception", "sequence_def", 
  "dictionary_def", "enum_id", "enum_def", "@11", "enumerator_list", 
  "enumerator", "out_qualifier", "parameters", "throws", "scoped_name", 
  "type", "string_literal", "string_list", "local_qualifier", 
  "const_initializer", "const_def", "keyword", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    52,    53,    54,    54,    56,    55,    57,    55,    58,
      55,    55,    55,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    61,    60,    62,    62,
      63,    65,    64,    66,    66,    67,    67,    67,    67,    68,
      69,    70,    70,    71,    73,    72,    74,    74,    74,    74,
      75,    76,    76,    77,    79,    78,    80,    80,    81,    81,
      82,    82,    82,    82,    83,    83,    83,    84,    84,    85,
      85,    85,    85,    85,    85,    87,    86,    88,    86,    89,
      89,    90,    90,    91,    93,    92,    94,    94,    94,    95,
      95,    96,    96,    96,    96,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   104,   103,   105,   105,
     106,   106,   106,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   115,   115,
     115,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     3,     3,     0,     0,     3,     0,     5,     0,
       4,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     2,     2,
       2,     0,     7,     2,     0,     4,     3,     2,     0,     2,
       1,     2,     2,     2,     0,     6,     4,     3,     2,     0,
       1,     2,     2,     2,     0,     8,     2,     0,     2,     0,
       4,     3,     2,     0,     1,     2,     1,     1,     1,     2,
       3,     3,     2,     3,     3,     0,     5,     0,     5,     1,
       1,     2,     2,     2,     0,     7,     3,     1,     1,     2,
       0,     4,     3,     2,     0,     1,     3,     1,     1,     1,
       6,     6,     8,     8,     2,     2,     0,     6,     3,     1,
       1,     1,     0,     1,     0,     0,     3,     5,     4,     6,
       3,     5,     2,     0,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       2,     1,     3,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     5,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     0,     0,     0,     5,   145,     1,     9,   141,   143,
       0,     0,     0,     0,   144,     0,    11,    13,    18,    19,
      20,    21,    14,    15,    16,    17,    22,    23,    24,     0,
      25,     0,   140,     0,     3,     2,     6,    26,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   137,     0,   124,
     138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    43,    53,    83,   106,    10,   142,     0,   136,   125,
       0,   139,     0,     0,     0,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,    51,    52,    81,    82,    28,    29,
      41,    42,     0,     0,   104,   105,     0,    31,     0,     0,
      59,     0,    84,     0,     0,   126,     0,   150,   151,   149,
     146,   147,   148,   153,     8,     0,     0,    33,     0,     0,
      56,     0,    54,    88,    89,    87,     0,   112,     0,   152,
       0,     0,     0,     0,     0,     0,    58,     0,     0,     0,
     110,     0,   109,   111,    27,   100,   101,     0,     0,     0,
       0,     0,    64,    48,    50,    66,    45,     0,    86,     0,
       0,     0,   107,   112,     0,     0,    37,    40,    32,    47,
       0,    39,    65,     0,     0,     0,     0,    68,     0,     0,
       0,     0,    95,    93,    67,    85,   108,   102,   103,    36,
       0,    46,     0,    79,    80,    62,    66,    55,    92,     0,
       0,    69,    72,     0,   113,     4,     0,     0,    35,    61,
       0,    70,    73,    71,    74,    77,     0,    75,   114,    91,
      60,   123,   116,   120,   123,     4,     0,    78,   118,    76,
       0,   122,    97,    98,    99,   117,   121,     0,   119,    96,
       0,     0,     0
};

static const short yydefgoto[] =
{
     260,     4,     5,     6,    12,    52,    31,    16,    17,    67,
      60,    18,    19,   138,   117,   170,   172,   186,    61,    20,
      21,   118,   155,   173,    62,    22,    23,   157,   120,   142,
     195,   174,   200,   201,   202,   244,   241,   215,    63,    24,
      25,   146,   144,   122,   181,   203,   251,   252,    26,    27,
      64,    28,   123,   161,   162,   225,   226,   247,    50,   204,
       9,    10,    29,   133,    30,   163
};

static const short yypact[] =
{
     331,    50,    67,    67,-32768,    37,-32768,-32768,    67,    62,
      64,    70,    12,    78,-32768,   722,    72,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   193,
  -32768,    12,-32768,    67,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    63,-32768,    83,-32768,
      -8,    15,    74,   437,   468,   499,   530,    71,    73,   561,
      -1,    87,    -3,    11,-32768,-32768,-32768,    88,-32768,-32768,
     101,-32768,    86,    94,    12,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   722,   722,-32768,-32768,     3,-32768,   106,     3,
     125,    57,-32768,   107,    69,-32768,    94,-32768,-32768,-32768,
  -32768,-32768,   120,-32768,-32768,   104,   108,   120,   114,   258,
     120,    57,-32768,-32768,-32768,    56,   115,   592,   116,-32768,
     623,   722,   288,   117,   722,   119,-32768,   118,    57,   192,
  -32768,   121,   122,-32768,-32768,-32768,-32768,   123,   130,   722,
     131,   258,-32768,   132,-32768,   654,-32768,   225,-32768,   134,
     329,   133,-32768,   592,   685,   288,   137,-32768,-32768,-32768,
     258,-32768,-32768,   138,   329,   139,   192,-32768,   704,   704,
      24,   124,-32768,   140,-32768,-32768,-32768,-32768,-32768,-32768,
     288,-32768,   225,-32768,-32768,   143,   370,-32768,-32768,    45,
      54,-32768,-32768,   136,-32768,   128,   -17,   192,-32768,-32768,
     225,-32768,-32768,-32768,-32768,-32768,   722,-32768,   157,-32768,
  -32768,   173,-32768,   654,   173,   128,   406,-32768,-32768,-32768,
     722,-32768,   141,   120,-32768,-32768,   654,   406,-32768,-32768,
     189,   190,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,  -125,    -6,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -154,  -156,-32768,-32768,-32768,
  -32768,-32768,  -145,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    -180,  -136,   -92,-32768,     0,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   -74,-32768,  -168,-32768,   -66,-32768,-32768,-32768,
  -32768,-32768,-32768,    13,-32768,   -34,-32768,   -26,   -72,   -15,
     211,     4,-32768,   102,-32768,   -51
};


#define	YYLAST		755


static const short yytable[] =
{
      51,   132,   105,   107,   109,   111,    36,    11,   115,   119,
     -57,   116,   -12,     1,   154,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,   121,    70,    65,   189,   169,   218,   237,
     238,   209,   229,   187,   180,    48,    49,    66,    -4,    -4,
      13,   -57,    71,   -34,   137,   211,   154,   140,    72,   145,
     240,     2,   194,     3,   132,   -90,   228,   -12,   213,   239,
     169,   221,   222,    14,    15,   154,    73,   156,   134,   145,
       1,   180,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
     242,   143,   231,   232,   178,   169,   145,   194,    70,    48,
      49,   233,   234,     7,   255,    -4,    -4,   135,   136,   166,
     236,     8,   180,   158,    34,   194,   219,   220,     2,    33,
       3,    37,    35,    68,   -12,    -7,    69,    74,   148,   112,
     250,   113,   127,   128,   192,   223,    48,    49,   129,   130,
     131,   -44,   124,   208,   125,   224,   167,   126,   141,   175,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     139,   147,    70,   150,   175,   151,  -114,  -114,   152,   159,
     171,   164,   177,  -114,   176,   192,   182,     2,   224,   183,
    -115,  -115,   184,   185,   253,   190,   188,   196,   205,   216,
     210,   212,   235,   227,   217,   253,   230,   246,   257,   261,
     262,   259,   248,   179,   214,   254,   206,    53,    54,    55,
      56,    57,    58,    59,   245,   258,   254,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,   249,    32,
       0,   243,    -4,    -4,    -4,    -4,   193,     0,   149,     0,
       0,     2,     0,     0,     0,   256,     0,   -94,     0,     0,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,     0,     0,     0,     0,    -4,    -4,    -4,    -4,   153,
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
     -63,     0,     0,     0,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,     0,     0,     0,     0,     0,   168,
      -4,    -4,     0,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     0,   -49,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,     0,     0,     0,     0,     0,     0,
      -4,    -4,     0,     0,     0,     0,     0,     2,     0,     0,
       0,   -12,     1,   -38,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,     0,     0,   197,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    -4,    -4,   198,
     199,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     3,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   191,     0,     0,     0,   -67,   -67,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    48,    49,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     104,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   106,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,   108,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   110,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,     0,   114,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,   160,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,   165,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,   191,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,   207,   197,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,     0,     0,     0,     0,    48,    49,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
       0,     0,     0,     0,    48,    49
};

static const short yycheck[] =
{
      15,    73,    53,    54,    55,    56,    12,     3,    59,    12,
      13,    12,     0,     1,   139,     3,     4,     5,     6,     7,
       8,     9,    10,    12,    32,    31,   171,   152,   196,    46,
      47,   185,   212,   169,   159,    32,    33,    33,    26,    27,
       3,    44,    50,    44,   116,   190,   171,   119,    33,   121,
     230,    39,   177,    41,   126,    44,   210,    45,   194,   227,
     185,    37,    38,    26,    27,   190,    51,   141,    74,   141,
       1,   196,     3,     4,     5,     6,     7,     8,     9,    10,
     236,    24,    37,    38,   158,   210,   158,   212,    32,    32,
      33,    37,    38,    43,   250,    26,    27,   112,   113,   150,
     225,    34,   227,    47,    40,   230,   198,   199,    39,    47,
      41,    33,    42,    50,    45,    43,    33,    43,   124,    48,
     245,    48,    28,    29,   175,     1,    32,    33,    34,    35,
      36,    44,    44,   184,    33,    11,   151,    51,    13,   154,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      44,    44,    32,    49,   169,    47,    32,    33,    44,    44,
      43,    45,    44,    39,    45,   216,    45,    39,    11,    47,
      46,    47,    49,    43,   246,    43,    45,    43,    45,   194,
      43,    43,    46,    43,    45,   257,    43,    14,    47,     0,
       0,   257,   243,     1,   194,   246,   183,     4,     5,     6,
       7,     8,     9,    10,   238,   256,   257,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   244,     8,
      -1,   236,    30,    31,    32,    33,     1,    -1,   126,    -1,
      -1,    39,    -1,    -1,    -1,   250,    -1,    45,    -1,    -1,
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
#define YYPURE 1

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

case 1:
#line 103 "Grammar.y"
{
;
    break;}
case 2:
#line 111 "Grammar.y"
{
    yyval = yyvsp[-1];
;
    break;}
case 3:
#line 120 "Grammar.y"
{
    yyval = yyvsp[-1];
;
    break;}
case 4:
#line 124 "Grammar.y"
{
    yyval = new StringListTok;
;
    break;}
case 5:
#line 133 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[0]);
    if(!metaData->v.empty())
    {
        unit->setGlobalMetaData(metaData->v);
    }
;
    break;}
case 7:
#line 142 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-1]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[0]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
    unit->setSeenDefinition();
;
    break;}
case 9:
#line 153 "Grammar.y"
{
    yyerrok;
;
    break;}
case 11:
#line 158 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 12:
#line 162 "Grammar.y"
{
;
    break;}
case 13:
#line 170 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ModulePtr::dynamicCast(yyvsp[0]));
;
    break;}
case 14:
#line 174 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 15:
#line 178 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 16:
#line 182 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 17:
#line 186 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 18:
#line 190 "Grammar.y"
{
    assert(yyvsp[0] == 0);
;
    break;}
case 19:
#line 194 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ExceptionPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 20:
#line 198 "Grammar.y"
{
    assert(yyvsp[0] == 0);
;
    break;}
case 21:
#line 202 "Grammar.y"
{
    assert(yyvsp[0] == 0 || StructPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 22:
#line 206 "Grammar.y"
{
    assert(yyvsp[0] == 0 || SequencePtr::dynamicCast(yyvsp[0]));
;
    break;}
case 23:
#line 210 "Grammar.y"
{
    assert(yyvsp[0] == 0 || DictionaryPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 24:
#line 214 "Grammar.y"
{
    assert(yyvsp[0] == 0 || EnumPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 25:
#line 218 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ConstPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 26:
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
;
    break;}
case 27:
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
;
    break;}
case 28:
#line 260 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 29:
#line 264 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = yyvsp[0];
;
    break;}
case 30:
#line 275 "Grammar.y"
{
    unit->error("exceptions cannot be forward declared");
    yyval = 0;
;
    break;}
case 31:
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
;
    break;}
case 32:
#line 299 "Grammar.y"
{
    if(yyvsp[-3])
    {
	unit->popContainer();
    }
    yyval = yyvsp[-3];
;
    break;}
case 33:
#line 312 "Grammar.y"
{
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ContainedPtr contained = cont->lookupException(scoped->v);
    cont->checkIntroduced(scoped->v);
    yyval = contained;
;
    break;}
case 34:
#line 320 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 35:
#line 329 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 36:
#line 338 "Grammar.y"
{
;
    break;}
case 37:
#line 341 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 38:
#line 345 "Grammar.y"
{
;
    break;}
case 39:
#line 353 "Grammar.y"
{
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypeStringTokPtr typestring = new TypeStringTok;
    typestring->v = make_pair(type, ident->v);
    yyval = typestring;
;
    break;}
case 41:
#line 372 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 42:
#line 376 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as struct name");
    yyval = yyvsp[0];
;
    break;}
case 43:
#line 387 "Grammar.y"
{
    unit->error("structs cannot be forward declared");
    yyval = 0;
;
    break;}
case 44:
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
;
    break;}
case 45:
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
;
    break;}
case 46:
#line 433 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 47:
#line 442 "Grammar.y"
{
;
    break;}
case 48:
#line 445 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 49:
#line 449 "Grammar.y"
{
;
    break;}
case 51:
#line 463 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 52:
#line 467 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as class name");
    yyval = yyvsp[0];
;
    break;}
case 53:
#line 478 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, false, local->v);
    yyval = cl;
;
    break;}
case 54:
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
;
    break;}
case 55:
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
;
    break;}
case 56:
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
;
    break;}
case 57:
#line 565 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 58:
#line 574 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 59:
#line 578 "Grammar.y"
{
    yyval = new ClassListTok;
;
    break;}
case 60:
#line 587 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 61:
#line 596 "Grammar.y"
{
;
    break;}
case 62:
#line 599 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 63:
#line 603 "Grammar.y"
{
;
    break;}
case 64:
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
;
    break;}
case 65:
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
;
    break;}
case 66:
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
;
    break;}
case 68:
#line 683 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 69:
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
;
    break;}
case 70:
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
;
    break;}
case 71:
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
;
    break;}
case 72:
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
;
    break;}
case 73:
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
;
    break;}
case 74:
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
;
    break;}
case 75:
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
;
    break;}
case 76:
#line 853 "Grammar.y"
{
    OperationPtr op = OperationPtr::dynamicCast(yyvsp[-1]);
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v);
    }
;
    break;}
case 77:
#line 863 "Grammar.y"
{
    if(yyvsp[-2])
    {
	unit->popContainer();
    }
    yyerrok;
;
    break;}
case 78:
#line 871 "Grammar.y"
{
    OperationPtr op = OperationPtr::dynamicCast(yyvsp[-1]);
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v);
    }
;
    break;}
case 81:
#line 893 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 82:
#line 897 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as interface name");
    yyval = yyvsp[0];
;
    break;}
case 83:
#line 908 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, true, local->v);
    cont->checkIntroduced(ident->v, cl);
    yyval = cl;
;
    break;}
case 84:
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
;
    break;}
case 85:
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
;
    break;}
case 86:
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
;
    break;}
case 87:
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
;
    break;}
case 88:
#line 1027 "Grammar.y"
{
    unit->error("illegal inheritance from type Object");
    yyval = new ClassListTok;
;
    break;}
case 89:
#line 1037 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 90:
#line 1041 "Grammar.y"
{
    yyval = new ClassListTok;
;
    break;}
case 91:
#line 1050 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 92:
#line 1059 "Grammar.y"
{
;
    break;}
case 93:
#line 1062 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 94:
#line 1066 "Grammar.y"
{
;
    break;}
case 96:
#line 1080 "Grammar.y"
{
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[-2]);
    ExceptionListTokPtr exceptionList = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;
    break;}
case 97:
#line 1087 "Grammar.y"
{
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[0]);
    ExceptionListTokPtr exceptionList = new ExceptionListTok;
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;
    break;}
case 98:
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
;
    break;}
case 99:
#line 1111 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = unit->currentContainer()->createException(IceUtil::generateUUID(), 0, false);
;
    break;}
case 100:
#line 1122 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
;
    break;}
case 101:
#line 1130 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as sequence name");
;
    break;}
case 102:
#line 1144 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-7]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-4]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, valueType, local->v);
;
    break;}
case 103:
#line 1153 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-7]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-4]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, valueType, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as dictionary name");
;
    break;}
case 104:
#line 1168 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 105:
#line 1172 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumeration name");
    yyval = yyvsp[0];
;
    break;}
case 106:
#line 1183 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    EnumPtr en = cont->createEnum(ident->v, local->v);
    cont->checkIntroduced(ident->v, en);
    yyval = en;
;
    break;}
case 107:
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
;
    break;}
case 108:
#line 1211 "Grammar.y"
{
    EnumeratorListTokPtr ens = EnumeratorListTokPtr::dynamicCast(yyvsp[-2]);
    ens->v.splice(ens->v.end(), EnumeratorListTokPtr::dynamicCast(yyvsp[0])->v);
    yyval = ens;
;
    break;}
case 109:
#line 1217 "Grammar.y"
{
;
    break;}
case 110:
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
;
    break;}
case 111:
#line 1237 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumerator");
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;
    break;}
case 112:
#line 1244 "Grammar.y"
{
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;
    break;}
case 113:
#line 1254 "Grammar.y"
{
    BoolTokPtr out = new BoolTok;
    out->v = true;
    yyval = out;
;
    break;}
case 114:
#line 1260 "Grammar.y"
{
    BoolTokPtr out = new BoolTok;
    out->v = false;
    yyval = out;
;
    break;}
case 115:
#line 1271 "Grammar.y"
{
;
    break;}
case 116:
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
;
    break;}
case 117:
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
;
    break;}
case 118:
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
;
    break;}
case 119:
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
;
    break;}
case 120:
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
;
    break;}
case 121:
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
;
    break;}
case 122:
#line 1361 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 123:
#line 1365 "Grammar.y"
{
    yyval = new ExceptionListTok;
;
    break;}
case 124:
#line 1374 "Grammar.y"
{
;
    break;}
case 125:
#line 1377 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ident->v = "::" + ident->v;
    yyval = ident;
;
    break;}
case 126:
#line 1383 "Grammar.y"
{
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    scoped->v += "::";
    scoped->v += ident->v;
    yyval = scoped;
;
    break;}
case 127:
#line 1396 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindByte);
;
    break;}
case 128:
#line 1400 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindBool);
;
    break;}
case 129:
#line 1404 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindShort);
;
    break;}
case 130:
#line 1408 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindInt);
;
    break;}
case 131:
#line 1412 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindLong);
;
    break;}
case 132:
#line 1416 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindFloat);
;
    break;}
case 133:
#line 1420 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindDouble);
;
    break;}
case 134:
#line 1424 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindString);
;
    break;}
case 135:
#line 1428 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindObject);
;
    break;}
case 136:
#line 1432 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindObjectProxy);
;
    break;}
case 137:
#line 1436 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindLocalObject);
;
    break;}
case 138:
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
;
    break;}
case 139:
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
;
    break;}
case 140:
#line 1500 "Grammar.y"
{
    StringTokPtr str1 = StringTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr str2 = StringTokPtr::dynamicCast(yyvsp[0]);
    str1->v += str2->v;
;
    break;}
case 141:
#line 1506 "Grammar.y"
{
;
    break;}
case 142:
#line 1514 "Grammar.y"
{
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringListTokPtr stringList = StringListTokPtr::dynamicCast(yyvsp[0]);
    stringList->v.push_back(str->v);
    yyval = stringList;
;
    break;}
case 143:
#line 1521 "Grammar.y"
{
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr stringList = new StringListTok;
    stringList->v.push_back(str->v);
    yyval = stringList;
;
    break;}
case 144:
#line 1533 "Grammar.y"
{
    BoolTokPtr local = new BoolTok;
    local->v = true;
    yyval = local;
;
    break;}
case 145:
#line 1539 "Grammar.y"
{
    BoolTokPtr local = new BoolTok;
    local->v = false;
    yyval = local;
;
    break;}
case 146:
#line 1550 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindLong);
    IntegerTokPtr intVal = IntegerTokPtr::dynamicCast(yyvsp[0]);
    ostringstream sstr;
    sstr << intVal->v;
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, sstr.str());
    yyval = basestring;
;
    break;}
case 147:
#line 1560 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindDouble);
    FloatingTokPtr floatVal = FloatingTokPtr::dynamicCast(yyvsp[0]);
    ostringstream sstr;
    sstr << floatVal->v;
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, sstr.str());
    yyval = basestring;
;
    break;}
case 148:
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
;
    break;}
case 149:
#line 1599 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindString);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 150:
#line 1607 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 151:
#line 1615 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 152:
#line 1628 "Grammar.y"
{
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-3]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    yyval = unit->currentContainer()->createConst(ident->v, const_type, value->v.first, value->v.second);
;
    break;}
case 153:
#line 1635 "Grammar.y"
{
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("missing constant name");
    yyval = unit->currentContainer()->createConst(IceUtil::generateUUID(), const_type, value->v.first, value->v.second);
;
    break;}
case 154:
#line 1647 "Grammar.y"
{
;
    break;}
case 155:
#line 1650 "Grammar.y"
{
;
    break;}
case 156:
#line 1653 "Grammar.y"
{
;
    break;}
case 157:
#line 1656 "Grammar.y"
{
;
    break;}
case 158:
#line 1659 "Grammar.y"
{
;
    break;}
case 159:
#line 1662 "Grammar.y"
{
;
    break;}
case 160:
#line 1665 "Grammar.y"
{
;
    break;}
case 161:
#line 1668 "Grammar.y"
{
;
    break;}
case 162:
#line 1671 "Grammar.y"
{
;
    break;}
case 163:
#line 1674 "Grammar.y"
{
;
    break;}
case 164:
#line 1677 "Grammar.y"
{
;
    break;}
case 165:
#line 1680 "Grammar.y"
{
;
    break;}
case 166:
#line 1683 "Grammar.y"
{
;
    break;}
case 167:
#line 1686 "Grammar.y"
{
;
    break;}
case 168:
#line 1689 "Grammar.y"
{
;
    break;}
case 169:
#line 1692 "Grammar.y"
{
;
    break;}
case 170:
#line 1695 "Grammar.y"
{
;
    break;}
case 171:
#line 1698 "Grammar.y"
{
;
    break;}
case 172:
#line 1701 "Grammar.y"
{
;
    break;}
case 173:
#line 1704 "Grammar.y"
{
;
    break;}
case 174:
#line 1707 "Grammar.y"
{
;
    break;}
case 175:
#line 1710 "Grammar.y"
{
;
    break;}
case 176:
#line 1713 "Grammar.y"
{
;
    break;}
case 177:
#line 1716 "Grammar.y"
{
;
    break;}
case 178:
#line 1719 "Grammar.y"
{
;
    break;}
case 179:
#line 1722 "Grammar.y"
{
;
    break;}
case 180:
#line 1725 "Grammar.y"
{
;
    break;}
case 181:
#line 1728 "Grammar.y"
{
;
    break;}
case 182:
#line 1731 "Grammar.y"
{
;
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
#line 1735 "Grammar.y"

