%{
#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
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

%}

%union {
	int ival;
	float fval;
	char* sval;
}


%token <ival> INTEGER_LITERAL    300
%token <sval> CHARACTER_LITERAL  301
%token <sval> COMMA              302
%token <sval> LEFT_BRACKET       303
%token <sval> RIGHT_BRACKET      304
%token <sval> RANK_SPECIFIER     305

%token <sval> PLUSEQ     306
%token <sval> MINUSEQ    307
%token <sval> STAREQ     308
%token <sval> DIVEQ      309
%token <sval> MODEQ      310
%token <sval> XOREQ      311
%token <sval> ANDEQ      312
%token <sval> OREQ       313
%token <sval> LTLT       314
%token <sval> GTGT       315
%token <sval> GTGTEQ     316
%token <sval> LTLTEQ     317
%token <sval> EQEQ       318
%token <sval> NOTEQ      319
%token <sval> LEQ        320
%token <sval> GEQ        321
%token <sval> ANDAND     322
%token <sval> OROR       323
%token <sval> PLUSPLUS   324
%token <sval> MINUSMINUS 325
%token <sval> ARROW      326
%token <sval> IDENTIFIER 327
%token <sval> INT_TYPE   328
%token <sval> BOOL_TYPE  329
%token <sval> CHAR_TYPE  330
%token <sval> ABSTRACT   331
%token <sval> BREAK      332
%token <sval> BASE       333
%token <sval> CASE       334
%token <sval> CLASS      335
%token <sval> CONST      336
%token <sval> CONTINUE   337
%token <sval> DEFAULT    338
%token <sval> DO         339
%token <sval> ELSE       340
%token <sval> FALSE      341
%token <sval> FOR        342
%token <sval> FOREACH    343
%token <sval> GOTO       344
%token <sval> IF         345
%token <sval> IN         346
%token <sval> INTERFACE  347
%token <sval> NAMESPACE  348
%token <sval> NEW        349
%token <sval> NULL_TYPE  350
%token <sval> OBJECT     351
%token <sval> OPERATOR   352
%token <sval> OUT        353
%token <sval> OVERRIDE   354
%token <sval> PRIVATE    355
%token <sval> PROTECTED  356
%token <sval> PUBLIC     357
%token <sval> RETURN     358
%token <sval> SIZEOF     359
%token <sval> STRING_TYPE 360
%token <sval> STRUCT    361
%token <sval> SWITCH    362
%token <sval> THIS      363
%token <sval> TRUE      364
%token <sval> TYPEOF    365
%token <sval> USING     366
%token <sval> VIRTUAL   367
%token <sval> VOID      368
%token <sval> WHILE     369
%token <sval> STRING_LITERAL 372
%token <sval> COLCOL    373
%start compilation_unit
%%


literal
	 : boolean_literal  { T.clear();T.pb("literal");T.pb("boolean_literal");R.pb(T); }
	 | INTEGER_LITERAL  { T.clear();T.pb("literal");T.pb("INTEGER_LITERAL");R.pb(T); }
	 | CHARACTER_LITERAL  { T.clear();T.pb("literal");T.pb("CHARACTER_LITERAL");R.pb(T); }
	 | STRING_LITERAL  { T.clear();T.pb("literal");T.pb("STRING_LITERAL");R.pb(T); }
	 | NULL_TYPE  { T.clear();T.pb("literal");T.pb("NULL_TYPE");R.pb(T); }
	 ;
boolean_literal
	 : TRUE  { T.clear();T.pb("boolean_literal");T.pb("TRUE");R.pb(T); }
	 | FALSE  { T.clear();T.pb("boolean_literal");T.pb("FALSE");R.pb(T); }
	 ;
namespace_name
	 : qualified_identifier  { T.clear();T.pb("namespace_name");T.pb("qualified_identifier");R.pb(T); }
	 ;
type_name
	 : qualified_identifier  { T.clear();T.pb("type_name");T.pb("qualified_identifier");R.pb(T); }
	 ;
type
	 : non_array_type  { T.clear();T.pb("type");T.pb("non_array_type");R.pb(T); }
	 | array_type  { T.clear();T.pb("type");T.pb("array_type");R.pb(T); }
	 ;
non_array_type
	 : simple_type  { T.clear();T.pb("non_array_type");T.pb("simple_type");R.pb(T); }
	 | type_name  { T.clear();T.pb("non_array_type");T.pb("type_name");R.pb(T); }
	 ;
simple_type
	 : primitive_type  { T.clear();T.pb("simple_type");T.pb("primitive_type");R.pb(T); }
	 | class_type  { T.clear();T.pb("simple_type");T.pb("class_type");R.pb(T); }
	 ;
primitive_type
	 : numeric_type  { T.clear();T.pb("primitive_type");T.pb("numeric_type");R.pb(T); }
	 | BOOL_TYPE  { T.clear();T.pb("primitive_type");T.pb("BOOL_TYPE");R.pb(T); }
	 ;
numeric_type
	 : integral_type  { T.clear();T.pb("numeric_type");T.pb("integral_type");R.pb(T); }
	 ;
integral_type
	 : INT_TYPE  { T.clear();T.pb("integral_type");T.pb("INT_TYPE");R.pb(T); }
	 | CHAR_TYPE  { T.clear();T.pb("integral_type");T.pb("CHAR_TYPE");R.pb(T); }
	 ;
class_type
	 : OBJECT  { T.clear();T.pb("class_type");T.pb("OBJECT");R.pb(T); }
	 | STRING_TYPE  { T.clear();T.pb("class_type");T.pb("STRING_TYPE");R.pb(T); }
	 ;
array_type
	 : array_type rank_specifier  { T.clear();T.pb("array_type");T.pb("array_type");T.pb("rank_specifier");R.pb(T); }
	 | simple_type rank_specifier  { T.clear();T.pb("array_type");T.pb("simple_type");T.pb("rank_specifier");R.pb(T); }
	 | qualified_identifier rank_specifier  { T.clear();T.pb("array_type");T.pb("qualified_identifier");T.pb("rank_specifier");R.pb(T); }
	 ;
rank_specifier
	 : RANK_SPECIFIER  { T.clear();T.pb("rank_specifier");T.pb("RANK_SPECIFIER");R.pb(T); }
	 ;
rank_specifiers_opt
	 : eps  { T.clear();T.pb("rank_specifiers_opt");T.pb("eps");R.pb(T); }
	 | rank_specifier  { T.clear();T.pb("rank_specifiers_opt");T.pb("rank_specifier");R.pb(T); }
	 ;
variable_reference
	 : expression  { T.clear();T.pb("variable_reference");T.pb("expression");R.pb(T); }
	 ;
argument_list
	 : argument  { T.clear();T.pb("argument_list");T.pb("argument");R.pb(T); }
	 | argument_list COMMA argument  { T.clear();T.pb("argument_list");T.pb("argument_list");T.pb("COMMA");T.pb("argument");R.pb(T); }
	 ;
argument
	 : expression  { T.clear();T.pb("argument");T.pb("expression");R.pb(T); }
	 | OUT variable_reference  { T.clear();T.pb("argument");T.pb("OUT");T.pb("variable_reference");R.pb(T); }
	 ;
primary_expression
	 : parenthesized_expression  { T.clear();T.pb("primary_expression");T.pb("parenthesized_expression");R.pb(T); }
	 | primary_expression_no_parenthesis  { T.clear();T.pb("primary_expression");T.pb("primary_expression_no_parenthesis");R.pb(T); }
	 ;
primary_expression_no_parenthesis
	 : literal  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("literal");R.pb(T); }
	 | array_creation_expression  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("array_creation_expression");R.pb(T); }
	 | member_access  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("member_access");R.pb(T); }
	 | invocation_expression  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("invocation_expression");R.pb(T); }
	 | element_access  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("element_access");R.pb(T); }
	 | this_access  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("this_access");R.pb(T); }
	 | base_access  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("base_access");R.pb(T); }
	 | new_expression  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("new_expression");R.pb(T); }
	 | typeof_expression  { T.clear();T.pb("primary_expression_no_parenthesis");T.pb("typeof_expression");R.pb(T); }
	 ;
parenthesized_expression
	 : '(' expression ')'  { T.clear();T.pb("parenthesized_expression");T.pb("\'(\'");T.pb("expression");T.pb("\')\'");R.pb(T); }
	 ;
member_access
	 : primary_expression '.' IDENTIFIER  { T.clear();T.pb("member_access");T.pb("primary_expression");T.pb("\'.\'");T.pb("IDENTIFIER");R.pb(T); }
	 | primitive_type '.' IDENTIFIER  { T.clear();T.pb("member_access");T.pb("primitive_type");T.pb("\'.\'");T.pb("IDENTIFIER");R.pb(T); }
	 | class_type '.' IDENTIFIER  { T.clear();T.pb("member_access");T.pb("class_type");T.pb("\'.\'");T.pb("IDENTIFIER");R.pb(T); }
	 ;
invocation_expression
	 : primary_expression_no_parenthesis '(' argument_list_opt ')'  { T.clear();T.pb("invocation_expression");T.pb("primary_expression_no_parenthesis");T.pb("\'(\'");T.pb("argument_list_opt");T.pb("\')\'");R.pb(T); }
	 | qualified_identifier '(' argument_list_opt ')'  { T.clear();T.pb("invocation_expression");T.pb("qualified_identifier");T.pb("\'(\'");T.pb("argument_list_opt");T.pb("\')\'");R.pb(T); }
	 ;
argument_list_opt
	 : eps  { T.clear();T.pb("argument_list_opt");T.pb("eps");R.pb(T); }
	 | argument_list  { T.clear();T.pb("argument_list_opt");T.pb("argument_list");R.pb(T); }
	 ;
element_access
	 : primary_expression LEFT_BRACKET expression_list RIGHT_BRACKET  { T.clear();T.pb("element_access");T.pb("primary_expression");T.pb("LEFT_BRACKET");T.pb("expression_list");T.pb("RIGHT_BRACKET");R.pb(T); }
	 | qualified_identifier LEFT_BRACKET expression_list RIGHT_BRACKET  { T.clear();T.pb("element_access");T.pb("qualified_identifier");T.pb("LEFT_BRACKET");T.pb("expression_list");T.pb("RIGHT_BRACKET");R.pb(T); }
	 ;
expression_list
	 : expression  { T.clear();T.pb("expression_list");T.pb("expression");R.pb(T); }
	 | expression_list COMMA expression  { T.clear();T.pb("expression_list");T.pb("expression_list");T.pb("COMMA");T.pb("expression");R.pb(T); }
	 ;
this_access
	 : THIS  { T.clear();T.pb("this_access");T.pb("THIS");R.pb(T); }
	 ;
base_access
	 : BASE '.' IDENTIFIER  { T.clear();T.pb("base_access");T.pb("BASE");T.pb("\'.\'");T.pb("IDENTIFIER");R.pb(T); }
	 | BASE LEFT_BRACKET expression_list RIGHT_BRACKET  { T.clear();T.pb("base_access");T.pb("BASE");T.pb("LEFT_BRACKET");T.pb("expression_list");T.pb("RIGHT_BRACKET");R.pb(T); }
	 ;
new_expression
	 : object_creation_expression  { T.clear();T.pb("new_expression");T.pb("object_creation_expression");R.pb(T); }
	 ;
object_creation_expression
	 : NEW type '(' argument_list_opt ')'  { T.clear();T.pb("object_creation_expression");T.pb("NEW");T.pb("type");T.pb("\'(\'");T.pb("argument_list_opt");T.pb("\')\'");R.pb(T); }
	 ;
array_creation_expression
	 : NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET rank_specifiers_opt array_initializer_opt  { T.clear();T.pb("array_creation_expression");T.pb("NEW");T.pb("non_array_type");T.pb("LEFT_BRACKET");T.pb("expression_list");T.pb("RIGHT_BRACKET");T.pb("rank_specifiers_opt");T.pb("array_initializer_opt");R.pb(T); }
	 | NEW array_type array_initializer  { T.clear();T.pb("array_creation_expression");T.pb("NEW");T.pb("array_type");T.pb("array_initializer");R.pb(T); }
	 ;
array_initializer_opt
	 : eps  { T.clear();T.pb("array_initializer_opt");T.pb("eps");R.pb(T); }
	 | array_initializer  { T.clear();T.pb("array_initializer_opt");T.pb("array_initializer");R.pb(T); }
	 ;
typeof_expression
	 : TYPEOF '(' type ')'  { T.clear();T.pb("typeof_expression");T.pb("TYPEOF");T.pb("\'(\'");T.pb("type");T.pb("\')\'");R.pb(T); }
	 | TYPEOF '(' VOID ')'  { T.clear();T.pb("typeof_expression");T.pb("TYPEOF");T.pb("\'(\'");T.pb("VOID");T.pb("\')\'");R.pb(T); }
	 ;
addressof_expression
	 : '&' unary_expression  { T.clear();T.pb("addressof_expression");T.pb("\'&\'");T.pb("unary_expression");R.pb(T); }
	 ;
postfix_expression
	 : primary_expression  { T.clear();T.pb("postfix_expression");T.pb("primary_expression");R.pb(T); }
	 | qualified_identifier  { T.clear();T.pb("postfix_expression");T.pb("qualified_identifier");R.pb(T); }
	 ;
unary_expression_not_plusminus
	 : postfix_expression  { T.clear();T.pb("unary_expression_not_plusminus");T.pb("postfix_expression");R.pb(T); }
	 | '!' unary_expression  { T.clear();T.pb("unary_expression_not_plusminus");T.pb("\'!\'");T.pb("unary_expression");R.pb(T); }
	 | '~' unary_expression  { T.clear();T.pb("unary_expression_not_plusminus");T.pb("\'~\'");T.pb("unary_expression");R.pb(T); }
	 | cast_expression  { T.clear();T.pb("unary_expression_not_plusminus");T.pb("cast_expression");R.pb(T); }
	 ;
pre_increment_expression
	 : PLUSPLUS unary_expression  { T.clear();T.pb("pre_increment_expression");T.pb("PLUSPLUS");T.pb("unary_expression");R.pb(T); }
	 ;
pre_decrement_expression
	 : MINUSMINUS unary_expression  { T.clear();T.pb("pre_decrement_expression");T.pb("MINUSMINUS");T.pb("unary_expression");R.pb(T); }
	 ;
unary_expression
	 : unary_expression_not_plusminus  { T.clear();T.pb("unary_expression");T.pb("unary_expression_not_plusminus");R.pb(T); }
	 | '+' unary_expression  { T.clear();T.pb("unary_expression");T.pb("\'+\'");T.pb("unary_expression");R.pb(T); }
	 | '-' unary_expression  { T.clear();T.pb("unary_expression");T.pb("\'-\'");T.pb("unary_expression");R.pb(T); }
	 | '*' unary_expression  { T.clear();T.pb("unary_expression");T.pb("\'*\'");T.pb("unary_expression");R.pb(T); }
	 | pre_increment_expression  { T.clear();T.pb("unary_expression");T.pb("pre_increment_expression");R.pb(T); }
	 | pre_decrement_expression  { T.clear();T.pb("unary_expression");T.pb("pre_decrement_expression");R.pb(T); }
	 | addressof_expression  { T.clear();T.pb("unary_expression");T.pb("addressof_expression");R.pb(T); }
	 ;
cast_expression
	 : '(' expression ')' unary_expression_not_plusminus  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("expression");T.pb("\')\'");T.pb("unary_expression_not_plusminus");R.pb(T); }
	 | '(' multiplicative_expression '*' ')' unary_expression  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("multiplicative_expression");T.pb("\'*\'");T.pb("\')\'");T.pb("unary_expression");R.pb(T); }
	 | '(' qualified_identifier rank_specifier type_quals_opt ')' unary_expression  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("qualified_identifier");T.pb("rank_specifier");T.pb("type_quals_opt");T.pb("\')\'");T.pb("unary_expression");R.pb(T); }
	 | '(' primitive_type type_quals_opt ')' unary_expression  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("primitive_type");T.pb("type_quals_opt");T.pb("\')\'");T.pb("unary_expression");R.pb(T); }
	 | '(' class_type type_quals_opt ')' unary_expression  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("class_type");T.pb("type_quals_opt");T.pb("\')\'");T.pb("unary_expression");R.pb(T); }
	 | '(' VOID type_quals_opt ')' unary_expression  { T.clear();T.pb("cast_expression");T.pb("\'(\'");T.pb("VOID");T.pb("type_quals_opt");T.pb("\')\'");T.pb("unary_expression");R.pb(T); }
	 ;
type_quals_opt
	 : eps  { T.clear();T.pb("type_quals_opt");T.pb("eps");R.pb(T); }
	 | type_quals  { T.clear();T.pb("type_quals_opt");T.pb("type_quals");R.pb(T); }
	 ;
type_quals
	 : type_qual  { T.clear();T.pb("type_quals");T.pb("type_qual");R.pb(T); }
	 | type_quals type_qual  { T.clear();T.pb("type_quals");T.pb("type_quals");T.pb("type_qual");R.pb(T); }
	 ;
type_qual
	 : rank_specifier  { T.clear();T.pb("type_qual");T.pb("rank_specifier");R.pb(T); }
	 | '*'  { T.clear();T.pb("type_qual");T.pb("\'*\'");R.pb(T); }
	 ;
multiplicative_expression
	 : unary_expression  { T.clear();T.pb("multiplicative_expression");T.pb("unary_expression");R.pb(T); }
	 | multiplicative_expression '*' unary_expression  { T.clear();T.pb("multiplicative_expression");T.pb("multiplicative_expression");T.pb("\'*\'");T.pb("unary_expression");R.pb(T); }
	 | multiplicative_expression '/' unary_expression  { T.clear();T.pb("multiplicative_expression");T.pb("multiplicative_expression");T.pb("\'/\'");T.pb("unary_expression");R.pb(T); }
	 | multiplicative_expression '%' unary_expression  { T.clear();T.pb("multiplicative_expression");T.pb("multiplicative_expression");T.pb("\'%\'");T.pb("unary_expression");R.pb(T); }
	 ;
additive_expression
	 : multiplicative_expression  { T.clear();T.pb("additive_expression");T.pb("multiplicative_expression");R.pb(T); }
	 | additive_expression '+' multiplicative_expression  { T.clear();T.pb("additive_expression");T.pb("additive_expression");T.pb("\'+\'");T.pb("multiplicative_expression");R.pb(T); }
	 | additive_expression '-' multiplicative_expression  { T.clear();T.pb("additive_expression");T.pb("additive_expression");T.pb("\'-\'");T.pb("multiplicative_expression");R.pb(T); }
	 ;
shift_expression
	 : additive_expression  { T.clear();T.pb("shift_expression");T.pb("additive_expression");R.pb(T); }
	 | shift_expression LTLT additive_expression  { T.clear();T.pb("shift_expression");T.pb("shift_expression");T.pb("LTLT");T.pb("additive_expression");R.pb(T); }
	 | shift_expression GTGT additive_expression  { T.clear();T.pb("shift_expression");T.pb("shift_expression");T.pb("GTGT");T.pb("additive_expression");R.pb(T); }
	 ;
relational_expression
	 : shift_expression  { T.clear();T.pb("relational_expression");T.pb("shift_expression");R.pb(T); }
	 | relational_expression '<' shift_expression  { T.clear();T.pb("relational_expression");T.pb("relational_expression");T.pb("\'<\'");T.pb("shift_expression");R.pb(T); }
	 | relational_expression '>' shift_expression  { T.clear();T.pb("relational_expression");T.pb("relational_expression");T.pb("\'>\'");T.pb("shift_expression");R.pb(T); }
	 | relational_expression LEQ shift_expression  { T.clear();T.pb("relational_expression");T.pb("relational_expression");T.pb("LEQ");T.pb("shift_expression");R.pb(T); }
	 | relational_expression GEQ shift_expression  { T.clear();T.pb("relational_expression");T.pb("relational_expression");T.pb("GEQ");T.pb("shift_expression");R.pb(T); }
	 ;
equality_expression
	 : relational_expression  { T.clear();T.pb("equality_expression");T.pb("relational_expression");R.pb(T); }
	 | equality_expression EQEQ relational_expression  { T.clear();T.pb("equality_expression");T.pb("equality_expression");T.pb("EQEQ");T.pb("relational_expression");R.pb(T); }
	 | equality_expression NOTEQ relational_expression  { T.clear();T.pb("equality_expression");T.pb("equality_expression");T.pb("NOTEQ");T.pb("relational_expression");R.pb(T); }
	 ;
and_expression
	 : equality_expression  { T.clear();T.pb("and_expression");T.pb("equality_expression");R.pb(T); }
	 | and_expression '&' equality_expression  { T.clear();T.pb("and_expression");T.pb("and_expression");T.pb("\'&\'");T.pb("equality_expression");R.pb(T); }
	 ;
exclusive_or_expression
	 : and_expression  { T.clear();T.pb("exclusive_or_expression");T.pb("and_expression");R.pb(T); }
	 | exclusive_or_expression '^' and_expression  { T.clear();T.pb("exclusive_or_expression");T.pb("exclusive_or_expression");T.pb("\'^\'");T.pb("and_expression");R.pb(T); }
	 ;
inclusive_or_expression
	 : exclusive_or_expression  { T.clear();T.pb("inclusive_or_expression");T.pb("exclusive_or_expression");R.pb(T); }
	 | inclusive_or_expression '|' exclusive_or_expression  { T.clear();T.pb("inclusive_or_expression");T.pb("inclusive_or_expression");T.pb("\'|\'");T.pb("exclusive_or_expression");R.pb(T); }
	 ;
conditional_and_expression
	 : inclusive_or_expression  { T.clear();T.pb("conditional_and_expression");T.pb("inclusive_or_expression");R.pb(T); }
	 | conditional_and_expression ANDAND inclusive_or_expression  { T.clear();T.pb("conditional_and_expression");T.pb("conditional_and_expression");T.pb("ANDAND");T.pb("inclusive_or_expression");R.pb(T); }
	 ;
conditional_or_expression
	 : conditional_and_expression  { T.clear();T.pb("conditional_or_expression");T.pb("conditional_and_expression");R.pb(T); }
	 | conditional_or_expression OROR conditional_and_expression  { T.clear();T.pb("conditional_or_expression");T.pb("conditional_or_expression");T.pb("OROR");T.pb("conditional_and_expression");R.pb(T); }
	 ;
conditional_expression
	 : conditional_or_expression  { T.clear();T.pb("conditional_expression");T.pb("conditional_or_expression");R.pb(T); }
	 | conditional_or_expression '?' expression ':' expression  { T.clear();T.pb("conditional_expression");T.pb("conditional_or_expression");T.pb("\'?\'");T.pb("expression");T.pb("\':\'");T.pb("expression");R.pb(T); }
	 ;
assignment
	 : unary_expression assignment_operator expression  { T.clear();T.pb("assignment");T.pb("unary_expression");T.pb("assignment_operator");T.pb("expression");R.pb(T); }
	 ;
assignment_operator
	 : '='  { T.clear();T.pb("assignment_operator");T.pb("\'=\'");R.pb(T); }
	 | PLUSEQ  { T.clear();T.pb("assignment_operator");T.pb("PLUSEQ");R.pb(T); }
	 | MINUSEQ  { T.clear();T.pb("assignment_operator");T.pb("MINUSEQ");R.pb(T); }
	 | STAREQ  { T.clear();T.pb("assignment_operator");T.pb("STAREQ");R.pb(T); }
	 | DIVEQ  { T.clear();T.pb("assignment_operator");T.pb("DIVEQ");R.pb(T); }
	 | MODEQ  { T.clear();T.pb("assignment_operator");T.pb("MODEQ");R.pb(T); }
	 | XOREQ  { T.clear();T.pb("assignment_operator");T.pb("XOREQ");R.pb(T); }
	 | ANDEQ  { T.clear();T.pb("assignment_operator");T.pb("ANDEQ");R.pb(T); }
	 | OREQ  { T.clear();T.pb("assignment_operator");T.pb("OREQ");R.pb(T); }
	 | GTGTEQ  { T.clear();T.pb("assignment_operator");T.pb("GTGTEQ");R.pb(T); }
	 | LTLTEQ  { T.clear();T.pb("assignment_operator");T.pb("LTLTEQ");R.pb(T); }
	 ;
expression
	 : conditional_expression  { T.clear();T.pb("expression");T.pb("conditional_expression");R.pb(T); }
	 | assignment  { T.clear();T.pb("expression");T.pb("assignment");R.pb(T); }
	 ;
constant_expression
	 : expression  { T.clear();T.pb("constant_expression");T.pb("expression");R.pb(T); }
	 ;
boolean_expression
	 : expression  { T.clear();T.pb("boolean_expression");T.pb("expression");R.pb(T); }
	 ;
statement
	 : declaration_statement  { T.clear();T.pb("statement");T.pb("declaration_statement");R.pb(T); }
	 | embedded_statement  { T.clear();T.pb("statement");T.pb("embedded_statement");R.pb(T); }
	 ;
embedded_statement
	 : block  { T.clear();T.pb("embedded_statement");T.pb("block");R.pb(T); }
	 | empty_statement  { T.clear();T.pb("embedded_statement");T.pb("empty_statement");R.pb(T); }
	 | expression_statement  { T.clear();T.pb("embedded_statement");T.pb("expression_statement");R.pb(T); }
	 | selection_statement  { T.clear();T.pb("embedded_statement");T.pb("selection_statement");R.pb(T); }
	 | iteration_statement  { T.clear();T.pb("embedded_statement");T.pb("iteration_statement");R.pb(T); }
	 | jump_statement  { T.clear();T.pb("embedded_statement");T.pb("jump_statement");R.pb(T); }
	 ;
block
	 : '{' statement_list_opt '}'  { T.clear();T.pb("block");T.pb("\'{\'");T.pb("statement_list_opt");T.pb("\'}\'");R.pb(T); }
	 ;
statement_list_opt
	 : eps  { T.clear();T.pb("statement_list_opt");T.pb("eps");R.pb(T); }
	 | statement_list  { T.clear();T.pb("statement_list_opt");T.pb("statement_list");R.pb(T); }
	 ;
statement_list
	 : statement  { T.clear();T.pb("statement_list");T.pb("statement");R.pb(T); }
	 | statement_list statement  { T.clear();T.pb("statement_list");T.pb("statement_list");T.pb("statement");R.pb(T); }
	 ;
empty_statement
	 : ';'  { T.clear();T.pb("empty_statement");T.pb("\';\'");R.pb(T); }
	 ;
declaration_statement
	 : local_variable_declaration ';'  { T.clear();T.pb("declaration_statement");T.pb("local_variable_declaration");T.pb("\';\'");R.pb(T); }
	 ;
local_variable_declaration
	 : type variable_declarators  { T.clear();T.pb("local_variable_declaration");T.pb("type");T.pb("variable_declarators");R.pb(T); }
	 ;
variable_declarators
	 : variable_declarator  { T.clear();T.pb("variable_declarators");T.pb("variable_declarator");R.pb(T); }
	 | variable_declarators COMMA variable_declarator  { T.clear();T.pb("variable_declarators");T.pb("variable_declarators");T.pb("COMMA");T.pb("variable_declarator");R.pb(T); }
	 ;
variable_declarator
	 : IDENTIFIER  { T.clear();T.pb("variable_declarator");T.pb("IDENTIFIER");R.pb(T); }
	 | IDENTIFIER '=' variable_initializer  { T.clear();T.pb("variable_declarator");T.pb("IDENTIFIER");T.pb("\'=\'");T.pb("variable_initializer");R.pb(T); }
	 ;
variable_initializer
	 : expression  { T.clear();T.pb("variable_initializer");T.pb("expression");R.pb(T); }
	 | array_initializer  { T.clear();T.pb("variable_initializer");T.pb("array_initializer");R.pb(T); }
	 ;
expression_statement
	 : statement_expression ';'  { T.clear();T.pb("expression_statement");T.pb("statement_expression");T.pb("\';\'");R.pb(T); }
	 ;
statement_expression
	 : invocation_expression  { T.clear();T.pb("statement_expression");T.pb("invocation_expression");R.pb(T); }
	 | object_creation_expression  { T.clear();T.pb("statement_expression");T.pb("object_creation_expression");R.pb(T); }
	 | assignment  { T.clear();T.pb("statement_expression");T.pb("assignment");R.pb(T); }
	 | pre_increment_expression  { T.clear();T.pb("statement_expression");T.pb("pre_increment_expression");R.pb(T); }
	 | pre_decrement_expression  { T.clear();T.pb("statement_expression");T.pb("pre_decrement_expression");R.pb(T); }
	 ;
selection_statement
	 : if_statement  { T.clear();T.pb("selection_statement");T.pb("if_statement");R.pb(T); }
	 | switch_statement  { T.clear();T.pb("selection_statement");T.pb("switch_statement");R.pb(T); }
	 ;
if_statement
	 : IF '(' boolean_expression ')' embedded_statement  { T.clear();T.pb("if_statement");T.pb("IF");T.pb("\'(\'");T.pb("boolean_expression");T.pb("\')\'");T.pb("embedded_statement");R.pb(T); }
	 | IF '(' boolean_expression ')' embedded_statement ELSE embedded_statement  { T.clear();T.pb("if_statement");T.pb("IF");T.pb("\'(\'");T.pb("boolean_expression");T.pb("\')\'");T.pb("embedded_statement");T.pb("ELSE");T.pb("embedded_statement");R.pb(T); }
	 ;
switch_statement
	 : SWITCH '(' expression ')' switch_block  { T.clear();T.pb("switch_statement");T.pb("SWITCH");T.pb("\'(\'");T.pb("expression");T.pb("\')\'");T.pb("switch_block");R.pb(T); }
	 ;
switch_block
	 : '{' switch_sections_opt '}'  { T.clear();T.pb("switch_block");T.pb("\'{\'");T.pb("switch_sections_opt");T.pb("\'}\'");R.pb(T); }
	 ;
switch_sections_opt
	 : eps  { T.clear();T.pb("switch_sections_opt");T.pb("eps");R.pb(T); }
	 | switch_sections  { T.clear();T.pb("switch_sections_opt");T.pb("switch_sections");R.pb(T); }
	 ;
switch_sections
	 : switch_section  { T.clear();T.pb("switch_sections");T.pb("switch_section");R.pb(T); }
	 | switch_sections switch_section  { T.clear();T.pb("switch_sections");T.pb("switch_sections");T.pb("switch_section");R.pb(T); }
	 ;
switch_section
	 : switch_labels statement_list  { T.clear();T.pb("switch_section");T.pb("switch_labels");T.pb("statement_list");R.pb(T); }
	 ;
switch_labels
	 : switch_label  { T.clear();T.pb("switch_labels");T.pb("switch_label");R.pb(T); }
	 | switch_labels switch_label  { T.clear();T.pb("switch_labels");T.pb("switch_labels");T.pb("switch_label");R.pb(T); }
	 ;
switch_label
	 : CASE constant_expression ':'  { T.clear();T.pb("switch_label");T.pb("CASE");T.pb("constant_expression");T.pb("\':\'");R.pb(T); }
	 | DEFAULT ':'  { T.clear();T.pb("switch_label");T.pb("DEFAULT");T.pb("\':\'");R.pb(T); }
	 ;
iteration_statement
	 : while_statement  { T.clear();T.pb("iteration_statement");T.pb("while_statement");R.pb(T); }
	 | do_statement  { T.clear();T.pb("iteration_statement");T.pb("do_statement");R.pb(T); }
	 | for_statement  { T.clear();T.pb("iteration_statement");T.pb("for_statement");R.pb(T); }
	 | foreach_statement  { T.clear();T.pb("iteration_statement");T.pb("foreach_statement");R.pb(T); }
	 ;
while_statement
	 : WHILE '(' boolean_expression ')' embedded_statement  { T.clear();T.pb("while_statement");T.pb("WHILE");T.pb("\'(\'");T.pb("boolean_expression");T.pb("\')\'");T.pb("embedded_statement");R.pb(T); }
	 ;
do_statement
	 : DO embedded_statement WHILE '(' boolean_expression ')' ';'  { T.clear();T.pb("do_statement");T.pb("DO");T.pb("embedded_statement");T.pb("WHILE");T.pb("\'(\'");T.pb("boolean_expression");T.pb("\')\'");T.pb("\';\'");R.pb(T); }
	 ;
for_statement
	 : FOR '(' for_initializer_opt ';' for_condition_opt ';' for_iterator_opt ')' embedded_statement  { T.clear();T.pb("for_statement");T.pb("FOR");T.pb("\'(\'");T.pb("for_initializer_opt");T.pb("\';\'");T.pb("for_condition_opt");T.pb("\';\'");T.pb("for_iterator_opt");T.pb("\')\'");T.pb("embedded_statement");R.pb(T); }
	 ;
for_initializer_opt
	 : eps  { T.clear();T.pb("for_initializer_opt");T.pb("eps");R.pb(T); }
	 | for_initializer  { T.clear();T.pb("for_initializer_opt");T.pb("for_initializer");R.pb(T); }
	 ;
for_condition_opt
	 : eps  { T.clear();T.pb("for_condition_opt");T.pb("eps");R.pb(T); }
	 | for_condition  { T.clear();T.pb("for_condition_opt");T.pb("for_condition");R.pb(T); }
	 ;
for_iterator_opt
	 : eps  { T.clear();T.pb("for_iterator_opt");T.pb("eps");R.pb(T); }
	 | for_iterator  { T.clear();T.pb("for_iterator_opt");T.pb("for_iterator");R.pb(T); }
	 ;
for_initializer
	 : local_variable_declaration  { T.clear();T.pb("for_initializer");T.pb("local_variable_declaration");R.pb(T); }
	 | statement_expression_list  { T.clear();T.pb("for_initializer");T.pb("statement_expression_list");R.pb(T); }
	 ;
for_condition
	 : boolean_expression  { T.clear();T.pb("for_condition");T.pb("boolean_expression");R.pb(T); }
	 ;
for_iterator
	 : statement_expression_list  { T.clear();T.pb("for_iterator");T.pb("statement_expression_list");R.pb(T); }
	 ;
statement_expression_list
	 : statement_expression  { T.clear();T.pb("statement_expression_list");T.pb("statement_expression");R.pb(T); }
	 | statement_expression_list COMMA statement_expression  { T.clear();T.pb("statement_expression_list");T.pb("statement_expression_list");T.pb("COMMA");T.pb("statement_expression");R.pb(T); }
	 ;
foreach_statement
	 : FOREACH '(' type IDENTIFIER IN expression ')' embedded_statement  { T.clear();T.pb("foreach_statement");T.pb("FOREACH");T.pb("\'(\'");T.pb("type");T.pb("IDENTIFIER");T.pb("IN");T.pb("expression");T.pb("\')\'");T.pb("embedded_statement");R.pb(T); }
	 ;
jump_statement
	 : break_statement  { T.clear();T.pb("jump_statement");T.pb("break_statement");R.pb(T); }
	 | continue_statement  { T.clear();T.pb("jump_statement");T.pb("continue_statement");R.pb(T); }
	 | goto_statement  { T.clear();T.pb("jump_statement");T.pb("goto_statement");R.pb(T); }
	 | return_statement  { T.clear();T.pb("jump_statement");T.pb("return_statement");R.pb(T); }
	 ;
break_statement
	 : BREAK ';'  { T.clear();T.pb("break_statement");T.pb("BREAK");T.pb("\';\'");R.pb(T); }
	 ;
continue_statement
	 : CONTINUE ';'  { T.clear();T.pb("continue_statement");T.pb("CONTINUE");T.pb("\';\'");R.pb(T); }
	 ;
goto_statement
	 : GOTO IDENTIFIER ';'  { T.clear();T.pb("goto_statement");T.pb("GOTO");T.pb("IDENTIFIER");T.pb("\';\'");R.pb(T); }
	 ;
return_statement
	 : RETURN expression_opt ';'  { T.clear();T.pb("return_statement");T.pb("RETURN");T.pb("expression_opt");T.pb("\';\'");R.pb(T); }
	 ;
expression_opt
	 : eps  { T.clear();T.pb("expression_opt");T.pb("eps");R.pb(T); }
	 | expression  { T.clear();T.pb("expression_opt");T.pb("expression");R.pb(T); }
	 ;
compilation_unit
	 : using_directives_opt  { T.clear();T.pb("compilation_unit");T.pb("using_directives_opt");R.pb(T); }
	 | using_directives_opt namespace_member_declarations  { T.clear();T.pb("compilation_unit");T.pb("using_directives_opt");T.pb("namespace_member_declarations");R.pb(T); }
	 ;
using_directives_opt
	 : eps  { T.clear();T.pb("using_directives_opt");T.pb("eps");R.pb(T); }
	 | using_directives  { T.clear();T.pb("using_directives_opt");T.pb("using_directives");R.pb(T); }
	 ;
namespace_member_declarations_opt
	 : eps  { T.clear();T.pb("namespace_member_declarations_opt");T.pb("eps");R.pb(T); }
	 | namespace_member_declarations  { T.clear();T.pb("namespace_member_declarations_opt");T.pb("namespace_member_declarations");R.pb(T); }
	 ;
namespace_declaration
	 : NAMESPACE qualified_identifier namespace_body comma_opt  { T.clear();T.pb("namespace_declaration");T.pb("NAMESPACE");T.pb("qualified_identifier");T.pb("namespace_body");T.pb("comma_opt");R.pb(T); }
	 ;
comma_opt
	 : eps  { T.clear();T.pb("comma_opt");T.pb("eps");R.pb(T); }
	 | ';'  { T.clear();T.pb("comma_opt");T.pb("\';\'");R.pb(T); }
	 ;
qualified_identifier
	 : IDENTIFIER  { T.clear();T.pb("qualified_identifier");T.pb("IDENTIFIER");R.pb(T); }
	 | qualifier IDENTIFIER  { T.clear();T.pb("qualified_identifier");T.pb("qualifier");T.pb("IDENTIFIER");R.pb(T); }
	 ;
qualifier
	 : IDENTIFIER '.'  { T.clear();T.pb("qualifier");T.pb("IDENTIFIER");T.pb("\'.\'");R.pb(T); }
	 | qualifier IDENTIFIER '.'  { T.clear();T.pb("qualifier");T.pb("qualifier");T.pb("IDENTIFIER");T.pb("\'.\'");R.pb(T); }
	 ;
namespace_body
	 : '{' using_directives_opt namespace_member_declarations_opt '}'  { T.clear();T.pb("namespace_body");T.pb("\'{\'");T.pb("using_directives_opt");T.pb("namespace_member_declarations_opt");T.pb("\'}\'");R.pb(T); }
	 ;
using_directives
	 : using_directive  { T.clear();T.pb("using_directives");T.pb("using_directive");R.pb(T); }
	 | using_directives using_directive  { T.clear();T.pb("using_directives");T.pb("using_directives");T.pb("using_directive");R.pb(T); }
	 ;
using_directive
	 : using_alias_directive  { T.clear();T.pb("using_directive");T.pb("using_alias_directive");R.pb(T); }
	 | using_namespace_directive  { T.clear();T.pb("using_directive");T.pb("using_namespace_directive");R.pb(T); }
	 ;
using_alias_directive
	 : USING IDENTIFIER '=' qualified_identifier ';'  { T.clear();T.pb("using_alias_directive");T.pb("USING");T.pb("IDENTIFIER");T.pb("\'=\'");T.pb("qualified_identifier");T.pb("\';\'");R.pb(T); }
	 ;
using_namespace_directive
	 : USING namespace_name ';'  { T.clear();T.pb("using_namespace_directive");T.pb("USING");T.pb("namespace_name");T.pb("\';\'");R.pb(T); }
	 ;
namespace_member_declarations
	 : namespace_member_declaration  { T.clear();T.pb("namespace_member_declarations");T.pb("namespace_member_declaration");R.pb(T); }
	 | namespace_member_declarations namespace_member_declaration  { T.clear();T.pb("namespace_member_declarations");T.pb("namespace_member_declarations");T.pb("namespace_member_declaration");R.pb(T); }
	 ;
namespace_member_declaration
	 : namespace_declaration  { T.clear();T.pb("namespace_member_declaration");T.pb("namespace_declaration");R.pb(T); }
	 | type_declaration  { T.clear();T.pb("namespace_member_declaration");T.pb("type_declaration");R.pb(T); }
	 ;
type_declaration
	 : class_declaration  { T.clear();T.pb("type_declaration");T.pb("class_declaration");R.pb(T); }
	 | struct_declaration  { T.clear();T.pb("type_declaration");T.pb("struct_declaration");R.pb(T); }
	 | interface_declaration  { T.clear();T.pb("type_declaration");T.pb("interface_declaration");R.pb(T); }
	 ;
modifiers_opt
	 : eps  { T.clear();T.pb("modifiers_opt");T.pb("eps");R.pb(T); }
	 | modifiers  { T.clear();T.pb("modifiers_opt");T.pb("modifiers");R.pb(T); }
	 ;
modifiers
	 : modifier  { T.clear();T.pb("modifiers");T.pb("modifier");R.pb(T); }
	 | modifiers modifier  { T.clear();T.pb("modifiers");T.pb("modifiers");T.pb("modifier");R.pb(T); }
	 ;
modifier
	 : ABSTRACT  { T.clear();T.pb("modifier");T.pb("ABSTRACT");R.pb(T); }
	 | NEW  { T.clear();T.pb("modifier");T.pb("NEW");R.pb(T); }
	 | PRIVATE  { T.clear();T.pb("modifier");T.pb("PRIVATE");R.pb(T); }
	 | PROTECTED  { T.clear();T.pb("modifier");T.pb("PROTECTED");R.pb(T); }
	 | PUBLIC  { T.clear();T.pb("modifier");T.pb("PUBLIC");R.pb(T); }
	 ;
class_declaration
	 : modifiers_opt CLASS IDENTIFIER class_base_opt class_body comma_opt  { T.clear();T.pb("class_declaration");T.pb("modifiers_opt");T.pb("CLASS");T.pb("IDENTIFIER");T.pb("class_base_opt");T.pb("class_body");T.pb("comma_opt");R.pb(T); }
	 ;
class_base_opt
	 : eps  { T.clear();T.pb("class_base_opt");T.pb("eps");R.pb(T); }
	 | class_base  { T.clear();T.pb("class_base_opt");T.pb("class_base");R.pb(T); }
	 ;
class_base
	 : ':' class_type  { T.clear();T.pb("class_base");T.pb("\':\'");T.pb("class_type");R.pb(T); }
	 | ':' interface_type_list  { T.clear();T.pb("class_base");T.pb("\':\'");T.pb("interface_type_list");R.pb(T); }
	 | ':' class_type COMMA interface_type_list  { T.clear();T.pb("class_base");T.pb("\':\'");T.pb("class_type");T.pb("COMMA");T.pb("interface_type_list");R.pb(T); }
	 ;
interface_type_list
	 : type_name  { T.clear();T.pb("interface_type_list");T.pb("type_name");R.pb(T); }
	 | interface_type_list COMMA type_name  { T.clear();T.pb("interface_type_list");T.pb("interface_type_list");T.pb("COMMA");T.pb("type_name");R.pb(T); }
	 ;
class_body
	 : '{' class_member_declarations_opt '}'  { T.clear();T.pb("class_body");T.pb("\'{\'");T.pb("class_member_declarations_opt");T.pb("\'}\'");R.pb(T); }
	 ;
class_member_declarations_opt
	 : eps  { T.clear();T.pb("class_member_declarations_opt");T.pb("eps");R.pb(T); }
	 | class_member_declarations  { T.clear();T.pb("class_member_declarations_opt");T.pb("class_member_declarations");R.pb(T); }
	 ;
class_member_declarations
	 : class_member_declaration  { T.clear();T.pb("class_member_declarations");T.pb("class_member_declaration");R.pb(T); }
	 | class_member_declarations class_member_declaration  { T.clear();T.pb("class_member_declarations");T.pb("class_member_declarations");T.pb("class_member_declaration");R.pb(T); }
	 ;
class_member_declaration
	 : field_declaration  { T.clear();T.pb("class_member_declaration");T.pb("field_declaration");R.pb(T); }
	 | method_declaration  { T.clear();T.pb("class_member_declaration");T.pb("method_declaration");R.pb(T); }
	 | operator_declaration  { T.clear();T.pb("class_member_declaration");T.pb("operator_declaration");R.pb(T); }
	 | constructor_declaration  { T.clear();T.pb("class_member_declaration");T.pb("constructor_declaration");R.pb(T); }
	 | destructor_declaration  { T.clear();T.pb("class_member_declaration");T.pb("destructor_declaration");R.pb(T); }
	 | type_declaration  { T.clear();T.pb("class_member_declaration");T.pb("type_declaration");R.pb(T); }
	 ;
field_declaration
	 : modifiers_opt type variable_declarators ';'  { T.clear();T.pb("field_declaration");T.pb("modifiers_opt");T.pb("type");T.pb("variable_declarators");T.pb("\';\'");R.pb(T); }
	 ;
method_declaration
	 : method_header method_body  { T.clear();T.pb("method_declaration");T.pb("method_header");T.pb("method_body");R.pb(T); }
	 ;
method_header
	 : modifiers_opt type qualified_identifier '(' formal_parameter_list_opt ')'  { T.clear();T.pb("method_header");T.pb("modifiers_opt");T.pb("type");T.pb("qualified_identifier");T.pb("\'(\'");T.pb("formal_parameter_list_opt");T.pb("\')\'");R.pb(T); }
	 | modifiers_opt VOID qualified_identifier '(' formal_parameter_list_opt ')'  { T.clear();T.pb("method_header");T.pb("modifiers_opt");T.pb("VOID");T.pb("qualified_identifier");T.pb("\'(\'");T.pb("formal_parameter_list_opt");T.pb("\')\'");R.pb(T); }
	 ;
formal_parameter_list_opt
	 : eps  { T.clear();T.pb("formal_parameter_list_opt");T.pb("eps");R.pb(T); }
	 | formal_parameter_list  { T.clear();T.pb("formal_parameter_list_opt");T.pb("formal_parameter_list");R.pb(T); }
	 ;
method_body
	 : block  { T.clear();T.pb("method_body");T.pb("block");R.pb(T); }
	 | ';'  { T.clear();T.pb("method_body");T.pb("\';\'");R.pb(T); }
	 ;
formal_parameter_list
	 : formal_parameter  { T.clear();T.pb("formal_parameter_list");T.pb("formal_parameter");R.pb(T); }
	 | formal_parameter_list COMMA formal_parameter  { T.clear();T.pb("formal_parameter_list");T.pb("formal_parameter_list");T.pb("COMMA");T.pb("formal_parameter");R.pb(T); }
	 ;
formal_parameter
	 : fixed_parameter  { T.clear();T.pb("formal_parameter");T.pb("fixed_parameter");R.pb(T); }
	 ;
fixed_parameter
	 : parameter_modifier_opt type IDENTIFIER  { T.clear();T.pb("fixed_parameter");T.pb("parameter_modifier_opt");T.pb("type");T.pb("IDENTIFIER");R.pb(T); }
	 ;
parameter_modifier_opt
	 : eps  { T.clear();T.pb("parameter_modifier_opt");T.pb("eps");R.pb(T); }
	 | OUT  { T.clear();T.pb("parameter_modifier_opt");T.pb("OUT");R.pb(T); }
	 ;
operator_declaration
	 : modifiers_opt operator_declarator operator_body  { T.clear();T.pb("operator_declaration");T.pb("modifiers_opt");T.pb("operator_declarator");T.pb("operator_body");R.pb(T); }
	 ;
operator_declarator
	 : overloadable_operator_declarator  { T.clear();T.pb("operator_declarator");T.pb("overloadable_operator_declarator");R.pb(T); }
	 ;
overloadable_operator_declarator
	 : type OPERATOR overloadable_operator '(' type IDENTIFIER ')'  { T.clear();T.pb("overloadable_operator_declarator");T.pb("type");T.pb("OPERATOR");T.pb("overloadable_operator");T.pb("\'(\'");T.pb("type");T.pb("IDENTIFIER");T.pb("\')\'");R.pb(T); }
	 | type OPERATOR overloadable_operator '(' type IDENTIFIER COMMA type IDENTIFIER ')'  { T.clear();T.pb("overloadable_operator_declarator");T.pb("type");T.pb("OPERATOR");T.pb("overloadable_operator");T.pb("\'(\'");T.pb("type");T.pb("IDENTIFIER");T.pb("COMMA");T.pb("type");T.pb("IDENTIFIER");T.pb("\')\'");R.pb(T); }
	 ;
overloadable_operator
	 : '+'  { T.clear();T.pb("overloadable_operator");T.pb("\'+\'");R.pb(T); }
	 | '-'  { T.clear();T.pb("overloadable_operator");T.pb("\'-\'");R.pb(T); }
	 | '!'  { T.clear();T.pb("overloadable_operator");T.pb("\'!\'");R.pb(T); }
	 | '~'  { T.clear();T.pb("overloadable_operator");T.pb("\'~\'");R.pb(T); }
	 | PLUSPLUS  { T.clear();T.pb("overloadable_operator");T.pb("PLUSPLUS");R.pb(T); }
	 | MINUSMINUS  { T.clear();T.pb("overloadable_operator");T.pb("MINUSMINUS");R.pb(T); }
	 | TRUE  { T.clear();T.pb("overloadable_operator");T.pb("TRUE");R.pb(T); }
	 | FALSE  { T.clear();T.pb("overloadable_operator");T.pb("FALSE");R.pb(T); }
	 | '*'  { T.clear();T.pb("overloadable_operator");T.pb("\'*\'");R.pb(T); }
	 | '/'  { T.clear();T.pb("overloadable_operator");T.pb("\'/\'");R.pb(T); }
	 | '%'  { T.clear();T.pb("overloadable_operator");T.pb("\'%\'");R.pb(T); }
	 | '&'  { T.clear();T.pb("overloadable_operator");T.pb("\'&\'");R.pb(T); }
	 | '|'  { T.clear();T.pb("overloadable_operator");T.pb("\'|\'");R.pb(T); }
	 | '^'  { T.clear();T.pb("overloadable_operator");T.pb("\'^\'");R.pb(T); }
	 | LTLT  { T.clear();T.pb("overloadable_operator");T.pb("LTLT");R.pb(T); }
	 | GTGT  { T.clear();T.pb("overloadable_operator");T.pb("GTGT");R.pb(T); }
	 | EQEQ  { T.clear();T.pb("overloadable_operator");T.pb("EQEQ");R.pb(T); }
	 | NOTEQ  { T.clear();T.pb("overloadable_operator");T.pb("NOTEQ");R.pb(T); }
	 | '>'  { T.clear();T.pb("overloadable_operator");T.pb("\'>\'");R.pb(T); }
	 | '<'  { T.clear();T.pb("overloadable_operator");T.pb("\'<\'");R.pb(T); }
	 | GEQ  { T.clear();T.pb("overloadable_operator");T.pb("GEQ");R.pb(T); }
	 | LEQ  { T.clear();T.pb("overloadable_operator");T.pb("LEQ");R.pb(T); }
	 ;
constructor_declaration
	 : modifiers_opt constructor_declarator constructor_body  { T.clear();T.pb("constructor_declaration");T.pb("modifiers_opt");T.pb("constructor_declarator");T.pb("constructor_body");R.pb(T); }
	 ;
constructor_declarator
	 : IDENTIFIER '(' formal_parameter_list_opt ')' constructor_initializer_opt  { T.clear();T.pb("constructor_declarator");T.pb("IDENTIFIER");T.pb("\'(\'");T.pb("formal_parameter_list_opt");T.pb("\')\'");T.pb("constructor_initializer_opt");R.pb(T); }
	 ;
constructor_initializer_opt
	 : eps  { T.clear();T.pb("constructor_initializer_opt");T.pb("eps");R.pb(T); }
	 | constructor_initializer  { T.clear();T.pb("constructor_initializer_opt");T.pb("constructor_initializer");R.pb(T); }
	 ;
constructor_initializer
	 : ':' BASE '(' argument_list_opt ')'  { T.clear();T.pb("constructor_initializer");T.pb("\':\'");T.pb("BASE");T.pb("\'(\'");T.pb("argument_list_opt");T.pb("\')\'");R.pb(T); }
	 | ':' THIS '(' argument_list_opt ')'  { T.clear();T.pb("constructor_initializer");T.pb("\':\'");T.pb("THIS");T.pb("\'(\'");T.pb("argument_list_opt");T.pb("\')\'");R.pb(T); }
	 ;
destructor_declaration
	 : modifiers_opt '~' IDENTIFIER '(' ')' block  { T.clear();T.pb("destructor_declaration");T.pb("modifiers_opt");T.pb("\'~\'");T.pb("IDENTIFIER");T.pb("\'(\'");T.pb("\')\'");T.pb("block");R.pb(T); }
	 ;
operator_body
	 : block  { T.clear();T.pb("operator_body");T.pb("block");R.pb(T); }
	 | ';'  { T.clear();T.pb("operator_body");T.pb("\';\'");R.pb(T); }
	 ;
constructor_body
	 : block  { T.clear();T.pb("constructor_body");T.pb("block");R.pb(T); }
	 | ';'  { T.clear();T.pb("constructor_body");T.pb("\';\'");R.pb(T); }
	 ;
struct_declaration
	 : modifiers_opt STRUCT IDENTIFIER struct_interfaces_opt struct_body comma_opt  { T.clear();T.pb("struct_declaration");T.pb("modifiers_opt");T.pb("STRUCT");T.pb("IDENTIFIER");T.pb("struct_interfaces_opt");T.pb("struct_body");T.pb("comma_opt");R.pb(T); }
	 ;
struct_interfaces_opt
	 : eps  { T.clear();T.pb("struct_interfaces_opt");T.pb("eps");R.pb(T); }
	 | struct_interfaces  { T.clear();T.pb("struct_interfaces_opt");T.pb("struct_interfaces");R.pb(T); }
	 ;
struct_interfaces
	 : ':' interface_type_list  { T.clear();T.pb("struct_interfaces");T.pb("\':\'");T.pb("interface_type_list");R.pb(T); }
	 ;
struct_body
	 : '{' struct_member_declarations_opt '}'  { T.clear();T.pb("struct_body");T.pb("\'{\'");T.pb("struct_member_declarations_opt");T.pb("\'}\'");R.pb(T); }
	 ;
struct_member_declarations_opt
	 : eps  { T.clear();T.pb("struct_member_declarations_opt");T.pb("eps");R.pb(T); }
	 | struct_member_declarations  { T.clear();T.pb("struct_member_declarations_opt");T.pb("struct_member_declarations");R.pb(T); }
	 ;
struct_member_declarations
	 : struct_member_declaration  { T.clear();T.pb("struct_member_declarations");T.pb("struct_member_declaration");R.pb(T); }
	 | struct_member_declarations struct_member_declaration  { T.clear();T.pb("struct_member_declarations");T.pb("struct_member_declarations");T.pb("struct_member_declaration");R.pb(T); }
	 ;
struct_member_declaration
	 : field_declaration  { T.clear();T.pb("struct_member_declaration");T.pb("field_declaration");R.pb(T); }
	 | method_declaration  { T.clear();T.pb("struct_member_declaration");T.pb("method_declaration");R.pb(T); }
	 | operator_declaration  { T.clear();T.pb("struct_member_declaration");T.pb("operator_declaration");R.pb(T); }
	 | constructor_declaration  { T.clear();T.pb("struct_member_declaration");T.pb("constructor_declaration");R.pb(T); }
	 | type_declaration  { T.clear();T.pb("struct_member_declaration");T.pb("type_declaration");R.pb(T); }
	 ;
array_initializer
	 : '{' variable_initializer_list_opt '}'  { T.clear();T.pb("array_initializer");T.pb("\'{\'");T.pb("variable_initializer_list_opt");T.pb("\'}\'");R.pb(T); }
	 | '{' variable_initializer_list COMMA '}'  { T.clear();T.pb("array_initializer");T.pb("\'{\'");T.pb("variable_initializer_list");T.pb("COMMA");T.pb("\'}\'");R.pb(T); }
	 ;
variable_initializer_list_opt
	 : eps  { T.clear();T.pb("variable_initializer_list_opt");T.pb("eps");R.pb(T); }
	 | variable_initializer_list  { T.clear();T.pb("variable_initializer_list_opt");T.pb("variable_initializer_list");R.pb(T); }
	 ;
variable_initializer_list
	 : variable_initializer  { T.clear();T.pb("variable_initializer_list");T.pb("variable_initializer");R.pb(T); }
	 | variable_initializer_list COMMA variable_initializer  { T.clear();T.pb("variable_initializer_list");T.pb("variable_initializer_list");T.pb("COMMA");T.pb("variable_initializer");R.pb(T); }
	 ;
interface_declaration
	 : modifiers_opt INTERFACE IDENTIFIER interface_base_opt interface_body comma_opt  { T.clear();T.pb("interface_declaration");T.pb("modifiers_opt");T.pb("INTERFACE");T.pb("IDENTIFIER");T.pb("interface_base_opt");T.pb("interface_body");T.pb("comma_opt");R.pb(T); }
	 ;
interface_base_opt
	 : eps  { T.clear();T.pb("interface_base_opt");T.pb("eps");R.pb(T); }
	 | interface_base  { T.clear();T.pb("interface_base_opt");T.pb("interface_base");R.pb(T); }
	 ;
interface_base
	 : ':' interface_type_list  { T.clear();T.pb("interface_base");T.pb("\':\'");T.pb("interface_type_list");R.pb(T); }
	 ;
interface_body
	 : '{' interface_member_declarations_opt '}'  { T.clear();T.pb("interface_body");T.pb("\'{\'");T.pb("interface_member_declarations_opt");T.pb("\'}\'");R.pb(T); }
	 ;
interface_member_declarations_opt
	 : eps  { T.clear();T.pb("interface_member_declarations_opt");T.pb("eps");R.pb(T); }
	 | interface_member_declarations  { T.clear();T.pb("interface_member_declarations_opt");T.pb("interface_member_declarations");R.pb(T); }
	 ;
interface_member_declarations
	 : interface_member_declaration  { T.clear();T.pb("interface_member_declarations");T.pb("interface_member_declaration");R.pb(T); }
	 | interface_member_declarations interface_member_declaration  { T.clear();T.pb("interface_member_declarations");T.pb("interface_member_declarations");T.pb("interface_member_declaration");R.pb(T); }
	 ;
interface_member_declaration
	 : interface_method_declaration  { T.clear();T.pb("interface_member_declaration");T.pb("interface_method_declaration");R.pb(T); }
	 ;
interface_method_declaration
	 : new_opt type IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body  { T.clear();T.pb("interface_method_declaration");T.pb("new_opt");T.pb("type");T.pb("IDENTIFIER");T.pb("\'(\'");T.pb("formal_parameter_list_opt");T.pb("\')\'");T.pb("interface_empty_body");R.pb(T); }
	 | new_opt VOID IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body  { T.clear();T.pb("interface_method_declaration");T.pb("new_opt");T.pb("VOID");T.pb("IDENTIFIER");T.pb("\'(\'");T.pb("formal_parameter_list_opt");T.pb("\')\'");T.pb("interface_empty_body");R.pb(T); }
	 ;
new_opt
	 : eps  { T.clear();T.pb("new_opt");T.pb("eps");R.pb(T); }
	 | NEW  { T.clear();T.pb("new_opt");T.pb("NEW");R.pb(T); }
	 ;
interface_empty_body
	 : ';'  { T.clear();T.pb("interface_empty_body");T.pb("\';\'");R.pb(T); }
	 | '{' '}'  { T.clear();T.pb("interface_empty_body");T.pb("\'{\'");T.pb("\'}\'");R.pb(T); }
	 ;
eps
    : /* Nothing*/ {T.clear();T.pb("eps");T.pb("");R.pb(T);}
    ;


%%

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
