
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "stringProcessing.h"
#include "Stemmer.h"

using namespace std;

struct wordData {
	int offset;
	int frequency = 0;
	//total num words/unique words??
};
class Tokenizer
	{

public:
	Tokenizer ( )
		{
		docIndex = new unordered_map< string, vector<wordData>>;
		}

	unordered_map< string, vector< wordData>> *get ( ) const
		{
		return docIndex;
		}
	//add type of word parameter, ie paragraph, url etc

    void execute ( string & originalText, int offset )
		{
		vector< string > splitText = splitStr ( originalText, ' ' );
        string processedString = "";
		int vectorLength = 0;
        for ( int i = 0; i < splitText.size( ); ++i )
            {
             // case fold
             processedString = toLower( splitText[ i ] );
             //strip all characters
             processedString = stripStr( processedString );

             if ( !isStopWord ( lowerString ) )
				{
                // stem word
                processedString = stem.execute( processedString );

                wordData currentWord;
				currentWord.offset = offset;
				vectorLength = ( *docIndex )[ lowerString ].size( );
				( *docIndex )[ lowerString ].push_back ( currentWord );
                //incrementing frequency value of the current word
				( *docIndex )[ lowerString ][ vectorLength - 1 ].frequency += 1;
				++offset;
				}
			}
		}



	/**
 	* Tokenizer Cstor
 	*/
	Tokenizer ( );

	/**
 	* Returns pointer to the docIndex dictionary
	 *
 	* @return pointer to unordered_map< string, vector< int>>
 	*/
	unordered_map< string, vector<wordData>> *get ( ) const;

	/**
	 * Executes the Tokenizer
	 * Sends tokens to dictionary
	 *
	 * token -> [offsets]
	 * @param originalText
	 * @param offset
	 */
	void execute ( string &originalText, int offset );

	private:
        unordered_map< string, vector<wordData>> *docIndex;
		Stemmer stem;
	};
