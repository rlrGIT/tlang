#include "AST.h"

void AST_node_::set_par_pointers()
{
	std::vector<AST_node_*> children = this->get_children();
	for (AST_node_* child : children) {
		
		child->stored_parent = this;
		child->set_par_pointers();

	}	
}

AST_node_ *AST_node_::get_parent_without_checking()
{
	return stored_parent;
}

AST_node_ *AST_node_::parent()	// get the parent node, after the 'set parent pointers' pass
{
	assert("parent pointers have been set" && stored_parent);
	return stored_parent;
}

AST_node_ *A_root_::parent()
{
	EM_error("Called parent() for root node. This typically happens when A_root has not defined a method for some inherited attribute.", true);
	throw "Oops, shouldn't get here, if 'true' is on for 'is this error fatal";
}
