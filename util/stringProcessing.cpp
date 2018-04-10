//
// Created by Ben Bergkamp on 3/6/18.
//

#include "stringProcessing.h"
#include "Stemmer.h"
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

/**
 * Finds the needle in the haystack
 * returns position of first match
 *
 * @param needle
 * @param haystack
 * @return
 */
unsigned long findStr ( string needle, string haystack )
	{
	unsigned long needleIt = 0;
	unsigned long haystackIt = 0;

	while ( haystackIt < haystack.size( ) )
		{
		//keep looking for instance of a match
		if ( haystack[ haystackIt ] != needle[ needleIt ] )
			{
			++haystackIt;
			}

		else if ( haystack[ haystackIt ] == needle[ needleIt ] )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			unsigned long temp = haystackIt;
			while ( haystack[ temp ] == needle[ needleIt ] )
				{
				++temp;
				++needleIt;
				//if it hits the end of the needleing, it signifies an exact match
				if ( needleIt == needle.size( ) )
					{
					//this is pointing at the beginning of the match
					return haystackIt;
					}

				}
			//need to reset because still has to search rest of the string for a match
			needleIt = 0;
			//sets the original text pointer to where the last search left off
			haystackIt = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return haystackIt;

	}

/**
 * Finds the next position of the needle in the string
 *
 * @param needle
 * @param haystackIt
 * @param haystack
 * @return
 */
unsigned long findNext ( string needle, unsigned long haystackIt, string haystack )
	{
	unsigned long needleIt = 0;
	while ( haystackIt < haystack.size( ) )
		{
		//keep looking for instance of a match
		if ( haystack[ haystackIt ] != needle[ needleIt ] )
			{
			++haystackIt;
			}

		else if ( haystack[ haystackIt ] == needle[ needleIt ] )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			if ( needle.size( ) == 1 )
				{
				return haystackIt;
				}
			unsigned long temp = haystackIt;
			while ( haystack[ temp ] == needle[ needleIt ] )
				{
				++temp;
				++needleIt;
				//if it hits the end of the needleing, it signifies an exact match
				if ( needleIt == needle.size( ) - 1 && haystack[ temp ] == needle[ needleIt ] )
					{
					//this is pointing at the beginning of the match
					return haystackIt;
					}

				}
			//need to reset because still has to search rest of the string for a match
			needleIt = 0;
			//sets the original text pointer to where the last search left off
			haystackIt = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return haystackIt;
	}

/**
 * Finds the previous position of the needle in the string
 *
 *
 * @param needle
 * @param haystackIt
 * @return unsigned long
 */
unsigned long findPrev ( string needle, unsigned long haystackIt, string haystack )
	{
	if ( needle == "" )
		{
		return haystack.size( );
		}
	unsigned long needleIt = needle.size( ) - 1;

	while ( haystackIt >= 0 )
		{
		//keep looking for instance of a match
		if ( haystack[ haystackIt ] != needle[ needleIt ] )
			{
			if ( haystackIt == 0 )
				{
				return haystack.size( );
				}
			--haystackIt;
			}

		else if ( haystack[ haystackIt ] == needle[ needleIt ] )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			unsigned long temp = haystackIt;
			while ( haystack[ temp ] == needle[ needleIt ] )
				{
				//if it hits the end of the needleing, it signifies an exact match
				if ( needleIt == 0 && haystack[ temp ] == needle[ needleIt ] )
					{
					//this is pointing at the beginning of the match
					return temp;
					}

				if ( temp != haystackIt + 1 )
					{
					if ( temp == 0 )
						{
						return haystack.size( );
						}
					--temp;
					}
				if ( needleIt != 0 )
					{
					--needleIt;
					}

				}
			//need to reset because still has to search rest of the string for a match
			needleIt = needle.size( ) - 1;
			//sets the original text pointer to where the last search left off
			haystackIt = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return haystack.size( );
	}

/**
 * Returns a vector of strings from @originalText, split by @delim
 * Will remove symbols if bool is set
 *
 * @param originalText
 * @param delim
 * @param removeChars
 * @return vector < string >
 */
vector< string > splitStr ( string originalText, char delim, bool removeSyms )
	{
	vector< string > splitWords;
	char begin;
	int i = 0;
	while ( i < originalText.size( ) )
		{
		begin = originalText[ i ];
		string word = "";
		while ( begin != delim && i < originalText.size( ) )
			{
			if ( removeSyms)
				{
				if( isAlpha( begin ) || isNum( begin ) )
					{
					word.push_back( begin );
					}
				}
			else
				{
				word.push_back( begin );
				}
			++i;
			begin = originalText[ i ];
			}

		if ( word != "" && word != " " && word[ 0 ] != delim )
			{
			splitWords.push_back( word );
			}
		++i;
		}

	return splitWords;

	}




/**
 * Splits string by multiple delimiters
 *
 * @param originalText
 * @param delims
 * @param removeSyms
 * @return
 */
vector< string > splitStr ( string originalText, set< char > delims, bool removeSyms )
	{
	vector< string > splitWords;
	char begin;
	for ( int i = 0; i < originalText.size( ); ++i )
		{
		begin = originalText[ i ];
		string word = "";
		while ( delims.find( begin ) == delims.end( ) && i < originalText.size( ) )
			{
			if ( removeSyms && ( isAlpha( begin ) || isNum( begin ) ) )
				{
				word.push_back( begin );
				}
			else if ( !removeSyms )
				{
				word.push_back( begin );
				}
			++i;
			begin = originalText[ i ];
			}

		if ( word != "" && word != " " )
			{
			splitWords.push_back( word );
			}
		}

	return splitWords;

	}


/**
 * Returns true if @word is a stopword
 *
 * @param word
 * @return bool
 */
bool isStopWord ( string word )
	{
	return ( stopWords.find( word ) != stopWords.end( ) );

	}

/**
 * Returns lowercase @word
 *
 * @param word
 * @return string
 */
string toLower ( string word )
	{
	unsigned long wordIt = 0;
	string lowerWord = "";
	while ( wordIt < word.size( ) )
		{
		if ( word[ wordIt ] >= 'A' && word[ wordIt ] <= 'Z' )
			{
			lowerWord += ( word[ wordIt ] + 32 );
			}

		else
			{
			lowerWord += word[ wordIt ];
			}
		++wordIt;
		}

	return lowerWord;
	}

/**
 * Returns stemmed @word
 *
 * @param word
 * @return string
 */
string stemWord ( string word )
	{
	Stemmer stemmer;
	word = stemmer.execute( word );
	return word;
	}

/**
 * Returns a substring [ post, len )
 *
 * @param word
 * @param pos
 * @param len
 * @return
 */
string subStr ( string word, unsigned long pos, unsigned long len )
	{
	string substr = "";
	for ( int i = 0; i < len; ++i )
		{
		substr.push_back( word[ pos ] );
		++pos;
		}
	return substr;
	}

/**
 * Removes the chars in vector from word
 *
 * @param word
 * @param chars
 * @return string
 */
string stripStr ( string word, vector< char > chars )
	{
	string wordStripped = "";
	bool isSymbol = false;

	int j = 0;
	while ( j < word.size( ) )
		{
		for ( int i = 0; i < chars.size( ); ++i )
			{
			if ( word[ j ] == chars[ i ] )
				{
				isSymbol = true;
				}
			}
		if ( !isSymbol )
			{
			wordStripped.push_back( word[ j ] );
			}
		++j;
		}
	return wordStripped;
	}

/**
 * Removes all chars from word
 * Assumes word is lowercase
 *
 * @param word
 * @param chars
 * @return string
 */
string stripStr ( string word )
	{
	string wordStripped = "";
	int i = 0;
	while ( i < word.size( ) )
		{
		if ( isAlpha( word[ i ] ) || isNum( word[ i ] ) )
			{
			wordStripped.push_back( word[ i ] );
			}
		++i;
		}
	return wordStripped;
	}

/**
 * Returns true is character is a letter
 *
 * @param ch
 * @return bool
 */
bool isAlpha ( char ch )
	{
	// capital letter
	if ( ch >= 'A' && ch <= 'Z' )
		{
		return true;
		}
	// lowercase letter
	if ( ch >= 'a' && ch <= 'z' )
		{
		return true;
		}
	return false;
	}

/**
 * Returns true is character is a number
 *
 * @param ch
 * @return bool
 */
bool isNum ( char ch )
	{
	if ( ch >= '0' && ch <= '9' )
		{
		return true;
		}
	return false;
	}

/**
 * Returns last n characters in string
 * @param input
 * @param n
 * @return
 */
string lastN ( string input, int n )
	{
	unsigned long inputSize = input.size( );
	return ( n > 0 && inputSize > n ) ? input.substr( inputSize - n ) : "";
	}