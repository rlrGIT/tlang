#include "AST.h"
#include <map>

/*

ord, chr, size, substring, concat,
tstrcmp, div, mod, not, getchar_ord,
putchar_ord, flush, printint,
print, println, getchar, ungetchar,
getline, getint, exit, malloc,
free

*/

static std::vector<std::string> function_names = { "ord", "chr", "size", "substring", "concat", 
						   "tstrcmp", "div", "mod", "not", "getchar_ord",
						   "putchar_ord", "flush", "printint",
					    	   "print", "println", "getchar", "ungetchar",
						   "getline", "getint", "exit", "malloc", "free" };

std::map<std::string, int> init_fmap(std::vector<std::string> names)
{
	std::map<std::string, int> function_usage;
	for (std::string name : names) {
		function_usage[name] = 0;
	}
	return function_usage;
}

static std::map<std::string, int> function_usage = init_fmap(function_names);

A_expList_* reverse_explist(A_expList_* list)
{
	A_expList_* reversed = 0;
	while (list != 0) {
		A_exp_* head = list->get_head();
		reversed = A_ExpList(head, reversed);
		list = list->get_tail();
	}
	return reversed;
}

A_decList_* reverse_declist(A_decList_* list)
{
	A_decList_* reversed = 0;
	while (list != 0) {
		A_dec_* head = list->get_head();
		reversed = A_DecList(head, reversed);
		list = list->get_tail();
	}
	return reversed;
}

AST_node_* AST_node_::canonical_form()
{
	EM_error("Canonical form method not overwritten (AST_node_)");
	return 0;
}

A_functionDec_* A_functionDec_::canonical_form()
{
	return this;
}

A_fundec_* A_fundec_::canonical_form()
{
	Symbol name = this->get_name();
	Symbol return_type = this->get_rtype_sym();
	A_fieldList_* params = this->get_params();
	A_exp_* body = this->get_body();

	if ((params != 0) && (body != 0)) {
		return A_Fundec(pos(), name, params->canonical_form(), return_type, body->canonical_form());
	}
	if ((params != 0) && (body == 0)) {
		return A_Fundec(pos(), name, params->canonical_form(), return_type, 0);
	}
	if ((body != 0) && (params == 0)) {
		return A_Fundec(pos(), name, 0, return_type, body->canonical_form());
	}
	return A_Fundec(pos(), name, 0, return_type, 0);
}

A_fundecList_* A_fundecList_::canonical_form()
{
	A_fundec_* head = this->get_head();	
	A_fundecList_* tail = this->get_tail();
	
	if (tail != 0) {
		return A_FundecList(head->canonical_form(), tail->canonical_form());	
	}
	return A_FundecList(head->canonical_form(), 0);
} 


A_field_* A_field_::canonical_form()
{	
	return this;
}

A_fieldList_* A_fieldList_::canonical_form()
{
	A_field_* head = this->get_head();
	A_fieldList_* tail = this->get_tail();
	if (tail == 0) {
		return A_FieldList(head->canonical_form(), 0);
	}
	return A_FieldList(head->canonical_form(), tail->canonical_form());	
}

/* A_exp canonical form functions */

A_exp_* A_exp_::canonical_form()
{
	EM_error("Canonical form method not overwritten (A_exp_)");
	return 0;	
}

A_exp_* A_leafExp_::canonical_form()
{
	return this;
}

// variables should be terminals
A_exp_* A_varExp_::canonical_form()
{
	return this;
}

A_exp_* A_whileExp_::canonical_form()
{
	A_exp_* test = this->get_test();
	A_exp_* body = this->get_body();
	return A_WhileExp(pos(), test->canonical_form(), body->canonical_form());
}

A_exp_* A_assignExp_::canonical_form()
{
	A_var_* var = this->get_var();
	A_exp_* exp = this->get_exp();
	return A_AssignExp(pos(), var, exp->canonical_form());	
} 

A_exp_* A_forExp_::canonical_form()
{
	Symbol var = this->get_var();
	A_exp_* lo = this->get_lo();
	A_exp_* hi = this->get_hi();
	A_exp_* body = this->get_body();
	return A_ForExp(pos(), var, lo->canonical_form(), hi->canonical_form(), body->canonical_form()); 
}

A_exp_* A_opExp_::canonical_form()
{	

	Ty_ty left_ty = _left->typecheck();
	Ty_ty right_ty = _right->typecheck(); 
	A_oper op = this->get_oper();

	bool not_int_op = ((op != A_plusOp) && (op != A_minusOp) && (op != A_timesOp));
	if ((left_ty == Ty_String()) && (right_ty == Ty_String()) && not_int_op) {
		A_exp_* left_c = _left->canonical_form();
		A_exp_* right_c = _right->canonical_form();
		A_exp_* tstrcmp = A_CallExp(pos(), to_Symbol("tstrcmp"), A_ExpList(left_c, A_ExpList(right_c, 0)));
		A_exp_* zero = A_IntExp(pos(), 0);
		return A_OpExp(pos(), A_gtOp, tstrcmp->canonical_form(), zero); 
	}

	// return another opexp that compares integers against constant 0
	return A_OpExp(pos(), _oper, _left->canonical_form(), _right->canonical_form());		
}

A_exp_* A_letExp_::canonical_form()
{
	A_decList_* decs = this->get_decs();
	A_exp_* body = this->get_body();
	return A_LetExp(pos(), decs->canonical_form(), body->canonical_form()); 
}

A_exp_* A_ifExp_::canonical_form()
{
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();
	if (else_or_null != 0) {
		return A_IfExp(pos(), test->canonical_form(), then->canonical_form(), else_or_null->canonical_form());	
	}
	return A_IfExp(pos(), test->canonical_form(), then->canonical_form(), 0);
}

A_exp_* A_breakExp_::canonical_form()
{
	return this;
}

A_expList_* A_expList_::canonical_form()
{
	A_expList_* list = this;
	A_expList_* canon_list = 0;
	
	while (list != 0) {
		A_exp_* head = list->get_head();
		A_exp_* canon_head = head->canonical_form();
		canon_list = A_ExpList(canon_head, canon_list);
		list = list->get_tail();
	}
	canon_list = reverse_explist(canon_list);
	return canon_list;
}

A_exp_* A_seqExp_::canonical_form()
{
	if (_seq != 0) {
		A_expList_* canon_seq = _seq->canonical_form();
		return A_SeqExp(pos(), canon_seq);
	}
	return this;
}

A_exp_* A_callExp_::canonical_form()
{
	int arg_counter = 0;
	A_expList_* args = this->get_args();
	
	if (args == 0) {
		return this;
	}

	A_exp_* let = 0;
	A_decList_* decs = 0;
 	A_expList_* var_args = 0;
	string f_name = Symbol_to_string(this->get_func());
	
	while (args != 0) {
		A_exp_* arg = args->get_head();
		A_exp_* canon_arg = arg->canonical_form(); //nesting

		if (function_usage.count(f_name) <= 0) {
			EM_error("Function " + f_name + " not found.", 1);
		}

		int call_num = function_usage[f_name]; 
		Symbol arg_name = to_Symbol(f_name + str(call_num) + "_arg" + str(arg_counter));
		A_dec_* arg_dec = A_VarDec(pos(), arg_name, 0, canon_arg);
		A_exp_* arg_exp = A_VarExp(pos(), A_SimpleVar(pos(), arg_name)); 
		decs = A_DecList(arg_dec, decs);
		var_args = A_ExpList(arg_exp, var_args);
	
		arg_counter += 1;	
		args = args->get_tail();
	}	

	function_usage[f_name]++; 	
	Symbol f_sym = this->get_func();
	var_args = reverse_explist(var_args);
	A_exp_* call_with_vargs = A_CallExp(pos(), f_sym, var_args);
	let = A_LetExp(pos(), decs, call_with_vargs);
	return let; 	
}







A_dec_* A_dec_::canonical_form()
{
	EM_error("Canonical form for A_dec not overwritten", 1);
	return 0;
}

A_dec_* A_varDec_::canonical_form()
{
	Symbol name = this->get_name();
	Symbol type_sym = this->get_type_sym();
	A_exp_* init = this->get_init_exp();
	return A_VarDec(pos(), name, type_sym, init->canonical_form());
}

A_decList_* A_decList_::canonical_form()
{
	A_decList_* decs = this;
	A_decList_* canon_decs = 0;
	while (decs != 0) {
		A_dec_* head = decs->get_head();
		A_dec_* canon_head = head->canonical_form();
		canon_decs = A_DecList(canon_head, canon_decs);
		decs = decs->get_tail();
	}
	canon_decs = reverse_declist(canon_decs);
	return canon_decs;
}

/* canonical form functions for variables */ 

A_var_* A_var_::canonical_form()
{
	EM_error("Canonical form for A_var not overwritten", 1);
	return 0;
}

A_var_* A_simpleVar_::canonical_form()
{
	EM_debug("Canoncial form for a simple var");
	return this; 
}
