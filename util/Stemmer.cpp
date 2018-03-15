
#include "Stemmer.h"
#include "stringProcessing.h"

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
	int m = 0;
	int begin = 0;
	unsigned long end = word.size( ) - 1;
	// Looking for CVC pattern
	while ( begin <= end )
		{
		if ( !isConsonant( word.begin( ) + begin, word.begin( ) ) )
			{
			break;
			}
		begin += 1;
		}
	if ( begin > end )
		{
		return m;
		}
	begin += 1;

	while ( begin <= end )
		{
		while ( begin <= end )
			{
			if ( isConsonant( word.begin( ) + begin, word.begin( ) ) )
				{
				break;
				}
			begin += 1;
			}
		if ( begin > end )
			{
			return m;
			}
		begin += 1;
		m += 1;
		while ( begin <= end )
			{
			if ( !isConsonant( word.begin( ) + begin, word.begin( ) ) )
				{
				break;
				}
			begin += 1;
			}
		if ( begin > end )
			{
			return m;
			}
		begin += 1;
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
bool Stemmer::isVowelPresent ( string::iterator wordBeg, string::iterator wordEnd, string word )
	{
	while ( wordBeg != wordEnd )
		{
		if ( !isConsonant( wordBeg, word.begin( ) ) )
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
 * @param wordIt
 * @param wordBegin
 * @return
 */
bool Stemmer::isConsonant ( string::iterator wordIt, string::iterator wordBegin )
	{
	if ( *wordIt == 'a' || *wordIt == 'e' || *wordIt == 'i' || *wordIt == 'o' || *wordIt == 'u' )
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
			return ( !isConsonant( wordIt - 1, wordBegin ) );
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
	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;
	auto substrAT = findPrev( "at", endPtr, begPtr + word.size( ) - 3 );
	auto substrBL = findPrev( "bl", endPtr, begPtr + word.size( ) - 3 );
	auto substrIZ = findPrev( "iz", endPtr, begPtr + word.size( ) - 3 );

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
bool Stemmer::doubleCon ( string word )
	{
	unsigned long end = word.size( ) - 1;
	auto endPtr = word.begin( ) + end;

	if ( word.size( ) > 2 && *endPtr == *( endPtr - 1 ) )
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
bool Stemmer::endCVC ( std::string word )
	{
	unsigned long end = word.size( ) - 1;
	auto endPtr = word.begin( ) + end - 1;

	if ( word.size( ) > 3 )
		{
		// the stem ends cvc
		if ( isConsonant( endPtr, word.begin( ) ) && !isConsonant( endPtr - 1, word.begin( ) ) &&
		     isConsonant( endPtr - 2, word.begin( ) ) )
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
std::string Stemmer::step1a ( std::string word )
	{
	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;

	// check S at end
	if ( word.at( end ) == 's' )
		{
		string wordStem( word.begin( ), word.end( ) );

		auto substrSSES = findPrev( "sses", endPtr, begPtr + word.size( ) - 5 );
		auto substrIES = findPrev( "ies", endPtr, begPtr + word.size( ) - 4 );
		auto substrSS = findPrev( "ss", endPtr, begPtr + word.size( ) - 3 );
		auto substrS = findPrev( "s", endPtr, begPtr + word.size( ) - 2 );
		// sses -> ss
		// caresses -> caress
		if ( *substrSSES != '\0' )
			{
			wordStem = subStr( word.begin( ), substrSSES );
			wordStem += "ss";
			}
			// ies -> i
			// ponies -> poni
		else if ( *substrIES != '\0' )
			{
			wordStem = subStr( word.begin( ), substrIES );
			wordStem += 'i';
			}
			// ss -> ss
			// caress -> caress
		else if ( *substrSS != '\0' )
			{
			// do nothing
			}
			// s ->
			// cats -> cat
		else if ( *substrS != '\0' )
			{
			wordStem = subStr( word.begin( ), substrS );
			}
		else
			{
			wordStem = subStr( word.begin( ), word.end( ) );
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

	auto substrEED = findPrev( "eed", endPtr, begPtr + word.size( ) - 4 );
	auto substrED = findPrev( "ed", endPtr, begPtr + word.size( ) - 3 );
	auto substrING = findPrev( "ing", endPtr, begPtr + word.size( ) - 4 );

	// check EED at end and m > 0
	// feed -> feed
	// agreed -> agree
	if ( measure( word ) > 1 && *substrEED != '\0' )
		{
		wordStem = subStr( word.begin( ), substrEED );
		wordStem += "ee";
		}
		// check ED at end and preceeded by substr with vowel
		// plastered -> plaster
		// bled -> bled
	else if ( measure( word ) > 1 && *substrED != '\0' && isVowelPresent( word.begin( ), substrED, word ) )
		{
		wordStem = subStr( word.begin( ), substrED );
		if ( addE( wordStem ) )
			{
			wordStem += 'e';
			}
		else if ( doubleCon( wordStem ) )
			{
			wordStem = subStr( word, 0, wordStem.size( ) - 1 );
			}
		else if ( measure( word ) == 1 && endCVC( wordStem + 'e' ) )
			{
			wordStem += 'e';
			}
		}
		// check ING at end and proceeded by substr with vowel
		// motoring -> motor
		// sing -> sing
	else if ( *substrING != '\0' && isVowelPresent( word.begin( ), substrING, word ) )
		{
		wordStem = subStr( word.begin( ), substrING );
		if ( addE( wordStem ) )
			{
			wordStem += 'e';
			}
		else if ( doubleCon( wordStem ) )
			{
			wordStem = subStr( word, 0, wordStem.size( ) - 1 );
			}
		else if ( measure( wordStem ) == 1 && endCVC( wordStem + 'e' ) )
			{
			wordStem += 'e';
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
	unsigned long end = word.size( ) - 1;
	auto endPtr = word.begin( ) + end;

	// Y -> I
	// happy -> happi
	// sky -> sky
	if ( *endPtr == 'y' )
		{
		if ( isVowelPresent( word.begin( ), endPtr, word ) )
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

	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;
	string wordStem( word.begin( ), word.end( ) );

	auto substrATIONAL = findPrev( "ational", endPtr, begPtr + word.size( ) - 8 );
	auto substrTIONAL = findPrev( "tional", endPtr, begPtr + word.size( ) - 7 );
	auto substrENCI = findPrev( "enci", endPtr, begPtr + word.size( ) - 5 );
	auto substrANCI = findPrev( "anci", endPtr, begPtr + word.size( ) - 5 );
	auto substrIZER = findPrev( "izer", endPtr, begPtr + word.size( ) - 5 );
	auto substrABLI = findPrev( "abli", endPtr, begPtr + word.size( ) - 5 );
	auto substrALLI = findPrev( "alli", endPtr, begPtr + word.size( ) - 5 );
	auto substrENTLI = findPrev( "entli", endPtr, begPtr + word.size( ) - 6 );
	auto substrELI = findPrev( "eli", endPtr, begPtr + word.size( ) - 4 );
	auto substrOUSLI = findPrev( "ousli", endPtr, begPtr + word.size( ) - 6 );
	auto substrIZATION = findPrev( "ization", endPtr, begPtr + word.size( ) - 8 );
	auto substrATION = findPrev( "ation", endPtr, begPtr + word.size( ) - 6 );
	auto substrATOR = findPrev( "ator", endPtr, begPtr + word.size( ) - 5 );
	auto substrALISM = findPrev( "alism", endPtr, begPtr + word.size( ) - 6 );
	auto substrIVENESS = findPrev( "iveness", endPtr, begPtr + word.size( ) - 8 );
	auto substrFULNESS = findPrev( "fulness", endPtr, begPtr + word.size( ) - 8 );
	auto substrOUSNESS = findPrev( "ousness", endPtr, begPtr + word.size( ) - 8 );
	auto substrALITI = findPrev( "aliti", endPtr, begPtr + word.size( ) - 6 );
	auto substrIVITI = findPrev( "iviti", endPtr, begPtr + word.size( ) - 6 );
	auto substrBILITI = findPrev( "biliti", endPtr, begPtr + word.size( ) - 7 );

	// ATIONAL -> ATE
	// relational -> relate
	if ( *substrATIONAL != '\0' && ( begPtr + 1 ) != substrATIONAL )
		{
		wordStem = subStr( word.begin( ), substrATIONAL );
		wordStem += "ate";
		}
		// TIONAL -> TION
		// conditional -> condition
		// rational -> rational
	else if ( *substrTIONAL != '\0' )
		{
		wordStem = subStr( word.begin( ), substrTIONAL );
		wordStem += "tion";
		}
		// ENCI -> ENCE
		// valenci -> valence
	else if ( *substrENCI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrENCI );
		wordStem += "ence";
		}
		// ANCI -> ANCE
		// hesitanci ->	hesitance
	else if ( *substrANCI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrANCI );
		wordStem += "ance";
		}
		// IZER -> IZE
		// digitizer -> digitize
	else if ( *substrIZER != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIZER );
		wordStem += "ize";
		}
		// ABLI -> ABLE
		// conformabli -> comformable
	else if ( *substrABLI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrABLI );
		wordStem += "able";
		}
		// ALLI -> AL
		// radicalli -> radical
	else if ( *substrALLI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrALLI );
		wordStem += "al";
		}
		// ENTLI -> ENT
		// differentli -> different
	else if ( *substrENTLI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrENTLI );
		wordStem += "ent";
		}
		// ELI -> E
		// vileli -> vile
	else if ( *substrELI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrELI );
		wordStem += 'e';
		}
		// OUSLI -> OUS
		// analogousli	->	analogous
	else if ( *substrOUSLI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrOUSLI );
		wordStem += "ous";
		}
		// IZATION -> IZE
		// vietnamization	->	vietnamize
	else if ( *substrIZATION != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIZATION );
		wordStem += "ize";
		}
		// ATION -> ATE
		// predication	->	predicate
	else if ( *substrATION != '\0' )
		{
		wordStem = subStr( word.begin( ), substrATION );
		wordStem += "ate";
		}
		// ATOR -> ATE
		// predication	->	predicate
	else if ( *substrATOR != '\0' )
		{
		wordStem = subStr( word.begin( ), substrATOR );
		wordStem += "ate";
		}
		// ALISM -> AL
		// feudalism -> feudal
	else if ( *substrALISM != '\0' )
		{
		wordStem = subStr( word.begin( ), substrALISM );
		wordStem += "al";
		}
		// IVENESS -> IVE
		// decisivenss	->	decisive
	else if ( *substrIVENESS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIVENESS );
		wordStem += "ive";
		}
		// FULNESS -> FUL
		// hopefulness	->	hopeful
	else if ( *substrFULNESS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrFULNESS );
		wordStem += "ful";
		}
		// OUSNESS -> OUS
		// callousness	->	callous
	else if ( *substrOUSNESS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrOUSNESS );
		wordStem += "ous";
		}
		// ALITI -> AL
		// formalit	->	callous
	else if ( *substrOUSNESS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrOUSNESS );
		wordStem += "al";
		}
		// IVITI -> IVE
		// sensitiviti	->	sensitive
	else if ( *substrIVITI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIVITI );
		wordStem += "ive";
		}
		// BILITI -> BLE
		// sensibiliti	->	sensible
	else if ( *substrBILITI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrBILITI );
		wordStem += "ble";
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

	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;
	string wordStem( word.begin( ), word.end( ) );

	auto substrICATE = findPrev( "icate", endPtr, begPtr + word.size( ) - 6 );
	auto substrATIVE = findPrev( "ative", endPtr, begPtr + word.size( ) - 6 );
	auto substrALIZE = findPrev( "alize", endPtr, begPtr + word.size( ) - 6 );
	auto substrICITI = findPrev( "iciti", endPtr, begPtr + word.size( ) - 6 );
	auto substrICAL = findPrev( "ical", endPtr, begPtr + word.size( ) - 4 );
	auto substrFUL = findPrev( "ful", endPtr, begPtr + word.size( ) - 4 );
	auto substrNESS = findPrev( "ness", endPtr, begPtr + word.size( ) - 5 );

	// ICATE -> IC
	// triplicate -> triplic
	if ( *substrICATE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrICATE );
		wordStem += "ic";
		}
		// ATIVE ->
		// formative -> form
	else if ( *substrATIVE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrATIVE );
		}
		// ALIZE -> AL
		// formalize -> formal
	else if ( *substrALIZE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrALIZE );
		wordStem += "al";
		}
		// ICITI -> IC
		// electriciti ->	electric
	else if ( *substrICITI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrICITI );
		wordStem += "ic";
		}
		// ICAL -> IC
		// electrical -> electric
	else if ( *substrICAL != '\0' )
		{
		wordStem = subStr( word.begin( ), substrICAL );
		wordStem += "ic";
		}
		// FUL ->
		// hopeful -> hope
	else if ( *substrFUL != '\0' )
		{
		wordStem = subStr( word.begin( ), substrFUL );
		}
		// NESS ->
		// goodness -> good
	else if ( *substrNESS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrNESS );
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

	unsigned long end = word.size( ) - 1;
	auto begPtr = word.begin( );
	auto endPtr = begPtr + end;
	string wordStem( word.begin( ), word.end( ) );


	auto substrAL = findPrev( "al", endPtr, begPtr + word.size( ) - 3 );
	auto substrANCE = findPrev( "ance", endPtr, begPtr + word.size( ) - 5 );
	auto substrENCE = findPrev( "ence", endPtr, begPtr + word.size( ) - 5 );
	auto substrER = findPrev( "er", endPtr, begPtr + word.size( ) - 3 );
	auto substrIC = findPrev( "ic", endPtr, begPtr + word.size( ) - 3 );
	auto substrABLE = findPrev( "able", endPtr, begPtr + word.size( ) - 5 );
	auto substrIBLE = findPrev( "ible", endPtr, begPtr + word.size( ) - 5 );
	auto substrANT = findPrev( "ant", endPtr, begPtr + word.size( ) - 4 );
	auto substrEMENT = findPrev( "ement", endPtr, begPtr + word.size( ) - 6 );
	auto substrMENT = findPrev( "ment", endPtr, begPtr + word.size( ) - 5 );
	auto substrENT = findPrev( "ent", endPtr, begPtr + word.size( ) - 4 );
	auto substrION = findPrev( "ion", endPtr, begPtr + word.size( ) - 4 );
	auto substrOU = findPrev( "ou", endPtr, begPtr + word.size( ) - 3 );
	auto substrISM = findPrev( "ism", endPtr, begPtr + word.size( ) - 4 );
	auto substrATE = findPrev( "ate", endPtr, begPtr + word.size( ) - 4 );
	auto substrITI = findPrev( "iti", endPtr, begPtr + word.size( ) - 4 );
	auto substrOUS = findPrev( "ous", endPtr, begPtr + word.size( ) - 4 );
	auto substrIVE = findPrev( "ive", endPtr, begPtr + word.size( ) - 4 );
	auto substrIZE = findPrev( "ize", endPtr, begPtr + word.size( ) - 4 );

	// AL ->
	// revival -> reviv
	if ( *substrAL != '\0' )
		{
		wordStem = subStr( word.begin( ), substrAL );
		}
		// ANCE ->
		// allowance -> allow
	else if ( *substrANCE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrANCE );
		}
		// ENCE ->
		// inference -> infer
	else if ( *substrENCE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrENCE );
		}
		// ER ->
		// airliner ->	airlin
	else if ( *substrER != '\0' )
		{
		wordStem = subStr( word.begin( ), substrER );
		}
		// IC ->
		// gyroscopic -> gyroscope
	else if ( *substrIC != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIC );
		}
		// ABLE ->
		// adjustable -> adjust
	else if ( *substrABLE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrABLE );
		}
		// IBLE ->
		// goodness -> good
	else if ( *substrIBLE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIBLE );
		}
		// ANT ->
		// irritant -> irrit
	else if ( *substrANT != '\0' )
		{
		wordStem = subStr( word.begin( ), substrANT );
		}
		// EMENT ->
		// replacement -> replace
	else if ( *substrEMENT != '\0' )
		{
		wordStem = subStr( word.begin( ), substrEMENT );
		}
		// MENT ->
		// adjustment -> adjust
	else if ( *substrMENT != '\0' )
		{
		wordStem = subStr( word.begin( ), substrMENT );
		}
		// ENT ->
		// dependent -> depend
	else if ( *substrENT != '\0' )
		{
		wordStem = subStr( word.begin( ), substrENT );
		}
		// TION ->
		// stem must end in 't' or 's'
		// adoption -> adopt
	else if ( *substrION != '\0' && ( *( substrION - 1 ) == 's' || *( substrION - 1 ) == 't' ) )
		{
		wordStem = subStr( word.begin( ), substrION );
		}
		// OU ->
		// homologou -> homolog
	else if ( *substrOU != '\0' )
		{
		wordStem = subStr( word.begin( ), substrOU );
		}
		// ISM ->
		// communism -> commun
	else if ( *substrISM != '\0' )
		{
		wordStem = subStr( word.begin( ), substrISM );
		}
		// ATE ->
		// activate -> activ
	else if ( *substrATE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrATE );
		}
		// ITI ->
		// angulariti -> angular
	else if ( *substrITI != '\0' )
		{
		wordStem = subStr( word.begin( ), substrITI );
		}
		// OUS ->
		// homologous -> homolog
	else if ( *substrOUS != '\0' )
		{
		wordStem = subStr( word.begin( ), substrOUS );
		}
		// IVE ->
		// effective -> effect
	else if ( *substrIVE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIVE );
		}
		// IZE ->
		// bowdlerize -> bowdler
	else if ( *substrIZE != '\0' )
		{
		wordStem = subStr( word.begin( ), substrIZE );
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
	unsigned long end = word.size( ) - 1;
	auto endPtr = word.begin( ) + end;

	// E ->
	// probabte -> probat
	if ( measure( word ) > 1 && *endPtr == 'e' )
		{
		word = subStr( word, 0, word.size( ) - 1 );
		return word;
		}
	// E ->
	// cease -> cease
	if ( measure( word ) == 1 && !endCVC( word ) && *endPtr == 'e' )
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
	unsigned long end = word.size( ) - 1;
	auto endPtr = word.begin( ) + end;

	if ( word.size( ) > 2 && measure( word ) > 1 && *endPtr == 'l' && *( endPtr - 1 ) == 'l' )
		{
		word = subStr( word, 0, word.size( ) - 1 );
		}
	return word;
	}