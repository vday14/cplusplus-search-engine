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
 * html encoded mapped to correct char
 */
static set < std::string > encodeSet =
		{ "&quot;", "#34;", "&amp;", "#38;", "&apos;", "#39;", "&lt;", "#60;", "&gt;", "#62;", "&nbsp;", "#160;",
		  "&cent;", "#162;", "&pound;", "#163;", "&yen;", "#165;", "&sect;", "#167;", "&uml;", "#168;", "&copy;",
		  "#169;", "&reg;", "#174;", "&macr;", "#175;", "&deg;", "#176;", "&plusmn;", "#177;", "&acute;", "#180;",
		  "&para;", "#182;", "&middot;", "#183;", "&cedil;", "#184;", "&raquo;", "#187;", "&prime;", "#8242;", "&Prime;",
		  "#8243;", "&lsaquo;", "#8249;", "&rsaquo;", "#8250;", "&oline;", "#8254;", "&frasl;", "#8260;", "&euro;", "#8364;",
		  "&trade;", "#8482;", "&nabla;", "#8711;", "&isin;", "#8712;", "&notin;", "#8713;", "&ni;", "#8715;", "&prod;",
		  "#8719;", "&sum;", "#8721;", "&minus;", "#8722;", "&lowast;", "#8727;", "&radic;", "#8730;", "&int;", "#8747;",
		  "&there4;", "#8756;", "&sim;", "#8764;", "#8773;", "&asymp;", "#8776;", "&ne;", "#8800;", "&equiv;", "#8801;",
		  "&le;", "#8804;", "&ge;", "#8805;", "&lsquo;", "&rsquo;" };


/**
 * Removes weird html encodings
 *
 * @param originalText
 * @return
 */
std::string unEncodeHtml( std::string originalText );

/**
 * Finds the needle in the haystack
 * returns position of first match
 *
 * @param needle
 * @param haystack
 * @return
 */
unsigned long findStr ( string needle, string haystack );

/**
 * Finds the next position of the needle in the string
 *
 * @param needle
 * @param haystackIt
 * @param haystack
 * @return
 */
unsigned long findNext ( string needle, unsigned long haystackIt, string haystack );

/**
 * Finds the previous position of the needle in the string
 *
 *
 * @param needle
 * @param haystackIt
 * @return unsigned long
 */
unsigned long findPrev ( string needle, unsigned long haystackIt, string haystack );

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
vector< string > splitStr ( string originalText, set< char > delims, bool removeSyms );

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
 * Returns a substring [ pos, len )
 *
 * @param word
 * @param pos
 * @param len
 * @return
 */
string subStr ( string word, unsigned long pos, unsigned long len );

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

/**
 * Returns last n characters in string
 * @param input
 * @param n
 * @return
 */
string lastN ( string input, int n );

/**
 * Remove first char in word - used in ranker to remove decorator
 * @param input
 * @return
 */
std::string removeDecorator( std::string input);

string addDecorator ( string input, string decorator );