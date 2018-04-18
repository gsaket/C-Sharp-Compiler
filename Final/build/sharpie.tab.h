/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 169 "src/sharpie.y" /* yacc.c:1909  */

	int ival;
	float fval;
	char* sval;
	Attr* NT;

#line 138 "sharpie.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SHARPIE_TAB_H_INCLUDED  */
