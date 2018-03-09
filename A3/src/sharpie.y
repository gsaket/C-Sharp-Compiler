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


map<int, string> TknStr;
map<int, int> FreqToken;
vector<vector<string> > Rules;
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
%token <sval> BLOCK_BEGIN 370
%token <sval> BLOCK_END   371
%token <sval> STRING_LITERAL 372
%token <sval> COLCOL    373
%start compilation_unit
%%

/***** C.1.8 Literals *****/
literal
  : boolean_literal
  | INTEGER_LITERAL
  | CHARACTER_LITERAL
  | STRING_LITERAL
  | NULL_TYPE
  ;
boolean_literal
  : TRUE
  | FALSE
  ;
/********** C.2 Syntactic grammar **********/

/***** C.2.1 Basic concepts *****/
namespace_name
  : qualified_identifier
  ;
type_name
  : qualified_identifier
  ;
/***** C.2.2 Types *****/
type
  : non_array_type
  | array_type
  ;
non_array_type
  : simple_type
  | type_name
  ;
simple_type
  : primitive_type
  | class_type
  ;
primitive_type
  : numeric_type
  | BOOL_TYPE
  ;
numeric_type
  : integral_type
  ;
integral_type
  :  INT_TYPE
  | CHAR_TYPE
  ;
class_type
  : OBJECT 
  | STRING_TYPE
  ;
array_type
  : array_type rank_specifier
  | simple_type rank_specifier
  | qualified_identifier rank_specifier
  ;
rank_specifier
  : RANK_SPECIFIER
  ;
rank_specifiers_opt
  : 
  | rank_specifier
  ;
/***** C.2.3 Variables *****/
variable_reference
  : expression
  ;
/***** C.2.4 Expressions *****/
argument_list
  : argument
  | argument_list COMMA argument
  ;
argument
  : expression
  | OUT variable_reference
  ;
primary_expression
  : parenthesized_expression
  | primary_expression_no_parenthesis
  ;
primary_expression_no_parenthesis
  : literal
  | array_creation_expression
  | member_access
  | invocation_expression
  | element_access
  | this_access
  | base_access
  | new_expression
  | typeof_expression
  ;
parenthesized_expression
  : '(' expression ')'
  ;
member_access
  : primary_expression '.' IDENTIFIER
  | primitive_type '.' IDENTIFIER
  | class_type '.' IDENTIFIER
  ;
invocation_expression
  : primary_expression_no_parenthesis '(' argument_list_opt ')'
  | qualified_identifier '(' argument_list_opt ')'
  ;
argument_list_opt
  : /* Nothing */
  | argument_list
  ;
element_access
  : primary_expression LEFT_BRACKET expression_list RIGHT_BRACKET
  | qualified_identifier LEFT_BRACKET expression_list RIGHT_BRACKET
  ;
expression_list
  : expression
  | expression_list COMMA expression
  ;
this_access
  : THIS
  ;
base_access
  : BASE '.' IDENTIFIER
  | BASE LEFT_BRACKET expression_list RIGHT_BRACKET
  ;
new_expression
  : object_creation_expression
  ;
object_creation_expression
  : NEW type '(' argument_list_opt ')'
  ;
array_creation_expression
  : NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET rank_specifiers_opt array_initializer_opt
  | NEW array_type array_initializer
  ;
array_initializer_opt
  : /* Nothing */
  | array_initializer
  ;
typeof_expression
  : TYPEOF '(' type ')'
  | TYPEOF '(' VOID ')'
  ;
addressof_expression
  : '&' unary_expression
  ;
postfix_expression
  : primary_expression
  | qualified_identifier
  ;
unary_expression_not_plusminus
  : postfix_expression
  | '!' unary_expression
  | '~' unary_expression
  | cast_expression
  ;
pre_increment_expression
  : PLUSPLUS unary_expression
  ;
pre_decrement_expression
  : MINUSMINUS unary_expression
  ;
unary_expression
  : unary_expression_not_plusminus
  | '+' unary_expression
  | '-' unary_expression
  | '*' unary_expression
  | pre_increment_expression
  | pre_decrement_expression
  | addressof_expression
  ;
cast_expression
  : '(' expression ')' unary_expression_not_plusminus
  | '(' multiplicative_expression '*' ')' unary_expression 
  | '(' qualified_identifier rank_specifier type_quals_opt ')' unary_expression  
  | '(' primitive_type type_quals_opt ')' unary_expression
  | '(' class_type type_quals_opt ')' unary_expression
  | '(' VOID type_quals_opt ')' unary_expression
  ;
type_quals_opt
  : /* Nothing */
  | type_quals
  ;
type_quals
  : type_qual
  | type_quals type_qual
  ;
type_qual 
  : rank_specifier 
  | '*'
  ;
multiplicative_expression
  : unary_expression
  | multiplicative_expression '*' unary_expression  
  | multiplicative_expression '/' unary_expression
  | multiplicative_expression '%' unary_expression
  ;
additive_expression
  : multiplicative_expression
  | additive_expression '+' multiplicative_expression
  | additive_expression '-' multiplicative_expression
  ;
shift_expression
  : additive_expression 
  | shift_expression LTLT additive_expression
  | shift_expression GTGT additive_expression
  ;
relational_expression
  : shift_expression
  | relational_expression '<' shift_expression
  | relational_expression '>' shift_expression
  | relational_expression LEQ shift_expression
  | relational_expression GEQ shift_expression
  ;
equality_expression
  : relational_expression
  | equality_expression EQEQ relational_expression
  | equality_expression NOTEQ relational_expression
  ;
and_expression
  : equality_expression
  | and_expression '&' equality_expression
  ;
exclusive_or_expression
  : and_expression
  | exclusive_or_expression '^' and_expression
  ;
inclusive_or_expression
  : exclusive_or_expression
  | inclusive_or_expression '|' exclusive_or_expression
  ;
conditional_and_expression
  : inclusive_or_expression
  | conditional_and_expression ANDAND inclusive_or_expression
  ;
conditional_or_expression
  : conditional_and_expression
  | conditional_or_expression OROR conditional_and_expression
  ;
conditional_expression
  : conditional_or_expression
  | conditional_or_expression '?' expression ':' expression
  ;
assignment
: unary_expression assignment_operator expression
  ;
assignment_operator
  : '=' 
  | PLUSEQ 
  | MINUSEQ 
  | STAREQ 
  | DIVEQ 
  | MODEQ 
  | XOREQ 
  | ANDEQ 
  | OREQ 
  | GTGTEQ 
  | LTLTEQ 
  ;
expression
  : conditional_expression
  | assignment
  ;
constant_expression
  : expression
  ;
boolean_expression
  : expression
  ;
/***** C.2.5 Statements *****/
statement
  : declaration_statement
  | embedded_statement
  ;
embedded_statement
  : block
  | empty_statement
  | expression_statement
  | selection_statement
  | iteration_statement
  | jump_statement
  ;
block
  : '{' statement_list_opt '}'
  ;
statement_list_opt
  : /* Nothing */
  | statement_list
  ;

statement_list
  : statement
  | statement_list statement
  ;
empty_statement
  : ';'
  ;
declaration_statement
  : local_variable_declaration ';'
  ;
local_variable_declaration
  : type variable_declarators
  ;
variable_declarators
  : variable_declarator
  | variable_declarators COMMA variable_declarator
  ;
variable_declarator
  : IDENTIFIER
  | IDENTIFIER '=' variable_initializer
  ;
variable_initializer
  : expression
  | array_initializer
  ;
expression_statement
  : statement_expression ';'
  ;
statement_expression
  : invocation_expression
  | object_creation_expression
  | assignment
  | pre_increment_expression
  | pre_decrement_expression
  ;
selection_statement
  : if_statement
  | switch_statement
  ;
if_statement
  : IF '(' boolean_expression ')' embedded_statement
  | IF '(' boolean_expression ')' embedded_statement ELSE embedded_statement
  ;
switch_statement
  : SWITCH '(' expression ')' switch_block
  ;
switch_block
  : '{' switch_sections_opt '}'
  ;
switch_sections_opt
  : /* Nothing */
  | switch_sections
  ;
switch_sections
  : switch_section
  | switch_sections switch_section
  ;
switch_section
  : switch_labels statement_list
  ;
switch_labels
  : switch_label
  | switch_labels switch_label
  ;
switch_label
  : CASE constant_expression ':'
  | DEFAULT ':'
  ;
iteration_statement
  : while_statement
  | do_statement
  | for_statement
  | foreach_statement
  ;
while_statement
  : WHILE '(' boolean_expression ')' embedded_statement
  ;
do_statement
  : DO embedded_statement WHILE '(' boolean_expression ')' ';'
  ;
for_statement
  : FOR '(' for_initializer_opt ';' for_condition_opt ';' for_iterator_opt ')' embedded_statement
  ;
for_initializer_opt
  : /* Nothing */
  | for_initializer
  ;
for_condition_opt
  : /* Nothing */
  | for_condition
  ;
for_iterator_opt
  : /* Nothing */
  | for_iterator
  ;
for_initializer
  : local_variable_declaration
  | statement_expression_list
  ;
for_condition
  : boolean_expression
  ;
for_iterator
  : statement_expression_list
  ;
statement_expression_list
  : statement_expression
  | statement_expression_list COMMA statement_expression
  ;
foreach_statement
  : FOREACH '(' type IDENTIFIER IN expression ')' embedded_statement
  ;
jump_statement
  : break_statement
  | continue_statement
  | goto_statement
  | return_statement
  ;
break_statement
  : BREAK ';'
  ;
continue_statement
  : CONTINUE ';'
  ;
goto_statement
  : GOTO IDENTIFIER ';'
  ;
return_statement
  : RETURN expression_opt ';'
  ;
expression_opt
  : /* Nothing */
  | expression
  ;

/*(*B.2.6 Namespaces;*) */
compilation_unit
  : using_directives_opt 
  | using_directives_opt namespace_member_declarations
  ;
using_directives_opt
  : /* Nothing */
  | using_directives
  ;
namespace_member_declarations_opt
  : /* Nothing */
  | namespace_member_declarations
  ;
namespace_declaration
  : NAMESPACE qualified_identifier namespace_body comma_opt
  ;
comma_opt
  : /* Nothing */
  | ';'
  ;
qualified_identifier
  : IDENTIFIER
  | qualifier IDENTIFIER
  ;
qualifier
  : IDENTIFIER '.' 
  | qualifier IDENTIFIER '.' 
  ;
namespace_body
  : '{' using_directives_opt namespace_member_declarations_opt '}'
  ;
using_directives
  : using_directive
  | using_directives using_directive
  ;
using_directive
  : using_alias_directive
  | using_namespace_directive
  ;
using_alias_directive
  : USING IDENTIFIER '=' qualified_identifier ';'
  ;
using_namespace_directive
  : USING namespace_name ';'
  ;
namespace_member_declarations
  : namespace_member_declaration
  | namespace_member_declarations namespace_member_declaration
  ;
namespace_member_declaration
  : namespace_declaration
  | type_declaration
  ;
type_declaration
  : class_declaration
  | struct_declaration
  | interface_declaration
  ;

modifiers_opt
  : /* Nothing */
  | modifiers
  ;
modifiers
  : modifier
  | modifiers modifier
  ;
modifier
  : ABSTRACT
  | NEW
  | PRIVATE
  | PROTECTED
  | PUBLIC
  ;
/***** C.2.6 Classes *****/
class_declaration
  : modifiers_opt CLASS IDENTIFIER class_base_opt class_body comma_opt
  ;
class_base_opt
  : /* Nothing */
  | class_base
  ;
class_base
  : ':' class_type
  | ':' interface_type_list
  | ':' class_type COMMA interface_type_list
  ;
interface_type_list
  : type_name
  | interface_type_list COMMA type_name
  ;
class_body
  : '{' class_member_declarations_opt '}'
  ;
class_member_declarations_opt
  : /* Nothing */
  | class_member_declarations
  ;
class_member_declarations
  : class_member_declaration
  | class_member_declarations class_member_declaration
  ;
class_member_declaration
  : field_declaration
  | method_declaration
  | operator_declaration
  | constructor_declaration
  | destructor_declaration
  | type_declaration
  ;
field_declaration
  : modifiers_opt type variable_declarators ';'
  ;
method_declaration
  : method_header method_body
  ;
method_header
  : modifiers_opt type qualified_identifier '(' formal_parameter_list_opt ')'
  | modifiers_opt VOID qualified_identifier '(' formal_parameter_list_opt ')'
  ;
formal_parameter_list_opt
  : /* Nothing */
  | formal_parameter_list
  ;
method_body
  : block
  | ';'
  ;
formal_parameter_list
  : formal_parameter
  | formal_parameter_list COMMA formal_parameter
  ;
formal_parameter
  : fixed_parameter
  ;
fixed_parameter
  : parameter_modifier_opt type IDENTIFIER
  ;
parameter_modifier_opt
  : /* Nothing */
  | OUT
  ;
/* Widen operator_declaration to make modifiers optional */
operator_declaration
  : modifiers_opt operator_declarator operator_body
  ;
operator_declarator
  : overloadable_operator_declarator
  ;
overloadable_operator_declarator
  : type OPERATOR overloadable_operator '(' type IDENTIFIER ')'
  | type OPERATOR overloadable_operator '(' type IDENTIFIER COMMA type IDENTIFIER ')'
  ;
overloadable_operator
  : '+' 
  | '-' 
  | '!' 
  | '~' 
  | PLUSPLUS 
  | MINUSMINUS 
  | TRUE 
  | FALSE
  | '*' 
  | '/' 
  | '%' 
  | '&' 
  | '|' 
  | '^' 
  | LTLT 
  | GTGT 
  | EQEQ 
  | NOTEQ 
  | '>' 
  | '<' 
  | GEQ 
  | LEQ
  ;
constructor_declaration
  : modifiers_opt constructor_declarator constructor_body
  ;
constructor_declarator
  : IDENTIFIER '(' formal_parameter_list_opt ')' constructor_initializer_opt
  ;
constructor_initializer_opt
  : /* Nothing */
  | constructor_initializer
  ;
constructor_initializer
  : ':' BASE '(' argument_list_opt ')'
  | ':' THIS '(' argument_list_opt ')'
  ;
/* Widen from unsafe_opt to modifiers_opt */
destructor_declaration
  : modifiers_opt '~' IDENTIFIER '(' ')' block
  ;
operator_body
  : block
  | ';'
  ;
constructor_body /*** Added by AJ - same as method_body ***/
  : block
  | ';'
  ;

/***** C.2.7 Structs *****/
struct_declaration
  : modifiers_opt STRUCT IDENTIFIER struct_interfaces_opt struct_body comma_opt
  ;
struct_interfaces_opt
  : /* Nothing */
  | struct_interfaces
  ;
struct_interfaces
  : ':' interface_type_list
  ;
struct_body
  : '{' struct_member_declarations_opt '}'
  ;
struct_member_declarations_opt
  : /* Nothing */
  | struct_member_declarations
  ;
struct_member_declarations
  : struct_member_declaration
  | struct_member_declarations struct_member_declaration
  ;
struct_member_declaration
  : field_declaration
  | method_declaration
  | operator_declaration
  | constructor_declaration
  | type_declaration
  ;

/***** C.2.8 Arrays *****/
array_initializer
  : '{' variable_initializer_list_opt '}'
  | '{' variable_initializer_list COMMA '}'
  ;
variable_initializer_list_opt
  : /* Nothing */
  | variable_initializer_list
  ;
variable_initializer_list
  : variable_initializer
  | variable_initializer_list COMMA variable_initializer
  ;

/***** C.2.9 Interfaces *****/
interface_declaration
  : modifiers_opt INTERFACE IDENTIFIER interface_base_opt interface_body comma_opt
  ;
interface_base_opt
  : /* Nothing */
  | interface_base
  ;
interface_base
  : ':' interface_type_list
  ;
interface_body
  : '{' interface_member_declarations_opt '}'
  ;
interface_member_declarations_opt
  : /* Nothing */
  | interface_member_declarations
  ;
interface_member_declarations
  : interface_member_declaration
  | interface_member_declarations interface_member_declaration
  ;
interface_member_declaration
  : interface_method_declaration
  ;
/* inline return_type to avoid conflict with interface_property_declaration */
interface_method_declaration
  : new_opt type IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body
  | new_opt VOID IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body
  ;
new_opt
  : /* Nothing */
  | NEW
  ;
/* mono seems to allow this */
interface_empty_body
  : ';'
  | '{' '}'
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
TknStr[BLOCK_BEGIN]="BLOCK_BEGIN";
TknStr[BLOCK_END]="BLOCK_END";
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
	cout << "EEK, parse error!  Message: " << s << endl;
	exit(-1);
}
