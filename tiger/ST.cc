#include <logic.h>
#include "errormsg.h"
#include "ST.h"
#include "AST.h"


// merge a list of symbol tables into one
function_lib auto_merge(std::list<function_lib> merge_tables)
{
	function_lib final_lib = function_lib();
	for (function_lib table : merge_tables) {
		final_lib = merge(final_lib, table);
	}
	return final_lib;
} 


/* Primitive Types For Field Types (Ty_Field) */
Ty_field int_field_arg = Ty_Field(to_Symbol("i"), Ty_Int());
Ty_field string_field_arg = Ty_Field(to_Symbol("s"), Ty_String());

// Ty_ty Ty_Function(Ty_ty the_return_type, Ty_fieldList the_parameters)
// Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail)
// Ty_field Ty_Field(Symbol name, Ty_ty ty)
// ST(const nametype &name, const symbol_info &info);

// STRING MANIPULATION
//    ORD(s:string) : int   // returns the character number for a 1-char string
//    CHR(i:int) : string   // returns a 1-char string such that ord(chr(x)) == x
//    SIZE(s:string) : int  // length of the string
//    SUBSTRING(s:string, first:int, n:int) : string  // indices start at 0
//    CONCAT(s1:string, s2:string) : string           // concatenation
// ** TSTRCMP(s1:string, s2:string) : int
//       // tstrcmp(a,b) returns neg # if a < b, 0 if =, pos # if a > b

nametype ord_name = to_Symbol("ord"); 
Ty_ty ord_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(string_field_arg, 0)); 
std_lib_info ord_func = std_lib_info(ord_fn_types, 1);
function_lib ord = function_lib(ord_name, ord_func);

nametype chr_name = to_Symbol("chr");
Ty_ty chr_fn_types = Ty_Function(Ty_String(), Ty_FieldList(int_field_arg, 0));
std_lib_info chr_func = std_lib_info(chr_fn_types, 1);
function_lib chr = function_lib(chr_name, chr_func);

nametype size_name = to_Symbol("size");
Ty_ty size_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(string_field_arg, 0));
std_lib_info size_func = std_lib_info(size_fn_types, 1);
function_lib size = function_lib(size_name, size_func);

nametype substring_name = to_Symbol("substring");
Ty_ty substring_fn_types = Ty_Function(Ty_String(), Ty_FieldList(string_field_arg, (Ty_FieldList(int_field_arg, Ty_FieldList(int_field_arg, 0)))));
std_lib_info substring_func = std_lib_info(substring_fn_types, 3);
function_lib substring = function_lib(substring_name, substring_func);

nametype concat_name = to_Symbol("concat");
Ty_ty concat_fn_types = Ty_Function(Ty_String(), Ty_FieldList(string_field_arg, Ty_FieldList(string_field_arg, 0)));
std_lib_info concat_func = std_lib_info(concat_fn_types, 2);
function_lib concat = function_lib(concat_name, concat_func);

nametype tstrcmp_name = to_Symbol("tstrcmp");
Ty_ty tstrcmp_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(string_field_arg, Ty_FieldList(string_field_arg, 0)));
std_lib_info tstrcmp_func = std_lib_info(tstrcmp_fn_types, 2);
function_lib tstrcmp = function_lib(tstrcmp_name, tstrcmp_func);

// ARITHMETIC/BOOLEAN OPERATIONS
// ** DIV(num:int, den:int): int    // finds floor(num/den), assuming no overflow
// ** MOD(num:int, den:int): int    // finds the remainder of num/den
//    NOT(i:int) : int              // binary negation; makes false true and vice-versa

nametype div_name = to_Symbol("div");
Ty_ty div_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(int_field_arg, Ty_FieldList(int_field_arg, 0)));
std_lib_info div_func = std_lib_info(div_fn_types, 2);
function_lib divf = function_lib(div_name, div_func);

nametype mod_name = to_Symbol("mod");
Ty_ty mod_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(int_field_arg, Ty_FieldList(int_field_arg, 0)));
std_lib_info mod_func = std_lib_info(mod_fn_types, 2);
function_lib mod = function_lib(mod_name, mod_func);

nametype not_name = to_Symbol("not");
Ty_ty not_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(int_field_arg, 0));
std_lib_info not_func = std_lib_info(not_fn_types, 1);
function_lib notf = function_lib(not_name, not_func);

// OUTPUT AND INPUT
// *  GETCHAR_ORD(): int    // read one character, return as a number (like C's getchar(), but no EOF check)
// *  PUTCHAR_ORD(i:int)    // print the character chr(i) (like C's putchar(c))
//    FLUSH()               // makes sure output has been written to the terminal
// *  PRINTINT(i:int)       // print an integer (currently uses base 16)
//    PRINT(s:string)       // print a string
// *  PRINTLN(s:string)		// print s and a newline character
//    GETCHAR() : string    // read a one-character string
// *  UNGETCHAR()	    // make next 'getchar' or 'getchar_ord' return previously read character
// *  GETLINE() : string    // read a one-line string
// *  GETINT() : int        // read an integer (not yet implemented except in HERA-C) ... LEAVES REGISTERS INTACT for convenience

nametype getchar_ord_name = to_Symbol("getchar_ord");
Ty_ty getchar_ord_fn_types = Ty_Function(Ty_Int(), 0);  //should this be a null type or just zero - difficult for type checking
std_lib_info getchar_ord_func = std_lib_info(getchar_ord_fn_types, 0);
function_lib getchar_ord_t = function_lib(getchar_ord_name, getchar_ord_func);

nametype putchar_ord_name = to_Symbol("putchar_ord");
Ty_ty putchar_ord_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(int_field_arg, 0));
std_lib_info putchar_ord_func = std_lib_info(putchar_ord_fn_types, 1);
function_lib putchar_ord_t = function_lib(putchar_ord_name, putchar_ord_func);

nametype flush_name = to_Symbol("flush");
Ty_ty flush_fn_types = Ty_Function(Ty_Void(), 0);
std_lib_info flush_func = std_lib_info(flush_fn_types, 0);
function_lib flush_t = function_lib(flush_name, flush_func);  

nametype printint_name = to_Symbol("printint");
Ty_ty printint_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(int_field_arg, 0));
std_lib_info printint_func = std_lib_info(printint_fn_types, 1);
function_lib printint_t = function_lib(printint_name, printint_func);

nametype print_name = to_Symbol("print");
Ty_ty print_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(string_field_arg, 0));
std_lib_info print_func = std_lib_info(print_fn_types, 1);
function_lib print_t = function_lib(print_name, print_func);

nametype println_name = to_Symbol("println");
Ty_ty println_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(string_field_arg, 0));
std_lib_info println_func = std_lib_info(println_fn_types, 1);
function_lib println_t = function_lib(println_name, println_func);

nametype getchar_name = to_Symbol("getchar");
Ty_ty getchar_fn_types = Ty_Function(Ty_String(), 0);
std_lib_info getchar_func = std_lib_info(getchar_fn_types, 0);
function_lib getchar_t = function_lib(getchar_name, getchar_func);

nametype ungetchar_name = to_Symbol("ungetchar");
Ty_ty ungetchar_fn_types = Ty_Function(Ty_Void(), 0);
std_lib_info ungetchar_func = std_lib_info(ungetchar_fn_types, 0);
function_lib ungetchar_t = function_lib(ungetchar_name, ungetchar_func);

nametype getline_name = to_Symbol("getline");
Ty_ty getline_fn_types = Ty_Function(Ty_String(), 0);
std_lib_info getline_func = std_lib_info(getline_fn_types, 0);
function_lib getline_t = function_lib(getline_name, getline_func);

nametype getint_name = to_Symbol("getint");
Ty_ty getint_fn_types = Ty_Function(Ty_Int(), 0);
std_lib_info getint_func = std_lib_info(getint_fn_types, 0); 
function_lib getint_t = function_lib(getint_name, getint_func);


// OTHER
//    EXIT(i:int)                   // halts the program
// ** MALLOC(n_cells: int): int     // address of allocated space
// ** FREE(address: int)            // release region returned by above (currently does nothing)

nametype exit_name = to_Symbol("exit");
Ty_ty exit_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(int_field_arg, 0));
std_lib_info exit_func = std_lib_info(exit_fn_types, 1);
function_lib exit_t = function_lib(exit_name, exit_func);

nametype malloc_name = to_Symbol("malloc");
Ty_ty malloc_fn_types = Ty_Function(Ty_Int(), Ty_FieldList(int_field_arg, 0));
std_lib_info malloc_func = std_lib_info(malloc_fn_types, 1);
function_lib malloc_t = function_lib(malloc_name, malloc_func);

nametype free_name = to_Symbol("free");
Ty_ty free_fn_types = Ty_Function(Ty_Void(), Ty_FieldList(int_field_arg, 0));
std_lib_info free_func = std_lib_info(free_fn_types, 1);
function_lib free_t = function_lib(free_name, free_func);


// IMPLEMENTATION

// For now, a symbol table can just be a list
// In fact, we can ensure that the symbols at the outer scope
//   are always further along in the list, so if we just find
//   the first symbol with the given name, it will be the one
//   at the inner scope.

std::list<function_lib> library_functions = { ord, chr, size, substring, concat,
					      tstrcmp, divf, mod, notf, getchar_ord_t,
					      putchar_ord_t, flush_t, printint_t, 
					      print_t, println_t, getchar_t, ungetchar_t,
					      getline_t, getint_t, exit_t, malloc_t,
					      free_t 
					    };

// at long last, declare the symbol table
function_lib HERA_std_lib = auto_merge(library_functions);

type_lib int_type = type_lib(to_Symbol("int"), Ty_Int());
type_lib bool_type = type_lib(to_Symbol("bool"), Ty_Bool());
type_lib string_type = type_lib(to_Symbol("string"), Ty_String());
type_lib tiger_types = merge(int_type, merge(string_type, bool_type));

/*
	The following functions use individual symbol tables generated
	by set_local_ST to generate a symbol table of all variables in 
	scope at that node. 
*/

local_var_ST AST_node_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{	
	if (stored_parent != 0) {
		return stored_parent->get_vars_in_scope(this, vars_so_far);		
	}
	return vars_so_far;
}


local_var_ST A_root_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{
	return vars_so_far;
}

local_var_ST A_letExp_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{
	A_exp_* body = this->get_body();
	if (child == body) {
		A_decList_* decs = this->get_decs();
		local_var_ST dec_vars;
		while (decs != 0) {
			A_dec_* head = decs->get_head();
			local_var_ST new_dec = head->set_my_vars();
			dec_vars = merge(dec_vars, new_dec);
			decs = decs->get_tail();
		}
		vars_so_far = merge(vars_so_far, dec_vars);
		return stored_parent->get_vars_in_scope(this, vars_so_far);
	}
	return stored_parent->get_vars_in_scope(this, vars_so_far);
}

local_var_ST A_decList_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{
	A_dec_* head = this->get_head();
	local_var_ST dec_var = head->set_my_vars();
	local_var_ST new_scope = merge(vars_so_far, dec_var);
	return stored_parent->get_vars_in_scope(this, new_scope); 
}

local_var_ST A_varDec_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{
	// grandparent will be the letexp node in the base case
	AST_node_* grandparent = get_grandparent(); 
	return grandparent->get_vars_in_scope(this, vars_so_far);	
}

local_var_ST A_forExp_::get_vars_in_scope(AST_node_* child, local_var_ST vars_so_far)
{
	A_exp_* body = this->get_body();
	if (child == body) {
		local_var_ST ind_var = this->set_my_vars();
		local_var_ST new_scope = merge(vars_so_far, ind_var);
		return stored_parent->get_vars_in_scope(this, new_scope);
	}
	return stored_parent->get_vars_in_scope(this, vars_so_far);
}






local_var_ST AST_node_::set_local_ST()
{
	return local_var_ST();	
}

local_var_ST A_decList_::set_local_ST()
{
	A_dec_* dec = this->get_head();
	return dec->set_my_vars();
}

local_var_ST A_varDec_::set_local_ST()
{
	Symbol name = this->get_name();
	Symbol type = this->get_type_sym();
	A_exp_* init = this->get_init_exp();
	int var_offset = this->get_stack_offset() - 1;
	local_var_ST new_var;

	// if explicitly typed, set type to be the declared type, send init_exp to by 
	// typechecked
	if (type != 0) {	
		if (!is_name_there(type, tiger_types)) {
			EM_error("Variable declared with unrecognized types", 1);
		}
		Ty_ty var_ty = lookup(type, tiger_types);
		stack_variable var_exp_ty = stack_variable(var_offset, var_ty, init);
		new_var = local_var_ST(name, var_exp_ty);
		return new_var;
	}
	
	// if implicitly typed, set type to zero, send init_exp to be typechecked
	stack_variable var_imp_ty = stack_variable(var_offset, 0, init);
	new_var = local_var_ST(name, var_imp_ty);
	return new_var;
}

local_var_ST A_forExp_::set_local_ST()
{
	// create new ST for the new variable
	Symbol var_name = this->get_var();
	A_exp_* lo = this->get_lo();
	
	stack_variable loop_var = stack_variable(get_stack_offset(), Ty_Int(), lo);
	local_var_ST ind_var = local_var_ST(var_name, loop_var);
	return ind_var;
}

