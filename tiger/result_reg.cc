#include "AST.h"


int AST_node_::sethi_ullman()
{
	std::string error_msg = "Sethi-Ullman allocation was not overridden - went to AST_node.";
	EM_error(error_msg, true);
	return 0;
}

int A_exp_::sethi_ullman()
{
	std::string error_msg = "Sethi-Ullman allocation was not overridden - went to A_exp.";
	EM_error(error_msg, true);
	return 0;	
}

int A_root_::sethi_ullman()
{
/*
	A_exp_* main = this->get_main();
	if (main != 0)
		return main->sethi_ullman();
	return 1;
*/
	return this->sethi_ullman();
}


int A_breakExp_::sethi_ullman()
{
	return 1; // may need to change 
}

int A_opExp_::sethi_ullman()
{
	int new_su;
	int su1 = this->_left->sethi_ullman();
	int su2 = this->_right->sethi_ullman();
	if (su1 == su2) {
		new_su = su1 + 1;
		return new_su; 
	}
	return std::max(su1, su2);
}


/* A_callExp and A_expList are not complete */ 

// should cover function calls with A_expList version
int A_callExp_::sethi_ullman()
{
	A_expList_* args = this->get_args();
	if (args != 0)
		return args->sethi_ullman(); 
	return 1;
}	

// at least as big as anything below it, and it is also the place we put our result
// take the largest node for each one
int A_expList_::sethi_ullman()
{
/*
	A_exp_* head = this->get_head();
	A_expList_* tail = this->get_tail();
	int head_su = head->sethi_ullman();
	
	if (tail != 0) {
		int tail_su = tail->sethi_ullman();
		if (head_su == tail_su)
			return head_su + 1;
		return std::max(head_su, tail_su);
	}
	return head_su;
*/
	A_expList_* args_expList = this;	
	
	int cur_max_su = -1;
	int arg_su_num = -1;
	
	// set sethi_ullman numbers for each argument
	while (args_expList != 0) {
		arg_su_num = args_expList->_head->sethi_ullman();
		if (arg_su_num > cur_max_su) {
			// record su_num and the node it came from if there is a max
			cur_max_su = arg_su_num;
//			max_node = args_expList->_head;
//			max_node->set_su(arg_su_num);
		}
		args_expList = args_expList->_tail;
	}
	return cur_max_su;//max_node->get_su();
}

int A_seqExp_::sethi_ullman()
{
	// if null, treat it like a leaf
	if (this->_seq == 0)
		return 1;
	else 	
		return this->_seq->sethi_ullman();	 
}

int A_ifExp_::sethi_ullman()
{
	A_exp_* test = this->get_test();
	A_exp_* then = this->get_then();
	A_exp_* else_or_null = this->get_else_or_null();

	int test_su = test->sethi_ullman();
	int then_su = then->sethi_ullman();
	
	if (else_or_null != 0) {
		int else_su = else_or_null->sethi_ullman();
	//	if (test_su == then_su && then_su == else_su) {
	//		return test_su + 1;
	//	}
		return std::max(std::max(test_su, then_su), else_su);
	}
	//if (test_su == then_su)
	//	return test_su + 1;
	return std::max(test_su, then_su);
}

// not sure if this is quite right yet
int A_whileExp_::sethi_ullman()
{
	A_exp_* test = this->get_test();
	A_exp_* body = this->get_body();

	int test_su = test->sethi_ullman();
	int body_su = body->sethi_ullman();
	
	if (body_su == 0)
		return test_su;

	if (test_su == body_su) 
		return test_su + 1;

	return std::max(test_su, body_su);	
}

int A_forExp_::sethi_ullman()
{
	A_exp_* lo = this->get_lo();
	A_exp_* hi = this->get_hi();
	A_exp_* body = this->get_body();
	
	int lo_su = lo->sethi_ullman();
	int hi_su = hi->sethi_ullman();
	
	if (body != 0) {
		int body_su = body->sethi_ullman();
		if (lo_su == hi_su && hi_su == body_su) {
			return body_su + 1;
		}
		return std::max(lo_su, std::max(hi_su, body_su));
	}
	if (lo_su == hi_su) {
		return lo_su + 1;
	}
	return std::max(lo_su, hi_su);
}


// covers ints, strings, booleans - acts as a base case
int A_leafExp_::sethi_ullman()
{
	return 1;
}

int A_letExp_::sethi_ullman()
{
	A_decList_* decs = this->get_decs();
	A_exp_* exps = this->get_body();

	int decs_su = decs->sethi_ullman();
	int exps_su = exps->sethi_ullman();
	
	return std::max(decs_su, exps_su);
}


int A_dec_::sethi_ullman()
{
	EM_error("Sethi-ullman for declarations not overwritten", 1);
	return 0;
}

int A_decList_::sethi_ullman()
{

	A_decList_* decs = this;	
//	A_dec_* max_node;
	
//	bool all_equal = true;
	int cur_max_su = -1;
	int dec_su_num = -1;
	
	// set sethi_ullman numbers for each argument
	while (decs != 0) {
		A_dec_* head = decs->get_head();
		dec_su_num = head->sethi_ullman();
		if (dec_su_num > cur_max_su) {
			// record su_num and the node it came from if there is a max
			cur_max_su = dec_su_num;
		//	max_node = head;
		//	max_node->set_su(dec_su_num);
		//	all_equal = false;
	//	}
		//if (dec_su_num < cur_max_su) {
		//	all_equal = false;
		} 
		decs = decs->get_tail();
	}
	// sethi ullman 
	//if (all_equal) {
	//	return dec_su_num + 1;
	return cur_max_su;
}


int A_assignExp_::sethi_ullman()
{
	A_exp_* exp_val = this->get_exp();
	return exp_val->sethi_ullman();
}

int A_varDec_::sethi_ullman()
{
	A_exp_* init_exp = this->get_init_exp();
	return init_exp->sethi_ullman();
}

int A_varExp_::sethi_ullman()
{
	return 1;
}

int A_simpleVar_::sethi_ullman()
{
	return 1;
}

