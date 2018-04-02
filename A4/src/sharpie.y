%{
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



string tmpLbl[100]; // memoizing labels for switch case
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


%}

%union {
	int ival;
	float fval;
	char* sval;
	Attr* NT;
}


%token <sval> INTEGER_LITERAL    300
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


%type <NT> literal boolean_literal namespace_name type_name type non_array_type simple_type primitive_type numeric_type integral_type 
%type <NT> class_type array_type rank_specifier rank_specifiers_opt variable_reference argument_list argument primary_expression primary_expression_no_parenthesis parenthesized_expression 
%type <NT> member_access invocation_expression argument_list_opt element_access expression_list this_access base_access new_expression object_creation_expression array_creation_expression 
%type <NT> array_initializer_opt typeof_expression addressof_expression postfix_expression unary_expression_not_plusminus pre_increment_expression pre_decrement_expression unary_expression cast_expression type_quals_opt 
%type <NT> type_quals type_qual multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression 
%type <NT> conditional_and_expression conditional_or_expression conditional_expression assignment assignment_operator expression constant_expression boolean_expression statement embedded_statement 
%type <NT> block statement_list_opt statement_list empty_statement declaration_statement local_variable_declaration variable_declarators variable_declarator variable_initializer expression_statement 
%type <NT> statement_expression selection_statement if_statement switch_statement switch_block switch_sections_opt switch_sections switch_section switch_labels switch_label 
%type <NT> iteration_statement while_statement do_statement for_statement for_initializer_opt for_condition_opt for_iterator_opt for_initializer for_condition for_iterator 
%type <NT> statement_expression_list foreach_statement jump_statement break_statement continue_statement goto_statement return_statement expression_opt compilation_unit using_directives_opt 
%type <NT> namespace_member_declarations_opt namespace_declaration comma_opt qualified_identifier qualifier namespace_body using_directives using_directive using_alias_directive using_namespace_directive 
%type <NT> namespace_member_declarations namespace_member_declaration type_declaration modifiers_opt modifiers modifier class_declaration class_base_opt class_base interface_type_list 
%type <NT> class_body class_member_declarations_opt class_member_declarations class_member_declaration field_declaration method_declaration method_header formal_parameter_list_opt method_body formal_parameter_list 
%type <NT> formal_parameter fixed_parameter parameter_modifier_opt operator_declaration operator_declarator overloadable_operator_declarator overloadable_operator constructor_declaration constructor_declarator constructor_initializer_opt 
%type <NT> constructor_initializer destructor_declaration operator_body constructor_body struct_declaration struct_interfaces_opt struct_interfaces struct_body struct_member_declarations_opt struct_member_declarations 
%type <NT> struct_member_declaration array_initializer variable_initializer_list_opt variable_initializer_list interface_declaration interface_base_opt interface_base interface_body interface_member_declarations_opt interface_member_declarations 
%type <NT> interface_member_declaration interface_method_declaration new_opt interface_empty_body begin_scope eps

%start compilation_unit
%%

literal
  : boolean_literal {
    $$=$1;
  }
  | INTEGER_LITERAL {
    $$=new Attr();
    $$->place=string($1);
  }
  | CHARACTER_LITERAL {
    $$=new Attr();
    $$->place=string($1);
  }
  | STRING_LITERAL{
    $$=new Attr();
    $$->place=string($1);
  }
  | NULL_TYPE{
    $$=new Attr();
    $$->place=string($1);
  }
  ;
boolean_literal
  : TRUE {
    $$=new Attr();
    ($$->place)="1";
  }
  | FALSE {
    $$=new Attr();
    ($$->place)="0";
  }
  ;
namespace_name
  : qualified_identifier {
    $$=$1;
  }
  ;
type_name
  : qualified_identifier {
    $$=$1;
  }
  ;
type
  : non_array_type {
    $$=$1;
  }
  | array_type {
    $$=$1;
  }
  ;
non_array_type
  : simple_type {
    $$=$1;
  }
  | type_name {
    $$=$1;
  }
  ;
simple_type
  : primitive_type {
    $$=$1;
  }
  | class_type
  ;
primitive_type
  : numeric_type {
    $$=$1;
  }
  | BOOL_TYPE {
    $$=new Attr();
    $$->type="bool";
    $$->width=1;
  }
  ;
numeric_type
  : integral_type {
    $$=$1;
  }
  ;
integral_type
  :  INT_TYPE {
    $$=new Attr();
    $$->type="int";
    $$->width=4;
  }
  | CHAR_TYPE {
    $$=new Attr();
    $$->type="char";
    $$->width=1;
  }
  ;
class_type
  : OBJECT
  | STRING_TYPE
  ;
array_type
  : array_type rank_specifier
  | simple_type rank_specifier {
    $$=new Attr();
    $$->isarray=true;
    $$->elem=$1;
  }
  | qualified_identifier rank_specifier
  ;
rank_specifier
  : RANK_SPECIFIER
  ;
rank_specifiers_opt
  : eps
  | rank_specifier
  ;
variable_reference
  : expression
  ;
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
  : eps
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
  : eps
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
  | qualified_identifier {
    $$ = $1;
  }
  ;
unary_expression_not_plusminus
  : postfix_expression {
    $$ = $1;
  }
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
  : unary_expression_not_plusminus {
    $$=$1;
  }
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
  : eps
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
  : unary_expression {
    $$ = $1;
  }
  | multiplicative_expression '*' unary_expression {
    translate($$,$1,$3,"*");
  }
  | multiplicative_expression '/' unary_expression {
    translate($$,$1,$3,"/");
  }
  | multiplicative_expression '%' unary_expression{
    translate($$,$1,$3,"%");
  }
  ;
additive_expression
  : multiplicative_expression {
    $$=$1;
  }
  | additive_expression '+' multiplicative_expression {
    translate($$,$1,$3,"+");
    /*
     *for(int i=0;i<(int)(($$->code).size());i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"----"<<endl;
     */
  }
  | additive_expression '-' multiplicative_expression{
    translate($$,$1,$3,"-");
  }
  ;
shift_expression
  : additive_expression {
    $$ = $1;
  }
  | shift_expression LTLT additive_expression{
    translate($$,$1,$3,"<<");
  }
  | shift_expression GTGT additive_expression{
    translate($$,$1,$3,">>");
  }
  ;
relational_expression
  : shift_expression {
    $$ = $1;
  }
  | relational_expression '<' shift_expression{
    translate($$,$1,$3,"<");
  }
  | relational_expression '>' shift_expression{
    translate($$,$1,$3,">");
  }
  | relational_expression LEQ shift_expression{
    translate($$,$1,$3,"<=");
  }
  | relational_expression GEQ shift_expression{
    translate($$,$1,$3,">=");
  }
  ;
equality_expression
  : relational_expression {
    $$=$1;
  }
  | equality_expression EQEQ relational_expression{
    translate($$,$1,$3,"==");
  }
  | equality_expression NOTEQ relational_expression{
    translate($$,$1,$3,"!=");
  }
  ;
and_expression
  : equality_expression{
    $$=$1;
  }
  | and_expression '&' equality_expression{
    translate($$,$1,$3,"&");
  }
  ;
exclusive_or_expression
  : and_expression{
    $$=$1;
  }
  | exclusive_or_expression '^' and_expression{
    translate($$,$1,$3,"^");
  }
  ;
inclusive_or_expression
  : exclusive_or_expression{
    $$=$1;
  }
  | inclusive_or_expression '|' exclusive_or_expression{
    translate($$,$1,$3,"|");
  }
  ;
conditional_and_expression
  : inclusive_or_expression {
    $$=$1;
  }
  | conditional_and_expression ANDAND inclusive_or_expression{
    translate($$,$1,$3,"&&");
  }
  ;
conditional_or_expression
  : conditional_and_expression{
    $$=$1;
  }
  | conditional_or_expression OROR conditional_and_expression{
    translate($$,$1,$3,"||");
  }
  ;
conditional_expression
  : conditional_or_expression{
    $$=$1;
  }
  | conditional_or_expression '?' expression ':' expression{
    // TODO
  }
  ;
assignment
: unary_expression assignment_operator expression {
  // TODO: handle others later
    $$=new Attr();
  /*if(CurTable->lookup($1->place)){*/
    $$->place = $1->place;
    Combine($$->code, $3->code, $1->code);
    string code_= getTAC(2,"=",$1->place,$3->place);
    ($$->code).pb(code_);
    /*cout<<"assign->->->"<<endl;*/
    /*cout<<code_<<endl;*/
    /*cout<<"<-<-<-assign"<<endl;*/
  /*
   *}else{
   *  cerr<<"ERROR: Symbol "<<($1->place)<<" used without declaration."<<endl;
   *  exit(0);
   *}
   */
}
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
  : conditional_expression{
    $$=$1;
  }
  | assignment {
    $$=$1;
  }
  ;
constant_expression
  : expression {
    $$=$1; // check if variable is altered
  }
  ;
boolean_expression
  : expression {
    $$=$1;
  }
  ;
statement
  : declaration_statement {
    /*cout<<"statement ->declaration_statement asda"<<endl;*/
    $$=$1;
  }
  | embedded_statement {
    /*cout<<"statement ->embedded_statement asda"<<endl;*/
    $$=$1;
  }
  ;
embedded_statement
  : block {
    $$=$1;
  }
  | empty_statement {
    $$=$1;
  }
  | expression_statement {
    /*cout<<"embedded_statement->expression_statement"<<endl;*/
    $$=$1;
  }
  | selection_statement {
    $$=$1;
  }
  | iteration_statement {
    $$=$1;
  }
  | jump_statement {
    $$=$1;
  }
  ;

block
  : '{' begin_scope statement_list_opt '}'{
  /*: '{' statement_list_opt '}'{*/
    $$ = $2;
    /*cout<<"dgdfgg"<<endl;*/
    EndScope();
    /*cout<<"Enddgdfgg"<<endl;*/
  }
  ;
statement_list_opt
  : eps {
    $$=$1;
  }
  | statement_list {
    /*cout<<"statement_list_opt"<<endl;*/
    $$ = $1;
  }
  ;

statement_list
  : statement {
    /*cout<<"statement_list to statement"<<endl;*/
    $$ = $1;
  }
  | statement_list statement {
    /*cout<<"statement_list to statement_list statement "<<endl;*/
    $$=$1;
	Combine($$->code, $1->code, $2->code);
    /*cout<<"statement_list to statement 22222"<<endl;*/
  }
  ;
empty_statement
  : ';' {
    $$ = new Attr();
    /*cout<<"hello there"<<endl;*/
    //TODO
  }
  ;
declaration_statement
  : local_variable_declaration ';' {
    $$=$1;
  }
  ;
local_variable_declaration
  : type variable_declarators {
    /*cout<<"local_variable_declaration asdad"<<endl;*/
    $$=new Attr();
    if($1->isarray == false){
	for(int i=0;i<(int)($2->var_dec).size();i++){
	  Attr * CurVar = ($2->var_dec)[i];
	  // insert CurVar->place into table
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    Combine($$->code,$$->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ($$->code).pb(code_);
	  }
	}
    }else{
       for(int i=0;i<(int)($2->var_dec).size();i++){
	  Attr * CurVar = ($2->var_dec)[i];
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    int ArrayLength=(CurVarInit->init_list).size();
	    string code_="array,"+($1->elem)->type+","+to_string(ArrayLength)+","+CurVar->place;
	    ($$->code).pb(code_);
	    for(int j=0;j<(int)(CurVarInit->init_list).size();j++){
	      Attr * CurVarInitElem = (CurVarInit->init_list)[j];
	      int ElemWidth=($1->elem)->width;
	      // TODO:update width for this array struct=len*Elemwidth
	      code_="update,"+(CurVarInitElem->place)+","+(CurVar->place)+","+to_string(ElemWidth*j);
	      Combine($$->code,$$->code,CurVarInitElem->code);
	      ($$->code).pb(code_);
	    }
	  }else{
	    // default length 100 size array
	    string code_="array,"+($1->elem)->type+",100,"+CurVar->place;
	    ($$->code).pb(code_);
	  }
	}
     }
    /*
     *for(auto it : ($$->code))
     *  cout<<it<<endl;
     *cout<<"******"<<endl;
     */
  }
  ;
variable_declarators
  : variable_declarator {
    $$=$1;
    ($$->var_dec).pb($1);
  }
  | variable_declarators COMMA variable_declarator {
    $$=$1;
    ($$->var_dec).pb($3);
  }
  ;
variable_declarator
  : IDENTIFIER {
    $$=new Attr();
    $$->place = string($1);
    $$->init = NULL;
    $$->line=yylineno;
  }
  | IDENTIFIER '=' variable_initializer {
    $$=new Attr();
    $$->place = string($1);
    $$->init = $3;
    $$->line=yylineno;
  }
  ;
variable_initializer
  : expression {
    $$=$1;
  }
  | array_initializer {
    $$=$1;
  }
  ;
expression_statement
  : statement_expression ';' {
    /*cout<<"expression_statement -> statement_expression"<<endl;*/
    $$=$1;
  }
  ;
statement_expression
  : invocation_expression {
    /*cout<<"invocation_expression"<<endl;*/
    $$=$1;
  }
  | object_creation_expression {
    $$=$1;
  }
  | assignment {
    $$=$1;
  }
  | pre_increment_expression {
    $$=$1;
  }
  | pre_decrement_expression {
    $$=$1;
  }
  ;
selection_statement
  : if_statement {
    $$=$1;
  }
  | switch_statement {
    $$=$1;
  }
  ;
if_statement
  : IF '(' boolean_expression ')' embedded_statement {
    string ltrue=getLabel();
    string lfalse=getLabel();
    $$=new Attr();
    $$->code=$3->code;
    string code_="ifgoto,==,1,"+($3->place)+","+ltrue;
    ($$->code).pb(code_);
    code_="goto,"+lfalse;
    ($$->code).pb(code_);
    code_="label,"+ltrue;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $5->code);
    code_="label,"+lfalse;
    ($$->code).pb(code_);
  }
  | IF '(' boolean_expression ')' embedded_statement ELSE embedded_statement {
    string ltrue=getLabel();
    string lnext=getLabel();
    $$=new Attr();
    $$->code=$3->code;
    string code_="ifgoto,==,1,"+($3->place)+","+ltrue;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $7->code);
    code_="goto,"+lnext;
    ($$->code).pb(code_);
    code_="label,"+ltrue;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $5->code);
    code_="label,"+lnext;
    ($$->code).pb(code_);
    /*
     *cout<<"%%%%%%%%%%%"<<endl;
     *for(int i=0;i<($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"%%%%%%%%%%%"<<endl;
     */
  }
  ;
switch_statement
  : SWITCH '(' expression ')' switch_block {
    // refer slides for naming convention
    cout<<"----$$$$$$$$$$"<<endl;
    string ltest=getLabel();
    string lnext=getLabel();
    $$=new Attr();
    Combine($$->code, $$->code, $3->code);
    string code_="goto,"+ltest;
    ($$->code).pb(code_);
    for(int i=0;i<(int)($5->sw_sec).size();i++){
      Attr * sec=($5->sw_sec)[i];
      string lsec=getLabel();
      tmpLbl[i]=lsec;
      code_="label,"+lsec;
      ($$->code).pb(code_);
      Combine($$->code, $$->code, sec->code);
    }
    code_="goto,"+lnext;
    ($$->code).pb(code_);
    code_="label,"+ltest;
    ($$->code).pb(code_);
    for(int i=0;i<(int)($5->sw_sec).size();i++){
      Attr * sec=($5->sw_sec)[i];
      if((sec->sw_lbl)->sw_default == true){
	code_="goto,"+tmpLbl[i];
	($$->code).pb(code_);
      }else{
	code_="ifgoto,==,"+((sec->sw_lbl)->place)+","+($3->place)+","+tmpLbl[i];
	($$->code).pb(code_);
      }
    }
    code_="label,"+lnext;
    ($$->code).pb(code_);
    for(int i=0;i<(int)($$->code).size();i++){
      // change break appropriately
      if(($$->code)[i] == "goto,-1"){
	($$->code)[i]="goto,"+lnext;
      }
      cout<<($$->code)[i]<<endl;
    }
    cout<<"$$$$$$$$$$"<<endl;
  }
  ;
switch_block
  : '{' begin_scope switch_sections_opt '}' {
    $$=$3;
    EndScope();
  }
  ;
switch_sections_opt
  : eps {
    $$=$1;
  }
  | switch_sections {
    $$=$1;
  }
  ;
switch_sections
  : switch_section {
    $$=$1;
    ($$->sw_sec).pb($1);
  }
  | switch_sections switch_section {
    $$=$1;
    ($$->sw_sec).pb($2);
  }
  ;
switch_section
  : switch_label statement_list {
    $$=$2;
    ($$->sw_lbl)=$1;
  }
  ;
switch_labels
  : switch_label
  | switch_labels switch_label
  ;
switch_label
  : CASE constant_expression ':' {
    $$=$2;
  }
  | DEFAULT ':' {
    $$=new Attr();
    ($$->sw_default)=true;
  }
  ;
iteration_statement
  : while_statement {
    $$=$1;
  }
  | do_statement {
    $$=$1;
  }
  | for_statement {
    $$=$1;
  }
  | foreach_statement {
    $$=$1;
  }
  ;
while_statement
  : WHILE '(' boolean_expression ')' embedded_statement {
    $$=new Attr();
    string lbegin=getLabel();
    string lnext=getLabel();
    string ltrue=getLabel();
    string code_="label,"+lbegin;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $3->code);
    code_="ifgoto,==,1,"+($3->place)+","+ltrue;
    ($$->code).pb(code_);
    code_="goto,"+lnext;
    ($$->code).pb(code_);
    code_="label,"+ltrue;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $5->code);
    code_="goto,"+lbegin;
    ($$->code).pb(code_);
    code_="label,"+lnext;
    ($$->code).pb(code_);
    cout<<"-----^^^^^^^^^"<<endl;
    for(int i=0;i<(int)($$->code).size();i++){
      cout<<($$->code)[i]<<endl;
    }
    cout<<"^^^^^^^^^^^"<<endl;
  }
  ;
do_statement
  : DO embedded_statement WHILE '(' boolean_expression ')' ';'
  ;
for_statement
  : FOR '(' for_initializer_opt ';' for_condition_opt ';' for_iterator_opt ')' embedded_statement
  ;
for_initializer_opt
  : eps
  | for_initializer
  ;
for_condition_opt
  : eps
  | for_condition
  ;
for_iterator_opt
  : eps
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
  : break_statement {
    $$=$1;
  }
  | continue_statement
  | goto_statement
  | return_statement {
    $$=$1;
  }
  ;
break_statement
  : BREAK ';' {
    $$=new Attr();
    string code_="goto,-1";
    ($$->code).pb(code_);
  }
  ;
continue_statement
  : CONTINUE ';'
  ;
goto_statement
  : GOTO IDENTIFIER ';'
  ;
return_statement
  : RETURN expression_opt ';' {
    $$=$2;
    string code_="return"+($2->place);
    ($$->code).pb(code_);
  }
  ;
expression_opt
  : eps {
    $$=$1;
  }
  | expression {
    $$=$1;
  }
  ;

compilation_unit
  : using_directives_opt 
  | using_directives_opt namespace_member_declarations
  ;
using_directives_opt
  : eps
  | using_directives
  ;
namespace_member_declarations_opt
  : eps
  | namespace_member_declarations
  ;
namespace_declaration
  : NAMESPACE qualified_identifier namespace_body comma_opt
  ;
comma_opt
  : eps
  | ';'
  ;
qualified_identifier
  : IDENTIFIER {
	$$ = new Attr();
	$$->place = string($1);
  }
  | qualifier IDENTIFIER{
    
  }
  ;
qualifier
  : IDENTIFIER '.'{
    
  }
  | qualifier IDENTIFIER '.' {
  
  }
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
  : eps
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
class_declaration
  : modifiers_opt CLASS IDENTIFIER class_base_opt class_body comma_opt
  ;
class_base_opt
  : eps
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
  : eps
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
  : eps
  | formal_parameter_list
  ;
method_body
  : block {
    /*cout<<"sddadadee"<<endl;*/
    $$=$1;
  }
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
  : eps
  | OUT
  ;
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
  : eps
  | constructor_initializer
  ;
constructor_initializer
  : ':' BASE '(' argument_list_opt ')'
  | ':' THIS '(' argument_list_opt ')'
  ;
destructor_declaration
  : modifiers_opt '~' IDENTIFIER '(' ')' block
  ;
operator_body
  : block
  | ';'
  ;
constructor_body
  : block
  | ';'
  ;
struct_declaration
  : modifiers_opt STRUCT IDENTIFIER struct_interfaces_opt struct_body comma_opt
  ;
struct_interfaces_opt
  : eps
  | struct_interfaces
  ;
struct_interfaces
  : ':' interface_type_list
  ;
struct_body
  : '{' struct_member_declarations_opt '}'
  ;
struct_member_declarations_opt
  : eps
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

array_initializer
  : '{' variable_initializer_list_opt '}' {
    $$=$2;
  }
  ;
variable_initializer_list_opt
  : eps {
    $$=$1;
  }
  | variable_initializer_list {
    $$=$1;
  }
  ;
variable_initializer_list
  : variable_initializer {
    $$=$1;
    ($$->init_list).pb($1);
  }
  | variable_initializer_list COMMA variable_initializer {
    $$=$1;
    ($$->init_list).pb($3);
  }
  ;

interface_declaration
  : modifiers_opt INTERFACE IDENTIFIER interface_base_opt interface_body comma_opt
  ;
interface_base_opt
  : eps
  | interface_base
  ;
interface_base
  : ':' interface_type_list
  ;
interface_body
  : '{' interface_member_declarations_opt '}'
  ;
interface_member_declarations_opt
  : eps
  | interface_member_declarations
  ;
interface_member_declarations
  : interface_member_declaration
  | interface_member_declarations interface_member_declaration
  ;
interface_member_declaration
  : interface_method_declaration
  ;
interface_method_declaration
  : new_opt type IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body
  | new_opt VOID IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body
  ;
new_opt
  : eps
  | NEW
  ;
interface_empty_body
  : ';'
  | '{' '}'
  ;
begin_scope
  : eps {
    BeginScope();
  }
eps
    : /* Nothing*/ {
      $$=new Attr();
    }
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
