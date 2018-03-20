
#pragma once

#include <string>
#include "stringProcessing.h"

/**
 * Modeled after the Porter Stemmer algorithm
 * http://snowball.tartarus.org/algorithms/porter/stemmer.html
 */
class Stemmer
	{
public:

	/**
	 * Stemmer Cstor
	 */
	Stemmer ( );

	/**
	 * Returns the stem of a word
	 *
	 * @param word
	 * @return
	 */
	std::string execute ( std::string word );

private:

	/**
	 * Number of consonant sequences
	 *
	 * <c><v>       -> 0
	 * <c>vc<v>  	 -> 1
	 * <c>vcvc<v>   -> 2
	 * <c>vcvcvc<v> -> 3
	 *
	 * @param word
	 * @return
	 */
	int measure ( std::string word );

	/**
	 * Check if a vowel is present in the stem
	 *
	 * @param wordBeg
	 * @param wordEnd
	 * @param word
	 * @return
	 */
	bool isVowelPresent ( unsigned long wordBeg, unsigned long wordEnd, string word );

	/**
	 * Return true if the wordIt points to a consonant
	 *
	 *
	 * @param wordIt
	 * @param word
	 * @return
	 */
	bool isConsonant ( unsigned long wordIt, string word );

	/**
	 * Returns true if should add 'e' to end
	 *
	 * @param word
	 * @return
	 */
	bool addE ( string word );

	/**
	 * Returns true if word ends in double constant
	 * Not LL, SS, ZZ
	 * @param word
	 * @return
	 */
	bool doubleCon ( string word );

	/**
	 * Returns true if a word ends in a
	 * Consonant, Vowel, Consonant pattern
	 * Except when second C is W, X, or Y
	 *
	 * @param word
	 * @return
	 */
	bool endCVC ( std::string word );

	/**
	 * Stem plural words
	 *
	 * @param word
	 * @return
	 */
	std::string step1a ( std::string word );

	/**
	 * Stem ED and ING
	 *
	 * @param word
	 * @return
	 */
	std::string step1b ( std::string word );

	/**
	 * Checks for Y -> I
	 *
	 * @param word
	 * @return
	 */
	string step1c ( string word );

	/**
	 * Step 2
	 *
	 * @param word
	 * @return
	 */
	string step2 ( std::string word );

	/**
	 * Step 3
	 *
	 * @param word
	 * @return
	 */
	std::string step3 ( std::string word );

	/**
	 * Step 4
	 *
	 * @param word
	 * @return
	 */
	std::string step4 ( std::string word );

	/**
	 * Step 5a
	 *
	 * @param word
	 * @return
	 */
	std::string step5a ( std::string word );

	/**
	 * Step 5b
	 *
	 * @param word
	 * @return
	 */
	std::string step5b ( std::string word );

	};


