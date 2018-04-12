
#include "../Scorer.h"
#include "../Site.h"
#include <iostream>
#include <vector>
#include <cassert>

void testPhraseMatchSimple( );

int main( )
	{
	cout << "------Starting Scorer Test------" << endl;
	testPhraseMatchSimple ( );
	cout << "------Passed All Scorer Tests---" << endl;
	}

void testPhraseMatchSimple( )
	{

	Query query( "banana cream pie" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query );

	/// Banana Cream Pie
	newSite.wordData[ "banana"].frequency = 1;
	newSite.wordData[ "cream"].frequency = 1;
	newSite.wordData[ "pie"].frequency = 1;

	newSite.wordData[ "banana"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets.push_back( 1 );
	newSite.wordData[ "pie"].offsets.push_back( 2 );

	Scorer scorer = Scorer();
	auto score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 3 );

	/// Banana Strawberry Cream Pie

	newSite.wordData[ "strawberry"].frequency = 1;

	newSite.wordData[ "strawberry"].offsets.push_back( 0 );
	newSite.wordData[ "cream"].offsets[ 0 ] = 2;
	newSite.wordData[ "pie"].offsets[ 0 ] = 3;

	score = scorer.phraseMatch( newSite );
	cout << "Score: " << score << endl;
	assert( score == 2 );

	/// Banana Strawberry Cream Cake Pie
	newSite.wordData[ "cake"].frequency = 1;

	newSite.wordData[ "cake"].offsets.push_back( 3 );
	newSite.wordData[ "pie"].offsets[ 0 ] = 4;

	score = scorer.phraseMatch( newSite );
	cout << "Score: " << score << endl;
	assert( score == 0 );

	}