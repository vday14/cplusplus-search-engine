//
// Created by Zane Dunnings on 3/16/18.
//

#include "QueryParser.h"
#include<unordered_set>
#include "../../util/stringProcessing.h"
#include<iostream>
/***
 *  QUERY PARSER CLASS
 *
 *  1. Constraint() - CAll this at the highest level, will split on ORs if there are ORs at the highest level,
 *  	Will split on AND if theres an AND at the highest level. b
 *
 *
 */

/*** Builds QueryTree from input query
 *
 * @param input
 */
void QueryParser::parse( string input )
	{
	query = input;
	query = stemWord(query);
	preprocess();
	Token current;
	queryTree = Constraint ( query );
	}

/***
 * takes in a string and seperates on OR, if no OR, then AND. It will create a AND or OR Tuple if theres a complex string.
 * If the string is one word, it will become a WORD tuple and return itself.
 * @param input
 */
Tuple* QueryParser::Constraint( string input )
	{
	vector<Tuple * > constraintList;

	//Break on top level OR
	if( isOrType( input ) )
		{
		Tuple *t = new Tuple( OrTupleType );
		constraintList = breakOnOR ( input );
		t->Next = constraintList;
		return t;
		}
	else if( isAndType ( input ) )
		{
		Tuple *t = new Tuple( AndTupleType);
		constraintList = breakOnAND ( input );
		t->Next = constraintList;
		return t;
		}
	else
		{
		Tuple *t = new Tuple( input, WordTupleType);
		return t;
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
	vector<string> query = splitStr (input, ' ', false);

	vector<Tuple *> constraintList;
	int start = 0;
	for( int i = 0; i < query.size( ); ++i )
		{
		//TODO: remove the parenths matching, just return the biggest string possible
		if( query[ i ] == "(")
			{
			++depth;
			++i;
			string text;

			while ( depth != 0)
				{
				if( i > query.size() )
					break;
				if( query[ i ] == "(")
					++depth;
				else if ( query[ i ] == ")")
					--depth;
				if( depth != 0)
					{
					if( text!= "")
						text+=" ";
					text+=query[ i ];
					++i;
					}
				}
			Tuple * subConstraint = Constraint( text );
			constraintList.push_back( subConstraint );
			start = i + 1;
			}
		else if( query[ i ] == ")")
			{
			--depth;
			}
		else if( MatchOR( query[ i ]) && depth == 0 )
			{
			string text;
			for ( int j = start; j < i; ++ j)
				{
				text+= query[ j ];
				if( j < ( i -1 ) )
					text+= " ";
				}
			if( text != "" && text != " ")
				{
				Tuple * subConstraint = Constraint( text );
				constraintList.push_back( subConstraint );
				}
			start = i + 1;

			}
		else if( i == query.size( ) - 1 )
			{
			string text;
			for ( int j = start; j <= i; ++ j)
				{
				text+= query[ j ];
				if( j <= ( i -1 ) )
					text+= " ";
				}
			Tuple * subConstraint = Constraint( text );
			constraintList.push_back( subConstraint );
			}
		}
	return constraintList;
	}


/***
 * Returns if a string has an OR at its highest level
 */
bool QueryParser::isOrType( string input )
	{
	vector<string> query = splitStr (input, ' ', false);
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
	vector<string> query = splitStr (input, ' ', false);

	if( query.size( ) == 1)
		return false;

	int depth = 0;
	for( auto word = query.begin();  word != query.end();  ++word )
		{
		if( depth == 0 && MatchOR ( *word ))
			return false;
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
	return true;
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
	vector<string> query = splitStr (input, ' ', false);

	vector<Tuple *> constraintList;
	int start = 0;
	for( int i = 0; i < query.size( ); ++i )
		{
		//TODO: remove the parenths matching, just return the biggest string possible
		if( query[ i ] == "(")
			{
			++depth;
			++i;
			string text;

			while ( depth != 0)
				{
				if( query[ i ] == "(")
					++depth;
				else if ( query[ i ] == ")")
					--depth;
				if( depth != 0)
					{
					if( text!= "")
						text+=" ";
					text+=query[ i ];
					++i;
					}
				}
			Tuple * subConstraint = Constraint( text );
			constraintList.push_back( subConstraint );
			start = i + 1;
			}
		else if( query[ i ] == ")")
			{
			--depth;
			}
		else if( MatchAND( query[ i ]) && depth == 0 )
			{
			}
		else if( depth == 0 )
			{
			string text;
			text = query[ i ];
			Tuple * subConstraint =  Constraint( text );
			constraintList.push_back( subConstraint );
			}
		}
	return constraintList;
	}


/***
 * Prints the compiled Query for testing
 */
void QueryParser::printCompiledQuery()
	{
	cout << "\nQuery Tree: \n";
	cout << getTestingTree();

	}

/***
 * generates the string that the printCompiledQuery will print
 *
 */
string QueryParser::getTestingTree()
	{
	string output = "";
	deque<Tuple *> queue;
	deque<int> levelQueue;
	queue.push_back( queryTree );
	levelQueue.push_back( 0 );
	traverse( queue, levelQueue, output );
	return output;
	}


void QueryParser::traverse(deque< Tuple*> queue, deque< int> levels, string &output)
	{
	int deepest = 0;
	int level = 0;
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
		output += " | ";
		if( currLevel > deepest)
			{
			deepest = currLevel;
			output += "\n[ ";
			output += to_string(deepest);
			output += " ] ";
			}

		output += " ";
		output += current->object.text;
		output += " ";
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

void QueryParser::preprocess( )
	{
	string formattedString;
	for( int i = 0; i < query.size(); ++i)
		{
		if( query[ i ] == '(' || query[ i ] == ')')
			{
			formattedString += " ";
			formattedString +=  query[i] ;
			formattedString += " ";
			}
		else
			{
			formattedString+=  query[i];
			}
		}
	query = formattedString;
	}