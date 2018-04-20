
#include "../Scorer.h"
#include "../Site.h"
#include "../../indexer/Corpus.h"
#include <iostream>
#include <vector>
#include <cassert>

void testStaticScore( );
void testProximityMatchSimple( );
void testProximityMatchOneWord ( );
void testPhraseMatchSymbols ( );
void testProxMultipleOffsets ( );
void testPhraseMatchMultipleOffsets ( );
void testWordLocationScore( );

void testMatchType( );
void testTFIDF( );


int main( )
	{
	cout << "------Starting Scorer Test------" << endl << endl;

	testStaticScore( );
	testProximityMatchSimple( );
	testProximityMatchOneWord( );
	testPhraseMatchSymbols ( );
	testProxMultipleOffsets( );
	testMatchType ( );
	testWordLocationScore( );
	testTFIDF( );


	cout << "------Passed All Scorer Tests--- :)" << endl;
	}


void testStaticScore( )
	{
	cout << "Testing Static Score....." << endl;
	Query query( "banana cream pie" );
	std::string url = "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie";
	Site newSite( url, query, "TITLE" );

	//.com
	Scorer scorer = Scorer( );
	auto score = scorer.staticScore( newSite );
	cout << "Score: " << score << endl;
	assert( score == 0.6 );

	//.edu & no protocol
	url = "umich.edu/";
	Site newSite2( url, query, "TITLE" );
	score = scorer.staticScore( newSite2 );
	cout << "Score: " << score << endl;
	assert( score == 0.9 );

	//.gov
	url = "https://www.whitehouse.gov/";
	Site newSite3( url, query, "TITLE" );
	score = scorer.staticScore( newSite3 );
	cout << "Score: " << score << endl;
	assert( score == 0.9 );

	//.net
	url = "testwebsite.net";
	Site newSite4( url, query, "TITLE" );
	score = scorer.staticScore( newSite4 );
	cout << "Score: " << score << endl;
	assert( score == 0.4 );

	//.us
	url = "http://testing.us";
	Site newSite5( url, query, "TITLE" );
	score = scorer.staticScore( newSite5 );
	cout << "Score: " << score << endl;
	assert( score == 0.1 );

	//other
	url = "umich.biz/";
	Site newSite6( url, query, "TITLE" );
	score = scorer.staticScore( newSite6 );
	cout << "Score: " << score << endl;
	assert( score == 0.0 );

	cout << "Static Score Passed!" << endl << endl;

	}

void testProximityMatchSimple( )
	{
	cout << "Testing Proximity Match....." << endl;

	Query query( "banana cream pie" );
	std::string url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query, "TITLE" );

	/// Banana Cream Pie
	newSite.wordData[ "banana"].frequency = 1;
	newSite.wordData[ "cream"].frequency = 1;
	newSite.wordData[ "pie"].frequency = 1;

	newSite.wordData[ "banana"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets.push_back( 1 );
	newSite.wordData[ "pie"].offsets.push_back( 2 );

	Scorer scorer = Scorer( );
	auto score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );
	cout << "Score: " << score << endl;
	assert( score == 1 );

	/// Banana Strawberry Cream Pie

	newSite.wordData[ "strawberry"].frequency = 1;

	newSite.wordData[ "strawberry"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets[ 0 ] = 2;
	newSite.wordData[ "pie"].offsets[ 0 ] = 3;

	score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );
	cout << "Score: " << score << endl;
	assert( score == 0.66576959070293562 );

	Query query2( "strawberry milkshake recipe" );
	std::string url2( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite2( url2, query2, "TITLE" );

	/// Cake Pie
	newSite2.wordData[ "cake"].frequency = 3;
	newSite2.wordData[ "pie"].frequency = 2;

	newSite2.wordData[ "cake"].offsets = { 0, 4, 8 };
	newSite2.wordData[ "pie"].offsets = { 2, 6 };

	score = scorer.proximityMatch( newSite2, newSite2.getQuery( ).getQueryTokens( ) );
	cout << "Score: " << score << endl;
	assert( score == 0 );

	cout << "PASSED Proximity Matching Simple :)\n";
	}

void testProximityMatchOneWord ( )
	{

	cout << "Testing Proximity Match One Word....." << endl;

	Query query( "Cream" );
	std::string url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query, "TITLE" );

	/// Banana Cream Pie
	newSite.wordData[ "banana"].frequency = 1;
	newSite.wordData[ "cream"].frequency = 1;
	newSite.wordData[ "cake"].frequency = 1;

	newSite.wordData[ "banana"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets.push_back( 1 );
	newSite.wordData[ "cake"].offsets.push_back( 2 );

	Scorer scorer = Scorer();
	auto score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );

	cout << "Score: " << score << endl;
	assert( score == 0 );

	cout << "Proximity Match One Word Passed!" << endl << endl;

	}

void testPhraseMatchSymbols ( )
	{
	cout << "Testing Proximity Match Symbols....." << endl;
	Query query( "$Cream@ Pie!" );
	std::string url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query, "TITLE" );

	/// Banana Cream Pie Cake
	newSite.wordData[ "banana"].frequency = 1;
	newSite.wordData[ "cream"].frequency = 1;
	newSite.wordData[ "pie"].frequency = 1;
	newSite.wordData[ "cake"].frequency = 1;

	newSite.wordData[ "banana"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets.push_back( 1 );
	newSite.wordData[ "pie"].offsets.push_back( 2 );
	newSite.wordData[ "cake"].offsets.push_back( 3 );

	Scorer scorer = Scorer();
	auto score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );

	cout << "Score: " << score << endl;
	assert( score == 1 );

	cout << "Proximity Match Symbols Passed!" << endl << endl;

	cout << "PASSED Phrase Matching with Symbols :)\n";

	}

void testProxMultipleOffsets ( )
	{
	cout << "Testing Proximity Match Mult Offsets....." << endl;

	Query query( "Banana Cream Pie" );
	std::string url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query, "TITLE" );

	/// Banana Banana Cream Cream Pie Pie
	newSite.wordData[ "banana"].frequency = 2;
	newSite.wordData[ "cream"].frequency = 2;
	newSite.wordData[ "pie"].frequency = 2;

	newSite.wordData[ "banana"].offsets = { 0, 1 };
	newSite.wordData[ "cream"].offsets = { 2, 3 };
	newSite.wordData[ "pie"].offsets = { 4, 5 };

	Scorer scorer = Scorer();
	auto score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );

	cout << "Score: " << score << endl;
	assert( score == 0.49932719302720169 );

	/// Banana Pie Cream Banana Cream Pie Pie Random Random Cream Banana Random Random Cream Random Pie
	///   0     1     2     3     4     5  6    7      8     9     10       11    12    13    14-19  20-26
	newSite.wordData[ "banana"].frequency = 3;
	newSite.wordData[ "cream"].frequency = 4;
	newSite.wordData[ "pie"].frequency = 7;

	newSite.wordData[ "banana"].offsets = { 0, 3, 10 };
	newSite.wordData[ "cream"].offsets = { 2, 4, 9, 13 };
	newSite.wordData[ "pie"].offsets = { 1, 5, 6, 20, 24, 25, 26 };

	score = scorer.proximityMatch( newSite, newSite.getQuery( ).getQueryTokens( ) );

	cout << "Score: " << score << endl;
	assert( score == 0.66711520464853225 );

	cout << "Proximity Match Mult Offsets Passed!" << endl << endl;
	}

void testMatchType( )
	{

	cout << "Testing Word Type...\n";

	string body = "%banana";
	string url = "$banana";
	string title = "#banana";
	string plain = "banana";
	string anchor = "@banana";

	Scorer scorer;

	assert( scorer.matchType( body ) == Scorer::bodyType);
	assert( scorer.matchType( url ) == Scorer::URLType);
	assert( scorer.matchType( title ) == Scorer::titleType);
	assert( scorer.matchType( plain ) == Scorer::bodyType );

	//TODO: change this when we add the anchor text

	assert( scorer.matchType ( anchor ) == Scorer::bodyType );

	cout << "PASSED the type test :)\n";
	}


void testWordLocationScore( )
	{

	cout << "Testing wordLocation score...\n";
	Query query( "Banana Cream Pie" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie/cream-pie-recipes/pie" );
	Site newSite( url.getCompleteUrl(), query, "Banana Cream Pie recipe for the best pie thats banana banana" );

	Scorer scorer;

	/// Banana Banana Cream Cream Pie Pie
	newSite.wordData[ "#banana"].frequency = 1;
	newSite.wordData[ "#cream"].frequency = 2;
	newSite.wordData[ "#pie"].frequency = 3;
	newSite.wordData[ "%banana"].frequency = 3;
	newSite.wordData[ "%cream"].frequency = 1;
	newSite.wordData[ "%pie"].frequency = 2;
	newSite.wordData[ "$banana"].frequency = 1;
	newSite.wordData[ "$cream"].frequency = 2;
	newSite.wordData[ "$pie"].frequency = 3;

	newSite.wordData[ "#banana"].offsets = { 0, 1 };
	newSite.wordData[ "#cream"].offsets = { 2, 3 };
	newSite.wordData[ "#pie"].offsets = { 4, 5 };
	newSite.wordData[ "%banana"].offsets = { 0, 1 };
	newSite.wordData[ "%cream"].offsets = { 2, 3 };
	newSite.wordData[ "%pie"].offsets = { 4, 5 };
	newSite.wordData[ "$banana"].offsets = { 0, 1 };
	newSite.wordData[ "$cream"].offsets = { 2, 3 };
	newSite.wordData[ "$pie"].offsets = { 4, 5 };

	double manualScore = 0.737179;
	assert(scorer.wordLocationScore ( newSite ) <= manualScore + 0.001 && scorer.wordLocationScore ( newSite ) >= manualScore - 0.001);

	cout << "PASSED Location Score :)\n\n";

	}


void testTFIDF( )
	{
	cout << "Testing TFIDF score...\n";

	/*Query query( "Banana Cream Pie" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie/cream-pie-recipes/pie" );
	Site newSite( url.getCompleteUrl(), query, "Banana Cream Pie recipe for the best pie thats banana banana" );
	newSite.numTermsInDoc = 100;
	newSite.docCount = 8000;

	Scorer scorer;

	newSite.wordData[ "#banana"].frequency = 7;
	newSite.wordData[ "#cream"].frequency = 3;
	newSite.wordData[ "#pie"].frequency = 5;

	newSite.wordData[ "#banana"].offsets = { 0, 1 };
	newSite.wordData[ "#cream"].offsets = { 2, 3 };
	newSite.wordData[ "#pie"].offsets = { 4, 5 };

	newSite.wordData[ "#banana"].docFrequency = 5;
	newSite.wordData[ "#cream"].docFrequency = 20;
	newSite.wordData[ "#pie"].docFrequency = 30;

	auto score = scorer.tfIdfScore ( newSite, query.getQueryTitle ( ) );
	cout << "Score: " << score << endl;
	// TODO
	assert( score != 0 );


	Query query1( "trump is president FBI" );
	ParsedUrl url1( "https://www.politico.com/story/2018/04/16/james-comey-interview-trump-white-house-response-526281" );
	Site newSite1( url1.getCompleteUrl(), query1, "Trump office president FBI white house trump fbi white white trump house" );
	cout << "here" << endl;

	Scorer scorer1;
	newSite1.wordData[ "#trump"].frequency = 3;
	newSite1.wordData[ "#offic"].frequency = 1;
	newSite1.wordData[ "#presid"].frequency = 4;
	newSite1.wordData[ "#white" ].frequency = 3;
	newSite1.wordData[ "#hous" ].frequency = 2;
	newSite1.wordData[ "#fbi" ].frequency = 2;
	newSite1.wordData[ "%trump" ].frequency = 3;
	newSite1.wordData[ "%comei" ].frequency = 1;
	newSite1.wordData[ "%white" ].frequency = 2;
	newSite1.wordData[ "%hous" ].frequency = 1;
	newSite1.wordData[ "%hous" ].frequency = 1;
	newSite1.wordData[ "%corrupt" ].frequency = 5;
	newSite1.wordData[ "$jame"].frequency = 1;
	newSite1.wordData[ "$comei"].frequency = 2;
	newSite1.wordData[ "$trump"].frequency = 1;

	double score1 = scorer1.tfIdfScore( newSite1, query1.getQueryTitle( ) );

	cout << score1 << endl;
	assert( score1 > 0 && score1 < 1 );

	cout << "PASSED TFIDF Score :)\n\n";*/


	}