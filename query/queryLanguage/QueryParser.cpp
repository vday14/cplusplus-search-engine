//
// Created by Zane Dunnings on 3/16/18.
//

#include "QueryParser.h"
#include<unordered_set>
//#include "../../util/stringProcessing.h"
#include<iostream>
/***
 *  QUERY PARSER CLASS
 *
 *  1. Constraint() - CAll this at the highest level, will split on ORs if there are ORs at the highest level,
 *  	Will split on AND if theres an AND at the highest level. b
 *
 *
 */
/***
 * Returns a token of the next word in the query, past the given index
 * @param index
 * @return
 */
Token QueryParser::FindNextToken( int &index ){
	//TODO remove this when you add new ISR
	unordered_set<char> stopChars;
	stopChars.insert(' ');

	int size = 1;
	int start = index;


	while(start + size < query.size())
		{
		if ( query[ start + size ] == '"' )
			{
			++size;
			while( query[start + size ]!= '"' && (start + size < query.size()) )
				{
				++size;
				}
			if(start + size < query.size())
				++size;
			index = start + size;
			string text = query.substr ( start, size );
			if( MatchOR ( text ) )
				return Token( "-OR-" );
			return Token( text );
			}
		else if ( stopChars.count( query[ start + size ] ) > 0)
			{
			while( query[start] == ' ')
				{
				++start;
				}
			index = start + size;
			string text = query.substr ( start, size );
			cout << "horse" << text;

			return Token( text );
			}
		else
			{
			++size;
			}
		}
		index = start + size;
		string text = query.substr ( start, size );
	cout << "horsey: " << text;

	return Token( text );
	}

/*** Builds QueryTree from input query
 *
 * @param input
 */
void QueryParser::parse( string input )
	{
	query = input;
	Token current;
	int location = 0;
	while( location < input.size( ) )
		{
		//TODO needs to be BF Traversal
		current = FindNextToken( location );
		Tuple * next = new Tuple( current );
		queryTree->Next.push_back( next );

		}
	}

/***
 * destructor for the Query Parser
 */
QueryParser::~QueryParser ( )
	{
	delete_children ( queryTree );
	delete queryTree;
	}

/***
 * Traverses down the tree and deletes all of the nodes in the tree
 * @param node
 */
void QueryParser::delete_children( Tuple* node )
	{
	for( int i = 0; i < node->Next.size( ); ++i )
		{
		delete_children( node->Next[ i ] );
		delete node->Next[ i ];
		}
	}

/***
 * Prints the compiled Query for testing
 */
void QueryParser::printCompiledQuery()
	{
	cout << "Query Tree: \n";
	deque<Tuple *> queue;
	deque<int> levelQueue;
	queue.push_back( queryTree );
	levelQueue.push_back( 0 );
	traverse( queue, levelQueue );
	}


void QueryParser::traverse(deque< Tuple*> queue, deque< int> levels)
	{
	int deepest = 0;
	while(!queue.empty())
		{
		Tuple *current = queue.front ( );
		queue.pop_front ( );
		int currLevel = levels.front();
		levels.pop_front ();
		for ( int i = 0; i < current->Next.size ( ); ++i )
			{
			queue.push_back( current->Next[ i ] );
			levels.push_back( currLevel + 1);
			}
		cout << " | ";
		if( currLevel > deepest)
			{
			deepest = currLevel;
			cout << "\n[ "<<deepest<<" ] ";
			}

		cout << " " << current->object.text << " ";
		}
	}

/***
 * Returns whether or not the input string is a conditional OR type
 * @param input
 * @return
 */
bool QueryParser::MatchOR( string input )
	{
	unordered_set<string> ORMatch;
	ORMatch.insert("OR");
	ORMatch.insert("|");
	ORMatch.insert("||");
	ORMatch.insert("or");

	if( ORMatch.count( input ) > 0 )
		{
		return true;
		}
	return false;
	}

/***
 * Returns whether or not the input string is a conditional OR type
 * @param input
 * @return
 */
bool QueryParser::MatchAND( string input )
	{
	unordered_set<string> ORMatch;
	ORMatch.insert("AND");
	ORMatch.insert("&");
	ORMatch.insert("&&");
	ORMatch.insert("and");

	if( ORMatch.count( input ) > 0 )
		{
		return true;
		}
	return false;
	}

/***
 * Highest level query parsing, splits the input string on OR, then builds tree subtrees without
 * @param input
 */
Tuple* QueryParser::Constraint( string input )
	{
	vector<Tuple * > constraintList;
	Tuple *t = new Tuple();
	constraintList = breakOnOR( input );


	if( constraintList.size( ) > 1 )
		t->Type = OrTupleType;
	else
		t->Type = AndTupleType;
		Tuple* toBeKilled = constraintList[ 0 ];
		constraintList = breakOnAND ( input );
	t->Next = constraintList;

	//Iterate through the subcontraints and if there are ORs, then run this again, else split on and for each
	for (int i = 0; i < constraintList.size( ); ++i )
		{
		string word =constraintList[ i ]->object.text;
		//If the subtype needs an or, then build a new or tuple
		if(isOrType(word))
			{
			Tuple* toBeKilled = constraintList[ i ];
			constraintList[ i ] = Constraint ( word );
			constraintList[ i ]->Type = OrTupleType;
			delete toBeKilled;
			toBeKilled = nullptr;
			}
		else if(isAndType(word))
			{
			Tuple* toBeKilled = constraintList[ i ];
			constraintList[ i ] = Constraint ( word );
			constraintList[ i ]->Type = AndTupleType;
			delete toBeKilled;
			toBeKilled = nullptr;
			}
		}



	}


/***
 * Breaks input string on ORs, returns a list of tuples of those strings
 * E.G. hello | (bye OR goodbye) hola -> [ 'hello', '(bye OR goodbye) hola' ]
 * @param input
 * @return
 */
vector<Tuple * > QueryParser::breakOnOR( string input )
	{
	int depth = 0;

	//TODO: use these to cover different types of nested brackets with a couple queues
	unordered_set<char> openBracket;
	openBracket.insert('(');
	openBracket.insert('{');
	openBracket.insert('[');

	unordered_set<char> closedBracket;
	closedBracket.insert(')');
	closedBracket.insert('}');
	closedBracket.insert(']');
	vector<string> query = splitStr (input, ' ', 0);

	vector<Tuple *> constraintList;
	int start = 0;
	for( int i = 0; i < query.size( ); ++i )
		{
		//TODO: remove the parenths matching, just return the biggest string possible
		if( query[ i ] == "(")
			{
			++depth;
			}
		else if( query[ i ] == ")")
			{
			--depth;
			}
		else if( MatchOR( query[ i ]) && depth == 0 )
			{
			string text = query[ 0 ];
			for ( int j = start; j < i; ++ j)
				{
				text+= query[ j ];
				}
			Tuple * subConstraint = new Tuple( text );
			constraintList.push_back( subConstraint );
			start = i + 1;
			}
		else if( i == query.size( ) - 1 )
			{
			string text;
			for ( int j = start; j < i; ++ j)
				{
				text+= query[ j ];
				}
			Tuple * subConstraint = new Tuple( text );
			constraintList.push_back( subConstraint );
			}
		}
		return constraintList;
	}

Tuple * baseConstraint( string input )
	{
//	while( t = simpleConstraint ( input ))
	return nullptr;
	}

/***
 * Returns if a string has an OR at its highest level
 */
bool QueryParser::isOrType( string input )
	{
	vector<string> query = splitStr (input, ' ', 0);
	int depth = 0;
	for( auto word = query.begin();  word != query.end();  ++word )
		{
		if(depth == 0 && MatchOR(*word))
			{
			return true;
			}
		if(*word == "(")
			{
			++depth;
			}
		else if(*word == ")")
			{
			--depth;
			}
		}
	return false;
	}

/***
 * Returns if a string has an OR at its highest level
 */
bool QueryParser::isAndType( string input )
	{
	vector<string> query = splitStr (input, ' ', 0);
	int depth = 0;
	for( auto word = query.begin();  word != query.end();  ++word )
		{
		if(depth == 0 && MatchAND(*word))
			{
			return true;
			}
		if(*word == "(")
			{
			++depth;
			}
		else if(*word == ")")
			{
			--depth;
			}



		}
	return false;
	}

vector<Tuple * > QueryParser::breakOnAND( string input )
	{
	int depth = 0;

	//TODO: use these to cover different types of nested brackets with a couple queues
	unordered_set<char> openBracket;
	openBracket.insert('(');
	openBracket.insert('{');
	openBracket.insert('[');

	unordered_set<char> closedBracket;
	closedBracket.insert(')');
	closedBracket.insert('}');
	closedBracket.insert(']');
	vector<string> query = splitStr (input, ' ', 0);

	vector<Tuple *> constraintList;
	int start = 0;
	for( int i = 0; i < query.size( ); ++i )
		{
		//TODO: remove the parenths matching, just return the biggest string possible
		if( query[ i ] == "(")
			{
			++depth;
			}
		else if( query[ i ] == ")")
			{
			--depth;
			}
		else if( MatchAND( query[ i ]) && depth == 0 )
			{
			string text = query[ 0 ];
			for ( int j = start; j < i; ++ j)
				{
				text+= query[ j ];
				}
			Tuple * subConstraint = new Tuple( text );
			constraintList.push_back( subConstraint );
			start = i + 1;
			}
		else if( i == query.size( ) - 1 )
			{
			string text;
			for ( int j = start; j < i; ++ j)
				{
				text+= query[ j ];
				}
			Tuple * subConstraint = new Tuple( text );
			constraintList.push_back( subConstraint );
			}
		}
	return constraintList;
	}