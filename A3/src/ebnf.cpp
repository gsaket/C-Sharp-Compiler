(* grammar csharp4 *)
start :	compilation_unit;

(*B.1 Lexical grammar*) 
input :
	[input_section];
input_section :
	input_section_part
	 | input_section, input_section_part;
input_section_part :
	[input_elements], new_line;
input_elements :
	input_element
	 | input_elements, input_element;
input_element :
	whitespace
	 | comment
	 | ?any token?;

(*B.1.1 Line terminators*) 
new_line :
	?Carriage return character (U+000D)?
	 | ?Line feed character (U+000A)?
	 | ?Carriage return character (U+000D) followed by line feed character (U+000A)?
	 | ?Next line character (U+0085)?
	 | ?Line separator character (U+2028)?
	 | ?Paragraph separator character (U+2029)?;

(*B.1.2 Comments*) 
comment :
	single_line_comment
	 | delimited_comment;
single_line_comment :
	'//', [input_characters];
input_characters :
	input_character
	 | input_characters, input_character;
input_character :
	?Any Unicode character except a new_line_character?;
new_line_character :
	?Carriage return character (U+000D)?
	 | ?Line feed character (U+000A)?
	 | ?Next line character (U+0085)?
	 | ?Line separator character (U+2028)?
	 | ?Paragraph separator character (U+2029)?;

(*B.1.3 White space*) 
whitespace :
	?Any character with Unicode class Zs?
	 | ?Horizontal tab character (U+0009)?
	 | ?Vertical tab character (U+000B)?
	 | ?Form feed character (U+000C)?;

(*B.1.4 Tokens*) 
token :
	identifier
	 | keyword
	 | integer_literal
	 | character_literal
	 | string_literal
	 | operator_or_punctuator;

(*B.1.6 Identifiers*) 
identifier :
	available_identifier
	 | '@', identifier_or_keyword;
available_identifier :
	?An identifier_or_keyword that is not a keyword?;
identifier_or_keyword :
	identifier_start_character, [identifier_part_characters];
identifier_start_character :
	letter_character
	 | '_';
identifier_part_characters :
	identifier_part_character
	 | identifier_part_characters, identifier_part_character;
identifier_part_character :
	letter_character
	 | decimal_digit_character
	 | connecting_character
	 | combining_character
	 | formatting_character;
letter_character :
	?A Unicode character of classes Lu, Ll, Lt, Lm, Lo, or Nl?
combining_character :
	?A Unicode character of classes Mn or Mc?
decimal_digit_character :
	?A Unicode character of the class Nd?
connecting_character :
	?A Unicode character of the class Pc?
formatting_character :
	?A Unicode character of the class Cf?

(*B.1.7 Keywords*) 
keyword :
	'abstract' | 'base' | 'bool' | 'break'
	 | 'case' | 'char'
	 | 'class' | 'continue' | 'default'
	 | 'do' | 'else'
	 | 'false'
	 | 'for' | 'foreach' | 'goto'
	 | 'if' | 'in' | 'int' | 'interface'
	 |'namespace'
	 | 'new' | 'null' | 'object' | 'operator' | 'out'
	 | 'override' | 'private' | 'protected' | 'public'
	 | 'ref' | 'return'
	 | 'sizeof' | 'string'
	 | 'struct' | 'switch' | 'this' | 'true'
	 | 'typeof'
	 | 'using' | 'virtual' | 'void'
	 | 'while';

(*B.1.8 Literals*)
literal :
	boolean_literal
	 | integer_literal
	 | character_literal
	 | string_literal
	 | null_literal;
boolean_literal :
	'true'
	 | 'false';
integer_literal :
	decimal_digits;
decimal_digits :
	decimal_digit
	 | decimal_digits, decimal_digit;
decimal_digit :
	'0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9';
sign :
	'+' | '-';
character_literal :
	"'", character, "'";
character :
	single_character
	 | simple_escape_sequence;
single_character :
	?Any character except ' (U+0027), \ (U+005C), and new_line_character?;
simple_escape_sequence :
	"\'" | '\"' | '\\' | '\0' | '\a' | '\b' | '\f' | '\n' | '\r' | '\t' | '\v';
string_literal :
	regular_string_literal
	 | verbatim_string_literal;
regular_string_literal :
	'"', [regular_string_literal_characters], '"';
regular_string_literal_characters :
	regular_string_literal_character
	 | regular_string_literal_characters, regular_string_literal_character;
regular_string_literal_character :
	single_regular_string_literal_character
	 | simple_escape_sequence;
single_regular_string_literal_character :
	?Any character except " (U+0022), \ (U+005C), and new_line_character?;
verbatim_string_literal :
	'@"', [verbatim_string_literal_characters], '"';
verbatim_string_literal_characters :
	verbatim_string_literal_character
	 | verbatim_string_literal_characters, verbatim_string_literal_character;
verbatim_string_literal_character :
	single_verbatim_string_literal_character
	 | quote_escape_sequence;
single_verbatim_string_literal_character :
	?any character except "?;
quote_escape_sequence :
	'""';
null_literal :
	'null';

(*B.1.9 Operators and punctuators*) 
operator_or_punctuator :
	'{' | '}' | '[' | ']' | '(' | ')' | '.' | ',' | ':' | ';'
	 | '+' | '-' | '*' | '/' | '%' | '&' | '|' | '^' | '!' | '~'
	 | '=' | '<' | '>' | '?' | '::' | '++' | '--' | '&&' | '||'
	 | '==' | '!=' | '<=' | '>=' | '+=' | '-=' | '*=' | '/=' | '%='
	 | '&=' | '|=' | '^=' | '<<' | '<<=' ;
right_shift :
	'>>';
right_shift_assignment :
	'>>=';


(*B.2 Syntactic grammar*) 

(*B.2.1 Basic concepts*) 
namespace_name :
	namespace_or_type_name;
type_name :
	namespace_or_type_name;
namespace_or_type_name :
	identifier
	 | namespace_or_type_name, '.', identifier
	 | qualified_alias_member;

(*B.2.2 Types*) 
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
	 | 'bool';
numeric_type :
	integral_type;
integral_type :
	 'int'
	| 'char';
reference_type :
	class_type
	 | interface_type
	 | array_type;
class_type :
	type_name
	 | 'object'
	 | 'string';
interface_type :
	type_name;

(*B.2.3 Variables*) 
variable_reference :
	expression;

(*B.2.4 Expressions*) 
argument_list :
	argument
	 | argument_list, ',', argument;
argument :
	[argument_name], argument_value;
argument_name :
	identifier, ':';
argument_value :
	expression
	 | 'ref', variable_reference
	 | 'out', variable_reference;
primary_expression :
	primary_no_array_creation_expression
	 | array_creation_expression;
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
	 | default_value_expression;
simple_name :
	identifier;
parenthesized_expression :
	'(', expression, ')';
member_access :
	primary_expression, '.', identifier
	 | predefined_type, '.', identifier
	 | qualified_alias_member, '.', identifier;
predefined_type :
	'bool' | 'char' | 'int'
	 | 'object' | 'string' ;
invocation_expression :
	primary_expression, '(', [argument_list], ')';
element_access :
	primary_no_array_creation_expression, '[', expression_list, ']';
expression_list :
	expression
	 | expression_list, ',', expression;
this_access :
	'this';
base_access :
	'base', '.', identifier
	 | 'base', '[', expression_list, ']';
object_creation_expression :
	'new', type, '(', [argument_list], ')', [object_or_collection_initializer]
	 | 'new', type, object_or_collection_initializer;
object_or_collection_initializer :
	object_initializer
	 | collection_initializer;
object_initializer :
	'{', [member_initializer_list], '}'
	 | '{', member_initializer_list, ',', '}';
member_initializer_list :
	member_initializer
	 | member_initializer_list, ',', member_initializer;
member_initializer :
	identifier, '=', initializer_value;
initializer_value :
	expression
	 | object_or_collection_initializer;
collection_initializer :
	'{', element_initializer_list, '}'
	 | '{', element_initializer_list, ',', '}';
element_initializer_list :
	element_initializer
	 | element_initializer_list, ',', element_initializer;
element_initializer :
	non_assignment_expression
	 | '{', expression_list, '}';
array_creation_expression :
	'new', non_array_type, '[', expression_list, ']', [rank_specifier], [array_initializer]
	 | 'new', array_type, array_initializer
	 | 'new', rank_specifier, array_initializer;
member_declarator_list :
	member_declarator
	 | member_declarator_list, ',', member_declarator;
member_declarator :
	simple_name
	 | member_access
	 | base_access
	 | identifier, '=', expression;
typeof_expression :
	'typeof', '(', type, ')'
	 | 'typeof', '(', 'void', ')';
default_value_expression :
	'default', '(', type, ')';
unary_expression :
	primary_expression
	 | '+', unary_expression
	 | '-', unary_expression
	 | '!', unary_expression
	 | '~', unary_expression
	 | pre_increment_expression
	 | pre_decrement_expression
	 | cast_expression;
pre_increment_expression :
	'++', unary_expression;
pre_decrement_expression :
	'--', unary_expression;
cast_expression :
	'(', type, ')', unary_expression;
multiplicative_expression :
	unary_expression
	 | multiplicative_expression, '*', unary_expression
	 | multiplicative_expression, '/', unary_expression
	 | multiplicative_expression, '%', unary_expression;
additive_expression :
	multiplicative_expression
	 | additive_expression, '+', multiplicative_expression
	 | additive_expression, '-', multiplicative_expression;
shift_expression :
	additive_expression
	 | shift_expression, '<<', additive_expression
	 | shift_expression, right_shift, additive_expression;
relational_expression :
	shift_expression
	 | relational_expression, '<', shift_expression
	 | relational_expression, '>', shift_expression
	 | relational_expression, '<=', shift_expression
	 | relational_expression, '>=', shift_expression;
equality_expression :
	relational_expression
	 | equality_expression, '==', relational_expression
	 | equality_expression, '!=', relational_expression;
and_expression :
	equality_expression
	 | and_expression, '&', equality_expression;
exclusive_or_expression :
	and_expression
	 | exclusive_or_expression, '^', and_expression;
inclusive_or_expression :
	exclusive_or_expression
	 | inclusive_or_expression, '|', exclusive_or_expression;
conditional_and_expression :
	inclusive_or_expression
	 | conditional_and_expression, '&&', inclusive_or_expression;
conditional_or_expression :
	conditional_and_expression
	 | conditional_or_expression, '||', conditional_and_expression;
conditional_expression :
	conditional_or_expression
	 | conditional_or_expression, '?', expression, ':', expression;
assignment :
	unary_expression, assignment_operator, expression;
assignment_operator :
	'='
	 | '+='
	 | '-='
	 | '*='
	 | '/='
	 | '%='
	 | '&='
	 | '|='
	 | '^='
	 | '<<='
	 | right_shift_assignment;
expression :
	non_assignment_expression
	 | assignment;
non_assignment_expression :
	conditional_expression;
constant_expression :
	expression;
boolean_expression :
	expression;

(*B.2.5 Statements*) 
statement :
	 declaration_statement
	 | embedded_statement;
embedded_statement :
	block
	 | empty_statement
	 | expression_statement
	 | selection_statement
	 | iteration_statement
	 | jump_statement;
block :
	'{', [statement_list], '}';
statement_list :
	statement
	 | statement_list, statement;
empty_statement :
	';';
declaration_statement :
	local_variable_declaration, ';'
local_variable_declaration :
	local_variable_type, local_variable_declarators;
local_variable_type :
	type
	 | 'var';
local_variable_declarators :
	local_variable_declarator
	 | local_variable_declarators, ',', local_variable_declarator;
local_variable_declarator :
	identifier
	 | identifier, '=', local_variable_initializer;
local_variable_initializer :
	expression
	 | array_initializer;
expression_statement :
	statement_expression, ';';
statement_expression :
	invocation_expression
	 | object_creation_expression
	 | assignment
	 | pre_increment_expression
	 | pre_decrement_expression;
selection_statement :
	if_statement
	 | switch_statement;
if_statement :
	'if', '(', boolean_expression, ')', embedded_statement
	 | 'if', '(', boolean_expression, ')', embedded_statement, 'else', embedded_statement;
switch_statement :
	'switch', '(', expression, ')', switch_block;
switch_block :
	'{', [switch_sections], '}';
switch_sections :
	switch_section
	 | switch_sections, switch_section;
switch_section :
	switch_labels, statement_list;
switch_labels :
	switch_label
	 | switch_labels, switch_label;
switch_label :
	'case', constant_expression, ':'
	 | 'default', ':';

iteration_statement :
	while_statement
	 | do_statement
	 | for_statement
	 | foreach_statement;
while_statement :
	'while', '(', boolean_expression, ')', embedded_statement;
do_statement :
	'do', embedded_statement, 'while', '(', boolean_expression, ')', ';';
for_statement :
	'for', '(', [for_initializer], ';', [for_condition], ';', [for_iterator], ')', embedded_statement;
for_initializer :
	local_variable_declaration
	 | statement_expression_list;
for_condition :
	boolean_expression;
for_iterator :
	statement_expression_list;
statement_expression_list :
	statement_expression
	 | statement_expression_list, ',', statement_expression;
foreach_statement :
	'foreach', '(', local_variable_type, identifier, 'in', expression, ')', embedded_statement;
jump_statement :
	break_statement
	 | continue_statement
	 | goto_statement
	 | return_statement;
break_statement :
	'break', ';';
continue_statement :
	'continue', ';';
goto_statement :
	'goto', identifier, ';';
return_statement :
	'return', [expression], ';';

(*B.2.6 Namespaces;*) 
compilation_unit :
	 [using_directives], [namespace_member_declarations];
namespace_declaration :
	'namespace', qualified_identifier, namespace_body, [';'];
qualified_identifier :
	identifier
	 | qualified_identifier, '.', identifier;
namespace_body :
	'{', [using_directives], [namespace_member_declarations], '}';
using_directives :
	using_directive
	 | using_directives, using_directive;
using_directive :
	using_alias_directive
	 | using_namespace_directive;
using_alias_directive :
	'using', identifier, '=', namespace_or_type_name, ';';
using_namespace_directive :
	'using', namespace_name, ';';
namespace_member_declarations :
	namespace_member_declaration
	 | namespace_member_declarations, namespace_member_declaration;
namespace_member_declaration :
	namespace_declaration
	 | type_declaration;
type_declaration :
	class_declaration
	 | struct_declaration
	 | interface_declaration;
qualified_alias_member :
	identifier, '::', identifier;

(*B.2.7 Classes;*) 
class_declaration :
	 [class_modifiers], 'class', identifier, [class_base], class_body, [';'];
class_modifiers :
	class_modifier
	 | class_modifiers, class_modifier;
class_modifier :
	'new'
	 | 'public'
	 | 'protected'
	 | 'private'
	 | 'abstract';
class_base :
	':', class_type
	 | ':', interface_type_list
	 | ':', class_type, ',', interface_type_list;
interface_type_list :
	interface_type
	 | interface_type_list, ',', interface_type;
class_body :
	'{', [class_member_declarations], '}';
class_member_declarations :
	class_member_declaration
	 | class_member_declarations, class_member_declaration;
class_member_declaration :
	 field_declaration
	 | method_declaration
	 | operator_declaration
	 | constructor_declaration
	 | destructor_declaration
	 | type_declaration;
field_declaration :
	[field_modifiers], type, variable_declarators, ';';
field_modifiers :
	field_modifier
	 | field_modifiers, field_modifier;
field_modifier :
	'new'
	 | 'public'
	 | 'protected'
	 | 'private';
variable_declarators :
	variable_declarator
	 | variable_declarators, ',', variable_declarator;
variable_declarator :
	identifier
	 | identifier, '=', variable_initializer;
variable_initializer :
	expression
	 | array_initializer;
method_declaration :
	method_header, method_body;
method_header :
	 [method_modifiers], return_type, member_name, '(', [formal_parameter_list], ')';
method_modifiers :
	method_modifier
	 | method_modifiers, method_modifier;
method_modifier :
	'new'
	 | 'public'
	 | 'protected'
	 | 'private'
	 | 'virtual'
	 | 'override'
	 | 'abstract';
return_type :
	type
	 | 'void';
member_name :
	identifier
	 | interface_type, '.', identifier;
method_body :
	block
	 | ';';
formal_parameter_list :
	fixed_parameters;
fixed_parameters :
	fixed_parameter
	 | fixed_parameters, ',', fixed_parameter;
fixed_parameter :
	[parameter_modifier], type, identifier, [default_argument];
default_argument :
	'=', expression;
parameter_modifier :
	'ref'
	 | 'out'
	 | 'this';
operator_declaration :
	operator_modifiers, operator_declarator, operator_body;
operator_modifiers :
	operator_modifier
	 | operator_modifiers, operator_modifier;
operator_modifier :
	'public';
operator_declarator :
	unary_operator_declarator
	 | binary_operator_declarator;
unary_operator_declarator :
	type, 'operator', overloadable_unary_operator, '(', type, identifier, ')';
overloadable_unary_operator :
	'+' | '-' | '!' | '~' | '++' | '--' | 'true' | 'false';
binary_operator_declarator :
	type, 'operator', overloadable_binary_operator, '(', type, identifier, ',', type, identifier, ')';
overloadable_binary_operator :
	'+'
	 | '-'
	 | '*'
	 | '/'
	 | '%'
	 | '&'
	 | '|'
	 | '^'
	 | '<<'
	 | 'right_shift'
	 | '=='
	 | '!='
	 | '>'
	 | '<'
	 | '>='
	 | '<=';
operator_body :
	block
	 | ';';
constructor_declaration :
	[constructor_modifiers], constructor_declarator, constructor_body;
constructor_modifiers :
	constructor_modifier
	 | constructor_modifiers, constructor_modifier;
constructor_modifier :
	'public'
	 | 'protected'
	 | 'private';
constructor_declarator :
	identifier, '(', [formal_parameter_list], ')', [constructor_initializer];
constructor_initializer :
	':', 'base', '(', [argument_list], ')'
	 | ':', 'this', '(', [argument_list], ')';
constructor_body :
	block
	 | ';';
destructor_declaration :
	 '~', identifier, '(', ')', destructor_body
	 | destructor_declaration_unsafe;
destructor_body :
	block
	 | ';';

(*B.2.8 Structs*) 
struct_declaration :
	 [struct_modifiers], 'struct', identifier, [struct_interfaces], struct_body, [';'];
struct_modifiers :
	struct_modifier
	 | struct_modifiers, struct_modifier;
struct_modifier :
	'new'
	 | 'public'
	 | 'protected'
	 | 'private';
struct_interfaces :
	':', interface_type_list;
struct_body :
	'{', [struct_member_declarations], '}';
struct_member_declarations :
	struct_member_declaration
	 | struct_member_declarations, struct_member_declaration;
struct_member_declaration :
	 field_declaration
	 | method_declaration
	 | operator_declaration
	 | constructor_declaration
	 | type_declaration;

(*B.2.9 Arrays*) 
array_type :
	non_array_type, rank_specifier;
non_array_type :
	type;
rank_specifier :
	'[', ']';
array_initializer :
	'{', [variable_initializer_list], '}'
	 | '{', variable_initializer_list, ',', '}';
variable_initializer_list :
	variable_initializer
	 | variable_initializer_list, ',', variable_initializer;

(*B.2.10 Interfaces*) 
interface_declaration :
	[interface_modifiers], 'interface', identifier, [interface_base], interface_body, [';'];
interface_modifiers :
	interface_modifier
	 | interface_modifiers, interface_modifier;
interface_modifier :
	'new'
	 | 'public'
	 | 'protected'
	 | 'private';
interface_base :
	':', interface_type_list;
interface_body :
	'{', [interface_member_declarations], '}';
interface_member_declarations :
	interface_member_declaration
	 | interface_member_declarations, interface_member_declaration;
interface_member_declaration :
	interface_method_declaration;
interface_method_declaration :
	 ['new'], return_type, identifier, '(', [formal_parameter_list], ')', ';';

