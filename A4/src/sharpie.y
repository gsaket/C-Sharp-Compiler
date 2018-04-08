%{
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

%token <sval> WRITELINE 374
%token <sval> READLINE 375


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
%type <NT> print_statement read_statement

%start compilation_unit
%%

literal
  : boolean_literal {
    $$=$1;
    CurTable->insertLiteral("bool", $1->place);
  }
  | INTEGER_LITERAL {
    $$=new Attr();
    $$->place=string($1);
    CurTable->insertLiteral("int", $$->place);
  }
  | CHARACTER_LITERAL {
    $$=new Attr();
    $$->place=string($1);
    CurTable->insertLiteral("char", ($$->place));
  }
  | STRING_LITERAL{
    $$=new Attr();
    $$->place=string($1);
    CurTable->insertLiteral("string", ($$->place));
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
    // not used
    $$=$1;
  }
  ;
simple_type
  : primitive_type {
    $$=$1;
  }
  | class_type {
    // Not used
    $$=$1;
  }
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
  | STRING_TYPE {
    $$=new Attr();
    $$->type="string";
    $$->width=400;
  }
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
  : expression {
    $$=$1;
  }
  ;
argument_list
  : argument {
    $$=$1;
    ($$->arg_lst).pb($1);
  }
  | argument_list COMMA argument {
    // TODO: Check usage
    $$=$1;
    ($$->arg_lst).pb($3);
  }
  ;
argument
  : expression {
    $$=$1;
  }
  | OUT variable_reference
  ;
primary_expression
  : parenthesized_expression {
    $$=$1;
  }
  | primary_expression_no_parenthesis {
    $$=$1;
  }
  ;
primary_expression_no_parenthesis
  : literal {
    $$=$1;
  }
  | array_creation_expression {
    $$=$1;
  }
  | member_access {
    $$=$1;
  }
  | invocation_expression {
    $$=$1;
  }
  | element_access {
    $$=$1;
  }
  | this_access {
    $$=$1;
  }
  | base_access {
    $$=$1;
  }
  | new_expression {
    $$=$1;
  }
  | typeof_expression {
    $$=$1;
  }
  ;
parenthesized_expression
  : '(' expression ')' {
    $$=$2;
  }
  ;
member_access
  : primary_expression '.' IDENTIFIER
  | primitive_type '.' IDENTIFIER
  | class_type '.' IDENTIFIER
  ;
invocation_expression
  : primary_expression_no_parenthesis '(' argument_list_opt ')'
  | qualified_identifier '(' argument_list_opt ')' {
      string FunName=($1->place);
      if(!(CurTable->lookup(($1->place)))){
	cerr<<"Error Line "<<yylineno<<": Function "<<($1->place)<<" Not defined"<<endl;
	exit(0);
      }
      // Already looked up
      SymTable* DeclTbl=getDeclScope(FunName,CurTable);
      int arg_cnt=(int)($3->arg_lst).size();
      if((DeclTbl->Node)[FunName].Y != "function"){
	cerr<<"Error Line "<<yylineno<<": "<<($1->place)<<" Ain't No function!"<<endl;
	exit(0);
      }
      if(arg_cnt  != (DeclTbl->Args)[FunName].X){
	cerr<<"Error Line "<<yylineno<<": "<<($1->place)<<" Number of arguments don't match"<<endl;
	exit(0);
      }
      $$=new Attr();
      string code_;
      for(int i=0;i<arg_cnt;i++){
	Attr* CurArg=($3->arg_lst)[i];
	Combine($$->code, $$->code, CurArg->code);
      }
      for(int i=0;i<arg_cnt;i++){
	Attr* CurArg=($3->arg_lst)[i];
	code_="param,"+(CurArg->place)+","+to_string(i+1);
	($$->code).pb(code_);

	// check declartion of initializer
	if(!(CurTable->lookup(change_string(CurArg->place)))){
	  cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurArg->place)<<" used without declaration."<<endl;
	  exit(0);
	}
	// check type compatibility
	string typ1=((DeclTbl->Args)[FunName].Y)[i];
	string typ2=getTyp(change_string(CurArg->place));
	if(typ1 != typ2){
	  cerr<<"ERROR: Line: "<<(yylineno)<<" "<<(CurArg->place)<<" has type "<<typ2<<". Expected type "<<typ1<<endl;
	  exit(0);
	}

      }
      string RetType=(DeclTbl->Node)[FunName].X;
      string tp="NULL";
      if(RetType != "void"){
	tp=CurTable->getTemp(RetType);
	($$->place)=tp;
      }
      code_="call,"+FunName+","+to_string(arg_cnt)+","+tp;
      ($$->code).pb(code_);
  }
  ;
argument_list_opt
  : eps {
    $$=$1;
  }
  | argument_list {
    $$=$1;
  }
  ;
element_access
  : primary_expression LEFT_BRACKET expression_list RIGHT_BRACKET
  | qualified_identifier LEFT_BRACKET expression_list RIGHT_BRACKET {
    $$=new Attr();
    if(!(CurTable->lookup(change_string($1->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<" Array "<<($1->place)<<" used without declaration."<<endl;
      exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string($1->place), CurTable);
    if((DeclTbl->Node)[change_string($1->place)].Y != "array"){
      cerr<<"ERROR: Line: "<<(yylineno)<<($1->place)<<" Ain't no array!"<<endl;
      exit(0);
    }
    Combine($$->code, $$->code, $3->code);
    string tp1=CurTable->getTemp("int");
    string tp2=CurTable->getTemp("int");
    string required_type=(DeclTbl->Node)[change_string($1->place)].X;
    string tp3=CurTable->getTemp(required_type);
    string wid="1";
    if(required_type == "int")wid="4";
    string code_="=,"+tp1+","+($3->place);
    ($$->code).pb(code_);
    code_="*,"+tp2+","+tp1+","+wid;
    ($$->code).pb(code_);
    // member, var, array, offset :: var=array[offset]
    code_="member,"+tp3+","+($1->place)+","+tp2;
    ($$->code).pb(code_);
    ($$->place)=tp3;
    ($$->array_element) = true;
    ($$->array_name)=($1->place);
    ($$->array_off)=tp2;
  }
  ;
expression_list
  : expression {
    $$=$1;
  }
  | expression_list COMMA expression {
    // not used
    $$=$1;
  }
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
  : eps {
    $$=$1;
  }
  | array_initializer {
    $$=$1;
  }
  ;
typeof_expression
  : TYPEOF '(' type ')'
  | TYPEOF '(' VOID ')'
  ;
addressof_expression
  : '&' unary_expression
  ;
postfix_expression
  : primary_expression {
    $$=$1;
  }
  | qualified_identifier {
    $$ = $1;
  }
  ;
unary_expression_not_plusminus
  : postfix_expression {
    $$ = $1;
  }
  | '!' unary_expression {
    $$=$2;
    string code_="!,"+($2->place);
    ($$->code).pb(code_);
    if(!(CurTable->lookup(change_string($2->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<($2->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
  | '~' unary_expression {
    $$=$2;
    string code_="~,"+($2->place);
    ($$->code).pb(code_);
    if(!(CurTable->lookup(change_string($2->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<($2->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
  | cast_expression
  ;
pre_increment_expression
  : PLUSPLUS unary_expression {
    $$=$2;
    string code_="+,"+($2->place)+",1,"+($2->place);
    ($$->code).pb(code_);
    if($2->array_element == true){
      // update the array
      code_="update,"+($2->place)+","+($2->array_name)+","+($2->array_off);
      ($$->code).pb(code_);
    }
    if(!(CurTable->lookup(change_string($2->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<($2->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
  ;
pre_decrement_expression
  : MINUSMINUS unary_expression {
    $$=$2;
    string code_="-,"+($2->place)+","+($2->place)+",1";
    ($$->code).pb(code_);
     if($2->array_element == true){
      // update the array
      code_="update,"+($2->place)+","+($2->array_name)+","+($2->array_off);
      ($$->code).pb(code_);
    }
    if(!(CurTable->lookup(change_string($2->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<($2->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
  ;
unary_expression
  : unary_expression_not_plusminus {
    $$=$1;
  }
  | '+' unary_expression {
    $$=$2;
  }
  | '-' unary_expression {
    $$=$2;
    string tp=CurTable->getTemp("int");
    string code_="-,"+tp+",0,"+($2->place);
    ($$->code).pb(code_);
    ($$->place)=tp;
    if(!(CurTable->lookup(change_string($2->place)))){
      cerr<<"ERROR: Line: "<<(yylineno)<<($2->place)<<" used without declaration."<<endl;
      exit(0);
    }
  }
  | '*' unary_expression
  | pre_increment_expression {
    $$=$1;
  }
  | pre_decrement_expression {
    $$=$1;
  }
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
    CheckTyp($1,$3,"int");
  }
  | multiplicative_expression '/' unary_expression {
    translate($$,$1,$3,"/");
    CheckTyp($1,$3,"int");
  }
  | multiplicative_expression '%' unary_expression{
    translate($$,$1,$3,"%");
    CheckTyp($1,$3,"int");
  }
  ;
additive_expression
  : multiplicative_expression {
    $$=$1;
  }
  | additive_expression '+' multiplicative_expression {
    translate($$,$1,$3,"+");
    CheckTyp($1,$3,"int");
    /*
     *for(int i=0;i<(int)(($$->code).size());i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"----"<<endl;
     */
  }
  | additive_expression '-' multiplicative_expression{
    translate($$,$1,$3,"-");
    CheckTyp($1,$3,"int");
  }
  ;
shift_expression
  : additive_expression {
    $$ = $1;
  }
  | shift_expression LTLT additive_expression{
    translate($$,$1,$3,"<<");
    CheckTyp($1,$3,"int");
  }
  | shift_expression GTGT additive_expression{
    translate($$,$1,$3,">>");
    CheckTyp($1,$3,"int");
  }
  ;
relational_expression
  : shift_expression {
    $$ = $1;
  }
  | relational_expression '<' shift_expression{
    translate($$,$1,$3,"<","bool");
    CheckTyp($1,$3,"int");
  }
  | relational_expression '>' shift_expression{
    translate($$,$1,$3,">","bool");
    CheckTyp($1,$3,"int");
  }
  | relational_expression LEQ shift_expression{
    translate($$,$1,$3,"<=","bool");
    CheckTyp($1,$3,"int");
  }
  | relational_expression GEQ shift_expression{
    translate($$,$1,$3,">=","bool");
    CheckTyp($1,$3,"int");
  }
  ;
equality_expression
  : relational_expression {
    $$=$1;
  }
  | equality_expression EQEQ relational_expression{
    translate($$,$1,$3,"==","bool");
    // can compare char/int/bool
    CheckTyp($1,$3,"null");
  }
  | equality_expression NOTEQ relational_expression{
    translate($$,$1,$3,"!=","bool");
    CheckTyp($1,$3,"null");
  }
  ;
and_expression
  : equality_expression{
    $$=$1;
  }
  | and_expression '&' equality_expression{
    translate($$,$1,$3,"&");
    CheckTyp($1,$3,"int");
  }
  ;
exclusive_or_expression
  : and_expression{
    $$=$1;
  }
  | exclusive_or_expression '^' and_expression{
    translate($$,$1,$3,"^");
    CheckTyp($1,$3,"int");
  }
  ;
inclusive_or_expression
  : exclusive_or_expression{
    $$=$1;
  }
  | inclusive_or_expression '|' exclusive_or_expression{
    translate($$,$1,$3,"|");
    CheckTyp($1,$3,"int");
  }
  ;
conditional_and_expression
  : inclusive_or_expression {
    $$=$1;
  }
  | conditional_and_expression ANDAND inclusive_or_expression{
    translate($$,$1,$3,"&&","bool");
    CheckTyp($1,$3,"bool");
  }
  ;
conditional_or_expression
  : conditional_and_expression{
    $$=$1;
  }
  | conditional_or_expression OROR conditional_and_expression{
    translate($$,$1,$3,"||","bool");
    CheckTyp($1,$3,"bool");
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
  /*cout<<"In assignment"<<endl;*/
  // TODO: handle others later
  $$=new Attr();
  // Left side shouldn't be a literal
  if(CurTable->lookup(change_string($1->place)) && CurTable->lookup(change_string($3->place))){
    string typ1;
    string cat1;
    string a1;
    if(($1->array_element) == true){
      typ1=getTyp(($1->array_name));
      cat1=getCat(($1->array_name));
      a1=($1->array_name);
      // update, input, array, offset
      $$->place=$3->place;
      int lcode=(int)($1->code).size();
      string code_="update,"+($3->place)+","+($1->array_name)+","+($1->array_off);
      ($1->code)[lcode-1]=code_;
      Combine($$->code, $3->code, $1->code);
    }else{
      typ1=getTyp(change_string($1->place));
      cat1=getCat(change_string($1->place));
      a1=($1->place);
      $$->place = $1->place;
      Combine($$->code, $3->code, $1->code);
      string code_= getTAC(2,"=",$1->place,$3->place);
      ($$->code).pb(code_);
    }
    string typ2=getTyp(change_string($3->place));
    if(typ1 != typ2){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbols "<<(a1)<<" and "<<($3->place)<<" are of type "<<typ1<<" and "<<typ2<<". Assignment not possible."<<endl;
	exit(0);
    }
    if(cat1 == "literal"){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<($1->place)<<" is a literal. Can't be assigned!"<<endl;
	exit(0);
    }

  }else if(!(CurTable->lookup(change_string($1->place)))){
    cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<($1->place)<<" used without declaration."<<endl;
    exit(0);
  }else if(!(CurTable->lookup(change_string($3->place)))){
    cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<($3->place)<<" used without declaration."<<endl;
    exit(0);
  }

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
/*
 *    cout<<"st......"<<endl;
 *    for(int i=0;i<($1->code).size();i++){
 *      cout<<($1->code)[i]<<endl;
 *    }
 *    cout<<"ed......"<<endl;
 *
 */
  }
  | print_statement {
    $$=$1;
  }
  | read_statement {
    $$=$1;
  }
  ;
print_statement
  : WRITELINE '(' argument ')' ';' {
    $$=new Attr();
    Combine($$->code, $$->code, $3->code);
    if(!(CurTable->lookup(change_string($3->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<($3->place)<<" is not declared"<<endl;
	exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string($3->place), CurTable);
    string typ=(DeclTbl->Node)[change_string($3->place)].X;
    // print, var, type
    string code_="print,"+($3->place)+","+typ;
    ($$->code).pb(code_);
  }
  ;
read_statement
  : READLINE '(' argument ')' ';' {
    $$=new Attr();
    Combine($$->code, $$->code, $3->code);
    if(!(CurTable->lookup(change_string($3->place)))){
	cerr<<"ERROR: Line: "<<(yylineno)<<" Symbol "<<($3->place)<<" is not declared"<<endl;
	exit(0);
    }
    SymTable* DeclTbl=getDeclScope(change_string($3->place), CurTable);
    string typ=(DeclTbl->Node)[change_string($3->place)].X;
    // read, var, type
    string code_="read,"+($3->place)+","+typ;
    ($$->code).pb(code_);
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
    $$ = $3;
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
    // Checking Re-declaration
    for(int i=0;i<(int)($2->var_dec).size();i++){
      Attr* CurVar=($2->var_dec)[i];
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
    $$=new Attr();
    if($1->isarray == false){
	string typ1=($1->type);
	for(int i=0;i<(int)($2->var_dec).size();i++){
	  Attr * CurVar = ($2->var_dec)[i];
	  // TODO:insert CurVar->place into table-> DONE!
	  CurVar->place=change_string((CurVar->place));
	  CurTable->insertVariable(($1->type), CurVar->place);
	  CurVar->place+="_"+to_string((CurTable->table_id));
	  string code_=($1->type)+","+(CurVar->place);
	  ($$->code).pb(code_);
	  if(CurVar->init != NULL){

	    Attr * CurVarInit=(CurVar->init);
	    Combine($$->code,$$->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ($$->code).pb(code_);

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
       for(int i=0;i<(int)($2->var_dec).size();i++){
	  Attr * CurVar = ($2->var_dec)[i];
	  if(CurVar->init != NULL){
	    string typ1=($1->elem)->type;
	    Attr * CurVarInit=(CurVar->init);
	    int ArrayLength=(CurVarInit->init_list).size();
	    CurTable->insertArray(($1->elem)->type, CurVar->place);
	    string code_="array,"+($1->elem)->type+","+to_string(ArrayLength)+","+CurVar->place;
	    ($$->code).pb(code_);
	    for(int j=0;j<(int)(CurVarInit->init_list).size();j++){
	      Attr * CurVarInitElem = (CurVarInit->init_list)[j];
	      int ElemWidth=($1->elem)->width;
	      // TODO:update width for this array struct=len*Elemwidth
	      code_="update,"+(CurVarInitElem->place)+","+(CurVar->place)+","+to_string(ElemWidth*j);
	      Combine($$->code,$$->code,CurVarInitElem->code);
	      ($$->code).pb(code_);

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
	    CurTable->insertArray(($1->elem)->type, CurVar->place);
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
    /*
     *if(CurTable->look_in_shadow($$->place)){
     *  ($$->place)=($$->place)+"_"+to_string(NumScopes);
     *}
     */
    if(CurTable->lookup(change_string($$->place))){
      SymTable* DeclTbl= getDeclScope(change_string($$->place),CurTable);
      ($$->place)+="_"+to_string(DeclTbl->table_id);
    }
    $$->init = NULL;
    $$->line=yylineno;
  }
  | IDENTIFIER '=' variable_initializer {
    $$=new Attr();
    $$->place = string($1);
/*
 *    if(CurTable->look_in_shadow($$->place)){
 *      ($$->place)=($$->place)+"_"+to_string(NumScopes);
 *    }
 *
 */
    if(CurTable->lookup(change_string($$->place))){
      SymTable* DeclTbl= getDeclScope(change_string($$->place),CurTable);
      ($$->place)+="_"+to_string(DeclTbl->table_id);
    }
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
    /*cout<<"----$$$$$$$$$$"<<endl;*/
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
    int si=(int)($$->code).size();
    if(($$->code)[si-1] != "goto,-1")
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
    }

    /*
     *cout<<"st$$$$$$$$$$"<<endl;
     *for(int i=0;i<(int)($$->code).size();i++){
     *  cout<<($$->code)[i]<<endl;
     *}
     *cout<<"ed$$$$$$$$$$"<<endl;
     */
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
    for(int i=0;i<(int)($$->code).size();i++){
      if(($$->code)[i] == "goto,-1"){
	// change break appropriately
	($$->code)[i]="goto,"+lnext;
      }else if(($$->code)[i] == "goto,-2"){
	// change continue appropriately
	($$->code)[i]="goto,"+lbegin;
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
  ;
do_statement
  : DO embedded_statement WHILE '(' boolean_expression ')' ';'
  ;
for_statement
  : FOR '(' for_initializer_opt ';' for_condition_opt ';' for_iterator_opt ')' embedded_statement {
    $$=new Attr();
    string lbegin=getLabel();
    string lnext=getLabel();
    string ltrue=getLabel();
    Combine($$->code, $$->code, $3->code);
    string code_="label,"+lbegin;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $5->code);
    code_="ifgoto,==,1,"+($5->place)+","+ltrue;
    ($$->code).pb(code_);
    code_="goto,"+lnext;
    ($$->code).pb(code_);
    code_="label,"+ltrue;
    ($$->code).pb(code_);
    Combine($$->code, $$->code, $9->code);
    Combine($$->code, $$->code, $7->code);
    code_="goto,"+lbegin;
    ($$->code).pb(code_);
    code_="label,"+lnext;
    ($$->code).pb(code_);
    for(int i=0;i<(int)($$->code).size();i++){
      if(($$->code)[i] == "goto,-1"){
	// change break appropriately
	($$->code)[i]="goto,"+lnext;
      }else if(($$->code)[i] == "goto,-2"){
	// change continue appropriately
	($$->code)[i]="goto,"+lbegin;
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
  ;
for_initializer_opt
  : eps {
    $$=$1;
  }
  | for_initializer {
    $$=$1;
  }
  ;
for_condition_opt
  : eps {
    $$=$1;
  }
  | for_condition {
    $$=$1;
  }
  ;
for_iterator_opt
  : eps {
    $$=$1;
  }
  | for_iterator {
    $$=$1;
  }
  ;
for_initializer
  : local_variable_declaration {
    $$=$1;
  }
  | statement_expression_list {
    $$=$1;
  }
  ;
for_condition
  : boolean_expression {
    $$=$1;
  }
  ;
for_iterator
  : statement_expression_list {
    $$=$1;
  }
  ;
statement_expression_list
  : statement_expression {
    $$=$1;
  }
  | statement_expression_list COMMA statement_expression {
    $$=$1;
    Combine($$->code, $$->code, $3->code);
  }
  ;
foreach_statement
  : FOREACH '(' type IDENTIFIER IN expression ')' embedded_statement
  ;
jump_statement
  : break_statement {
    $$=$1;
  }
  | continue_statement {
    $$=$1;
  }
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
  : CONTINUE ';' {
    $$=new Attr();
    string code_="goto,-2";
    ($$->code).pb(code_);
  }
  ;
goto_statement
  : GOTO IDENTIFIER ';'
  ;
return_statement
  : RETURN expression_opt ';' {
    $$=$2;
    string code_="return,"+($2->place);
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
  : using_directives_opt {
    $$=$1;
  }
  | using_directives_opt namespace_member_declarations {
    $$=$2;
    cout<<"------CODE-----"<<endl;
    cout<<"0,call,Main,0,NULL"<<endl;
    cout<<"1,exit"<<endl;
    for(int i=0;i<(int)($$->code).size();i++){
      cout<<(i+2)<<","<<($$->code)[i]<<endl;
    }
    cout<<"------END--CODE-----"<<endl;
  }
  ;
using_directives_opt
  : eps {
    $$=$1;
  }
  | using_directives {
    $$=$1;
  }
  ;
namespace_member_declarations_opt
  : eps {
    $$=$1;
  }
  | namespace_member_declarations {
    $$=$1;
  }
  ;
namespace_declaration
  : NAMESPACE qualified_identifier namespace_body comma_opt {
  
  }
  ;
comma_opt
  : eps {
    $$=$1;
  }
  | ';' {
    $$=new Attr();
  }
  ;
qualified_identifier
  : IDENTIFIER {
	$$ = new Attr();
	$$->place = string($1);
/*
 *        if(CurTable->look_in_shadow($$->place)){
 *          ($$->place)=($$->place)+"_"+to_string(NumScopes);
 *        }
 *
 */
    if(CurTable->lookup(change_string($$->place))){
      SymTable* DeclTbl= getDeclScope(change_string($$->place),CurTable);
      if((DeclTbl->Node)[change_string($$->place)].Y == "variable")
	($$->place)+="_"+to_string(DeclTbl->table_id);
    }

  }
  | qualifier IDENTIFIER{
    // not used
    $$=new Attr();
    $$->place = string($2);
  }
  ;
qualifier
  : IDENTIFIER '.'{
    // not used
    $$=new Attr();
    $$->place = string($1);
  }
  | qualifier IDENTIFIER '.' {
    // not used
    $$=new Attr();
    $$->place = string($2);
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
  : namespace_member_declaration {
    $$=$1;
  }
  | namespace_member_declarations namespace_member_declaration {
    // not here
    $$=$1;
    cerr<<"Not expected here"<<endl;
    Combine($$->code, $$->code, $2->code);
  }
  ;
namespace_member_declaration
  : namespace_declaration {
    $$=$1;
  }
  | type_declaration {
    $$=$1;
  }
  ;
type_declaration
  : class_declaration {
    $$=$1;
  }
  | struct_declaration {
    $$=$1;
  }
  | interface_declaration {
    $$=$1;
  }
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
  : modifiers_opt CLASS IDENTIFIER class_base_opt class_body comma_opt {
    // CLASS IDENTIFIER class_body
    $$=$5;
  }
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
  : '{' begin_scope class_member_declarations_opt '}' {
     $$=$3;
     EndScope();
  }
  ;
class_member_declarations_opt
  : eps {
    $$=$1;
  }
  | class_member_declarations {
    $$=$1;
  }
  ;
class_member_declarations
  : class_member_declaration {
    $$=$1;
  }
  | class_member_declarations class_member_declaration {
    $$=$1;
    Combine($$->code, $$->code, $2->code);
  }
  ;
class_member_declaration
  : field_declaration {
    $$=$1;
  }
  | method_declaration {
    $$=$1;
  }
  | operator_declaration {
    $$=$1;
  }
  | constructor_declaration {
    $$=$1;
  }
  | destructor_declaration {
    $$=$1;
  }
  | type_declaration {
    $$=$1;
  }
  ;
field_declaration
  : modifiers_opt type variable_declarators ';' {
    // Checking Re-declaration
    for(int i=0;i<(int)($3->var_dec).size();i++){
      Attr* CurVar=($3->var_dec)[i];
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
    $$=new Attr();
    if($2->isarray == false){
	for(int i=0;i<(int)($3->var_dec).size();i++){
	  Attr * CurVar = ($3->var_dec)[i];
	  // TODO:insert CurVar->place into table-> DONE!
	  CurVar->place=change_string((CurVar->place));
	  CurTable->insertVariable(($2->type), CurVar->place);
	  CurVar->place+="_"+to_string(CurTable->table_id);
	  string code_=($2->type)+","+(CurVar->place);
	  ($$->code).pb(code_);
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    Combine($$->code,$$->code,CurVarInit->code);
	    string code_=getTAC(2,"=",CurVar->place, CurVarInit->place);
	    ($$->code).pb(code_);
	  }
	}
    }else{
       for(int i=0;i<(int)($3->var_dec).size();i++){
	  Attr * CurVar = ($3->var_dec)[i];
	  if(CurVar->init != NULL){
	    Attr * CurVarInit=(CurVar->init);
	    int ArrayLength=(CurVarInit->init_list).size();
	    CurTable->insertArray(($2->elem)->type, CurVar->place);
	    string code_="array,"+($2->elem)->type+","+to_string(ArrayLength)+","+CurVar->place;
	    ($$->code).pb(code_);
	    for(int j=0;j<(int)(CurVarInit->init_list).size();j++){
	      Attr * CurVarInitElem = (CurVarInit->init_list)[j];
	      int ElemWidth=($2->elem)->width;
	      // TODO:update width for this array struct=len*Elemwidth
	      code_="update,"+(CurVarInitElem->place)+","+(CurVar->place)+","+to_string(ElemWidth*j);
	      Combine($$->code,$$->code,CurVarInitElem->code);
	      ($$->code).pb(code_);
	    }
	  }else{
	    // default length 100 size array
	    CurTable->insertArray(($2->elem)->type, CurVar->place);
	    string code_="array,"+($2->elem)->type+",100,"+CurVar->place;
	    ($$->code).pb(code_);
	  }
	}
     }

  }
  ;
method_declaration
  :  method_header method_body {
/* 	// updated
 *      $$=new Attr();
 *      string code_="function,"+($1->place);
 *      ($$->code).pb(code_);
 *      Combine($$->code, $$->code, $2->code);
 *
 */
      string ret_typ=($1->ret_typ);
      string method_name=($1->place);
      $$=new Attr();
      string code_="function,"+method_name;
      ($$->code).pb(code_);
      int par_cnt=(int)($1->par_lst).size();
      int off=8;
      for(int i=par_cnt-1;i>=0;i--){
	// pop, var, offset
	code_="pop,"+((($1->par_lst)[i])->place)+","+to_string(off);
	off+=4;
	($$->code).pb(code_);
      }
      Combine($$->code, $$->code, $2->code);
      if($1->ret_typ == "void"){
	code_="return,NULL";
	($$->code).pb(code_);
      }
  }
  ;
method_header
  : modifiers_opt type qualified_identifier '(' formal_parameter_list_opt ')' {
    $$=new Attr();
    ($$->code)=($5->code);
    ($$->par_lst)=($5->par_lst);
    ($$->place)=($3->place);
    ($$->ret_typ)=($2->type);
    /*
     *for(int i=0;i<(int)($$->par_lst).size();i++){
     *  cout<<(($$->par_lst)[i]->place)<<endl;
     *}
     *cout<<"++++"<<endl;
     */
    int par_cnt=(int)($5->par_lst).size();
    vector<string> par_typs;
    // delaying variable insertion in scope
    FLAG=true;
    for(int i=0;i<par_cnt;i++){
      string typ=(($5->par_lst)[i])->type;
      string plc=(($5->par_lst)[i])->place;
      (($5->par_lst)[i])->place+="_"+to_string(NumScopes);
      par_typs.pb(typ);
      par_var.pb(mp(typ, plc));
    }
    CurTable->insertFunc($$->place, $$->ret_typ, par_typs, par_cnt);
  }
  | modifiers_opt VOID qualified_identifier '(' formal_parameter_list_opt ')' {
     $$=new Attr();
    ($$->code)=($5->code);
    ($$->par_lst)=($5->par_lst);
    ($$->place)=($3->place);
    ($$->ret_typ)="void";
    /*
     *for(int i=0;i<(int)($$->par_lst).size();i++){
     *  cout<<(($$->par_lst)[i]->place)<<endl;
     *}
     *cout<<"++++"<<endl;
     */
    int par_cnt=(int)($5->par_lst).size();
    vector<string> par_typs;
    // delaying variable insertion in scope
    FLAG=true;
    for(int i=0;i<par_cnt;i++){
      string typ=(($5->par_lst)[i])->type;
      string plc=(($5->par_lst)[i])->place;
      (($5->par_lst)[i])->place+="_"+to_string(NumScopes);
      par_typs.pb(typ);
      par_var.pb(mp(typ, plc));
    }
    CurTable->insertFunc($$->place, $$->ret_typ, par_typs, par_cnt);
  }
  ;
formal_parameter_list_opt
  : eps {
    $$=$1;
  }
  | formal_parameter_list {
    $$=$1;
  }
  ;
method_body
  : block {
    /*cout<<"sddadadee"<<endl;*/
    $$=$1;
  }
  | ';' {
    $$=new Attr();
  }
  ;
formal_parameter_list
  : formal_parameter {
    $$=$1;
    ($$->par_lst).pb($1);
    /*cout<<"insert "<<($1->place)<<endl;*/
  }
  | formal_parameter_list COMMA formal_parameter {
    $$=$1;
    ($$->par_lst).pb($3);
    /*cout<<"insert "<<($3->place)<<endl;*/
  }
  ;
formal_parameter
  : fixed_parameter {
    $$=$1;
  }
  ;
fixed_parameter
  : parameter_modifier_opt type IDENTIFIER {
    $$=new Attr();
    ($$->place)=string($3);
    /*
     *if(CurTable->look_in_shadow($$->place)){
     *  ($$->place)=($$->place)+"_"+to_string(NumScopes);
     *}
     */
    // delaying this process till next scope
    /*CurTable->insertVariable(($2->type),($$->place));*/
    // TODO: insert array type
    ($$->type)=($2->type);
  }
  ;
parameter_modifier_opt
  : eps {
    $$=$1;
  }
  | OUT {
    // Not used
  }
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
    NumScopes=1;
    FLAG=false;
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
