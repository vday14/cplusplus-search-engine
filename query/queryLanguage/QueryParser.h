//
// Created by Zane Dunnings on 3/16/18.
//


#pragma  once
#include "../../util/DataStructureLib/tuple.cpp"
#include<deque>
#include <set>

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
			:queryTree( nullptr ), query( "" ), decorate(true){
		}

	void parse( string input );

	Token FindNextToken( int &index );
	Tuple * Constraint( string input );
	vector<Tuple * > breakOnOR( string input );
	vector<Tuple * > breakOnAND( string input );

	void printCompiledQuery( );
	string getTestingTree( );
	void toggleDecorator();

	~QueryParser ( );


	Tuple* queryTree;
	string query;
private:
	bool decorate;
	void stemQuery(string input );
	void preprocess( );
	void traverse(deque< Tuple*> queue, deque< int> levels, string &output);
	void delete_children( Tuple* node );
	bool MatchOR( string input );
	bool MatchAND( string input );
	bool isAndType( string input );
	bool isOrType( string input );
	Tuple * getDecoratedWord( string input );
	bool isStopWord ( string word );


	/**
 * Set of stopwords
 */
	 set< string > stopWords = { "a", "all", "an", "any", "are", "as", "at", "be", "been", "but",
	                                   "by", "few",
	                                   "from",
	                                   "for", "have", "he", "her", "here", "him", "his", "how",
	                                   "i", "in", "is", "it", "its", "many ", "me", "my", "none", "of", "on", "or", "our",
	                                   "she",
	                                   "some", "the", "their", "them", "there", "they", "that",
	                                   "this", "to", "us", "was", "what", "when", "where", "which", "who", "why", "will",
	                                   "with", "www",
	                                   "you", "your" };



	};

