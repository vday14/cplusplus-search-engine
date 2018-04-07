//
// Created by Zane Dunnings on 3/17/18.
//

// Outline of query language from Prof. Nicole Hamilton, University of Michigan 03/15/2018
//31 lines
#include<string>
#include<vector>
#include "../../parser/Parser.h"
//#include "../../constraintSolver/ISRAnd.h"
using namespace std;


class Token
	{
public:
	Token()
			:text(""), end( true ), OR( false ), AND( false ){}
	Token( string input )
			:text( input ), end( false ), OR( false ), AND( false )
		{
		if(input ==  "-OR-" )
			OR = true;
		else if(input == "-AND-")
			AND=true;
		}
	//TODO: This is for scaling to add more ISR types
	string text;
	bool OR;
	bool AND;
	bool end;
	};

enum TupleType
	{
	PhraseTupleType,
	OrTupleType,
	AndTupleType,
	NotTupleType,
	SearchTupleType
	};

class Tuple
	{
public:

	Token object;
	vector<Tuple *> Next;
	TupleType Type;
	//ISR *Compile( );
	Tuple( )
			: object( Token() ), Type( AndTupleType ) {}
	Tuple( Token input )
			: object( input ), Type( AndTupleType )
		{
		if(input.AND)
			Type = AndTupleType;
		else if (input.OR)
			Type = OrTupleType;
		else
			Type = PhraseTupleType;
		}
	Tuple( TupleType type)
			: object( Token( ) ), Type( type )
		{
		switch( type )
			{
			case( AndTupleType ):
				object = Token("-AND-");
				break;
			case( OrTupleType ):
				object = Token("-OR-");
			default:
				break;
			}
		}

	};