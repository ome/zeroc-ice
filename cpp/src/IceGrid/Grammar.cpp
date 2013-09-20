
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "Grammar.y"


// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
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



/* Line 189 of yacc.c  */
#line 108 "Grammar.tab.c"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     ICE_GRID_SOCKETS = 267,
     ICE_GRID_ADD = 268,
     ICE_GRID_REMOVE = 269,
     ICE_GRID_LIST = 270,
     ICE_GRID_SHUTDOWN = 271,
     ICE_GRID_STRING = 272,
     ICE_GRID_START = 273,
     ICE_GRID_STOP = 274,
     ICE_GRID_PATCH = 275,
     ICE_GRID_SIGNAL = 276,
     ICE_GRID_STDOUT = 277,
     ICE_GRID_STDERR = 278,
     ICE_GRID_DESCRIBE = 279,
     ICE_GRID_PROPERTIES = 280,
     ICE_GRID_PROPERTY = 281,
     ICE_GRID_STATE = 282,
     ICE_GRID_PID = 283,
     ICE_GRID_ENDPOINTS = 284,
     ICE_GRID_ACTIVATION = 285,
     ICE_GRID_OBJECT = 286,
     ICE_GRID_FIND = 287,
     ICE_GRID_SHOW = 288,
     ICE_GRID_COPYING = 289,
     ICE_GRID_WARRANTY = 290,
     ICE_GRID_DIFF = 291,
     ICE_GRID_UPDATE = 292,
     ICE_GRID_INSTANTIATE = 293,
     ICE_GRID_TEMPLATE = 294,
     ICE_GRID_SERVICE = 295,
     ICE_GRID_ENABLE = 296,
     ICE_GRID_DISABLE = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 192 "Grammar.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2612

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNRULES -- Number of states.  */
#define YYNSTATES  367

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,    10,    13,    14,    17,    20,
      25,    30,    35,    40,    45,    50,    55,    60,    65,    70,
      75,    80,    85,    90,    96,   102,   108,   114,   119,   125,
     131,   136,   141,   146,   151,   156,   161,   166,   171,   176,
     181,   186,   191,   196,   201,   206,   211,   216,   221,   226,
     231,   236,   241,   246,   251,   256,   261,   266,   271,   276,
     281,   286,   291,   296,   301,   306,   311,   316,   321,   326,
     331,   336,   341,   346,   351,   356,   361,   366,   371,   376,
     381,   386,   391,   396,   401,   406,   411,   416,   421,   426,
     431,   436,   441,   446,   451,   456,   461,   466,   471,   476,
     481,   486,   491,   496,   501,   506,   511,   516,   521,   526,
     531,   536,   541,   546,   551,   556,   560,   564,   568,   573,
     579,   585,   592,   597,   601,   605,   610,   614,   618,   621,
     623,   626,   629,   633,   637,   638,   640,   642,   644,   646,
     648,   650,   652,   654,   656,   658,   660,   662,   664,   666,
     668,   670,   672,   674,   676,   678,   680,   682,   684,   686,
     688,   690,   692,   694,   696,   698,   700,   702,   704,   706,
     708,   710,   712
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    -1,    46,    47,    48,    -1,
      47,    48,    -1,    -1,     3,    43,    -1,     4,    43,    -1,
       5,    13,    49,    43,    -1,     5,    13,     3,    43,    -1,
       5,    14,    49,    43,    -1,     5,    14,     3,    43,    -1,
       5,    36,    49,    43,    -1,     5,    36,     3,    43,    -1,
       5,    37,    49,    43,    -1,     5,    37,     3,    43,    -1,
       5,    24,    49,    43,    -1,     5,    24,     3,    43,    -1,
       5,    20,    49,    43,    -1,     5,    20,     3,    43,    -1,
       5,    15,    49,    43,    -1,     5,    15,     3,    43,    -1,
       8,    39,    24,    49,    43,    -1,     8,    39,    24,     3,
      43,    -1,     8,    39,    38,    49,    43,    -1,     8,    39,
      38,     3,    43,    -1,     8,    39,     3,    43,    -1,    40,
      39,    24,    49,    43,    -1,    40,    39,    24,     3,    43,
      -1,    40,    39,     3,    43,    -1,     6,    24,    49,    43,
      -1,     6,    24,     3,    43,    -1,     6,    10,    49,    43,
      -1,     6,    10,     3,    43,    -1,     6,    11,    49,    43,
      -1,     6,    11,     3,    43,    -1,     6,    12,    49,    43,
      -1,     6,    12,     3,    43,    -1,     6,    16,    49,    43,
      -1,     6,    16,     3,    43,    -1,     6,    15,    49,    43,
      -1,     6,    15,     3,    43,    -1,     6,    33,    49,    43,
      -1,     6,    33,     3,    43,    -1,     7,    24,    49,    43,
      -1,     7,    24,     3,    43,    -1,     7,    10,    49,    43,
      -1,     7,    10,     3,    43,    -1,     7,    16,    49,    43,
      -1,     7,    16,     3,    43,    -1,     7,    15,    49,    43,
      -1,     7,    15,     3,    43,    -1,     7,    33,    49,    43,
      -1,     7,    33,     3,    43,    -1,     8,    14,    49,    43,
      -1,     8,    14,     3,    43,    -1,     8,    24,    49,    43,
      -1,     8,    24,     3,    43,    -1,     8,    18,    49,    43,
      -1,     8,    18,     3,    43,    -1,     8,    19,    49,    43,
      -1,     8,    19,     3,    43,    -1,     8,    20,    49,    43,
      -1,     8,    20,     3,    43,    -1,     8,    21,    49,    43,
      -1,     8,    21,     3,    43,    -1,     8,    22,    49,    43,
      -1,     8,    22,     3,    43,    -1,     8,    23,    49,    43,
      -1,     8,    23,     3,    43,    -1,     8,    27,    49,    43,
      -1,     8,    27,     3,    43,    -1,     8,    28,    49,    43,
      -1,     8,    28,     3,    43,    -1,     8,    25,    49,    43,
      -1,     8,    25,     3,    43,    -1,     8,    26,    49,    43,
      -1,     8,    26,     3,    43,    -1,     8,    41,    49,    43,
      -1,     8,    41,     3,    43,    -1,     8,    42,    49,    43,
      -1,     8,    42,     3,    43,    -1,     8,    15,    49,    43,
      -1,     8,    15,     3,    43,    -1,     8,    33,    49,    43,
      -1,     8,    33,     3,    43,    -1,    40,    18,    49,    43,
      -1,    40,    18,     3,    43,    -1,    40,    19,    49,    43,
      -1,    40,    19,     3,    43,    -1,    40,    24,    49,    43,
      -1,    40,    24,     3,    43,    -1,    40,    25,    49,    43,
      -1,    40,    25,     3,    43,    -1,    40,    26,    49,    43,
      -1,    40,    26,     3,    43,    -1,    40,    15,    49,    43,
      -1,    40,    15,     3,    43,    -1,     9,    29,    49,    43,
      -1,     9,    29,     3,    43,    -1,     9,    14,    49,    43,
      -1,     9,    14,     3,    43,    -1,     9,    15,    49,    43,
      -1,     9,    15,     3,    43,    -1,    31,    13,    49,    43,
      -1,    31,    13,     3,    43,    -1,    31,    14,    49,    43,
      -1,    31,    14,     3,    43,    -1,    31,    32,    49,    43,
      -1,    31,    32,     3,    43,    -1,    31,    15,    49,    43,
      -1,    31,    15,     3,    43,    -1,    31,    24,    49,    43,
      -1,    31,    24,     3,    43,    -1,    33,    34,    43,    -1,
      33,    35,    43,    -1,     3,    50,    43,    -1,     3,    50,
      50,    43,    -1,     3,    50,    17,    49,    43,    -1,     3,
      50,    50,    50,    43,    -1,     3,    50,    50,    17,    49,
      43,    -1,     3,    17,    49,    43,    -1,     3,     1,    43,
      -1,    50,     3,    43,    -1,    50,    17,     1,    43,    -1,
      50,     1,    43,    -1,    17,     1,    43,    -1,     1,    43,
      -1,    43,    -1,    17,    49,    -1,    50,    49,    -1,    17,
       3,    49,    -1,    50,     3,    49,    -1,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,
      15,    -1,    16,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    24,    -1,    27,    -1,    28,    -1,    25,    -1,
      26,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      23,    -1,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    92,    99,   102,   109,   117,   121,   125,
     129,   133,   137,   141,   145,   149,   153,   157,   161,   165,
     169,   173,   177,   181,   185,   189,   193,   197,   201,   205,
     209,   213,   217,   221,   225,   229,   233,   237,   241,   245,
     249,   253,   257,   261,   265,   269,   273,   277,   281,   285,
     289,   293,   297,   301,   305,   309,   313,   317,   321,   325,
     329,   333,   337,   341,   345,   349,   353,   357,   361,   365,
     369,   373,   377,   381,   385,   389,   393,   397,   401,   405,
     409,   413,   417,   421,   425,   429,   433,   437,   441,   445,
     449,   453,   457,   461,   465,   469,   473,   477,   481,   485,
     489,   493,   497,   501,   505,   509,   513,   517,   521,   525,
     529,   533,   537,   541,   545,   549,   553,   557,   561,   572,
     576,   587,   598,   602,   606,   610,   616,   621,   626,   630,
     639,   644,   649,   655,   662,   670,   673,   676,   679,   682,
     685,   688,   691,   694,   697,   700,   703,   706,   709,   712,
     715,   718,   721,   724,   727,   730,   733,   736,   739,   742,
     745,   748,   751,   754,   757,   760,   763,   766,   769,   772,
     775,   778,   781
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ICE_GRID_HELP", "ICE_GRID_EXIT",
  "ICE_GRID_APPLICATION", "ICE_GRID_NODE", "ICE_GRID_REGISTRY",
  "ICE_GRID_SERVER", "ICE_GRID_ADAPTER", "ICE_GRID_PING", "ICE_GRID_LOAD",
  "ICE_GRID_SOCKETS", "ICE_GRID_ADD", "ICE_GRID_REMOVE", "ICE_GRID_LIST",
  "ICE_GRID_SHUTDOWN", "ICE_GRID_STRING", "ICE_GRID_START",
  "ICE_GRID_STOP", "ICE_GRID_PATCH", "ICE_GRID_SIGNAL", "ICE_GRID_STDOUT",
  "ICE_GRID_STDERR", "ICE_GRID_DESCRIBE", "ICE_GRID_PROPERTIES",
  "ICE_GRID_PROPERTY", "ICE_GRID_STATE", "ICE_GRID_PID",
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
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      49,    49,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     3,     2,     0,     2,     2,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     5,     5,     5,     5,     4,     5,     5,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     4,     5,
       5,     6,     4,     3,     3,     4,     3,     3,     2,     1,
       2,     2,     3,     3,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     6,     0,     1,     0,     0,     0,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,     0,   148,   149,   150,   151,   172,   171,   152,   155,
     156,   153,   154,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   129,     5,     0,
       4,   128,     0,   135,   136,   137,   138,   139,   140,   134,
     159,   161,   168,     7,     0,     8,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,     0,
     134,   134,   134,   134,   134,     0,   134,   134,   134,   134,
     134,     0,     0,   134,   134,   134,   134,   134,   134,     0,
       0,     0,     0,   123,   134,     0,   134,   134,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   134,   126,   124,     0,   134,
     130,   122,   134,   131,     0,   134,   118,     0,    10,     9,
      12,    11,    22,    21,    20,    19,    18,    17,    14,    13,
      16,    15,    34,    33,    36,    35,    38,    37,    42,    41,
      40,    39,    32,    31,    44,    43,    48,    47,    52,    51,
      50,    49,    46,    45,    54,    53,    56,    55,    84,    83,
      60,    59,    62,    61,    64,    63,    66,    65,    68,    67,
      70,    69,    58,    57,    76,    75,    78,    77,    72,    71,
      74,    73,    86,    85,    27,     0,     0,     0,     0,    80,
      79,    82,    81,   102,   101,   104,   103,   100,    99,   106,
     105,   108,   107,   112,   111,   114,   113,   110,   109,    98,
      97,    88,    87,    90,    89,    92,    91,    94,    93,    96,
      95,    30,     0,     0,   125,   132,   133,   119,     0,   120,
      24,    23,    26,    25,    29,    28,   121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,    48,   125,   126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
      39,    53,    56,    61,   -67,    61,    20,   179,    69,    93,
     142,  2492,   123,    95,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   117,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   146,   -67,    11,   -67,   -67,
     -67,   -67,   -67,   -67,    96,   -67,   -67,   -67,   -67,   122,
     -67,   -67,    76,   -67,   -67,   -67,   -67,   -67,   -67,  2459,
     -67,   -67,   -67,   -67,   219,   -67,   260,   300,   340,   380,
     420,   460,   500,   540,   580,   620,   660,   700,   740,   780,
     820,   860,   900,   940,   980,  1020,  1060,  1100,  1140,  1180,
    1220,  1260,  1300,  1340,  1380,  1420,  1460,  1500,  1540,   102,
    1580,  1620,  1660,  1700,  1740,    84,  1780,  1820,  1860,  1900,
    1940,    85,    90,  1980,  2020,  2060,  2100,  2140,  2180,    30,
      91,   112,   135,   -67,  2220,   120,  2260,  2459,   -67,  2299,
     124,   125,   128,   129,   131,   134,   139,  2460,  2461,  2462,
    2463,  2466,  2467,  2468,  2469,  2470,  2471,  2472,  2474,  2475,
    2476,  2477,  2478,  2479,  2480,  2481,  2483,  2484,  2485,  2486,
    2487,  2488,  2489,  2490,  2491,  2493,  2494,  2495,  2496,  2497,
    2498,  2499,  2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,
    2508,  2509,  2510,  2511,  2512,  2513,  2514,  2515,  2516,  2517,
    2518,  2519,  2520,  2521,  2522,  2523,  2524,  2340,  2380,  2525,
    2526,  2527,  2528,  2529,  2530,  2531,  2532,  2533,  2534,   -67,
    2535,  2536,  2537,  2538,  2539,  2540,  2541,  2542,  2543,  2544,
     -67,   -67,  2545,  2546,  2547,  2548,  2549,  2550,  2551,  2552,
    2553,  2554,  2555,  2556,  2557,  2420,   -67,   -67,  2558,  2459,
     -67,   -67,  2459,   -67,  2559,  2459,   -67,  2560,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,  2561,  2562,  2563,  2564,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,  2565,  2566,   -67,   -67,   -67,   -67,  2567,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,  2609,  2607,   -66,    52
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
     131,   133,   135,   137,   139,   141,   143,   145,   147,   149,
     151,   153,   155,   157,   159,   161,   163,   165,   167,   169,
     171,   173,   175,   177,   179,   181,   183,   185,   187,   189,
     191,   193,   195,   234,   200,   202,   204,   206,   208,    -3,
     211,   213,   215,   217,   219,   111,   112,   223,   225,   227,
     229,   231,   233,     4,   235,    49,    -2,    49,   240,    64,
     243,   244,     6,    51,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   196,    66,    67,    68,   102,
     103,   113,    65,    69,   114,   115,   129,    70,   105,   123,
     116,   117,   118,   120,   104,   121,   197,   209,   220,    71,
      72,   316,   318,   221,   236,   119,   238,    85,    86,   122,
     198,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    73,    74,    75,   237,    98,    76,    77,   106,
     107,   108,    99,   241,   100,   101,    78,   248,   249,   353,
     109,   250,   251,   355,   252,    79,   356,   253,   110,   358,
      52,   247,   254,    53,    54,    55,    56,    57,    58,    14,
      15,    16,    17,    18,    19,    20,    59,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      60,    36,    61,    38,    39,    40,    41,    42,    43,    62,
      45,    46,    63,    53,    54,    55,    56,    57,    58,    14,
      15,    16,    17,    18,    19,    20,   127,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      60,    36,    61,    38,    39,    40,    41,    42,    43,    62,
      45,    46,   128,   130,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   132,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   134,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   136,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   138,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   140,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   142,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   144,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   146,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   148,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   150,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   152,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   154,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   156,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   158,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   160,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   162,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   164,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   166,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   168,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   170,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   172,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   174,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   176,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   178,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   180,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   182,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   184,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   186,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   188,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   190,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   192,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   194,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   199,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   201,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   203,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   205,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   207,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   210,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   212,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   214,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   216,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   218,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   222,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   224,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   226,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   228,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   230,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   232,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   239,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   242,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,    53,    54,    55,    56,    57,    58,    14,
      15,    16,    17,    18,    19,    20,   245,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      60,    36,    61,    38,    39,    40,    41,    42,    43,    62,
      45,    46,   246,   315,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   317,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,   352,    53,    54,    55,    56,    57,    58,
      14,    15,    16,    17,    18,    19,    20,   124,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    60,    36,    61,    38,    39,    40,    41,    42,    43,
      62,    45,    46,    53,    54,    55,    56,    57,    58,    14,
      15,    16,    17,    18,    19,    20,   124,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      60,    36,    61,    38,    39,    40,    41,    42,    43,    62,
      45,    46,    80,   255,   256,   257,   258,    81,    82,   259,
     260,   261,   262,   263,   264,   265,    83,   266,   267,   268,
     269,   270,   271,   272,   273,    84,   274,   275,   276,   277,
     278,   279,   280,   281,   282,     0,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   354,   357,   359,   360,   361,   362,   363,   364,   365,
     366,     5,    50
};

static const yytype_int16 yycheck[] =
{
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     3,   100,   101,   102,   103,   104,     0,
     106,   107,   108,   109,   110,    34,    35,   113,   114,   115,
     116,   117,   118,     0,    24,     3,     0,     5,   124,     7,
     126,   127,     1,    43,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,     3,    13,    14,    15,    14,
      15,    15,    43,    20,    18,    19,    64,    24,     1,    43,
      24,    25,    26,     1,    29,     3,    24,    43,    43,    36,
      37,   197,   198,    43,    43,    39,     1,    14,    15,    17,
      38,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    10,    11,    12,    43,    33,    15,    16,    13,
      14,    15,    39,    43,    41,    42,    24,    43,    43,   235,
      24,    43,    43,   239,    43,    33,   242,    43,    32,   245,
       1,   129,    43,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    10,    43,    43,    43,    43,    15,    16,    43,
      43,    43,    43,    43,    43,    43,    24,    43,    43,    43,
      43,    43,    43,    43,    43,    33,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    -1,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,     2,     5
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    46,    47,     0,    47,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    48,    50,
      48,    43,     1,     4,     5,     6,     7,     8,     9,    17,
      31,    33,    40,    43,    50,    43,    13,    14,    15,    20,
      24,    36,    37,    10,    11,    12,    15,    16,    24,    33,
      10,    15,    16,    24,    33,    14,    15,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    33,    39,
      41,    42,    14,    15,    29,     1,    13,    14,    15,    24,
      32,    34,    35,    15,    18,    19,    24,    25,    26,    39,
       1,     3,    17,    43,    17,    49,    50,    17,    43,    50,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    49,     3,    24,    38,     3,
      49,     3,    49,     3,    49,     3,    49,     3,    49,    43,
       3,    49,     3,    49,     3,    49,     3,    49,     3,    49,
      43,    43,     3,    49,     3,    49,     3,    49,     3,    49,
       3,    49,     3,    49,     3,    24,    43,    43,     1,     3,
      49,    43,     3,    49,    49,    17,    43,    50,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,     3,    49,     3,    49,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,     3,    49,    43,    49,    49,    43,    49,    43,
      43,    43,    43,    43,    43,    43,    43
};

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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

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
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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

/* Line 1455 of yacc.c  */
#line 89 "Grammar.y"
    {
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 92 "Grammar.y"
    {
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 100 "Grammar.y"
    {
;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 103 "Grammar.y"
    {
;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 109 "Grammar.y"
    {
    parser->checkInterrupted();
;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 118 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 122 "Grammar.y"
    {
    return 0;
;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 126 "Grammar.y"
    {
    parser->addApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 130 "Grammar.y"
    {
    parser->usage("application", "add");
;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 134 "Grammar.y"
    {
    parser->removeApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 138 "Grammar.y"
    {
    parser->usage("application", "remove");
;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 142 "Grammar.y"
    {
    parser->diffApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 146 "Grammar.y"
    {
    parser->usage("application", "diff");
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 150 "Grammar.y"
    {
    parser->updateApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 154 "Grammar.y"
    {
    parser->usage("application", "update");
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 158 "Grammar.y"
    {
    parser->describeApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 162 "Grammar.y"
    {
    parser->usage("application", "describe");
;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 166 "Grammar.y"
    {
    parser->patchApplication((yyvsp[(3) - (4)]));
;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 170 "Grammar.y"
    {
    parser->usage("application", "patch");
;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 174 "Grammar.y"
    {
    parser->listAllApplications((yyvsp[(3) - (4)]));
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 178 "Grammar.y"
    {
    parser->usage("application", "list");
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 182 "Grammar.y"
    {
    parser->describeServerTemplate((yyvsp[(4) - (5)]));
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 186 "Grammar.y"
    {
    parser->usage("server template", "describe");
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 190 "Grammar.y"
    {
    parser->instantiateServerTemplate((yyvsp[(4) - (5)]));
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 194 "Grammar.y"
    {
    parser->usage("server template", "instantiate");
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 198 "Grammar.y"
    {
    parser->usage("server template");
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 202 "Grammar.y"
    {
    parser->describeServiceTemplate((yyvsp[(4) - (5)]));
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 206 "Grammar.y"
    {
    parser->usage("service template", "describe");
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 210 "Grammar.y"
    {
    parser->usage("service template");
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 214 "Grammar.y"
    {
    parser->describeNode((yyvsp[(3) - (4)]));
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 218 "Grammar.y"
    {
    parser->usage("node", "describe");
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 222 "Grammar.y"
    {
    parser->pingNode((yyvsp[(3) - (4)]));
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 226 "Grammar.y"
    {
    parser->usage("node", "ping");
;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 230 "Grammar.y"
    {
    parser->printLoadNode((yyvsp[(3) - (4)]));
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 234 "Grammar.y"
    {
    parser->usage("node", "load");
;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 238 "Grammar.y"
    {
    parser->printNodeProcessorSockets((yyvsp[(3) - (4)]));
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 242 "Grammar.y"
    {
    parser->usage("node", "sockets");
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 246 "Grammar.y"
    {
    parser->shutdownNode((yyvsp[(3) - (4)]));
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 250 "Grammar.y"
    {
    parser->usage("node", "shutdown");
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 254 "Grammar.y"
    {
    parser->listAllNodes((yyvsp[(3) - (4)]));
;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 258 "Grammar.y"
    {
    parser->usage("node", "list");
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 262 "Grammar.y"
    {
    parser->showFile("node", (yyvsp[(3) - (4)]));
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 266 "Grammar.y"
    {
    parser->usage("node", "show");
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 270 "Grammar.y"
    {
    parser->describeRegistry((yyvsp[(3) - (4)]));
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 274 "Grammar.y"
    {
    parser->usage("registry", "describe");
;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 278 "Grammar.y"
    {
    parser->pingRegistry((yyvsp[(3) - (4)]));
;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 282 "Grammar.y"
    {
    parser->usage("registry", "ping");
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 286 "Grammar.y"
    {
    parser->shutdownRegistry((yyvsp[(3) - (4)]));
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 290 "Grammar.y"
    {
    parser->usage("registry", "shutdown");
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 294 "Grammar.y"
    {
    parser->listAllRegistries((yyvsp[(3) - (4)]));
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 298 "Grammar.y"
    {
    parser->usage("registry", "list");
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 302 "Grammar.y"
    {
    parser->showFile("registry", (yyvsp[(3) - (4)]));
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 306 "Grammar.y"
    {
    parser->usage("registry", "show");
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 310 "Grammar.y"
    {
    parser->removeServer((yyvsp[(3) - (4)]));
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 314 "Grammar.y"
    {
    parser->usage("server", "remove");
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 318 "Grammar.y"
    {
    parser->describeServer((yyvsp[(3) - (4)]));
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 322 "Grammar.y"
    {
    parser->usage("server", "describe");
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 326 "Grammar.y"
    {
    parser->startServer((yyvsp[(3) - (4)]));
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 330 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 334 "Grammar.y"
    {
    parser->stopServer((yyvsp[(3) - (4)]));
;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 338 "Grammar.y"
    {
    parser->usage("server", "stop");
;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 342 "Grammar.y"
    {
    parser->patchServer((yyvsp[(3) - (4)]));
;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 346 "Grammar.y"
    {
    parser->usage("server", "patch");
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 350 "Grammar.y"
    {
    parser->signalServer((yyvsp[(3) - (4)]));
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 354 "Grammar.y"
    {
    parser->usage("server", "signal");
;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 358 "Grammar.y"
    {
    parser->writeMessage((yyvsp[(3) - (4)]), 1);
;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 362 "Grammar.y"
    {
    parser->usage("server", "stdout");
;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 366 "Grammar.y"
    {
    parser->writeMessage((yyvsp[(3) - (4)]), 2);
;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 370 "Grammar.y"
    {
    parser->usage("server", "stderr");
;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 374 "Grammar.y"
    {
    parser->stateServer((yyvsp[(3) - (4)]));
;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 378 "Grammar.y"
    {
    parser->usage("server", "start");
;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 382 "Grammar.y"
    {
    parser->pidServer((yyvsp[(3) - (4)]));
;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 386 "Grammar.y"
    {
    parser->usage("server", "pid");
;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 390 "Grammar.y"
    {
    parser->propertiesServer((yyvsp[(3) - (4)]), false);
;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 394 "Grammar.y"
    {
    parser->usage("server", "properties");
;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 398 "Grammar.y"
    {
    parser->propertiesServer((yyvsp[(3) - (4)]), true);
;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 402 "Grammar.y"
    {
    parser->usage("server", "property");
;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 406 "Grammar.y"
    {
    parser->enableServer((yyvsp[(3) - (4)]), true);
;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 410 "Grammar.y"
    {
    parser->usage("server", "enable");
;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 414 "Grammar.y"
    {
    parser->enableServer((yyvsp[(3) - (4)]), false);
;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 418 "Grammar.y"
    {
    parser->usage("server", "disable");
;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 422 "Grammar.y"
    {
    parser->listAllServers((yyvsp[(3) - (4)]));
;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 426 "Grammar.y"
    {
    parser->usage("server", "list");
;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 430 "Grammar.y"
    {
    parser->showFile("server", (yyvsp[(3) - (4)]));
;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 434 "Grammar.y"
    {
    parser->usage("server", "show");
;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 438 "Grammar.y"
    {
    parser->startService((yyvsp[(3) - (4)]));
;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 442 "Grammar.y"
    {
    parser->usage("service", "start");
;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 446 "Grammar.y"
    {
    parser->stopService((yyvsp[(3) - (4)]));
;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 450 "Grammar.y"
    {
    parser->usage("service", "stop");
;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 454 "Grammar.y"
    {
    parser->describeService((yyvsp[(3) - (4)]));
;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 458 "Grammar.y"
    {
    parser->usage("service", "describe");
;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 462 "Grammar.y"
    {
    parser->propertiesService((yyvsp[(3) - (4)]), false);
;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 466 "Grammar.y"
    {
    parser->usage("service", "properties");
;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 470 "Grammar.y"
    {
    parser->propertiesService((yyvsp[(3) - (4)]), true);
;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 474 "Grammar.y"
    {
    parser->usage("service", "property");
;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 478 "Grammar.y"
    {
    parser->listServices((yyvsp[(3) - (4)]));
;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 482 "Grammar.y"
    {
    parser->usage("service", "list");
;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 486 "Grammar.y"
    {
    parser->endpointsAdapter((yyvsp[(3) - (4)]));
;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 490 "Grammar.y"
    {
    parser->usage("adapter", "endpoints");
;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 494 "Grammar.y"
    {
    parser->removeAdapter((yyvsp[(3) - (4)]));
;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 498 "Grammar.y"
    {
    parser->usage("adapter", "remove");
;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 502 "Grammar.y"
    {
    parser->listAllAdapters((yyvsp[(3) - (4)]));
;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 506 "Grammar.y"
    {
    parser->usage("adapter", "list");
;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 510 "Grammar.y"
    {
    parser->addObject((yyvsp[(3) - (4)]));
;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 514 "Grammar.y"
    {
    parser->usage("object", "add");
;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 518 "Grammar.y"
    {
    parser->removeObject((yyvsp[(3) - (4)]));
;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 522 "Grammar.y"
    {
    parser->usage("object", "remove");
;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 526 "Grammar.y"
    {
    parser->findObject((yyvsp[(3) - (4)]));
;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 530 "Grammar.y"
    {
    parser->usage("object", "find");
;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 534 "Grammar.y"
    {
    parser->listObject((yyvsp[(3) - (4)]));
;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 538 "Grammar.y"
    {
    parser->usage("object", "list");
;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 542 "Grammar.y"
    {
    parser->describeObject((yyvsp[(3) - (4)]));
;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 546 "Grammar.y"
    {
    parser->usage("object", "describe");
;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 550 "Grammar.y"
    {
    parser->showCopying();
;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 554 "Grammar.y"
    {
    parser->showWarranty();
;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 558 "Grammar.y"
    {
    parser->usage((yyvsp[(2) - (3)]).front());
;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 562 "Grammar.y"
    {
    if(((yyvsp[(2) - (4)]).front() == "server" || (yyvsp[(2) - (4)]).front() == "service") && (yyvsp[(3) - (4)]).front() == "template")
    {
        parser->usage((yyvsp[(2) - (4)]).front() + " " + (yyvsp[(3) - (4)]).front());
    }
    else
    {
        parser->usage((yyvsp[(2) - (4)]).front(), (yyvsp[(3) - (4)]).front());
    }
;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 573 "Grammar.y"
    {
    parser->usage((yyvsp[(2) - (5)]).front(), (yyvsp[(3) - (5)]).front());
;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 577 "Grammar.y"
    {
    if(((yyvsp[(2) - (5)]).front() == "server" || (yyvsp[(2) - (5)]).front() == "service") && (yyvsp[(3) - (5)]).front() == "template")
    {
        parser->usage((yyvsp[(2) - (5)]).front() + " " + (yyvsp[(3) - (5)]).front(), (yyvsp[(4) - (5)]).front());
    }
    else
    {
        parser->usage((yyvsp[(2) - (5)]).front(), (yyvsp[(3) - (5)]).front());
    }
;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 588 "Grammar.y"
    {
    if(((yyvsp[(2) - (6)]).front() == "server" || (yyvsp[(2) - (6)]).front() == "service") && (yyvsp[(3) - (6)]).front() == "template")
    {
        parser->usage((yyvsp[(2) - (6)]).front() + " " + (yyvsp[(3) - (6)]).front(), (yyvsp[(4) - (6)]).front());
    }
    else
    {
        parser->usage((yyvsp[(2) - (6)]).front(), (yyvsp[(3) - (6)]).front());
    }
;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 599 "Grammar.y"
    {
    parser->usage((yyvsp[(2) - (4)]).front());
;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 603 "Grammar.y"
    {
    parser->usage();
;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 607 "Grammar.y"
    {
    parser->usage((yyvsp[(1) - (3)]).front());
;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 611 "Grammar.y"
    {
    (yyvsp[(1) - (4)]).push_back((yyvsp[(2) - (4)]).front());
    parser->invalidCommand((yyvsp[(1) - (4)]));
    yyerrok;
;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 617 "Grammar.y"
    {
    parser->invalidCommand((yyvsp[(1) - (3)]));
    yyerrok;
;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 622 "Grammar.y"
    {
    parser->invalidCommand((yyvsp[(1) - (3)]));
    yyerrok;
;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 627 "Grammar.y"
    {
    yyerrok;
;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 631 "Grammar.y"
    {
;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 640 "Grammar.y"
    {
    (yyval) = (yyvsp[(2) - (2)]);
    (yyval).push_front((yyvsp[(1) - (2)]).front());
;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 645 "Grammar.y"
    {
    (yyval) = (yyvsp[(2) - (2)]);
    (yyval).push_front((yyvsp[(1) - (2)]).front());
;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 650 "Grammar.y"
    {
    (yyval) = (yyvsp[(2) - (3)]);
    (yyval).push_front("help");
    (yyval).push_front((yyvsp[(1) - (3)]).front());
;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 656 "Grammar.y"
    {
    (yyval) = (yyvsp[(2) - (3)]);
    (yyval).push_front("help");
    (yyval).push_front((yyvsp[(1) - (3)]).front());
;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 662 "Grammar.y"
    {
    (yyval) = YYSTYPE();
;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 671 "Grammar.y"
    {
;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 674 "Grammar.y"
    {
;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 677 "Grammar.y"
    {
;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 680 "Grammar.y"
    {
;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 683 "Grammar.y"
    {
;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 686 "Grammar.y"
    {
;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 689 "Grammar.y"
    {
;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 692 "Grammar.y"
    {
;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 695 "Grammar.y"
    {
;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 698 "Grammar.y"
    {
;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 701 "Grammar.y"
    {
;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 704 "Grammar.y"
    {
;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 707 "Grammar.y"
    {
;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 710 "Grammar.y"
    {
;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 713 "Grammar.y"
    {
;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 716 "Grammar.y"
    {
;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 719 "Grammar.y"
    {
;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 722 "Grammar.y"
    {
;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 725 "Grammar.y"
    {
;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 728 "Grammar.y"
    {
;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 731 "Grammar.y"
    {
;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 734 "Grammar.y"
    {
;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 737 "Grammar.y"
    {
;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 740 "Grammar.y"
    {
;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 743 "Grammar.y"
    {
;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 746 "Grammar.y"
    {
;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 749 "Grammar.y"
    {
;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 752 "Grammar.y"
    {
;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 755 "Grammar.y"
    {
;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 758 "Grammar.y"
    {
;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 761 "Grammar.y"
    {
;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 764 "Grammar.y"
    {
;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 767 "Grammar.y"
    {
;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 770 "Grammar.y"
    {
;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 773 "Grammar.y"
    {
;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 776 "Grammar.y"
    {
;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 779 "Grammar.y"
    {
;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 782 "Grammar.y"
    {
;}
    break;



/* Line 1455 of yacc.c  */
#line 3684 "Grammar.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
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
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



