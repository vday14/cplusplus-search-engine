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
                                   "with",
                                   "you", "your" };

/**
 * Finds the needle in the haystack
 * returns position of first match
 * @param haystack
 * @param needle
 * @return string::iterator
 */
string::iterator findStr ( string needle, string haystack );

/**
 * Finds the next position of the needle in the string
 * @param needle
 * @param pointer
 * @return string::iterator
 */
string::iterator findNext ( string needle, string::iterator haystackPointer );

/**
 * Finds the previous position of the needle in the string
 * @param needle
 * @param haystackPointer
 * @return
 */
string::iterator findPrev ( string needle, string::iterator haystackPointer );

/**
 * Returns a vector of strings from @originalText, split by @delim
 * @param originalText
 * @param delim
 * @return
 */
vector< string > splitStr ( string originalText, char delim );

/**
 * Returns true if @word is a stopword
 * @param word
 * @return
 */
bool isStopWord ( string word );

/**
 * Returns lowercase @word
 * @param word
 * @return
 */
string toLower ( string word );

//TODO
/**
 * Returns stemmed @word
 * @param word
 * @return
 */
string stemWord ( string word );

