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

%%

/*(* grammar csharp4 *)*/
start :
      compilation_unit;
/*(*B.1.4 Tokens*) */
/*
 *token :
 *         IDENTIFIER
 *         | keyword
 *         | INTEGER_LITERAL
 *         | CHARACTER_LITERAL
 *         | STRING_LITERAL
 *         | operator_or_punctuator;
 */
/*(*B.1.7 Keywords*) */
/*
 *keyword :
 *        ABSTRACT
 *        | BASE
 *        | BOOL_TYPE
 *        | BREAK
 *        | CASE
 *        | CHAR_TYPE
 *        | CLASS
 *        | CONTINUE
 *        | DEFAULT
 *        | DO
 *        | ELSE
 *        | FALSE
 *        | FOR
 *        | FOREACH
 *        | GOTO
 *        | IF
 *        | IN
 *        | INT_TYPE
 *        | INTERFACE
 *        |NAMESPACE
 *        | NEW
 *        | NULL_TYPE
 *        | OBJECT
 *        | OPERATOR
 *        | OUT
 *        | OVERRIDE
 *        | PRIVATE
 *        | PROTECTED
 *        | PUBLIC
 *        | RETURN
 *        | SIZEOF
 *        | STRING_TYPE
 *        | STRUCT
 *        | SWITCH
 *        | THIS
 *        | TRUE
 *        | TYPEOF
 *        | USING
 *        | VIRTUAL
 *        | VOID
 *        | WHILE
 *        ;
 *
 */
/*(*B.1.8 Literals*)*/
literal :
	boolean_literal
	 | INTEGER_LITERAL
	 | CHARACTER_LITERAL
	 | STRING_LITERAL
	 | NULL_TYPE
	 ;
boolean_literal :
	TRUE
	 | FALSE
	 ;

/*(*B.1.9 Operators and punctuators*) */
/*
 *operator_or_punctuator :
 *        BLOCK_BEGIN
 *        | BLOCK_END
 *        | LEFT_BRACKET
 *        | RIGHT_BRACKET
 *        | '('
 *        | ')'
 *        | '.'
 *        | COMMA
 *        | ':'
 *        | ';'
 *        | '+'
 *        | '-'
 *        | '*'
 *        | '/'
 *        | '%'
 *        | '&'
 *        | '|'
 *        | '^'
 *        | '!'
 *        | '~'
 *        | '='
 *        | '<'
 *        | '>'
 *        | '?'
 *        | COLCOL
 *        | PLUSPLUS
 *        | MINUSMINUS
 *        | ANDAND
 *        | OROR
 *        | EQEQ
 *        | NOTEQ
 *        | LEQ
 *        | GEQ
 *        | PLUSEQ
 *        | MINUSEQ
 *        | STAREQ
 *        | DIVEQ
 *        | MODEQ
 *        | ANDEQ
 *        | OREQ
 *        | XOREQ
 *        | LTLT
 *        | LTLTEQ
 *        ;
 */
right_shift :
	GTGT
	;
right_shift_assignment :
			 GTGTEQ
			 ;

/*(*B.2 Syntactic grammar*) */

/*(*B.2.1 Basic concepts*) */
namespace_name :
	namespace_or_type_name;
type_name :
	namespace_or_type_name;
namespace_or_type_name :
	IDENTIFIER
	 | namespace_or_type_name '.' IDENTIFIER
	 | qualified_alias_member;

/*(*B.2.2 Types*) */
type :
	 value_type
	 | reference_type
value_type :
	struct_type;
struct_type :
	type_name
	 | simple_type;
simple_type :
	numeric_type
	 | BOOL_TYPE
	 ;
numeric_type :
	integral_type;
integral_type :
	 INT_TYPE
	| CHAR_TYPE
	;
reference_type :
	class_type
	 | interface_type
	 | array_type
	 ;
class_type :
	type_name
	 | OBJECT
	 | STRING_TYPE
	 ;
interface_type :
	type_name;

/*(*B.2.3 Variables*) */
variable_reference :
	expression
	;

/*(*B.2.4 Expressions*) */
argument_list :
	 argument
	 | argument_list COMMA argument
	 ;
argument :
	argument_name argument_value
	| argument_value
	;
argument_name :
	IDENTIFIER ':';
argument_value :
	expression
	 | OUT variable_reference
	 ;
primary_expression :
	primary_no_array_creation_expression
	 | array_creation_expression
	 ;
primary_no_array_creation_expression :
	literal
	 | simple_name
	 | parenthesized_expression
	 | member_access
	 | invocation_expression
	 | element_access
	 | this_access
	 | base_access
	 | object_creation_expression
	 | typeof_expression
	 | default_value_expression
	 ;
simple_name :
	IDENTIFIER
	;
parenthesized_expression :
	'(' expression ')'
	;
member_access :
	primary_expression '.' IDENTIFIER
	 | predefined_type '.' IDENTIFIER
	 | qualified_alias_member '.' IDENTIFIER
	 ;
predefined_type :
	BOOL_TYPE
	| CHAR_TYPE
	| INT_TYPE
	| OBJECT
	| STRING_TYPE
	;
invocation_expression :
	primary_expression '(' argument_list ')'
	| primary_expression '(' ')';
element_access :
	primary_no_array_creation_expression LEFT_BRACKET expression_list RIGHT_BRACKET
	;
expression_list :
	expression
	 | expression_list COMMA expression
	 ;
this_access :
	THIS
	;
base_access :
	BASE '.' IDENTIFIER
	| BASE LEFT_BRACKET expression_list RIGHT_BRACKET
	;
object_creation_expression :
	NEW type '(' argument_list ')' object_or_collection_initializer
	| NEW type '(' argument_list ')'
	| NEW type '(' ')' object_or_collection_initializer
	| NEW type '(' ')'
	| NEW type object_or_collection_initializer
	;
object_or_collection_initializer :
	object_initializer
	| collection_initializer
	;
object_initializer :
	BLOCK_BEGIN member_initializer_list BLOCK_END
	| BLOCK_BEGIN BLOCK_END
	| BLOCK_BEGIN member_initializer_list COMMA BLOCK_END
	;
member_initializer_list :
	member_initializer
	| member_initializer_list COMMA member_initializer
	;
member_initializer :
	IDENTIFIER '=' initializer_value
	;
initializer_value :
	expression
	 | object_or_collection_initializer
	 ;
collection_initializer :
	BLOCK_BEGIN element_initializer_list BLOCK_END
	 | BLOCK_BEGIN element_initializer_list COMMA BLOCK_END
	 ;
element_initializer_list :
	element_initializer
	 | element_initializer_list COMMA element_initializer
	 ;
element_initializer :
	non_assignment_expression
	 | BLOCK_BEGIN expression_list BLOCK_END
	 ;
array_creation_expression :
	NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET RANK_SPECIFIER array_initializer
	| NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET array_initializer
	| NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET RANK_SPECIFIER
	| NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET
	 | NEW array_type array_initializer
	 | NEW RANK_SPECIFIER array_initializer
	 ;
typeof_expression :
	TYPEOF '(' type ')'
	 | TYPEOF '(' VOID ')'
	 ;
default_value_expression :
	DEFAULT '(' type ')'
	;
unary_expression :
	primary_expression
	 | '+' unary_expression
	 | '-' unary_expression
	 | '!' unary_expression
	 | '~' unary_expression
	 | pre_increment_expression
	 | pre_decrement_expression
	 | cast_expression
	 ;
pre_increment_expression :
	PLUSPLUS unary_expression
	;
pre_decrement_expression :
	MINUSMINUS unary_expression
	;
cast_expression :
	'(' type ')' unary_expression
	;
multiplicative_expression :
	unary_expression
	 | multiplicative_expression '*' unary_expression
	 | multiplicative_expression '/' unary_expression
	 | multiplicative_expression '%' unary_expression
	 ;
additive_expression :
	multiplicative_expression
	 | additive_expression '+' multiplicative_expression
	 | additive_expression '-' multiplicative_expression
	 ;
shift_expression :
	additive_expression
	 | shift_expression LTLT additive_expression
	 | shift_expression right_shift additive_expression
	 ;
relational_expression :
	shift_expression
	 | relational_expression '<' shift_expression
	 | relational_expression '>' shift_expression
	 | relational_expression LEQ shift_expression
	 | relational_expression GEQ shift_expression
	 ;
equality_expression :
	relational_expression
	 | equality_expression EQEQ relational_expression
	 | equality_expression NOTEQ relational_expression
	 ;
and_expression :
	equality_expression
	 | and_expression '&' equality_expression
	 ;
exclusive_or_expression :
	and_expression
	 | exclusive_or_expression '^' and_expression
	 ;
inclusive_or_expression :
	exclusive_or_expression
	 | inclusive_or_expression '|' exclusive_or_expression
	 ;
conditional_and_expression :
	inclusive_or_expression
	 | conditional_and_expression ANDAND inclusive_or_expression
	 ;
conditional_or_expression :
	conditional_and_expression
	 | conditional_or_expression OROR conditional_and_expression
	 ;
conditional_expression :
	conditional_or_expression
	 | conditional_or_expression '?' expression ':' expression
	 ;
assignment :
	unary_expression assignment_operator expression
	;
assignment_operator :
	'='
	 | PLUSEQ
	 | MINUSEQ
	 | STAREQ
	 | DIVEQ
	 | MODEQ
	 | ANDEQ
	 | OREQ
	 | XOREQ
	 | LTLTEQ
	 | right_shift_assignment
	 ;
expression :
	non_assignment_expression
	 | assignment
	 ;
non_assignment_expression :
	conditional_expression
	;
constant_expression :
	expression
	;
boolean_expression :
	expression
	;


/*(*B.2.5 Statements*) */
statement :
	 declaration_statement
	 | embedded_statement
	 ;
embedded_statement :
	block
	 | empty_statement
	 | expression_statement
	 | selection_statement
	 | iteration_statement
	 | jump_statement
	 ;
block :
	BLOCK_BEGIN statement_list BLOCK_END
	| BLOCK_BEGIN BLOCK_END
	;
statement_list :
	statement
	 | statement_list statement
	 ;
empty_statement :
	';'
	;
declaration_statement :
	local_variable_declaration ';'
local_variable_declaration :
	local_variable_type local_variable_declarators
	;
local_variable_type :
	type
	;
local_variable_declarators :
	local_variable_declarator
	| local_variable_declarators COMMA local_variable_declarator
	;
local_variable_declarator :
	IDENTIFIER
	 | IDENTIFIER '=' local_variable_initializer
	 ;
local_variable_initializer :
	expression
	| array_initializer;
expression_statement :
	statement_expression ';'
	;
statement_expression :
	invocation_expression
	 | object_creation_expression
	 | assignment
	 | pre_increment_expression
	 | pre_decrement_expression
	 ;
selection_statement :
	if_statement
	 | switch_statement
	 ;
if_statement :
	IF '(' boolean_expression ')' embedded_statement
	 | IF '(' boolean_expression ')' embedded_statement ELSE embedded_statement
	 ;
switch_statement :
	SWITCH '(' expression ')' switch_block
	;
switch_block :
	BLOCK_BEGIN switch_sections BLOCK_END
	|BLOCK_BEGIN BLOCK_END
	;
switch_sections :
	switch_section
	 | switch_sections switch_section
	 ;
switch_section :
	switch_labels statement_list;
switch_labels :
	switch_label
	 | switch_labels switch_label;
switch_label :
	CASE constant_expression ':'
	 | DEFAULT ':'
	 ;

iteration_statement :
	while_statement
	 | do_statement
	 | for_statement
	 | foreach_statement
	 ;
while_statement :
	WHILE '(' boolean_expression ')' embedded_statement
	;
do_statement :
	DO embedded_statement WHILE '(' boolean_expression ')' ';'
	;
for_statement :
	FOR '(' for_initializer ';' for_condition ';' for_iterator ')' embedded_statement
	;
for_initializer :
	local_variable_declaration
	 | statement_expression_list
	 ;
for_condition :
	boolean_expression
	;
for_iterator :
	statement_expression_list
	;
statement_expression_list :
	statement_expression
	 | statement_expression_list COMMA statement_expression
	 ;
foreach_statement :
	FOREACH '(' local_variable_type IDENTIFIER IN expression ')' embedded_statement
	;
jump_statement :
	break_statement
	 | continue_statement
	 | goto_statement
	 | return_statement
	 ;
break_statement :
	BREAK ';'
	;
continue_statement :
	CONTINUE ';'
	;
goto_statement :
	GOTO IDENTIFIER ';'
	;
return_statement :
	RETURN expression ';'
	|RETURN ';'
	;

/*(*B.2.6 Namespaces;*) */
compilation_unit :
	 using_directives namespace_member_declarations
	 | namespace_member_declarations
	 | using_directive
	 ;
namespace_declaration :
	NAMESPACE qualified_identifier namespace_body ';'
	| NAMESPACE qualified_identifier namespace_body
	;
qualified_identifier :
	IDENTIFIER
	 | qualified_identifier '.' IDENTIFIER
	 ;
namespace_body :
	using_directives namespace_member_declarations
	| using_directives
	| namespace_member_declarations
	| using_directives namespace_body
	| namespace_member_declarations namespace_body
	;
using_directives :
	using_directive
	 | using_directives using_directive
	 ;
using_directive :
	using_alias_directive
	 | using_namespace_directive
	 ;
using_alias_directive :
	USING IDENTIFIER '=' namespace_or_type_name ';'
	;
using_namespace_directive :
	USING namespace_name ';'
	;
namespace_member_declarations :
	namespace_member_declaration
	 | namespace_member_declarations namespace_member_declaration
	 ;
namespace_member_declaration :
	namespace_declaration
	 | type_declaration
	 ;
type_declaration :
	class_declaration
	 | struct_declaration
	 | interface_declaration
	 ;
qualified_alias_member :
	IDENTIFIER COLCOL IDENTIFIER
	;

/*(*B.2.7 Classes;*) */
class_declaration :
	 class_modifiers CLASS IDENTIFIER class_base class_body ';'
	 |class_modifiers CLASS IDENTIFIER class_body ';'
	 ;
class_modifiers :
	class_modifier
	 | class_modifiers class_modifier;
class_modifier :
	NEW
	 | PUBLIC
	 | PROTECTED
	 | PRIVATE
	 | ABSTRACT
	 ;
class_base :
	':' class_type
	 | ':' interface_type_list
	 | ':' class_type COMMA interface_type_list
	 ;
interface_type_list :
	interface_type
	 | interface_type_list COMMA interface_type
	 ;
class_body :
	BLOCK_BEGIN class_member_declarations BLOCK_END
	| BLOCK_BEGIN BLOCK_END
	;
class_member_declarations :
	class_member_declaration
	 | class_member_declarations class_member_declaration
	 ;
class_member_declaration :
	 field_declaration
	 | method_declaration
	 | operator_declaration
	 | constructor_declaration
	 | destructor_declaration
	 | type_declaration
	 ;
field_declaration :
	type variable_declarators ';'
	|field_modifiers type variable_declarators ';'
	;
field_modifiers :
	field_modifier
	 | field_modifiers field_modifier
	 ;
field_modifier :
	NEW
	 | PUBLIC
	 | PROTECTED
	 | PRIVATE
	 ;
variable_declarators :
	variable_declarator
	 | variable_declarators COMMA variable_declarator
	 ;
variable_declarator :
	IDENTIFIER
	 | IDENTIFIER '=' variable_initializer
	 ;
variable_initializer :
	expression
	 | array_initializer
	 ;
method_declaration :
	method_header method_body
	;
method_header :
	 method_modifiers return_type member_name '(' formal_parameter_list ')'
	 | method_modifiers return_type member_name '(' ')'
	 ;
method_modifiers :
	method_modifier
	 | method_modifiers method_modifier
	 ;
method_modifier :
	NEW
	 | PUBLIC
	 | PROTECTED
	 | PRIVATE
	 | VIRTUAL
	 | OVERRIDE
	 | ABSTRACT
	 ;
return_type :
	type
	 | VOID
	 ;
member_name :
	IDENTIFIER
	 | interface_type '.' IDENTIFIER
	 ;
method_body :
	block
	 | ';'
	 ;
formal_parameter_list :
	fixed_parameters
	;
fixed_parameters :
	fixed_parameter
	 | fixed_parameters COMMA fixed_parameter
	 ;
fixed_parameter :
	parameter_modifier type IDENTIFIER default_argument
	| type IDENTIFIER default_argument
	| parameter_modifier type IDENTIFIER
	| type IDENTIFIER
	;
default_argument :
	'=' expression
	;
parameter_modifier :
	 OUT
	 | THIS
	 ;
operator_declaration :
	operator_modifiers operator_declarator operator_body
	;
operator_modifiers :
	operator_modifier
	 | operator_modifiers operator_modifier
	 ;
operator_modifier :
	PUBLIC
	;
operator_declarator :
	unary_operator_declarator
	 | binary_operator_declarator
	 ;
unary_operator_declarator :
	type OPERATOR overloadable_unary_operator '(' type IDENTIFIER ')'
	;
overloadable_unary_operator :
	'+'
	| '-'
	| '!'
	| '~'
	| PLUSPLUS
	| MINUSMINUS
	| TRUE
	| FALSE
	;
binary_operator_declarator :
	type OPERATOR overloadable_binary_operator '(' type IDENTIFIER COMMA type IDENTIFIER ')'
	;
overloadable_binary_operator :
	 | '*'
	 | '/'
	 | '%'
	 | '&'
	 | '|'
	 | '^'
	 | LTLT
	 | right_shift
	 | EQEQ
	 | NOTEQ
	 | '>'
	 | '<'
	 | LEQ
	 | GEQ
	 ;
operator_body :
	block
	 | ';'
	 ;
constructor_declaration :
	constructor_modifiers constructor_declarator constructor_body
	| constructor_declarator constructor_body
	;
constructor_modifiers :
	constructor_modifier
	 | constructor_modifiers constructor_modifier
	 ;
constructor_modifier :
	PUBLIC
	 | PROTECTED
	 | PRIVATE
	 ;
constructor_declarator :
	IDENTIFIER '(' formal_parameter_list ')' constructor_initializer
	| IDENTIFIER '(' ')' constructor_initializer
	| IDENTIFIER '(' formal_parameter_list ')'
	| IDENTIFIER '(' ')'
	;
constructor_initializer :
	':' BASE '(' argument_list ')'
	| ':' BASE '(' ')'
	| ':' THIS '(' argument_list ')'
	| ':' THIS '(' ')'
	;
constructor_body :
	block
	 | ';'
	 ;
destructor_declaration :
	 '~' IDENTIFIER '(' ')' destructor_body
	 ;
destructor_body :
	block
	 | ';'
	 ;

/*(*B.2.8 Structs*) */
struct_declaration :
	struct_modifiers STRUCT IDENTIFIER struct_interfaces struct_body ';'
	| struct_modifiers STRUCT IDENTIFIER struct_body ';'
	;
struct_modifiers :
	struct_modifier
	 | struct_modifiers struct_modifier
	 ;
struct_modifier :
	NEW
	 | PUBLIC
	 | PROTECTED
	 | PRIVATE
	 ;
struct_interfaces :
	':' interface_type_list
	;
struct_body :
	BLOCK_BEGIN struct_member_declarations BLOCK_END
	| BLOCK_BEGIN  BLOCK_END
	;
struct_member_declarations :
	struct_member_declaration
	 | struct_member_declarations struct_member_declaration
	 ;
struct_member_declaration :
	 field_declaration
	 | method_declaration
	 | operator_declaration
	 | constructor_declaration
	 | type_declaration
	 ;

/*(*B.2.9 Arrays*) */
array_type :
	non_array_type RANK_SPECIFIER
	;
non_array_type :
	type
	;
array_initializer :
	BLOCK_BEGIN variable_initializer_list BLOCK_END
	| BLOCK_BEGIN BLOCK_END
	| BLOCK_BEGIN variable_initializer_list COMMA BLOCK_END
	;
variable_initializer_list :
	variable_initializer
	| variable_initializer_list COMMA variable_initializer
	;


/*(*B.2.10 Interfaces*) */
interface_declaration :
	interface_modifiers INTERFACE IDENTIFIER interface_base interface_body ';'
	| interface_modifiers INTERFACE IDENTIFIER interface_body ';'
	;
interface_modifiers :
	interface_modifier
	 | interface_modifiers interface_modifier
	 ;
interface_modifier :
	NEW
	 | PUBLIC
	 | PROTECTED
	 | PRIVATE
	 ;
interface_base :
	':' interface_type_list
	;
interface_body :
	BLOCK_BEGIN interface_member_declarations BLOCK_END
	| BLOCK_BEGIN BLOCK_END
	;
interface_member_declarations :
	interface_member_declaration
	 | interface_member_declarations interface_member_declaration
	 ;
interface_member_declaration :
	interface_method_declaration
	;
interface_method_declaration :
	 NEW return_type IDENTIFIER '(' formal_parameter_list ')' ';'
	 | return_type IDENTIFIER '(' formal_parameter_list ')' ';'
	 | NEW return_type IDENTIFIER '(' ')' ';'
	 | return_type IDENTIFIER '(' ')' ';'
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
