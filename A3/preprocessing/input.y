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
namespace_name
  : qualified_identifier
  ;
type_name
  : qualified_identifier
  ;
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
  : eps
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
  : eps
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
  : eps
  | expression
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
  : '{' variable_initializer_list_opt '}'
  | '{' variable_initializer_list COMMA '}'
  ;
variable_initializer_list_opt
  : eps
  | variable_initializer_list
  ;
variable_initializer_list
  : variable_initializer
  | variable_initializer_list COMMA variable_initializer
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
