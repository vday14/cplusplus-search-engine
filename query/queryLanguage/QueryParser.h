//
// Created by Zane Dunnings on 3/16/18.
//


#pragma  once
#include "../../util/DataStructureLib/tuple.cpp"
#include<deque>

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
	string getTestingTree( );

	~QueryParser ( );


	Tuple* queryTree;
	string query;
private:
	void preprocess( );
	void traverse(deque< Tuple*> queue, deque< int> levels, string &output);
	void delete_children( Tuple* node );
	bool MatchOR( string input );
	bool MatchAND( string input );
	bool isAndType( string input );
	bool isOrType( string input );
	Tuple * getDecoratedWord( string input );



	};

