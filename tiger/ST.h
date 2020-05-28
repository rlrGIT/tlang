#if ! defined ST_H
#define ST_H 1

// General Symbol Table abstraction
//  Fall 2001 - Spring 2002, by davew@cs.haverford.edu

// Basic operations:
//  Create null or 1-element ST's with constructor.
//  "Fuse" (a.k.a. FuseOneScope) combines disjoint ST's (for dec's in same scope).
//  "Merge" (a.k.a. MergeAndShadow) combines ST's from different scopes
//	merge(outer,inner) has symbols from "inner" shadow those of "outer".
// For details & sample uses of operations, see test_ST in ST.c.

#include <list>
#include "types.h"
#include "symbol.h"

typedef Symbol nametype;  

// This would let us change to using something other than Symbols (e.g. Strings) as names
/* This was originally sym_info - I'm not sure if this should be the sym info struct 
   used in the construction of the symbol table - I assume so - although we may
   need to make this a child class of something more general for things other than
   functions such as variables in the future. 
*/

// Sym_info_ is a node type pointed to by Sym_info
// Sym_Info is a function producing a type of Sym_info (constructor)
// this class may need to be expanded in the future to have more attributes
// for now it is basically a wrapper class.
class std_lib_info {
public: 
	// weird constructor - ask about "uninitialized error"
	std_lib_info(Ty_ty type, int num_args)
	{
		this->type = type;
		this->num_args = num_args;
	}

	Ty_ty get_type()
	{
		return this->type;
	}

	int count_args()
	{
		return num_args;
	}

	string __repr__()
	{
		return  "sym_info struct with attributes: \n" 
			"type (Ty_ty): " + repr(type) + "\n\n";
	}
	
	string __str__()
	{
		return this->__repr__();
	}

protected: 

	Ty_ty type;	
	int num_args;
};



// note that symbol_info type has not been specified - class symbol_info is like a placeholder for a generic variable
// e.g. if a function using this generic form is invoked with type int, gcc automatically creates a version of the function
// and replaces it with type int 
template <class symbol_info> class ST;
template <class symbol_info> class ST_node; // should be private to class ST, but this breaks g++

template <class symbol_info> bool is_name_there(const nametype &look_for_me, const ST<symbol_info> &in_this_table);
template <class symbol_info> symbol_info &lookup(const nametype &must_find_this, const ST<symbol_info> &in_this_table);
template <class symbol_info> ST<symbol_info> merge_or_fuse(const ST<symbol_info> &outer, const ST<symbol_info> &inner, bool merge_dups);

template <class symbol_info> class ST {
public:
	
	ST();
	ST(const nametype &name, const symbol_info &info);
 	friend bool is_name_there<symbol_info>(const nametype &look_for_me, const ST<symbol_info> &in_this_table);
	friend symbol_info &lookup<symbol_info>(const nametype &must_find_this, const ST<symbol_info> &in_this_table);

	
	string __repr__();
	string __str__()  { return this->__repr__(); }

	class duplicate_symbol { // error type for exceptions
	public:
		nametype name;
		duplicate_symbol(const nametype &n);
	};

	class undefined_symbol {  // another exception type
	public:
		nametype name;
		undefined_symbol(const nametype &n);
	};

private:
	ST_node<symbol_info> *head; // Null pointer for empty ST
	const ST_node<symbol_info> *check_for(const nametype &name) const;
	friend ST<symbol_info> merge_or_fuse<symbol_info>(const ST<symbol_info> &outer, const ST<symbol_info> &inner, bool merge_dups);
};


// Build a "single-scope" Symbol Table from 2 single-scope tables.
//   If name sets not disjoint, throw ST::duplicate_symbol(name)
// Implementations are free to throw some other error if
//   s1 or s2 are result of a "merge"
//   rather than constructors & fuse operations.
// NOTE that this does not COPY any symbol_info structures -- they are all SHARED
template <class symbol_info> ST<symbol_info> fuse(const ST<symbol_info> &s1, const ST<symbol_info> &s2);

// Merge two tables for different scopes.
//   The names in the first ST shadow those in the second ST
//   Never complains (unless out of memory)
// NOTE that this does not COPY any symbol_info structures -- they are all SHARED
template <class symbol_info> ST<symbol_info> merge(const ST<symbol_info> &inner, const ST<symbol_info> &outer);
template <class symbol_info>  ST<symbol_info> FuseOneScope(const ST<symbol_info> &s1, const ST<symbol_info> &s2) { return fuse(s1, s2); }
template <class symbol_info>  ST<symbol_info> MergeAndShadow(const ST<symbol_info> &inner, const ST<symbol_info> &outer) { return merge(inner, outer); }
template <class symbol_info> String to_String(const ST<symbol_info> &table);

typedef ST<std_lib_info> function_lib;
typedef ST<Ty_ty> type_lib;
// GLOBAL VAR
extern function_lib HERA_std_lib;
extern type_lib tiger_types; 

#include "ST.t"

#endif
