#include "util.h"
#include "AST.h"
#include "errormsg.h"
#include "typecheck.h"
#include "ST.h"
//
// Change this comment to describe the attributes you'll be using
//  to check types in tiger programs.
//

#define SYM_INFO_FOR_STDLIB

/* use Ty_Error when necessary */
Ty_ty AST_node_::typecheck()
{
	std::string message = "Typecheck function called on AST_node class and was not overridden.";
	EM_error(message, 1);
	return Ty_Error();
}

// don't think that this should be used yet
Ty_ty A_exp_::typecheck()
{
	std::string message = "Typecheck function called on A_exp class and was not overridden.";
	EM_error(message, 1);
	return Ty_Error();
}


Ty_ty A_root_::typecheck()
{
	EM_debug("got to typechecking root");
	Ty_ty type = this->main_expr->typecheck();
	set_type(type);
	return type;
}

// The bodies of other type checking functions,
//  including any virtual functions you introduce into
//  the AST classes, should go here.


/* Primitive types in typecheck get set - complex ones get set once primitives are evaluated */
Ty_ty A_intExp_::typecheck()
{
	set_type(Ty_Int());
	return get_type();
}

Ty_ty A_stringExp_::typecheck()
{
	set_type(Ty_String());
	return get_type();
}

Ty_ty A_boolExp_::typecheck()
{
	set_type(Ty_Bool());
	return get_type();
}

Ty_ty A_varExp_::typecheck()
{
	// allow overriding methods
	A_var_* var = this->get_var(); 	 
	Ty_ty var_ty = var->typecheck();
	set_type(var_ty);
	return var_ty;
}

Ty_ty A_assignExp_::typecheck()
{
	A_var_* var = this->get_var();
	A_exp_* exp = this->get_exp(); 

	Ty_ty var_type = var->typecheck();	
	Ty_ty exp_type = exp->typecheck();
	
	if (var_type != exp_type) {
		string error_msg = "Assignment expression attempting to cast type: " +
				to_String(exp_type) + " to " + to_String(var_type) + "\n";
		EM_error(error_msg, 1); 
	}	

	set_type(Ty_Void());
	return Ty_Void();
}

Ty_ty A_simpleVar_::typecheck()
{
	Symbol name = this->get_var_name();
	local_var_ST vars = get_vars(); // infinite loop	

	// assert that the expression and declared type are the same		
	EM_debug("simpleVar: " + Symbol_to_string(name) + " with scope: \n" + repr(vars));
	if (!is_name_there(name, vars)) {
		EM_error("SimpleVar: " + Symbol_to_string(name) + " not in scope", 1);
	}	

	stack_variable var_info = lookup(name, vars);
	Ty_ty var_type = var_info.get_type();

	if (var_type != 0) {
		set_type(var_type);
		return var_type;
	}
	A_exp_* init_exp = var_info.get_my_init();
	Ty_ty exp_type = init_exp->typecheck();
	
	// otherwise just use expression type
	if ((exp_type != Ty_Bool()) && (exp_type != Ty_Int()) && (exp_type != Ty_String())) {
		EM_error("Variable declared with illegal implicit type.", 1);
	}
	
	set_type(exp_type);
	return exp_type;
}

Ty_ty A_decList_::typecheck()
{
	A_decList_* decs = this;
	Ty_ty head_type;
	while (decs != 0) {
		A_dec_* head = decs->get_head();
		head_type = head->typecheck();
		decs = decs->get_tail();
	}
	set_type(head_type);	
	return head_type;	
}


Ty_ty A_letExp_::typecheck()
{
	A_decList_* decs = this->get_decs();
	A_exp_* body = this->get_body();
		
	decs->typecheck();
	if (body == 0) {
		set_type(Ty_Void());
		return Ty_Void();
	}
	Ty_ty body_ty =	body->typecheck();
	set_type(body_ty);
	return body_ty;
}


Ty_ty A_varDec_::typecheck()
{	
	A_exp_* init = this->get_init_exp();
	Ty_ty init_ty = init->typecheck();

	// need to deal with two cases - implicit/nonimplicit typing		
	if (get_type_sym() == 0) {
		set_type(init_ty);	
		return init_ty;
	}
	
	// if explicitly declared, lookup the variable
	Symbol type_name = this->get_type_sym();
	if (!is_name_there(type_name, tiger_types)) {
		EM_error("varDec type not valid: " + Symbol_to_string(type_name));
	}
	Ty_ty type = lookup(type_name, tiger_types);

	if (type != init_ty) {
		EM_error("Variable declared with mismatched types.", 1);
	}
	set_type(type);
	return type;	
}


Ty_ty A_expList_::typecheck()
{
	Ty_ty head_type;	
	A_expList_* list = this;
	
	if (list != 0) {	
		while (list != 0) {
			A_exp_* head = list->get_head();
			head_type = head->typecheck();
			list = list->get_tail();
		}
		// use last value in body
		this->set_type(head_type);
		return head_type;
	}
	this->set_type(Ty_Void());
	return Ty_Void();
}


Ty_ty A_breakExp_::typecheck()
{
	// check proper nesting
	this->legal = this->in_loop();
	if (this->is_legal_break()) {
		set_type(Ty_Void());
		return Ty_Void();
	}
	EM_error("Illegal break statement encountered outside a while loop", 1);
	return Ty_Error();
}

Ty_ty A_opExp_::typecheck()
{
	if (this->_left == 0 || this->_right == 0)
		EM_error("Warning null-type passed to A_opExp.", 1);

	// evaluate subtrees
	Ty_ty left_ty =	this->_left->typecheck();
	Ty_ty right_ty = this->_right->typecheck();

	std::string error_msg = "Incompatible types used in A_opExp: "; 
	std::string wrong_types = to_String(left_ty) + " and " + to_String(right_ty) + "\n";
	
	if (left_ty != right_ty) {
		EM_error(error_msg + wrong_types, 1);	
	}
	
	if (_oper == A_plusOp || _oper == A_minusOp || _oper == A_timesOp) {
		if (left_ty == Ty_Int() || right_ty == Ty_Int()) {

			set_type(Ty_Int());
			this->l_type = left_ty;
			this->r_type = right_ty;
			return this->type;
		}
		EM_error(error_msg + wrong_types + " in ", 1); 
	}
	
	if (_oper == A_ltOp || _oper == A_leOp || _oper == A_gtOp || 
	    _oper == A_geOp) { 
		
		if ((left_ty == Ty_String() && right_ty == Ty_String()) ||
		    (left_ty == Ty_Int() && right_ty == Ty_Int())) {

			this->l_type = left_ty;
			this->r_type = right_ty;
			set_type(Ty_Bool());
			return this->type;  
		}
		EM_error(error_msg + wrong_types, 1);
	}

	if (_oper == A_eqOp || _oper == A_neqOp) {
		if ((left_ty == Ty_Bool()   && right_ty == Ty_Bool()) ||
		    (left_ty == Ty_Int()    && right_ty == Ty_Int())  ||
		    (left_ty == Ty_String() && right_ty == Ty_String()))   {

			this->l_type = left_ty;
			this->r_type = right_ty;
			set_type(Ty_Bool());
			return this->type;
		} 
		
		EM_error(error_msg + wrong_types, 1);
		return Ty_Error();
	}
	EM_error("Unrecognized operator in typecheck", 1);
	return Ty_Error();
}

/* not sure if this is needed - left basic outline here though */ 
////Ty_tyList(Ty_ty head, Ty_tyList tail)
Ty_ty A_seqExp_::typecheck()
{
	Ty_ty cur_elem_ty = Ty_Void(); 
	A_expList_* explist = this->_seq;
	while (explist != 0) {
		A_exp_* head = explist->get_head();
		cur_elem_ty = head->typecheck();
		explist = explist->get_tail();
	}
	if (explist == 0) {
		set_type(cur_elem_ty);
		return cur_elem_ty; 
	}		
	EM_error("This should never happen -- somehow sequence expression with non-void type was accepted in typechecking", 1);
	return Ty_Error();
}

// Ty_ty Ty_Function(Ty_ty the_return_type, Ty_fieldList the_parameters)
// Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail)

Ty_ty A_callExp_::typecheck()
{
	nametype f_name = this->get_func();
	A_expList f_args = this->get_args(); 	
	
	if (!is_name_there(f_name, HERA_std_lib)) {
		EM_error("Function call to unknown library function " + Symbol_to_string(f_name), 1);	
	}
 
	//fetch a bunch of information
	std_lib_info function_info = lookup(f_name, HERA_std_lib);
	Ty_ty function_types = function_info.get_type();
	Ty_ty return_type = function_types->u.function.return_type;
	Ty_fieldList param_types = function_types->u.function.parameter_types;

	// assert arguments for functions are valid
	while (f_args != 0 && param_types != 0) {
		A_exp head = f_args->get_head();
		Ty_ty arg_type = head->typecheck();

		if (arg_type != param_types->head->ty) {
			string param_err = "Function: " + Symbol_to_string(f_name) + 
					"called with illegal parameter of type: " +
					to_String(arg_type);
			EM_error(param_err, 1); 
		}

		f_args = f_args->get_tail();
		param_types = param_types->tail;
	}
	
	f_args = this->get_args();
	int num_args = function_info.count_args();
	int arg_count = 0;
	
	while (f_args != 0) {
		arg_count += 1;
		f_args = f_args->get_tail();
	}	
	
	if (arg_count != num_args) {
		string arg_count_err = "Function call to: " + Symbol_to_string(f_name) + 
					" has the wrong number of arguments: " + str(arg_count) + "\n";
		EM_error(arg_count_err, 1); 
	}
	
	set_type(return_type);
	return return_type;

}

// does typechecking here entail solving the if/else expession? 
// involves evaluation of boolean statements - need to include code typechecking booleans
Ty_ty A_ifExp_::typecheck()
{
	// typecheck test expression for type errors
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();

	Ty_ty test_ty =	test->typecheck();
	Ty_ty then_ty = then->typecheck();

	// if there is an else expression
	if (else_or_null != 0) {

		Ty_ty else_or_null_ty = else_or_null->typecheck();
		
		if (then_ty != else_or_null_ty) {
			string error_msg = "If/then/else expression has inconsistent types :" 
				+ to_String(then_ty) + " and " + to_String(else_or_null_ty) + ".\n";
			EM_error(error_msg, 1);
		}
	
		if (test_ty != Ty_Bool()) {
			string error_msg = "Test condition is of type: " + to_String(test_ty) + " not Ty_bool().\n";
			EM_error(error_msg, 1);
		} 

		set_type(then_ty);
		return this->type;	
	}
	
	if (then_ty != Ty_Void()) {
		string error_msg = "Then condition for if/then expression has non-void value: " + 
			to_String(then_ty);
		EM_error(error_msg, 1);
	}
	set_type(Ty_Void());	
	return Ty_Void();
}

Ty_ty A_whileExp_::typecheck()
{
	A_exp_* test_exp = this->_test;
	A_exp_* body_exp = this->_body;

	Ty_ty test_ty = test_exp->typecheck();
	Ty_ty body_ty = body_exp->typecheck();
	// assert test condition is a boolean
	if (test_ty != Ty_Bool()) {
		string error_msg = "While loop condition is not a boolean type: " + 
			to_String(test_ty);
		EM_error(error_msg, 1);
	}
	// assert body has no return value - we are only updating
	if (body_ty != Ty_Void()) {
		string error_msg = "While loop body has non-void value: " +
			to_String(body_ty);
		EM_error(error_msg, 1);
	}
	set_type(Ty_Void());
	return Ty_Void();	
}

Ty_ty A_forExp_::typecheck()
{
	A_exp_* lo = this->get_lo();
	A_exp_* hi = this->get_hi();
	A_exp_* body = this->get_body();

	Ty_ty lo_ty = lo->typecheck();
	Ty_ty hi_ty = hi->typecheck();
	Ty_ty body_ty = body->typecheck();

	int for_offset = this->get_stack_offset();
	int body_offset = body->get_stack_offset();

	EM_debug("For loop with offset: " + str(for_offset));
	EM_debug("For loop body with offset: " + str(body_offset));

	// value of variable
	if (lo_ty != Ty_Int() || hi_ty != Ty_Int()) {
		string error_msg = "Illegal types for for-loop bounds :";
		EM_error(error_msg + to_String(lo_ty) + " and " + to_String(hi_ty) + "\n", 1);
	}
	if (body_ty != Ty_Void())
		EM_error("For loop using non-void expression with type: " + to_String(body_ty), 1);

	set_type(Ty_Void());
	return Ty_Void();
}

