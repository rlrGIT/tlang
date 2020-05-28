// Note: to learn how to invoke bison/flex in Eclipse, see https://www.eclipse.org/forums/index.php/t/1075215/
// And refer to the example at https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html#A-Complete-C_002b_002b-Example

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define api.parser.class {tigerParser}

/* next two from https://www.gnu.org/software/bison/manual/html_node/Complete-Symbols.html#Complete-Symbols */
%define api.value.type variant
%define api.token.constructor

%code requires
{
class tigerParseDriver;
}
%param { tigerParseDriver& driver }

// According to the Example, this turns on "location tracking"
%locations
// Thanks to Ian Fisher HC '19 for explaining the details of the parts I'd failed to get working


%{
#include "tigerParseDriver.h"
%}

%token END  0
%token <bool> BOOL
%token <int>  INT
%token <std::string> ID STRING

// NOTE that bison complains if you have the same symbol listed as %token (above) and %type (below)
//      so if you want to add attributes to a token, remove it from the list below

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN L_SQUARE_BRACKET R_SQUARE_BRACKET 
  L_CURLY_BRACE R_CURLY_BRACE
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END_LET OF 
  BREAK NIL
  FUNCTION VAR TYPE DOT
  PLUS MINUS TIMES DIVIDE ASSIGN EQ NEQ LT LE GT GE OR AND NOT
;

/* precedence (stickiness) ... put the stickiest stuff at the bottom of the list */


%nonassoc IF WHILE DO
%precedence THEN BREAK // avoid nonassociative related conflicts by only declaring precedence, not associativity 
%precedence ELSE // else should have higher precedence to match with the closest if 
%precedence ASSIGN
%left AND OR
%nonassoc EQ LT GT LE GE NEQ 
%left PLUS MINUS
%left TIMES DIVIDE
%precedence UMINUS NOT

/* Attributes types for nonterminals are next */
%type <expAttrs>  exp 
%type <A_expList> expList seqExp expSeq  
%type <A_dec> 	  dec 
%type <A_decList> decList
%type <A_field> field
%type <A_fieldList> fieldList
%type <A_fundec> fundec
%type <A_fundecList> fundeclist 

// The line below means our grammar must not have conflicts
//  (no conflicts means it is "an LALR(1) grammar",
//   meaning it must be unambiguous and have some other properties).
%expect 1


%%

%start program;
program: exp[main]				{ EM_debug("Got the main expression of our tiger program.", $main.AST->pos());
		 					  driver.AST = new A_root_($main.AST);
		 						};

exp:    INT[i]					{ $$.AST = A_IntExp(Position::fromLex(@i), $i);
							EM_debug("Got int " + str($i), $$.AST->pos());
								}
	
	| STRING[i]				{ $$.AST = A_StringExp(Position::fromLex(@i), $i);
								EM_debug("Got string expression.", $$.AST->pos()); 
								}
	
	| BOOL[i]				{ $$.AST = A_BoolExp(Position::fromLex(@i), $i);
								EM_debug("Got boolean expression.", $$.AST->pos());
								}

	| NIL[i]				{ $$.AST = A_NilExp(Position::fromLex(@i));
								EM_debug("Got nil expression.", $$.AST->pos());
								}

	| ID[i]					{ $$.AST = A_VarExp(Position::fromLex(@i), A_SimpleVar(Position::fromLex(@i), to_Symbol($i)));
								EM_debug("Got a variable - was it defined/declared?", $$.AST->pos()); 
								}

	| BREAK					{ $$.AST = A_BreakExp(Position::fromLex(@BREAK));
								EM_debug("Got break expression.", $$.AST->pos());
								}

	| exp[exp1] PLUS exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()), 
										A_plusOp, $exp1.AST, $exp2.AST);
							EM_debug("Got plus expression.", $$.AST->pos());
								} 	

	| exp[exp1] MINUS exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_minusOp, $exp1.AST, $exp2.AST);
								EM_debug("Got minus expression.", $$.AST->pos());
								}

	| exp[exp1] TIMES exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_timesOp, $exp1.AST, $exp2.AST);
								EM_debug("Got times expression.", $$.AST->pos());
								}

	| exp[exp1] DIVIDE exp[exp2]		{ $$.AST = A_CallExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
								to_Symbol("div"), A_ExpList($exp1.AST, A_ExpList($exp2.AST, 0)));
								EM_debug("Got call to divide.", $$.AST->pos());
								}
	
	| MINUS exp[exp1] %prec UMINUS		{ $$.AST = A_OpExp(Position::fromLex(@exp1), A_minusOp, 
									A_IntExp(Position::fromLex(@exp1), 0), $exp1.AST);
								}
	
	| exp[exp1] EQ exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_eqOp, $exp1.AST, $exp2.AST);
    								EM_debug("Got equalilty (=) expression.", $$.AST->pos());
								}
 
	| exp[exp1] NEQ exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_neqOp, $exp1.AST, $exp2.AST);
								EM_debug("Got inequality operator (<>)  expression.", $$.AST->pos());
			 					}

	| exp[exp1] LT exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_ltOp, $exp1.AST, $exp2.AST);
								EM_debug("Got inequality operator (<)  expression.", $$.AST->pos());
								}

	| exp[exp1] LE exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_leOp, $exp1.AST, $exp2.AST);
								EM_debug("Got inequality operator (<=)  expression.", $$.AST->pos());
								}

	| exp[exp1] GE exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_geOp, $exp1.AST, $exp2.AST);
								EM_debug("Got inequality operator (>)  expression.", $$.AST->pos());
								}

	| exp[exp1] GT exp[exp2]		{ $$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
											A_gtOp, $exp1.AST, $exp2.AST);
								EM_debug("Got inequality operator (>=)  expression.", $$.AST->pos());
								}

	| exp[exp1] AND exp[exp2]		{ $$.AST = A_IfExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()), 
									$exp1.AST, $exp2.AST, A_BoolExp($exp1.AST->pos(), false));
								EM_debug("Got and (&) expression.", $$.AST->pos());
								}

	| exp[exp1] OR exp[exp2]		{ $$.AST = A_IfExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
										$exp1.AST, A_BoolExp($exp1.AST->pos(), true), $exp2.AST);
								EM_debug("Got and (&) expression.", $$.AST->pos());
								}

	| NOT exp[exp1] 			{ $$.AST = A_IfExp(Position::fromLex(@exp1), $exp1.AST,
									 A_BoolExp($exp1.AST->pos(), false), A_BoolExp($exp1.AST->pos(), true));
								EM_debug("Got and (&) expression.", $$.AST->pos());
								}	
		
	
	| LPAREN RPAREN				{ $$.AST = A_SeqExp(Position::fromLex(@LPAREN), 0);
								EM_debug("Got null expression -- check your references.", $$.AST->pos());
								}

	| LPAREN exp[exp1] RPAREN		{ $$.AST = $exp1.AST;  
								EM_debug("Got paren expression.", $$.AST->pos());
								}

	| LPAREN seqExp[exps] RPAREN		{ $$.AST = A_SeqExp(Position::fromLex(@LPAREN), $exps);
								EM_debug("Got seqeunce expression.", $$.AST->pos());
								}


	| ID[func] LPAREN RPAREN		{ $$.AST = A_CallExp(Position::fromLex(@func), to_Symbol($func), 0);
								EM_debug("Got empty function call.", $$.AST->pos());
								}

	| ID[func] LPAREN expList[args] RPAREN  { $$.AST = A_CallExp(Position::fromLex(@func), to_Symbol($func), $args);
								EM_debug("Got function with arguments.", $$.AST->pos());
								}

	| IF exp[cond1] THEN exp[cond2]		{ $$.AST = A_IfExp(Position::fromLex(@cond1), $cond1.AST, $cond2.AST, 0);
								EM_debug("Got if expression without else.", $$.AST->pos());
								}
	
	| IF exp[cond1] THEN exp[cond2] ELSE exp[cond3]
						 { $$.AST = A_IfExp(Position::fromLex(@cond1), $cond1.AST, $cond2.AST, $cond3.AST);
		 						EM_debug("Got if expression with then and else.", $$.AST->pos());
								}

	| WHILE exp[test] DO exp[body] 		{ $$.AST = A_WhileExp(Position::range($test.AST->pos(), $body.AST->pos()), 
									$test.AST, $body.AST);
								EM_debug("Got while expression.", $$.AST->pos());
								}

	| FOR ID[lvalue] ASSIGN exp[lo] TO exp[hi] DO exp[body]
						{ $$.AST = A_ForExp(Position::range(Position::fromLex(@lvalue), $body.AST->pos()),
									to_Symbol($lvalue), $lo.AST, $hi.AST, $body.AST);
								EM_debug("Got for expression.", $$.AST->pos());
								}

	| ID[lvalue] ASSIGN exp[val] 		{ $$.AST = A_AssignExp(Position::range(Position::fromLex(@lvalue), $val.AST->pos()),
									A_SimpleVar(Position::fromLex(@lvalue), to_Symbol($lvalue)), 
									$val.AST);
								EM_debug("Got assignment expression", $$.AST->pos()); 
								}

	| LET decList[decs] IN expSeq[exps] END_LET 
						{ $$.AST = A_LetExp(Position::fromLex(@LET), $decs, A_SeqExp(Position::fromLex(@IN), $exps));
								EM_debug("Got let expression.", $$.AST->pos());
								};


expList:  exp[head]				{ $$ = A_ExpList($head.AST, 0); 
								}

	| exp[head] COMMA expList[tail] 	{ $$ = A_ExpList($head.AST, $tail); 
								};
	


seqExp:   exp[exp1] SEMICOLON exp[exp2]		{ $$ = A_ExpList($exp1.AST, A_ExpList($exp2.AST, 0));									
								EM_debug("Got sequence expression with two components");
								}
	
	| exp[head] SEMICOLON seqExp[tail]	{ $$ = A_ExpList($head.AST, $tail);
								EM_debug("Got sequence expression with more than two components");
								};



dec:      VAR ID[name] ASSIGN exp[value]	{ $$ = A_VarDec(Position::fromLex(@VAR), to_Symbol($name), 0, $value.AST); 
								EM_debug("Got variable with implicit type declaration");
								}

	| VAR ID[name] COLON ID[type] ASSIGN exp[value] 
						{ $$ = A_VarDec(Position::fromLex(@VAR), to_Symbol($name), to_Symbol($type),
									$value.AST);
								EM_debug("Got variable with explicit type declaration");
								}

	| fundeclist[list] 			{ $$ = A_FunctionDec($list->pos(), $list);
								EM_debug("Got function declaration");
								};


fundeclist: fundec[single]			{ $$ = A_FundecList($single, 0);
								EM_debug("Got singular function declaration in function declist");
								}

	  | fundec[head] fundeclist[tail]	{ $$ = A_FundecList($head, $tail);
								EM_debug("Got function declaration list");
								};


fundec:	  
/*
	  FUNCTION ID[fname] LPAREN RPAREN EQ exp[body] 
						{ $$ = A_Fundec(Position::fromLex(@fname), to_Symbol($fname), 0, 0, $body.AST);
								EM_debug("Got implicitly typed function with no arguments");	
								}

	| FUNCTION ID[fname] LPAREN RPAREN COLON ID[type] EQ exp[body]	
						{ $$ = A_Fundec(Position::fromLex(@fname), to_Symbol($fname), 0, to_Symbol($type), $body.AST);
								EM_debug("Got explicitly typed function with no arguments");
								}
*/	  FUNCTION ID[fname] LPAREN fieldList[fields] RPAREN EQ exp[body]
						{ $$ = A_Fundec(Position::fromLex(@fname), to_Symbol($fname), $fields, 0, $body.AST);
								}

	| FUNCTION ID[fname] LPAREN fieldList[fields] RPAREN COLON ID[type] EQ exp[body]
						{ $$ = A_Fundec(Position::fromLex(@fname), to_Symbol($fname), $fields, to_Symbol($type), $body.AST); 
								};


field:    ID[name]				{ $$ = A_Field(Position::fromLex(@name), to_Symbol($name), 0);
									EM_debug("Got field with implicit type");
								}

	| ID[name] COLON ID[type]		{ $$ = A_Field(Position::fromLex(@name), to_Symbol($name), to_Symbol($type));	
									EM_debug("Got field with explicit type");
								};


fieldList:   %empty				{ $$ = 0;
									EM_debug("Got empty fieldlist");
								} 

           | field[single]			{ $$ = A_FieldList($single, 0);
									EM_debug("Got a fieldList of size 1"); 
								}

	   | field[head] COMMA fieldList[tail] 	{ $$ = A_FieldList($head, $tail);
									EM_debug("Got a fieldList of size 2 or more");
								};
								

expSeq:   %empty				{ $$ = A_ExpList(0, 0); 
								EM_debug("Got empty sequence of expressions");
								}
	
	| exp[exp1] 				{ $$ = A_ExpList($exp1.AST, 0);
								EM_debug("Got single expression in sequence");
								}

	| exp[head] SEMICOLON expSeq[tail]	{ $$ = A_ExpList($head.AST, $tail);
								EM_debug("Got sequence of expressions");
								};


decList: dec[dec1] 				{ $$ = A_DecList($dec1, 0); 
								EM_debug("Got a single declaration");
								}
							
	| dec[head] decList[tail] 		{ $$ = A_DecList($head, $tail); 
								EM_debug("Got a list of declarations");
								};

/*
// Note: In older compiler tools, instead of writing $exp1 and $exp2, we'd write $1 and $3,//        to refer to the first and third elements on the right-hand-side of the production.
//        We can still use this notation (and note that Appel uses it in his book), e.g. the above is like
//					$$.AST = A_OpExp(Position::range($exp1.AST->pos(), $exp2.AST->pos()),
//									 A_timesOp, $1.AST,$3.AST);
// Also: Bison's location system produces information about nonterminals as well as terminals,
//        so we could use @exp1 to get it's information about the locations of exp1
//        writing, e.g., Position::fromLex(@exp1) or instead of $exp1.AST->pos()
*/

%%

void
yy::tigerParser::error(const location_type& l,
          	       const std::string& m)
  {
	  EM_debug("In yy::tigerParser::error");
	  EM_error(m, true, Position::fromLex(l));
  }
