// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 24 "tiger-grammar.yy" // lalr1.cc:429

#include "tigerParseDriver.h"

#line 44 "tiger-grammar.tab.cc" // lalr1.cc:429

#include "tiger-grammar.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "tiger-grammar.tab.cc" // lalr1.cc:510

  /// Build a parser object.
  tigerParser::tigerParser (tigerParseDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  tigerParser::~tigerParser ()
  {}

  tigerParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  tigerParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  tigerParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  tigerParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  tigerParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  tigerParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  tigerParser::symbol_number_type
  tigerParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  tigerParser::stack_symbol_type::stack_symbol_type ()
  {}

  tigerParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 54: // dec
        value.YY_MOVE_OR_COPY< A_dec > (YY_MOVE (that.value));
        break;

      case 60: // decList
        value.YY_MOVE_OR_COPY< A_decList > (YY_MOVE (that.value));
        break;

      case 52: // expList
      case 53: // seqExp
      case 59: // expSeq
        value.YY_MOVE_OR_COPY< A_expList > (YY_MOVE (that.value));
        break;

      case 57: // field
        value.YY_MOVE_OR_COPY< A_field > (YY_MOVE (that.value));
        break;

      case 58: // fieldList
        value.YY_MOVE_OR_COPY< A_fieldList > (YY_MOVE (that.value));
        break;

      case 56: // fundec
        value.YY_MOVE_OR_COPY< A_fundec > (YY_MOVE (that.value));
        break;

      case 55: // fundeclist
        value.YY_MOVE_OR_COPY< A_fundecList > (YY_MOVE (that.value));
        break;

      case 3: // BOOL
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 51: // exp
        value.YY_MOVE_OR_COPY< expAttrs > (YY_MOVE (that.value));
        break;

      case 4: // INT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 5: // ID
      case 6: // STRING
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  tigerParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 54: // dec
        value.move< A_dec > (YY_MOVE (that.value));
        break;

      case 60: // decList
        value.move< A_decList > (YY_MOVE (that.value));
        break;

      case 52: // expList
      case 53: // seqExp
      case 59: // expSeq
        value.move< A_expList > (YY_MOVE (that.value));
        break;

      case 57: // field
        value.move< A_field > (YY_MOVE (that.value));
        break;

      case 58: // fieldList
        value.move< A_fieldList > (YY_MOVE (that.value));
        break;

      case 56: // fundec
        value.move< A_fundec > (YY_MOVE (that.value));
        break;

      case 55: // fundeclist
        value.move< A_fundecList > (YY_MOVE (that.value));
        break;

      case 3: // BOOL
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 51: // exp
        value.move< expAttrs > (YY_MOVE (that.value));
        break;

      case 4: // INT
        value.move< int > (YY_MOVE (that.value));
        break;

      case 5: // ID
      case 6: // STRING
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  tigerParser::stack_symbol_type&
  tigerParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 54: // dec
        value.move< A_dec > (that.value);
        break;

      case 60: // decList
        value.move< A_decList > (that.value);
        break;

      case 52: // expList
      case 53: // seqExp
      case 59: // expSeq
        value.move< A_expList > (that.value);
        break;

      case 57: // field
        value.move< A_field > (that.value);
        break;

      case 58: // fieldList
        value.move< A_fieldList > (that.value);
        break;

      case 56: // fundec
        value.move< A_fundec > (that.value);
        break;

      case 55: // fundeclist
        value.move< A_fundecList > (that.value);
        break;

      case 3: // BOOL
        value.move< bool > (that.value);
        break;

      case 51: // exp
        value.move< expAttrs > (that.value);
        break;

      case 4: // INT
        value.move< int > (that.value);
        break;

      case 5: // ID
      case 6: // STRING
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  tigerParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  tigerParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  tigerParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  tigerParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  tigerParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  tigerParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  tigerParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  tigerParser::debug_level_type
  tigerParser::debug_level () const
  {
    return yydebug_;
  }

  void
  tigerParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  tigerParser::state_type
  tigerParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  tigerParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  tigerParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  tigerParser::operator() ()
  {
    return parse ();
  }

  int
  tigerParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 54: // dec
        yylhs.value.emplace< A_dec > ();
        break;

      case 60: // decList
        yylhs.value.emplace< A_decList > ();
        break;

      case 52: // expList
      case 53: // seqExp
      case 59: // expSeq
        yylhs.value.emplace< A_expList > ();
        break;

      case 57: // field
        yylhs.value.emplace< A_field > ();
        break;

      case 58: // fieldList
        yylhs.value.emplace< A_fieldList > ();
        break;

      case 56: // fundec
        yylhs.value.emplace< A_fundec > ();
        break;

      case 55: // fundeclist
        yylhs.value.emplace< A_fundecList > ();
        break;

      case 3: // BOOL
        yylhs.value.emplace< bool > ();
        break;

      case 51: // exp
        yylhs.value.emplace< expAttrs > ();
        break;

      case 4: // INT
        yylhs.value.emplace< int > ();
        break;

      case 5: // ID
      case 6: // STRING
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 77 "tiger-grammar.yy" // lalr1.cc:919
    { EM_debug("Got the main expression of our tiger program.", yystack_[0].value.as < expAttrs > ().AST->pos());
		 					  driver.AST = new A_root_(yystack_[0].value.as < expAttrs > ().AST);
		 						}
#line 702 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 3:
#line 81 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IntExp(Position::fromLex(yystack_[0].location), yystack_[0].value.as < int > ());
							EM_debug("Got int " + str(yystack_[0].value.as < int > ()), yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 710 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 4:
#line 85 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_StringExp(Position::fromLex(yystack_[0].location), yystack_[0].value.as < std::string > ());
								EM_debug("Got string expression.", yylhs.value.as < expAttrs > ().AST->pos()); 
								}
#line 718 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 5:
#line 89 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_BoolExp(Position::fromLex(yystack_[0].location), yystack_[0].value.as < bool > ());
								EM_debug("Got boolean expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 726 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 6:
#line 93 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_NilExp(Position::fromLex(yystack_[0].location));
								EM_debug("Got nil expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 734 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 7:
#line 97 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_VarExp(Position::fromLex(yystack_[0].location), A_SimpleVar(Position::fromLex(yystack_[0].location), to_Symbol(yystack_[0].value.as < std::string > ())));
								EM_debug("Got a variable - was it defined/declared?", yylhs.value.as < expAttrs > ().AST->pos()); 
								}
#line 742 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 8:
#line 101 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_BreakExp(Position::fromLex(yystack_[0].location));
								EM_debug("Got break expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 750 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 9:
#line 105 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()), 
										A_plusOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
							EM_debug("Got plus expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 759 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 10:
#line 110 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_minusOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got minus expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 768 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 11:
#line 115 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_timesOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got times expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 777 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 12:
#line 120 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_CallExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
								to_Symbol("div"), A_ExpList(yystack_[2].value.as < expAttrs > ().AST, A_ExpList(yystack_[0].value.as < expAttrs > ().AST, 0)));
								EM_debug("Got call to divide.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 786 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 13:
#line 125 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::fromLex(yystack_[0].location), A_minusOp, 
									A_IntExp(Position::fromLex(yystack_[0].location), 0), yystack_[0].value.as < expAttrs > ().AST);
								}
#line 794 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 14:
#line 129 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_eqOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
    								EM_debug("Got equalilty (=) expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 803 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 15:
#line 134 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_neqOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got inequality operator (<>)  expression.", yylhs.value.as < expAttrs > ().AST->pos());
			 					}
#line 812 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 16:
#line 139 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_ltOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got inequality operator (<)  expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 821 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 17:
#line 144 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_leOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got inequality operator (<=)  expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 830 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 18:
#line 149 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_geOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got inequality operator (>)  expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 839 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 19:
#line 154 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_OpExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
											A_gtOp, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got inequality operator (>=)  expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 848 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 20:
#line 159 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IfExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()), 
									yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST, A_BoolExp(yystack_[2].value.as < expAttrs > ().AST->pos(), false));
								EM_debug("Got and (&) expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 857 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 21:
#line 164 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IfExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()),
										yystack_[2].value.as < expAttrs > ().AST, A_BoolExp(yystack_[2].value.as < expAttrs > ().AST->pos(), true), yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got and (&) expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 866 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 22:
#line 169 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IfExp(Position::fromLex(yystack_[0].location), yystack_[0].value.as < expAttrs > ().AST,
									 A_BoolExp(yystack_[0].value.as < expAttrs > ().AST->pos(), false), A_BoolExp(yystack_[0].value.as < expAttrs > ().AST->pos(), true));
								EM_debug("Got and (&) expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 875 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 23:
#line 175 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_SeqExp(Position::fromLex(yystack_[1].location), 0);
								EM_debug("Got null expression -- check your references.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 883 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 24:
#line 179 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = yystack_[1].value.as < expAttrs > ().AST;  
								EM_debug("Got paren expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 891 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 25:
#line 183 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_SeqExp(Position::fromLex(yystack_[2].location), yystack_[1].value.as < A_expList > ());
								EM_debug("Got seqeunce expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 899 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 26:
#line 188 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_CallExp(Position::fromLex(yystack_[2].location), to_Symbol(yystack_[2].value.as < std::string > ()), 0);
								EM_debug("Got empty function call.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 907 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 27:
#line 192 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_CallExp(Position::fromLex(yystack_[3].location), to_Symbol(yystack_[3].value.as < std::string > ()), yystack_[1].value.as < A_expList > ());
								EM_debug("Got function with arguments.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 915 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 28:
#line 196 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IfExp(Position::fromLex(yystack_[2].location), yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST, 0);
								EM_debug("Got if expression without else.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 923 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 29:
#line 201 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_IfExp(Position::fromLex(yystack_[4].location), yystack_[4].value.as < expAttrs > ().AST, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
		 						EM_debug("Got if expression with then and else.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 931 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 30:
#line 205 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_WhileExp(Position::range(yystack_[2].value.as < expAttrs > ().AST->pos(), yystack_[0].value.as < expAttrs > ().AST->pos()), 
									yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got while expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 940 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 31:
#line 211 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_ForExp(Position::range(Position::fromLex(yystack_[6].location), yystack_[0].value.as < expAttrs > ().AST->pos()),
									to_Symbol(yystack_[6].value.as < std::string > ()), yystack_[4].value.as < expAttrs > ().AST, yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got for expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 949 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 32:
#line 216 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_AssignExp(Position::range(Position::fromLex(yystack_[2].location), yystack_[0].value.as < expAttrs > ().AST->pos()),
									A_SimpleVar(Position::fromLex(yystack_[2].location), to_Symbol(yystack_[2].value.as < std::string > ())), 
									yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got assignment expression", yylhs.value.as < expAttrs > ().AST->pos()); 
								}
#line 959 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 33:
#line 223 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < expAttrs > ().AST = A_LetExp(Position::fromLex(yystack_[4].location), yystack_[3].value.as < A_decList > (), A_SeqExp(Position::fromLex(yystack_[2].location), yystack_[1].value.as < A_expList > ()));
								EM_debug("Got let expression.", yylhs.value.as < expAttrs > ().AST->pos());
								}
#line 967 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 34:
#line 228 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[0].value.as < expAttrs > ().AST, 0); 
								}
#line 974 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 35:
#line 231 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < A_expList > ()); 
								}
#line 981 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 36:
#line 236 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[2].value.as < expAttrs > ().AST, A_ExpList(yystack_[0].value.as < expAttrs > ().AST, 0));									
								EM_debug("Got sequence expression with two components");
								}
#line 989 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 37:
#line 240 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < A_expList > ());
								EM_debug("Got sequence expression with more than two components");
								}
#line 997 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 38:
#line 246 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_dec > () = A_VarDec(Position::fromLex(yystack_[3].location), to_Symbol(yystack_[2].value.as < std::string > ()), 0, yystack_[0].value.as < expAttrs > ().AST); 
								EM_debug("Got variable with implicit type declaration");
								}
#line 1005 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 39:
#line 251 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_dec > () = A_VarDec(Position::fromLex(yystack_[5].location), to_Symbol(yystack_[4].value.as < std::string > ()), to_Symbol(yystack_[2].value.as < std::string > ()),
									yystack_[0].value.as < expAttrs > ().AST);
								EM_debug("Got variable with explicit type declaration");
								}
#line 1014 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 40:
#line 256 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_dec > () = A_FunctionDec(yystack_[0].value.as < A_fundecList > ()->pos(), yystack_[0].value.as < A_fundecList > ());
								EM_debug("Got function declaration");
								}
#line 1022 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 41:
#line 261 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fundecList > () = A_FundecList(yystack_[0].value.as < A_fundec > (), 0);
								EM_debug("Got singular function declaration in function declist");
								}
#line 1030 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 42:
#line 265 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fundecList > () = A_FundecList(yystack_[1].value.as < A_fundec > (), yystack_[0].value.as < A_fundecList > ());
								EM_debug("Got function declaration list");
								}
#line 1038 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 43:
#line 282 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fundec > () = A_Fundec(Position::fromLex(yystack_[5].location), to_Symbol(yystack_[5].value.as < std::string > ()), yystack_[3].value.as < A_fieldList > (), 0, yystack_[0].value.as < expAttrs > ().AST);
								}
#line 1045 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 44:
#line 286 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fundec > () = A_Fundec(Position::fromLex(yystack_[7].location), to_Symbol(yystack_[7].value.as < std::string > ()), yystack_[5].value.as < A_fieldList > (), to_Symbol(yystack_[2].value.as < std::string > ()), yystack_[0].value.as < expAttrs > ().AST); 
								}
#line 1052 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 45:
#line 290 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_field > () = A_Field(Position::fromLex(yystack_[0].location), to_Symbol(yystack_[0].value.as < std::string > ()), 0);
									EM_debug("Got field with implicit type");
								}
#line 1060 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 46:
#line 294 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_field > () = A_Field(Position::fromLex(yystack_[2].location), to_Symbol(yystack_[2].value.as < std::string > ()), to_Symbol(yystack_[0].value.as < std::string > ()));	
									EM_debug("Got field with explicit type");
								}
#line 1068 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 47:
#line 299 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fieldList > () = 0;
									EM_debug("Got empty fieldlist");
								}
#line 1076 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 48:
#line 303 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fieldList > () = A_FieldList(yystack_[0].value.as < A_field > (), 0);
									EM_debug("Got a fieldList of size 1"); 
								}
#line 1084 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 49:
#line 307 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_fieldList > () = A_FieldList(yystack_[2].value.as < A_field > (), yystack_[0].value.as < A_fieldList > ());
									EM_debug("Got a fieldList of size 2 or more");
								}
#line 1092 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 50:
#line 312 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(0, 0); 
								EM_debug("Got empty sequence of expressions");
								}
#line 1100 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 51:
#line 316 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[0].value.as < expAttrs > ().AST, 0);
								EM_debug("Got single expression in sequence");
								}
#line 1108 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 52:
#line 320 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_expList > () = A_ExpList(yystack_[2].value.as < expAttrs > ().AST, yystack_[0].value.as < A_expList > ());
								EM_debug("Got sequence of expressions");
								}
#line 1116 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 53:
#line 325 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_decList > () = A_DecList(yystack_[0].value.as < A_dec > (), 0); 
								EM_debug("Got a single declaration");
								}
#line 1124 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;

  case 54:
#line 329 "tiger-grammar.yy" // lalr1.cc:919
    { yylhs.value.as < A_decList > () = A_DecList(yystack_[1].value.as < A_dec > (), yystack_[0].value.as < A_decList > ()); 
								EM_debug("Got a list of declarations");
								}
#line 1132 "tiger-grammar.tab.cc" // lalr1.cc:919
    break;


#line 1136 "tiger-grammar.tab.cc" // lalr1.cc:919
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  tigerParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  tigerParser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char tigerParser::yypact_ninf_ = -29;

  const signed char tigerParser::yytable_ninf_ = -1;

  const short
  tigerParser::yypact_[] =
  {
     120,   -29,   -29,    12,   -29,    59,   120,   120,     5,   -27,
     -29,   -29,   120,   120,    11,   155,    92,   120,   -29,   142,
       3,   -16,   234,   -22,    26,    41,   -27,   -29,    17,    23,
     -29,   -29,   -29,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   -29,   129,    40,   155,   120,
     -29,   -29,   120,   120,   120,    45,     7,   -29,   -29,   120,
     -28,   -28,   -29,   -29,   262,   262,   262,   262,   262,   262,
     273,   273,   120,   -29,   171,   -29,   203,   155,   219,    51,
      52,   120,   184,    32,   -29,   120,   120,    53,    60,    49,
      28,   155,   120,   -29,   155,   249,    63,    51,    -7,   120,
     -29,   120,   -29,   -29,    66,   120,   155,   155,    33,   155,
     120,   155
  };

  const unsigned char
  tigerParser::yydefact_[] =
  {
       0,     5,     3,     7,     4,     0,     0,     0,     0,     0,
       8,     6,     0,     0,     0,     2,     0,     0,    23,     0,
       0,     0,     0,     0,     0,     0,    53,    40,    41,     0,
      13,    22,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    34,     0,    32,     0,
      24,    25,     0,     0,     0,     0,     0,    54,    42,    50,
       9,    10,    11,    12,    14,    15,    16,    17,    19,    18,
      21,    20,     0,    27,    36,    37,    28,    30,     0,    47,
       0,     0,    51,     0,    35,     0,     0,    45,    48,     0,
       0,    38,    50,    33,    29,     0,     0,    47,     0,     0,
      52,     0,    46,    49,     0,     0,    39,    31,     0,    43,
       0,    44
  };

  const signed char
  tigerParser::yypgoto_[] =
  {
     -29,   -29,     0,     1,    25,   -29,    47,   -29,   -29,   -20,
     -14,    56
  };

  const signed char
  tigerParser::yydefgoto_[] =
  {
      -1,    14,    46,    47,    20,    26,    27,    28,    88,    89,
      83,    29
  };

  const signed char
  tigerParser::yytable_[] =
  {
      15,   104,    52,    24,    25,    19,    21,    22,    35,    36,
      23,    32,    30,    31,    51,    80,    54,    48,    33,    34,
      35,    36,    16,    37,    38,    39,    40,    41,    42,    43,
      44,    55,   105,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    81,    56,    24,    59,    74,
      17,    73,    76,    77,    78,    79,    87,    90,    93,    82,
      98,    96,     1,     2,     3,     4,    99,    97,   102,     5,
      18,   108,   110,    84,    75,    58,     6,   103,   100,     7,
       8,    91,    57,     9,     0,    94,    95,    10,    11,     0,
       0,     0,    82,     0,    12,     1,     2,     3,     4,   106,
       0,   107,     5,    45,     0,   109,    13,     0,     0,     6,
     111,     0,     7,     8,     0,     0,     9,     0,     0,     0,
      10,    11,     0,     1,     2,     3,     4,    12,     0,     0,
       5,     0,     0,     0,     0,     0,    72,     6,     0,    13,
       7,     8,     0,     0,     9,     0,     0,     0,    10,    11,
       0,    49,     0,    50,     0,    12,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,    36,    13,    37,    38,
      39,    40,    41,    42,    43,    44,    33,    34,    35,    36,
      49,    37,    38,    39,    40,    41,    42,    43,    44,    33,
      34,    35,    36,    92,    37,    38,    39,    40,    41,    42,
      43,    44,     0,     0,     0,    33,    34,    35,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    33,    34,
      35,    36,    85,    37,    38,    39,    40,    41,    42,    43,
      44,     0,     0,     0,     0,     0,     0,    33,    34,    35,
      36,    86,    37,    38,    39,    40,    41,    42,    43,    44,
       0,     0,     0,    33,    34,    35,    36,    53,    37,    38,
      39,    40,    41,    42,    43,    44,     0,     0,    33,    34,
      35,    36,   101,    37,    38,    39,    40,    41,    42,    43,
      44,     0,     0,    33,    34,    35,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    33,    34,    35,    36,
       0,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,     0,    37,    38,    39,    40,    41,    42
  };

  const signed char
  tigerParser::yycheck_[] =
  {
       0,     8,    18,    30,    31,     5,     6,     7,    36,    37,
       5,     0,    12,    13,    11,     8,    38,    17,    34,    35,
      36,    37,    10,    39,    40,    41,    42,    43,    44,    45,
      46,     5,    39,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    38,     5,    30,    25,    49,
      38,    11,    52,    53,    54,    10,     5,     5,    26,    59,
      11,     8,     3,     4,     5,     6,    38,     7,     5,    10,
      11,     5,    39,    72,    49,    28,    17,    97,    92,    20,
      21,    81,    26,    24,    -1,    85,    86,    28,    29,    -1,
      -1,    -1,    92,    -1,    35,     3,     4,     5,     6,    99,
      -1,   101,    10,    11,    -1,   105,    47,    -1,    -1,    17,
     110,    -1,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      28,    29,    -1,     3,     4,     5,     6,    35,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    -1,     7,    17,    -1,    47,
      20,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,    29,
      -1,     9,    -1,    11,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    47,    39,    40,
      41,    42,    43,    44,    45,    46,    34,    35,    36,    37,
       9,    39,    40,    41,    42,    43,    44,    45,    46,    34,
      35,    36,    37,     9,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    34,    35,
      36,    37,    19,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    22,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    34,    35,    36,    37,    23,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    34,    35,
      36,    37,    23,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    34,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    44
  };

  const unsigned char
  tigerParser::yystos_[] =
  {
       0,     3,     4,     5,     6,    10,    17,    20,    21,    24,
      28,    29,    35,    47,    50,    51,    10,    38,    11,    51,
      53,    51,    51,     5,    30,    31,    54,    55,    56,    60,
      51,    51,     0,    34,    35,    36,    37,    39,    40,    41,
      42,    43,    44,    45,    46,    11,    51,    52,    51,     9,
      11,    11,    18,    23,    38,     5,     5,    60,    55,    25,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,     7,    11,    51,    53,    51,    51,    51,    10,
       8,    38,    51,    59,    52,    19,    22,     5,    57,    58,
       5,    51,     9,    26,    51,    51,     8,     7,    11,    38,
      59,    23,     5,    58,     8,    39,    51,    51,     5,    51,
      39,    51
  };

  const unsigned char
  tigerParser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      59,    59,    59,    60,    60
  };

  const unsigned char
  tigerParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     4,     4,     6,
       4,     8,     3,     5,     1,     3,     3,     3,     4,     6,
       1,     1,     2,     7,     9,     1,     3,     0,     1,     3,
       0,     1,     3,     1,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const tigerParser::yytname_[] =
  {
  "END", "error", "$undefined", "BOOL", "INT", "ID", "STRING", "COMMA",
  "COLON", "SEMICOLON", "LPAREN", "RPAREN", "L_SQUARE_BRACKET",
  "R_SQUARE_BRACKET", "L_CURLY_BRACE", "R_CURLY_BRACE", "ARRAY", "IF",
  "THEN", "ELSE", "WHILE", "FOR", "TO", "DO", "LET", "IN", "END_LET", "OF",
  "BREAK", "NIL", "FUNCTION", "VAR", "TYPE", "DOT", "PLUS", "MINUS",
  "TIMES", "DIVIDE", "ASSIGN", "EQ", "NEQ", "LT", "LE", "GT", "GE", "OR",
  "AND", "NOT", "UMINUS", "$accept", "program", "exp", "expList", "seqExp",
  "dec", "fundeclist", "fundec", "field", "fieldList", "expSeq", "decList", YY_NULLPTR
  };


  const unsigned short
  tigerParser::yyrline_[] =
  {
       0,    77,    77,    81,    85,    89,    93,    97,   101,   105,
     110,   115,   120,   125,   129,   134,   139,   144,   149,   154,
     159,   164,   169,   175,   179,   183,   188,   192,   196,   200,
     205,   210,   216,   222,   228,   231,   236,   240,   246,   250,
     256,   261,   265,   281,   285,   290,   294,   299,   303,   307,
     312,   316,   320,   325,   329
  };

  // Print the state stack on the debug stream.
  void
  tigerParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  tigerParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1542 "tiger-grammar.tab.cc" // lalr1.cc:1242
#line 343 "tiger-grammar.yy" // lalr1.cc:1243


void
yy::tigerParser::error(const location_type& l,
          	       const std::string& m)
  {
	  EM_debug("In yy::tigerParser::error");
	  EM_error(m, true, Position::fromLex(l));
  }
