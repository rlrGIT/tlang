#include "AST.h"
#include <vector>

// default method - should always be overwritten by a specific expression type
std::vector<AST_node_*> AST_node_::get_children()
{
	std::string error_msg = "get children method for AST_node was not overridden"; 
	EM_error(error_msg, 1);
	return {};
}

std::vector<AST_node_*> A_root_::get_children()
{
	A_exp_* main = this->main_expr;
	std::vector<AST_node_*> c_vect = {main};
	return c_vect; 
}

std::vector<AST_node_*> A_exp_::get_children()
{
	std::string error_msg = "get children method for A_exp was not overridden";
	EM_error(error_msg, 1);
	return {};
}

std::vector<AST_node_*> A_opExp_::get_children()
{
	std::vector<AST_node_*> c_vect = {this->_left, this->_right};
	return c_vect;
}

std::vector<AST_node_*> A_assignExp_::get_children()
{
	std::vector<AST_node_*> c_vect = {this->get_var(), this->get_exp()};
	return c_vect;
}

std::vector<AST_node_*> A_letExp_::get_children()
{
	A_decList_* decs = this->get_decs();
	A_exp_* body = this->get_body();

	if (body != 0) {
		std::vector<AST_node_*> c_vect = {decs, body};	
		return c_vect;
	}
	
	std::vector<AST_node_*> c_vect = {decs};	
	return c_vect;
}

std::vector<AST_node_*> A_decList_::get_children()
{
	A_dec_* head = this->get_head();
	A_decList_* tail = this->get_tail();
	
	if (tail != 0) {
		std::vector<AST_node_*> c_vect = {head, tail};
		return c_vect;
	}
	std::vector<AST_node_*> c_vect = {head};
	return c_vect;
}

std::vector<AST_node_*> A_dec_::get_children()
{
	EM_error("A_dec get_children method not overwritten", 1);	
	return {};
}

std::vector<AST_node_*> A_varDec_::get_children()
{
	A_exp_* init = this->get_init_exp();
	std::vector<AST_node_*> c_vect = {init};
	return c_vect;
}

std::vector<AST_node_*> A_expList_::get_children()
{
	A_exp_* head = this->get_head();
	A_expList_* tail = this->get_tail();
	
	if (tail != 0) {
		std::vector<AST_node_*> c_vect = {head, tail};
		return c_vect;
	}
	std::vector<AST_node_*> c_vect = {head};
	return c_vect;
}

std::vector<AST_node_*> A_fundec_::get_children()
{
	A_fieldList_* params = this->get_params();
	A_exp_* body = this->get_body();
	if (params != 0) {
		if (body != 0) {
			std::vector<AST_node_*> c_vect = {params, body};
			return c_vect;
		}
		std::vector<AST_node_*> c_vect = {params};
		return c_vect;
	}
	// note we already checked to see if both are non-empty
	if (body != 0) {
		std::vector<AST_node_*> c_vect = {body};
		return c_vect;
	}
	std::vector<AST_node_*> empty = {};	
	return empty;
}

std::vector<AST_node_*> A_fundecList_::get_children()
{
	A_fundec_* head = this->get_head();	
	A_fundecList_* tail = this->get_tail();
	if (tail != 0) {
		std::vector<AST_node_*> c_vect = {head, tail};
		return c_vect;
	}
	// invariant: loop head never null
	std::vector<AST_node_*> c_vect = {head};
	return c_vect;
}

std::vector<AST_node_*> A_functionDec_::get_children()
{
	// invariant: requires at least one function 
	A_fundecList_* functions = this->get_declared_functions();
	std::vector<AST_node_*> c_vect = {functions};
	return c_vect;
}

std::vector<AST_node_*> A_field_::get_children()
{
	std::vector<AST_node_*> empty = {};
	return empty;	
}

std::vector<AST_node_*> A_fieldList_::get_children()
{
	A_field_* head = this->get_head();
	A_fieldList_* tail = this->get_tail();
	
	if (tail != 0) {
		if (head != 0) {	
			std::vector<AST_node_*> c_vect = {head, tail};
			return c_vect;
		}
		std::vector<AST_node_*> c_vect = {tail};
		return c_vect;
	}
	if (head != 0) {
		std::vector<AST_node_*> c_vect = {head};
		return c_vect;
	}
	std::vector<AST_node_*> empty = {};
	return empty;	
}

std::vector<AST_node_*> A_seqExp_::get_children()
{
	if (this->_seq != 0)
		return this->_seq->get_children();
	return {};
}

std::vector<AST_node_*> A_callExp_::get_children()
{
	if (this->_args != 0)
		return this->_args->get_children();
	return {};
}

std::vector<AST_node_*> A_ifExp_::get_children()
{
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();

	std::vector<AST_node_*> children = {}; 
	if (else_or_null != 0) {
		children = {test, then, else_or_null};
		return children;
	}
	children = {test, then};
	return children;
}

std::vector<AST_node_*> A_forExp_::get_children()
{	
	A_exp_* lo = this->get_lo();
	A_exp_*	hi = this->get_hi();
	A_exp_* body = this->get_body();

	std::vector<AST_node_*> children = {}; 
	if (body != 0) {
		children = {lo, hi, body};
		return children;
	}
	children = {lo, hi};
	return children;
}

std::vector<AST_node_*> A_whileExp_::get_children()
{
	A_exp_* test = this->get_test();
	A_exp_* body = this->get_body();

	std::vector<AST_node_*> children = {}; 
	if (body != 0) {
		children = {test, body};
		return children;
	}		
	children = {test};
	return children;
}

std::vector<AST_node_*> A_varExp_::get_children()
{
	std::vector<AST_node_*> children = {this->get_var()};
	return children;
}

std::vector<AST_node_*> A_simpleVar_::get_children()
{
	std::vector<AST_node_*> empty = {};
	return empty;
}

std::vector<AST_node_*> A_breakExp_::get_children()
{
	std::vector<AST_node_*> empty = {};
	return empty;
} 

std::vector<AST_node_*> A_var_::get_children()
{
	std::vector<AST_node_*> empty = {};
	return empty;
}

// covers integers, strings, and booleans 
std::vector<AST_node_*> A_leafExp_::get_children()
{
	std::vector<AST_node_*> empty = {};
	return empty;
}
