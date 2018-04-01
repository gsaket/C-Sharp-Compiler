%{
#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
#define X first
#define Y second
#include "../include/attr.h"
#include "sharpie.tab.h"  // to get the token types that we return

int legalChar(const char c);

bool comp(char* a, char* b)
{
  return (strcmp(a,b)<0);
}

char LegalList [] = {
    '.', ';', ':',
    '(', ')','{', '}', '<', '>',
    '+', '-', '*', '/', '%', '&', '|', '!', '~', '^',
    '=', '?','"'
};

map<int, vector<char*> > TknStats;

%}

%option noyywrap
%option yylineno

SingleLineComment    "//".*
WhiteSpace            [ \t\n\r]
Digit                [0-9]
IntegerLiteral       {Digit}+
Sign                 [+\-]
SingleChar            [^\\\']
SimpleEscSeq         \\[\'\"\\0abfnrtv]
Character              {SingleChar}|{SimpleEscSeq}
CharacterLiteral      \'{Character}\'
SingleStringChar     [^\\\"]
RegStringChar        {SingleStringChar}|{SimpleEscSeq}
RegularString         \"{RegStringChar}*\"
SingleVerbatimChar   [^\"]
QuoteEscSeq          \"\"
VerbStringChar       {SingleVerbatimChar}|{QuoteEscSeq}
VerbatimString        @\"{VerbStringChar}*\"
StringLiteral         {RegularString}|{VerbatimString}
LetterChar            [A-Za-z]
IdentChar             {Digit}|{LetterChar}|"_"|"@"
Identifier             ({LetterChar}|"_"){IdentChar}*
AtIdentifier          \@{Identifier}
RankSpecifier         "["{WhiteSpace}*"]"

%%

{WhiteSpace}         { ;/* Ignoring WhiteSpace*/}
{SingleLineComment}  { ;/* Ignoring SingleLineComment*/}
{IntegerLiteral}     { yylval.sval=strdup(yytext);return INTEGER_LITERAL; }
{CharacterLiteral}   { yylval.sval=strdup(yytext);return CHARACTER_LITERAL; }
{StringLiteral}      { yylval.sval=strdup(yytext);return STRING_LITERAL; }

","   { yylval.sval=strdup(yytext);return COMMA; }
"["   { yylval.sval=strdup(yytext);return LEFT_BRACKET; }
"]"   { yylval.sval=strdup(yytext);return RIGHT_BRACKET; }
{RankSpecifier}     { yylval.sval=strdup(yytext);return RANK_SPECIFIER; }
"+="  { yylval.sval=strdup(yytext);return PLUSEQ; }
"-="  { yylval.sval=strdup(yytext);return MINUSEQ; }
"*="  { yylval.sval=strdup(yytext);return STAREQ; }
"/="  { yylval.sval=strdup(yytext);return DIVEQ; }
"%="  { yylval.sval=strdup(yytext);return MODEQ; }
"^="  { yylval.sval=strdup(yytext);return XOREQ; }
"&="  { yylval.sval=strdup(yytext);return ANDEQ; }
"|="  { yylval.sval=strdup(yytext);return OREQ; }
"<<"  { yylval.sval=strdup(yytext);return LTLT; }
">>"  { yylval.sval=strdup(yytext);return GTGT; }
">>="  { yylval.sval=strdup(yytext);return GTGTEQ; }
"<<="  { yylval.sval=strdup(yytext);return LTLTEQ; }
"=="  { yylval.sval=strdup(yytext);return EQEQ; }
"!="  { yylval.sval=strdup(yytext);return NOTEQ; }
"<="  { yylval.sval=strdup(yytext);return LEQ; }
">="  { yylval.sval=strdup(yytext);return GEQ; }
"&&"  { yylval.sval=strdup(yytext);return ANDAND; }
"||"  { yylval.sval=strdup(yytext);return OROR; }
"++"  { yylval.sval=strdup(yytext);return PLUSPLUS; }
"--"  { yylval.sval=strdup(yytext);return MINUSMINUS; }
"->"  { yylval.sval=strdup(yytext);return ARROW; }
"::"  { yylval.sval=strdup(yytext);return COLCOL; }

"int"  { yylval.sval=strdup(yytext);return INT_TYPE; }
"bool" { yylval.sval=strdup(yytext);return BOOL_TYPE; }
"char" { yylval.sval=strdup(yytext);return CHAR_TYPE; }
"abstract"  { yylval.sval=strdup(yytext);return ABSTRACT; }
"break" { yylval.sval=strdup(yytext);return BREAK;}
"base"  { yylval.sval=strdup(yytext);return BASE;}
"case"    { yylval.sval=strdup(yytext);return CASE;}
"class"    { yylval.sval=strdup(yytext);return CLASS;}
"const"    { yylval.sval=strdup(yytext);return CONST;}
"continue"    { yylval.sval=strdup(yytext);return CONTINUE;}
"default"    { yylval.sval=strdup(yytext);return DEFAULT;}
"do"        { yylval.sval=strdup(yytext);return DO;}
"else"      { yylval.sval=strdup(yytext);return ELSE;}
"false"     { yylval.sval=strdup(yytext);return FALSE;}
"for"       { yylval.sval=strdup(yytext);return FOR;}
"foreach"    { yylval.sval=strdup(yytext);return FOREACH;}
"goto"      { yylval.sval=strdup(yytext);return GOTO;}
"if"        { yylval.sval=strdup(yytext);return IF;}
"in"        { yylval.sval=strdup(yytext);return IN;}
"interface"    { yylval.sval=strdup(yytext);return INTERFACE;}
"namespace"    { yylval.sval=strdup(yytext);return NAMESPACE;}
"new"         { yylval.sval=strdup(yytext);return NEW;}
"null"        { yylval.sval=strdup(yytext);return NULL_TYPE;}
"object"      { yylval.sval=strdup(yytext);return OBJECT;}
"operator"    { yylval.sval=strdup(yytext);return OPERATOR;}
"out"        { yylval.sval=strdup(yytext);return OUT;}
"override"   { yylval.sval=strdup(yytext);return OVERRIDE;}
"private"    { yylval.sval=strdup(yytext);return PRIVATE;}
"protected"    { yylval.sval=strdup(yytext);return PROTECTED;}
"public"    { yylval.sval=strdup(yytext);return PUBLIC;}
"return"    { yylval.sval=strdup(yytext);return RETURN;}
"sizeof"    { yylval.sval=strdup(yytext);return SIZEOF;}
"string"    { yylval.sval=strdup(yytext);return STRING_TYPE;}
"struct"    { yylval.sval=strdup(yytext);return STRUCT;}
"switch"    { yylval.sval=strdup(yytext);return SWITCH;}
"this"       { yylval.sval=strdup(yytext);return THIS;}
"true"       { yylval.sval=strdup(yytext);return TRUE;}
"typeof"     { yylval.sval=strdup(yytext);return TYPEOF;}
"using"      { yylval.sval=strdup(yytext);return USING;}
"virtual"    { yylval.sval=strdup(yytext);return VIRTUAL;}
"void"       { yylval.sval=strdup(yytext);return VOID;}
"while"      { yylval.sval=strdup(yytext);return WHILE;}


{Identifier}          { yylval.sval=strdup(yytext);return IDENTIFIER; }
{AtIdentifier}       { yylval.sval=strdup(yytext);return IDENTIFIER; }

.           { yylval.sval=strdup(yytext);if(legalChar(yytext[0])) return yytext[0];
	      else cout<<"Cannot Tokenize: "<<yytext<<endl;
	    }

%%

int legalChar(const char c)
{
  int num_allowed = 20;
  int i;
	for (i=0; i<num_allowed; i++) {
		if (LegalList[i]==c){
		 return 1;
		}
	}
  return 0;
}


