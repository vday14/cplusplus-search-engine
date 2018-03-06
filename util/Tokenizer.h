//
// Created by anvia on 1/31/2018.
//
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "stringProcessing.h"

using namespace std;

class Tokenizer
	{
public:
	Tokenizer ( )
		{
		docIndex = new unordered_map< string, vector< int>>;
		}

	unordered_map< string, vector< int>> *get ( ) const
		{
		return docIndex;
		}

	void execute ( string originalText, int offset )
		{
		vector< string > splitText = splitStr ( originalText, ' ' );
		string lowerString = "";
		for ( int i = 0; i < splitText.size ( ); ++i )
			{
			lowerString = toLower ( splitText[ i ] );
			if ( !isStopWord ( lowerString ) )
				{
				( *docIndex )[ lowerString ].push_back ( offset );
				++offset;
				}
			}
		}

private:
	unordered_map< string, vector< int>> *docIndex;
	};
