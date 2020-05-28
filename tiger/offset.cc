#include "AST.h"

/*
	The following methods calculate the next available
	location on the stack that can be readily used by
	nodes at runtime

	These methods request from the bottom up, but are
	calculated top down. In this sense, they are inherited.
*/


int AST_node_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	if (stored_parent != 0) {
		return stored_parent->calculate_stack_offset(this, offset_so_far);
	}
	// in case of root	
	return offset_so_far;
}


int A_letExp_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	A_exp_* body = this->get_body();	
	if (child == body) {
		
		EM_debug("Body of let expression requesting offset");
	
		int decs_offset = 0;
		A_decList_* decs = this->get_decs();
		// synthesized
		while (decs != 0) {
			A_dec_* head = decs->get_head();
			decs_offset += head->calc_req_offset();
			decs = decs->get_tail();	
		}
		// check in case of root
		int new_offset = decs_offset + offset_so_far;
		if (stored_parent != 0) {
			return stored_parent->calculate_stack_offset(this, new_offset);	
		}
		return new_offset;
	}
	// if the declist is asking
	if (stored_parent != 0)	{
		return stored_parent->calculate_stack_offset(this, offset_so_far);
	}
		
	return offset_so_far;
}

// parent could be declist or nondeclist
int A_decList_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	int new_offset = this->calc_req_offset() + offset_so_far;
	if (stored_parent != 0) {
		EM_debug("Setting offset: FP + " + str(new_offset));
		return stored_parent->calculate_stack_offset(this, new_offset);
	}
	return new_offset;
}

int A_dec_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	EM_error("calculate_stack_offset not overwritten for A_dec node type", 1);
	return -1;
}

int A_varDec_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	return stored_parent->calculate_stack_offset(this, offset_so_far);
}

int A_forExp_::calculate_stack_offset(AST_node_* child, int offset_so_far)
{
	A_exp_* body = this->get_body();
	if (body == child) {	
		int new_offset = this->calc_req_offset() + offset_so_far;
		EM_debug("For loop increased offset to: " + str(new_offset));	
		if (stored_parent != 0) {
			return stored_parent->calculate_stack_offset(this, new_offset);
		}
		// in case of root
		return new_offset;
	}
	if (stored_parent != 0) {
		return stored_parent->calculate_stack_offset(this, offset_so_far);
	}
	// in case of root
	return offset_so_far;
}


/* 
	The following methods return how much space on the
	stack is required by its respective node type
*/

int AST_node_::set_required_offset()
{
	// default requires no space on stack
	return 0;
}

// dependent on the number of declarations, and the kind of declarations
// remember this is for specific nodes
int A_decList_::set_required_offset()
{
	A_dec_* head = this->get_head();
	int head_offset = head->calc_req_offset();
	return head_offset; 
}

int A_dec_::set_required_offset()
{
	EM_error("calc_req_offset not overwritten for A_dec type node", 1);
	return -1;
}

int A_varDec_::set_required_offset()
{
	// variables only take up a single slot
	return 1;
}

int A_forExp_::set_required_offset()
{
	// for loops require space for lo/hi expressions on stack
	return 2;
}
