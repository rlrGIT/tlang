#include "AST.h"
#include "errormsg.h"
#include <logic.h>

// Abstract Syntax for Tiger
//
// January 2002, davew@cs.haverford.edu
//
// See AST-print.cc for printing, various other files for attributes other than pos

// First, an example to help illustrate the creation of AST nodes;
// After that come the class declarations

// To run the examples, use the command
//	g++ -std=c++0x -I/home/courses/include -D AST_EXAMPLES_IS_MAIN=1 -D ERRORMSG_SKIP_LEX=1 AST.cc AST-print.cc AST-print-attributes.cc HERA_code.cc result_reg.cc util.cc errormsg.cc -L/home/courses/lib -lcourses -o AST_examples && ./AST_examples


#if defined(AST_EXAMPLES_IS_MAIN) && AST_EXAMPLES_IS_MAIN
int main()
{
	EM_reset("Examples in AST_examples() in AST.cc", -1, true);
	AST_examples();
	AST_example_functions();
	return 0;
}
#endif


// Now, the functions for the actual AST classes...
AST_node_::AST_node_(A_pos pos) : stored_pos(pos)  // concise initialization of "pos" data field
{
}

AST_node_::~AST_node_()
{
}

A_root_::A_root_(A_exp main_exp) : AST_node_(main_exp->pos()), main_expr(main_exp) {

	this->stored_parent = 0;
	this->set_par_pointers();
	EM_debug("Inital parent pointers set...");	

	A_exp_* canon_main = main_expr->canonical_form();
	this->main_expr = canon_main;	
	EM_debug("Canonical form successfully built!");
	
	this->set_par_pointers();
	EM_debug("Parent pointers have been set for cna");
}



String to_String(AST_node_ *n)
{
	return n->print_rep(0, have_AST_attrs);
}

A_exp_::A_exp_(A_pos p) : AST_node_(p)
{
}

A_literalExp_::A_literalExp_(A_pos p) : A_exp_(p)
{
}

A_leafExp_::A_leafExp_(A_pos p) : A_literalExp_(p)
{
}

A_nilExp_::A_nilExp_(A_pos pos) :  A_leafExp_(pos)
{
}

A_boolExp_::A_boolExp_(A_pos pos, bool init) :  A_leafExp_(pos), value(init)
{
}

A_intExp_::A_intExp_(A_pos pos, int i) :  A_leafExp_(pos), value(i)
{
}

A_stringExp_::A_stringExp_(A_pos pos, String s) : A_leafExp_(pos), value(s)
{
}

A_recordExp_::A_recordExp_(A_pos pos, Symbol typ, A_efieldList fields) :  A_literalExp_(pos), _typ(typ), _fields(fields)
{
	precondition(typ != 0);
}

A_arrayExp_::A_arrayExp_(A_pos pos, Symbol typ, A_exp size, A_exp init) :  A_literalExp_(pos), _typ(typ), _size(size), _init(init)
{
	precondition(typ!=0 && size!=0 && init!=0);
}


A_varExp_::A_varExp_(A_pos pos, A_var var) :  A_exp_(pos), _var(var)
{
	precondition(var != 0);
}


A_opExp_::A_opExp_(A_pos pos, A_oper oper, A_exp left, A_exp right) :  A_exp_(pos), _oper(oper), _left(left), _right(right)
{
	precondition(left != 0 && right != 0);
}

A_assignExp_::A_assignExp_(A_pos pos, A_var var, A_exp exp) : A_exp_(pos), _var(var), _exp(exp)
{
	precondition(exp != 0 && var != 0);
}

A_letExp_::A_letExp_(A_pos pos, A_decList decs, A_exp body) :  A_exp_(pos), _decs(decs), _body(body)
{
	// Appel says body and decs can each be null
}

A_callExp_::A_callExp_(A_pos pos, Symbol func, A_expList args) :  A_exp_(pos), _func(func), _args(args)
{
	precondition(func != 0);
}

A_controlExp_::A_controlExp_(A_pos p) : A_exp_(p)
{
}

A_ifExp_::A_ifExp_(A_pos pos, A_exp test, A_exp then, A_exp else_or_0_pointer_for_no_else) :  A_controlExp_(pos), _test(test), _then(then), _else_or_null(else_or_0_pointer_for_no_else)
{
	precondition(test != 0 && then != 0);
}


A_forExp_::A_forExp_(A_pos pos, Symbol var, A_exp lo, A_exp hi, A_exp body) :  A_controlExp_(pos), _var(var), _lo(lo), _hi(hi), _body(body)
{
	precondition(var != 0 && lo != 0 && hi != 0 && body != 0);
}

A_whileExp_::A_whileExp_(A_pos pos, A_exp test, A_exp body) : A_exp_(pos), _test(test), _body(body) 
{
	precondition(test != 0 && body != 0);
}


A_breakExp_::A_breakExp_(A_pos pos) :  A_controlExp_(pos)
{
}

A_seqExp_::A_seqExp_(A_pos pos, A_expList seq) :  A_controlExp_(pos), _seq(seq)
{
}



A_var_::A_var_(A_pos p) : AST_node_(p)
{
}

A_simpleVar_::A_simpleVar_(A_pos pos, Symbol sym) :  A_var_(pos), _sym(sym)
{
	precondition(sym != 0);
}

A_fieldVar_::A_fieldVar_(A_pos pos, A_var var, Symbol sym) :  A_var_(pos), _var(var), _sym(sym)
{
	precondition(var != 0 && sym != 0);
}

A_subscriptVar_::A_subscriptVar_(A_pos pos, A_var var, A_exp exp) :  A_var_(pos), _var(var), _exp(exp)
{
	precondition(exp != 0 && var != 0);
}


A_expList_::A_expList_(A_exp head, A_expList tail) :  AST_node_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}

int A_expList_::length()
{
	if (_tail == 0)
		return 1;
	else
		return 1+_tail->length();
}


A_efield_::A_efield_(Symbol name, A_exp exp) :  AST_node_(exp->pos()), _name(name), _exp(exp)
{
	precondition(exp != 0);
}

String A_efield_::fieldname()
{
	return Symbol_to_string(_name);
}

A_efieldList_::A_efieldList_(A_efield head, A_efieldList tail) :  AST_node_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}

A_dec_::A_dec_(A_pos p) : AST_node_(p)
{
}

A_decList_::A_decList_(A_dec head, A_decList tail) :  A_dec_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}

A_varDec_::A_varDec_(A_pos pos, Symbol var, Symbol typ, A_exp init) :  A_dec_(pos), _var(var), _typ(typ), _init(init)
{
	precondition(var != 0 && init != 0);
}

A_functionDec_::A_functionDec_(A_pos pos, A_fundecList functions_that_might_call_each_other) : A_dec_(pos), theFunctions(functions_that_might_call_each_other)
{
	precondition(functions_that_might_call_each_other != 0);
}

A_fundecList_::A_fundecList_(A_fundec head, A_fundecList tail) :  AST_node_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}
A_fundec_::A_fundec_(A_pos pos, Symbol name, A_fieldList params, Symbol result,  A_exp body) :  AST_node_(pos), _name(name), _params(params), _result(result), _body(body)
{
	precondition(name != 0 && body != 0);
}



A_ty_::A_ty_(A_pos p) : AST_node_(p)
{
}

A_nametyList_::A_nametyList_(A_namety head, A_nametyList tail) :  AST_node_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}

A_namety_::A_namety_(A_pos pos, Symbol name, A_ty ty) :  AST_node_(pos), _name(name), _ty(ty)
{
	precondition(name != 0 && ty != 0);
}

A_fieldList_::A_fieldList_(A_field head, A_fieldList tail) :  AST_node_(head->pos()), _head(head), _tail(tail)
{
	precondition(head != 0);
}

A_field_::A_field_(A_pos pos, Symbol name, Symbol typ) :  AST_node_(pos), _name(name), _typ(typ)
{
	precondition(name != 0 && typ != 0);
}


A_nameTy_::A_nameTy_(A_pos pos, Symbol name) :  A_ty_(pos), _name(name)
{
	precondition(name != 0);
}

A_recordty_::A_recordty_(A_pos pos, A_fieldList record) :  A_ty_(pos), _record(record)
{
}

A_arrayty_::A_arrayty_(A_pos pos, Symbol array) :  A_ty_(pos), _array(array)
{
	precondition(array != 0);
}

bool have_AST_attrs = false;

