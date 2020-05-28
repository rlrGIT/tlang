Compiler Overview:

/* LEXING, PARSING, CANONICAL FORM */

Lexing and parsing are handled by the .ll and .yy files, respectively. 
Construction of the tree can be broken down into multiple phases:

1) original AST construction (by applying lexed tokens to the grammar)
2) construction of a canonical AST (via a top-down tree traversal)

The construction of a canonical tree allows us to more easily deal with
stack memory management for functions, as we can convert nested function
calls into a series of nested let expressions:

concat(concat("a", "b"), "c") <EOF> 

==>

let 
	var concat1_arg0 := 
		let 
			var concat0_arg0 := "a" 
			var concat0_arg1 := "b" 
		in 
			concat(concat0_arg0, concat0_arg1) 
		end 

	var concat1_arg1 := "c"
in
	concat(concat1_arg0, concat1_arg1)
end

Canonical construction also allows for specific operators with function
calls to be converted as well. For example, operators with string arguments
are converted to function calls to a string comparison function that returns an 
integer. We handle this by converting the original opExp to an integer opExp that 
compares the output of the string comparison function (tstrcmp) to the integer 
constant 0:

"a" < "b" ==> tstrcmp("a", "b") > 0 


/* SYMBOL TABLES */

(see ST.cc, ST.h)

Symbol tables are built on the fly from the node that requested the infromation.
Traversals up and down the tree gather appropriate variables merging them into 
an accumulator table before returning them to the node that called.


/* TYPECHECKING */ 

Typechecking is done top down, but both sets and returns the type of a subtree.
Typechecking and symbol table setting cannot occur independently, due to 
implicitly typed variables. In some cases, we need to typecheck before ST's are set, 
such as during canonicalization or ST setting. 
