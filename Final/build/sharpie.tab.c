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
#define mp make_pair

/*#define YYDEBUG 1*/

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
#define YYERROR_VERBOSE
extern int yylineno;



string tmpLbl[100]; // memoizing labels for switch case
map<int, string> TknStr;
map<int, int> FreqToken;
vector<vector<string> > R;
vector<string> T;
SymTable* CurTable;
int CurLabel;
int NumScopes;
vector<pair<string,string> > par_var;
bool CS_FLAG=true;
string CS_Name;
bool FLAG;

string change_string(string s)
{
  /*return s;*/
  int len = s.length();
  string ret = "";
  int idx = len;
  for(int i = len-1; i >= 0; i--)
  {
    if(s[i]=='_')
    {
      idx = i;
    }
  }
  for(int i = 0; i < idx; i++)
    ret+=s[i];
  return ret;
}

void Combine(vector<string> &a, vector<string> b, vector<string> c){
  b.insert(b.end(),c.begin(),c.end());
  a=b;
}

void BeginScope(){
  /*cout<<"HELLO"<<endl;*/
  SymTable* newTable = new SymTable();
  newTable->table_id=NumScopes;
  (CurTable->children).pb(newTable);
  newTable->parent = CurTable;
  CurTable = newTable;
  NumScopes++;
  if(FLAG){
    for(int i=0;i<(int)(par_var).size();i++){
      CurTable->insertVariable(par_var[i].X, par_var[i].Y);
    }
    /*cout<<" params: in "<<(CurTable->table_id)<<endl;*/
    FLAG=false;
  }
  if(CS_FLAG == true){
    (CurTable->CSname)=CS_Name;
  }
  par_var.clear();
}

void EndScope(){
  CurTable=CurTable->parent;
}

SymTable* getDeclScope(string id,SymTable* ct){
  if(ct == NULL){
    return NULL;
  }
  if((ct->Node).find(id) == (ct->Node).end()){
    return getDeclScope(id,ct->parent);
  }
  return ct;
}

string getLabel(){
  CurLabel++;
  return "L"+to_string(CurLabel);
}

string getCat(string s){
  SymTable* DeclTbl=getDeclScope(s, CurTable);
  return (DeclTbl->Node)[s].Y;
}



string getTyp(string s){
  SymTable* DeclTbl=getDeclScope(s, CurTable);
  return (DeclTbl->Node)[s].X;
}


bool CheckTyp(Attr* a, Attr* b, string typ){
    string typ1=getTyp(change_string(a->place));
    string typ2=getTyp(change_string(b->place));
    if(typ == "null"){
      if(typ1 != typ2){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbols "<<(a->place)<<" and "<<(b->place)<<" are of type "<<typ1<<" and "<<typ2<<". They can't be compared!"<<endl;
	exit(0);
      }
      return true;
    }
    if(typ1 != typ){
      cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<(a->place)<<" is of type "<<typ1<<". Expected type: "<<typ<<endl;
      exit(0);
    }
    if(typ2 != typ){
      cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<(b->place)<<" is of type "<<typ2<<". Expected type: "<<typ<<endl;
      exit(0);
    }
    return true;
}

string getTAC(int flag, string OP, string dest, string op1, string op2="NONE"){
  if(flag == 1){
    return OP+","+dest+","+op1+","+op2;
  }
  if(flag == 2){
    return OP+","+dest+","+op1;
  }
}



void translate(Attr* &p, Attr* q, Attr* r, string OP, string ret_typ="int"){
    if(!(CurTable->lookup(change_string(q->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<(q->place)<<" used without declaration."<<endl;
      exit(0);
    }
    if(!(CurTable->lookup(change_string(r->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<(r->place)<<" used without declaration."<<endl;
      exit(0);
    }
    string tp = CurTable->getTemp(ret_typ);
    p = new Attr();
    p->place = tp;
    Combine(p->code,q->code, r->code);
    string code_ = getTAC(1, OP, p->place, q->place, r->place);
    p->code.pb(code_);
}





#line 234 "sharpie.tab.c" /* yacc.c:339  */

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
    COLCOL = 373,
    WRITELINE = 374,
    READLINE = 375
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 169 "src/sharpie.y" /* yacc.c:355  */

	int ival;
	float fval;
	char* sval;
	Attr* NT;

#line 358 "sharpie.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SHARPIE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 375 "sharpie.tab.c" /* yacc.c:358  */

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
#define YYLAST   1316

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  170
/* YYNRULES -- Number of rules.  */
#define YYNRULES  362
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  609

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   376

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,     2,     2,     2,    87,    80,     2,
      77,    78,    85,    83,     2,    84,    79,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    93,    95,
      88,    94,    89,    92,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    96,    91,    97,    82,     2,     2,     2,
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
       2,     2,    73,    74,    75,    76,     2
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   278,   278,   282,   287,   292,   297,   303,   307,   313,
     318,   323,   326,   331,   334,   340,   343,   349,   352,   359,
     364,   369,   376,   377,   384,   385,   390,   393,   396,   397,
     400,   405,   409,   416,   419,   422,   425,   430,   433,   436,
     439,   442,   445,   448,   451,   454,   459,   464,   465,   466,
     469,   470,   587,   590,   595,   596,   628,   631,   637,   640,
     641,   644,   649,   654,   655,   658,   661,   666,   667,   670,
     673,   676,   681,   684,   693,   702,   705,   721,   737,   740,
     743,   754,   755,   758,   761,   764,   765,   766,   767,   768,
     769,   772,   773,   776,   777,   780,   781,   784,   787,   792,
     796,   802,   805,   815,   821,   824,   828,   834,   837,   841,
     845,   849,   855,   858,   863,   869,   872,   878,   881,   887,
     890,   896,   899,   905,   908,   914,   917,   922,   971,   972,
     973,   974,   975,   976,   977,   978,   979,   980,   981,   984,
     987,   992,   997,  1002,  1006,  1018,  1021,  1026,  1041,  1056,
    1059,  1062,  1066,  1069,  1072,  1078,  1086,  1089,  1096,  1100,
    1108,  1115,  1120,  1245,  1249,  1255,  1270,  1288,  1291,  1296,
    1302,  1306,  1309,  1312,  1315,  1320,  1323,  1328,  1343,  1368,
    1420,  1426,  1429,  1434,  1438,  1444,  1454,  1457,  1463,  1466,
    1469,  1472,  1477,  1516,  1519,  1559,  1562,  1567,  1570,  1575,
    1578,  1583,  1586,  1591,  1596,  1601,  1604,  1610,  1613,  1616,
    1619,  1620,  1625,  1632,  1639,  1642,  1649,  1652,  1658,  1661,
    1673,  1676,  1681,  1684,  1689,  1694,  1697,  1702,  1722,  1730,
    1734,  1741,  1746,  1747,  1750,  1751,  1754,  1757,  1762,  1765,
    1773,  1776,  1781,  1784,  1787,  1793,  1796,  1801,  1804,  1809,
    1813,  1817,  1821,  1825,  1831,  1872,  1880,  1881,  1884,  1885,
    1886,  1889,  1890,  1893,  1900,  1903,  1908,  1917,  1929,  1933,
    1937,  1940,  1943,  1946,  1951,  2010,  2055,  2083,  2112,  2115,
    2120,  2124,  2129,  2134,  2141,  2146,  2161,  2164,  2169,  2172,
    2175,  2176,  2179,  2180,  2181,  2182,  2183,  2184,  2185,  2186,
    2187,  2188,  2189,  2190,  2191,  2192,  2193,  2194,  2195,  2196,
    2197,  2198,  2199,  2200,  2203,  2206,  2209,  2210,  2213,  2214,
    2217,  2220,  2221,  2224,  2225,  2228,  2246,  2253,  2254,  2257,
    2260,  2267,  2270,  2275,  2279,  2285,  2288,  2292,  2293,  2294,
    2298,  2303,  2306,  2311,  2315,  2322,  2325,  2326,  2329,  2332,
    2335,  2336,  2339,  2340,  2343,  2346,  2347,  2350,  2351,  2354,
    2355,  2358,  2362
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
  "COLCOL", "WRITELINE", "READLINE", "'('", "')'", "'.'", "'&'", "'!'",
  "'~'", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "':'", "'='", "';'", "'{'", "'}'", "$accept", "literal",
  "boolean_literal", "namespace_name", "type_name", "type",
  "non_array_type", "simple_type", "primitive_type", "numeric_type",
  "integral_type", "class_type", "array_type", "rank_specifier",
  "rank_specifiers_opt", "variable_reference", "argument_list", "argument",
  "primary_expression", "primary_expression_no_parenthesis",
  "parenthesized_expression", "member_access", "invocation_expression",
  "argument_list_opt", "element_access", "expression_list", "this_access",
  "base_access", "new_expression", "object_creation_expression",
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
  "boolean_expression", "statement", "print_statement", "read_statement",
  "embedded_statement", "block", "statement_list_opt", "statement_list",
  "empty_statement", "declaration_statement", "local_variable_declaration",
  "variable_declarators", "variable_declarator", "variable_initializer",
  "expression_statement", "statement_expression", "selection_statement",
  "if_statement", "switch_statement", "switch_block",
  "switch_sections_opt", "switch_sections", "switch_section",
  "switch_label", "iteration_statement", "while_statement", "do_statement",
  "for_statement", "for_initializer_opt", "for_condition_opt",
  "for_iterator_opt", "for_initializer", "for_condition", "for_iterator",
  "statement_expression_list", "foreach_statement", "jump_statement",
  "break_statement", "continue_statement", "goto_statement",
  "return_statement", "expression_opt", "compilation_unit",
  "using_directives_opt", "namespace_member_declarations_opt",
  "namespace_declaration", "comma_opt", "qualified_identifier",
  "qualifier", "namespace_body", "using_directives", "using_directive",
  "using_alias_directive", "using_namespace_directive",
  "namespace_member_declarations", "namespace_member_declaration",
  "type_declaration", "modifiers_opt", "modifiers", "modifier",
  "class_declaration", "class_name", "class_base_opt", "class_base",
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
  "struct_declaration", "struct_name", "struct_interfaces_opt",
  "struct_interfaces", "struct_body", "struct_member_declarations_opt",
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
       0,   256,   376,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   372,   373,   374,   375,    40,    41,    46,
      38,    33,   126,    43,    45,    42,    47,    37,    60,    62,
      94,   124,    63,    58,    61,    59,   123,   125
};
# endif

#define YYPACT_NINF -374

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-374)))

#define YYTABLE_NINF -352

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -33,    33,    68,   248,   -33,  -374,  -374,  -374,  -374,   -32,
      11,  -374,    82,  -374,  -374,   109,  -374,  -374,  -374,  -374,
    -374,   259,  -374,  -374,   153,   281,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,   109,  -374,    77,   103,   115,  -374,   211,
     230,   244,  -374,   186,  -374,   -33,   192,  -374,   197,   208,
    -374,   216,  -374,   512,  -374,  -374,  -374,   189,   229,  -374,
    -374,   109,   262,  -374,  -374,   109,   286,  -374,  -374,   207,
     108,   233,  -374,  -374,  -374,   339,  -374,   382,  -374,   192,
     382,   347,   192,   382,  -374,   192,  -374,   109,   109,   281,
    -374,  -374,  -374,   304,   -30,  -374,  -374,   379,   305,  -374,
     281,  -374,   382,  -374,  -374,   234,   316,   156,  -374,  -374,
    -374,   127,  -374,  -374,  -374,   317,  -374,  -374,  -374,  -374,
    -374,  -374,   370,  -374,   388,  -374,   411,  -374,  -374,  -374,
    -374,   411,   411,  -374,   353,  -374,  -374,  -374,  -374,   323,
     178,  -374,   329,   -20,   109,   402,   158,   174,  -374,   200,
    -374,  -374,  -374,  -374,  -374,  -374,   357,   358,  -374,  -374,
    -374,  -374,  -374,  -374,   380,   361,   363,   107,  1225,    12,
    -374,   364,  -374,  -374,  -374,  -374,  -374,  -374,   659,   380,
     380,  -374,   365,   439,  -374,  -374,   495,   367,   380,   368,
     863,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,   375,   423,  -374,   380,  -374,  -374,  1107,
    1107,   359,    32,   371,   791,  -374,   381,   390,   426,   392,
     495,  -374,  1107,   395,  -374,  -374,   403,   404,  -374,   408,
     409,   924,  1107,  1107,  1107,  1107,  1107,  1107,  -374,  -374,
    -374,   423,   413,   414,    34,   418,  -374,  -374,    24,  -374,
    -374,  -374,  -374,    25,  -374,  -374,  -374,  -374,  -374,    37,
      60,    64,  -374,  -374,  -374,  -374,  -374,  -374,  -374,   362,
     659,  -374,  -374,   405,  -374,   406,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,   144,
    -374,   396,   419,   412,   380,   469,   428,   420,   863,   413,
     414,  -374,  -374,  -374,  -374,    64,   261,   240,   303,    65,
     330,   424,   417,   429,   484,    26,  -374,  -374,  -374,  -374,
      21,  -374,   495,   416,  -374,   437,  -374,  -374,  -374,  1107,
     487,  -374,   447,  1107,   495,   427,  1107,   452,   518,    13,
    -374,   435,  -374,  1107,   397,  1107,   985,   985,    20,    29,
      31,   270,   453,   141,  -374,  -374,  -374,  -374,  -374,  -374,
     527,   504,   505,  1107,   506,   985,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  1107,  -374,  -374,
    -374,  -374,  1107,   985,   284,   284,    -5,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,   441,   534,  -374,  1107,
    1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107,
    1107,  1107,  1107,  1107,  1107,  1107,  1107,  1107,   511,  -374,
     199,  -374,  -374,   466,  -374,  -374,   450,  -374,   543,  -374,
     521,  -374,  -374,   474,   985,  1107,  -374,  -374,   481,   483,
     488,   489,  1107,   496,  -374,   497,  -374,  -374,   498,    20,
    -374,  -374,   499,   500,  1046,  1163,    20,  -374,  -374,   237,
    -374,   560,  -374,   502,  -374,  -374,   249,   503,  -374,   476,
    -374,  -374,   508,   509,  -374,   863,  -374,  -374,  -374,  -374,
     261,   261,   240,   240,   303,   303,   303,   303,    65,    65,
     330,   424,   417,   429,   484,   494,    39,  1107,  -374,  1107,
    1107,  1107,   539,   791,   513,   307,   501,  -374,  -374,   791,
    -374,  -374,   507,   515,  1107,  -374,  1107,  1107,  1107,  -374,
     516,  -374,   985,  -374,  -374,  -374,  -374,   985,   985,  -374,
    1107,   495,  -374,  -374,   523,  -374,   517,  -374,  -374,  -374,
    1107,   550,  -374,   411,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  1107,  -374,   525,   526,  -374,   566,   519,
    1107,   528,   791,  -374,   522,  -374,    17,  -374,  -374,  -374,
     529,  -374,   530,  -374,   543,  -374,   791,  -374,  -374,  -374,
    -374,  1107,   520,   514,    17,  -374,   659,  -374,  -374,   791,
    -374,  -374,   524,  -374,  -374,  -374,   659,  -374,  -374
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     362,     0,     0,   362,   221,   232,   234,   235,   220,   227,
       0,     9,     0,     1,   249,     0,   250,   251,   252,   253,
     240,   362,   238,   241,     0,   246,   247,   242,   243,   244,
     245,   233,   229,     0,   237,   228,   227,     0,   239,     0,
       0,     0,   248,     0,   230,   362,   362,   255,   362,   362,
     326,   362,   236,   362,   226,   224,   225,     0,     0,   257,
     256,     0,     0,   347,   346,     0,     0,   328,   327,     0,
     362,   245,    22,    23,   261,   258,    10,   259,   362,   362,
     348,   362,   362,   329,   362,   362,   231,     0,     0,   362,
     361,   254,   358,     0,   362,   352,   354,     0,   357,   345,
     362,   325,   260,   262,   273,     0,     0,   362,   266,   268,
     269,     0,   270,   271,   272,   245,   349,   353,   357,    20,
      18,    21,     0,    14,     0,    11,    13,    15,    17,    19,
      16,    12,    10,   339,     0,   335,   336,   337,   338,     0,
     362,   333,   245,   227,     0,     0,     0,     0,   289,     0,
     263,   267,   281,   362,   280,   275,     0,     0,    27,    25,
      24,    26,   330,   334,   362,     0,     0,   165,     0,     0,
     163,     0,   322,   321,   288,   324,   323,   314,   362,   362,
     362,   287,     0,   279,   282,   284,     0,   286,   362,     0,
       0,   306,   307,   308,   309,   313,   312,   296,   297,   299,
     298,   303,   294,   295,   292,   293,   300,   301,   302,   311,
     310,   305,   304,     0,     0,   274,   362,     3,     4,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     0,     0,
       0,     6,   362,     0,    58,     7,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,    37,
       2,     0,    15,    16,    70,    36,    35,    39,    40,    41,
      42,    43,    44,    61,    38,    45,    84,    72,    78,    82,
      83,     0,    75,   172,   158,   145,   146,   144,   149,     0,
     157,   150,   143,     0,   151,     0,   152,   175,   176,   153,
     188,   189,   190,   191,   154,   208,   209,   210,   211,    71,
     156,     0,     0,   362,   362,     0,     0,     0,   362,     0,
       0,    40,    61,    82,    83,    97,   101,   104,   107,   112,
     115,   117,   119,   121,   123,   125,   139,   140,   167,   166,
      71,   168,     0,   165,   164,     0,    76,    77,   212,     0,
       0,   213,     0,   362,     0,     0,     0,     0,    11,    12,
     217,     0,   216,     0,     0,     0,     0,     0,   362,   362,
     362,   101,     0,    71,    69,    73,    74,    79,    80,    81,
     162,     0,     0,     0,     0,   362,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   128,     0,   155,   159,
     161,   169,     0,   362,     0,     0,     0,   315,   317,   316,
     283,   286,   285,   277,   320,   343,     0,   342,   341,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,    56,    59,     0,   201,   205,     0,   196,   202,   195,
       0,   214,   142,     0,   362,     0,    64,   215,     0,     0,
       0,     0,     0,     0,    33,     0,    96,    95,     0,    92,
      93,    91,     0,     0,     0,    46,   362,    48,    49,     0,
      47,    53,    31,     0,    52,   127,     0,     0,   359,     0,
     356,   355,     0,     0,   340,     0,    98,    99,   100,    97,
     102,   103,   105,   106,   110,   111,   108,   109,   113,   114,
     116,   118,   120,   122,   124,     0,     0,     0,    60,     0,
     362,     0,     0,     0,     0,     0,     0,    68,    67,     0,
      34,    30,     0,     0,     0,    94,     0,     0,     0,    85,
       0,    54,     0,    50,    55,    51,   360,   362,   362,   344,
       0,     0,   290,    57,     0,   203,     0,   198,   197,   206,
       0,   177,    62,   362,   362,   179,   192,   147,   148,    90,
      88,    89,    86,     0,    32,     0,     0,   126,     0,     0,
     362,     0,     0,    29,   362,    28,   362,    87,   318,   319,
       0,   193,     0,   200,   204,   199,     0,   178,    63,    66,
      65,     0,     0,     0,   182,   183,     0,   181,   291,     0,
     207,   141,     0,   187,   180,   184,   185,   194,   186
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,  -374,  -374,  -374,   400,   -86,   385,  -374,   -93,  -374,
    -374,   -52,   393,  -116,  -374,  -374,  -374,  -332,  -374,  -374,
    -374,  -374,  -123,  -373,  -374,  -323,  -374,  -374,  -374,   -88,
    -374,  -374,  -374,  -374,  -374,   159,   -17,    49,   -49,  -374,
    -325,  -374,   166,  -232,   -21,   -82,   -23,   205,   203,   206,
     209,   202,  -374,  -374,    79,  -374,   301,  -374,  -337,  -274,
    -374,  -374,  -191,   -98,  -374,    35,  -374,  -374,   289,   378,
     422,  -306,  -374,  -335,  -374,  -374,  -374,  -374,  -374,  -374,
      43,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,    63,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,   593,  -374,  -374,   204,    -1,  -374,  -374,  -374,   635,
    -374,  -374,   588,     2,    62,   238,  -374,   617,  -374,  -374,
    -374,  -374,   184,  -374,  -374,  -374,   536,   -97,   -74,  -374,
      97,  -374,  -374,   340,  -374,  -374,   -19,  -374,  -374,  -374,
      23,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,   510,  -342,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,   552,  -374,  -374,   257,   -83,    46
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   249,   250,    10,   123,   251,   125,   126,   309,   128,
     129,   310,   131,   457,   574,   520,   471,   472,   254,   255,
     256,   257,   311,   473,   259,   430,   260,   261,   262,   312,
     264,   588,   265,   266,   267,   268,   313,   314,   315,   272,
     458,   459,   460,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   387,   454,   602,   443,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   169,
     170,   329,   284,   285,   286,   287,   288,   555,   593,   594,
     595,   596,   289,   290,   291,   292,   436,   546,   582,   437,
     547,   583,   438,   293,   294,   295,   296,   297,   298,   351,
       2,     3,    69,    20,    55,   330,    12,    46,     4,     5,
       6,     7,    21,    22,    23,    24,    25,    26,    27,    48,
      58,    59,    77,    79,   106,   107,   108,   109,   110,   111,
     182,   155,   183,   184,   185,   186,   112,   147,   148,   213,
     113,   149,   397,   398,   114,   174,   177,    28,    51,    66,
      67,    85,   139,   140,   141,   331,   406,   407,    29,    62,
      63,    82,    93,    94,    95,    96,    97,   480,    89,    30
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,   100,   405,   135,   127,    75,   389,   446,   435,   361,
     159,   124,   127,   154,    37,   160,   161,   214,   451,   146,
     477,   158,    92,    38,   453,   455,   136,   392,   158,  -170,
    -171,   482,    43,   342,   462,   463,     1,   158,   339,   158,
     373,   127,  -173,   135,   541,   130,     8,    32,   146,   173,
     469,   176,   426,   130,   591,   258,    76,   164,   592,    32,
      76,   483,    33,     9,    76,  -174,   136,  -351,    13,   476,
     178,   514,    38,   376,   377,   378,   379,   380,   381,   382,
     383,   137,   130,   384,   385,   252,    76,    76,   416,   417,
     263,     8,    56,   127,    60,    64,   132,    68,   393,    71,
     305,   258,  -170,  -171,   132,   456,    34,   215,   371,   308,
     372,   340,    35,   374,   456,  -173,   456,   542,   427,  -170,
    -171,   137,   515,   138,    90,    56,   253,    98,    56,   271,
      90,    56,  -173,   132,   130,   115,   263,   127,  -174,    36,
     118,   530,    14,   165,   347,   171,   142,   392,   359,   158,
     392,   104,   158,   418,   419,  -174,    44,   258,   386,    15,
      16,   269,   133,   138,   565,   566,    17,    18,    19,   104,
     336,   337,   544,   545,   -10,   271,   549,   299,   130,   539,
     490,   491,    32,   161,  -227,   132,    32,   252,   167,   360,
      14,    39,   263,   364,   365,   366,   367,   368,   369,    90,
     564,   190,   133,    40,   507,  -223,   508,   269,    16,   404,
     187,    45,    14,   168,    17,    18,    19,    41,   393,    36,
     258,   393,   152,   153,   300,   187,   187,   270,   253,   132,
      16,   271,   589,   160,   187,   435,    17,    18,    19,   127,
     363,    47,   507,    72,   531,    80,   428,   466,  -218,    83,
     252,   127,    73,  -265,   507,   263,   534,   273,   440,  -219,
      49,   127,   187,   269,   143,   119,   120,   121,   450,   172,
     153,   102,    39,   270,    50,  -332,   301,   302,   352,   299,
     130,    52,    14,    91,    40,   306,    99,    54,    72,   101,
      57,   253,   130,    14,   271,   175,   153,    73,    41,    15,
      16,    61,   130,   273,    86,   144,    17,    18,    19,    65,
      15,    16,   507,   335,   553,    14,   145,    17,    18,    19,
     414,   415,   551,   412,   413,    78,   269,   105,   556,   270,
    -222,   132,   389,    16,   494,   495,   496,   497,   134,    17,
      18,    19,   299,   132,    87,   105,   409,   410,   411,   399,
     401,   420,   421,   132,   408,   464,   410,   411,    81,   273,
     486,   487,   488,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   134,   478,
     479,   587,    84,   143,   119,   120,   121,    88,   258,   439,
     258,    39,   270,   492,   493,   600,   258,   498,   499,    92,
     156,   116,  -350,    40,   461,   461,   461,    72,   607,    36,
     119,   120,   121,   150,  -264,   486,    73,    41,   157,   158,
     162,   474,   273,   263,   144,   263,  -331,    36,   119,   120,
     121,   263,   166,    72,   179,   180,   181,   573,   188,   474,
     189,   216,    73,   303,   304,  -278,   307,   258,   127,   258,
     122,    72,   332,   333,   338,   568,   345,    74,   343,   388,
      73,    74,   271,   258,   271,    74,   341,   344,   449,   346,
     271,   576,   353,   258,   394,   559,   258,   560,   561,   562,
     354,   355,   263,   258,   263,   356,   357,    74,   103,   130,
     474,   328,   371,   372,   269,   375,   269,   395,   263,   402,
     390,   391,   269,   252,   422,   396,   403,   423,   263,   425,
     190,   263,   461,   252,   577,   429,   153,   432,   263,   433,
     424,   271,   441,   271,   445,    36,   119,   120,   121,   444,
     447,   465,   214,   350,   467,   468,   470,   271,   484,   485,
     132,   506,   362,   509,   253,   510,    14,   271,   511,    72,
     271,   512,   513,   269,   253,   269,   548,   271,    73,   516,
     270,   517,   270,    15,    16,   532,   518,   519,   270,   269,
      17,    18,    19,   536,   522,   523,   524,   526,   527,   269,
     533,   535,   269,   474,   474,   537,   538,   540,   550,   269,
     273,   552,   273,   572,   563,   299,   580,   554,   273,   575,
      90,   569,   557,   578,   579,   299,   586,   598,   599,   328,
     558,   604,   570,   603,   581,   348,   585,   608,   308,   270,
     590,   270,   597,   349,   529,   525,   501,   500,   504,   370,
     502,   606,   434,   584,   503,   270,   334,   605,    53,    31,
     431,    70,    42,   151,   400,   270,   117,   442,   270,   273,
     163,   273,   481,     0,   448,   270,   442,     0,     0,     0,
       0,     0,   217,   218,     0,   273,     0,     0,     0,     0,
       0,     0,     0,     0,   431,   273,     0,     0,   273,     0,
       0,     0,     0,     0,     0,   273,   219,   220,   475,    36,
     119,   120,   121,   431,   221,   222,     0,     0,     0,   223,
       0,   224,     0,   225,   226,   227,   228,   229,     0,     0,
       0,   230,   231,    72,     0,     0,     0,     0,     0,     0,
     232,     0,    73,     0,   233,   234,   235,   236,   505,     0,
       0,   237,   238,     0,   239,   240,   241,     0,     0,   242,
     243,   244,   245,   246,   247,     0,   431,     0,     0,     0,
       0,     0,     0,   521,   248,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   328,     0,     0,     0,
       0,     0,     0,     0,   217,   218,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   543,     0,
     442,   442,     0,     0,     0,     0,     0,     0,   219,   220,
       0,    36,   119,   120,   121,     0,   221,   222,     0,     0,
       0,   223,     0,   224,     0,   225,   226,   227,   228,   229,
       0,   567,     0,   230,   231,    72,     0,     0,     0,     0,
       0,   571,   232,     0,    73,     0,   233,   234,   235,   236,
       0,     0,     0,   237,   238,     0,   217,   218,   241,     0,
       0,   242,   243,   244,   245,   246,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   248,   153,     0,     0,
     219,   220,   601,    36,   119,   120,   121,     0,     0,   222,
       0,     0,     0,     0,     0,     0,     0,   225,     0,     0,
       0,     0,     0,     0,     0,   230,   231,    72,     0,     0,
       0,     0,     0,     0,     0,     0,    73,   217,   218,   234,
     235,   236,     0,     0,     0,     0,   238,     0,     0,     0,
     241,     0,     0,   242,   243,   244,   245,   246,   247,     0,
       0,   219,   220,     0,    36,   119,   120,   121,     0,   308,
     222,     0,     0,     0,     0,     0,     0,     0,   225,     0,
       0,     0,     0,     0,     0,     0,   230,   231,    72,     0,
       0,     0,     0,     0,     0,     0,     0,    73,   217,   218,
     234,   235,   236,     0,     0,   358,     0,   238,     0,     0,
       0,   241,     0,     0,   242,   243,   244,   245,   246,   247,
       0,     0,   219,   220,     0,    36,   119,   120,   121,     0,
       0,   222,     0,     0,     0,     0,     0,     0,     0,   225,
       0,     0,     0,     0,     0,     0,     0,   230,   231,    72,
       0,   452,     0,     0,     0,     0,     0,     0,    73,   217,
     218,   234,   235,   236,     0,     0,     0,     0,   238,     0,
       0,     0,   241,     0,     0,   242,   243,   244,   245,   246,
     247,     0,     0,   219,   220,     0,    36,   119,   120,   121,
       0,     0,   222,     0,     0,     0,     0,     0,     0,     0,
     225,     0,     0,     0,     0,     0,     0,     0,   230,   231,
      72,     0,     0,     0,     0,     0,     0,     0,     0,    73,
     217,   218,   234,   235,   236,     0,     0,     0,     0,   238,
       0,     0,     0,   241,   528,     0,   242,   243,   244,   245,
     246,   247,     0,     0,   219,   220,     0,    36,   119,   120,
     121,     0,     0,   222,     0,     0,     0,     0,     0,     0,
       0,   225,     0,     0,     0,     0,     0,     0,     0,   230,
     231,    72,     0,     0,     0,     0,   217,   218,     0,     0,
      73,     0,     0,   234,   235,   236,     0,     0,     0,     0,
     238,     0,     0,     0,   241,     0,     0,   242,   243,   244,
     245,   246,   247,    36,   119,   120,   121,     0,     0,   222,
       0,     0,     0,     0,     0,     0,     0,   225,     0,     0,
       0,     0,     0,     0,     0,   230,   231,    72,     0,     0,
       0,     0,     0,     0,     0,     0,    73,     0,     0,   234,
     235,   236,     0,     0,     0,     0,   238,     0,     0,     0,
     241,     0,   191,   192,   243,   244,   193,   194,   195,   196,
       0,     0,   197,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212
};

static const yytype_int16 yycheck[] =
{
       1,    84,   308,   100,    97,    57,   280,   349,   343,   241,
     126,    97,   105,   111,    15,   131,   132,     5,   355,   105,
     393,     8,    52,    21,   356,   357,   100,     6,     8,     5,
       5,    36,    33,   224,   359,   360,    69,     8,     6,     8,
       6,   134,     5,   140,     5,    97,     0,    79,   134,   147,
     373,   149,    26,   105,    37,   178,    57,    77,    41,    79,
      61,    66,    94,    30,    65,     5,   140,    97,     0,   392,
     153,   444,    70,     9,    10,    11,    12,    13,    14,    15,
      16,   100,   134,    19,    20,   178,    87,    88,    23,    24,
     178,    45,    46,   186,    48,    49,    97,    51,    77,    53,
     186,   224,    78,    78,   105,    85,    95,    95,    79,    96,
      79,    79,    30,    79,    85,    78,    85,    78,    92,    95,
      95,   140,   445,   100,    78,    79,   178,    81,    82,   178,
      84,    85,    95,   134,   186,    89,   224,   230,    78,    30,
      94,   466,    34,   144,   230,   146,   100,     6,   241,     8,
       6,    89,     8,    88,    89,    95,    79,   280,    94,    51,
      52,   178,   100,   140,   537,   538,    58,    59,    60,   107,
     219,   220,   509,   510,    30,   224,   511,   178,   230,   485,
     412,   413,    79,   299,    77,   186,    79,   280,    30,   241,
      34,    38,   280,   242,   243,   244,   245,   246,   247,   153,
     532,    94,   140,    50,     5,    97,     7,   224,    52,   307,
     164,    96,    34,    55,    58,    59,    60,    64,    77,    30,
     343,    77,    95,    96,   178,   179,   180,   178,   280,   230,
      52,   280,   574,   349,   188,   570,    58,    59,    60,   332,
     241,    30,     5,    54,     7,    61,   332,   363,     0,    65,
     343,   344,    63,    97,     5,   343,     7,   178,   344,     0,
      30,   354,   216,   280,    30,    31,    32,    33,   354,    95,
      96,    87,    38,   224,    30,    97,   179,   180,   232,   280,
     332,    95,    34,    79,    50,   188,    82,    95,    54,    85,
      93,   343,   344,    34,   343,    95,    96,    63,    64,    51,
      52,    93,   354,   224,    97,    71,    58,    59,    60,    93,
      51,    52,     5,   216,     7,    34,    82,    58,    59,    60,
      17,    18,   513,    83,    84,    96,   343,    89,   519,   280,
      97,   332,   606,    52,   416,   417,   418,   419,   100,    58,
      59,    60,   343,   344,     5,   107,    85,    86,    87,   303,
     304,    21,    22,   354,   308,    85,    86,    87,    96,   280,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   140,    95,
      96,   572,    96,    30,    31,    32,    33,     5,   511,   343,
     513,    38,   343,   414,   415,   586,   519,   420,   421,    52,
      30,    97,    97,    50,   358,   359,   360,    54,   599,    30,
      31,    32,    33,    97,    97,   464,    63,    64,    30,     8,
      97,   375,   343,   511,    71,   513,    97,    30,    31,    32,
      33,   519,    30,    54,    77,    77,    56,   553,    77,   393,
      77,    77,    63,    78,     5,    78,    78,   570,   541,   572,
      71,    54,    77,    30,    95,   541,    30,    57,    77,    97,
      63,    61,   511,   586,   513,    65,    95,    77,    71,    77,
     519,   554,    77,   596,    78,   524,   599,   526,   527,   528,
      77,    77,   570,   606,   572,    77,    77,    87,    88,   541,
     444,   190,    79,    79,   511,    77,   513,    78,   586,    30,
      95,    95,   519,   596,    80,    93,    78,    90,   596,    25,
      94,   599,   466,   606,   563,    78,    96,    30,   606,    72,
      91,   570,    95,   572,     6,    30,    31,    32,    33,    77,
      95,    78,     5,   232,    30,    30,    30,   586,    97,     5,
     541,    30,   241,    77,   596,    95,    34,   596,     5,    54,
     599,    30,    78,   570,   606,   572,   510,   606,    63,    78,
     511,    78,   513,    51,    52,     5,    78,    78,   519,   586,
      58,    59,    60,    97,    78,    78,    78,    78,    78,   596,
      78,    78,   599,   537,   538,    77,    77,    93,    49,   606,
     511,    78,   513,    43,    78,   596,    30,    96,   519,   553,
     554,    78,    95,    78,    78,   606,    78,    78,    78,   308,
      95,    97,    95,    93,    95,   230,   570,    93,    96,   570,
     574,   572,   576,   230,   465,   459,   423,   422,   426,   251,
     424,   596,   343,   570,   425,   586,   214,   594,    45,     4,
     339,    53,    25,   107,   304,   596,    94,   346,   599,   570,
     140,   572,   395,    -1,   353,   606,   355,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,   586,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   373,   596,    -1,    -1,   599,    -1,
      -1,    -1,    -1,    -1,    -1,   606,    27,    28,   387,    30,
      31,    32,    33,   392,    35,    36,    -1,    -1,    -1,    40,
      -1,    42,    -1,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    63,    -1,    65,    66,    67,    68,   427,    -1,
      -1,    72,    73,    -1,    75,    76,    77,    -1,    -1,    80,
      81,    82,    83,    84,    85,    -1,   445,    -1,    -1,    -1,
      -1,    -1,    -1,   452,    95,    96,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   485,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   507,    -1,
     509,   510,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      -1,    30,    31,    32,    33,    -1,    35,    36,    -1,    -1,
      -1,    40,    -1,    42,    -1,    44,    45,    46,    47,    48,
      -1,   540,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      -1,   550,    61,    -1,    63,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    72,    73,    -1,     3,     4,    77,    -1,
      -1,    80,    81,    82,    83,    84,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    -1,    -1,
      27,    28,   591,    30,    31,    32,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,     3,     4,    66,
      67,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      77,    -1,    -1,    80,    81,    82,    83,    84,    85,    -1,
      -1,    27,    28,    -1,    30,    31,    32,    33,    -1,    96,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,     3,     4,
      66,    67,    68,    -1,    -1,    71,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      -1,    -1,    27,    28,    -1,    30,    31,    32,    33,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63,     3,
       4,    66,    67,    68,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,    84,
      85,    -1,    -1,    27,    28,    -1,    30,    31,    32,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
       3,     4,    66,    67,    68,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    -1,    -1,    27,    28,    -1,    30,    31,    32,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,
      83,    84,    85,    30,    31,    32,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      77,    -1,    17,    18,    81,    82,    21,    22,    23,    24,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    69,   198,   199,   206,   207,   208,   209,   267,    30,
     101,   203,   204,     0,    34,    51,    52,    58,    59,    60,
     201,   210,   211,   212,   213,   214,   215,   216,   245,   256,
     267,   207,    79,    94,    95,    30,    30,   203,   211,    38,
      50,    64,   215,   203,    79,    96,   205,    30,   217,    30,
      30,   246,    95,   199,    95,   202,   267,    93,   218,   219,
     267,    93,   257,   258,   267,    93,   247,   248,   267,   200,
     210,   267,    54,    63,   102,   109,   203,   220,    96,   221,
     220,    96,   259,   220,    96,   249,    97,     5,     5,   266,
     267,   202,    52,   260,   261,   262,   263,   264,   267,   202,
     266,   202,   220,   102,   212,   213,   222,   223,   224,   225,
     226,   227,   234,   238,   242,   267,    97,   262,   267,    31,
      32,    33,    71,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   203,   212,   213,   225,   226,   234,   238,   250,
     251,   252,   267,    30,    71,    82,   103,   235,   236,   239,
      97,   224,    95,    96,   161,   229,    30,    30,     8,   111,
     111,   111,    97,   252,    77,   203,    30,    30,    55,   167,
     168,   203,    95,   161,   243,    95,   161,   244,   266,    77,
      77,    56,   228,   230,   231,   232,   233,   267,    77,    77,
      94,    17,    18,    21,    22,    23,    24,    27,    28,    44,
      67,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,   237,     5,    95,    77,     3,     4,    27,
      28,    35,    36,    40,    42,    44,    45,    46,    47,    48,
      52,    53,    61,    65,    66,    67,    68,    72,    73,    75,
      76,    77,    80,    81,    82,    83,    84,    85,    95,    99,
     100,   103,   106,   109,   116,   117,   118,   119,   120,   122,
     124,   125,   126,   127,   128,   130,   131,   132,   133,   134,
     135,   136,   137,   152,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   170,   171,   172,   173,   174,   180,
     181,   182,   183,   191,   192,   193,   194,   195,   196,   203,
     267,   228,   228,    78,     5,   103,   228,    78,    96,   106,
     109,   120,   127,   134,   135,   136,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   154,   169,
     203,   253,    77,    30,   168,   228,   136,   136,    95,     6,
      79,    95,   160,    77,    77,    30,    77,   103,   104,   110,
     154,   197,   267,    77,    77,    77,    77,    77,    71,   106,
     109,   141,   154,   203,   136,   136,   136,   136,   136,   136,
     167,    79,    79,     6,    79,    77,     9,    10,    11,    12,
      13,    14,    15,    16,    19,    20,    94,   153,    97,   157,
      95,    95,     6,    77,    78,    78,    93,   240,   241,   267,
     231,   267,    30,    78,   161,   169,   254,   255,   267,    85,
      86,    87,    83,    84,    17,    18,    23,    24,    88,    89,
      21,    22,    80,    90,    91,    25,    26,    92,   103,    78,
     123,   154,    30,    72,   166,   171,   184,   187,   190,   267,
     103,    95,   154,   156,    77,     6,   253,    95,   154,    71,
     103,   156,    56,   115,   154,   115,    85,   111,   138,   139,
     140,   267,   138,   138,    85,    78,   111,    30,    30,   123,
      30,   114,   115,   121,   267,   154,   123,   121,    95,    96,
     265,   265,    36,    66,    97,     5,   136,   136,   136,   136,
     141,   141,   142,   142,   143,   143,   143,   143,   144,   144,
     145,   146,   147,   148,   149,   154,    30,     5,     7,    77,
      95,     5,    30,    78,   121,   123,    78,    78,    78,    78,
     113,   154,    78,    78,    78,   140,    78,    78,    78,   133,
     138,     7,     5,    78,     7,    78,    97,    77,    77,   169,
      93,     5,    78,   154,   156,   156,   185,   188,   267,   171,
      49,   160,    78,     7,    96,   175,   160,    95,    95,   136,
     136,   136,   136,    78,   115,   121,   121,   154,   103,    78,
      95,   154,    43,   111,   112,   267,   266,   136,    78,    78,
      30,    95,   186,   189,   190,   267,    78,   160,   129,   253,
     267,    37,    41,   176,   177,   178,   179,   267,    78,    78,
     160,   154,   155,    93,    97,   178,   163,   160,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    98,    99,    99,    99,    99,    99,   100,   100,   101,
     102,   103,   103,   104,   104,   105,   105,   106,   106,   107,
     108,   108,   109,   109,   110,   110,   110,   111,   112,   112,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   119,   119,   119,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   125,
     125,   126,   127,   128,   128,   129,   129,   130,   130,   131,
     132,   132,   133,   133,   133,   133,   134,   135,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   137,   137,   137,
     137,   138,   138,   139,   139,   140,   140,   141,   141,   141,
     141,   142,   142,   142,   143,   143,   143,   144,   144,   144,
     144,   144,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   154,
     154,   155,   156,   157,   157,   157,   157,   158,   159,   160,
     160,   160,   160,   160,   160,   161,   162,   162,   163,   163,
     164,   165,   166,   167,   167,   168,   168,   169,   169,   170,
     171,   171,   171,   171,   171,   172,   172,   173,   173,   174,
     175,   176,   176,   177,   177,   178,   179,   179,   180,   180,
     180,   180,   181,   182,   183,   184,   184,   185,   185,   186,
     186,   187,   187,   188,   189,   190,   190,   191,   192,   192,
     192,   192,   193,   194,   195,   196,   197,   197,   198,   198,
     199,   199,   200,   200,   201,   202,   202,   203,   203,   204,
     204,   205,   206,   206,   207,   207,   208,   209,   210,   210,
     211,   211,   212,   212,   212,   213,   213,   214,   214,   215,
     215,   215,   215,   215,   216,   217,   218,   218,   219,   219,
     219,   220,   220,   221,   222,   222,   223,   223,   224,   224,
     224,   224,   224,   224,   225,   226,   227,   227,   228,   228,
     229,   229,   230,   230,   231,   232,   233,   233,   234,   235,
     236,   236,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   238,   239,   240,   240,   241,   241,
     242,   243,   243,   244,   244,   245,   246,   247,   247,   248,
     249,   250,   250,   251,   251,   252,   252,   252,   252,   252,
     253,   254,   254,   255,   255,   256,   257,   257,   258,   259,
     260,   260,   261,   261,   262,   263,   263,   264,   264,   265,
     265,   266,   267
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
       1,     1,     1,     1,     1,     1,     1,     5,     5,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     2,
       1,     2,     2,     1,     3,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     5,     7,     5,
       4,     1,     1,     1,     2,     2,     3,     2,     1,     1,
       1,     1,     5,     7,     9,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     8,     1,     1,
       1,     1,     2,     2,     3,     3,     1,     1,     1,     2,
       1,     1,     1,     1,     4,     1,     1,     1,     2,     2,
       3,     4,     1,     2,     1,     1,     5,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     6,     1,     1,     1,     2,     2,
       4,     1,     3,     4,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     4,     2,     6,     6,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     1,     3,     1,
       7,    10,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     1,     1,     5,     5,
       6,     1,     1,     1,     1,     6,     1,     1,     1,     2,
       4,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     6,     1,     1,     2,     3,
       1,     1,     1,     2,     1,     7,     7,     1,     1,     1,
       2,     1,     0
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
#line 278 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    CurTable->insertLiteral("bool", (yyvsp[0].NT)->place);
  }
#line 2115 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 282 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
    CurTable->insertLiteral("int", (yyval.NT)->place);
  }
#line 2125 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 287 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
    CurTable->insertLiteral("char", ((yyval.NT)->place));
  }
#line 2135 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 292 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
    CurTable->insertLiteral("string", ((yyval.NT)->place));
  }
#line 2145 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 297 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
  }
#line 2154 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 303 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="1";
  }
#line 2163 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 307 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="0";
  }
#line 2172 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 313 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2180 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 318 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2188 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 323 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2196 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 326 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2204 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 331 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2212 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 334 "src/sharpie.y" /* yacc.c:1646  */
    {
    // not used
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2221 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 340 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2229 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 343 "src/sharpie.y" /* yacc.c:1646  */
    {
    // Not used
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2238 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 349 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2246 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 352 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="bool";
    (yyval.NT)->width=1;
  }
#line 2256 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 359 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2264 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 364 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="int";
    (yyval.NT)->width=4;
  }
#line 2274 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 369 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="char";
    (yyval.NT)->width=1;
  }
#line 2284 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 377 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->type="string";
    (yyval.NT)->width=400;
  }
#line 2294 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 385 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->isarray=true;
    (yyval.NT)->elem=(yyvsp[-1].NT);
  }
#line 2304 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 400 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2312 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 405 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->arg_lst).pb((yyvsp[0].NT));
  }
#line 2321 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 409 "src/sharpie.y" /* yacc.c:1646  */
    {
    // TODO: Check usage
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->arg_lst).pb((yyvsp[0].NT));
  }
#line 2331 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 416 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2339 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 422 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2347 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 425 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2355 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 430 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2363 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 433 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2371 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 436 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2379 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 439 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2387 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 442 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2395 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 445 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2403 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 448 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2411 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 451 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2419 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 454 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2427 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 459 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 2435 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 470 "src/sharpie.y" /* yacc.c:1646  */
    {
      (yyval.NT)=new Attr();
      bool isQI=((yyvsp[-3].NT)->isQI);
      string FunName=((yyvsp[-3].NT)->place);
      string Objname, CurCSname;
      SymTable* DeclTbl;
      if(isQI){
	FunName=((yyvsp[-3].NT)->QI.Y);
	Objname = ((yyvsp[-3].NT)->QI.X);
	// TODO: check if object
	if(!(CurTable->lookup(Objname))){
	  cerr<<"Error Line "<<yylineno<<": "<<Objname<<" used without declared"<<endl;
	  exit(0);
	}
	DeclTbl=getDeclScope(Objname, CurTable);
	// TODO: check if this method is defined, parameter type
	CurCSname = (DeclTbl->Node)[Objname].X;
	DeclTbl=getDeclScope(CurCSname, CurTable);
	if((DeclTbl->prvt_lst)[CurCSname].find(FunName) != (DeclTbl->prvt_lst)[CurCSname].end()){
	  cerr<<"Error Line "<<yylineno<<": Function "<<FunName<<" is a private method!"<<endl;
	  exit(0);
	}
	if(((DeclTbl->Mtdmap)[CurCSname]).find(FunName) == ((DeclTbl->Mtdmap)[CurCSname]).end()){
	  cerr<<"Error Line "<<yylineno<<": Function "<<FunName<<" Not defined"<<endl;
	  exit(0);
	}
	/*cout<<"Class Name: "<<CurCSname<<" SIZE: "<<(DeclTbl->Smap)[CurCSname].size()<<endl;*/
	for(auto flds : (DeclTbl->Smap)[CurCSname]){
	  string typ_ = (flds.Y);
	  string smtg_glob = CurCSname+"."+(flds.X);
	  string smtg_ = (Objname)+"."+(flds.X);
	  string code_="=,"+smtg_glob+","+smtg_;
	  ((yyval.NT)->code).pb(code_);
	}
      }
      if(!isQI && !(CurTable->lookup(((yyvsp[-3].NT)->place)))){
	cerr<<"Error Line "<<yylineno<<": Function "<<((yyvsp[-3].NT)->place)<<" Not defined"<<endl;
	exit(0);
      }
      // Already looked up
      DeclTbl=getDeclScope(FunName,CurTable);
      if(isQI){
	DeclTbl=getDeclScope(CurCSname, CurTable);
      }
      int arg_cnt=(int)((yyvsp[-1].NT)->arg_lst).size();
      if(!isQI && (DeclTbl->Node)[FunName].Y != "function"){
	cerr<<"Error Line "<<yylineno<<": "<<((yyvsp[-3].NT)->place)<<" Ain't No function!"<<endl;
	exit(0);
      }
      if(!isQI && arg_cnt  != (DeclTbl->Args)[FunName].X){
	cerr<<"Error Line "<<yylineno<<": "<<((yyvsp[-3].NT)->place)<<" Number of arguments don't match"<<endl;
	exit(0);
      }
      if(isQI){
	int chk_arg_cnt=((((DeclTbl->Mtdmap)[CurCSname])[FunName]).Y).size();
	if(arg_cnt != chk_arg_cnt){
	  cerr<<"Error Line "<<yylineno<<": "<<FunName<<" Number of arguments don't match"<<endl;
	  exit(0);
	}
      }
      string code_;
      for(int i=0;i<arg_cnt;i++){
	Attr* CurArg=((yyvsp[-1].NT)->arg_lst)[i];
	Combine((yyval.NT)->code, (yyval.NT)->code, CurArg->code);
      }
      for(int i=0;i<arg_cnt;i++){
	Attr* CurArg=((yyvsp[-1].NT)->arg_lst)[i];
	code_="param,"+(CurArg->place)+","+to_string(i+1);
	((yyval.NT)->code).pb(code_);
	// check declartion of initializer
	if(!(CurTable->lookup(change_string(CurArg->place)))){
	  cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurArg->place)<<" used without declaration."<<endl;
	  exit(0);
	}
	// check type compatibility
	string typ1;
	string typ2=getTyp(change_string(CurArg->place));
	if(!isQI){
	  typ1=((DeclTbl->Args)[FunName].Y)[i];
	}else{
	  typ1=((((DeclTbl->Mtdmap)[CurCSname])[FunName]).Y)[i];
	}
	if(typ1 != typ2){
	  cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurArg->place)<<" has type "<<typ2<<". Expected type "<<typ1<<endl;
	  exit(0);
	}

      }

      string RetType="void";
      if(!isQI){
	RetType=(DeclTbl->Node)[FunName].X;
      }else{
	DeclTbl=getDeclScope(CurCSname, CurTable);
	RetType=(DeclTbl->Mtdmap)[CurCSname][FunName].X;
	/*cout<<"RTE : "<<RetType<<endl;*/
      }
      string tp="NULL";
      if(RetType != "void"){
	tp=CurTable->getTemp(RetType);
	((yyval.NT)->place)=tp;
      }
      code_="call,"+FunName+","+to_string(arg_cnt)+","+tp;
      ((yyval.NT)->code).pb(code_);
      if(isQI){
	DeclTbl=getDeclScope(CurCSname, CurTable);
	for(auto flds : (DeclTbl->Smap)[CurCSname]){
	  string typ_ = (flds.Y);
	  string smtg_glob = CurCSname+"."+(flds.X);
	  string smtg_ = (Objname)+"."+(flds.X);
	  string code_="=,"+smtg_+","+smtg_glob;
	  ((yyval.NT)->code).pb(code_);
	}
      }
  }
#line 2555 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 587 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2563 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 590 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2571 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 596 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    if(!(CurTable->lookup(change_string((yyvsp[-3].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<" Array "<<((yyvsp[-3].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string((yyvsp[-3].NT)->place), CurTable);
    if((DeclTbl->Node)[change_string((yyvsp[-3].NT)->place)].Y != "array"){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[-3].NT)->place)<<" Ain't no array!"<<endl;
      exit(0);
    }
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-1].NT)->code);
    string tp1=CurTable->getTemp("int");
    string tp2=CurTable->getTemp("int");
    string required_type=(DeclTbl->Node)[change_string((yyvsp[-3].NT)->place)].X;
    string tp3=CurTable->getTemp(required_type);
    string wid="1";
    if(required_type == "int")wid="4";
    string code_="=,"+tp1+","+((yyvsp[-1].NT)->place);
    ((yyval.NT)->code).pb(code_);
    code_="*,"+tp2+","+tp1+","+wid;
    ((yyval.NT)->code).pb(code_);
    // member, var, array, offset :: var=array[offset]
    code_="member,"+tp3+","+((yyvsp[-3].NT)->place)+","+tp2;
    ((yyval.NT)->code).pb(code_);
    ((yyval.NT)->place)=tp3;
    ((yyval.NT)->array_element) = true;
    ((yyval.NT)->array_name)=((yyvsp[-3].NT)->place);
    ((yyval.NT)->array_off)=tp2;
  }
#line 2606 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 628 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2614 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 631 "src/sharpie.y" /* yacc.c:1646  */
    {
    // not used
    (yyval.NT)=(yyvsp[-2].NT);
  }
#line 2623 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 644 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2631 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 649 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-3].NT);
  }
#line 2639 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 658 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2647 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 661 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2655 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 673 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2663 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 676 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2671 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 681 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2679 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 684 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    string code_="!,"+((yyvsp[0].NT)->place);
    ((yyval.NT)->code).pb(code_);
    if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
#line 2693 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 693 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    string code_="~,"+((yyvsp[0].NT)->place);
    ((yyval.NT)->code).pb(code_);
    if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
#line 2707 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 705 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    string code_="+,"+((yyvsp[0].NT)->place)+",1,"+((yyvsp[0].NT)->place);
    ((yyval.NT)->code).pb(code_);
    if((yyvsp[0].NT)->array_element == true){
      // update the array
      code_="update,"+((yyvsp[0].NT)->place)+","+((yyvsp[0].NT)->array_name)+","+((yyvsp[0].NT)->array_off);
      ((yyval.NT)->code).pb(code_);
    }
    if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
#line 2726 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 721 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    string code_="-,"+((yyvsp[0].NT)->place)+","+((yyvsp[0].NT)->place)+",1";
    ((yyval.NT)->code).pb(code_);
     if((yyvsp[0].NT)->array_element == true){
      // update the array
      code_="update,"+((yyvsp[0].NT)->place)+","+((yyvsp[0].NT)->array_name)+","+((yyvsp[0].NT)->array_off);
      ((yyval.NT)->code).pb(code_);
    }
    if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
#line 2745 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 737 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2753 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 740 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2761 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 743 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    string tp=CurTable->getTemp("int");
    string code_="-,"+tp+",0,"+((yyvsp[0].NT)->place);
    ((yyval.NT)->code).pb(code_);
    ((yyval.NT)->place)=tp;
    if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
#line 2777 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 755 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2785 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 758 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2793 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 784 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2801 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 787 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"YO: "<<($1->place)<<endl;*/
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"*");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2811 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 792 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"/");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2820 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 796 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"%");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2829 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 802 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2837 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 805 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"+");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
    /*
     *for(int i=0;i<(int)(($$->code).size());i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"----"<<endl;
     */
  }
#line 2852 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 815 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"-");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2861 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 821 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2869 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 824 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<<");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2878 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 828 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">>");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2887 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 834 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 2895 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 837 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2904 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 841 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2913 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 845 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"<=","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2922 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 849 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),">=","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2931 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 855 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2939 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 858 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"==","bool");
    // can compare char/int/bool
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"null");
  }
#line 2949 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 863 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"!=","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"null");
  }
#line 2958 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 869 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2966 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 872 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"&");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2975 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 878 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 2983 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 881 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"^");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 2992 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 887 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3000 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 890 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"|");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"int");
  }
#line 3009 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 896 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3017 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 899 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"&&","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"bool");
  }
#line 3026 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 905 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3034 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 908 "src/sharpie.y" /* yacc.c:1646  */
    {
    translate((yyval.NT),(yyvsp[-2].NT),(yyvsp[0].NT),"||","bool");
    CheckTyp((yyvsp[-2].NT),(yyvsp[0].NT),"bool");
  }
#line 3043 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 914 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3051 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 917 "src/sharpie.y" /* yacc.c:1646  */
    {
    // TODO
  }
#line 3059 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 922 "src/sharpie.y" /* yacc.c:1646  */
    {
  /*cout<<"In assignment"<<endl;*/
  // TODO: handle others later
  (yyval.NT)=new Attr();
  // Left side shouldn't be a literal
  if(CurTable->lookup(change_string((yyvsp[-2].NT)->place)) && CurTable->lookup(change_string((yyvsp[0].NT)->place))){
    string typ1;
    string cat1;
    string a1;
    if(((yyvsp[-2].NT)->array_element) == true){
      typ1=getTyp(((yyvsp[-2].NT)->array_name));
      cat1=getCat(((yyvsp[-2].NT)->array_name));
      a1=((yyvsp[-2].NT)->array_name);
      // update, input, array, offset
      (yyval.NT)->place=(yyvsp[0].NT)->place;
      int lcode=(int)((yyvsp[-2].NT)->code).size();
      string code_="update,"+((yyvsp[0].NT)->place)+","+((yyvsp[-2].NT)->array_name)+","+((yyvsp[-2].NT)->array_off);
      ((yyvsp[-2].NT)->code)[lcode-1]=code_;
      Combine((yyval.NT)->code, (yyvsp[0].NT)->code, (yyvsp[-2].NT)->code);
    }else{
      typ1=getTyp(change_string((yyvsp[-2].NT)->place));
      cat1=getCat(change_string((yyvsp[-2].NT)->place));
      a1=((yyvsp[-2].NT)->place);
      (yyval.NT)->place = (yyvsp[-2].NT)->place;
      Combine((yyval.NT)->code, (yyvsp[0].NT)->code, (yyvsp[-2].NT)->code);
      string code_= getTAC(2,"=",(yyvsp[-2].NT)->place,(yyvsp[0].NT)->place);
      ((yyval.NT)->code).pb(code_);
    }
    string typ2=getTyp(change_string((yyvsp[0].NT)->place));
    if(typ1 != typ2){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbols "<<(a1)<<" and "<<((yyvsp[0].NT)->place)<<" are of type "<<typ1<<" and "<<typ2<<". Assignment not possible."<<endl;
	exit(0);
    }
    if(cat1 == "literal"){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<((yyvsp[-2].NT)->place)<<" is a literal. Can't be assigned!"<<endl;
	exit(0);
    }

  }else if(!(CurTable->lookup(change_string((yyvsp[-2].NT)->place)))){
    cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<((yyvsp[-2].NT)->place)<<" used without declaration."<<endl;
    exit(0);
  }else if(!(CurTable->lookup(change_string((yyvsp[0].NT)->place)))){
    cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<((yyvsp[0].NT)->place)<<" used without declaration."<<endl;
    exit(0);
  }

}
#line 3111 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 984 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3119 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 987 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3127 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 992 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT); // check if variable is altered
  }
#line 3135 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 997 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3143 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1002 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement ->declaration_statement asda"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3152 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1006 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement ->embedded_statement asda"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
/*
 *    cout<<"st......"<<endl;
 *    for(int i=0;i<($1->code).size();i++){
 *      cout<<($1->code)[i]<<endl;
 *    }
 *    cout<<"ed......"<<endl;
 *
 */
  }
#line 3169 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1018 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3177 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1021 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3185 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1026 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    if(!(CurTable->lookup(change_string((yyvsp[-2].NT)->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<((yyvsp[-2].NT)->place)<<" is not declared"<<endl;
	exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string((yyvsp[-2].NT)->place), CurTable);
    string typ=(DeclTbl->Node)[change_string((yyvsp[-2].NT)->place)].X;
    // print, var, type
    string code_="print,"+((yyvsp[-2].NT)->place)+","+typ;
    ((yyval.NT)->code).pb(code_);
  }
#line 3203 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1041 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    if(!(CurTable->lookup(change_string((yyvsp[-2].NT)->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<((yyvsp[-2].NT)->place)<<" is not declared"<<endl;
	exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string((yyvsp[-2].NT)->place), CurTable);
    string typ=(DeclTbl->Node)[change_string((yyvsp[-2].NT)->place)].X;
    // read, var, type
    string code_="read,"+((yyvsp[-2].NT)->place)+","+typ;
    ((yyval.NT)->code).pb(code_);
  }
#line 3221 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1056 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3229 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1059 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3237 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1062 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"embedded_statement->expression_statement"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3246 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1066 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3254 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1069 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3262 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1072 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3270 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1078 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = (yyvsp[-1].NT);
    /*cout<<"dgdfgg"<<endl;*/
    EndScope();
    /*cout<<"Enddgdfgg"<<endl;*/
  }
#line 3281 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1086 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3289 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1089 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list_opt"<<endl;*/
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 3298 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1096 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list to statement"<<endl;*/
    (yyval.NT) = (yyvsp[0].NT);
  }
#line 3307 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1100 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"statement_list to statement_list statement "<<endl;*/
    (yyval.NT)=(yyvsp[-1].NT);
	Combine((yyval.NT)->code, (yyvsp[-1].NT)->code, (yyvsp[0].NT)->code);
    /*cout<<"statement_list to statement 22222"<<endl;*/
  }
#line 3318 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1108 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT) = new Attr();
    /*cout<<"hello there"<<endl;*/
    //TODO
  }
#line 3328 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1115 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 3336 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1120 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"local_variable_declaration asdad"<<endl;*/
    // Checking Re-declaration
    for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
      Attr* CurVar=((yyvsp[0].NT)->var_dec)[i];
      if((CurTable->lookup_in_this(change_string(CurVar->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<(CurVar->place)<<" is already declared in this scope."<<endl;
	exit(0);
      }
      /*
       *if((CurTable->lookup(CurVar->place))){
       *  // declared in outer scope
       *  (CurTable->shadow).insert(CurVar->place);
       *  (CurVar->place)=(CurVar->place)+"_"+to_string(NumScopes);
       *}
       */
    }
    (yyval.NT)=new Attr();
    bool lookuptyp=(CurTable->lookup((yyvsp[-1].NT)->place));
    bool CS=false;
    SymTable* DeclTbl;
    if(lookuptyp){
      DeclTbl = getDeclScope((yyvsp[-1].NT)->place, CurTable);
      string smtg= (DeclTbl->Node)[((yyvsp[-1].NT)->place)].Y;
      if(smtg == "struct" || smtg == "class"){
	CS=true;
      }
    }
    if(CS){
      for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
	Attr* CurVar = ((yyvsp[0].NT)->var_dec)[i];
	// for sanity
	(CurVar->place)=change_string((CurVar->place));
	//           struct/class name, object name
	(CurTable->insertObj((yyvsp[-1].NT)->place, (CurVar->place)));
	for(auto flds : (DeclTbl->Smap)[((yyvsp[-1].NT)->place)]){
	  if((DeclTbl->prvt_lst)[((yyvsp[-1].NT)->place)].find(flds.X) != (DeclTbl->prvt_lst)[((yyvsp[-1].NT)->place)].end()){
	    continue;
	  }
	  string smtg = (CurVar->place)+"."+(flds.X);
	  string typ_ = (flds.Y);
	  (CurTable->insertVariable(typ_, smtg));
	  string code_=(typ_)+","+smtg;
	  ((yyval.NT)->code).pb(code_);
	}
      }
    }else if((yyvsp[-1].NT)->isarray == false){
	string typ1=((yyvsp[-1].NT)->type);
	for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
	  Attr * CurVar = ((yyvsp[0].NT)->var_dec)[i];
	  // TODO:insert CurVar->place into table-> DONE!
	  CurVar->place=change_string((CurVar->place));
	  CurTable->insertVariable(((yyvsp[-1].NT)->type), CurVar->place);
	  CurVar->place+="_"+to_string((CurTable->table_id));
	  string code_=((yyvsp[-1].NT)->type)+","+(CurVar->place);
	  ((yyval.NT)->code).pb(code_);
	  if(CurVar->init != NULL){

	    Attr * CurVarInit=(CurVar->init);
	    Combine((yyval.NT)->code,(yyval.NT)->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ((yyval.NT)->code).pb(code_);

	    // check declartion of initializer
	    if(!(CurTable->lookup(change_string(CurVarInit->place)))){
	      cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInit->place)<<" used without declaration."<<endl;
	      exit(0);
	    }
	    // check type compatibility
	    string typ2=getTyp(change_string(CurVarInit->place));
	    if(typ1 != typ2){
	      cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInit->place)<<" has type "<<typ2<<". Expected type "<<typ1<<endl;
	      exit(0);
	    }

	  }
	}
     }else{
       for(int i=0;i<(int)((yyvsp[0].NT)->var_dec).size();i++){
	  Attr * CurVar = ((yyvsp[0].NT)->var_dec)[i];
	  if(CurVar->init != NULL){
	    string typ1=((yyvsp[-1].NT)->elem)->type;
	    Attr * CurVarInit=(CurVar->init);
	    int ArrayLength=(CurVarInit->init_list).size();
	    CurTable->insertArray(((yyvsp[-1].NT)->elem)->type, CurVar->place);
	    string code_="array,"+((yyvsp[-1].NT)->elem)->type+","+to_string(ArrayLength)+","+CurVar->place;
	    ((yyval.NT)->code).pb(code_);
	    for(int j=0;j<(int)(CurVarInit->init_list).size();j++){
	      Attr * CurVarInitElem = (CurVarInit->init_list)[j];
	      int ElemWidth=((yyvsp[-1].NT)->elem)->width;
	      // TODO:update width for this array struct=len*Elemwidth
	      code_="update,"+(CurVarInitElem->place)+","+(CurVar->place)+","+to_string(ElemWidth*j);
	      Combine((yyval.NT)->code,(yyval.NT)->code,CurVarInitElem->code);
	      ((yyval.NT)->code).pb(code_);

	      // check declartion of initializer
	      if(!(CurTable->lookup(change_string(CurVarInitElem->place)))){
		cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInitElem->place)<<" used without declaration."<<endl;
		exit(0);
	      }

	      // check type compatibility
	      string typ2=getTyp(change_string(CurVarInitElem->place));
	      if(typ1 != typ2){
		cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInitElem->place)<<" has type "<<typ2<<". Expected type "<<typ1<<endl;
		exit(0);
	      }

	    }
	  }else{
	    // default length 100 size array
	    CurTable->insertArray(((yyvsp[-1].NT)->elem)->type, CurVar->place);
	    string code_="array,"+((yyvsp[-1].NT)->elem)->type+",100,"+CurVar->place;
	    ((yyval.NT)->code).pb(code_);
	  }
	}
    }
    /*
     *for(auto it : ($$->code))
     *  cout<<it<<endl;
     *cout<<"******"<<endl;
     */
  }
#line 3464 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1245 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->var_dec).pb((yyvsp[0].NT));
  }
#line 3473 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1249 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->var_dec).pb((yyvsp[0].NT));
  }
#line 3482 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1255 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[0].sval));
    /*
     *if(CurTable->look_in_shadow($$->place)){
     *  ($$->place)=($$->place)+"_"+to_string(NumScopes);
     *}
     */
    if(CurTable->lookup(change_string((yyval.NT)->place))){
      SymTable* DeclTbl= getDeclScope(change_string((yyval.NT)->place),CurTable);
      ((yyval.NT)->place)+="_"+to_string(DeclTbl->table_id);
    }
    (yyval.NT)->init = NULL;
    (yyval.NT)->line=yylineno;
  }
#line 3502 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1270 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[-2].sval));
/*
 *    if(CurTable->look_in_shadow($$->place)){
 *      ($$->place)=($$->place)+"_"+to_string(NumScopes);
 *    }
 *
 */
    if(CurTable->lookup(change_string((yyval.NT)->place))){
      SymTable* DeclTbl= getDeclScope(change_string((yyval.NT)->place),CurTable);
      ((yyval.NT)->place)+="_"+to_string(DeclTbl->table_id);
    }
    (yyval.NT)->init = (yyvsp[0].NT);
    (yyval.NT)->line=yylineno;
  }
#line 3523 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1288 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3531 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1291 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3539 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1296 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"expression_statement -> statement_expression"<<endl;*/
    (yyval.NT)=(yyvsp[-1].NT);
   }
#line 3548 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1302 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"invocation_expression"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3557 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1306 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3565 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1309 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3573 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1312 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3581 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1315 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3589 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1320 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3597 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1323 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3605 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1328 "src/sharpie.y" /* yacc.c:1646  */
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
#line 3625 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1343 "src/sharpie.y" /* yacc.c:1646  */
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
    /*
     *cout<<"%%%%%%%%%%%"<<endl;
     *for(int i=0;i<($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"%%%%%%%%%%%"<<endl;
     */
  }
#line 3653 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1368 "src/sharpie.y" /* yacc.c:1646  */
    {
    // refer slides for naming convention
    /*cout<<"----$$$$$$$$$$"<<endl;*/
    string ltest=getLabel();
    string lnext=getLabel();
    (yyval.NT)=new Attr();
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    string code_="goto,"+ltest;
    ((yyval.NT)->code).pb(code_);
    for(int i=0;i<(int)((yyvsp[0].NT)->sw_sec).size();i++){
      Attr * sec=((yyvsp[0].NT)->sw_sec)[i];
      string lsec=getLabel();
      tmpLbl[i]=lsec;
      code_="label,"+lsec;
      ((yyval.NT)->code).pb(code_);
      Combine((yyval.NT)->code, (yyval.NT)->code, sec->code);
    }
    code_="goto,"+lnext;
    int si=(int)((yyval.NT)->code).size();
    if(((yyval.NT)->code)[si-1] != "goto,-1")
      ((yyval.NT)->code).pb(code_);
    code_="label,"+ltest;
    ((yyval.NT)->code).pb(code_);
    for(int i=0;i<(int)((yyvsp[0].NT)->sw_sec).size();i++){
      Attr * sec=((yyvsp[0].NT)->sw_sec)[i];
      if((sec->sw_lbl)->sw_default == true){
	code_="goto,"+tmpLbl[i];
	((yyval.NT)->code).pb(code_);
      }else{
	code_="ifgoto,==,"+((sec->sw_lbl)->place)+","+((yyvsp[-2].NT)->place)+","+tmpLbl[i];
	((yyval.NT)->code).pb(code_);
      }
    }
    code_="label,"+lnext;
    ((yyval.NT)->code).pb(code_);
    for(int i=0;i<(int)((yyval.NT)->code).size();i++){
      // change break appropriately
      if(((yyval.NT)->code)[i] == "goto,-1"){
	((yyval.NT)->code)[i]="goto,"+lnext;
      }
    }

    /*
     *cout<<"st$$$$$$$$$$"<<endl;
     *for(int i=0;i<(int)($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"ed$$$$$$$$$$"<<endl;
     */
  }
#line 3708 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1420 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
    EndScope();
  }
#line 3717 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1426 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3725 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1429 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3733 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1434 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->sw_sec).pb((yyvsp[0].NT));
  }
#line 3742 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1438 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
    ((yyval.NT)->sw_sec).pb((yyvsp[0].NT));
  }
#line 3751 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1444 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->sw_lbl)=(yyvsp[-1].NT);
  }
#line 3760 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1454 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 3768 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1457 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->sw_default)=true;
  }
#line 3777 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1463 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3785 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1466 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3793 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1469 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3801 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1472 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3809 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1477 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    string lbegin=getLabel();
    string lnext=getLabel();
    string ltrue=getLabel();
    string code_="label,"+lbegin;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    code_="ifgoto,==,1,"+((yyvsp[-2].NT)->place)+","+ltrue;
    ((yyval.NT)->code).pb(code_);
    code_="goto,"+lnext;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+ltrue;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
    code_="goto,"+lbegin;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+lnext;
    ((yyval.NT)->code).pb(code_);
    for(int i=0;i<(int)((yyval.NT)->code).size();i++){
      if(((yyval.NT)->code)[i] == "goto,-1"){
	// change break appropriately
	((yyval.NT)->code)[i]="goto,"+lnext;
      }else if(((yyval.NT)->code)[i] == "goto,-2"){
	// change continue appropriately
	((yyval.NT)->code)[i]="goto,"+lbegin;
      }
    }

    /*
     *cout<<"-----^^^^^^^^^"<<endl;
     *for(int i=0;i<(int)($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"^^^^^^^^^^^"<<endl;
     */
  }
#line 3851 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1519 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    string lbegin=getLabel();
    string lnext=getLabel();
    string ltrue=getLabel();
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-6].NT)->code);
    string code_="label,"+lbegin;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-4].NT)->code);
    code_="ifgoto,==,1,"+((yyvsp[-4].NT)->place)+","+ltrue;
    ((yyval.NT)->code).pb(code_);
    code_="goto,"+lnext;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+ltrue;
    ((yyval.NT)->code).pb(code_);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[-2].NT)->code);
    code_="goto,"+lbegin;
    ((yyval.NT)->code).pb(code_);
    code_="label,"+lnext;
    ((yyval.NT)->code).pb(code_);
    for(int i=0;i<(int)((yyval.NT)->code).size();i++){
      if(((yyval.NT)->code)[i] == "goto,-1"){
	// change break appropriately
	((yyval.NT)->code)[i]="goto,"+lnext;
      }else if(((yyval.NT)->code)[i] == "goto,-2"){
	// change continue appropriately
	((yyval.NT)->code)[i]="goto,"+lbegin;
      }
    }
    /*
     *cout<<"st/////////"<<endl;
     *for(int i=0;i<(int)($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"ed/////////"<<endl;
     */
  }
#line 3894 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1559 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3902 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1562 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3910 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1567 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3918 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1570 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3926 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1575 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3934 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1578 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3942 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1583 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3950 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1586 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3958 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1591 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3966 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1596 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3974 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1601 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3982 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1604 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
  }
#line 3991 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1613 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 3999 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1616 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4007 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1620 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4015 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1625 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    string code_="goto,-1";
    ((yyval.NT)->code).pb(code_);
  }
#line 4025 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1632 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    string code_="goto,-2";
    ((yyval.NT)->code).pb(code_);
  }
#line 4035 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1642 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
    string code_="return,"+((yyvsp[-1].NT)->place);
    ((yyval.NT)->code).pb(code_);
  }
#line 4045 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1649 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4053 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1652 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4061 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1658 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4069 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1661 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    /*cout<<"------CODE-----"<<endl;*/
    cout<<"0,call,Main,0,NULL"<<endl;
    cout<<"1,exit"<<endl;
    for(int i=0;i<(int)((yyval.NT)->code).size();i++){
      cout<<(i+2)<<","<<((yyval.NT)->code)[i]<<endl;
    }
    /*cout<<"------END--CODE-----"<<endl;*/
  }
#line 4084 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1673 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4092 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1676 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4100 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1681 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4108 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1684 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4116 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1689 "src/sharpie.y" /* yacc.c:1646  */
    {
  
  }
#line 4124 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1694 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4132 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1697 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
  }
#line 4140 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1702 "src/sharpie.y" /* yacc.c:1646  */
    {
	(yyval.NT) = new Attr();
	(yyval.NT)->place = string((yyvsp[0].sval));
/*
 *        if(CurTable->look_in_shadow($$->place)){
 *          ($$->place)=($$->place)+"_"+to_string(NumScopes);
 *        }
 *
 */
    if(CurTable->lookup(change_string((yyval.NT)->place))){
      SymTable* DeclTbl= getDeclScope(change_string((yyval.NT)->place),CurTable);
      string smtg = (CurTable->CSname) + "." + (yyval.NT)->place;
      if(CS_FLAG && (CurTable->lookup(smtg))){
	(yyval.NT)->place = smtg;
      }
      else if((DeclTbl->Node)[change_string((yyval.NT)->place)].Y == "variable")
	((yyval.NT)->place)+="_"+to_string(DeclTbl->table_id);
    }

  }
#line 4165 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1722 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = ((yyvsp[-1].NT)->place)+"."+string((yyvsp[0].sval));
    ((yyval.NT)->QI)=mp(((yyvsp[-1].NT)->place), string((yyvsp[0].sval)));
    ((yyval.NT)->isQI)=true;
  }
#line 4176 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1730 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[-1].sval));
  }
#line 4185 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1734 "src/sharpie.y" /* yacc.c:1646  */
    {
    // not used
    (yyval.NT)=new Attr();
    (yyval.NT)->place = string((yyvsp[-1].sval));
  }
#line 4195 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1762 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4203 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1765 "src/sharpie.y" /* yacc.c:1646  */
    {
    // not here
    (yyval.NT)=(yyvsp[-1].NT);
    /*cerr<<"Not expected here"<<endl;*/
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
  }
#line 4214 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1773 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4222 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1776 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4230 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1781 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4238 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1784 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4246 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1787 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4254 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1793 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4262 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1796 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4270 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1801 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4278 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1804 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 4286 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1809 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="abstract";
  }
#line 4295 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1813 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="new";
  }
#line 4304 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1817 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="private";
  }
#line 4313 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1821 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="protected";
  }
#line 4322 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1825 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)="public";
  }
#line 4331 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1831 "src/sharpie.y" /* yacc.c:1646  */
    {
    // CLASS IDENTIFIER class_body
    /*$$=$5;*/
    //  field_name, type
    ((yyval.NT)->code)=((yyvsp[-1].NT)->code);
    set<string> prvt_fld_mtd;
    map<string,string> tmap;
    /*cout<<"SI: "<<(int)($5->fld_lst).size()<<endl;*/
    for(int i=0;i<(int)((yyvsp[-1].NT)->fld_lst).size();i++){
      Attr* CurFld = ((yyvsp[-1].NT)->fld_lst)[i];
      string typ=(CurFld->fld).X;
      /*cout<<"GFD "<<i<<endl;*/
      for(int j=0;j<(int)((CurFld->fld).Y).size();j++){
	Attr* CurFldElem = ((CurFld->fld).Y)[j];
	// without "_"
	tmap[(CurFldElem->place)]=typ;
	if(CurFld->acc_mod == "private"){
	  prvt_fld_mtd.insert((CurFldElem->place));
	}
      }
    }
    // for methods
    // method_name , <ret_typ, par_typs>
    map<string,pair<string, vector<string> > > tmap1;
    /*cout<<"SI: "<<(int)($5->fld_lst).size()<<endl;*/
    for(int i=0;i<(int)((yyvsp[-1].NT)->mtd_lst).size();i++){
      Attr* CurMtd = ((yyvsp[-1].NT)->mtd_lst)[i];
      string typ=(CurMtd->fld).X;
      pair<string, vector<string> > mtd_arg;
      mtd_arg.X = (CurMtd->ret_typ);
      mtd_arg.Y = (CurMtd->par_types);
      tmap1[(CurMtd->place)]=mtd_arg;
      if(CurMtd->acc_mod == "private"){
	prvt_fld_mtd.insert((CurMtd->place));
      }
      /*cout<<"METHOD: "<<(CurMtd->place)<<" RetType : "<<(CurMtd->ret_typ)<<endl;*/
    }
    (CurTable->insertClass((yyvsp[-3].NT)->place, tmap, tmap1, prvt_fld_mtd));
  }
#line 4375 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1872 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
    CS_FLAG=true;
    CS_Name=string((yyvsp[0].sval));
  }
#line 4386 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1893 "src/sharpie.y" /* yacc.c:1646  */
    {
     (yyval.NT)=(yyvsp[-1].NT);
     CS_FLAG=false;
     EndScope();
  }
#line 4396 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1900 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4404 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1903 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4412 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1908 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    if(((yyvsp[0].NT)->is_field_decl)){
      ((yyval.NT)->fld_lst).pb((yyvsp[0].NT));
    }
    if(((yyvsp[0].NT)->is_method_decl)){
      ((yyval.NT)->mtd_lst).pb((yyvsp[0].NT));
    }
  }
#line 4426 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1917 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
    if(((yyvsp[0].NT)->is_field_decl)){
      ((yyval.NT)->fld_lst).pb((yyvsp[0].NT));
    }
    if(((yyvsp[0].NT)->is_method_decl)){
      ((yyval.NT)->mtd_lst).pb((yyvsp[0].NT));
    }
    Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
  }
#line 4441 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1929 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->is_field_decl)=true;
  }
#line 4450 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1933 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->is_method_decl)=true;
  }
#line 4459 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1937 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4467 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1940 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4475 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1943 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4483 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1946 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4491 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1951 "src/sharpie.y" /* yacc.c:1646  */
    {
    // Checking Re-declaration
    for(int i=0;i<(int)((yyvsp[-1].NT)->var_dec).size();i++){
      Attr* CurVar=((yyvsp[-1].NT)->var_dec)[i];
      if((CurTable->lookup_in_this(change_string(CurVar->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<(CurVar->place)<<" is already declared in this scope."<<endl;
	exit(0);
      }
      /*
       *if((CurTable->lookup(CurVar->place))){
       *  // declared in outer scope
       *  (CurTable->shadow).insert(CurVar->place);
       *  (CurVar->place)=(CurVar->place)+"_"+to_string(NumScopes);
       *}
       */
    }
    (yyval.NT)=new Attr();
    (yyval.NT)->fld=mp((yyvsp[-2].NT)->type, ((yyvsp[-1].NT)->var_dec));
    ((yyval.NT)->acc_mod)=((yyvsp[-3].NT)->place);
    /*cout<<"ACCESS: "<<($1->place)<<endl;*/
    if((yyvsp[-2].NT)->isarray == false){
	string typ1=((yyvsp[-2].NT)->type);
	for(int i=0;i<(int)((yyvsp[-1].NT)->var_dec).size();i++){
	  Attr * CurVar = ((yyvsp[-1].NT)->var_dec)[i];
	  // TODO:insert CurVar->place into table-> DONE!
	  CurVar->place=change_string((CurVar->place));
	
	  CurTable->insertVariable(((yyvsp[-2].NT)->type), CurVar->place);
	  CurTable->insertField(((yyvsp[-2].NT)->type), (CurTable->CSname)+"."+(CurVar->place));
	  /*CurVar->place+="_"+to_string((CurTable->table_id));*/

	  string code_=((yyvsp[-2].NT)->type)+","+(CurTable->CSname) + "." + (CurVar->place);
	  ((yyval.NT)->code).pb(code_);
	  if(CurVar->init != NULL){

	    Attr * CurVarInit=(CurVar->init);
	    Combine((yyval.NT)->code,(yyval.NT)->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ((yyval.NT)->code).pb(code_);

	    // check declartion of initializer
	    if(!(CurTable->lookup(change_string(CurVarInit->place)))){
	      cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInit->place)<<" used without declaration."<<endl;
	      exit(0);
	    }
	    // check type compatibility
	    string typ2=getTyp(change_string(CurVarInit->place));
	    if(typ1 != typ2){
	      cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurVarInit->place)<<" has type "<<typ2<<". Expected type "<<typ1<<endl;
	      exit(0);
	    }

	  }
	}
     }

  }
#line 4553 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2010 "src/sharpie.y" /* yacc.c:1646  */
    {
/* 	// updated
 *      $$=new Attr();
 *      string code_="function,"+($1->place);
 *      ($$->code).pb(code_);
 *      Combine($$->code, $$->code, $2->code);
 *
 */
      string ret_typ=((yyvsp[-1].NT)->ret_typ);
      string method_name=((yyvsp[-1].NT)->place);
      (yyval.NT)=new Attr();
      ((yyval.NT)->place)=method_name;
      ((yyval.NT)->ret_typ)=ret_typ;
      ((yyval.NT)->par_types)=((yyvsp[-1].NT)->par_types);
      ((yyval.NT)->acc_mod)=((yyvsp[-1].NT)->acc_mod);
      string code_="function,"+method_name;
      ((yyval.NT)->code).pb(code_);
      int par_cnt=(int)((yyvsp[-1].NT)->par_lst).size();
      int off=8;
      for(int i=par_cnt-1;i>=0;i--){
	// pop, var, offset
	code_="pop,"+((((yyvsp[-1].NT)->par_lst)[i])->place)+","+to_string(off);
	off+=4;
	((yyval.NT)->code).pb(code_);
      }
      Combine((yyval.NT)->code, (yyval.NT)->code, (yyvsp[0].NT)->code);
      if((yyvsp[-1].NT)->ret_typ == "void"){
	code_="return,NULL";
	((yyval.NT)->code).pb(code_);
      }else{
	bool chk_ret=false;
	for(int i=0;i<((yyval.NT)->code).size();i++){
	  code_=((yyval.NT)->code)[i];
	  if(code_.substr(0,6) == "return"){
	    chk_ret=true;
	  }
	}
	if(!chk_ret){
	  cerr<<"ERROR: Line: "<<(yylineno)<<" No return statement found!"<<endl;
	  exit(0);
	}
      }
  }
#line 4601 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2055 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->code)=((yyvsp[-1].NT)->code);
    ((yyval.NT)->par_lst)=((yyvsp[-1].NT)->par_lst);
    ((yyval.NT)->place)=((yyvsp[-3].NT)->place);
    ((yyval.NT)->ret_typ)=((yyvsp[-4].NT)->type);
    ((yyval.NT)->acc_mod)=((yyvsp[-5].NT)->place);
    /*
     *for(int i=0;i<(int)($$->par_lst).size();i++){
     *  cout<<(($$->par_lst)[i]->place)<<endl;
     *}
     *cout<<"++++"<<endl;
     */
    int par_cnt=(int)((yyvsp[-1].NT)->par_lst).size();
    vector<string> par_typs;
    // delaying variable insertion in scope
    FLAG=true;
    for(int i=0;i<par_cnt;i++){
      string typ=(((yyvsp[-1].NT)->par_lst)[i])->type;
      string plc=(((yyvsp[-1].NT)->par_lst)[i])->place;
      (((yyvsp[-1].NT)->par_lst)[i])->place+="_"+to_string(NumScopes);
      par_typs.pb(typ);
      par_var.pb(mp(typ, plc));
    }
    CurTable->insertFunc((yyval.NT)->place, (yyval.NT)->ret_typ, par_typs, par_cnt);
    ((yyval.NT)->par_types)=par_typs;
    /*cout<<"ID: "<<($$->place)<<" PAR_SIZE: "<<(par_typs).size()<<endl;*/
  }
#line 4634 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2083 "src/sharpie.y" /* yacc.c:1646  */
    {
     (yyval.NT)=new Attr();
    ((yyval.NT)->code)=((yyvsp[-1].NT)->code);
    ((yyval.NT)->par_lst)=((yyvsp[-1].NT)->par_lst);
    ((yyval.NT)->place)=((yyvsp[-3].NT)->place);
    ((yyval.NT)->ret_typ)="void";
    ((yyval.NT)->acc_mod)=((yyvsp[-5].NT)->place);
    /*
     *for(int i=0;i<(int)($$->par_lst).size();i++){
     *  cout<<(($$->par_lst)[i]->place)<<endl;
     *}
     *cout<<"++++"<<endl;
     */
    int par_cnt=(int)((yyvsp[-1].NT)->par_lst).size();
    vector<string> par_typs;
    // delaying variable insertion in scope
    FLAG=true;
    for(int i=0;i<par_cnt;i++){
      string typ=(((yyvsp[-1].NT)->par_lst)[i])->type;
      string plc=(((yyvsp[-1].NT)->par_lst)[i])->place;
      (((yyvsp[-1].NT)->par_lst)[i])->place+="_"+to_string(NumScopes);
      par_typs.pb(typ);
      par_var.pb(mp(typ, plc));
    }
    CurTable->insertFunc((yyval.NT)->place, (yyval.NT)->ret_typ, par_typs, par_cnt);
    ((yyval.NT)->par_types)=par_typs;
  }
#line 4666 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2112 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4674 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2115 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4682 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2120 "src/sharpie.y" /* yacc.c:1646  */
    {
    /*cout<<"sddadadee"<<endl;*/
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4691 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2124 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
  }
#line 4699 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 2129 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->par_lst).pb((yyvsp[0].NT));
    /*cout<<"insert "<<($1->place)<<endl;*/
  }
#line 4709 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 2134 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->par_lst).pb((yyvsp[0].NT));
    /*cout<<"insert "<<($3->place)<<endl;*/
  }
#line 4719 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 2141 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4727 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 2146 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    ((yyval.NT)->place)=string((yyvsp[0].sval));
    /*
     *if(CurTable->look_in_shadow($$->place)){
     *  ($$->place)=($$->place)+"_"+to_string(NumScopes);
     *}
     */
    // delaying this process till next scope
    /*CurTable->insertVariable(($2->type),($$->place));*/
    // TODO: insert array type
    ((yyval.NT)->type)=((yyvsp[-1].NT)->type);
  }
#line 4745 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 2161 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4753 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 2164 "src/sharpie.y" /* yacc.c:1646  */
    {
    // Not used
  }
#line 4761 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2228 "src/sharpie.y" /* yacc.c:1646  */
    {
    //  field_name, type
    map<string,string> tmap;
    /*cout<<"SI: "<<(int)($5->fld_lst).size()<<endl;*/
    for(int i=0;i<(int)((yyvsp[-1].NT)->fld_lst).size();i++){
      Attr* CurFld = ((yyvsp[-1].NT)->fld_lst)[i];
      string typ=(CurFld->fld).X;
      cout<<"GFD "<<i<<endl;
      for(int j=0;j<(int)((CurFld->fld).Y).size();j++){
	Attr* CurFldElem = ((CurFld->fld).Y)[j];
	// without "_"
	tmap[(CurFldElem->place)]=typ;
      }
    }
    (CurTable->insertStruct((yyvsp[-3].NT)->place, tmap));
  }
#line 4782 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2246 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
    (yyval.NT)->place=string((yyvsp[0].sval));
    CS_FLAG=true;
    CS_Name=string((yyvsp[0].sval));
  }
#line 4793 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2260 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
    CS_FLAG=false;
    EndScope();
  }
#line 4803 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2267 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=new Attr();
  }
#line 4811 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2270 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4819 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2275 "src/sharpie.y" /* yacc.c:1646  */
    {
   (yyval.NT)=(yyvsp[0].NT);
   ((yyval.NT)->fld_lst).pb((yyvsp[0].NT));
  }
#line 4828 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2279 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
   ((yyval.NT)->fld_lst).pb((yyvsp[0].NT));
  }
#line 4837 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2285 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4845 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2288 "src/sharpie.y" /* yacc.c:1646  */
    {
    // not used
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4854 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2298 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-1].NT);
  }
#line 4862 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2303 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4870 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2306 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
  }
#line 4878 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2311 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[0].NT);
    ((yyval.NT)->init_list).pb((yyvsp[0].NT));
  }
#line 4887 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2315 "src/sharpie.y" /* yacc.c:1646  */
    {
    (yyval.NT)=(yyvsp[-2].NT);
    ((yyval.NT)->init_list).pb((yyvsp[0].NT));
  }
#line 4896 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2358 "src/sharpie.y" /* yacc.c:1646  */
    {
    BeginScope();
  }
#line 4904 "sharpie.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2362 "src/sharpie.y" /* yacc.c:1646  */
    {
      (yyval.NT)=new Attr();
      (yyval.NT)->place="";
    }
#line 4913 "sharpie.tab.c" /* yacc.c:1646  */
    break;


#line 4917 "sharpie.tab.c" /* yacc.c:1646  */
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
#line 2369 "src/sharpie.y" /* yacc.c:1906  */


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
    NumScopes=1;
    FLAG=false;
    CS_FLAG=true;
    yyin = myfile;
    do {
    	yyparse();
    } while (!feof(yyin));
}



void yyerror(const char *s) {
	/*cout << "EEK, parse error!  Message: " << s << endl;*/
	printf("%d:%s LA=[%s]\n",yylineno,s,yytname[YYTRANSLATE(yychar)]);
	exit(-1);
}
