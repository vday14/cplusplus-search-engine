
#pragma once

#include <string>
#include "stringProcessing.h"

/**
 * Modeled after the Porter Stemmer algorithm
 * http://snowball.tartarus.org/algorithms/porter/stemmer.html
 */
class Stemmer
	{

	Stemmer ( )
		{ }

	std::string stem ( std::string word )
		{
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
	int measure ( std::string word )
		{
		int m = 0;
		int begin = 0;
		unsigned long end = word.size ( ) - 1;

		while ( true )
			{
			if ( begin > end )
				{
				return m;
				}
			if ( isConsonant ( word.begin ( ) + begin, word.begin ( ) ) )
				{
				break;
				}
			begin += 1;
			}
		begin += 1;

		while ( true )
			{
			while ( true )
				{
				if ( begin > end )
					{
					return m;
					}
				if ( isConsonant ( word.begin ( ) + begin, word.begin ( ) ) )
					{
					break;
					}
				begin += 1;
				}
			begin += 1;
			m += 1;
			while ( true )
				{
				if ( begin > end )
					{
					return m;
					}
				if ( isConsonant ( word.begin ( ) + begin, word.begin ( ) ) )
					{
					break;
					}
				begin += 1;
				}
			begin += 1;
			}
		}

	/**
	 * Check if a vowel is present in the stem
	 *
	 * @param wordBeg
	 * @param wordEnd
	 * @param word
	 * @return
	 */
	bool isVowelPresent ( string::iterator wordBeg, string::iterator wordEnd, string word )
		{
		while ( wordBeg != wordEnd )
			{
			if ( !isConsonant ( wordBeg, word.begin ( ) ) )
				{
				return true;
				}
			}
		return false;
		}

	/**
	 * Return true if the wordIt points to a consonant
	 *
	 * @param wordIt
	 * @param wordBegin
	 * @return
	 */
	bool isConsonant ( string::iterator wordIt, string::iterator wordBegin )
		{
		if ( *wordIt == 'a' || *wordIt == 'e' || *wordIt == 'i' || *wordIt == 'u' )
			{
			return false;
			}
		if ( *wordIt == 'y' )
			{
			if ( wordIt == wordBegin )
				{
				return true;
				}
			else
				{
				return ( !isConsonant ( wordIt - 1, wordBegin ) );
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
	bool addE ( string word )
		{
		// AT -> ATE
		// BL -> BLE
		// IZ -> IZE
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;
		auto substrAT = findPrev ( "at", endPtr );
		auto substrBL = findPrev ( "bl", endPtr );
		auto substrIZ = findPrev ( "iz", endPtr );

		if ( *substrAT != '\0' || *substrBL != '\0' || *substrIZ != '\0' )
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
	bool doubleCon ( string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		if ( word.size ( ) > 2 && *endPtr == *( endPtr - 1 ) )
			{
			if ( *endPtr == 'l' || *endPtr == 's' || *endPtr == 'z' )
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
	bool endCVC ( std::string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		if ( word.size ( ) > 2 )
			{
			// the stem ends cvc
			if ( isConsonant ( endPtr, word.begin ( ) ) && !isConsonant ( endPtr - 1, word.begin ( ) ) &&
			     isConsonant ( endPtr - 2, word.begin ( ) ) )
				{
				// the second c is not W, X or Y
				if ( *( endPtr - 1 ) != 'w' && *( endPtr - 1 ) != 'x' && *( endPtr - 1 ) != 'y' )
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
	std::string step_1a ( std::string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		// check S at end
		if ( word.at ( end ) == 's' )
			{
			string wordStem ( word.begin ( ), word.end ( ) );

			auto substrSSES = findPrev ( "sses", endPtr );
			auto substrIES = findPrev ( "ies", endPtr );
			auto substrSS = findPrev ( "ss", endPtr );
			auto substrS = findPrev ( "s", endPtr );
			// sses -> ss
			// caresses -> caress
			if ( *substrSSES != '\0' )
				{
				string wordStem ( word.begin ( ), substrSSES + 1 );
				}
				// ies -> i
				// ponies -> poni
			else if ( *substrIES != '\0' )
				{
				string wordStem ( word.begin ( ), substrIES + 1 );
				}
				// ss -> ss
				// caress -> caress
			else if ( *substrSS != '\0' )
				{
				string wordStem ( word.begin ( ), word.end ( ) );
				}
				// s ->
				// cats -> cat
			else if ( *substrS != '\0' )
				{
				string wordStem ( word.begin ( ), substrS + 1 );
				}
			else
				{
				string wordStem ( word.begin ( ), word.end ( ) );
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
	std::string step_1b ( std::string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		if ( measure ( word ) > 0 )
			{
			string wordStem ( word.begin ( ), word.end ( ) );

			auto substrEED = findPrev ( "eed", endPtr );
			auto substrED = findPrev ( "ed", endPtr );
			auto substrING = findPrev ( "ing", endPtr );

			// check EED at end and m > 0
			// feed -> feed
			// agreed -> agree
			if ( *substrEED != '\0' )
				{
				string wordStem ( word.begin ( ), substrEED + 1 );
				}
				// check ED at end and preceeded by substr with vowel
				// plastered -> plaster
				// bled -> bled
			else if ( *substrED != '\0' && isVowelPresent ( word.begin ( ), substrED, word ) )
				{

				string wordStem ( word.begin ( ), substrED + 1 );
				if ( addE ( wordStem ) )
					{
					wordStem += 'e';
					}
				else if ( doubleCon ( wordStem ) )
					{
					wordStem = wordStem.substr ( 0, wordStem.size ( ) - 1 );
					}
				else if ( measure ( wordStem ) > 1 && endCVC ( wordStem ) )
					{
					wordStem += 'e';
					}
				}
				// check ING at end and proceeded by substr with vowel
				// motoring -> motor
				// sing -> sing
			else if ( *substrING != '\0' && isVowelPresent ( word.begin ( ), substrING, word ) )
				{
				string wordStem ( word.begin ( ), substrING + 1 );
				if ( addE ( wordStem ) )
					{
					wordStem += 'e';
					}
				}

			return wordStem;
			}
		return word;

		}

	/**
	 * Checks for Y -> I
	 * @param word
	 * @return
	 */
	string step1c ( string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		// Y -> I
		// happy -> happi
		// sky -> sky
		if ( *endPtr == 'y' )
			{
			if ( isVowelPresent ( word.begin ( ), endPtr, word ) )
				{
				word = word.substr ( 0, word.size ( ) - 1 );
				word += 'i';
				}
			}
		return word;
		}

	/**
	 * Step 2
	 * @param word
	 * @return
	 */
	string step2 ( std::string word )
		{

		if ( measure ( word ) == 0 )
			{
			return word;
			}

		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;
		string wordStem ( word.begin ( ), word.end ( ) );

		auto substrATIONAL = findPrev ( "ational", endPtr );
		auto substrTIONAL = findPrev ( "tional", endPtr );
		auto substrENCI = findPrev ( "enci", endPtr );
		auto substrANCI = findPrev ( "anci", endPtr );
		auto substrIZER = findPrev ( "izer", endPtr );
		auto substrABLI = findPrev ( "abli", endPtr );
		auto substrALLI = findPrev ( "alli", endPtr );
		auto substrENTLI = findPrev ( "entli", endPtr );
		auto substrELI = findPrev ( "eli", endPtr );
		auto substrOUSLI = findPrev ( "ousli", endPtr );
		auto substrIZATION = findPrev ( "ization", endPtr );
		auto substrATION = findPrev ( "ation", endPtr );
		auto substrATOR = findPrev ( "ator", endPtr );
		auto substrALISM = findPrev ( "alism", endPtr );
		auto substrIVENESS = findPrev ( "iveness", endPtr );
		auto substrFULNESS = findPrev ( "fulness", endPtr );
		auto substrOUSNESS = findPrev ( "ousness", endPtr );
		auto substrALITI = findPrev ( "aliti", endPtr );
		auto substrIVITI = findPrev ( "iviti", endPtr );
		auto substrBILITI = findPrev ( "biliti", endPtr );

		// ATIONAL -> ATE
		// relational -> relate
		if ( *substrATIONAL != '\0' )
			{
			string wordStem ( word.begin ( ), substrATIONAL + 1 );
			wordStem + 'ate';
			}
			// TIONAL -> TION
			// conditional -> condition
			// rational -> rational
		else if ( *substrTIONAL != '\0' )
			{
			string wordStem ( word.begin ( ), substrTIONAL + 1 );
			wordStem += 'tion';
			}
			// ENCI -> ENCE
			// valenci -> valence
		else if ( *substrENCI != '\0' )
			{
			string wordStem ( word.begin ( ), substrENCI + 1 );
			wordStem += 'ence';
			}
			// ANCI -> ANCE
			// hesitanci ->	hesitance
		else if ( *substrANCI != '\0' )
			{
			string wordStem ( word.begin ( ), substrANCI + 1 );
			wordStem += 'ance';
			}
			// IZER -> IZE
			// digitizer -> digitize
		else if ( *substrIZER != '\0' )
			{
			string wordStem ( word.begin ( ), substrIZER + 1 );
			wordStem += 'ize';
			}
			// ABLI -> ABLE
			// conformabli -> comformable
		else if ( *substrABLI != '\0' )
			{
			string wordStem ( word.begin ( ), substrABLI + 1 );
			wordStem += 'able';
			}
			// ALLI -> AL
			// radicalli -> radical
		else if ( *substrALLI != '\0' )
			{
			string wordStem ( word.begin ( ), substrALLI + 1 );
			wordStem += 'al';
			}
			// ENTLI -> ENT
			// differentli -> different
		else if ( *substrENTLI != '\0' )
			{
			string wordStem ( word.begin ( ), substrENTLI + 1 );
			wordStem += 'ent';
			}
			// ELI -> E
			// vileli -> vile
		else if ( *substrELI != '\0' )
			{
			string wordStem ( word.begin ( ), substrELI + 1 );
			wordStem += 'e';
			}
			// OUSLI -> OUS
			// analogousli	->	analogous
		else if ( *substrOUSLI != '\0' )
			{
			string wordStem ( word.begin ( ), substrOUSLI + 1 );
			wordStem += 'ous';
			}
			// IZATION -> IZE
			// vietnamization	->	vietnamize
		else if ( *substrIZATION != '\0' )
			{
			string wordStem ( word.begin ( ), substrIZATION + 1 );
			wordStem += 'ize';
			}
			// ATION -> ATE
			// predication	->	predicate
		else if ( *substrATION != '\0' )
			{
			string wordStem ( word.begin ( ), substrATION + 1 );
			wordStem += 'ate';
			}
			// ATOR -> ATE
			// predication	->	predicate
		else if ( *substrATOR != '\0' )
			{
			string wordStem ( word.begin ( ), substrATOR + 1 );
			wordStem += 'ate';
			}
			// ALISM -> AL
			// feudalism -> feudal
		else if ( *substrALISM != '\0' )
			{
			string wordStem ( word.begin ( ), substrALISM + 1 );
			wordStem += 'al';
			}
			// IVENESS -> IVE
			// decisivenss	->	decisive
		else if ( *substrIVENESS != '\0' )
			{
			string wordStem ( word.begin ( ), substrIVENESS + 1 );
			wordStem += 'ive';
			}
			// FULNESS -> FUL
			// hopefulness	->	hopeful
		else if ( *substrFULNESS != '\0' )
			{
			string wordStem ( word.begin ( ), substrFULNESS + 1 );
			wordStem += 'ful';
			}
			// OUSNESS -> OUS
			// callousness	->	callous
		else if ( *substrOUSNESS != '\0' )
			{
			string wordStem ( word.begin ( ), substrOUSNESS + 1 );
			wordStem += 'ous';
			}
			// ALITI -> AL
			// formalit	->	callous
		else if ( *substrOUSNESS != '\0' )
			{
			string wordStem ( word.begin ( ), substrOUSNESS + 1 );
			wordStem += 'al';
			}
			// IVITI -> IVE
			// sensitiviti	->	sensitive
		else if ( *substrIVITI != '\0' )
			{
			string wordStem ( word.begin ( ), substrIVITI + 1 );
			wordStem += 'ive';
			}
			// BILITI -> BLE
			// sensibiliti	->	sensible
		else if ( *substrBILITI != '\0' )
			{
			string wordStem ( word.begin ( ), substrBILITI + 1 );
			wordStem += 'ble';
			}

		return wordStem;
		}

	/**
	 * Step 3
	 *
	 * @param word
	 * @return
	 */
	std::string step3 ( std:: string word )
		{

		if ( measure ( word ) == 0 )
			{
			return word;
			}

		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;
		string wordStem ( word.begin ( ), word.end ( ) );

		auto substrICATE = findPrev ( "icate", endPtr );
		auto substrATIVE = findPrev ( "ative", endPtr );
		auto substrALIZE = findPrev ( "alize", endPtr );
		auto substrICITI = findPrev ( "iciti", endPtr );
		auto substrICAL	 = findPrev ( "ical", endPtr );
		auto substrFUL		 = findPrev ( "ful", endPtr );
		auto substrNESS	 = findPrev ( "ness", endPtr );

		// ICATE -> IC
		// triplicate -> triplic
		if ( *substrICATE != '\0' )
			{
			string wordStem ( word.begin ( ), substrICATE + 1 );
			wordStem + 'ic';
			}
			// ATIVE ->
			// formative -> form
		else if ( *substrATIVE != '\0' )
			{
			string wordStem ( word.begin ( ), substrATIVE + 1 );
			}
			// ALIZE -> AL
			// formalize -> formal
		else if ( *substrALIZE != '\0' )
			{
			string wordStem ( word.begin ( ), substrALIZE + 1 );
			wordStem += 'al';
			}
			// ICITI -> IC
			// electriciti ->	electric
		else if ( *substrICITI != '\0' )
			{
			string wordStem ( word.begin ( ), substrICITI + 1 );
			wordStem += 'ic';
			}
			// ICAL -> IC
			// electrical -> electric
		else if ( *substrICAL != '\0' )
			{
			string wordStem ( word.begin ( ), substrICAL + 1 );
			wordStem += 'ic';
			}
			// FUL ->
			// hopeful -> hope
		else if ( *substrFUL != '\0' )
			{
			string wordStem ( word.begin ( ), substrFUL + 1 );
			}
			// NESS ->
			// goodness -> good
		else if ( *substrNESS != '\0' )
			{
			string wordStem ( word.begin ( ), substrNESS + 1 );
			}

		return wordStem;
		}

	/**
	 * Step 4
	 *
	 * @param word
	 * @return
	 */
	std::string step4( std::string word )
		{
		if ( measure ( word ) <= 1 )
			{
			return word;
			}

		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;
		string wordStem ( word.begin ( ), word.end ( ) );


		auto substrAL = findPrev ( "al", endPtr );
		auto substrANCE = findPrev ( "ance", endPtr );
		auto substrENCE = findPrev ( "ence", endPtr );
		auto substrER = findPrev ( "er", endPtr );
		auto substrIC = findPrev ( "ic", endPtr );
		auto substrABLE = findPrev ( "able", endPtr );
		auto substrIBLE = findPrev ( "ible", endPtr );
		auto substrANT = findPrev ( "ant", endPtr );
		auto substrEMENT = findPrev ( "ement", endPtr );
		auto substrMENT = findPrev ( "ment", endPtr );
		auto substrENT = findPrev ( "ent", endPtr );
		auto substrTION = findPrev ( "tion", endPtr );
		auto substrOU = findPrev ( "ou", endPtr );
		auto substrISM	= findPrev ( "ism", endPtr );
		auto substrATE = findPrev ( "ate", endPtr );
		auto substrITI = findPrev ( "iti", endPtr );
		auto substrOUS = findPrev ( "ous", endPtr );
		auto substrIVE = findPrev ( "ive", endPtr );
		auto substrIZE = findPrev ( "ize", endPtr );

		// AL ->
		// revival -> reviv
		if ( *substrAL != '\0' )
			{
			string wordStem ( word.begin ( ), substrAL + 1 );
			}
			// ANCE ->
			// allowance -> allow
		else if ( *substrANCE != '\0' )
			{
			string wordStem ( word.begin ( ), substrANCE + 1 );
			}
			// ENCE ->
			// inference -> infer
		else if ( *substrENCE != '\0' )
			{
			string wordStem ( word.begin ( ), substrENCE + 1 );
			}
			// ER ->
			// airliner ->	airlin
		else if ( *substrER != '\0' )
			{
			string wordStem ( word.begin ( ), substrER + 1 );
			}
			// IC ->
			// gyroscopic -> gyroscope
		else if ( *substrIC != '\0' )
			{
			string wordStem ( word.begin ( ), substrIC + 1 );
			}
			// ABLE ->
			// adjustable -> adjust
		else if ( *substrABLE != '\0' )
			{
			string wordStem ( word.begin ( ), substrABLE + 1 );
			}
			// IBLE ->
			// goodness -> good
		else if ( *substrIBLE != '\0' )
			{
			string wordStem ( word.begin ( ), substrIBLE + 1 );
			}
			// ANT ->
			// irritant -> irrit
		else if ( *substrANT != '\0' )
			{
			string wordStem ( word.begin ( ), substrANT + 1 );
			}
			// EMENT ->
			// replacement -> replace
		else if ( *substrEMENT != '\0' )
			{
			string wordStem ( word.begin ( ), substrEMENT + 1 );
			}
			// MENT ->
			// adjustment -> adjust
		else if ( *substrMENT != '\0' )
			{
			string wordStem ( word.begin ( ), substrMENT + 1 );
			}
			// ENT ->
			// dependent -> depend
		else if ( *substrENT != '\0' )
			{
			string wordStem ( word.begin ( ), substrENT + 1 );
			}
			// TION ->
			// stem must end in 't' or 's'
			// adoption -> adopt
		else if ( *substrTION != '\0' && ( *( substrTION - 1) == 's' || *( substrTION - 1) == 't' ) )
			{
			string wordStem ( word.begin ( ), substrTION + 1 );
			}
			// OU ->
			// homologou -> homolog
		else if ( *substrOU != '\0' )
			{
			string wordStem ( word.begin ( ), substrOU + 1 );
			}
			// ISM ->
			// communism -> commun
		else if ( *substrISM != '\0' )
			{
			string wordStem ( word.begin ( ), substrISM + 1 );
			}
			// ATE ->
			// activate -> activ
		else if ( *substrATE != '\0' )
			{
			string wordStem ( word.begin ( ), substrATE + 1 );
			}
			// ITI ->
			// angulariti -> angular
		else if ( *substrITI != '\0' )
			{
			string wordStem ( word.begin ( ), substrITI + 1 );
			}
			// OUS ->
			// homologous -> homolog
		else if ( *substrOUS != '\0' )
			{
			string wordStem ( word.begin ( ), substrOUS + 1 );
			}
			// IVE ->
			// effective -> effect
		else if ( *substrIVE != '\0' )
			{
			string wordStem ( word.begin ( ), substrIVE + 1 );
			}
			// IZE ->
			// bowdlerize -> bowdler
		else if ( *substrIZE != '\0' )
			{
			string wordStem ( word.begin ( ), substrIZE + 1 );
			}
		return wordStem;

		}

	std::string step5a ( std::string word )
		{
		unsigned long end = word.size ( ) - 1;
		auto endPtr = word.begin ( ) + end;

		// E ->
		// probabte -> probat
		if ( measure ( word ) > 1 && *endPtr == 'e' )
			{
			word = word.substr ( 0, word.size ( ) - 1 );
			return word;
			}
		// E ->
		// cease -> cease
		if ( measure ( word ) == 1 && !endCVC ( word ) && *endPtr == 'e')
			{
			word = word.substr ( 0, word.size ( ) - 1 );
			return word;
			}
		return word;
		}

	std::string step5b ( std::string word )
		{
/**
 * Step 5b
(m > 1 and *d and *L)		->		single letter		    		controll		->		control
    		roll		->		roll

 */
		}

	};


