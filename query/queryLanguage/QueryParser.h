//
// Created by Zane Dunnings on 3/16/18.
//

#ifndef EECS398_SEARCH_QUERYPARSER_H
#define EECS398_SEARCH_QUERYPARSER_H

#include "../../util/DataStructureLib/tuple.cpp"
// Outline of query language from Prof. Nicole Hamilton, University of Michigan 03/15/2018
// 41 lines


//  <Constraint>        ::= <BaseConstraint>
//                              { <OrOp> <BaseConstraint> }
//
//
//  <OrOp>              ::= 'OR' | '|' | '||'
//
//  <BaseConstraint>    ::= <SimpleConstaint>
//                              { [ <AndOp> ] <SimpleConstraint> }
//
//  <AndOp>             ::= 'AND' | '&' | '&&'
//
//  <SimpleConstraint>  ::= <Phrase> | <NestedConstraint> |
//                          <UnaryOp> <SimpleConstraint> |
//                          <SearchWord>
//
//  <UnaryOp>           ::= '+' | '-' | 'NOT'
//
//  <Phrase>            ::= '"' { <SearchWord> } '"'
//
//  <NestedConstraint>  ::= '(' <Constraint> ')'


class QueryParser
	{
public:
	Token *FindNextToken();
	Tuple *FindConstraint();
	bool FindROOp();
	Tuple *FindBaseConstraint();
	bool FindAndOp( );
	Tuple *FindSimpleConstraint( );
	Tuple *FindPhrase( );
	Tuple *FindNestedConstraint( );
	Tuple *FindSearchWord( );

	void printCompiledQuery( );

	QueryParser( char *query );
	};

#endif //EECS398_SEARCH_QUERYPARSER_H
