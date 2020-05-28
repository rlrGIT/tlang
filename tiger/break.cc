#include "AST.h"
/* 
	set an attribute determining whether the current node is a 
	child of a while loop
*/

bool AST_node_::in_loop()
{
	if (stored_parent != 0)	{
		return stored_parent->in_loop();	
	}
	return false; // handles root node
}

bool A_whileExp_::in_loop()
{
	return true;
}

bool A_forExp_::in_loop()
{
	return true;
}

// necessary for call from class
bool A_breakExp_::in_loop()
{
	if (stored_parent != 0) {
		return stored_parent->in_loop();
	}
	return false;
}

string AST_node_::get_break_branch()
{
	if (stored_parent != 0) 
		return stored_parent->get_break_branch();
	// note default is set to "none" this will be checked during typechecking	
	return "";
}

string A_whileExp_::get_break_branch()
{
	return this->get_break_label();
}

string A_forExp_::get_break_branch()
{
	return this->get_break_label();
}

string A_breakExp_::get_break_branch()
{
	if (stored_parent != 0) 
		return stored_parent->get_break_branch();
	return "";
}
