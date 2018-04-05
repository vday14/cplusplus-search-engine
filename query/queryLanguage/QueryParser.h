//
// Created by Zane Dunnings on 3/16/18.
//

#ifndef EECS398_SEARCH_QUERYPARSER_H
#define EECS398_SEARCH_QUERYPARSER_H

#include "../../util/DataStructureLib/tuple.cpp"
#include<deque>
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
	QueryParser( )
			:queryTree( nullptr ), query( "" ){
		queryTree = new Tuple( TupleType::AndTupleType );
		}
	//QueryParser( string query );

	void parse( string input );

	Token FindNextToken( int &index );
	Tuple * Constraint( string input );
	vector<Tuple * > breakOnOR( string input );
	vector<Tuple * > breakOnAND( string input );

	void printCompiledQuery( );

	~QueryParser ( );


	Tuple* queryTree;
	string query;
private:
	void traverse(deque< Tuple*> queue, deque< int> levels);
	void delete_children( Tuple* node );
	bool MatchOR( string input );
	bool MatchAND( string input );
	bool isAndType( string input );
	bool isOrType( string input );



	};

#endif //EECS398_SEARCH_QUERYPARSER_H
