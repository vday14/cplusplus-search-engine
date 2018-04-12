
#include "../Scorer.h"
#include "../Site.h"
#include <iostream>
#include <vector>
#include <cassert>

void testPhraseMatchSimple( );
void testPhraseMatchToLower ( );
void testPhraseMatchOneWord ( );
void testPhraseMatchSymbols ( );
void testPhraseMatchMultipleOffsets ( );


int main( )
	{
	cout << "------Starting Scorer Test------" << endl;
	testPhraseMatchSimple( );
	testPhraseMatchToLower ( );
	testPhraseMatchOneWord ( );
	testPhraseMatchSymbols ( );
	testPhraseMatchMultipleOffsets ( );
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


void testPhraseMatchToLower ( )
	{

	Query query( "Cream Pie" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query );

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
	auto score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 2 );


	}


void testPhraseMatchOneWord ( )
	{

	Query query( "Cream" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query );

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
	auto score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 0 );


	}

void testPhraseMatchSymbols ( )
	{

	Query query( "$Cream@ Pie!" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query );

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
	auto score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 2 );

	}

void testPhraseMatchMultipleOffsets ( )
	{

	Query query( "Banana Cream Pie" );
	ParsedUrl url( "https://www.tasteofhome.com/recipes/favorite-banana-cream-pie" );
	Site newSite( url, query );

	/// Banana Banana Cream Cream Pie Pie
	newSite.wordData[ "banana"].frequency = 2;
	newSite.wordData[ "cream"].frequency = 2;
	newSite.wordData[ "pie"].frequency = 2;

	newSite.wordData[ "banana"].offsets = { 0, 1 };
	newSite.wordData[ "cream"].offsets = { 2, 3 };
	newSite.wordData[ "pie"].offsets = { 4, 5 };

	Scorer scorer = Scorer();
	auto score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 0 );

	/// Banana Cream Pie Banana Cream Pie
	newSite.wordData[ "banana"].frequency = 2;
	newSite.wordData[ "cream"].frequency = 2;
	newSite.wordData[ "pie"].frequency = 2;

	newSite.wordData[ "banana"].offsets = { 0, 3 };
	newSite.wordData[ "cream"].offsets = { 1, 4 };
	newSite.wordData[ "pie"].offsets = { 2, 5 };

	score = scorer.phraseMatch( newSite );

	cout << "Score: " << score << endl;
	assert( score == 6 );


	}

