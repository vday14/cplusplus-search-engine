//
// Created by Ben Bergkamp on 3/6/18.
//

#include "stringProcessing.h"
#include "Stemmer.h"

using namespace std;

/**
 * Finds the needle in the haystack
 * returns position of first match
 *
 * @param haystack
 * @param needle
 * @return string::iterator
 */
string::iterator findStr (string needle, string haystack )
	{

	auto beginNeedle = needle.begin ( );
	auto beginHaystack = haystack.begin();

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
			beginNeedle = needle.begin ( );
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
string::iterator findNext (string needle, string::iterator haystackPointer )
	{
	auto beginNeedle = needle.begin ( );
	auto beginHaystack = haystackPointer;
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
			beginNeedle = needle.begin ( );
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
 * Finds the previous position of the needle in the string
 *
 * @param needle
 * @param haystackPointer
 * @return
 */
string::iterator findPrev ( string needle, string::iterator haystackPointer )
	{
		auto beginNeedle = needle.begin ( );
		auto beginHaystack = haystackPointer;
		while ( *beginHaystack != '\0' )
			{
			//keep looking for instance of a match
			if ( *beginHaystack != *beginNeedle )
				{
				--beginHaystack;
				}

			else if ( *beginHaystack == *beginNeedle )
				{
				/* want to keep the original iterator where it is so it
					can return the beginning of the matched word if found */
				auto temp = beginHaystack;
				while ( *temp == *beginNeedle )
					{
					--temp;
					--beginNeedle;
					//if it hits the end of the needleing, it signifies an exact match
					if ( *beginNeedle == '\0' )
						{
						//this is pointing at the beginning of the match
						return beginHaystack;
						}

					}
				//need to reset because still has to search rest of the string for a match
				beginNeedle = needle.begin ( );
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
 * Returns a vector of strings from @originalText, split by @delim
 *
 * @param originalText
 * @param delim
 * @return
 */
vector< string > splitStr ( string originalText, char delim )
	{
	vector< string > splitWords;
	auto begin = originalText.begin ( );

	while ( *begin != '\0' )
	{
		string word = "";
		while ( *begin != delim && *begin != '\0' )
		{
			word += *begin;
			++begin;
		}

		splitWords.push_back ( word );
		++begin;
	}

	return splitWords;

	}

/**
 * Returns true if @word is a stopword
 *
 * @param word
 * @return
 */
bool isStopWord ( string word )
	{
	return ( stopWords.find ( word ) != stopWords.end ( ) );

	}

/**
 * Returns lowercase @word
 *
 * @param word
 * @return
 */
string toLower ( string word )
	{
	auto iter = word.begin ( );
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
 * @return
 */
string stemWord(string word)
	{
	Stemmer stemmer;
	word = stemmer.execute ( word );
	return word;
	}
