%{
#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
#define X first
#define Y second
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
{IntegerLiteral}     { return INTEGER_LITERAL; }
{CharacterLiteral}   { return CHARACTER_LITERAL; }
{StringLiteral}      { return STRING_LITERAL; }

","   { return COMMA; }
"["   { return LEFT_BRACKET; }
"]"   { return RIGHT_BRACKET; }
{RankSpecifier}     { return RANK_SPECIFIER; }
"+="  { return PLUSEQ; }
"-="  { return MINUSEQ; }
"*="  { return STAREQ; }
"/="  { return DIVEQ; }
"%="  { return MODEQ; }
"^="  { return XOREQ; }
"&="  { return ANDEQ; }
"|="  { return OREQ; }
"<<"  { return LTLT; }
">>"  { return GTGT; }
">>="  { return GTGTEQ; }
"<<="  { return LTLTEQ; }
"=="  { return EQEQ; }
"!="  { return NOTEQ; }
"<="  { return LEQ; }
">="  { return GEQ; }
"&&"  { return ANDAND; }
"||"  { return OROR; }
"++"  { return PLUSPLUS; }
"--"  { return MINUSMINUS; }
"->"  { return ARROW; }
"::"  { return COLCOL; }

"int"  {return INT_TYPE; }
"bool" { return BOOL_TYPE; }
"char" { return CHAR_TYPE; }
"abstract"  { return ABSTRACT; }
"break" {return BREAK;}
"base"  {return BASE;}
"case"    {return CASE;}
"class"    {return CLASS;}
"const"    {return CONST;}
"continue"    {return CONTINUE;}
"default"    {return DEFAULT;}
"do"        {return DO;}
"else"      {return ELSE;}
"false"     {return FALSE;}
"for"       {return FOR;}
"foreach"    {return FOREACH;}
"goto"      {return GOTO;}
"if"        {return IF;}
"in"        {return IN;}
"interface"    {return INTERFACE;}
"namespace"    {return NAMESPACE;}
"new"         {return NEW;}
"null"        {return NULL_TYPE;}
"object"      {return OBJECT;}
"operator"    {return OPERATOR;}
"out"        {return OUT;}
"override"   {return OVERRIDE;}
"private"    {return PRIVATE;}
"protected"    {return PROTECTED;}
"public"    {return PUBLIC;}
"return"    {return RETURN;}
"sizeof"    {return SIZEOF;}
"string"    {return STRING_TYPE;}
"struct"    {return STRUCT;}
"switch"    {return SWITCH;}
"this"       {return THIS;}
"true"       {return TRUE;}
"typeof"     {return TYPEOF;}
"using"      {return USING;}
"virtual"    {return VIRTUAL;}
"void"       {return VOID;}
"while"      {return WHILE;}


{Identifier}          { yylval.ival = 10;return IDENTIFIER; }
{AtIdentifier}       { return IDENTIFIER; }

.           { if(legalChar(yytext[0])) return yytext[0];
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


