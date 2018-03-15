
#include <string>
#include <vector>
#include "../Stemmer.h"
#include <iostream>
#include <cassert>

int main ( )
	{

	cout << "Beginning testing for Stemmer" << endl;

	Stemmer stem;

	assert ( stem.execute( "caresses" ) == "caress" );
	assert ( stem.execute( "ponies" ) == "poni" );
	assert ( stem.execute( "ties" ) == "ti" );
	assert ( stem.execute( "caress" ) == "caress" );
	assert ( stem.execute( "cats" ) == "cat" );
	assert ( stem.execute( "feed" ) == "feed" );

	assert ( stem.execute( "agreed" ) == "agre" );
	assert ( stem.execute( "plastered" ) == "plaster" );
	assert ( stem.execute( "bled" ) == "bled" );
	assert ( stem.execute( "motoring" ) == "motor" );
	assert ( stem.execute( "conflated" ) == "conflat" );

	assert ( stem.execute( "troubled" ) == "troubl" );
	assert ( stem.execute( "sized" ) == "size" );
	assert ( stem.execute( "hopping" ) == "hop" );
	assert ( stem.execute( "tanning" ) == "tan" );
	assert ( stem.execute( "tanned" ) == "tan" );

	assert ( stem.execute( "falling" ) == "fall" );
	assert ( stem.execute( "hissing" ) == "hiss" );
	assert ( stem.execute( "fizzed" ) == "fizz" );
	assert ( stem.execute( "failing" ) == "fail" );
	assert ( stem.execute( "filing" ) == "file" );

	assert ( stem.execute( "happy" ) == "happi" );
	assert ( stem.execute( "sky" ) == "sky" );
	assert ( stem.execute( "relational" ) == "relat" );
	assert ( stem.execute( "conditional" ) == "condit" );
	assert ( stem.execute( "rational" ) == "ration" );

	assert ( stem.execute( "valenci" ) == "valenc" );
	assert ( stem.execute( "hesitanci" ) == "hesit" );
	assert ( stem.execute( "digitizer" ) == "digit" );
	assert ( stem.execute( "conformabli" ) == "conform" );
	assert ( stem.execute( "radicalli" ) == "radic" );
	assert ( stem.execute( "differentli" ) == "differ" );

	assert ( stem.execute( "vileli" ) == "vile" );
	assert ( stem.execute( "analogousli" ) == "analog" );
	assert ( stem.execute( "vietnamization" ) == "vietnam" );
	assert ( stem.execute( "predication" ) == "predic" );
	assert ( stem.execute( "operator" ) == "oper" );
	assert ( stem.execute( "feudalism" ) == "feudal" );

	assert ( stem.execute( "decisiveness" ) == "decis" );
	assert ( stem.execute( "hopefulness" ) == "hope" );
	assert ( stem.execute( "callousness" ) == "callous" );
	assert ( stem.execute( "formaliti" ) == "formal" );
	assert ( stem.execute( "sensitiviti" ) == "sensit" );
	assert ( stem.execute( "sensibiliti" ) == "sensibl" );

	assert ( stem.execute( "triplicate" ) == "triplic" );
	assert ( stem.execute( "formative" ) == "form" );
	assert ( stem.execute( "formalize" ) == "formal" );
	assert ( stem.execute( "electriciti" ) == "electr" );
	assert ( stem.execute( "electrical" ) == "electr" );
	assert ( stem.execute( "hopeful" ) == "hope" );

	assert ( stem.execute( "goodness" ) == "good" );
	assert ( stem.execute( "revival" ) == "reviv" );
	assert ( stem.execute( "allowance" ) == "allow" );
	assert ( stem.execute( "inference" ) == "infer" );

	assert ( stem.execute( "airliner" ) == "airlin" );
	assert ( stem.execute( "gyroscopic" ) == "gyroscop" );
	assert ( stem.execute( "adjustable" ) == "adjust" );
	assert ( stem.execute( "defensible" ) == "defens" );
	assert ( stem.execute( "irritant" ) == "irrit" );
	assert ( stem.execute( "replacement" ) == "replac" );
	assert ( stem.execute( "adjustment" ) == "adjust" );
	assert ( stem.execute( "dependent" ) == "depend" );

	assert ( stem.execute( "adoption" ) == "adopt" );
	assert ( stem.execute( "homologou" ) == "homolog" );
	assert ( stem.execute( "communism" ) == "commun" );
	assert ( stem.execute( "activate" ) == "activ" );
	assert ( stem.execute( "angulariti" ) == "angular" );
	assert ( stem.execute( "homologous" ) == "homolog" );
	assert ( stem.execute( "effective" ) == "effect" );

	assert ( stem.execute( "bowdlerize" ) == "bowdler" );
	assert ( stem.execute( "probate" ) == "probat" );
	assert ( stem.execute( "cease" ) == "ceas" );
	assert ( stem.execute( "controll" ) == "control" );
	assert ( stem.execute( "roll" ) == "roll" );
	assert ( stem.execute( "university" ) == "univers" );
	assert ( stem.execute( "example" ) == "exampl" );

	assert ( stem.execute( "do" ) == "do" );
	assert ( stem.execute( "you" ) == "you" );
	assert ( stem.execute( "really" ) == "real" );
	assert ( stem.execute( "weakness" ) == "weak" );
	assert ( stem.execute( "yields" ) == "yield" );
	assert ( stem.execute( "temptation" ) == "temptat" );
	assert ( stem.execute( "are" ) == "ar" );
	assert ( stem.execute( "terrible" ) == "terribl" );


	cout << "\nTests passed for Stemmer :D" << endl;

	}

