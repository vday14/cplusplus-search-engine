//
// Created by Ben Bergkamp on 3/6/18.
//

#include "stringProcessing.h"
#include "Stemmer.h"
#include <cassert>
#include <iostream>
using namespace std;

/**
 * Finds the needle in the haystack
 * returns position of first match
 *
 * @param haystack
 * @param needle
 * @return string::iterator
 */
string::iterator findStr ( string needle, string haystack )
	{

	auto beginNeedle = needle.begin( );
	auto beginHaystack = haystack.begin( );

	while ( *beginHaystack != '\0' )
		{
		//keep looking for instance of a match
		if ( *beginHaystack != *beginNeedle )
			{
			++beginHaystack;
			}

		else if ( *beginHaystack == *beginNeedle )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			auto temp = beginHaystack;
			while ( *temp == *beginNeedle )
				{
				++temp;
				++beginNeedle;
				//if it hits the end of the needleing, it signifies an exact match
				if ( *beginNeedle == '\0' )
					{
					//this is pointing at the beginning of the match
					return beginHaystack;
					}

				}
			//need to reset because still has to search rest of the string for a match
			beginNeedle = needle.begin( );
			//sets the original text pointer to where the last search left off
			beginHaystack = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return beginHaystack;

	}

/**
 * Finds the next position of the needle in the string
 *
 * @param needle
 * @param pointer
 * @return string::iterator
 */
string::iterator findNext ( string needle, string::iterator haystackPointer )
	{
	auto beginNeedle = needle.begin( );
	while ( *haystackPointer != '\0' )
		{
		//keep looking for instance of a match
		if ( *haystackPointer != *beginNeedle )
			{
			++haystackPointer;
			}

		else if ( *haystackPointer == *beginNeedle )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			auto temp = haystackPointer;
			while ( *temp == *beginNeedle )
				{
				++temp;
				++beginNeedle;
				//if it hits the end of the needleing, it signifies an exact match
				if ( *beginNeedle == '\0' )
					{
					//this is pointing at the beginning of the match
					return haystackPointer;
					}

				}
			//need to reset because still has to search rest of the string for a match
			beginNeedle = needle.begin( );
			//sets the original text pointer to where the last search left off
			haystackPointer = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return haystackPointer;
	}

/**
 * Finds the previous position of the needle in the string
 *
 * @param needle
 * @param haystackPointer
 * @return string::iterator
 */
string::iterator findPrev ( string needle, string::iterator haystackPointer, string::iterator haystackBeg )
	{
	auto begNeedle = needle.begin( );
	auto endNeedle = begNeedle + ( needle.size( ) - 1 );

	while ( haystackPointer != haystackBeg )
		{
		//keep looking for instance of a match
		if ( *haystackPointer != *endNeedle )
			{
			--haystackPointer;
			}

		else if ( *haystackPointer == *endNeedle )
			{
			/* want to keep the original iterator where it is so it
				can return the beginning of the matched word if found */
			auto temp = haystackPointer;
			while ( *temp == *endNeedle )
				{
				//if it hits the end of the needleing, it signifies an exact match
				if ( endNeedle == begNeedle && *temp == *endNeedle )
					{
					//this is pointing at the beginning of the match
					return temp;
					}

				if ( temp != haystackBeg )
					{
					--temp;
					}
				if ( endNeedle != begNeedle )
					{
					--endNeedle;
					}

				}
			//need to reset because still has to search rest of the string for a match
			endNeedle = begNeedle + ( needle.size( ) - 1 );
			//sets the original text pointer to where the last search left off
			haystackPointer = temp;
			}

		else
			{
			//DO NOTHING
			}
		}

	return needle.end( );
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
vector< string > splitStr ( string originalText, char delim , bool removeSyms)
	{
	vector< string > splitWords;
	auto begin = originalText.begin( );

	while ( *begin != '\0' )
		{
		string word = "";
		while ( *begin != delim && *begin != '\0' )
			{
			if (removeSyms && ( isAlpha( *begin ) || isNum( *begin ) ) )
				{
				word += *begin;
				}
			++begin;
			}

		if (word != "" && word != " ")
			{
			splitWords.push_back( word );
			}
		++begin;
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
vector< string > splitStr ( string originalText, vector < char > delims , bool removeSyms)
	{
	vector< string > splitWords;
	char begin;
	for( int i = 0; i < originalText.size( ); ++i)
		{
		begin = originalText[i];
		string word = "";
		while ( !inArray( begin, delims ) && i < originalText.size() )
			{
			begin = originalText[i];
			if (removeSyms && ( isAlpha( begin ) || isNum( begin ) ) )
				{
				word += begin;
				}
			++i;
			}

		if(inArray( begin, delims ))
			--i;


		if (word != "" && word != " " )
			{
			splitWords.push_back( word );
			}
		}

	return splitWords;

	}

/**
 * Returns true if element is in array, false otherwise
 *
 * @param vec
 * @return
 */
template <typename T> bool inArray ( T needle, vector < T > haystack )
	{
	for ( int i = 0; i < haystack.size( ); ++ i)
		{
		if ( haystack[ i ] == needle )
			{
			return true;
			}
		}
	return false;
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
	auto iter = word.begin( );
	string lowerWord = "";
	while ( *iter != '\0' )
		{
		if ( *iter >= 'A' && *iter <= 'Z' )
			{
			lowerWord += ( *iter + 32 );
			}

		else
			{
			lowerWord += *iter;
			}
		++iter;
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
 * @return string
 */
string subStr ( string word, size_t pos, size_t len )
	{
	string substr = "";
	for ( int i = 0; i < len; ++i )
		{
		substr += word.at( pos );
		++pos;
		}
	return substr;
	}

/**
 * Returns a substring [ begin, end )
 *
 * @param pos
 * @param len
 * @return string
 */
string subStr ( string::iterator begin, string::iterator end )
	{
	string substr = "";
	while ( begin != end )
		{
		substr += *begin;
		++begin;
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
	auto begin = word.begin( );
	bool isSymbol = false;

	while ( begin != word.end( ) )
		{
		for ( int i = 0; i < chars.size( ); ++i )
			{
			if ( *begin == chars[ i ] )
				{
				isSymbol = true;
				}
			}
		if ( !isSymbol )
			{
			wordStripped += *begin;
			}
		++begin;
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
	auto begin = word.begin( );

	while ( begin != word.end( ) )
		{
		if ( isAlpha( *begin ) || isNum( *begin ) )
			{
			wordStripped += *begin;
			}
		++begin;
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