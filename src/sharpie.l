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
    '(', ')', '<', '>',
    '+', '-', '*', '/', '%', '&', '|', '!', '~', '^',
    '=', '?','"'
};

map<int, string> TknStr;
map<int, vector<char*> > TknStats;
map<int, int> FreqToken;

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
QuoteEscseq          \"\"
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

","   { return COMMA; }
"["   { return LEFT_BRACKET; }
"]"   { return RIGHT_BRACKET; }
{RankSpecifier}     { return RANK_SPECIFIER; }
"{"   { return BLOCK_BEGIN; }
"}"   { return BLOCK_END; }
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
"flase"     {return FALSE;}
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


{Identifier}          { return IDENTIFIER; }
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
TknStr[BLOCK_BEGIN]="BLOCK_BEGIN";
TknStr[BLOCK_END]="BLOCK_END";

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
}


int main(int argc, char** argv) {
	/*
	 *FILE *myfile = fopen("a.sharpie.file", "r");
	 *if (!myfile) {
	 *    cout << "I can't open a.sharpie.file!" << endl;
	 *    return -1;
	 *}
	 *yyin = myfile;
	 *do {
	 *    yyparse();
	 *} while (!feof(yyin));
	 */
	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
	    cout << "Can't open the file!" << endl;
	    return -1;
	}
	yyin = myfile;

	getStrings();
	int x;
	while(1){
		x=yylex();
		if(x == 0)break;
		TknStats[x].push_back(strdup(yytext));
		FreqToken[x]++;
	}
	cout<<"Token";
	for(int i=0;i<10;i++)
	  cout<<" ";
	cout<<"Occurences"<<"\t"<<"Lexemes"<<endl;
	map<int, vector<char*> > ::iterator it;
	for(it=TknStats.begin();it!=TknStats.end();it++){
	  int idx=it->X;
	  int length=TknStr[idx].size();
	  cout<<TknStr[idx];
	  int space=20-length;
	  for(int i=0;i<space;i++)cout<<" ";
	  cout<<FreqToken[idx]<<"\t\t";
	  sort(it->Y.begin(),it->Y.end(),comp);
	  for(int i=0;i<it->Y.size();i++)
	  {
	    if(i>0 && strcmp(it->Y[i],it->Y[i-1])==0)
	      continue;
	    if(i==0)
	      cout<<it->Y[i]<<endl;
	    else 
	    {
	      for(int i=0;i<20;i++)
		cout<<" ";
	      cout<<"  ";
	      cout<<"\t\t";
	      cout<<it->Y[i]<<endl;
	    }
	  }
	}
}


