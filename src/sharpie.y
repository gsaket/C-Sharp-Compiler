%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
%}

%union {
	int ival;
	float fval;
	char *sval;
}


%token <ival> INTEGER_LITERAL    300
%token <ival> CHARACTER_LITERAL  301
%token <ival> COMMA              302
%token <ival> LEFT_BRACKET       303
%token <ival> RIGHT_BRACKET      304
%token <ival> RANK_SPECIFIER     305

%token <ival> PLUSEQ     306
%token <ival> MINUSEQ    307
%token <ival> STAREQ     308
%token <ival> DIVEQ      309
%token <ival> MODEQ      310
%token <ival> XOREQ      311
%token <ival> ANDEQ      312
%token <ival> OREQ       313
%token <ival> LTLT       314
%token <ival> GTGT       315
%token <ival> GTGTEQ     316
%token <ival> LTLTEQ     317
%token <ival> EQEQ       318
%token <ival> NOTEQ      319
%token <ival> LEQ        320
%token <ival> GEQ        321
%token <ival> ANDAND     322
%token <ival> OROR       323
%token <ival> PLUSPLUS   324
%token <ival> MINUSMINUS 325
%token <ival> ARROW      326
%token <ival> IDENTIFIER 327
%token <ival> INT_TYPE   328
%token <ival> BOOL_TYPE  329
%token <ival> CHAR_TYPE  330
%token <ival> ABSTRACT   331
%token <ival> BREAK      332
%token <ival> BASE       333
%token <ival> CASE       334
%token <ival> CLASS      335
%token <ival> CONST      336
%token <ival> CONTINUE   337
%token <ival> DEFAULT    338
%token <ival> DO         339
%token <ival> ELSE       340
%token <ival> FALSE      341
%token <ival> FOR        342
%token <ival> FOREACH    343
%token <ival> GOTO       344
%token <ival> IF         345
%token <ival> IN         346
%token <ival> INTERFACE  347
%token <ival> NAMESPACE  348
%token <ival> NEW        349
%token <ival> NULL_TYPE  350
%token <ival> OBJECT     351
%token <ival> OPERATOR   352
%token <ival> OUT        353
%token <ival> OVERRIDE   354
%token <ival> PRIVATE    355
%token <ival> PROTECTED  356
%token <ival> PUBLIC     357
%token <ival> RETURN     358
%token <ival> SIZEOF     359
%token <ival> STRING_TYPE 360
%token <ival> STRUCT    361
%token <ival> SWITCH    362
%token <ival> THIS      363
%token <ival> TRUE      364
%token <ival> TYPEOF    365
%token <ival> USING     366
%token <ival> VIRTUAL   367
%token <ival> VOID      368
%token <ival> WHILE     369
%token <ival> BLOCK_BEGIN 370
%token <ival> BLOCK_END   371

%%

itype:
	 INT_TYPE;

%%

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	exit(-1);
}
