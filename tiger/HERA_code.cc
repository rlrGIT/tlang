#include "AST.h"
#include "util.h"
#include "ST.h"

// #include "children.cc"

/* Global vars for labelling */
const string indent_math = "    ";  // might want to use something different for, e.g., branches
static int str_count = 0;
static int label_count = 0;
static int gt_count = 0;
static int lt_count = 0;
static int ge_count = 0;
static int le_count = 0;
static int eq_count = 0;
static int neq_count = 0;
static int while_count = 0;
static int for_count = 0;
static int break_count = 0;


Symbol A_var_::get_name() {
	EM_error("Get A_var get name not overwritten");
	return 0;
}

Symbol A_simpleVar_::get_name() {
	Symbol name_s = this->get_var_name();	
	return name_s;
}


/* HERA CODE METHODS */

string AST_node_::HERA_code()  /// Default used during development; could be removed in final version
{
	string message = "HERA_code() requested for AST node type not yet having a HERA_code() method";
	EM_error(message, 1);
	return "#error " + message;  //if somehow we try to HERA-C-Run this, it will fail
}

string A_root_::HERA_code()
{
	return  "#include <Tiger-stdlib-stack-data.hera>\n\n" +		
		main_expr->HERA_data() + "CBON()\n\n" +
		main_expr->HERA_code() + "\nHALT()\n\n" +
		"#include <Tiger-stdlib-stack.hera>\n";
}

string A_intExp_::HERA_code()
{	
	return indent_math + "SET(" + result_reg_s() + ", " + str(value) + ")\n";
}

string A_boolExp_::HERA_code()
{
	bool val = this->get_val();
	if (val)
		return indent_math + "SET(" + result_reg_s() + ", 1)\n";
	return indent_math + "SET(" + result_reg_s() + ", 0)\n";
}
/*
string A_simpleVar_::HERA_code()
{
	Symbol name = this->get_var_name();
	local_var_ST scope = get_vars();
	if (!is_name_there(name, scope)) {
		EM_error("HERA code simpleVar expression out of scope.", 1);
	}
	stack_variable info = lookup(name, scope);
	int var_offset = info.get_offset();
	
}
*/
string A_assignExp_::HERA_code()
{
	A_var_* var = this->get_var();
	A_exp_* exp = this->get_exp();
	
	Symbol var_sym = var->get_name();
	string var_name = Symbol_to_string(var_sym);
	local_var_ST scope = get_vars();
	
	if (!is_name_there(var_sym, scope)) {
		EM_error("Variable in assign_exp " + var_name + " out of scope.", 1);			
	}
	stack_variable var_info = lookup(var_sym, scope);
	int offset = var_info.get_offset();
	string var_offset = str(offset);
	
	string exp_result = exp->result_reg_s();
	string store_inst = "STORE(" + exp_result + ", " +
				var_offset + ", FP) // reassignment of variable: " + var_name + "\n";

	string exp_code = "// new value of variable: " + var_name + "\n" + exp->HERA_code();
	return exp_code + store_inst; 
}

string A_varExp_::HERA_code()
{
	A_var_* var = this->get_var();
	Symbol var_name = var->get_name();
	local_var_ST scope = get_vars();

	if (!is_name_there(var_name, scope)) {
		EM_error("Variable " + Symbol_to_string(var_name) + " in var_exp out of scope.", 1);
	}
	stack_variable var_info = lookup(var_name, scope);
	int offset_i = var_info.get_offset();
	string offset_s = str(offset_i);

	string load_inst = indent_math + "LOAD(" + this->result_reg_s() + ", " + 
			offset_s + ", FP) // use of variable: " + Symbol_to_string(var_name) + "\n";
	return load_inst;	
}

string A_varDec_::HERA_code()
{
	A_exp_* init_exp = this->get_init_exp();
	string init_exp_code = init_exp->HERA_code();
	Symbol var_name = this->get_name();
	string var_s = Symbol_to_string(var_name);
	int offset = this->get_stack_offset() - 1;	
	
	string store_inst = indent_math + "STORE(" + init_exp->result_reg_s() + 
		", " + str(offset) + ", " + "FP) // " + var_s + " declared" + "\n\n";
	return init_exp_code + store_inst;
}

string A_decList_::HERA_code()
{
	string output = "";
	A_decList_* decs = this;
	while (decs != 0) {
		A_dec_* head = decs->get_head();
		string dec_code = "// variable declaration\n" + head->HERA_code();
		output += dec_code;
		decs = decs->get_tail();
	}
	return output;
}


string A_breakExp_::HERA_code()
{
	string break_branch = this->get_break_branch();
	return break_branch;
}

string HERA_math_op(Position p, A_oper op, string r_reg) // needed for opExp
{
	switch (op) {
	case A_plusOp:
		return "ADD";
	case A_minusOp:
		return "SUB";
	case A_timesOp:
		return "MUL";	// was MULT for HERA 2.3
	case A_gtOp:
		gt_count += 1;	
		return  "\n// Branch if greater than \n" 
			"BG(gt_cmp_true" + str(gt_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "0)\n" + 
			"BR(gt_cmp_false" + str(gt_count) + ")\n" + 
			"LABEL(gt_cmp_true" + str(gt_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n" + 
			"LABEL(gt_cmp_false" + str(gt_count) + ")\n\n";
	case A_geOp:
		ge_count += 1;
		return "\n// Branch if greater than or equal \n" 
			"BGE(gte_cmp_true" + str(ge_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "0)\n" +
			"BR(gte_cmp_false" + str(ge_count) + ")\n" + 
			"LABEL(gte_cmp_true" + str(ge_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n" +
			"LABEL(gte_cmp_false" + str(ge_count) + ")\n\n";
	case A_ltOp:
		lt_count += 1;
		return "\n// Branch if less than \n"
			"BL(lt_cmp_true" + str(lt_count) + ")\n" + indent_math +
		  	"SET(" + r_reg + ", " + "0)\n" +
			"BR(lt_cmp_false" + str(lt_count) + ")\n" +  
			"LABEL(lt_cmp_true" + str(lt_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n" + 
			"LABEL(lt_cmp_false" + str(lt_count) + ")\n\n";
	case A_leOp:
		le_count += 1;
		return "\n// Branch if less than equal \n" 
			"BLE(leq_cmp_true" + str(le_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "0)\n" + 
			"BR(leq_cmp_false" + str(le_count) + ")\n" +
			"LABEL(leq_cmp_true" + str(le_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n"
			"LABEL(leq_cmp_false" + str(le_count) + ")\n\n";
	case A_eqOp:
		eq_count += 1;
		return "\n// Branch if equal to \n"
			"BZ(eq_cmp_true" + str(eq_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "0)\n" + 
			"BR(eq_cmp_false" + str(eq_count) + ")\n" + 
			"LABEL(eq_cmp_true" + str(eq_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n" +
			"LABEL(eq_cmp_false" + str(eq_count) + ")\n\n";
	case A_neqOp:
		neq_count += 1;
		return "\n// Branch if not equal to \n" 
			"BNZ(neq_cmp_true" + str(neq_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "0)\n" + 
			"BR(neq_cmp_false" + str(neq_count) + ")\n" +
			"LABEL(neq_cmp_true" + str(neq_count) + ")\n" + indent_math +
			"SET(" + r_reg + ", " + "1)\n" + 
			"LABEL(neq_cmp_false" + str(neq_count) + ")\n\n";
	default:
		::EM_error("Unhandled case in HERA_math_op", 1);
		return "Oops_unhandled_hera_math_op";
	}
}

string A_letExp_::HERA_code()
{
	A_decList_* decs = this->get_decs();
	A_exp_* exps = this->get_body();
	string decs_out = decs->HERA_code();

	int frame_size = 0;
	while (decs != 0) {
		frame_size++;
		decs = decs->get_tail();
	}

	string create_frame = "// build let expression frame\nINC(SP, " + str(frame_size) + ")\n\n";
	string dec_frame = "// collapse let expression frame\nDEC(SP, " + str(frame_size) + ")\n";
	string move_to_par = "MOVE(" + result_reg_s() + ", " + exps->result_reg_s() + ")\n";
	string cmp_and_br = "";

	/*if (is_canonical()) {
		A_oper op = get_canonical_op();
		cmp_and_br = "CMP(" + result_reg_s() + ", R0)\n" + 
		HERA_math_op(pos(), op, result_reg_s());
	}
	*/
	if (exps != 0) {
		string exp_out = exps->HERA_code();
		return create_frame + decs_out + exp_out + move_to_par + dec_frame;
	}	
	return create_frame + decs_out + move_to_par + dec_frame;
}

string A_opExp_::HERA_code()
{
	Ty_ty type = this->type; 
	
	if (_oper == A_plusOp || _oper == A_minusOp || _oper == A_timesOp) 
		return this->integer_operator();
	
	if (type == Ty_Bool())
		return this->boolean_operator();
	
	return "";
}


string A_opExp_::boolean_operator()
{
	int su_left = this->_left->result_reg();
	int su_right = this->_right->result_reg();
	
        string par_reg = this->result_reg_s();
        string l_child_reg = this->_left->result_reg_s();
        string r_child_reg = this->_right->result_reg_s();
        string rescue = indent_math + "MOVE(" + par_reg + ", " + l_child_reg + ")\n";

	if (su_left == su_right) {
		string bool_output = indent_math + "CMP(" + par_reg + ", " + r_child_reg + ")" + 
					HERA_math_op(pos(), _oper, par_reg); //set the result of the bool to parent's register
		return _left->HERA_code() + rescue + _right->HERA_code() + bool_output; 
	}
	
	if (su_left > su_right) {
		string bool_output = indent_math + "CMP(" + l_child_reg + ", " + r_child_reg + ")" +
					 HERA_math_op(pos(), _oper, par_reg);
		return _left->HERA_code() + _right->HERA_code() + bool_output;
	}
	
	string bool_output = indent_math + "CMP(" + l_child_reg + ", " + par_reg + ")" + 
				HERA_math_op(pos(), _oper, par_reg);
	
	return _right->HERA_code() + _left->HERA_code() + bool_output; 
}


string A_opExp_::integer_operator()
{
	int su_left = this->_left->result_reg();
        int su_right = this->_right->result_reg();
 
        string par_reg = this->result_reg_s();
        string l_child_reg = this->_left->result_reg_s();
        string r_child_reg = this->_right->result_reg_s();

	A_oper op = this->get_oper();
	string arith_inst = HERA_math_op(pos(), op, par_reg);
 
        if (su_left == su_right) {
                string rescue = indent_math + "MOVE("
				 + par_reg + ", " + l_child_reg + ")\n";
 
                string output = indent_math + arith_inst + 
				"(" + par_reg + ", " + par_reg + ", " + r_child_reg + ")\n\n";
                 // rescue left child to parent's register 
                return _left->HERA_code() + rescue +  _right->HERA_code() + output;
        }
 
        if (su_left > su_right) {	
                string output = indent_math + arith_inst +  
				 "(" + par_reg + ", " + l_child_reg + ", " + r_child_reg + ")\n\n";
                return _left->HERA_code() + _right->HERA_code() + output;
        }
 
        string output = indent_math + arith_inst + 
			"(" + par_reg + ", " + l_child_reg + ", " + par_reg + ")\n\n";
        return _right->HERA_code() + _left->HERA_code() + output;
}


string A_stringExp_::HERA_code()
{
	std::string label = this->set_label("string" + str(str_count++));
	return indent_math + "SET(" + result_reg_s() + ", " + this->_label + ")\n";
}

string A_callExp_::HERA_code()
{
	string output = "";
	nametype func_name = this->get_func();
	A_expList_* func_args = this->get_args();
	
	if (!is_name_there(func_name, HERA_std_lib)) {
		EM_error("Call to unknown function: " + Symbol_to_string(func_name) + "\n", 1);
	}
	
	std_lib_info func_info = lookup(func_name, HERA_std_lib);
	int frame_size = 3 + std::max(func_info.count_args(), 1);
	string comment = "// function call to: " + Symbol_to_string(func_name) + "\n";
	string inc_frame = indent_math + "MOVE(FP_alt, SP)\n" + 
			   indent_math + "INC(SP, " + str(frame_size) + ") // create frame for " +
			   Symbol_to_string(func_name) + "\n";
	
	output += (comment + inc_frame); 
	int arg_loc = 3;
	while (func_args != 0) {
		A_exp head = func_args->get_head();
		
		string args_code = "\n" + head->HERA_code();
		string store_arg = indent_math + "STORE(" + head->result_reg_s() + 
					", " + str(arg_loc) + ", FP_alt) // store function arg\n";
		output += "\n// calculate function arg\n" + args_code + store_arg;
		func_args = func_args->get_tail();
		arg_loc += 1;
	}

	string f_call = "\n" + indent_math + "CALL(FP_alt, " + Symbol_to_string(func_name) + ")\n";	
	string f_dec = indent_math + "DEC(SP, " + str(frame_size) + ")\n";

	// if the return type isn't void, store the output where it can be used next
	Ty_ty f_types = func_info.get_type();
	Ty_ty r_type = f_types->u.function.return_type;

	if (r_type != Ty_Void()) {
		output += f_call + indent_math +
			"LOAD(" + result_reg_s() + ", 3, FP_alt)\n" + f_dec;
		return output;
	}
/*
	string cmp_and_br = "";
	if (is_canonical()) {
		A_oper op = get_canonical_op();
		cmp_and_br = "CMP(" + result_reg_s(), + ", R0)\n" +
				HERA_math_op(pos(), op, result_reg_s()); 
	}
*/
	// if return type is void
	output += f_call + f_dec + "\n\n";
	return output;
}


string A_seqExp_::HERA_code()
{
	string output = "";
	A_expList_* exps = this->_seq;

	// for void expression case
	if (exps == 0)
		return "";

	A_exp_* head = 0;
	while (exps != 0) {
		head = exps->get_head();
		string head_code = head->HERA_code();
		output += head_code;
		exps = exps->get_tail();
	}
	// assign value of seq_Exp to the relavent register
	string last_exp_reg = head->result_reg_s();
	string move_to_parent = indent_math + 
		"MOVE(" + this->result_reg_s() + ", " + last_exp_reg + ")\n"; 
	
	return output + move_to_parent;
}

/* will need to change for while loops with variables */ 
string A_whileExp_::HERA_code()
{
	A_exp_* test = this->get_test();
	A_exp_* body = this->get_body();
	
	string break_br = "BR(break" + str(break_count) + ")\n";
	string break_lb = "LABEL(break" + str(break_count++) + ")\n";	 
	this->set_break_label(break_br);

	string while_body = "";
	string while_test = test->HERA_code();
	string while_test_branch = "BG(condition_while_true" + str(while_count) + ")\n";
	string while_label = "LABEL(continue_while_loop" + str(while_count) + ")\n";
	string while_cont = "BR(continue_while_loop" + str(while_count) + ")\n";
	string while_exit = "BR(exit_while_loop" + str(while_count) + ")\n";
	string exit_label = "LABEL(exit_while_loop" + str(while_count) + ")\n";
	string test_true = "LABEL(condition_while_true" + str(while_count++) + ")\n";

	while_body = body->HERA_code();
	string compare = "CMP(" + test->result_reg_s() + ", " + "R0)\n";
	
	return while_label + while_test + compare + while_test_branch + while_exit 
			+ test_true + while_body + while_cont + exit_label + break_lb + "\n";
}


string A_forExp_::HERA_code()
{
	Symbol var = this->get_var(); 
	A_exp_* lo = this->get_lo();
	A_exp_* hi = this->get_hi();
	A_exp_* body = this->get_body();

	string break_br = "BR(break" + str(break_count) + ")\n";
	string break_lb = "LABEL(break" + str(break_count++) + ")\n";	 
	this->set_break_label(break_br);
	
	// calculate range
	string lo_code = lo->HERA_code();
	string lo_reg = lo->result_reg_s();	

	string hi_code = hi->HERA_code();
	string hi_reg = hi->result_reg_s();

	string body_code = body->HERA_code();
	string body_reg = body->result_reg_s(); //unsure of this is necessary? 
	local_var_ST body_scope = body->get_vars();

	stack_variable var_info = lookup(var, body_scope);
	int offset = var_info.get_offset();

	string br_continue = "BR(continue_for_loop" + str(for_count) + ")\n";
	string continue_loop = "LABEL(continue_for_loop" + str(for_count) + ")\n";

	string br_exit = "BL(exit_for_loop" + str(for_count) + ")\n\n";
	string exit_loop = "LABEL(exit_for_loop" + str(for_count) + ")\n";

	string br_invalid = "BL(invalid_range" + str(for_count) + ")\n";
	string invalid_range = "LABEL(invalid_range" + str(for_count++) + ")\n\n";

	string store_lo = indent_math + "STORE(" + lo_reg + ", " + str(offset) + ", FP)\n";
	string store_hi = indent_math + "STORE(" + hi_reg + ", " + str(offset + 1) + ", FP)\n";

	string load_lo = indent_math + "LOAD(R1, " + str(offset) + ", FP)\n";  
	string load_hi = indent_math + "LOAD(R2, " + str(offset + 1) + ", FP)\n"; 

	// final pieces 
	string create_frame = "INC(SP, 2)\n" + lo_code + store_lo + hi_code + store_hi; 
	string iterate = load_lo + load_hi + "CMP(R2, R1)\n" + br_invalid + continue_loop +
						load_lo + load_hi + "CMP(R2, R1)\n" + br_exit;
	string increment = load_lo + indent_math + "INC(R1, 1)\n" + "STORE(R1, " + str(offset) +
							 ", " + "FP)\n" + br_continue;
	string exit_labels = exit_loop + invalid_range + "DEC(SP, 2)\n";	

	string output = create_frame + iterate + 
			body_code + increment + exit_labels + break_lb;

	return output; 
		
}


string A_ifExp_::HERA_code()
{
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();

	string test_condition = test->HERA_code();
	string then_condition = then->HERA_code();

	string compare = "CMP(" + test->result_reg_s() + ", R0)\n"; 
	string true_branch = "BR(test_true" + str(label_count) + ")\n";
	string true_label = "\nLABEL(test_true" + str(label_count) + ")\n"; 
	string false_branch = "BZ(test_false" + str(label_count) + ")\n";    
	string false_label = "LABEL(test_false" + str(label_count) + ")\n";
	// need one for the then and one for the else 
	string move_to_par_reg_then = indent_math + "MOVE(" + this->result_reg_s() +
				 ", " + then->result_reg_s() + ")\n";

	this->set_scope_label(label_count++);	
	
	if (else_or_null != 0) {
		string else_condition = else_or_null->HERA_code();
		string move_to_par_reg_else = indent_math + "MOVE(" + this->result_reg_s() +
				 ", " + else_or_null->result_reg_s() + ")\n";
		
		return test_condition + compare + false_branch + then_condition + move_to_par_reg_then +
			true_branch + false_label + else_condition + move_to_par_reg_else + true_label + "\n"; 
	}

	return  test_condition + compare + false_branch + then_condition + move_to_par_reg_then +
				true_branch + false_label + true_label + "\n";
}











/* HERA DATA METHODS */ 

std::string AST_node_::HERA_data()
{
	std::string error_msg = "HERA_data() requested on AST node type without \
				 a declared HERA_data() method - checkout AST.h";
	EM_error(error_msg);	
	return "#error" + error_msg;
}

// HERA_data before CBON()
std::string A_stringExp_::HERA_data()
{      
	std::string label = this->set_label("string" + str(str_count++));
	return "DLABEL(" + this->_label + ")\t"
               + "LP_STRING(" + repr(this->value) + ")\n";
}

std::string A_assignExp_::HERA_data()
{
	A_exp_* exp = this->get_exp();
	return exp->HERA_data();
}

std::string A_callExp_::HERA_data()
{
	A_expList_* args = this->_args;

	if (args != 0) {
		std::string f_args_data = this->_args->HERA_data(); 
		return f_args_data;
	}
	return ""; // no data if no args
}


std::string A_expList_::HERA_data()
{
	A_expList_* expList_data = this;
	std::string output = ""; 	

	while (expList_data != 0) {
		output += expList_data->_head->HERA_data();
		expList_data = expList_data->_tail;
	}
	return output; 
}

// int and op expressions do not have data attributes
std::string A_intExp_::HERA_data()
{
	return "";
}

std::string A_opExp_::HERA_data()
{
	return _left->HERA_data() + _right->HERA_data();
}

std::string A_letExp_::HERA_data()
{
	A_decList_* decs = this->get_decs();
	A_exp_* body = this->get_body();
	return decs->HERA_data() + body->HERA_data();
}

std::string A_decList_::HERA_data()
{
	A_decList_* decs = this;
	string declist_data = "";
	while (decs != 0) {
		A_dec_* head = decs->get_head();
		string head_data = head->HERA_data();
		declist_data += head_data;
		decs = decs->get_tail();
	}
	return declist_data;	
}

std::string A_varDec_::HERA_data()
{
	A_exp_* init_exp = this->get_init_exp();
	return init_exp->HERA_data();
}


std::string A_ifExp_::HERA_data()
{
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();

	string test_condition = test->HERA_data();
	string then_condition = then->HERA_data();

	if (else_or_null != 0) { 
		string else_condition = else_or_null->HERA_data();
		return test_condition + then_condition + else_condition; 
	}
	return test_condition + then_condition;
}

std::string A_seqExp_::HERA_data()
{
	if (this->_seq != 0)
		return this->_seq->HERA_data();
	return "";
}

std::string A_whileExp_::HERA_data()
{
	A_exp_* test = this->get_test();
	A_exp_* body = this->get_body();

	string test_condition = test->HERA_data();
	string body_condition = body->HERA_data();

	if (body == 0)
		return test_condition;
	return test_condition + body_condition;
}

std::string A_forExp_::HERA_data()
{
	A_exp_* lo = this->get_lo();
	A_exp_* hi = this->get_hi();
	A_exp_* body = this->get_body();
	
	string lo_data = lo->HERA_data();
	string hi_data = hi->HERA_data();
	
	if (body != 0) {
		string body_data = body->HERA_data();
		return lo_data + hi_data + body_data;
	}
	return lo_data + hi_data;
}

std::string A_boolExp_::HERA_data()
{
	return "";
}

std::string A_breakExp_::HERA_data()
{
	return "";	
}

std::string A_varExp_::HERA_data()
{
	return "";
}

std::string A_simpleVar_::HERA_data()
{
	// may need to change for string variables
	return "";
}

