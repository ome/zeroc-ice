/* A Bison parser, made from cexp.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	INT	257
# define	CHAR	258
# define	NAME	259
# define	ERROR	260
# define	OR	261
# define	AND	262
# define	EQUAL	263
# define	NOTEQUAL	264
# define	LEQ	265
# define	GEQ	266
# define	LSH	267
# define	RSH	268
# define	UNARY	269

#line 27 "cexp.y"

#include "config.h"
#include <setjmp.h>
/* #define YYDEBUG 1 */


#ifdef HAVE_STRING_H
# include <string.h>
#endif

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#ifdef HAVE_LIMITS_H
# include <limits.h>
#endif

#ifdef MULTIBYTE_CHARS
#include <locale.h>
#endif

#include <stdio.h>

typedef unsigned char U_CHAR;

/* This is used for communicating lists of keywords with cccp.c.  */
struct arglist {
  struct arglist *next;
  U_CHAR *name;
  int length;
  int argno;
};

/* Define a generic NULL if one hasn't already been defined.  */

#ifndef NULL
#define NULL 0
#endif

#ifndef GENERIC_PTR
#if defined (USE_PROTOTYPES) ? USE_PROTOTYPES : defined (__STDC__)
#define GENERIC_PTR void *
#else
#define GENERIC_PTR char *
#endif
#endif

#ifndef NULL_PTR
#define NULL_PTR ((GENERIC_PTR) 0)
#endif

/* Find the largest host integer type and set its size and type.
   Watch out: on some crazy hosts `long' is shorter than `int'.  */

#ifndef HOST_WIDE_INT
# if HAVE_INTTYPES_H
#  include <inttypes.h>
#  define HOST_WIDE_INT intmax_t
#  define unsigned_HOST_WIDE_INT uintmax_t
# else
#  if (HOST_BITS_PER_LONG <= HOST_BITS_PER_INT && HOST_BITS_PER_LONGLONG <= HOST_BITS_PER_INT)
#   define HOST_WIDE_INT int
#  else
#  if (HOST_BITS_PER_LONGLONG <= HOST_BITS_PER_LONG || ! (defined LONG_LONG_MAX || defined LLONG_MAX))
#   define HOST_WIDE_INT long
#  else
#   define HOST_WIDE_INT long long
#  endif
#  endif
# endif
#endif

#ifndef unsigned_HOST_WIDE_INT
#define unsigned_HOST_WIDE_INT unsigned HOST_WIDE_INT
#endif

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#ifndef HOST_BITS_PER_WIDE_INT
#define HOST_BITS_PER_WIDE_INT (CHAR_BIT * sizeof (HOST_WIDE_INT))
#endif

#if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7)
# define __attribute__(x)
#endif

#ifndef PROTO
# if defined (USE_PROTOTYPES) ? USE_PROTOTYPES : defined (__STDC__)
#  define PROTO(ARGS) ARGS
# else
#  define PROTO(ARGS) ()
# endif
#endif

#if defined (__STDC__) && defined (HAVE_VPRINTF)
# include <stdarg.h>
# define VA_START(va_list, var) va_start (va_list, var)
# define PRINTF_ALIST(msg) char *msg, ...
# define PRINTF_DCL(msg)
# define PRINTF_PROTO(ARGS, m, n) PROTO (ARGS) __attribute__ ((format (__printf__, m, n)))
#else
# include <varargs.h>
# define VA_START(va_list, var) va_start (va_list)
# define PRINTF_ALIST(msg) msg, va_alist
# define PRINTF_DCL(msg) char *msg; va_dcl
# define PRINTF_PROTO(ARGS, m, n) () __attribute__ ((format (__printf__, m, n)))
# define vfprintf(file, msg, args) \
    { \
      char *a0 = va_arg(args, char *); \
      char *a1 = va_arg(args, char *); \
      char *a2 = va_arg(args, char *); \
      char *a3 = va_arg(args, char *); \
      fprintf (file, msg, a0, a1, a2, a3); \
    }
#endif

#define PRINTF_PROTO_1(ARGS) PRINTF_PROTO(ARGS, 1, 2)

HOST_WIDE_INT parse_c_expression PROTO((char *, int));

static int yylex PROTO((void));
static void yyerror PROTO((char *)) __attribute__ ((noreturn));
static HOST_WIDE_INT expression_value;
#ifdef TEST_EXP_READER
static int expression_signedp;
#endif

static jmp_buf parse_return_error;

/* Nonzero means count most punctuation as part of a name.  */
static int keyword_parsing = 0;

/* Nonzero means do not evaluate this expression.
   This is a count, since unevaluated expressions can nest.  */
static int skip_evaluation;

/* Nonzero means warn if undefined identifiers are evaluated.  */
static int warn_undef;

/* some external tables of character types */
extern unsigned char is_idstart[], is_idchar[], is_space[];

/* Flag for -pedantic.  */
extern int pedantic;

/* Flag for -traditional.  */
extern int traditional;

/* Flag for -lang-c89.  */
extern int c89;

#ifndef CHAR_TYPE_SIZE
#define CHAR_TYPE_SIZE BITS_PER_UNIT
#endif

#ifndef INT_TYPE_SIZE
#define INT_TYPE_SIZE BITS_PER_WORD
#endif

#ifndef LONG_TYPE_SIZE
#define LONG_TYPE_SIZE BITS_PER_WORD
#endif

#ifndef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE INT_TYPE_SIZE
#endif

#ifndef MAX_CHAR_TYPE_SIZE
#define MAX_CHAR_TYPE_SIZE CHAR_TYPE_SIZE
#endif

#ifndef MAX_INT_TYPE_SIZE
#define MAX_INT_TYPE_SIZE INT_TYPE_SIZE
#endif

#ifndef MAX_LONG_TYPE_SIZE
#define MAX_LONG_TYPE_SIZE LONG_TYPE_SIZE
#endif

#ifndef MAX_WCHAR_TYPE_SIZE
#define MAX_WCHAR_TYPE_SIZE WCHAR_TYPE_SIZE
#endif

#define MAX_CHAR_TYPE_MASK (MAX_CHAR_TYPE_SIZE < HOST_BITS_PER_WIDE_INT \
			    ? (~ (~ (HOST_WIDE_INT) 0 << MAX_CHAR_TYPE_SIZE)) \
			    : ~ (HOST_WIDE_INT) 0)

#define MAX_WCHAR_TYPE_MASK (MAX_WCHAR_TYPE_SIZE < HOST_BITS_PER_WIDE_INT \
			     ? ~ (~ (HOST_WIDE_INT) 0 << MAX_WCHAR_TYPE_SIZE) \
			     : ~ (HOST_WIDE_INT) 0)

/* Suppose A1 + B1 = SUM1, using 2's complement arithmetic ignoring overflow.
   Suppose A, B and SUM have the same respective signs as A1, B1, and SUM1.
   Suppose SIGNEDP is negative if the result is signed, zero if unsigned.
   Then this yields nonzero if overflow occurred during the addition.
   Overflow occurs if A and B have the same sign, but A and SUM differ in sign,
   and SIGNEDP is negative.
   Use `^' to test whether signs differ, and `< 0' to isolate the sign.  */
#define overflow_sum_sign(a, b, sum, signedp) \
	((~((a) ^ (b)) & ((a) ^ (sum)) & (signedp)) < 0)

struct constant;

GENERIC_PTR xmalloc PROTO((size_t));
HOST_WIDE_INT parse_escape PROTO((char **, HOST_WIDE_INT));
int check_assertion PROTO((U_CHAR *, int, int, struct arglist *));
struct hashnode *lookup PROTO((U_CHAR *, int, int));
void error PRINTF_PROTO_1((char *, ...));
void pedwarn PRINTF_PROTO_1((char *, ...));
void warning PRINTF_PROTO_1((char *, ...));

static int parse_number PROTO((int));
static HOST_WIDE_INT left_shift PROTO((struct constant *, unsigned_HOST_WIDE_INT));
static HOST_WIDE_INT right_shift PROTO((struct constant *, unsigned_HOST_WIDE_INT));
static void integer_overflow PROTO((void));

/* `signedp' values */
#define SIGNED (~0)
#define UNSIGNED 0

#line 251 "cexp.y"
#ifndef YYSTYPE
typedef union {
  struct constant {HOST_WIDE_INT value; int signedp;} integer;
  struct name {U_CHAR *address; int length;} name;
  struct arglist *keywords;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		77
#define	YYFLAG		-32768
#define	YYNTBASE	34

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 269 ? yytranslate[x] : 43)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    31,     2,    27,    14,     2,
      32,    33,    25,    23,     9,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     8,     2,
      17,     2,    18,     7,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    13,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    12,     2,    30,     2,     2,     2,
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
       6,    10,    11,    15,    16,    19,    20,    21,    22,    28
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     8,    11,    14,    17,    20,    23,
      24,    31,    35,    39,    43,    47,    51,    55,    59,    63,
      67,    71,    75,    79,    83,    87,    91,    95,    99,   100,
     105,   106,   111,   112,   113,   121,   123,   125,   127,   128,
     133
};
static const short yyrhs[] =
{
      35,     0,    36,     0,    35,     9,    36,     0,    24,    36,
       0,    29,    36,     0,    23,    36,     0,    30,    36,     0,
      31,     5,     0,     0,    31,     5,    37,    32,    42,    33,
       0,    32,    35,    33,     0,    36,    25,    36,     0,    36,
      26,    36,     0,    36,    27,    36,     0,    36,    23,    36,
       0,    36,    24,    36,     0,    36,    21,    36,     0,    36,
      22,    36,     0,    36,    15,    36,     0,    36,    16,    36,
       0,    36,    19,    36,     0,    36,    20,    36,     0,    36,
      17,    36,     0,    36,    18,    36,     0,    36,    14,    36,
       0,    36,    13,    36,     0,    36,    12,    36,     0,     0,
      36,    11,    38,    36,     0,     0,    36,    10,    39,    36,
       0,     0,     0,    36,     7,    40,    36,     8,    41,    36,
       0,     3,     0,     4,     0,     5,     0,     0,    32,    42,
      33,    42,     0,     5,    42,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   281,   291,   292,   299,   304,   307,   309,   312,   316,
     316,   323,   328,   341,   358,   371,   377,   383,   389,   395,
     398,   401,   408,   415,   422,   429,   432,   435,   438,   438,
     444,   444,   450,   450,   450,   458,   460,   462,   470,   472,
     485
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "INT", "CHAR", "NAME", "ERROR", "'?'", "':'", 
  "','", "OR", "AND", "'|'", "'^'", "'&'", "EQUAL", "NOTEQUAL", "'<'", 
  "'>'", "LEQ", "GEQ", "LSH", "RSH", "'+'", "'-'", "'*'", "'/'", "'%'", 
  "UNARY", "'!'", "'~'", "'#'", "'('", "')'", "start", "exp1", "exp", 
  "@1", "@2", "@3", "@4", "@5", "keywords", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    34,    35,    35,    36,    36,    36,    36,    36,    37,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    38,    36,
      39,    36,    40,    41,    36,    36,    36,    36,    42,    42,
      42
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     3,     2,     2,     2,     2,     2,     0,
       6,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     0,     7,     1,     1,     1,     0,     4,
       2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       1,     2,     6,     4,     5,     7,     8,     0,     0,    32,
      30,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       3,     0,     0,     0,    27,    26,    25,    19,    20,    23,
      24,    21,    22,    17,    18,    15,    16,    12,    13,    14,
      38,     0,    31,    29,    38,    38,     0,    33,    40,     0,
      10,     0,    38,    34,    39,     0,     0,     0
};

static const short yydefgoto[] =
{
      75,    10,    11,    38,    43,    42,    41,    71,    66
};

static const short yypact[] =
{
      12,-32768,-32768,-32768,    12,    12,    12,    12,     1,    12,
       4,    79,-32768,-32768,-32768,-32768,   -21,    31,    12,-32768,
  -32768,-32768,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    30,-32768,
      79,    12,    12,    12,   110,   124,   137,   148,   148,   155,
     155,   155,   155,   160,   160,   -17,   -17,-32768,-32768,-32768,
       2,    58,    34,    95,     2,     2,    54,-32768,-32768,    55,
  -32768,    12,     2,    79,-32768,    63,   188,-32768
};

static const short yypgoto[] =
{
  -32768,   180,    -4,-32768,-32768,-32768,-32768,-32768,   -60
};


#define	YYLAST		189


static const short yytable[] =
{
      12,    13,    14,    15,    68,    69,    16,    64,    35,    36,
      37,    -9,    74,    18,    40,     1,     2,     3,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    65,     4,     5,    61,    62,    63,
      18,     6,     7,     8,     9,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    60,    76,    39,    19,    67,    73,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    19,    70,    72,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    31,    32,    33,    34,
      35,    36,    37,    33,    34,    35,    36,    37,    77,    17
};

static const short yycheck[] =
{
       4,     5,     6,     7,    64,    65,     5,     5,    25,    26,
      27,    32,    72,     9,    18,     3,     4,     5,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    32,    23,    24,    41,    42,    43,
       9,    29,    30,    31,    32,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    32,     0,    33,     7,     8,    71,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,     7,    33,    33,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    21,    22,    23,    24,
      25,    26,    27,    23,    24,    25,    26,    27,     0,     9
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

case 1:
#line 282 "cexp.y"
{
		  expression_value = yyvsp[0].integer.value;
#ifdef TEST_EXP_READER
		  expression_signedp = yyvsp[0].integer.signedp;
#endif
		;
    break;}
case 3:
#line 293 "cexp.y"
{ if (pedantic)
			    pedwarn ("comma operator in operand of `#if'");
			  yyval.integer = yyvsp[0].integer; ;
    break;}
case 4:
#line 300 "cexp.y"
{ yyval.integer.value = - yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[0].integer.signedp;
			  if ((yyval.integer.value & yyvsp[0].integer.value & yyval.integer.signedp) < 0)
			    integer_overflow (); ;
    break;}
case 5:
#line 305 "cexp.y"
{ yyval.integer.value = ! yyvsp[0].integer.value;
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 6:
#line 308 "cexp.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 7:
#line 310 "cexp.y"
{ yyval.integer.value = ~ yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[0].integer.signedp; ;
    break;}
case 8:
#line 313 "cexp.y"
{ yyval.integer.value = check_assertion (yyvsp[0].name.address, yyvsp[0].name.length,
						      0, NULL_PTR);
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 9:
#line 317 "cexp.y"
{ keyword_parsing = 1; ;
    break;}
case 10:
#line 319 "cexp.y"
{ yyval.integer.value = check_assertion (yyvsp[-4].name.address, yyvsp[-4].name.length,
						      1, yyvsp[-1].keywords);
			  keyword_parsing = 0;
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 11:
#line 324 "cexp.y"
{ yyval.integer = yyvsp[-1].integer; ;
    break;}
case 12:
#line 329 "cexp.y"
{ yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (yyval.integer.signedp)
			    {
			      yyval.integer.value = yyvsp[-2].integer.value * yyvsp[0].integer.value;
			      if (yyvsp[-2].integer.value
				  && (yyval.integer.value / yyvsp[-2].integer.value != yyvsp[0].integer.value
				      || (yyval.integer.value & yyvsp[-2].integer.value & yyvsp[0].integer.value) < 0))
				integer_overflow ();
			    }
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					* yyvsp[0].integer.value); ;
    break;}
case 13:
#line 342 "cexp.y"
{ if (yyvsp[0].integer.value == 0)
			    {
			      if (!skip_evaluation)
				error ("division by zero in #if");
			      yyvsp[0].integer.value = 1;
			    }
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (yyval.integer.signedp)
			    {
			      yyval.integer.value = yyvsp[-2].integer.value / yyvsp[0].integer.value;
			      if ((yyval.integer.value & yyvsp[-2].integer.value & yyvsp[0].integer.value) < 0)
				integer_overflow ();
			    }
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					/ yyvsp[0].integer.value); ;
    break;}
case 14:
#line 359 "cexp.y"
{ if (yyvsp[0].integer.value == 0)
			    {
			      if (!skip_evaluation)
				error ("division by zero in #if");
			      yyvsp[0].integer.value = 1;
			    }
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (yyval.integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value % yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					% yyvsp[0].integer.value); ;
    break;}
case 15:
#line 372 "cexp.y"
{ yyval.integer.value = yyvsp[-2].integer.value + yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (overflow_sum_sign (yyvsp[-2].integer.value, yyvsp[0].integer.value,
						 yyval.integer.value, yyval.integer.signedp))
			    integer_overflow (); ;
    break;}
case 16:
#line 378 "cexp.y"
{ yyval.integer.value = yyvsp[-2].integer.value - yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (overflow_sum_sign (yyval.integer.value, yyvsp[0].integer.value,
						 yyvsp[-2].integer.value, yyval.integer.signedp))
			    integer_overflow (); ;
    break;}
case 17:
#line 384 "cexp.y"
{ yyval.integer.signedp = yyvsp[-2].integer.signedp;
			  if ((yyvsp[0].integer.value & yyvsp[0].integer.signedp) < 0)
			    yyval.integer.value = right_shift (&yyvsp[-2].integer, -yyvsp[0].integer.value);
			  else
			    yyval.integer.value = left_shift (&yyvsp[-2].integer, yyvsp[0].integer.value); ;
    break;}
case 18:
#line 390 "cexp.y"
{ yyval.integer.signedp = yyvsp[-2].integer.signedp;
			  if ((yyvsp[0].integer.value & yyvsp[0].integer.signedp) < 0)
			    yyval.integer.value = left_shift (&yyvsp[-2].integer, -yyvsp[0].integer.value);
			  else
			    yyval.integer.value = right_shift (&yyvsp[-2].integer, yyvsp[0].integer.value); ;
    break;}
case 19:
#line 396 "cexp.y"
{ yyval.integer.value = (yyvsp[-2].integer.value == yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 20:
#line 399 "cexp.y"
{ yyval.integer.value = (yyvsp[-2].integer.value != yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 21:
#line 402 "cexp.y"
{ yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value <= yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					<= yyvsp[0].integer.value); ;
    break;}
case 22:
#line 409 "cexp.y"
{ yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value >= yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					>= yyvsp[0].integer.value); ;
    break;}
case 23:
#line 416 "cexp.y"
{ yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value < yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					< yyvsp[0].integer.value); ;
    break;}
case 24:
#line 423 "cexp.y"
{ yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value > yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					> yyvsp[0].integer.value); ;
    break;}
case 25:
#line 430 "cexp.y"
{ yyval.integer.value = yyvsp[-2].integer.value & yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;
    break;}
case 26:
#line 433 "cexp.y"
{ yyval.integer.value = yyvsp[-2].integer.value ^ yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;
    break;}
case 27:
#line 436 "cexp.y"
{ yyval.integer.value = yyvsp[-2].integer.value | yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;
    break;}
case 28:
#line 439 "cexp.y"
{ skip_evaluation += !yyvsp[-1].integer.value; ;
    break;}
case 29:
#line 441 "cexp.y"
{ skip_evaluation -= !yyvsp[-3].integer.value;
			  yyval.integer.value = (yyvsp[-3].integer.value && yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 30:
#line 445 "cexp.y"
{ skip_evaluation += !!yyvsp[-1].integer.value; ;
    break;}
case 31:
#line 447 "cexp.y"
{ skip_evaluation -= !!yyvsp[-3].integer.value;
			  yyval.integer.value = (yyvsp[-3].integer.value || yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 32:
#line 451 "cexp.y"
{ skip_evaluation += !yyvsp[-1].integer.value; ;
    break;}
case 33:
#line 453 "cexp.y"
{ skip_evaluation += !!yyvsp[-4].integer.value - !yyvsp[-4].integer.value; ;
    break;}
case 34:
#line 455 "cexp.y"
{ skip_evaluation -= !!yyvsp[-6].integer.value;
			  yyval.integer.value = yyvsp[-6].integer.value ? yyvsp[-3].integer.value : yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-3].integer.signedp & yyvsp[0].integer.signedp; ;
    break;}
case 35:
#line 459 "cexp.y"
{ yyval.integer = yylval.integer; ;
    break;}
case 36:
#line 461 "cexp.y"
{ yyval.integer = yylval.integer; ;
    break;}
case 37:
#line 463 "cexp.y"
{ if (warn_undef && !skip_evaluation)
			    warning ("`%.*s' is not defined",
				     yyvsp[0].name.length, yyvsp[0].name.address);
			  yyval.integer.value = 0;
			  yyval.integer.signedp = SIGNED; ;
    break;}
case 38:
#line 471 "cexp.y"
{ yyval.keywords = 0; ;
    break;}
case 39:
#line 473 "cexp.y"
{ struct arglist *temp;
			  yyval.keywords = (struct arglist *) xmalloc (sizeof (struct arglist));
			  yyval.keywords->next = yyvsp[-2].keywords;
			  yyval.keywords->name = (U_CHAR *) "(";
			  yyval.keywords->length = 1;
			  temp = yyval.keywords;
			  while (temp != 0 && temp->next != 0)
			    temp = temp->next;
			  temp->next = (struct arglist *) xmalloc (sizeof (struct arglist));
			  temp->next->next = yyvsp[0].keywords;
			  temp->next->name = (U_CHAR *) ")";
			  temp->next->length = 1; ;
    break;}
case 40:
#line 486 "cexp.y"
{ yyval.keywords = (struct arglist *) xmalloc (sizeof (struct arglist));
			  yyval.keywords->name = yyvsp[-1].name.address;
			  yyval.keywords->length = yyvsp[-1].name.length;
			  yyval.keywords->next = yyvsp[0].keywords; ;
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
#line 491 "cexp.y"


/* During parsing of a C expression, the pointer to the next character
   is in this variable.  */

static char *lexptr;

/* Take care of parsing a number (anything that starts with a digit).
   Set yylval and return the token type; update lexptr.
   LEN is the number of characters in it.  */

/* maybe needs to actually deal with floating point numbers */

static int
parse_number (olen)
     int olen;
{
  register char *p = lexptr;
  register int c;
  register unsigned_HOST_WIDE_INT n = 0, nd, max_over_base;
  register int base = 10;
  register int len = olen;
  register int overflow = 0;
  register int digit, largest_digit = 0;
  int spec_long = 0;

  yylval.integer.signedp = SIGNED;

  if (*p == '0') {
    base = 8;
    if (len >= 3 && (p[1] == 'x' || p[1] == 'X')) {
      p += 2;
      base = 16;
      len -= 2;
    }
  }

  max_over_base = (unsigned_HOST_WIDE_INT) -1 / base;

  for (; len > 0; len--) {
    c = *p++;

    if (c >= '0' && c <= '9')
      digit = c - '0';
    else if (base == 16 && c >= 'a' && c <= 'f')
      digit = c - 'a' + 10;
    else if (base == 16 && c >= 'A' && c <= 'F')
      digit = c - 'A' + 10;
    else {
      /* `l' means long, and `u' means unsigned.  */
      while (1) {
	if (c == 'l' || c == 'L')
	  {
	    if (!pedantic < spec_long)
	      yyerror ("too many `l's in integer constant");
	    spec_long++;
	  }
	else if (c == 'u' || c == 'U')
	  {
	    if (! yylval.integer.signedp)
	      yyerror ("two `u's in integer constant");
	    yylval.integer.signedp = UNSIGNED;
	  }
	else {
	  if (c == '.' || c == 'e' || c == 'E' || c == 'p' || c == 'P')
	    yyerror ("Floating point numbers not allowed in #if expressions");
	  else {
	    char *buf = (char *) alloca (p - lexptr + 40);
	    sprintf (buf, "missing white space after number `%.*s'",
		     (int) (p - lexptr - 1), lexptr);
	    yyerror (buf);
	  }
	}

	if (--len == 0)
	  break;
	c = *p++;
      }
      /* Don't look for any more digits after the suffixes.  */
      break;
    }
    if (largest_digit < digit)
      largest_digit = digit;
    nd = n * base + digit;
    overflow |= (max_over_base < n) | (nd < n);
    n = nd;
  }

  if (base <= largest_digit)
    pedwarn ("integer constant contains digits beyond the radix");

  if (overflow)
    pedwarn ("integer constant out of range");

  /* If too big to be signed, consider it unsigned.  */
  if (((HOST_WIDE_INT) n & yylval.integer.signedp) < 0)
    {
      if (base == 10)
	warning ("integer constant is so large that it is unsigned");
      yylval.integer.signedp = UNSIGNED;
    }

  lexptr = p;
  yylval.integer.value = n;
  return INT;
}

struct token {
  char *operator;
  int token;
};

static struct token tokentab2[] = {
  {"&&", AND},
  {"||", OR},
  {"<<", LSH},
  {">>", RSH},
  {"==", EQUAL},
  {"!=", NOTEQUAL},
  {"<=", LEQ},
  {">=", GEQ},
  {"++", ERROR},
  {"--", ERROR},
  {NULL, ERROR}
};

/* Read one token, getting characters through lexptr.  */

static int
yylex ()
{
  register int c;
  register int namelen;
  register unsigned char *tokstart;
  register struct token *toktab;
  int wide_flag;
  HOST_WIDE_INT mask;

 retry:

  tokstart = (unsigned char *) lexptr;
  c = *tokstart;
  /* See if it is a special token of length 2.  */
  if (! keyword_parsing)
    for (toktab = tokentab2; toktab->operator != NULL; toktab++)
      if (c == *toktab->operator && tokstart[1] == toktab->operator[1]) {
	lexptr += 2;
	if (toktab->token == ERROR)
	  {
	    char *buf = (char *) alloca (40);
	    sprintf (buf, "`%s' not allowed in operand of `#if'", toktab->operator);
	    yyerror (buf);
	  }
	return toktab->token;
      }

  switch (c) {
  case '\n':
    return 0;
    
  case ' ':
  case '\t':
  case '\r':
    lexptr++;
    goto retry;
    
  case 'L':
    /* Capital L may start a wide-string or wide-character constant.  */
    if (lexptr[1] == '\'')
      {
	lexptr++;
	wide_flag = 1;
	mask = MAX_WCHAR_TYPE_MASK;
	goto char_constant;
      }
    if (lexptr[1] == '"')
      {
	lexptr++;
	wide_flag = 1;
	mask = MAX_WCHAR_TYPE_MASK;
	goto string_constant;
      }
    break;

  case '\'':
    wide_flag = 0;
    mask = MAX_CHAR_TYPE_MASK;
  char_constant:
    lexptr++;
    if (keyword_parsing) {
      char *start_ptr = lexptr - 1;
      while (1) {
	c = *lexptr++;
	if (c == '\\')
	  c = parse_escape (&lexptr, mask);
	else if (c == '\'')
	  break;
      }
      yylval.name.address = tokstart;
      yylval.name.length = lexptr - start_ptr;
      return NAME;
    }

    /* This code for reading a character constant
       handles multicharacter constants and wide characters.
       It is mostly copied from c-lex.c.  */
    {
      register HOST_WIDE_INT result = 0;
      register int num_chars = 0;
      unsigned width = MAX_CHAR_TYPE_SIZE;
      int max_chars;
      char *token_buffer;

      if (wide_flag)
	{
	  width = MAX_WCHAR_TYPE_SIZE;
#ifdef MULTIBYTE_CHARS
	  max_chars = MB_CUR_MAX;
#else
	  max_chars = 1;
#endif
	}
      else
	max_chars = MAX_LONG_TYPE_SIZE / width;

      token_buffer = (char *) alloca (max_chars + 1);

      while (1)
	{
	  c = *lexptr++;

	  if (c == '\'' || c == EOF)
	    break;

	  if (c == '\\')
	    {
	      c = parse_escape (&lexptr, mask);
	    }

	  num_chars++;

	  /* Merge character into result; ignore excess chars.  */
	  if (num_chars <= max_chars)
	    {
	      if (width < HOST_BITS_PER_WIDE_INT)
		result = (result << width) | c;
	      else
		result = c;
	      token_buffer[num_chars - 1] = c;
	    }
	}

      token_buffer[num_chars] = 0;

      if (c != '\'')
	error ("malformatted character constant");
      else if (num_chars == 0)
	error ("empty character constant");
      else if (num_chars > max_chars)
	{
	  num_chars = max_chars;
	  error ("character constant too long");
	}
      else if (num_chars != 1 && ! traditional)
	warning ("multi-character character constant");

      /* If char type is signed, sign-extend the constant.  */
      if (! wide_flag)
	{
	  int num_bits = num_chars * width;

	  if (lookup ((U_CHAR *) "__CHAR_UNSIGNED__",
		      sizeof ("__CHAR_UNSIGNED__") - 1, -1)
	      || ((result >> (num_bits - 1)) & 1) == 0)
	    yylval.integer.value
	      = result & (~ (unsigned_HOST_WIDE_INT) 0
			  >> (HOST_BITS_PER_WIDE_INT - num_bits));
	  else
	    yylval.integer.value
	      = result | ~(~ (unsigned_HOST_WIDE_INT) 0
			   >> (HOST_BITS_PER_WIDE_INT - num_bits));
	}
      else
	{
#ifdef MULTIBYTE_CHARS
	  /* Set the initial shift state and convert the next sequence.  */
	  result = 0;
	  /* In all locales L'\0' is zero and mbtowc will return zero,
	     so don't use it.  */
	  if (num_chars > 1
	      || (num_chars == 1 && token_buffer[0] != '\0'))
	    {
	      wchar_t wc;
	      (void) mbtowc (NULL_PTR, NULL_PTR, 0);
	      if (mbtowc (& wc, token_buffer, num_chars) == num_chars)
		result = wc;
	      else
		pedwarn ("Ignoring invalid multibyte character");
	    }
#endif
	  yylval.integer.value = result;
	}
    }

    /* This is always a signed type.  */
    yylval.integer.signedp = SIGNED;
    
    return CHAR;

    /* some of these chars are invalid in constant expressions;
       maybe do something about them later */
  case '/':
  case '+':
  case '-':
  case '*':
  case '%':
  case '|':
  case '&':
  case '^':
  case '~':
  case '!':
  case '@':
  case '<':
  case '>':
  case '[':
  case ']':
  case '.':
  case '?':
  case ':':
  case '=':
  case '{':
  case '}':
  case ',':
  case '#':
    if (keyword_parsing)
      break;
  case '(':
  case ')':
    lexptr++;
    return c;

  case '"':
    mask = MAX_CHAR_TYPE_MASK;
  string_constant:
    if (keyword_parsing) {
      char *start_ptr = lexptr;
      lexptr++;
      while (1) {
	c = *lexptr++;
	if (c == '\\')
	  c = parse_escape (&lexptr, mask);
	else if (c == '"')
	  break;
      }
      yylval.name.address = tokstart;
      yylval.name.length = lexptr - start_ptr;
      return NAME;
    }
    yyerror ("string constants not allowed in #if expressions");
    return ERROR;
  }

  if (c >= '0' && c <= '9' && !keyword_parsing) {
    /* It's a number */
    for (namelen = 1; ; namelen++) {
      int d = tokstart[namelen];
      if (! ((is_idchar[d] || d == '.')
	     || ((d == '-' || d == '+')
		 && (c == 'e' || c == 'E'
		     || ((c == 'p' || c == 'P') && ! c89))
		 && ! traditional)))
	break;
      c = d;
    }
    return parse_number (namelen);
  }

  /* It is a name.  See how long it is.  */

  if (keyword_parsing) {
    for (namelen = 0;; namelen++) {
      if (is_space[tokstart[namelen]])
	break;
      if (tokstart[namelen] == '(' || tokstart[namelen] == ')')
	break;
      if (tokstart[namelen] == '"' || tokstart[namelen] == '\'')
	break;
    }
  } else {
    if (!is_idstart[c]) {
      yyerror ("Invalid token in expression");
      return ERROR;
    }

    for (namelen = 0; is_idchar[tokstart[namelen]]; namelen++)
      ;
  }
  
  lexptr += namelen;
  yylval.name.address = tokstart;
  yylval.name.length = namelen;
  return NAME;
}


/* Parse a C escape sequence.  STRING_PTR points to a variable
   containing a pointer to the string to parse.  That pointer
   is updated past the characters we use.  The value of the
   escape sequence is returned.

   RESULT_MASK is used to mask out the result;
   an error is reported if bits are lost thereby.

   A negative value means the sequence \ newline was seen,
   which is supposed to be equivalent to nothing at all.

   If \ is followed by a null character, we return a negative
   value and leave the string pointer pointing at the null character.

   If \ is followed by 000, we return 0 and leave the string pointer
   after the zeros.  A value of 0 does not mean end of string.  */

HOST_WIDE_INT
parse_escape (string_ptr, result_mask)
     char **string_ptr;
     HOST_WIDE_INT result_mask;
{
  register int c = *(*string_ptr)++;
  switch (c)
    {
    case 'a':
      return TARGET_BELL;
    case 'b':
      return TARGET_BS;
    case 'e':
    case 'E':
      if (pedantic)
	pedwarn ("non-ANSI-standard escape sequence, `\\%c'", c);
      return 033;
    case 'f':
      return TARGET_FF;
    case 'n':
      return TARGET_NEWLINE;
    case 'r':
      return TARGET_CR;
    case 't':
      return TARGET_TAB;
    case 'v':
      return TARGET_VT;
    case '\n':
      return -2;
    case 0:
      (*string_ptr)--;
      return 0;
      
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      {
	register HOST_WIDE_INT i = c - '0';
	register int count = 0;
	while (++count < 3)
	  {
	    c = *(*string_ptr)++;
	    if (c >= '0' && c <= '7')
	      i = (i << 3) + c - '0';
	    else
	      {
		(*string_ptr)--;
		break;
	      }
	  }
	if (i != (i & result_mask))
	  {
	    i &= result_mask;
	    pedwarn ("octal escape sequence out of range");
	  }
	return i;
      }
    case 'x':
      {
	register unsigned_HOST_WIDE_INT i = 0, overflow = 0;
	register int digits_found = 0, digit;
	for (;;)
	  {
	    c = *(*string_ptr)++;
	    if (c >= '0' && c <= '9')
	      digit = c - '0';
	    else if (c >= 'a' && c <= 'f')
	      digit = c - 'a' + 10;
	    else if (c >= 'A' && c <= 'F')
	      digit = c - 'A' + 10;
	    else
	      {
		(*string_ptr)--;
		break;
	      }
	    overflow |= i ^ (i << 4 >> 4);
	    i = (i << 4) + digit;
	    digits_found = 1;
	  }
	if (!digits_found)
	  yyerror ("\\x used with no following hex digits");
	if (overflow | (i != (i & result_mask)))
	  {
	    i &= result_mask;
	    pedwarn ("hex escape sequence out of range");
	  }
	return i;
      }
    default:
      return c;
    }
}

static void
yyerror (s)
     char *s;
{
  error ("%s", s);
  skip_evaluation = 0;
  longjmp (parse_return_error, 1);
}

static void
integer_overflow ()
{
  if (!skip_evaluation && pedantic)
    pedwarn ("integer overflow in preprocessor expression");
}

static HOST_WIDE_INT
left_shift (a, b)
     struct constant *a;
     unsigned_HOST_WIDE_INT b;
{
   /* It's unclear from the C standard whether shifts can overflow.
      The following code ignores overflow; perhaps a C standard
      interpretation ruling is needed.  */
  if (b >= HOST_BITS_PER_WIDE_INT)
    return 0;
  else
    return (unsigned_HOST_WIDE_INT) a->value << b;
}

static HOST_WIDE_INT
right_shift (a, b)
     struct constant *a;
     unsigned_HOST_WIDE_INT b;
{
  if (b >= HOST_BITS_PER_WIDE_INT)
    return a->signedp ? a->value >> (HOST_BITS_PER_WIDE_INT - 1) : 0;
  else if (a->signedp)
    return a->value >> b;
  else
    return (unsigned_HOST_WIDE_INT) a->value >> b;
}

/* This page contains the entry point to this file.  */

/* Parse STRING as an expression, and complain if this fails
   to use up all of the contents of STRING.
   STRING may contain '\0' bytes; it is terminated by the first '\n'
   outside a string constant, so that we can diagnose '\0' properly.
   If WARN_UNDEFINED is nonzero, warn if undefined identifiers are evaluated.
   We do not support C comments.  They should be removed before
   this function is called.  */

HOST_WIDE_INT
parse_c_expression (string, warn_undefined)
     char *string;
     int warn_undefined;
{
  lexptr = string;
  warn_undef = warn_undefined;

  /* if there is some sort of scanning error, just return 0 and assume
     the parsing routine has printed an error message somewhere.
     there is surely a better thing to do than this.     */
  if (setjmp (parse_return_error))
    return 0;

  if (yyparse () != 0)
    abort ();

  if (*lexptr != '\n')
    error ("Junk after end of expression.");

  return expression_value;	/* set by yyparse () */
}

#ifdef TEST_EXP_READER

#if YYDEBUG
extern int yydebug;
#endif

int pedantic;
int traditional;

int main PROTO((int, char **));
static void initialize_random_junk PROTO((void));
static void print_unsigned_host_wide_int PROTO((unsigned_HOST_WIDE_INT));

/* Main program for testing purposes.  */
int
main (argc, argv)
     int argc;
     char **argv;
{
  int n, c;
  char buf[1024];
  unsigned_HOST_WIDE_INT u;

  pedantic = 1 < argc;
  traditional = 2 < argc;
#if YYDEBUG
  yydebug = 3 < argc;
#endif
  initialize_random_junk ();

  for (;;) {
    printf ("enter expression: ");
    n = 0;
    while ((buf[n] = c = getchar ()) != '\n' && c != EOF)
      n++;
    if (c == EOF)
      break;
    parse_c_expression (buf, 1);
    printf ("parser returned ");
    u = (unsigned_HOST_WIDE_INT) expression_value;
    if (expression_value < 0 && expression_signedp) {
      u = -u;
      printf ("-");
    }
    if (u == 0)
      printf ("0");
    else
      print_unsigned_host_wide_int (u);
    if (! expression_signedp)
      printf("u");
    printf ("\n");
  }

  return 0;
}

static void
print_unsigned_host_wide_int (u)
     unsigned_HOST_WIDE_INT u;
{
  if (u) {
    print_unsigned_host_wide_int (u / 10);
    putchar ('0' + (int) (u % 10));
  }
}

/* table to tell if char can be part of a C identifier. */
unsigned char is_idchar[256];
/* table to tell if char can be first char of a c identifier. */
unsigned char is_idstart[256];
/* table to tell if c is horizontal or vertical space.  */
unsigned char is_space[256];

/*
 * initialize random junk in the hash table and maybe other places
 */
static void
initialize_random_junk ()
{
  register int i;

  /*
   * Set up is_idchar and is_idstart tables.  These should be
   * faster than saying (is_alpha (c) || c == '_'), etc.
   * Must do set up these things before calling any routines tthat
   * refer to them.
   */
  for (i = 'a'; i <= 'z'; i++) {
    ++is_idchar[i - 'a' + 'A'];
    ++is_idchar[i];
    ++is_idstart[i - 'a' + 'A'];
    ++is_idstart[i];
  }
  for (i = '0'; i <= '9'; i++)
    ++is_idchar[i];
  ++is_idchar['_'];
  ++is_idstart['_'];
  ++is_idchar['$'];
  ++is_idstart['$'];

  ++is_space[' '];
  ++is_space['\t'];
  ++is_space['\v'];
  ++is_space['\f'];
  ++is_space['\n'];
  ++is_space['\r'];
}

void
error (PRINTF_ALIST (msg))
     PRINTF_DCL (msg)
{
  va_list args;

  VA_START (args, msg);
  fprintf (stderr, "error: ");
  vfprintf (stderr, msg, args);
  fprintf (stderr, "\n");
  va_end (args);
}

void
pedwarn (PRINTF_ALIST (msg))
     PRINTF_DCL (msg)
{
  va_list args;

  VA_START (args, msg);
  fprintf (stderr, "pedwarn: ");
  vfprintf (stderr, msg, args);
  fprintf (stderr, "\n");
  va_end (args);
}

void
warning (PRINTF_ALIST (msg))
     PRINTF_DCL (msg)
{
  va_list args;

  VA_START (args, msg);
  fprintf (stderr, "warning: ");
  vfprintf (stderr, msg, args);
  fprintf (stderr, "\n");
  va_end (args);
}

int
check_assertion (name, sym_length, tokens_specified, tokens)
     U_CHAR *name;
     int sym_length;
     int tokens_specified;
     struct arglist *tokens;
{
  return 0;
}

struct hashnode *
lookup (name, len, hash)
     U_CHAR *name;
     int len;
     int hash;
{
  return (DEFAULT_SIGNED_CHAR) ? 0 : ((struct hashnode *) -1);
}

GENERIC_PTR
xmalloc (size)
     size_t size;
{
  return (GENERIC_PTR) malloc (size);
}
#endif
