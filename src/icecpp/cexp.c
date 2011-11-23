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
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     CHAR = 259,
     NAME = 260,
     ERROR = 261,
     OR = 262,
     AND = 263,
     NOTEQUAL = 264,
     EQUAL = 265,
     GEQ = 266,
     LEQ = 267,
     RSH = 268,
     LSH = 269,
     UNARY = 270
   };
#endif
#define INT 258
#define CHAR 259
#define NAME 260
#define ERROR 261
#define OR 262
#define AND 263
#define NOTEQUAL 264
#define EQUAL 265
#define GEQ 266
#define LEQ 267
#define RSH 268
#define LSH 269
#define UNARY 270




/* Copy the first part of user declarations.  */
#line 26 "cexp.y"

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

#ifdef _MSC_VER
// I get these warnings from some bison versions:
// warning C4102: 'yyoverflowlab' : unreferenced label
#   pragma warning( disable : 4102 )
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

#ifndef MAX_CHAR_TYPE_SIZE
#define MAX_CHAR_TYPE_SIZE CHAR_TYPE_SIZE
#endif

#ifndef MAX_INT_TYPE_SIZE
#define MAX_INT_TYPE_SIZE INT_TYPE_SIZE
#endif

#ifndef MAX_LONG_TYPE_SIZE
#define MAX_LONG_TYPE_SIZE LONG_TYPE_SIZE
#endif


#define MAX_CHAR_TYPE_MASK (MAX_CHAR_TYPE_SIZE < HOST_BITS_PER_WIDE_INT \
			    ? (~ (~ (HOST_WIDE_INT) 0 << MAX_CHAR_TYPE_SIZE)) \
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

//
// Required to allow the code to compile with VC 8 with bison 2.1.
//
#if defined(_MSC_VER) && _MSC_VER == 1400
#   define __STDC__
#   define YYMALLOC
#   define YYFREE
#endif

//
// Required to allow the code to compile with VC 6 and VC 71 with
// bison 2.3.
//
#if defined(_MSC_VER) && _MSC_VER < 1400
#   define YYMALLOC malloc
#   define YYFREE free
#endif



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 265 "cexp.y"
typedef union YYSTYPE {
  struct constant {HOST_WIDE_INT value; int signedp;} integer;
  struct name {U_CHAR *address; int length;} name;
  struct arglist *keywords;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 351 "cexp.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 363 "cexp.c"

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  10
/* YYNRULES -- Number of rules. */
#define YYNRULES  41
/* YYNRULES -- Number of states. */
#define YYNSTATES  77

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   270

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,    10,    11,    15,    16,    19,    20,    21,    22,
      28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     7,    11,    14,    17,    20,    23,
      26,    27,    34,    38,    42,    46,    50,    54,    58,    62,
      66,    70,    74,    78,    82,    86,    90,    94,    98,   102,
     103,   108,   109,   114,   115,   116,   124,   126,   128,   130,
     131,   136
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      35,     0,    -1,    36,    -1,    37,    -1,    36,     9,    37,
      -1,    24,    37,    -1,    29,    37,    -1,    23,    37,    -1,
      30,    37,    -1,    31,     5,    -1,    -1,    31,     5,    38,
      32,    43,    33,    -1,    32,    36,    33,    -1,    37,    25,
      37,    -1,    37,    26,    37,    -1,    37,    27,    37,    -1,
      37,    23,    37,    -1,    37,    24,    37,    -1,    37,    22,
      37,    -1,    37,    21,    37,    -1,    37,    16,    37,    -1,
      37,    15,    37,    -1,    37,    20,    37,    -1,    37,    19,
      37,    -1,    37,    17,    37,    -1,    37,    18,    37,    -1,
      37,    14,    37,    -1,    37,    13,    37,    -1,    37,    12,
      37,    -1,    -1,    37,    11,    39,    37,    -1,    -1,    37,
      10,    40,    37,    -1,    -1,    -1,    37,     7,    41,    37,
       8,    42,    37,    -1,     3,    -1,     4,    -1,     5,    -1,
      -1,    32,    43,    33,    43,    -1,     5,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   294,   294,   304,   305,   312,   317,   320,   322,   325,
     330,   329,   336,   341,   354,   371,   384,   390,   396,   402,
     408,   411,   414,   421,   428,   435,   442,   445,   448,   452,
     451,   458,   457,   464,   466,   463,   471,   473,   475,   484,
     485,   498
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "CHAR", "NAME", "ERROR", "'?'",
  "':'", "','", "OR", "AND", "'|'", "'^'", "'&'", "NOTEQUAL", "EQUAL",
  "'<'", "'>'", "GEQ", "LEQ", "RSH", "LSH", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UNARY", "'!'", "'~'", "'#'", "'('", "')'", "$accept", "start",
  "exp1", "exp", "@1", "@2", "@3", "@4", "@5", "keywords", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    63,    58,    44,
     262,   263,   124,    94,    38,   264,   265,    60,    62,   266,
     267,   268,   269,    43,    45,    42,    47,    37,   270,    33,
     126,    35,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    37,    37,
      38,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    39,
      37,    40,    37,    41,    42,    37,    37,    37,    37,    43,
      43,    43
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     3,     2,     2,     2,     2,     2,
       0,     6,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     0,     7,     1,     1,     1,     0,
       4,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     7,     5,     6,     8,     9,     0,     1,
       0,    33,    31,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     4,     0,     0,     0,    28,    27,    26,    21,
      20,    24,    25,    23,    22,    19,    18,    16,    17,    13,
      14,    15,    39,     0,    32,    30,    39,    39,     0,    34,
      41,     0,    11,     0,    39,    35,    40
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    10,    11,    12,    40,    45,    44,    43,    73,    68
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const short yypact[] =
{
      14,   -63,   -63,   -63,    14,    14,    14,    14,     5,    14,
      11,     6,    81,   -63,   -63,   -63,   -63,   -18,    33,   -63,
      14,   -63,   -63,   -63,    14,    14,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      32,   -63,    81,    14,    14,    14,   112,   126,   139,   150,
     150,   157,   157,   157,   157,   162,   162,   -19,   -19,   -63,
     -63,   -63,     4,    60,    36,    97,     4,     4,   -20,   -63,
     -63,    56,   -63,    14,     4,    81,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -63,   -63,   181,    -4,   -63,   -63,   -63,   -63,   -63,   -62
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -11
static const yysigned_char yytable[] =
{
      13,    14,    15,    16,    70,    71,    37,    38,    39,    66,
      17,    19,    76,    72,   -10,    20,    42,     1,     2,     3,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    67,     4,     5,    63,
      64,    65,    20,     6,     7,     8,     9,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    62,     0,    41,    21,    69,    75,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    21,    74,
       0,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    33,    34,
      35,    36,    37,    38,    39,    35,    36,    37,    38,    39,
      18
};

static const yysigned_char yycheck[] =
{
       4,     5,     6,     7,    66,    67,    25,    26,    27,     5,
       5,     0,    74,    33,    32,     9,    20,     3,     4,     5,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    32,    23,    24,    43,
      44,    45,     9,    29,    30,    31,    32,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    32,    -1,    33,     7,     8,    73,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     7,    33,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    21,    22,
      23,    24,    25,    26,    27,    23,    24,    25,    26,    27,
       9
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    23,    24,    29,    30,    31,    32,
      35,    36,    37,    37,    37,    37,    37,     5,    36,     0,
       9,     7,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      38,    33,    37,    41,    40,    39,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    32,    37,    37,    37,     5,    32,    43,     8,
      43,    43,    33,    42,    33,    37,    43
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



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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

#endif
#endif
{
  
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
#line 295 "cexp.y"
    {
		  expression_value = yyvsp[0].integer.value;
#ifdef TEST_EXP_READER
		  expression_signedp = yyvsp[0].integer.signedp;
#endif
		;}
    break;

  case 4:
#line 306 "cexp.y"
    { if (pedantic)
			    pedwarn ("comma operator in operand of `#if'");
			  yyval.integer = yyvsp[0].integer; ;}
    break;

  case 5:
#line 313 "cexp.y"
    { yyval.integer.value = - yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[0].integer.signedp;
			  if ((yyval.integer.value & yyvsp[0].integer.value & yyval.integer.signedp) < 0)
			    integer_overflow (); ;}
    break;

  case 6:
#line 318 "cexp.y"
    { yyval.integer.value = ! yyvsp[0].integer.value;
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 7:
#line 321 "cexp.y"
    { yyval.integer = yyvsp[0].integer; ;}
    break;

  case 8:
#line 323 "cexp.y"
    { yyval.integer.value = ~ yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[0].integer.signedp; ;}
    break;

  case 9:
#line 326 "cexp.y"
    { yyval.integer.value = check_assertion (yyvsp[0].name.address, yyvsp[0].name.length,
						      0, NULL_PTR);
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 10:
#line 330 "cexp.y"
    { keyword_parsing = 1; ;}
    break;

  case 11:
#line 332 "cexp.y"
    { yyval.integer.value = check_assertion (yyvsp[-4].name.address, yyvsp[-4].name.length,
						      1, yyvsp[-1].keywords);
			  keyword_parsing = 0;
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 12:
#line 337 "cexp.y"
    { yyval.integer = yyvsp[-1].integer; ;}
    break;

  case 13:
#line 342 "cexp.y"
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
					* yyvsp[0].integer.value); ;}
    break;

  case 14:
#line 355 "cexp.y"
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
					/ yyvsp[0].integer.value); ;}
    break;

  case 15:
#line 372 "cexp.y"
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
					% yyvsp[0].integer.value); ;}
    break;

  case 16:
#line 385 "cexp.y"
    { yyval.integer.value = yyvsp[-2].integer.value + yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (overflow_sum_sign (yyvsp[-2].integer.value, yyvsp[0].integer.value,
						 yyval.integer.value, yyval.integer.signedp))
			    integer_overflow (); ;}
    break;

  case 17:
#line 391 "cexp.y"
    { yyval.integer.value = yyvsp[-2].integer.value - yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp;
			  if (overflow_sum_sign (yyval.integer.value, yyvsp[0].integer.value,
						 yyvsp[-2].integer.value, yyval.integer.signedp))
			    integer_overflow (); ;}
    break;

  case 18:
#line 397 "cexp.y"
    { yyval.integer.signedp = yyvsp[-2].integer.signedp;
			  if ((yyvsp[0].integer.value & yyvsp[0].integer.signedp) < 0)
			    yyval.integer.value = right_shift (&yyvsp[-2].integer, -yyvsp[0].integer.value);
			  else
			    yyval.integer.value = left_shift (&yyvsp[-2].integer, yyvsp[0].integer.value); ;}
    break;

  case 19:
#line 403 "cexp.y"
    { yyval.integer.signedp = yyvsp[-2].integer.signedp;
			  if ((yyvsp[0].integer.value & yyvsp[0].integer.signedp) < 0)
			    yyval.integer.value = left_shift (&yyvsp[-2].integer, -yyvsp[0].integer.value);
			  else
			    yyval.integer.value = right_shift (&yyvsp[-2].integer, yyvsp[0].integer.value); ;}
    break;

  case 20:
#line 409 "cexp.y"
    { yyval.integer.value = (yyvsp[-2].integer.value == yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 21:
#line 412 "cexp.y"
    { yyval.integer.value = (yyvsp[-2].integer.value != yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 22:
#line 415 "cexp.y"
    { yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value <= yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					<= yyvsp[0].integer.value); ;}
    break;

  case 23:
#line 422 "cexp.y"
    { yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value >= yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					>= yyvsp[0].integer.value); ;}
    break;

  case 24:
#line 429 "cexp.y"
    { yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value < yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					< yyvsp[0].integer.value); ;}
    break;

  case 25:
#line 436 "cexp.y"
    { yyval.integer.signedp = SIGNED;
			  if (yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp)
			    yyval.integer.value = yyvsp[-2].integer.value > yyvsp[0].integer.value;
			  else
			    yyval.integer.value = ((unsigned_HOST_WIDE_INT) yyvsp[-2].integer.value
					> yyvsp[0].integer.value); ;}
    break;

  case 26:
#line 443 "cexp.y"
    { yyval.integer.value = yyvsp[-2].integer.value & yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;}
    break;

  case 27:
#line 446 "cexp.y"
    { yyval.integer.value = yyvsp[-2].integer.value ^ yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;}
    break;

  case 28:
#line 449 "cexp.y"
    { yyval.integer.value = yyvsp[-2].integer.value | yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-2].integer.signedp & yyvsp[0].integer.signedp; ;}
    break;

  case 29:
#line 452 "cexp.y"
    { skip_evaluation += !yyvsp[-1].integer.value; ;}
    break;

  case 30:
#line 454 "cexp.y"
    { skip_evaluation -= !yyvsp[-3].integer.value;
			  yyval.integer.value = (yyvsp[-3].integer.value && yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 31:
#line 458 "cexp.y"
    { skip_evaluation += !!yyvsp[-1].integer.value; ;}
    break;

  case 32:
#line 460 "cexp.y"
    { skip_evaluation -= !!yyvsp[-3].integer.value;
			  yyval.integer.value = (yyvsp[-3].integer.value || yyvsp[0].integer.value);
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 33:
#line 464 "cexp.y"
    { skip_evaluation += !yyvsp[-1].integer.value; ;}
    break;

  case 34:
#line 466 "cexp.y"
    { skip_evaluation += !!yyvsp[-4].integer.value - !yyvsp[-4].integer.value; ;}
    break;

  case 35:
#line 468 "cexp.y"
    { skip_evaluation -= !!yyvsp[-6].integer.value;
			  yyval.integer.value = yyvsp[-6].integer.value ? yyvsp[-3].integer.value : yyvsp[0].integer.value;
			  yyval.integer.signedp = yyvsp[-3].integer.signedp & yyvsp[0].integer.signedp; ;}
    break;

  case 36:
#line 472 "cexp.y"
    { yyval.integer = yylval.integer; ;}
    break;

  case 37:
#line 474 "cexp.y"
    { yyval.integer = yylval.integer; ;}
    break;

  case 38:
#line 476 "cexp.y"
    { if (warn_undef && !skip_evaluation)
			    warning ("`%.*s' is not defined",
				     yyvsp[0].name.length, yyvsp[0].name.address);
			  yyval.integer.value = 0;
			  yyval.integer.signedp = SIGNED; ;}
    break;

  case 39:
#line 484 "cexp.y"
    { yyval.keywords = 0; ;}
    break;

  case 40:
#line 486 "cexp.y"
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
			  temp->next->length = 1; ;}
    break;

  case 41:
#line 499 "cexp.y"
    { yyval.keywords = (struct arglist *) xmalloc (sizeof (struct arglist));
			  yyval.keywords->name = yyvsp[-1].name.address;
			  yyval.keywords->length = yyvsp[-1].name.length;
			  yyval.keywords->next = yyvsp[0].keywords; ;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 1641 "cexp.c"

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


#line 504 "cexp.y"


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

  case '\'':
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


