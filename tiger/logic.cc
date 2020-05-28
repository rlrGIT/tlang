#include "logic.h"
#include <iostream>
using namespace std;

namespace HaverfordCS {

int assert_failed(const char *fact_expr, const char *file, unsigned int line)
{
	cerr << "assertion failed: " << fact_expr
	     << " at line " << line << " of file " << file << endl;
	throw "precondition failed";
}

int precondition_failed(const char *fact_expr, const char *file, unsigned int line)
{
	cerr << "precondition failed: " << fact_expr
	     << " at line " << line << " of file " << file << endl;
	throw "precondition failed";
}

int postcondition_failed(const char *fact_expr, const char *file, unsigned int line)
{
	cerr << "postcondition failed: " << fact_expr
	     << " at line " << line << " of file " << file << endl;
	throw "precondition failed";
}

int invariant_failed(const char *fact_expr, const char *file, unsigned int line)
{
	cerr << "invariant failed: " << fact_expr
	     << " at line " << line << " of file " << file << endl;
	throw "invariant failed";
}

}
