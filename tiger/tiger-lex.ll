%{

/* 
Define C++ functions that will be used later in the actions of part 3 

	- Dave's list of useful references for flex and bison for C++:
	- http://www.jonathanbeard.io/tutorials/FlexBisonC++
	- http://dinosaur.compilertools.net/flex/flex_19.html
	- https://www.gnu.org/software/bison/manual/html_node/Split-Symbols.html

*/

#include <stdlib.h>
#include "tigerParseDriver.h"
#include "tiger-grammar.tab.hh"

/* next line from https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Scanner.html#Calc_002b_002b-Scanner */
static yy::location loc;

/* 
The function below is somewhat overly verbose; it is designed to serve as an example of
	(a) calling a C function to process something from lex (see the "INT" pattern below), and
	(b) process a collection of characters one at a time, relying on their ASCII values
*/

/* convert array of char (numerals) into an string using the int pattern from lex */
static int textToInt(std::string the_text)
{
	char zero = '0';  // the character 0
	char nine = '9';
	int result = 0;

	/* the length() method of class string returns an "unsigned int" */
	for (unsigned int i = 0; i < the_text.length(); i++) {
		char numeral = the_text[i];
		
		/* We should get here *only* if we have only numerals,
		   since we're called only for the pattern {digit}+ below (part 3) */
		assert (numeral >= zero and numeral <= nine);
		
		/* conversion */
		int numeral_value = numeral-zero;
		result = 10 * result + numeral_value;
	}
	return result;
	
	/* alternate implementation: use hc_string's to_int function:
	   return to_int(the_text); */ 
}

static std::string textToString(std::string input_text)
{
	std::string output = "";
	int size = input_text.length() - 1;
        
	for (int i = 1; i < size; ) {	
		char cur_char = input_text[i];	
		if (cur_char == '\\' && i + 1 < size) {
			char next_char = input_text[i + 1];
			switch (next_char) {
				case 'n': { 
					output += '\n';
					i += 2;
					break; 
				}       
				case 't': {
					output += '\t';
					i += 2;
					break; 
				}       
				case '\\': {
					output += '\\';	
					i += 2;
					break;
				}       
			}       
		}       
		if (i < size)
			output += input_text[i++];
	}                      
return output;          
}

       
/* This uses some stuff created by flex, so it's easiest to just put it here. */
int tigerParseDriver::parse(const std::string &f)
{
	fileName = f;
	
	if (fileName == "" || fileName == "-") {
		yyin = stdin;
	} else if (!(yyin = fopen (fileName.c_str (), "r"))) {
		error ("cannot open " + fileName + ".");
		exit (EXIT_FAILURE);
	}

	yy::tigerParser parser(*this);
	int res = parser.parse();  /* sets this->AST_root */

	fclose(yyin);
	return res;
}

%}

/* In this second section of the lex file (after the %}),
   we can define variables in terms of regular expressions.
   A few other things, like %option, can also be used here.
   C-style comments (like this one) are also legal. */

/* options from the example */
%option noyywrap nounput

integer	[0-9]+

real	[0-9]+\.[0-9]*(e-?[0-9]+)?

comment \/\*([^\*]*\*)([\*]*|[^\*\/]([^\*]*\*))*\/

identifier [a-zA-Z]+[a-zA-Z0-9_]*

string \"[^\"]*\" 

/* " In the third section of the lex file (after the %%),
   we can define the patterns for each token
   in terms of regular expressions and the variables above,
   and give the action (as C++ code) for each token.
   Comments are legal only inside the actions. */

%%

%{
/* Surrounding four lines, and other things involving "loc", are from
https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Scanner.html#Calc_002b_002b-Scanner */

	loc.step();
%}

[ \t]	{ loc.step(); }
[\n\r]	{ loc.lines(yyleng); loc.step(); }

\+			{ return yy::tigerParser::make_PLUS(loc); }
\-			{ return yy::tigerParser::make_MINUS(loc); }
\*			{ return yy::tigerParser::make_TIMES(loc); }
\/			{ return yy::tigerParser::make_DIVIDE(loc); }
\(			{ return yy::tigerParser::make_LPAREN(loc); }
\)			{ return yy::tigerParser::make_RPAREN(loc); }
\,			{ return yy::tigerParser::make_COMMA(loc); }
\<			{ return yy::tigerParser::make_LT(loc); }
\>			{ return yy::tigerParser::make_GT(loc);  }
\<=			{ return yy::tigerParser::make_LE(loc); }
\>=			{ return yy::tigerParser::make_GE(loc); }
\=			{ return yy::tigerParser::make_EQ(loc); }
\:			{ return yy::tigerParser::make_COLON(loc); }
\<\>			{ return yy::tigerParser::make_NEQ(loc); }
\|			{ return yy::tigerParser::make_OR(loc); } 
\!			{ return yy::tigerParser::make_NOT(loc); }
\&			{ return yy::tigerParser::make_AND(loc); }
\;			{ return yy::tigerParser::make_SEMICOLON(loc); }
\:=			{ return yy::tigerParser::make_ASSIGN(loc); }
\.			{ return yy::tigerParser::make_DOT(loc); }
\[			{ return yy::tigerParser::make_L_SQUARE_BRACKET(loc); }
\]			{ return yy::tigerParser::make_R_SQUARE_BRACKET(loc); }

			/* make_INT, make_END from example at https://www.gnu.org/software/bison/manual/html_node/Complete-Symbols.html#Complete-Symbols */	  
let 			{ return yy::tigerParser::make_LET(loc); }

in 			{ return yy::tigerParser::make_IN(loc); }

var 			{ return yy::tigerParser::make_VAR(loc); }

function 		{ return yy::tigerParser::make_FUNCTION(loc); }

nil			{ return yy::tigerParser::make_NIL(loc); }

true 			{ return yy::tigerParser::make_BOOL(true, loc); }

false 			{ return yy::tigerParser::make_BOOL(false, loc); }

if 			{ return yy::tigerParser::make_IF(loc); }

then 			{ return yy::tigerParser::make_THEN(loc); }

else			{ return yy::tigerParser::make_ELSE(loc); }

end			{ return yy::tigerParser::make_END_LET(loc); }

while			{ return yy::tigerParser::make_WHILE(loc); } 

for			{ return yy::tigerParser::make_FOR(loc); }

to 			{ return yy::tigerParser::make_TO(loc); }

break			{ return yy::tigerParser::make_BREAK(loc); }

do 			{ return yy::tigerParser::make_DO(loc); }

{identifier}		{ return yy::tigerParser::make_ID(yytext, loc); }

{comment}		{ loc.step(); }

{integer}		{ return yy::tigerParser::make_INT(textToInt(yytext), loc); }

{string}		{ return yy::tigerParser::make_STRING(textToString(yytext), loc); }
			
			/* this RE matches the literal five characters <EOF>, regardless of upper/lower case   */
\<[Ee][Oo][Ff]\>	{ return yy::tigerParser::make_END(loc); }

			/* <<EOF>> is a flex built-in for an actual end of a file, when there is no more input */
<<EOF>>			{ return yy::tigerParser::make_END(loc); }

.	{ string it = "?"; it[0] = yytext[0]; EM_error("illegal token: " + it); }
%%
