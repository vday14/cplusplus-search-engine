
#include "Stemmer.h"
#include "stringProcessing.h"
#include <cassert>
#include <string>

/**
 * Stemmer Cstor
 */
Stemmer::Stemmer ( )
	{ }

/**
 * Returns the stem of a word
 *
 * @param word
 * @return
 */
std::string Stemmer::execute ( std::string word )
	{
	word = step1a( word );
	word = step1b( word );
	word = step1c( word );
	word = step2( word );
	word = step3( word );
	word = step4( word );
	word = step5a( word );
	word = step5b( word );
	return word;
	}

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
int Stemmer::measure ( std::string word )
	{
	// measure
	int m = 0;
	unsigned long wordIt = 0;
	unsigned long wordEnd = word.size( ) - 1;
	// Looking for CVC pattern
	while ( wordIt <= wordEnd )
		{
		if ( !isConsonant( wordIt, word ) )
			{
			break;
			}
		wordIt += 1;
		}
	if ( wordIt > wordEnd )
		{
		return m;
		}
	wordIt += 1;

	while ( wordIt <= wordEnd )
		{
		while ( wordIt <= wordEnd )
			{
			if ( isConsonant( wordIt, word ) )
				{
				break;
				}
			wordIt += 1;
			}
		if ( wordIt > wordEnd )
			{
			return m;
			}
		wordIt += 1;
		m += 1;
		while ( wordIt <= wordEnd )
			{
			if ( !isConsonant( wordIt, word ) )
				{
				break;
				}
			wordIt += 1;
			}
		if ( wordIt > wordEnd )
			{
			return m;
			}
		wordIt += 1;
		}
	return m;

	}

/**
 * Check if a vowel is present in the stem
 *
 * @param wordBeg
 * @param wordEnd
 * @param word
 * @return
 */
bool Stemmer::isVowelPresent ( unsigned long wordBeg, unsigned long wordEnd, string word )
	{
	while ( wordBeg != wordEnd && wordBeg < word.size( ) )
		{
		if ( !isConsonant( wordBeg, word ) )
			{
			return true;
			}
		++wordBeg;
		}
	return false;
	}

/**
 * Return true if the wordIt points to a consonant
 *
 *
 * @param wordIt
 * @param word
 * @return
 */
bool Stemmer::isConsonant ( unsigned long wordIt, string word )
	{
	assert ( wordIt < word.size( ) );

	char wordChar = word[ wordIt ];
	if ( wordChar == 'a' || wordChar == 'e' || wordChar == 'i' || wordChar == 'o' || wordChar == 'u' )
		{
		return false;
		}
	if ( wordChar == 'y' )
		{
		if ( wordIt == 0 )
			{
			return true;
			}
		else
			{
			return ( !isConsonant( wordIt - 1, word ) );
			}
		}
	return true;
	}

/**
 * Returns true if should add 'e' to end
 *
 * @param word
 * @return
 */
bool Stemmer::addE ( string word )
	{
	// AT -> ATE
	// BL -> BLE
	// IZ -> IZE
	string substr = lastN( word, 2 );

	if ( substr == "at" || substr == "bl" || substr == "iz" )
		{
		return true;
		}
	else
		{
		return false;
		}
	}

/**
 * Returns true if word ends in double constant
 * Not LL, SS, ZZ
 * @param word
 * @return
 */
bool Stemmer::doubleCon ( string word )
	{
	unsigned long endWord = word.size( ) - 1;

	if ( word.size( ) > 2 && word[ endWord ] == word[ endWord - 1 ] )
		{
		char doubleConsonant = word[ endWord ];
		if ( doubleConsonant == 'l' || doubleConsonant == 's' || doubleConsonant == 'z' )
			{
			return false;
			}
		else
			{
			return true;
			}
		}
	return false;
	}

/**
 * Returns true if a word ends in a
 * Consonant, Vowel, Consonant pattern
 * Except when second C is W, X, or Y
 *
 * @param word
 * @return
 */
bool Stemmer::endCVC ( std::string word )
	{
	unsigned long endWord = word.size( ) - 1;

	if ( word.size( ) > 2 )
		{
		// the stem ends cvc
		if ( isConsonant( endWord, word ) && !isConsonant( endWord - 1, word ) &&
		     isConsonant( endWord - 2, word ) )
			{
			// the second c is not W, X or Y
			if ( word[ endWord - 1 ] != 'w' && word[ endWord - 1 ] != 'x' && word[ endWord - 1 ] != 'y' )
				{
				return true;
				}
			}
		}
	return false;
	}

/**
 * Stem plural words
 *
 * @param word
 * @return
 */
std::string Stemmer::step1a ( std::string word )
	{

	// check S at end
	if ( word[ word.size( ) - 1 ] == 's' )
		{
		string wordStem = word;

		auto substrSSES = lastN( word, 4 );
		auto substrIES = lastN( word, 3 );
		auto substrSS = lastN( word, 2 );
		// sses -> ss
		// caresses -> caress
		if ( substrSSES == "sses" )
			{
			wordStem = subStr( word, 0, word.size( ) - 2 );
			}
			// ies -> i
			// ponies -> poni
		else if ( substrIES == "ies" )
			{
			wordStem = subStr( word, 0, word.size( ) - 2 );
			}
			// ss -> ss
			// caress -> caress
		else if ( substrSS == "ss" )
			{
			// do nothing
			}
			// s ->
			// cats -> cat
		else if ( word[ word.size( ) - 1 ] == 's' )
			{
			wordStem = subStr( word, 0, word.size( ) - 1 );
			}
		else
			{
			wordStem = word;
			}

		return wordStem;
		}
	return word;
	}

/**
 * Stem ED and ING
 *
 * @param word
 * @return
 */
std::string Stemmer::step1b ( std::string word )
	{
	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;

	string wordStem( word.begin( ), word.end( ) );

	auto lastThree = lastN( word, 3 );
	auto lastTwo = lastN( word, 2 );

	int m = measure( word );
	// check EED at end and m > 0
	// feed -> feed
	// agreed -> agree
	if ( m > 1 && lastThree == "eed" )
		{
		wordStem = subStr( word, 0, word.size( ) - 1 );
		}
		// check ED at end and preceeded by substr with vowel
		// plastered -> plaster
		// bled -> bled
	else if ( m > 1 && lastTwo == "ed" && isVowelPresent( 0, word.size( ) - 2, word ) )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		if ( addE( wordStem ) || ( m == 1 && endCVC( wordStem + 'e' ) ) )
			{
			wordStem += 'e';
			}
		else if ( doubleCon( wordStem ) )
			{
			wordStem = subStr( word, 0, wordStem.size( ) - 1 );
			}
		}
		// check ING at end and proceeded by substr with vowel
		// motoring -> motor
		// sing -> sing
	else if ( lastThree == "ing" && isVowelPresent( 0, word.size( ) - 3, word ) )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		auto a = addE( wordStem );
		auto m = measure( wordStem );
		auto e = endCVC( wordStem + 'e' );
		if ( addE( wordStem ) || ( measure( wordStem ) == 1 && endCVC( wordStem ) ) )
			{
			wordStem += 'e';
			}
		else if ( doubleCon( wordStem ) )
			{
			wordStem = subStr( word, 0, wordStem.size( ) - 1 );
			}
		}

	return wordStem;

	}

/**
 * Checks for Y -> I
 * @param word
 * @return
 */
string Stemmer::step1c ( string word )
	{

	// Y -> I
	// happy -> happi
	// sky -> sky
	if ( word[ word.size( ) - 1 ] == 'y' )
		{
		if ( isVowelPresent( 0, word.size( ) - 1, word ) )
			{
			word = subStr( word, 0, word.size( ) - 1 );
			word += 'i';
			}
		}
	return word;
	}

/**
 * Step 2
 *
 * @param word
 * @return
 */
string Stemmer::step2 ( std::string word )
	{
	if ( measure( word ) == 0 )
		{
		return word;
		}

	string wordStem = word;

	string lastSeven = lastN( word, 7 );
	string lastSix = lastN( word, 6 );
	string lastFive = lastN( word, 5 );
	string lastFour = lastN( word, 4 );
	string lastThree = lastN( word, 3 );
	string lastTwo = lastN( word, 2 );

	// ATIONAL -> ATE
	// relational -> relate
	if ( lastSeven == "ational" && word.size( ) != 8 )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		wordStem += 'e';
		}
		// TIONAL -> TION
		// conditional -> condition
		// rational -> rational
	else if ( lastSix == "tional" && measure( subStr( word, 0, word.size( ) - 6 ) ) > 0 )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		}
		// ENCI -> ENCE
		// valenci -> valence
	else if ( lastFour == "enci" )
		{
		wordStem = subStr( word, 0, word.size( ) - 1 );
		wordStem += 'e';
		}
		// ANCI -> ANCE
		// hesitanci ->	hesitance
	else if ( lastFour == "anci" )
		{
		wordStem = subStr( word, 0, word.size( ) - 1 );
		wordStem += 'e';
		}
		// IZER -> IZE
		// digitizer -> digitize
	else if ( lastFour == "izer" )
		{
		wordStem = subStr( word, 0, word.size( ) - 1 );
		}
		// ABLI -> ABLE
		// conformabli -> comformable
	else if ( lastFour == "abli" )
		{
		wordStem = subStr( word, 0, word.size( ) - 1 );
		wordStem += 'e';
		}
		// ALLI -> AL
		// radicalli -> radical
	else if ( lastFour == "alli" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// ENTLI -> ENT
		// differentli -> different
	else if ( lastFive == "entli" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// ELI -> E
		// vileli -> vile
	else if ( lastThree == "eli" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// OUSLI -> OUS
		// analogousli	->	analogous
	else if ( lastFive == "ousli" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// IZATION -> IZE
		// vietnamization	->	vietnamize
	else if ( lastSeven == "ization" )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		wordStem += 'e';
		}
		// ATION -> ATE
		// predication	->	predicate
	else if ( lastFive == "ation" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		wordStem += 'e';
		}
		// ATOR -> ATE
		// predication	->	predicate
	else if ( lastFour == "ator" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		wordStem += 'e';
		}
		// ALISM -> AL
		// feudalism -> feudal
	else if ( lastFive == "alism" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// IVENESS -> IVE
		// decisivenss	->	decisive
	else if ( lastSeven == "iveness" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// FULNESS -> FUL
		// hopefulness	->	hopeful
	else if ( lastSeven == "fulness" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// OUSNESS -> OUS
		// callousness	->	callous
	else if ( lastSeven == "ousness" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// ALITI -> AL
		// formalit	->	formal
	else if ( lastFive == "aliti" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// IVITI -> IVE
		// sensitiviti	->	sensitive
	else if ( lastFive == "iviti" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		wordStem += 'e';
		}
		// BILITI -> BLE
		// sensibiliti	->	sensible
	else if ( lastSix == "biliti" )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		wordStem += "le";
		}

	return wordStem;
	}

/**
 * Step 3
 *
 * @param word
 * @return
 */
std::string Stemmer::step3 ( std::string word )
	{

	if ( measure( word ) == 0 )
		{
		return word;
		}

	string wordStem = word;
	string lastFive = lastN( word, 5 );
	string lastFour = lastN( word, 4 );
	string lastThree = lastN( word, 3 );

	// ICATE -> IC
	// triplicate -> triplic
	if ( lastFive == "icate" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ATIVE ->
		// formative -> form
	else if ( lastFive == "ative" )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		}
		// ALIZE -> AL
		// formalize -> formal
	else if ( lastFive == "alize" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ICITI -> IC
		// electriciti ->	electric
	else if ( lastFive == "iciti" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ICAL -> IC
		// electrical -> electric
	else if ( lastFour == "ical" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// FUL ->
		// hopeful -> hope
	else if ( lastThree == "ful" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// NESS ->
		// goodness -> good
	else if ( lastFour == "ness" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}

	return wordStem;
	}

/**
 * Step 4
 *
 * @param word
 * @return
 */
std::string Stemmer::step4 ( std::string word )
	{
	if ( measure( word ) <= 2 )
		{
		return word;
		}

	string wordStem = word;
	string lastFive = lastN( word, 5 );
	string lastFour = lastN( word, 4 );
	string lastThree = lastN( word, 3 );
	string lastTwo = lastN( word, 2 );

	// AL ->
	// revival -> reviv
	if ( lastTwo == "al" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// ANCE ->
		// allowance -> allow
	else if ( lastFour == "ance" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// ENCE ->
		// inference -> infer
	else if ( lastFour == "ence" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// ER ->
		// airliner ->	airlin
	else if ( lastTwo == "er" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// IC ->
		// gyroscopic -> gyroscope
	else if ( lastTwo == "ic" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// ABLE ->
		// adjustable -> adjust
	else if ( lastFour == "able" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// IBLE ->
		// goodness -> good
	else if ( lastFour == "ible" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// ANT ->
		// irritant -> irrit
	else if ( lastThree == "ant" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// EMENT ->
		// replacement -> replace
	else if ( lastFive == "ement" )
		{
		wordStem = subStr( word, 0, word.size( ) - 5 );
		}
		// MENT ->
		// adjustment -> adjust
	else if ( lastFour == "ment" )
		{
		wordStem = subStr( word, 0, word.size( ) - 4 );
		}
		// ENT ->
		// dependent -> depend
	else if ( lastThree == "ent" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ION ->
		// stem must end in 't' or 's'
		// adoption -> adopt
	else if ( lastThree == "ion" && ( lastFour == "sion" || lastFour == "tion" ) )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// OU ->
		// homologou -> homolog
	else if ( lastTwo == "ou" )
		{
		wordStem = subStr( word, 0, word.size( ) - 2 );
		}
		// ISM ->
		// communism -> commun
	else if ( lastThree == "ism" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ATE ->
		// activate -> activ
	else if ( lastThree == "ate" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// ITI ->
		// angulariti -> angular
	else if ( lastThree == "iti" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// OUS ->
		// homologous -> homolog
	else if ( lastThree == "ous" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// IVE ->
		// effective -> effect
	else if ( lastThree == "ive" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
		// IZE ->
		// bowdlerize -> bowdler
	else if ( lastThree == "ize" )
		{
		wordStem = subStr( word, 0, word.size( ) - 3 );
		}
	return wordStem;

	}

/**
 * Step 5a
 *
 * @param word
 * @return
 */
std::string Stemmer::step5a ( std::string word )
	{
	auto m = measure( word );
	// E ->
	// probabte -> probat
	if ( m > 1 && word[ word.size( ) - 1 ] == 'e' )
		{
		word = subStr( word, 0, word.size( ) - 1 );
		return word;
		}
	// E ->
	// cease -> cease
	string wordStem = subStr( word, 0, word.size( ) - 1 );
	if ( m == 1 && !endCVC( wordStem ) && word[ word.size( ) - 1 ] == 'e' )
		{
		word = subStr( word, 0, word.size( ) - 1 );
		}
	return word;

	}

/**
 * Step 5b
 *
 * @param word
 * @return
 */
std::string Stemmer::step5b ( std::string word )
	{
	if ( word.size( ) > 2 && measure( word ) > 1 && word[ word.size( ) - 1 ] == 'l' && word[ word.size( ) - 2 ] == 'l' )
		{
		word = subStr( word, 0, word.size( ) - 1 );
		}
	return word;
	}