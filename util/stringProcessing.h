//
// Created by anvia on 1/31/2018.
//
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

/**
 * Set of stopwords
 */
static set< string > stopWords = { "a", "all", "an", "and", "any", "are", "as", "at", "be", "been", "but", "by", "few",
                                   "from",
                                   "for", "have", "he", "her", "here", "him", "his", "how",
                                   "i", "in", "is", "it", "its", "many ", "me", "my", "none", "of", "on", "or", "our",
                                   "she",
                                   "some", "the", "their", "them", "there", "they", "that",
                                   "this", "to", "us", "was", "what", "when", "where", "which", "who", "why", "will",
                                   "with", "www",
                                   "you", "your" };

/**
 * Finds the needle in the haystack
 * returns position of first match
 *
 * @param haystack
 * @param needle
 * @return string::iterator
 */
string::iterator findStr ( string needle, string haystack );

/**
 * Finds the next position of the needle in the string
 *
 * @param needle
 * @param pointer
 * @return string::iterator
 */
string::iterator findNext ( string needle, string::iterator haystackPointer );

/**
 * Finds the previous position of the needle in the string
 *
 * @param needle
 * @param haystackPointer
 * @param haystackBeg
 * @return string::iterator
 */
string::iterator findPrev ( string needle, string::iterator haystackPointer, string::iterator haystackBeg );

/**
 * Returns a vector of strings from @originalText, split by @delim
 * Will remove symbols if bool is set
 *
 * @param originalText
 * @param delim
 * @param removeSyms
 * @return vector< string >
 */
vector< string > splitStr ( string originalText, char delim, bool removeSyms );

/**
 * Splits string by multiple delimiters
 *
 * @param originalText
 * @param delims
 * @param removeSyms
 * @return
 */
vector< string > splitStr ( string originalText, vector < char > delims, bool removeSyms );

/**
 * Returns true if element is in array, false otherwise
 *
 * @param vec
 * @return
 */
template <typename T> bool inArray ( T needle, vector < T > haystack );

/**
 * Returns true if @word is a stopword
 *
 * @param word
 * @return bool
 */
bool isStopWord ( string word );

/**
 * Returns lowercase @word
 *
 * @param word
 * @return string
 */
string toLower ( string word );

/**
 * Returns stemmed @word
 *
 * @param word
 * @return string
 */
string stemWord ( string word );

/**
 * Returns a substring [ post, len )
 *
 * @param word
 * @param pos
 * @param len
 * @return string
 */
string subStr ( string word, size_t pos, size_t len );

/**
 * Returns a substring [ begin, end )
 *
 * @param pos
 * @param len
 * @return string
 */
string subStr ( string::iterator begin, string::iterator end );

/**
 * Removes the chars in vector from word
 *
 * @param word
 * @param chars
 * @return string
 */
string stripStr ( string word, vector< char > chars );

/**
 * Removes all chars from word
 * Assumes word is lowercase
 *
 * @param word
 * @return string
 */
string stripStr ( string word );

/**
 * Returns true is character is a letter
 *
 * @param ch
 * @return bool
 */
bool isAlpha ( char ch );

/**
 * Returns true is character is a number
 *
 * @param ch
 * @return bool
 */
bool isNum ( char ch );