/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/sharpie.y" /* yacc.c:339  */

#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include "../include/attr.h"

using namespace std;
#define X first
#define Y second
#define pb push_back

/*#define YYDEBUG 1*/

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
#define YYERROR_VERBOSE
extern int yylineno;



map<int, string> TknStr;
map<int, int> FreqToken;
vector<vector<string> > R;
vector<string> T;
SymTable* CurTable;
int CurLabel;

void Combine(vector<string> &a, vector<string> b, vector<string> c){
  b.insert(b.end(),c.begin(),c.end());
  a=b;
}

string getTAC(int flag, string OP, string dest, string op1, string op2="NONE"){
  if(flag == 1){
    return OP+","+dest+","+op1+","+op2;
  }
  if(flag == 2){
    return OP+","+dest+","+op1;
  }
}

void translate(Attr* &p, Attr* q, Attr* r, string OP){
    string tp = CurTable->getTemp();
    p = new Attr();
    p->place = tp;
    Combine(p->code,q->code, r->code);
    string code_ = getTAC(1, OP, p->place, q->place, r->place);
    p->code.pb(code_);
}

void BeginScope(){
  SymTable* newTable = new SymTable();
  (CurTable->children).pb(newTable);
  newTable->parent = CurTable;
  CurTable = newTable;
}

void EndScope(){
  CurTable=CurTable->parent;
}

string getLabel(){
  CurLabel++;
  return "L"+to_string(CurLabel);
}



#line 139 "sharpie.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sharpie.tab.h".  */
#ifndef YY_YY_SHARPIE_TAB_H_INCLUDED
# define YY_YY_SHARPIE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER_LITERAL = 300,
    CHARACTER_LITERAL = 301,
    COMMA = 302,
    LEFT_BRACKET = 303,
    RIGHT_BRACKET = 304,
    RANK_SPECIFIER = 305,
    PLUSEQ = 306,
    MINUSEQ = 307,
    STAREQ = 308,
    DIVEQ = 309,
    MODEQ = 310,
    XOREQ = 311,
    ANDEQ = 312,
    OREQ = 313,
    LTLT = 314,
    GTGT = 315,
    GTGTEQ = 316,
    LTLTEQ = 317,
    EQEQ = 318,
    NOTEQ = 319,
    LEQ = 320,
    GEQ = 321,
    ANDAND = 322,
    OROR = 323,
    PLUSPLUS = 324,
    MINUSMINUS = 325,
    ARROW = 326,
    IDENTIFIER = 327,
    INT_TYPE = 328,
    BOOL_TYPE = 329,
    CHAR_TYPE = 330,
    ABSTRACT = 331,
    BREAK = 332,
    BASE = 333,
    CASE = 334,
    CLASS = 335,
    CONST = 336,
    CONTINUE = 337,
    DEFAULT = 338,
    DO = 339,
    ELSE = 340,
    FALSE = 341,
    FOR = 342,
    FOREACH = 343,
    GOTO = 344,
    IF = 345,
    IN = 346,
    INTERFACE = 347,
    NAMESPACE = 348,
    NEW = 349,
    NULL_TYPE = 350,
    OBJECT = 351,
    OPERATOR = 352,
    OUT = 353,
    OVERRIDE = 354,
    PRIVATE = 355,
    PROTECTED = 356,
    PUBLIC = 357,
    RETURN = 358,
    SIZEOF = 359,
    STRING_TYPE = 360,
    STRUCT = 361,
    SWITCH = 362,
    THIS = 363,
    TRUE = 364,
    TYPEOF = 365,
    USING = 366,
    VIRTUAL = 367,
    VOID = 368,
    WHILE = 369,
    STRING_LITERAL = 372,
    COLCOL = 373
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 74 "src/sharpie.y" /* yacc.c:355  */

	int ival;
	float fval;
	char* sval;
	Attr* NT;

#line 261 "sharpie.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SHARPIE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 278 "sharpie.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  167
/* YYNRULES -- Number of rules.  */
#define YYNRULES  358
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  594

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   374

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,     2,     2,    85,    78,     2,
      75,    76,    83,    81,     2,    82,    77,    84,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    91,    95,
      86,    92,    87,    90,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,    89,    94,    80,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       2,     2,    73,    74,     2
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   179,   179,   182,   186,   190,   194,   200,   201,   204,
     209,   214,   217,   222,   225,   230,   233,   236,   239,   246,
     251,   256,   263,   264,   267,   268,   273,   276,   279,   280,
     283,   286,   287,   290,   291,   294,   295,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   309,   312,   313,   314,
     317,   318,   322,   323,   326,   327,   330,   331,   334,   337,
     338,   341,   344,   347,   348,   351,   352,   355,   356,   359,
     362,   363,   368,   371,   372,   373,   376,   379,   382,   385,
     386,   387,   388,   389,   390,   393,   394,   395,   396,   397,
     398,   401,   402,   405,   406,   409,   410,   413,   416,   419,
     422,   427,   430,   437,   442,   445,   448,   453,   456,   459,
     462,   465,   470,   473,   476,   481,   484,   489,   492,   497,
     500,   505,   508,   513,   516,   521,   524,   529,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   559,
     562,   567,   572,   577,   581,   587,   590,   593,   597,   600,
     603,   609,   618,   619,   626,   630,   638,   645,   650,   693,
     697,   703,   709,   717,   720,   725,   731,   735,   738,   741,
     744,   749,   752,   757,   772,   795,   798,   801,   802,   807,
     810,   813,   816,   817,   820,   821,   824,   827,   830,   833,
     838,   841,   844,   847,   848,   851,   852,   855,   856,   859,
     860,   863,   866,   869,   870,   873,   876,   877,   878,   879,
     882,   885,   888,   891,   894,   895,   899,   900,   903,   904,
     907,   908,   911,   914,   915,   918,   922,   927,   930,   935,
     938,   939,   942,   943,   946,   949,   952,   953,   956,   957,
     960,   961,   962,   966,   967,   970,   971,   974,   975,   976,
     977,   978,   981,   984,   985,   988,   989,   990,   993,   994,
     997,  1000,  1001,  1004,  1005,  1008,  1009,  1010,  1011,  1012,
    1013,  1016,  1019,  1022,  1023,  1026,  1027,  1030,  1034,  1037,
    1038,  1041,  1044,  1047,  1048,  1051,  1054,  1057,  1058,  1061,
    1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,  1070,  1071,
    1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,  1080,  1081,
    1082,  1085,  1088,  1091,  1092,  1095,  1096,  1099,  1102,  1103,
    1106,  1107,  1110,  1113,  1114,  1117,  1120,  1123,  1124,  1127,
    1128,  1131,  1132,  1133,  1134,  1135,  1139,  1144,  1147,  1152,
    1156,  1163,  1166,  1167,  1170,  1173,  1176,  1177,  1180,  1181,
    1184,  1187,  1188,  1191,  1192,  1195,  1196,  1199,  1203
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_LITERAL", "CHARACTER_LITERAL",
  "COMMA", "LEFT_BRACKET", "RIGHT_BRACKET", "RANK_SPECIFIER", "PLUSEQ",
  "MINUSEQ", "STAREQ", "DIVEQ", "MODEQ", "XOREQ", "ANDEQ", "OREQ", "LTLT",
  "GTGT", "GTGTEQ", "LTLTEQ", "EQEQ", "NOTEQ", "LEQ", "GEQ", "ANDAND",
  "OROR", "PLUSPLUS", "MINUSMINUS", "ARROW", "IDENTIFIER", "INT_TYPE",
  "BOOL_TYPE", "CHAR_TYPE", "ABSTRACT", "BREAK", "BASE", "CASE", "CLASS",
  "CONST", "CONTINUE", "DEFAULT", "DO", "ELSE", "FALSE", "FOR", "FOREACH",
  "GOTO", "IF", "IN", "INTERFACE", "NAMESPACE", "NEW", "NULL_TYPE",
  "OBJECT", "OPERATOR", "OUT", "OVERRIDE", "PRIVATE", "PROTECTED",
  "PUBLIC", "RETURN", "SIZEOF", "STRING_TYPE", "STRUCT", "SWITCH", "THIS",
  "TRUE", "TYPEOF", "USING", "VIRTUAL", "VOID", "WHILE", "STRING_LITERAL",
  "COLCOL", "'('", "')'", "'.'", "'&'", "'!'", "'~'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "'{'",
  "'}'", "';'", "$accept", "literal", "boolean_literal", "namespace_name",
  "type_name", "type", "non_array_type", "simple_type", "primitive_type",
  "numeric_type", "integral_type", "class_type", "array_type",
  "rank_specifier", "rank_specifiers_opt", "variable_reference",
  "argument_list", "argument", "primary_expression",
  "primary_expression_no_parenthesis", "parenthesized_expression",
  "member_access", "invocation_expression", "argument_list_opt",
  "element_access", "expression_list", "this_access", "base_access",
  "new_expression", "object_creation_expression",
  "array_creation_expression", "array_initializer_opt",
  "typeof_expression", "addressof_expression", "postfix_expression",
  "unary_expression_not_plusminus", "pre_increment_expression",
  "pre_decrement_expression", "unary_expression", "cast_expression",
  "type_quals_opt", "type_quals", "type_qual", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "conditional_and_expression",
  "conditional_or_expression", "conditional_expression", "assignment",
  "assignment_operator", "expression", "constant_expression",
  "boolean_expression", "statement", "embedded_statement", "block",
  "statement_list_opt", "statement_list", "empty_statement",
  "declaration_statement", "local_variable_declaration",
  "variable_declarators", "variable_declarator", "variable_initializer",
  "expression_statement", "statement_expression", "selection_statement",
  "if_statement", "switch_statement", "switch_block",
  "switch_sections_opt", "switch_sections", "switch_section",
  "switch_labels", "switch_label", "iteration_statement",
  "while_statement", "do_statement", "for_statement",
  "for_initializer_opt", "for_condition_opt", "for_iterator_opt",
  "for_initializer", "for_condition", "for_iterator",
  "statement_expression_list", "foreach_statement", "jump_statement",
  "break_statement", "continue_statement", "goto_statement",
  "return_statement", "expression_opt", "compilation_unit",
  "using_directives_opt", "namespace_member_declarations_opt",
  "namespace_declaration", "comma_opt", "qualified_identifier",
  "qualifier", "namespace_body", "using_directives", "using_directive",
  "using_alias_directive", "using_namespace_directive",
  "namespace_member_declarations", "namespace_member_declaration",
  "type_declaration", "modifiers_opt", "modifiers", "modifier",
  "class_declaration", "class_base_opt", "class_base",
  "interface_type_list", "class_body", "class_member_declarations_opt",
  "class_member_declarations", "class_member_declaration",
  "field_declaration", "method_declaration", "method_header",
  "formal_parameter_list_opt", "method_body", "formal_parameter_list",
  "formal_parameter", "fixed_parameter", "parameter_modifier_opt",
  "operator_declaration", "operator_declarator",
  "overloadable_operator_declarator", "overloadable_operator",
  "constructor_declaration", "constructor_declarator",
  "constructor_initializer_opt", "constructor_initializer",
  "destructor_declaration", "operator_body", "constructor_body",
  "struct_declaration", "struct_interfaces_opt", "struct_interfaces",
  "struct_body", "struct_member_declarations_opt",
  "struct_member_declarations", "struct_member_declaration",
  "array_initializer", "variable_initializer_list_opt",
  "variable_initializer_list", "interface_declaration",
  "interface_base_opt", "interface_base", "interface_body",
  "interface_member_declarations_opt", "interface_member_declarations",
  "interface_member_declaration", "interface_method_declaration",
  "new_opt", "interface_empty_body", "begin_scope", "eps", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   374,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   372,   373,    40,    41,    46,    38,    33,
     126,    43,    45,    42,    47,    37,    60,    62,    94,   124,
      63,    58,    61,   123,   125,    59
};
# endif

#define YYPACT_NINF -360

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-360)))

#define YYTABLE_NINF -348

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -31,    48,    51,   133,   -31,  -360,  -360,  -360,  -360,    58,
     -12,  -360,    81,  -360,  -360,   127,  -360,  -360,  -360,  -360,
    -360,   161,  -360,  -360,   167,   149,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,   127,  -360,    97,   100,    95,  -360,   164,
     173,   195,  -360,   134,  -360,   -31,   158,   176,   197,   200,
    -360,   295,  -360,  -360,  -360,   119,   165,  -360,  -360,   127,
     208,  -360,  -360,   127,   215,  -360,  -360,   178,   255,   236,
    -360,  -360,  -360,   318,  -360,   326,   149,   158,   326,   289,
     158,   326,   149,   158,  -360,   127,   127,  -360,   352,   250,
     181,  -360,  -360,  -360,   111,  -360,  -360,  -360,   251,  -360,
    -360,   258,    -5,  -360,  -360,   304,   269,  -360,  -360,   381,
    -360,  -360,  -360,  -360,   286,   268,  -360,   292,  -360,   326,
    -360,   210,  -360,  -360,  -360,   127,   348,  -360,     1,  -360,
     379,  -360,  -360,  -360,  -360,   379,   379,   229,  -360,   245,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,   359,
     361,  -360,  -360,   336,   319,   320,    59,  1202,    21,  -360,
     321,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   844,  -360,   322,   323,  -360,   317,   395,  -360,  -360,
     115,   325,   336,   334,   647,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,   342,   390,  -360,
     336,  -360,  -360,  1088,  1088,   338,    40,   339,   844,  -360,
     346,   347,   407,   371,   115,  -360,  1088,   373,  -360,  -360,
     374,   376,  -360,   917,  1088,  1088,  1088,  1088,  1088,  1088,
    -360,  -360,  -360,   390,   380,   382,    49,   386,  -360,  -360,
      12,  -360,  -360,  -360,  -360,    14,  -360,  -360,  -360,  -360,
    -360,    30,    34,   284,  -360,  -360,  -360,  -360,  -360,   344,
     844,  -360,  -360,   368,  -360,   369,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,   136,
    -360,   336,   336,   375,   336,   432,   389,   377,   647,   380,
     382,  -360,  -360,  -360,  -360,   284,   151,    50,   120,    68,
     131,   393,   384,   387,   448,    23,  -360,  -360,  -360,  -360,
       7,  -360,   115,   388,  -360,   402,  -360,  -360,  -360,  1088,
     449,  -360,   409,  1088,   115,   392,  1088,   408,   476,    37,
    -360,   394,  -360,  1088,   423,  1088,    19,     3,    22,   179,
     412,    66,  -360,  -360,  -360,  -360,  -360,  -360,   479,   455,
     460,  1088,   461,   974,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  1088,  -360,  -360,  -360,  -360,
    1088,   974,   416,   417,    -7,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,   401,   491,  -360,  1088,  1088,  1088,
    1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,  1088,
    1088,  1088,  1088,  1088,  1088,  1088,   469,  -360,   363,  -360,
    -360,   426,  -360,  -360,   410,  -360,   497,  -360,   473,  -360,
    -360,   428,   974,  1088,  -360,  -360,   430,   431,   434,   438,
    -360,  -360,   439,    19,  -360,  -360,   440,   441,  1031,  1142,
      19,  -360,  -360,   364,  -360,  1088,   503,  -360,   442,  -360,
    -360,  -360,   367,   444,   264,   264,   447,   452,  -360,   647,
    -360,  -360,  -360,  -360,   151,   151,    50,    50,   120,   120,
     120,   120,    68,    68,   131,   393,   384,   387,   448,   433,
      63,  1088,  -360,  1088,  1088,  1088,   480,   844,   454,   372,
     443,  -360,  -360,   844,  1088,  -360,  1088,  1088,  1088,  -360,
     456,  -360,  -360,  -360,   974,  -360,  -360,  -360,   445,  -360,
    -360,  -360,   974,   974,  -360,  1088,   115,  -360,  -360,   457,
    -360,   450,  -360,  -360,  -360,  1088,   495,  -360,   379,    38,
    -360,  -360,  -360,  -360,  -360,  -360,  1088,  -360,  -360,   466,
     467,  -360,   514,   451,  1088,   471,   844,  -360,   458,  -360,
    1088,   463,   472,    38,  -360,   762,  -360,  -360,  -360,  -360,
    -360,   485,  -360,   487,  -360,   497,  -360,   844,  -360,  -360,
    -360,  -360,  -360,   464,  -360,  -360,  -360,   844,  -360,  -360,
     844,  -360,  -360,  -360
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     358,     0,     0,   358,   219,   230,   232,   233,   218,   225,
       0,     9,     0,     1,   247,     0,   248,   249,   250,   251,
     238,   358,   236,   239,     0,   244,   245,   240,   241,   242,
     243,   231,   227,     0,   235,   226,   225,     0,   237,     0,
       0,     0,   246,     0,   228,   358,   358,   358,   358,   358,
     234,   358,   224,   222,   223,     0,     0,   254,   253,     0,
       0,   343,   342,     0,     0,   324,   323,     0,   358,   243,
      22,    23,   258,   255,    10,   256,   358,   358,   344,   358,
     358,   325,   358,   358,   229,     0,     0,   270,     0,     0,
     358,   263,   265,   266,     0,   267,   268,   269,   243,   252,
     354,     0,   358,   348,   350,     0,   353,   341,   335,     0,
     331,   332,   333,   334,     0,   358,   329,   243,   322,   257,
     259,   225,    20,    18,    21,     0,     0,    14,     0,    11,
      13,    15,    17,    19,    16,    12,    10,     0,   286,     0,
     260,   264,   358,   278,   277,   272,   345,   349,   353,     0,
       0,   326,   330,   358,     0,     0,   161,     0,     0,   159,
       0,    27,    25,    24,    26,   319,   318,   285,   321,   320,
     311,   358,   357,     0,     0,   284,     0,   276,   279,   281,
       0,   283,   358,     0,     0,   303,   304,   305,   306,   310,
     309,   293,   294,   296,   295,   300,   291,   292,   289,   290,
     297,   298,   299,   308,   307,   302,   301,     0,     0,   271,
     358,     3,     4,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     0,     0,     0,     6,   358,     0,    58,     7,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
     156,    37,     2,     0,    15,    16,    70,    36,    35,    39,
      40,    41,    42,    43,    44,    61,    38,    45,    84,    72,
      78,    82,    83,     0,    75,   168,   154,   144,   145,     0,
     153,   146,   143,     0,   147,     0,   148,   171,   172,   149,
     186,   187,   188,   189,   150,   206,   207,   208,   209,    71,
     152,   358,   358,   358,   358,     0,     0,     0,   358,     0,
       0,    40,    61,    82,    83,    97,   101,   104,   107,   112,
     115,   117,   119,   121,   123,   125,   139,   140,   163,   162,
      71,   164,     0,   161,   160,     0,    76,    77,   210,     0,
       0,   211,     0,   358,     0,     0,     0,     0,    11,    12,
     215,     0,   214,     0,     0,     0,   358,   358,   358,   101,
       0,    71,    69,    73,    74,    79,    80,    81,   158,     0,
       0,     0,     0,   358,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   128,     0,   151,   155,   157,   165,
       0,   358,     0,     0,     0,   312,   314,   313,   280,   283,
     282,   274,   317,   339,     0,   338,   337,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   273,     0,    56,
      59,     0,   199,   203,     0,   194,   200,   193,     0,   212,
     142,     0,   358,     0,    64,   213,     0,     0,     0,     0,
      96,    95,     0,    92,    93,    91,     0,     0,     0,    46,
     358,    48,    49,     0,    47,     0,    53,    31,     0,    33,
      52,   127,     0,     0,     0,     0,     0,     0,   336,     0,
      98,    99,   100,    97,   102,   103,   105,   106,   110,   111,
     108,   109,   113,   114,   116,   118,   120,   122,   124,     0,
       0,     0,    60,     0,   358,     0,     0,     0,     0,     0,
       0,    68,    67,     0,     0,    94,     0,     0,     0,    85,
       0,    54,    34,    30,     0,    50,    55,    51,     0,   355,
     352,   351,   358,   358,   340,     0,     0,   287,    57,     0,
     201,     0,   196,   195,   204,     0,   173,    62,   358,   358,
     175,   190,    90,    88,    89,    86,     0,    32,   356,     0,
       0,   126,     0,     0,   358,     0,     0,    29,   358,    28,
       0,     0,     0,   178,   179,     0,   182,   177,    87,   315,
     316,     0,   191,     0,   198,   202,   197,     0,   174,    63,
      66,    65,   141,     0,   185,   176,   180,   181,   183,   288,
       0,   205,   184,   192
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -360,  -360,  -360,  -360,   193,   -84,   324,  -360,   -68,  -360,
    -360,   -52,   341,  -102,  -360,  -360,  -360,    54,  -360,  -360,
    -360,  -360,  -147,  -359,  -360,  -319,  -360,  -360,  -360,   -56,
    -360,  -360,  -360,  -360,  -360,   121,   -28,    55,   190,  -360,
    -332,  -360,   128,  -225,  -156,  -208,   -91,   163,   166,   162,
     168,   170,  -360,  -360,    72,  -360,   327,  -360,  -335,  -268,
    -217,   -87,  -360,    13,  -360,  -360,   246,   337,   397,  -289,
    -360,  -327,  -360,  -360,  -360,  -360,  -360,  -360,    20,  -360,
      17,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,    31,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
     561,  -360,  -360,   191,    -1,  -360,  -360,  -360,   603,  -360,
    -360,   557,     2,   140,   169,  -360,   585,  -360,  -360,  -360,
     198,  -360,  -360,  -360,   522,   -39,   -38,  -360,  -170,  -360,
    -360,   328,  -360,  -360,   -34,  -360,  -360,  -360,   -22,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   498,  -334,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   512,  -360,  -360,   150,  -360,    18
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   241,   242,    10,   127,   243,   129,   130,   299,   132,
     133,   300,   135,   441,   558,   512,   456,   457,   246,   247,
     248,   249,   301,   458,   251,   418,   252,   253,   254,   302,
     256,   579,   257,   258,   259,   260,   303,   304,   305,   264,
     442,   443,   444,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   375,   459,   583,   431,   266,
     267,   268,   269,   270,   271,   272,   273,   158,   159,   319,
     274,   275,   276,   277,   278,   540,   562,   563,   564,   565,
     566,   279,   280,   281,   282,   424,   531,   573,   425,   532,
     574,   426,   283,   284,   285,   286,   287,   288,   341,     2,
       3,    67,    20,    53,   320,    12,    46,     4,     5,     6,
       7,    21,    22,    23,    24,    25,    26,    27,    56,    57,
      75,    77,    89,    90,    91,    92,    93,    94,   176,   145,
     177,   178,   179,   180,    95,   137,   138,   207,    96,   139,
     385,   386,    97,   167,   170,    28,    64,    65,    83,   114,
     115,   116,   321,   394,   395,    29,    60,    61,    80,   101,
     102,   103,   104,   105,   520,   171,    30
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,   332,   377,    73,   128,   434,   423,   144,   349,   393,
     439,   161,   296,   380,    37,   446,   447,  -166,     8,  -167,
     131,   150,   463,    38,   250,   128,   208,   161,   162,   466,
     161,   156,    43,   163,   164,  -169,   134,   131,     1,  -170,
     325,   131,   453,   110,   111,   161,   329,   100,   112,   414,
     166,    13,   169,   134,    74,   361,   157,   134,    74,   467,
     113,   462,    74,     8,    54,    58,    62,    66,   526,    69,
      38,   250,   380,   498,   161,   560,   110,   111,     9,   561,
     359,   112,   381,    34,    74,    74,   440,   136,  -166,  -347,
    -167,   404,   405,   113,    98,    54,   295,   106,    54,   360,
     117,    54,   440,   244,   136,   440,  -169,  -166,   136,  -167,
    -170,    35,   131,   415,   499,   255,   209,   330,   510,   245,
     148,   382,   383,   250,   154,  -169,   362,   160,   134,  -170,
     298,   400,   401,  -216,  -225,    32,    32,   402,   403,   527,
     337,   381,   380,   261,   161,    36,   122,   123,   124,    36,
      33,   184,   408,   409,   406,   407,   131,    36,   529,   530,
     172,  -217,   255,   549,   550,   347,   -10,    14,   534,    70,
     289,   181,   134,    70,    44,   474,   475,    32,    71,   136,
     524,   348,    71,    14,    15,    16,   250,   164,    45,   290,
     261,    17,    18,    19,    47,    14,   478,   479,   480,   481,
     181,    16,   244,    48,   142,    39,   143,    17,    18,    19,
     392,   381,    15,    16,   255,    14,    87,    40,   245,    17,
      18,    19,   108,   136,   580,    49,   262,   423,   181,    50,
      87,    41,   351,    16,   397,   398,   399,   163,   416,    17,
      18,    19,   261,   265,   342,    88,   476,   477,    72,   450,
     428,   109,    72,    52,   131,   108,    72,    78,    76,    88,
     438,    81,   448,   398,   399,   244,   131,    55,    99,   289,
     134,   107,    84,   262,   118,  -262,   131,   255,    72,   120,
     536,   245,   134,   119,   109,   153,   541,    32,    59,    14,
     265,    63,   134,   364,   365,   366,   367,   368,   369,   370,
     371,    79,    14,   372,   373,   261,    15,    16,    82,   181,
     181,   387,   389,    17,    18,    19,   396,   482,   483,   377,
      16,   136,   142,    85,   165,   262,    17,    18,    19,    14,
    -220,    86,   289,   136,    36,   122,   123,   124,   142,   578,
     168,   100,   265,   136,   140,  -261,    15,    16,   250,  -221,
     250,   427,   146,    17,    18,    19,   250,   518,    70,   519,
     591,   263,  -328,  -346,   445,   445,   445,    71,   491,   491,
     492,   511,   491,   593,   516,   149,   374,   491,   155,   538,
     151,   460,   121,   122,   123,   124,  -327,   161,   262,   173,
      39,   174,   175,   293,   182,   183,   210,   291,   292,   460,
     294,  -275,    40,   326,   327,   265,    70,   250,   263,   250,
     297,   121,   122,   123,   124,    71,    41,   322,   250,    39,
     323,   333,   334,   125,   352,   353,   354,   355,   356,   357,
     250,    40,   126,   328,   331,    70,   557,   335,   376,   255,
     250,   255,   552,   250,    71,    41,   336,   255,   343,   344,
     460,   345,   125,    36,   122,   123,   124,   359,   131,   360,
     263,   363,   390,   378,   379,   391,   384,   261,   445,   261,
     142,   410,   411,   413,   134,   261,   412,    70,   417,   420,
     184,   421,   433,   432,   208,   451,    71,   429,   449,   435,
     452,   454,   464,   465,   437,   468,   469,   244,   255,   490,
     255,   493,   495,   496,   497,   494,   500,   501,   514,   255,
     502,   318,   533,   245,   503,   504,   506,   507,   515,   244,
     517,   255,   522,   263,   525,   136,   261,   523,   261,   535,
     537,   255,   546,   553,   255,   245,   539,   261,   556,   548,
     460,   460,   569,   570,   571,   554,   572,   577,   338,   261,
     262,   298,   262,   340,   584,   592,   559,   567,   262,   261,
     350,   589,   261,   590,   289,   339,   585,   265,   547,   265,
     509,   505,   576,   484,   486,   265,   581,   485,   587,   422,
     358,   487,   588,   586,   488,   575,   289,   470,   471,   472,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   324,    51,    31,    68,   262,
      42,   262,   141,   152,   147,   521,     0,     0,     0,     0,
     262,     0,   388,     0,     0,   318,   265,     0,   265,     0,
       0,     0,   262,     0,     0,     0,     0,   265,   470,     0,
       0,     0,   262,     0,     0,   262,     0,     0,     0,   265,
     211,   212,     0,     0,     0,     0,   419,     0,     0,   265,
       0,     0,   265,   430,     0,     0,     0,     0,     0,     0,
     436,     0,   430,     0,   213,   214,     0,    36,   122,   123,
     124,     0,     0,   216,     0,   263,     0,   263,   419,     0,
       0,   219,     0,   263,   542,     0,   543,   544,   545,   224,
     225,    70,   461,     0,     0,     0,     0,   419,     0,     0,
      71,     0,     0,   228,   229,   230,     0,     0,     0,     0,
     232,     0,   233,     0,     0,   234,   235,   236,   237,   238,
     239,     0,     0,     0,     0,     0,   568,     0,     0,     0,
     298,     0,   489,     0,   263,     0,   263,     0,     0,     0,
       0,     0,     0,     0,     0,   263,     0,     0,     0,     0,
     419,     0,     0,     0,     0,   211,   212,   263,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   263,     0,     0,
     263,     0,   513,     0,     0,     0,     0,     0,     0,   213,
     214,     0,    36,   122,   123,   124,   318,   215,   216,   560,
       0,     0,   217,   561,   218,     0,   219,   220,   221,   222,
     223,     0,     0,     0,   224,   225,    70,     0,   528,     0,
     430,   430,     0,   226,     0,    71,     0,   227,   228,   229,
     230,     0,     0,     0,   231,   232,     0,   233,     0,     0,
     234,   235,   236,   237,   238,   239,     0,   211,   212,     0,
       0,     0,   551,     0,     0,   142,     0,   240,     0,     0,
       0,     0,   555,     0,     0,     0,     0,     0,     0,     0,
       0,   213,   214,     0,    36,   122,   123,   124,     0,   215,
     216,     0,     0,     0,   217,     0,   218,   582,   219,   220,
     221,   222,   223,     0,     0,     0,   224,   225,    70,     0,
       0,     0,     0,     0,     0,   226,     0,    71,     0,   227,
     228,   229,   230,     0,     0,     0,   231,   232,     0,   233,
     211,   212,   234,   235,   236,   237,   238,   239,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   142,     0,   240,
       0,     0,     0,     0,   213,   214,     0,    36,   122,   123,
     124,     0,     0,   216,     0,     0,     0,     0,     0,     0,
       0,   219,     0,     0,     0,     0,     0,     0,     0,   224,
     225,    70,     0,     0,     0,     0,     0,   211,   212,     0,
      71,     0,     0,   228,   229,   230,     0,     0,   346,     0,
     232,     0,   233,     0,     0,   234,   235,   236,   237,   238,
     239,   213,   214,     0,    36,   122,   123,   124,     0,     0,
     216,     0,     0,     0,     0,     0,     0,     0,   219,     0,
       0,     0,     0,     0,     0,     0,   224,   225,    70,     0,
     455,     0,     0,     0,   211,   212,     0,    71,     0,     0,
     228,   229,   230,     0,     0,     0,     0,   232,     0,   233,
       0,     0,   234,   235,   236,   237,   238,   239,   213,   214,
       0,    36,   122,   123,   124,     0,     0,   216,     0,     0,
       0,     0,     0,     0,     0,   219,     0,     0,     0,     0,
       0,     0,     0,   224,   225,    70,     0,     0,     0,     0,
       0,   211,   212,     0,    71,     0,     0,   228,   229,   230,
       0,     0,     0,     0,   232,     0,   233,   508,     0,   234,
     235,   236,   237,   238,   239,   213,   214,     0,    36,   122,
     123,   124,     0,     0,   216,     0,     0,     0,     0,     0,
       0,     0,   219,     0,     0,     0,     0,     0,     0,     0,
     224,   225,    70,     0,     0,   211,   212,     0,     0,     0,
       0,    71,     0,     0,   228,   229,   230,     0,     0,     0,
       0,   232,     0,   233,     0,     0,   234,   235,   236,   237,
     238,   239,    36,   122,   123,   124,     0,     0,   216,     0,
       0,     0,     0,     0,     0,     0,   219,     0,     0,     0,
       0,     0,     0,     0,   224,   225,    70,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,   228,   229,
     230,     0,     0,     0,     0,   232,     0,   233,     0,   185,
     186,   235,   236,   187,   188,   189,   190,     0,     0,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   193,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206
};

static const yytype_int16 yycheck[] =
{
       1,   218,   270,    55,    88,   339,   333,    94,   233,   298,
     345,     8,   182,     6,    15,   347,   348,     5,     0,     5,
      88,   105,   381,    21,   171,   109,     5,     8,   130,    36,
       8,    30,    33,   135,   136,     5,    88,   105,    69,     5,
     210,   109,   361,    82,    82,     8,     6,    52,    82,    26,
     137,     0,   139,   105,    55,     6,    55,   109,    59,    66,
      82,   380,    63,    45,    46,    47,    48,    49,     5,    51,
      68,   218,     6,   432,     8,    37,   115,   115,    30,    41,
      77,   115,    75,    95,    85,    86,    83,    88,    76,    94,
      76,    23,    24,   115,    76,    77,   180,    79,    80,    77,
      82,    83,    83,   171,   105,    83,    76,    95,   109,    95,
      76,    30,   180,    90,   433,   171,    95,    77,   450,   171,
     102,   291,   292,   270,   125,    95,    77,   128,   180,    95,
      93,    81,    82,     0,    75,    77,    77,    17,    18,    76,
     224,    75,     6,   171,     8,    30,    31,    32,    33,    30,
      92,    92,    21,    22,    86,    87,   224,    30,   493,   494,
     142,     0,   218,   522,   523,   233,    30,    34,   495,    54,
     171,   153,   224,    54,    77,   400,   401,    77,    63,   180,
     469,   233,    63,    34,    51,    52,   333,   289,    93,   171,
     218,    58,    59,    60,    30,    34,   404,   405,   406,   407,
     182,    52,   270,    30,    93,    38,    95,    58,    59,    60,
     297,    75,    51,    52,   270,    34,    76,    50,   270,    58,
      59,    60,    82,   224,   558,    30,   171,   554,   210,    95,
      90,    64,   233,    52,    83,    84,    85,   339,   322,    58,
      59,    60,   270,   171,   226,    76,   402,   403,    55,   351,
     334,    82,    59,    95,   322,   115,    63,    59,    93,    90,
     344,    63,    83,    84,    85,   333,   334,    91,    77,   270,
     322,    80,    94,   218,    83,    94,   344,   333,    85,    86,
     497,   333,   334,    85,   115,    75,   503,    77,    91,    34,
     218,    91,   344,     9,    10,    11,    12,    13,    14,    15,
      16,    93,    34,    19,    20,   333,    51,    52,    93,   291,
     292,   293,   294,    58,    59,    60,   298,   408,   409,   587,
      52,   322,    93,     5,    95,   270,    58,    59,    60,    34,
      94,     5,   333,   334,    30,    31,    32,    33,    93,   556,
      95,    52,   270,   344,    94,    94,    51,    52,   495,    94,
     497,   333,    94,    58,    59,    60,   503,    93,    54,    95,
     577,   171,    94,    94,   346,   347,   348,    63,     5,     5,
       7,     7,     5,   590,     7,    71,    92,     5,    30,     7,
      94,   363,    30,    31,    32,    33,    94,     8,   333,    30,
      38,    30,    56,    76,    75,    75,    75,    75,    75,   381,
       5,    76,    50,   213,   214,   333,    54,   554,   218,   556,
      76,    30,    31,    32,    33,    63,    64,    75,   565,    38,
      30,    75,    75,    71,   234,   235,   236,   237,   238,   239,
     577,    50,    80,    95,    95,    54,   538,    30,    94,   495,
     587,   497,   526,   590,    63,    64,    75,   503,    75,    75,
     432,    75,    71,    30,    31,    32,    33,    77,   526,    77,
     270,    75,    30,    95,    95,    76,    91,   495,   450,   497,
      93,    78,    88,    25,   526,   503,    89,    54,    76,    30,
      92,    72,     6,    75,     5,    30,    63,    95,    76,    95,
      30,    30,    76,    76,    71,    94,     5,   565,   554,    30,
     556,    75,     5,    30,    76,    95,    76,    76,     5,   565,
      76,   184,   494,   565,    76,    76,    76,    76,    76,   587,
      76,   577,    75,   333,    91,   526,   554,    75,   556,    49,
      76,   587,    76,    76,   590,   587,    93,   565,    43,    94,
     522,   523,    76,    76,    30,    95,    95,    76,   224,   577,
     495,    93,   497,   226,    91,    91,   538,   539,   503,   587,
     233,    76,   590,    76,   565,   224,    94,   495,   514,   497,
     449,   443,   554,   410,   412,   503,   558,   411,   565,   333,
     243,   413,   565,   563,   414,   554,   587,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   208,    45,     4,    51,   554,
      25,   556,    90,   115,   102,   465,    -1,    -1,    -1,    -1,
     565,    -1,   294,    -1,    -1,   298,   554,    -1,   556,    -1,
      -1,    -1,   577,    -1,    -1,    -1,    -1,   565,   448,    -1,
      -1,    -1,   587,    -1,    -1,   590,    -1,    -1,    -1,   577,
       3,     4,    -1,    -1,    -1,    -1,   329,    -1,    -1,   587,
      -1,    -1,   590,   336,    -1,    -1,    -1,    -1,    -1,    -1,
     343,    -1,   345,    -1,    27,    28,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    -1,   495,    -1,   497,   361,    -1,
      -1,    44,    -1,   503,   504,    -1,   506,   507,   508,    52,
      53,    54,   375,    -1,    -1,    -1,    -1,   380,    -1,    -1,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,
      73,    -1,    75,    -1,    -1,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,   546,    -1,    -1,    -1,
      93,    -1,   415,    -1,   554,    -1,   556,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   565,    -1,    -1,    -1,    -1,
     433,    -1,    -1,    -1,    -1,     3,     4,   577,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   587,    -1,    -1,
     590,    -1,   455,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    -1,    30,    31,    32,    33,   469,    35,    36,    37,
      -1,    -1,    40,    41,    42,    -1,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    53,    54,    -1,   491,    -1,
     493,   494,    -1,    61,    -1,    63,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    73,    -1,    75,    -1,    -1,
      78,    79,    80,    81,    82,    83,    -1,     3,     4,    -1,
      -1,    -1,   525,    -1,    -1,    93,    -1,    95,    -1,    -1,
      -1,    -1,   535,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    -1,    30,    31,    32,    33,    -1,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,   560,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    63,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    72,    73,    -1,    75,
       3,     4,    78,    79,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    95,
      -1,    -1,    -1,    -1,    27,    28,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    -1,
      73,    -1,    75,    -1,    -1,    78,    79,    80,    81,    82,
      83,    27,    28,    -1,    30,    31,    32,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,     3,     4,    -1,    63,    -1,    -1,
      66,    67,    68,    -1,    -1,    -1,    -1,    73,    -1,    75,
      -1,    -1,    78,    79,    80,    81,    82,    83,    27,    28,
      -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    -1,    -1,    73,    -1,    75,    76,    -1,    78,
      79,    80,    81,    82,    83,    27,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,     3,     4,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,
      -1,    73,    -1,    75,    -1,    -1,    78,    79,    80,    81,
      82,    83,    30,    31,    32,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,
      68,    -1,    -1,    -1,    -1,    73,    -1,    75,    -1,    17,
      18,    79,    80,    21,    22,    23,    24,    -1,    -1,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    69,   195,   196,   203,   204,   205,   206,   262,    30,
      99,   200,   201,     0,    34,    51,    52,    58,    59,    60,
     198,   207,   208,   209,   210,   211,   212,   213,   241,   251,
     262,   204,    77,    92,    95,    30,    30,   200,   208,    38,
      50,    64,   212,   200,    77,    93,   202,    30,    30,    30,
      95,   196,    95,   199,   262,    91,   214,   215,   262,    91,
     252,   253,   262,    91,   242,   243,   262,   197,   207,   262,
      54,    63,   100,   107,   200,   216,    93,   217,   216,    93,
     254,   216,    93,   244,    94,     5,     5,   209,   210,   218,
     219,   220,   221,   222,   223,   230,   234,   238,   262,   199,
      52,   255,   256,   257,   258,   259,   262,   199,   209,   210,
     221,   222,   230,   234,   245,   246,   247,   262,   199,   216,
     100,    30,    31,    32,    33,    71,    80,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   200,   231,   232,   235,
      94,   220,    93,    95,   157,   225,    94,   257,   262,    71,
     101,    94,   247,    75,   200,    30,    30,    55,   163,   164,
     200,     8,   109,   109,   109,    95,   157,   239,    95,   157,
     240,   261,   262,    30,    30,    56,   224,   226,   227,   228,
     229,   262,    75,    75,    92,    17,    18,    21,    22,    23,
      24,    27,    28,    44,    67,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   233,     5,    95,
      75,     3,     4,    27,    28,    35,    36,    40,    42,    44,
      45,    46,    47,    48,    52,    53,    61,    65,    66,    67,
      68,    72,    73,    75,    78,    79,    80,    81,    82,    83,
      95,    97,    98,   101,   104,   107,   114,   115,   116,   117,
     118,   120,   122,   123,   124,   125,   126,   128,   129,   130,
     131,   132,   133,   134,   135,   150,   155,   156,   157,   158,
     159,   160,   161,   162,   166,   167,   168,   169,   170,   177,
     178,   179,   180,   188,   189,   190,   191,   192,   193,   200,
     262,    75,    75,    76,     5,   101,   224,    76,    93,   104,
     107,   118,   125,   132,   133,   134,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   152,   165,
     200,   248,    75,    30,   164,   224,   134,   134,    95,     6,
      77,    95,   156,    75,    75,    30,    75,   101,   102,   108,
     152,   194,   262,    75,    75,    75,    71,   104,   107,   139,
     152,   200,   134,   134,   134,   134,   134,   134,   163,    77,
      77,     6,    77,    75,     9,    10,    11,    12,    13,    14,
      15,    16,    19,    20,    92,   151,    94,   155,    95,    95,
       6,    75,   224,   224,    91,   236,   237,   262,   227,   262,
      30,    76,   157,   165,   249,   250,   262,    83,    84,    85,
      81,    82,    17,    18,    23,    24,    86,    87,    21,    22,
      78,    88,    89,    25,    26,    90,   101,    76,   121,   152,
      30,    72,   162,   167,   181,   184,   187,   262,   101,    95,
     152,   154,    75,     6,   248,    95,   152,    71,   101,   154,
      83,   109,   136,   137,   138,   262,   136,   136,    83,    76,
     109,    30,    30,   121,    30,    56,   112,   113,   119,   152,
     262,   152,   121,   119,    76,    76,    36,    66,    94,     5,
     134,   134,   134,   134,   139,   139,   140,   140,   141,   141,
     141,   141,   142,   142,   143,   144,   145,   146,   147,   152,
      30,     5,     7,    75,    95,     5,    30,    76,   119,   121,
      76,    76,    76,    76,    76,   138,    76,    76,    76,   131,
     136,     7,   111,   152,     5,    76,     7,    76,    93,    95,
     260,   260,    75,    75,   165,    91,     5,    76,   152,   154,
     154,   182,   185,   262,   167,    49,   156,    76,     7,    93,
     171,   156,   134,   134,   134,   134,    76,   113,    94,   119,
     119,   152,   101,    76,    95,   152,    43,   109,   110,   262,
      37,    41,   172,   173,   174,   175,   176,   262,   134,    76,
      76,    30,    95,   183,   186,   187,   262,    76,   156,   127,
     248,   262,   152,   153,    91,    94,   174,   159,   176,    76,
      76,   156,    91,   156
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    96,    97,    97,    97,    97,    97,    98,    98,    99,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     106,   106,   107,   107,   108,   108,   108,   109,   110,   110,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   117,   117,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   123,
     123,   124,   125,   126,   126,   127,   127,   128,   128,   129,
     130,   130,   131,   131,   131,   131,   132,   133,   134,   134,
     134,   134,   134,   134,   134,   135,   135,   135,   135,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   139,   139,
     139,   140,   140,   140,   141,   141,   141,   142,   142,   142,
     142,   142,   143,   143,   143,   144,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   152,
     152,   153,   154,   155,   155,   156,   156,   156,   156,   156,
     156,   157,   158,   158,   159,   159,   160,   161,   162,   163,
     163,   164,   164,   165,   165,   166,   167,   167,   167,   167,
     167,   168,   168,   169,   169,   170,   171,   172,   172,   173,
     173,   174,   175,   175,   176,   176,   177,   177,   177,   177,
     178,   179,   180,   181,   181,   182,   182,   183,   183,   184,
     184,   185,   186,   187,   187,   188,   189,   189,   189,   189,
     190,   191,   192,   193,   194,   194,   195,   195,   196,   196,
     197,   197,   198,   199,   199,   200,   200,   201,   201,   202,
     203,   203,   204,   204,   205,   206,   207,   207,   208,   208,
     209,   209,   209,   210,   210,   211,   211,   212,   212,   212,
     212,   212,   213,   214,   214,   215,   215,   215,   216,   216,
     217,   218,   218,   219,   219,   220,   220,   220,   220,   220,
     220,   221,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   228,   229,   229,   230,   231,   232,   232,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   234,   235,   236,   236,   237,   237,   238,   239,   239,
     240,   240,   241,   242,   242,   243,   244,   245,   245,   246,
     246,   247,   247,   247,   247,   247,   248,   249,   249,   250,
     250,   251,   252,   252,   253,   254,   255,   255,   256,   256,
     257,   258,   258,   259,   259,   260,   260,   261,   262
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       4,     4,     1,     1,     4,     4,     1,     3,     1,     3,
       4,     1,     5,     7,     3,     1,     1,     4,     4,     2,
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     1,     1,     1,     4,     5,     6,     5,     5,
       5,     1,     1,     1,     2,     1,     1,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     1,     1,     2,     1,     2,     2,     1,
       3,     1,     3,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     5,     7,     5,     3,     1,     1,     1,
       2,     2,     1,     2,     3,     2,     1,     1,     1,     1,
       5,     7,     9,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     8,     1,     1,     1,     1,
       2,     2,     3,     3,     1,     1,     1,     2,     1,     1,
       1,     1,     4,     1,     1,     1,     2,     2,     3,     4,
       1,     2,     1,     1,     5,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     6,     1,     1,     2,     2,     4,     1,     3,
       3,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     4,     2,     6,     6,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     1,     7,    10,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     5,     1,     1,     5,     5,     6,     1,     1,
       1,     1,     6,     1,     1,     2,     3,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     6,     1,     1,     2,     3,     1,     1,     1,     2,
       1,     7,     7,     1,     1,     1,     2,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 179 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2008 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 182 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
  }
#line 2017 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 186 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
  }
#line 2026 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 190 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
  }
#line 2035 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 194 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
  }
#line 2044 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 204 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2052 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 209 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2060 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 214 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2068 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 217 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2076 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 222 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2084 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 225 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2092 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 230 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2100 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 236 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2108 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 239 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="bool";
    (yyval.NT)->width=1;
  }
#line 2118 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 246 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2126 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 251 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="int";
    (yyval.NT)->width=4;
  }
#line 2136 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 256 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="char";
    (yyval.NT)->width=1;
  }
#line 2146 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 268 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->isarray=true;
    (yyval.NT)->elem=(yyvsp[-1].NT);
  }
#line 2156 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 363 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2164 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 368 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2172 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 382 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2180 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 413 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2188 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 416 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"*");
  }
#line 2196 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 419 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"/");
  }
#line 2204 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 422 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"%");
  }
#line 2212 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 427 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2220 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 430 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"+");
    for(int i=0;i<(int)(((yyval.NT)->code).size());i++){
      cout<<((yyval.NT)->code)[i]<<endl;
    }
    cout<<"----"<<endl;
  }
#line 2232 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 437 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"-");
  }
#line 2240 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 442 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2248 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 445 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<<");
  }
#line 2256 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 448 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">>");
  }
#line 2264 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 453 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2272 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 456 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<");
  }
#line 2280 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 459 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">");
  }
#line 2288 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 462 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<=");
  }
#line 2296 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 465 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">=");
  }
#line 2304 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 470 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2312 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 473 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"==");
  }
#line 2320 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 476 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"!=");
  }
#line 2328 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 481 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2336 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 484 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"&");
  }
#line 2344 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 489 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2352 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 492 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"^");
  }
#line 2360 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 497 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2368 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 500 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"|");
  }
#line 2376 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 505 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2384 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 508 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"&&");
  }
#line 2392 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 513 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2400 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 516 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"||");
  }
#line 2408 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 521 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2416 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 524 "src/sharpie.y" /* yacc.c:1646  */
    {
    // TODO
  }
#line 2424 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 529 "src/sharpie.y" /* yacc.c:1646  */
    {
  // TODO: handle others later
    (yyval.NT)=new Attr();
  /*if(CurTable->lookup($1->place)){*/
    (yyval.NT)->place = (yyvsp[-2].NT)->place;
    Combine((yyval.NT)->code, (yyvsp[0].NT)->code, (yyvsp[-2].NT)->code);
    string code_= getTAC(2,"=",(yyvsp[-2].NT)->place,(yyvsp[0].NT)->place);
    cout<<code_<<endl;
  /*
   *}else{
   *  cerr<<"ERROR: Symbol "<<($1->place)<<" used without declaration."<<endl;
   *  exit(0);
   *}
   */
}
#line 2444 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 559 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2452 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 562 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2460 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 567 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT); // check if variable is altered
  }
#line 2468 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 572 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2476 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 577 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement ->declaration_statement asda"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2485 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 581 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement ->embedded_statement asda"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2494 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 587 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2502 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 590 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2510 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 593 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"embedded_statement->expression_statement"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2519 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 597 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2527 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 600 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2535 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 603 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2543 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 609 "src/sharpie.y" /* yacc.c:1646  */
    {
  /*: '{' statement_list_opt '}'{*/
    (yyval.NT) = (yyvsp[-2].NT);
    /*cout<<"dgdfgg"<<endl;*/
    EndScope();
    /*cout<<"Enddgdfgg"<<endl;*/
  }
#line 2555 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 619 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list_opt"<<endl;*/
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2564 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 626 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list to statement"<<endl;*/
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2573 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 630 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list to statement_list statement "<<endl;*/
    (yyval.NT)=(yyvsp[-1].NT);
	Combine((yyval.NT)->code, (yyvsp[-1].NT)->code, (yyvsp[0].NT)->code);
    /*cout<<"statement_list to statement 22222"<<endl;*/
  }
#line 2584 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 638 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = new Attr();
    /*cout<<"hello there"<<endl;*/
    //TODO
  }
#line 2594 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 645 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 2602 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 650 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"local_variable_declaration asdad"<<endl;*/
    (yyval.NT)=new Attr();
    if((yyvsp[-1].NT)->isarray == false){
	for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
	  Attr * CurVar = ((yyvsp[0].NT)->var_dec)[i];
	  // insert CurVar->place into table
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    Combine((yyval.NT)->code,(yyval.NT)->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ((yyval.NT)->code).pb(code_);
	  }
	}
    }else{
       for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
	  Attr * CurVar = ((yyvsp[0].NT)->var_dec)[i];
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    int ArrayLength=(CurVarInit->init_list).size();
	    string code_="array,"+((yyvsp[-1].NT)->elem)->type+","+to_string(ArrayLength)+","+CurVar->place;
	    ((yyval.NT)->code).pb(code_);
	    for(int j=0;j<(int)(CurVarInit->init_list).size();j++){
	      Attr * CurVarInitElem = (CurVarInit->init_list)[j];
	      int ElemWidth=((yyvsp[-1].NT)->elem)->width;
	      // TODO:update width for this array struct=len*Elemwidth
	      code_="update,"+(CurVarInitElem->place)+","+(CurVar->place)+","+to_string(ElemWidth*j);
	      Combine((yyval.NT)->code,(yyval.NT)->code,CurVarInitElem->code);
	      ((yyval.NT)->code).pb(code_);
	    }
	  }else{
	    // default length 100 size array
	    string code_="array,"+((yyvsp[-1].NT)->elem)->type+",100,"+CurVar->place;
	    ((yyval.NT)->code).pb(code_);
	  }
	}
     }
    for(auto it : ((yyval.NT)->code))
      cout<<it<<endl;
    cout<<"******"<<endl;
  }
#line 2648 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 693 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->var_dec).pb((yyvsp[0].NT));
  }
#line 2657 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 697 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->var_dec).pb((yyvsp[0].NT));
  }
#line 2666 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 703 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[0].sval));
    (yyval.NT)->init = NULL;
    (yyval.NT)->line=yylineno;
  }
#line 2677 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 709 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[-2].sval));
    (yyval.NT)->init = (yyvsp[0].NT);
    (yyval.NT)->line=yylineno;
  }
#line 2688 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 717 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2696 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 720 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2704 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 725 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"expression_statement -> statement_expression"<<endl;*/
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 2713 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 731 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"invocation_expression"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2722 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 735 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2730 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 738 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2738 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 741 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2746 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 744 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2754 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 749 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2762 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 752 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2770 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 757 "src/sharpie.y" /* yacc.c:1646  */
    {
    string ltrue=getLabel();
    string lfalse=getLabel();
    (yyval.NT)=new Attr();
    (yyval.NT)->code=(yyvsp[-2].NT)->code;
    string code_="ifgoto,==,1,"+((yyvsp[-2].NT)->place)+","+ltrue;
    ((yyval.NT)->code).pb(code_);
    code_="goto,"+lfalse;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+ltrue;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
    code_="label,"+lfalse;
    ((yyval.NT)->code).pb(code_);
  }
#line 2790 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 772 "src/sharpie.y" /* yacc.c:1646  */
    {
    string ltrue=getLabel();
    string lnext=getLabel();
    (yyval.NT)=new Attr();
    (yyval.NT)->code=(yyvsp[-4].NT)->code;
    string code_="ifgoto,==,1,"+((yyvsp[-4].NT)->place)+","+ltrue;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
    code_="goto,"+lnext;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+ltrue;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    code_="label,"+lnext;
    ((yyval.NT)->code).pb(code_);
    cout<<"%%%%%%%%%%%"<<endl;
    for(int i=0;i<((yyval.NT)->code).size();i++){
      cout<<((yyval.NT)->code)[i]<<endl;
    }
    cout<<"%%%%%%%%%%%"<<endl;
  }
#line 2816 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 802 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2824 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 807 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2832 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 824 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2840 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 827 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2848 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 830 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2856 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 833 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2864 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 918 "src/sharpie.y" /* yacc.c:1646  */
    {
	(yyval.NT) = new Attr();
	(yyval.NT)->place = string((yyvsp[0].sval));
  }
#line 2873 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 922 "src/sharpie.y" /* yacc.c:1646  */
    {
    
  }
#line 2881 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 927 "src/sharpie.y" /* yacc.c:1646  */
    {
    
  }
#line 2889 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 930 "src/sharpie.y" /* yacc.c:1646  */
    {
  
  }
#line 2897 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1030 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"sddadadee"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2906 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1139 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 2914 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1144 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2922 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1147 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2930 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1152 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->init_list).pb((yyvsp[0].NT));
  }
#line 2939 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1156 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->init_list).pb((yyvsp[0].NT));
  }
#line 2948 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1199 "src/sharpie.y" /* yacc.c:1646  */
    {
    BeginScope();
  }
#line 2956 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1203 "src/sharpie.y" /* yacc.c:1646  */
    {
      (yyval.NT)=new Attr();
    }
#line 2964 "sharpie.tab.c" /* yacc.c:1646  */
    break;


#line 2968 "sharpie.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1209 "src/sharpie.y" /* yacc.c:1906  */


/*
 *void print(){
 *    cout<<"Token";
 *    for(int i=0;i<10;i++)
 *      cout<<" ";
 *    cout<<"Occurences"<<"\t"<<"Lexemes"<<endl;
 *    map<int, vector<char*> > ::iterator it;
 *    for(it=TknStats.begin();it!=TknStats.end();it++){
 *      int idx=it->X;
 *      int length=TknStr[idx].size();
 *      cout<<TknStr[idx];
 *      int space=20-length;
 *      for(int i=0;i<space;i++)cout<<" ";
 *      cout<<FreqToken[idx]<<"\t\t";
 *      sort(it->Y.begin(),it->Y.end(),comp);
 *      for(int i=0;i<it->Y.size();i++)
 *      {
 *        if(i>0 && strcmp(it->Y[i],it->Y[i-1])==0)
 *          continue;
 *        if(i==0)
 *          cout<<it->Y[i]<<endl;
 *        else 
 *        {
 *          for(int i=0;i<20;i++)
 *        cout<<" ";
 *          cout<<"  ";
 *          cout<<"\t\t";
 *          cout<<it->Y[i]<<endl;
 *        }
 *      }
 *    }
 *}
 *
 */

void getStrings(){

TknStr[INTEGER_LITERAL]="INTEGER_LITERAL";
TknStr[CHARACTER_LITERAL]="CHARACTER_LITERAL";
TknStr[COMMA]="COMMA";
TknStr[LEFT_BRACKET]="LEFT_BRACKET";
TknStr[RIGHT_BRACKET]="RIGHT_BRACKET";
TknStr[RANK_SPECIFIER]="RANK_SPECIFIER";
TknStr[PLUSEQ]="PLUSEQ";
TknStr[MINUSEQ]="MINUSEQ";
TknStr[STAREQ]="STAREQ";
TknStr[DIVEQ]="DIVEQ";
TknStr[MODEQ]="MODEQ";
TknStr[XOREQ]="XOREQ";
TknStr[ANDEQ]="ANDEQ";
TknStr[OREQ]="OREQ";
TknStr[LTLT]="LTLT";
TknStr[GTGT]="GTGT";
TknStr[GTGTEQ]="GTGTEQ";
TknStr[LTLTEQ]="LTLTEQ";
TknStr[EQEQ]="EQEQ";
TknStr[NOTEQ]="NOTEQ";
TknStr[LEQ]="LEQ";
TknStr[GEQ]="GEQ";
TknStr[ANDAND]="ANDAND";
TknStr[OROR]="OROR";
TknStr[PLUSPLUS]="PLUSPLUS";
TknStr[MINUSMINUS]="MINUSMINUS";
TknStr[ARROW]="ARROW";
TknStr[COLCOL]="COLCOL";
TknStr[IDENTIFIER]="IDENTIFIER";
TknStr[INT_TYPE]="INT_TYPE";
TknStr[BOOL_TYPE]="BOOL_TYPE";
TknStr[CHAR_TYPE]="CHAR_TYPE";
TknStr[ABSTRACT]="ABSTRACT";
TknStr[BREAK]="BREAK";
TknStr[BASE]="BASE";
TknStr[CASE]="CASE";
TknStr[CLASS]="CLASS";
TknStr[CONST]="CONST";
TknStr[CONTINUE]="CONTINUE";
TknStr[DEFAULT]="DEFAULT";
TknStr[DO]="DO";
TknStr[ELSE]="ELSE";
TknStr[FALSE]="FALSE";
TknStr[FOR]="FOR";
TknStr[FOREACH]="FOREACH";
TknStr[GOTO]="GOTO";
TknStr[IF]="IF";
TknStr[IN]="IN";
TknStr[INTERFACE]="INTERFACE";
TknStr[NAMESPACE]="NAMESPACE";
TknStr[NEW]="NEW";
TknStr[NULL_TYPE]="NULL_TYPE";
TknStr[OBJECT]="OBJECT";
TknStr[OPERATOR]="OPERATOR";
TknStr[OUT]="OUT";
TknStr[OVERRIDE]="OVERRIDE";
TknStr[PRIVATE]="PRIVATE";
TknStr[PROTECTED]="PROTECTED";
TknStr[PUBLIC]="PUBLIC";
TknStr[RETURN]="RETURN";
TknStr[SIZEOF]="SIZEOF";
TknStr[STRING_TYPE]="STRING_TYPE";
TknStr[STRUCT]="STRUCT";
TknStr[SWITCH]="SWITCH";
TknStr[THIS]="THIS";
TknStr[TRUE]="TRUE";
TknStr[TYPEOF]="TYPEOF";
TknStr[USING]="USING";
TknStr[VIRTUAL]="VIRTUAL";
TknStr[VOID]="VOID";
TknStr[WHILE]="WHILE";
TknStr[STRING_LITERAL]="STRING_LITERAL";

TknStr[(int)('.')]="\'.\'";
TknStr[(int)(':')]="\':\'";
TknStr[(int)(';')]="\';\'";
TknStr[(int)('(')]="\'(\'";
TknStr[(int)(')')]="\')\'";
TknStr[(int)('<')]="\'<\'";
TknStr[(int)('>')]="\'>\'";
TknStr[(int)('+')]="\'+\'";
TknStr[(int)('-')]="\'-\'";
TknStr[(int)('*')]="\'*\'";
TknStr[(int)('/')]="\'/\'";
TknStr[(int)('%')]="\'%\'";
TknStr[(int)('&')]="\'&\'";
TknStr[(int)('|')]="\'|\'";
TknStr[(int)('!')]="\'!\'";
TknStr[(int)('~')]="\'~\'";
TknStr[(int)('^')]="\'^\'";
TknStr[(int)('=')]="\'=\'";
TknStr[(int)('?')]="\'?\'";
TknStr[(int)('"')]="\'\"\'";
TknStr[(int)('{')]="\'{\'";
TknStr[(int)('}')]="\'}\'";
}







int main(int argc, char** argv) {
    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
	    cout << "I can't open file!" << endl;
	    return -1;
    }
    CurTable=new SymTable();
    CurLabel=0;
    yyin = myfile;
    do {
    	yyparse();
    } while (!feof(yyin));

    int rules = (int)(R.size());
    for(int r=rules-1;r>=0;r--){
	cout<<R[r][0]<<" -> ";
	for(int i=1;i<(int)(R[r].size()); i++){
		cout<<R[r][i]<<" ";
	}
	cout<<" ;";
	cout<<endl;
    }



/*
 *    FILE *myfile = fopen(argv[1], "r");
 *    if (!myfile) {
 *        cout << "Can't open the file!" << endl;
 *        return -1;
 *    }
 *    yyin = myfile;
 *
 *    getStrings();
 *    int x;
 *    while(1){
 *        x=yylex();
 *        if(x == 0)break;
 *        TknStats[x].push_back(strdup(yytext));
 *        FreqToken[x]++;
 *    }
 */
}



void yyerror(const char *s) {
	/*cout << "EEK, parse error!  Message: " << s << endl;*/
	printf("%d:%s LA=[%s]\n",yylineno,s,yytname[YYTRANSLATE(yychar)]);
	exit(-1);
}
