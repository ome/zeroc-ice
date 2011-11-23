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

#line 1 "Grammar.y"


// **********************************************************************
//
// Copyright (c) 2003-2004 ZeroC, Inc. All rights reserved.
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



#define	YYFINAL		261
#define	YYFLAG		-32768
#define	YYNTBASE	50

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 115)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,    48,     2,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      46,    49,    47,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      36,    37,    38
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     8,    12,    13,    14,    18,    19,    25,
      29,    32,    33,    35,    37,    39,    41,    43,    45,    47,
      49,    51,    53,    55,    57,    59,    60,    67,    70,    73,
      76,    77,    85,    88,    89,    94,    98,   101,   102,   105,
     107,   110,   113,   116,   117,   124,   129,   133,   136,   137,
     139,   142,   145,   148,   149,   158,   161,   162,   165,   166,
     171,   175,   178,   179,   181,   184,   186,   188,   190,   193,
     197,   201,   204,   208,   212,   213,   219,   220,   226,   228,
     230,   233,   236,   239,   240,   248,   252,   254,   256,   259,
     260,   265,   269,   272,   273,   275,   279,   281,   283,   285,
     292,   299,   308,   317,   320,   323,   324,   331,   335,   337,
     339,   341,   342,   344,   345,   346,   349,   354,   358,   364,
     367,   372,   375,   376,   378,   381,   385,   387,   389,   391,
     393,   395,   397,   399,   401,   403,   406,   408,   410,   413,
     416,   418,   422,   424,   426,   427,   429,   431,   433,   435,
     437,   439,   445,   450,   452,   454,   456,   458,   460,   462,
     464,   466,   468,   470,   472,   474,   476,   478,   480,   482,
     484,   486,   488,   490,   492,   494,   496,   498,   500,   502,
     504,   506
};
static const short yyrhs[] =
{
      53,     0,    39,    39,   110,    40,    40,     0,    39,   110,
      40,     0,     0,     0,    51,    54,    53,     0,     0,    52,
      56,    55,    41,    53,     0,     1,    41,    53,     0,    52,
      56,     0,     0,    57,     0,    74,     0,    75,     0,    88,
       0,    89,     0,    60,     0,    61,     0,    68,     0,    69,
       0,    97,     0,    98,     0,   100,     0,   113,     0,     0,
       3,    33,    58,    42,    53,    43,     0,     6,    33,     0,
       6,   114,     0,   111,    59,     0,     0,   111,    59,    63,
      62,    42,    64,    43,     0,    12,   107,     0,     0,    52,
      66,    41,    64,     0,     1,    41,    64,     0,    52,    66,
       0,     0,   108,    33,     0,    80,     0,     7,    33,     0,
       7,   114,     0,   111,    67,     0,     0,   111,    67,    70,
      42,    71,    43,     0,    52,    72,    41,    71,     0,     1,
      41,    71,     0,    52,    72,     0,     0,    80,     0,     4,
      33,     0,     4,   114,     0,   111,    73,     0,     0,   111,
      73,    77,    78,    76,    42,    79,    43,     0,    12,   107,
       0,     0,    13,    91,     0,     0,    52,    86,    41,    79,
       0,     1,    41,    79,     0,    52,    86,     0,     0,    65,
       0,   108,   114,     0,   108,     0,   108,     0,    15,     0,
      81,    37,     0,    30,    81,    37,     0,    31,    81,    37,
       0,    81,    38,     0,    30,    81,    38,     0,    31,    81,
      38,     0,     0,    82,   105,    44,    84,   106,     0,     0,
      82,     1,    44,    85,   106,     0,    80,     0,    83,     0,
       5,    33,     0,     5,   114,     0,   111,    87,     0,     0,
     111,    87,    92,    90,    42,    93,    43,     0,   107,    45,
      91,     0,   107,     0,    24,     0,    12,    91,     0,     0,
      52,    94,    41,    93,     0,     1,    41,    93,     0,    52,
      94,     0,     0,    83,     0,    96,    45,    95,     0,    96,
       0,   107,     0,   114,     0,   111,     8,    46,   108,    47,
      33,     0,   111,     8,    46,   108,    47,   114,     0,   111,
       9,    46,   108,    45,   108,    47,    33,     0,   111,     9,
      46,   108,    45,   108,    47,   114,     0,    10,    33,     0,
      10,   114,     0,     0,   111,    99,   101,    42,   102,    43,
       0,   103,    45,   102,     0,   103,     0,    33,     0,   114,
       0,     0,    11,     0,     0,     0,   104,    65,     0,   105,
      45,   104,    65,     0,   104,   108,   114,     0,   105,    45,
     104,   108,   114,     0,   104,   108,     0,   105,    45,   104,
     108,     0,    14,    95,     0,     0,    33,     0,    32,    33,
       0,   107,    32,    33,     0,    16,     0,    17,     0,    18,
       0,    19,     0,    20,     0,    21,     0,    22,     0,    23,
       0,    24,     0,    24,    48,     0,    25,     0,   107,     0,
     107,    48,     0,    34,   109,     0,    34,     0,   109,    45,
     110,     0,   109,     0,    26,     0,     0,    35,     0,    36,
       0,   107,     0,    34,     0,    28,     0,    29,     0,    27,
     108,    33,    49,   112,     0,    27,   108,    49,   112,     0,
       3,     0,     4,     0,     5,     0,     6,     0,     7,     0,
       8,     0,     9,     0,    10,     0,    11,     0,    12,     0,
      13,     0,    14,     0,    15,     0,    16,     0,    17,     0,
      18,     0,    19,     0,    20,     0,    21,     0,    22,     0,
      23,     0,    24,     0,    25,     0,    26,     0,    27,     0,
      28,     0,    29,     0,    30,     0,    31,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    98,   106,   115,   119,   128,   128,   137,   137,   148,
     152,   156,   164,   168,   172,   176,   180,   184,   188,   192,
     196,   200,   204,   208,   212,   221,   221,   244,   248,   259,
     269,   269,   294,   302,   311,   320,   323,   327,   335,   348,
     354,   358,   369,   379,   379,   413,   422,   425,   429,   437,
     443,   447,   458,   471,   471,   501,   535,   544,   548,   557,
     566,   569,   573,   581,   604,   626,   652,   653,   662,   673,
     684,   695,   706,   717,   733,   733,   748,   748,   768,   769,
     775,   779,   790,   804,   804,   829,   864,   899,   909,   913,
     922,   931,   934,   938,   946,   952,   959,   971,   983,   994,
    1002,  1016,  1025,  1040,  1044,  1055,  1055,  1083,  1089,  1097,
    1109,  1116,  1126,  1132,  1143,  1146,  1159,  1172,  1184,  1196,
    1207,  1223,  1227,  1236,  1239,  1245,  1258,  1262,  1266,  1270,
    1274,  1278,  1282,  1286,  1290,  1294,  1298,  1302,  1321,  1362,
    1368,  1376,  1383,  1395,  1401,  1412,  1422,  1432,  1461,  1469,
    1477,  1490,  1497,  1509,  1512,  1515,  1518,  1521,  1524,  1527,
    1530,  1533,  1536,  1539,  1542,  1545,  1548,  1551,  1554,  1557,
    1560,  1563,  1566,  1569,  1572,  1575,  1578,  1581,  1584,  1587,
    1590,  1593
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
  "ICE_FLOATING_POINT_LITERAL", "ICE_IDENT_OP", "ICE_KEYWORD_OP", "'['", 
  "']'", "';'", "'{'", "'}'", "')'", "','", "'<'", "'>'", "'*'", "'='", 
  "start", "global_meta_data", "meta_data", "definitions", "@1", "@2", 
  "definition", "module_def", "@3", "exception_id", "exception_decl", 
  "exception_def", "@4", "exception_extends", "exception_exports", 
  "type_id", "exception_export", "struct_id", "struct_decl", "struct_def", 
  "@5", "struct_exports", "struct_export", "class_id", "class_decl", 
  "class_def", "@6", "class_extends", "implements", "class_exports", 
  "data_member", "return_type", "operation_preamble", "operation", "@7", 
  "@8", "class_export", "interface_id", "interface_decl", "interface_def", 
  "@9", "interface_list", "interface_extends", "interface_exports", 
  "interface_export", "exception_list", "exception", "sequence_def", 
  "dictionary_def", "enum_id", "enum_def", "@10", "enumerator_list", 
  "enumerator", "out_qualifier", "parameters", "throws", "scoped_name", 
  "type", "string_literal", "string_list", "local_qualifier", 
  "const_initializer", "const_def", "keyword", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    50,    51,    52,    52,    54,    53,    55,    53,    53,
      53,    53,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    58,    57,    59,    59,    60,
      62,    61,    63,    63,    64,    64,    64,    64,    65,    66,
      67,    67,    68,    70,    69,    71,    71,    71,    71,    72,
      73,    73,    74,    76,    75,    77,    77,    78,    78,    79,
      79,    79,    79,    80,    80,    80,    81,    81,    82,    82,
      82,    82,    82,    82,    84,    83,    85,    83,    86,    86,
      87,    87,    88,    90,    89,    91,    91,    91,    92,    92,
      93,    93,    93,    93,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,   101,   100,   102,   102,   103,
     103,   103,   104,   104,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     5,     3,     0,     0,     3,     0,     5,     3,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     2,     2,     2,
       0,     7,     2,     0,     4,     3,     2,     0,     2,     1,
       2,     2,     2,     0,     6,     4,     3,     2,     0,     1,
       2,     2,     2,     0,     8,     2,     0,     2,     0,     4,
       3,     2,     0,     1,     2,     1,     1,     1,     2,     3,
       3,     2,     3,     3,     0,     5,     0,     5,     1,     1,
       2,     2,     2,     0,     7,     3,     1,     1,     2,     0,
       4,     3,     2,     0,     1,     3,     1,     1,     1,     6,
       6,     8,     8,     2,     2,     0,     6,     3,     1,     1,
       1,     0,     1,     0,     0,     2,     4,     3,     5,     2,
       4,     2,     0,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       1,     3,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     5,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     0,     0,     5,   144,     1,     0,   140,     0,   142,
       0,     0,     0,   143,     0,    10,    12,    17,    18,    19,
      20,    13,    14,    15,    16,    21,    22,    23,     0,    24,
       9,   139,     0,     0,     3,     6,    25,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   136,     0,   123,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
      42,    52,    82,   105,     0,   141,     0,   135,   124,     0,
     138,     0,     0,     0,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,    50,    51,    80,    81,    27,    28,    40,
      41,     0,     0,   103,   104,     0,    30,     0,     0,    58,
       0,    83,     0,     2,     0,   125,     0,   149,   150,   148,
     145,   146,   147,   152,     8,     0,     0,    32,     0,     0,
      55,     0,    53,    87,    88,    86,     0,   111,     0,   151,
       0,     0,     0,     0,     0,     0,     0,    57,     0,     0,
       0,   109,     0,   108,   110,    26,    99,   100,     0,     0,
       0,     0,     0,    63,    47,    49,    65,    44,     0,    85,
       0,     0,     0,   106,   111,     0,     0,    36,    39,    31,
      46,     0,    38,    64,     0,     0,     0,     0,    67,     0,
       0,     0,     0,    94,    92,    66,    84,   107,   101,   102,
      35,     0,    45,     0,    78,    79,    61,    65,    54,    91,
       0,     0,    68,    71,     0,   112,     0,     0,     0,    34,
      60,     0,    69,    72,    70,    73,    76,   115,   119,    74,
     113,    90,    59,   122,   117,   122,     0,     0,    77,    75,
     116,   120,   121,    96,    97,    98,   118,     0,    95,     0,
       0,     0
};

static const short yydefgoto[] =
{
     259,     3,     4,     5,    11,    51,    15,    16,    66,    59,
      17,    18,   138,   116,   171,   173,   187,    60,    19,    20,
     117,   156,   174,    61,    21,    22,   158,   119,   142,   196,
     175,   201,   202,   203,   245,   243,   216,    62,    23,    24,
     146,   144,   121,   182,   204,   252,   253,    25,    26,    63,
      27,   122,   162,   163,   226,   227,   248,    49,   205,     9,
      10,    28,   133,    29,   164
};

static const short yypact[] =
{
     306,   -13,    50,-32768,    40,-32768,    15,    13,    13,   -10,
      22,    15,    31,-32768,   714,    54,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   168,-32768,
  -32768,-32768,    46,    13,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    59,-32768,    55,-32768,     1,
      23,    69,   410,   441,   472,   503,    77,    80,   534,    -2,
      88,    19,     2,-32768,    91,-32768,    90,-32768,-32768,   100,
  -32768,    86,    47,    15,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   714,   714,-32768,-32768,    58,-32768,    94,    58,   125,
      45,-32768,   112,-32768,   295,-32768,    47,-32768,-32768,-32768,
  -32768,-32768,   110,-32768,-32768,   108,   117,   110,   115,   226,
     110,    45,-32768,-32768,-32768,    25,   121,   565,   122,-32768,
     596,   714,   254,   123,    13,   714,   126,-32768,   137,    45,
     128,-32768,   127,   138,-32768,-32768,-32768,-32768,   135,   143,
     714,   142,   226,-32768,   145,-32768,   627,-32768,   198,-32768,
     147,   677,   146,-32768,   565,   658,   254,   150,-32768,-32768,
  -32768,   226,-32768,-32768,   151,   677,   152,   128,-32768,   696,
     696,    56,    95,-32768,   153,-32768,-32768,-32768,-32768,-32768,
  -32768,   254,-32768,   198,-32768,-32768,   156,   343,-32768,-32768,
      63,    66,-32768,-32768,   124,-32768,   714,    64,   128,-32768,
  -32768,   198,-32768,-32768,-32768,-32768,-32768,-32768,   627,-32768,
     182,-32768,-32768,   184,-32768,   184,   714,   379,-32768,-32768,
  -32768,   627,-32768,   157,   110,-32768,-32768,   379,-32768,   201,
     203,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,  -126,     0,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,  -174,  -217,-32768,-32768,-32768,-32768,
  -32768,  -155,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -186,
    -140,   -78,-32768,     9,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   -91,-32768,  -189,-32768,   -52,-32768,-32768,-32768,-32768,
  -32768,-32768,    24,-32768,   -33,-32768,   -36,   -67,   -14,   204,
      30,-32768,    84,-32768,   -51
};


#define	YYLAST		747


static const short yytable[] =
{
      50,   104,   106,   108,   110,   132,    30,   114,   219,   237,
     115,    35,   210,   155,   120,   -11,     1,   190,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,   170,   230,     6,   250,
     188,   118,   -56,    69,   181,    33,   212,   229,    32,   241,
     -33,    -4,    -4,    12,   -89,   242,   155,     7,   137,    70,
     157,   140,   195,   145,     2,   214,    71,    69,   -11,   132,
     170,   -56,    34,    65,    36,   155,    13,    14,   179,   143,
     159,   181,    72,   134,   145,   127,   128,    47,    48,    47,
      48,   129,   130,   131,     7,   170,    64,   195,    68,     8,
      47,    48,   145,   222,   223,    -7,   224,   135,   136,   167,
     232,   233,   181,   234,   235,   195,   225,    67,   239,   240,
      73,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   220,   221,   111,   148,   193,   112,  -113,  -113,   180,
     -43,   123,   124,   125,   209,   126,   139,   168,   141,  -114,
    -114,   176,    69,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,   147,   150,   176,   152,    -4,    -4,
      -4,    -4,   151,   160,   172,   165,   193,   154,   236,   177,
     183,   -93,    52,    53,    54,    55,    56,    57,    58,   178,
     254,   217,   185,   184,   186,   189,   191,   244,   197,   206,
     254,   211,   213,   225,   228,   218,   255,   231,   247,   194,
     256,   260,   257,   261,   215,   258,   255,   246,   207,   249,
     149,    31,   238,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,     0,     0,     0,   153,    -4,    -4,
      -4,    -4,   251,     0,     0,     0,     0,   154,     0,     0,
       0,   -62,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,     0,     0,     0,   169,     0,     0,    -4,    -4,
       0,     0,     0,     0,     0,   154,     0,     0,     0,   -48,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
       0,     0,     0,     0,     0,     0,    -4,    -4,     0,     0,
       0,     0,     0,   154,     0,     0,     1,   -37,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,   -11,     1,     0,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,     0,     0,     0,
       0,    -4,    -4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -4,    -4,     2,     0,     0,     0,   -11,     0,
       0,     0,     0,     0,     0,     2,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,     0,   192,     0,     0,     0,
     -66,   -66,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,    47,    48,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,     0,   103,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,     0,   105,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,     0,   107,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,     0,   109,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   113,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     0,   161,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     0,   166,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,     0,
     192,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       0,   208,   198,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,     0,     0,     0,     0,   199,   200,    47,
      48,   198,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     0,     0,     0,     0,     0,     0,    47,    48,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
       0,     0,     0,     0,     0,     0,    47,    48
};

static const short yycheck[] =
{
      14,    52,    53,    54,    55,    72,     6,    58,   197,   226,
      12,    11,   186,   139,    12,     0,     1,   172,     3,     4,
       5,     6,     7,     8,     9,    10,   152,   213,    41,   246,
     170,    12,    13,    32,   160,    45,   191,   211,     8,   228,
      42,    26,    27,     3,    42,   231,   172,    34,   115,    48,
     141,   118,   178,   120,    39,   195,    33,    32,    43,   126,
     186,    42,    40,    33,    33,   191,    26,    27,   159,    24,
      45,   197,    49,    73,   141,    28,    29,    32,    33,    32,
      33,    34,    35,    36,    34,   211,    40,   213,    33,    39,
      32,    33,   159,    37,    38,    41,     1,   111,   112,   150,
      37,    38,   228,    37,    38,   231,    11,    48,    44,    45,
      41,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,   199,   200,    46,   124,   176,    46,    32,    33,     1,
      42,    40,    42,    33,   185,    49,    42,   151,    13,    44,
      45,   155,    32,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    42,    47,   170,    42,    30,    31,
      32,    33,    45,    42,    41,    43,   217,    39,    44,    43,
      43,    43,     4,     5,     6,     7,     8,     9,    10,    42,
     247,   195,    47,    45,    41,    43,    41,   238,    41,    43,
     257,    41,    41,    11,    41,    43,   247,    41,    14,     1,
     251,     0,    45,     0,   195,   257,   257,   240,   184,   245,
     126,     7,   226,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,     1,    30,    31,
      32,    33,   246,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    43,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,     1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    43,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,     1,    43,     3,     4,
       5,     6,     7,     8,     9,    10,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    39,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    -1,    -1,
      37,    38,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     3,     4,     5,     6,     7,     8,     9,
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
      25,    26,    27,    28,    29,    30,    31,    -1,    33,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33
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
#line 99 "Grammar.y"
{
;
    break;}
case 2:
#line 107 "Grammar.y"
{
    yyval = yyvsp[-2];
;
    break;}
case 3:
#line 116 "Grammar.y"
{
    yyval = yyvsp[-1];
;
    break;}
case 4:
#line 120 "Grammar.y"
{
    yyval = new StringListTok;
;
    break;}
case 5:
#line 129 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[0]);
    if(!metaData->v.empty())
    {
        unit->setGlobalMetaData(metaData->v);
    }
;
    break;}
case 7:
#line 138 "Grammar.y"
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
#line 149 "Grammar.y"
{
    yyerrok;
;
    break;}
case 10:
#line 153 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 11:
#line 157 "Grammar.y"
{
;
    break;}
case 12:
#line 165 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ModulePtr::dynamicCast(yyvsp[0]));
;
    break;}
case 13:
#line 169 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 14:
#line 173 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 15:
#line 177 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDeclPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 16:
#line 181 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ClassDefPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 17:
#line 185 "Grammar.y"
{
    assert(yyvsp[0] == 0);
;
    break;}
case 18:
#line 189 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ExceptionPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 19:
#line 193 "Grammar.y"
{
    assert(yyvsp[0] == 0);
;
    break;}
case 20:
#line 197 "Grammar.y"
{
    assert(yyvsp[0] == 0 || StructPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 21:
#line 201 "Grammar.y"
{
    assert(yyvsp[0] == 0 || SequencePtr::dynamicCast(yyvsp[0]));
;
    break;}
case 22:
#line 205 "Grammar.y"
{
    assert(yyvsp[0] == 0 || DictionaryPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 23:
#line 209 "Grammar.y"
{
    assert(yyvsp[0] == 0 || EnumPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 24:
#line 213 "Grammar.y"
{
    assert(yyvsp[0] == 0 || ConstPtr::dynamicCast(yyvsp[0]));
;
    break;}
case 25:
#line 222 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ModulePtr module = cont->createModule(ident->v);
    if(!module)
    {
	YYERROR; // Can't continue, jump to next yyerrok
    }
    cont->checkIntroduced(ident->v, module);
    unit->pushContainer(module);
    yyval = module;
;
    break;}
case 26:
#line 235 "Grammar.y"
{
    unit->popContainer();
    yyval = yyvsp[-3];
;
    break;}
case 27:
#line 245 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 28:
#line 249 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = yyvsp[0];
;
    break;}
case 29:
#line 260 "Grammar.y"
{
    unit->error("exceptions cannot be forward declared");
    yyval = 0;
;
    break;}
case 30:
#line 270 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-1]);
    ExceptionPtr base = ExceptionPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ExceptionPtr ex = cont->createException(ident->v, base, local->v);
    if(!ex)
    {
	YYERROR; // Can't continue, jump to next yyerrok
    }
    cont->checkIntroduced(ident->v, ex);
    unit->pushContainer(ex);
    yyval = ex;
;
    break;}
case 31:
#line 285 "Grammar.y"
{
    unit->popContainer();
    yyval = yyvsp[-3];
;
    break;}
case 32:
#line 295 "Grammar.y"
{
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ContainedPtr contained = cont->lookupException(scoped->v);
    cont->checkIntroduced(scoped->v);
    yyval = contained;
;
    break;}
case 33:
#line 303 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 34:
#line 312 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 35:
#line 321 "Grammar.y"
{
;
    break;}
case 36:
#line 324 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 37:
#line 328 "Grammar.y"
{
;
    break;}
case 38:
#line 336 "Grammar.y"
{
    TypePtr type = TypePtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypeStringTokPtr typestring = new TypeStringTok;
    typestring->v = make_pair(type, ident->v);
    yyval = typestring;
;
    break;}
case 40:
#line 355 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 41:
#line 359 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as struct name");
    yyval = yyvsp[0];
;
    break;}
case 42:
#line 370 "Grammar.y"
{
    unit->error("structs cannot be forward declared");
    yyval = 0;
;
    break;}
case 43:
#line 380 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    StructPtr st = cont->createStruct(ident->v, local->v);
    if(!st)
    {
	YYERROR; // Can't continue, jump to next yyerrok
    }
    cont->checkIntroduced(ident->v, st);
    unit->pushContainer(st);
    yyval = st;
;
    break;}
case 44:
#line 394 "Grammar.y"
{
    unit->popContainer();
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
case 45:
#line 414 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 46:
#line 423 "Grammar.y"
{
;
    break;}
case 47:
#line 426 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 48:
#line 430 "Grammar.y"
{
;
    break;}
case 50:
#line 444 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 51:
#line 448 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as class name");
    yyval = yyvsp[0];
;
    break;}
case 52:
#line 459 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, false, local->v);
    yyval = cl;
;
    break;}
case 53:
#line 472 "Grammar.y"
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
    if(!cl)
    {
	YYERROR; // Can't continue, jump to next yyerrok
    }
    cont->checkIntroduced(ident->v, cl);
    unit->pushContainer(cl);
    yyval = cl;
;
    break;}
case 54:
#line 492 "Grammar.y"
{
    unit->popContainer();
    yyval = yyvsp[-3];
;
    break;}
case 55:
#line 502 "Grammar.y"
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
case 56:
#line 536 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 57:
#line 545 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 58:
#line 549 "Grammar.y"
{
    yyval = new ClassListTok;
;
    break;}
case 59:
#line 558 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 60:
#line 567 "Grammar.y"
{
;
    break;}
case 61:
#line 570 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 62:
#line 574 "Grammar.y"
{
;
    break;}
case 63:
#line 582 "Grammar.y"
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
case 64:
#line 605 "Grammar.y"
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
case 65:
#line 627 "Grammar.y"
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
case 67:
#line 654 "Grammar.y"
{
    yyval = 0;
;
    break;}
case 68:
#line 663 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType);
    cl->checkIntroduced(name, op);
    unit->pushContainer(op);
    yyval = op;
;
    break;}
case 69:
#line 674 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
    cl->checkIntroduced(name, op);
    unit->pushContainer(op);
    yyval = op;
;
    break;}
case 70:
#line 685 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
    cl->checkIntroduced(name, op);
    unit->pushContainer(op);
    yyval = op;
;
    break;}
case 71:
#line 696 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType);
    unit->pushContainer(op);
    unit->error("keyword `" + name + "' cannot be used as operation name");
    yyval = op;
;
    break;}
case 72:
#line 707 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
    unit->pushContainer(op);
    unit->error("keyword `" + name + "' cannot be used as operation name");
    yyval = op;
;
    break;}
case 73:
#line 718 "Grammar.y"
{
    TypePtr returnType = TypePtr::dynamicCast(yyvsp[-1]);
    string name = StringTokPtr::dynamicCast(yyvsp[0])->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    assert(cl);
    OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
    unit->pushContainer(op);
    unit->error("keyword `" + name + "' cannot be used as operation name");
    yyval = op;
;
    break;}
case 74:
#line 734 "Grammar.y"
{
    unit->popContainer();
    yyval = yyvsp[-2];
;
    break;}
case 75:
#line 739 "Grammar.y"
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
case 76:
#line 749 "Grammar.y"
{
    unit->popContainer();
    yyerrok;
;
    break;}
case 77:
#line 754 "Grammar.y"
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
case 80:
#line 776 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 81:
#line 780 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as interface name");
    yyval = yyvsp[0];
;
    break;}
case 82:
#line 791 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, true, local->v);
    cont->checkIntroduced(ident->v, cl);
    yyval = cl;
;
    break;}
case 83:
#line 805 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-1]);
    ContainerPtr cont = unit->currentContainer();
    ClassListTokPtr bases = ClassListTokPtr::dynamicCast(yyvsp[0]);
    ClassDefPtr cl = cont->createClassDef(ident->v, true, bases->v, local->v);
    if(!cl)
    {
	YYERROR; // Can't continue, jump to next yyerrok
    }
    cont->checkIntroduced(ident->v, cl);
    unit->pushContainer(cl);
    yyval = cl;
;
    break;}
case 84:
#line 820 "Grammar.y"
{
    unit->popContainer();
    yyval = yyvsp[-3];
;
    break;}
case 85:
#line 830 "Grammar.y"
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
case 86:
#line 865 "Grammar.y"
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
case 87:
#line 900 "Grammar.y"
{
    unit->error("illegal inheritance from type Object");
    yyval = new ClassListTok;
;
    break;}
case 88:
#line 910 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 89:
#line 914 "Grammar.y"
{
    yyval = new ClassListTok;
;
    break;}
case 90:
#line 923 "Grammar.y"
{
    StringListTokPtr metaData = StringListTokPtr::dynamicCast(yyvsp[-3]);
    ContainedPtr contained = ContainedPtr::dynamicCast(yyvsp[-2]);
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
;
    break;}
case 91:
#line 932 "Grammar.y"
{
;
    break;}
case 92:
#line 935 "Grammar.y"
{
    unit->error("`;' missing after definition");
;
    break;}
case 93:
#line 939 "Grammar.y"
{
;
    break;}
case 95:
#line 953 "Grammar.y"
{
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[-2]);
    ExceptionListTokPtr exceptionList = ExceptionListTokPtr::dynamicCast(yyvsp[0]);
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;
    break;}
case 96:
#line 960 "Grammar.y"
{
    ExceptionPtr exception = ExceptionPtr::dynamicCast(yyvsp[0]);
    ExceptionListTokPtr exceptionList = new ExceptionListTok;
    exceptionList->v.push_front(exception);
    yyval = exceptionList;
;
    break;}
case 97:
#line 972 "Grammar.y"
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
case 98:
#line 984 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    yyval = unit->currentContainer()->createException(IceUtil::generateUUID(), 0, false);
;
    break;}
case 99:
#line 995 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
;
    break;}
case 100:
#line 1003 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-5]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createSequence(ident->v, type, local->v);
    unit->error("keyword `" + ident->v + "' cannot be used as sequence name");
;
    break;}
case 101:
#line 1017 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-7]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr keyType = TypePtr::dynamicCast(yyvsp[-4]);
    TypePtr valueType = TypePtr::dynamicCast(yyvsp[-2]);
    ContainerPtr cont = unit->currentContainer();
    yyval = cont->createDictionary(ident->v, keyType, valueType, local->v);
;
    break;}
case 102:
#line 1026 "Grammar.y"
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
case 103:
#line 1041 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 104:
#line 1045 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumeration name");
    yyval = yyvsp[0];
;
    break;}
case 105:
#line 1056 "Grammar.y"
{
    BoolTokPtr local = BoolTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ContainerPtr cont = unit->currentContainer();
    EnumPtr en = cont->createEnum(ident->v, local->v);
    cont->checkIntroduced(ident->v, en);
    yyval = en;
;
    break;}
case 106:
#line 1065 "Grammar.y"
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
case 107:
#line 1084 "Grammar.y"
{
    EnumeratorListTokPtr ens = EnumeratorListTokPtr::dynamicCast(yyvsp[-2]);
    ens->v.splice(ens->v.end(), EnumeratorListTokPtr::dynamicCast(yyvsp[0])->v);
    yyval = ens;
;
    break;}
case 108:
#line 1090 "Grammar.y"
{
;
    break;}
case 109:
#line 1098 "Grammar.y"
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
case 110:
#line 1110 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("keyword `" + ident->v + "' cannot be used as enumerator");
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;
    break;}
case 111:
#line 1117 "Grammar.y"
{
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    yyval = ens;
;
    break;}
case 112:
#line 1127 "Grammar.y"
{
    BoolTokPtr out = new BoolTok;
    out->v = true;
    yyval = out;
;
    break;}
case 113:
#line 1133 "Grammar.y"
{
    BoolTokPtr out = new BoolTok;
    out->v = false;
    yyval = out;
;
    break;}
case 114:
#line 1144 "Grammar.y"
{
;
    break;}
case 115:
#line 1147 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-1]);
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
    }
;
    break;}
case 116:
#line 1160 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-1]);
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast(yyvsp[0]);
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
    }
;
    break;}
case 117:
#line 1173 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
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
case 118:
#line 1185 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-2]);
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
#line 1197 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-1]);
    TypePtr type = TypePtr::dynamicCast(yyvsp[0]);
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(IceUtil::generateUUID(), type, isOutParam->v);
	unit->error("missing parameter name");
    }
;
    break;}
case 120:
#line 1208 "Grammar.y"
{
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast(yyvsp[-1]);
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
#line 1224 "Grammar.y"
{
    yyval = yyvsp[0];
;
    break;}
case 122:
#line 1228 "Grammar.y"
{
    yyval = new ExceptionListTok;
;
    break;}
case 123:
#line 1237 "Grammar.y"
{
;
    break;}
case 124:
#line 1240 "Grammar.y"
{
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    ident->v = "::" + ident->v;
    yyval = ident;
;
    break;}
case 125:
#line 1246 "Grammar.y"
{
    StringTokPtr scoped = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[0]);
    scoped->v += "::";
    scoped->v += ident->v;
    yyval = scoped;
;
    break;}
case 126:
#line 1259 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindByte);
;
    break;}
case 127:
#line 1263 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindBool);
;
    break;}
case 128:
#line 1267 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindShort);
;
    break;}
case 129:
#line 1271 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindInt);
;
    break;}
case 130:
#line 1275 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindLong);
;
    break;}
case 131:
#line 1279 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindFloat);
;
    break;}
case 132:
#line 1283 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindDouble);
;
    break;}
case 133:
#line 1287 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindString);
;
    break;}
case 134:
#line 1291 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindObject);
;
    break;}
case 135:
#line 1295 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindObjectProxy);
;
    break;}
case 136:
#line 1299 "Grammar.y"
{
    yyval = unit->builtin(Builtin::KindLocalObject);
;
    break;}
case 137:
#line 1303 "Grammar.y"
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
case 138:
#line 1322 "Grammar.y"
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
case 139:
#line 1363 "Grammar.y"
{
    StringTokPtr str1 = StringTokPtr::dynamicCast(yyvsp[-1]);
    StringTokPtr str2 = StringTokPtr::dynamicCast(yyvsp[0]);
    str1->v += str2->v;
;
    break;}
case 140:
#line 1369 "Grammar.y"
{
;
    break;}
case 141:
#line 1377 "Grammar.y"
{
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[-2]);
    StringListTokPtr stringList = StringListTokPtr::dynamicCast(yyvsp[0]);
    stringList->v.push_back(str->v);
    yyval = stringList;
;
    break;}
case 142:
#line 1384 "Grammar.y"
{
    StringTokPtr str = StringTokPtr::dynamicCast(yyvsp[0]);
    StringListTokPtr stringList = new StringListTok;
    stringList->v.push_back(str->v);
    yyval = stringList;
;
    break;}
case 143:
#line 1396 "Grammar.y"
{
    BoolTokPtr local = new BoolTok;
    local->v = true;
    yyval = local;
;
    break;}
case 144:
#line 1402 "Grammar.y"
{
    BoolTokPtr local = new BoolTok;
    local->v = false;
    yyval = local;
;
    break;}
case 145:
#line 1413 "Grammar.y"
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
case 146:
#line 1423 "Grammar.y"
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
case 147:
#line 1433 "Grammar.y"
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
case 148:
#line 1462 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindString);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 149:
#line 1470 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 150:
#line 1478 "Grammar.y"
{
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast(yyvsp[0]);
    SyntaxTreeBaseStringTokPtr basestring = new SyntaxTreeBaseStringTok;
    basestring->v = pair<SyntaxTreeBasePtr,string>(type, literal->v);
    yyval = basestring;
;
    break;}
case 151:
#line 1491 "Grammar.y"
{
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-3]);
    StringTokPtr ident = StringTokPtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    yyval = unit->currentContainer()->createConst(ident->v, const_type, value->v.first, value->v.second);
;
    break;}
case 152:
#line 1498 "Grammar.y"
{
    TypePtr const_type = TypePtr::dynamicCast(yyvsp[-2]);
    SyntaxTreeBaseStringTokPtr value = SyntaxTreeBaseStringTokPtr::dynamicCast(yyvsp[0]);
    unit->error("missing constant name");
    yyval = unit->currentContainer()->createConst(IceUtil::generateUUID(), const_type, value->v.first, value->v.second);
;
    break;}
case 153:
#line 1510 "Grammar.y"
{
;
    break;}
case 154:
#line 1513 "Grammar.y"
{
;
    break;}
case 155:
#line 1516 "Grammar.y"
{
;
    break;}
case 156:
#line 1519 "Grammar.y"
{
;
    break;}
case 157:
#line 1522 "Grammar.y"
{
;
    break;}
case 158:
#line 1525 "Grammar.y"
{
;
    break;}
case 159:
#line 1528 "Grammar.y"
{
;
    break;}
case 160:
#line 1531 "Grammar.y"
{
;
    break;}
case 161:
#line 1534 "Grammar.y"
{
;
    break;}
case 162:
#line 1537 "Grammar.y"
{
;
    break;}
case 163:
#line 1540 "Grammar.y"
{
;
    break;}
case 164:
#line 1543 "Grammar.y"
{
;
    break;}
case 165:
#line 1546 "Grammar.y"
{
;
    break;}
case 166:
#line 1549 "Grammar.y"
{
;
    break;}
case 167:
#line 1552 "Grammar.y"
{
;
    break;}
case 168:
#line 1555 "Grammar.y"
{
;
    break;}
case 169:
#line 1558 "Grammar.y"
{
;
    break;}
case 170:
#line 1561 "Grammar.y"
{
;
    break;}
case 171:
#line 1564 "Grammar.y"
{
;
    break;}
case 172:
#line 1567 "Grammar.y"
{
;
    break;}
case 173:
#line 1570 "Grammar.y"
{
;
    break;}
case 174:
#line 1573 "Grammar.y"
{
;
    break;}
case 175:
#line 1576 "Grammar.y"
{
;
    break;}
case 176:
#line 1579 "Grammar.y"
{
;
    break;}
case 177:
#line 1582 "Grammar.y"
{
;
    break;}
case 178:
#line 1585 "Grammar.y"
{
;
    break;}
case 179:
#line 1588 "Grammar.y"
{
;
    break;}
case 180:
#line 1591 "Grammar.y"
{
;
    break;}
case 181:
#line 1594 "Grammar.y"
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
#line 1598 "Grammar.y"

