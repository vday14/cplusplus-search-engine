
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"
#include "../../crawler/Readers/LocalReader.h"
#include "../../crawler/Readers/HttpReader.h"
#include "../../crawler/Readers/HttpsReader.h"
#include "../../util/util.h"
#include "../../crawler/UrlFrontier.h"
using namespace std;

void testSimple( );
void testHttp( );
void testURL( );
void testBody ( );
void testExtractBody ( );
void testAnchorText ( );
void testHttps ( );
void testParseParagraph( );
void testTitleParsing( );

void printDictionary ( unordered_map< string, vector< unsigned long > > dictionary );


int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
	testSimple( );
	//FIXME is not getting proper links; RestrictedHost too restrictive
//	testHttp( );
	testURL( );
	testBody ( );
	testExtractBody ( );
	testAnchorText ( );
	//FIXME assert(ctx) is failing
//	testHttps( );
	testParseParagraph();
	testTitleParsing( );


	cout << "Parser Tests Passed! :D" << endl;
	}

void printDictionary ( const unordered_map< string, vector< unsigned long > > dictionary )
	{
	for ( auto it = dictionary.begin( ); it != dictionary.end( ); it++ )
		{
		cout << it->first << ':';
		for ( int i = 0; i < it->second.size( ); ++i )
			{
			cout << it->second[ i ] << " ";
			}
		cout << std::endl;
		}
	}


void testSimple ( )
	{
	cout << "Testing Simple: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl * fake_url = new ParsedUrl( "http://www.cats.com" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/plaintext.txt";

	LocalReader reader( filepath );
	reader.setUrl( fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 14 );
	assert ( dictionary->at( "%goodby" ).size( ) == 1 && dictionary->at( "%goodby" )[ 0 ] == 12 );
	assert ( dictionary->at( "%battl" ).size( ) && dictionary->at( "%battl" )[ 0 ] == 7 );
	assert ( dictionary->at( "%bottl" ).size( ) == 2 && dictionary->at( "%bottl" )[ 0 ] == 9 && dictionary->at( "%bottl" )[ 1 ] == 10 );
	assert ( dictionary->at( "%hello" ).size( ) == 2 && dictionary->at( "%hello" )[ 0 ] == 11 && dictionary->at( "%hello" )[ 1 ] == 13 );
	assert ( dictionary->at( "#aardvark" ).size( ) == 1 && dictionary->at( "#aardvark" )[ 0 ] == 3 );
	assert ( dictionary->at( "%bridg" ).size( ) == 1 && dictionary->at( "%bridg" )[ 0 ] == 8 );
	assert ( dictionary->at( "%bas" ).size( ) == 1 && dictionary->at( "%bas" )[ 0 ] == 6 );
	assert ( dictionary->at( "#anteat" ).size( ) == 1 && dictionary->at( "#anteat" )[ 0 ] == 4 );
	assert ( dictionary->at( "$cat" ).size( ) == 1 && dictionary->at( "$cat" )[ 0 ] == 0 );
	assert ( dictionary->at( "$com" ).size( ) == 1 && dictionary->at( "$com" )[ 0 ] == 1 );
	assert ( dictionary->at( "=www.cats.com/" ).size( ) == 1 && dictionary->at( "=www.cats.com/" )[ 0 ] == 0 );
	assert ( dictionary->at( "#appl" ).size( ) == 1 && dictionary->at( "#appl" )[ 0 ] == 2 );
	assert ( dictionary->at( "#allig" ).size( ) == 1 && dictionary->at( "#allig" )[ 0 ] == 5 );

	delete dictionary;
	dictionary = nullptr;
	cout << "Simple Test Passed!" << endl << endl;
	}

void testHttp( )
	{
	cout << "Testing Complex: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl httpURL = ParsedUrl( "http://veronicacday.com/" );

	HttpReader reader( &httpURL );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

//	assert( urlFrontierTest.Size( ) == 12 );
//	assert( urlFrontierTest.Pop( ).getCompleteUrl( ) == "https://trove.com/" );
//	assert( urlFrontierTest.Pop( ).getCompleteUrl( ) == "http://arcinnovations.xyz/" );
//	assert( urlFrontierTest.Pop( ).getCompleteUrl( ) == "https://gwydion.co/" );
//	assert( urlFrontierTest.Pop( ).getCompleteUrl( ) == "https://madeatmichigan.umich.edu/ventures/venture/gwydion/" );

	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 372 );

	assert ( dictionary->at( "=veronicacday.com/" ).size( ) == 1 && dictionary->at( "=veronicacday.com/" )[ 0 ] == 0 );
	assert ( dictionary->at( "%serena" ).size( ) == 2 && dictionary->at( "%serena" )[ 1 ] == 80 );
	assert ( dictionary->at( "#veronica" ).size( ) == 1 && dictionary->at( "#veronica" )[ 0 ] == 2 );
	assert ( dictionary->at( "#dai" ).size( ) == 1 && dictionary->at( "#dai" )[ 0 ] == 3 );
	assert ( dictionary->at( "%educ" ).size( ) == 1 && dictionary->at( "%educ" )[ 0 ] == 40 );
	assert ( dictionary->at( "%surgeri" ).size( ) == 2 && dictionary->at( "%surgeri" )[ 0 ] == 511 );
	assert ( dictionary->at( "%busi" ).size( ) == 6 );

	delete dictionary;
	dictionary = nullptr;

	cout << "Complex Test Passed! " << endl << endl;
	}


void testURL ( )
	{
	cout << "Testing URL: " << endl;
	UrlFrontier urlFrontierTest ;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://testurl.com" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/urlTest.html";

	LocalReader reader( filepath );
	reader.setUrl( &fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 3 );
	assert ( dictionary->at( "=testurl.com/" )[ 0 ] == 0 );
//	assert ( urlFrontierTest->Pop( )->getCompleteUrl( )  == "http://www.bafta.org/" );
	assert ( dictionary->find( "$bafta" ) == dictionary->end( ) );
	assert ( dictionary->at( "$testurl" )[ 0 ] == 0 );
	assert ( dictionary->at( "$com" )[ 0 ] == 1 );

	delete dictionary;
	dictionary = nullptr;
	cout << "URL Test Passed!" << endl << endl;
	}


void testBody ( )
	{
	cout << "Testing Body: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://www.testingBody.edu" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/testParserBody.html";

	LocalReader reader( filepath );
	reader.setUrl( &fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 17 );

	assert ( dictionary->at( "=www.testingBody.edu/" ).size( ) == 1 && dictionary->at( "=www.testingBody.edu/" )[ 0 ] == 0 );
	assert ( dictionary->at( "$edu" ).size( ) == 1 && dictionary->at( "$edu" )[ 0 ] == 1 );
	assert ( dictionary->at( "#stori" ).size( ) == 1 && dictionary->at( "#stori" )[ 0 ] == 2 );
	assert ( dictionary->at( "%up" ).size( ) == 1 && dictionary->at( "%up" )[ 0 ] == 10 );
	assert ( dictionary->at( "#cat" ).size( ) == 1 && dictionary->at( "#cat" )[ 0 ] == 3 );
	assert ( dictionary->at( "$testingbodi" ).size( ) == 1 && dictionary->at( "$testingbodi" )[ 0 ] == 0 );
	assert ( dictionary->at( "%saturdai" ).size( ) == 1 && dictionary->at( "%saturdai" )[ 0 ] == 4 );
	assert ( dictionary->at( "%cat" ).size( ) == 1 && dictionary->at( "%cat" )[ 0 ] == 6 );
	assert ( dictionary->at( "%joe" ).size( ) == 1 && dictionary->at( "%joe" )[ 0 ] == 5 );
	assert ( dictionary->at( "%went" ).size( ) == 1 && dictionary->at( "%went" )[ 0 ] == 7 );
	assert ( dictionary->at( "%weird" ).size( ) == 1 && dictionary->at( "%weird" )[ 0 ] == 12 );

	assert ( dictionary->at( "%store" ).size( ) == 3 && dictionary->at( "%store" )[ 0 ] == 8 &&
	         dictionary->at( "%store" )[ 1 ] == 13 && dictionary->at( "%store" )[ 2 ] == 16 );

	assert ( dictionary->at( "%climb" ).size( ) == 1 && dictionary->at( "%climb" )[ 0 ] == 9 );
	assert ( dictionary->at( "%mountain" ).size( ) == 1 && dictionary->at( "%mountain" )[ 0 ] == 11 );
	assert ( dictionary->at( "%call" ).size( ) == 1 && dictionary->at( "%call" )[ 0 ] == 14 );
	assert ( dictionary->at( "%food" ).size( ) == 1 && dictionary->at( "%food" )[ 0 ] == 15 );


	delete dictionary;
	dictionary = nullptr;
	cout << "Body Test Passed!" << endl << endl;
	}


void testExtractBody ( )
	{
	cout << "Testing ExtractBody: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl *fake_url = new ParsedUrl( "https://developer.mozilla.org/en-US/docs/Learn" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/testExtractBodyTest.html";

	LocalReader reader( filepath );
	reader.setUrl( fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert( dictionary != nullptr);
	assert( dictionary->size( ) == 16 );

	assert( dictionary->at( "=developer.mozilla.org/en-US/docs/Learn" )[ 0 ] == 0 );
	assert( dictionary->at( "$develop" )[ 0 ] == 0 );
	assert( dictionary->at( "%word" )[ 0 ] == 20 );
	assert( dictionary->at( "$mozilla" )[ 0 ] == 1);
	assert( dictionary->at( "$org" )[ 0 ] == 2 );
	assert( dictionary->at( "%paragraph" )[ 0 ] == 9 );
	assert( dictionary->at( "#specif" )[ 0 ] == 6 );
	assert( dictionary->at( "#titl" ).size( ) == 2 && dictionary->at( "#titl" )[ 0 ] == 7 && dictionary->at( "#titl" )[ 1 ] == 8 );
	assert( dictionary->at( "%text" ).size( ) == 4 && dictionary->at( "%text" )[ 0 ] == 11 && dictionary->at( "%text" )[ 1 ] == 12
	        && dictionary->at( "%text" )[ 2 ] == 13 && dictionary->at( "%text" )[ 3 ] == 19);

	assert( dictionary->at( "%bodi" ).size( ) == 4 && dictionary->at( "%bodi" )[ 0 ] == 10 && dictionary->at( "%bodi" )[ 1 ] == 14
	        && dictionary->at( "%bodi" )[ 2 ] == 17 && dictionary->at( "%bodi" )[ 3 ] == 18 );
	assert( dictionary->at( "%hello" )[ 0 ] == 15 );
	assert( dictionary->at( "%more" )[ 0 ] == 16 );

	delete dictionary;
	dictionary = nullptr;

	cout << "Extract Body Test Passed!" << endl;
	}

void testAnchorText ( )
	{
	cout << "Testing Anchor Text: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://www.testingBody.edu" );
	fake_url.setAnchorText( "anchor text example Click Here!");

	string filepath = util::GetCurrentWorkingDir( ) + "/tests/testParserBody.html";

	LocalReader reader( filepath );
	reader.setUrl( &fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert ( dictionary->at( "@anchor" )[ 0 ] == 0 );
	assert ( dictionary->at( "@text" )[ 0 ] == 1 );
	assert ( dictionary->at( "@exampl" )[ 0 ] == 2 );
	assert ( dictionary->find( "@click" ) == dictionary->end( ) );
	assert ( dictionary->find( "@here" ) == dictionary->end( ) );
	assert ( dictionary->find( "click" ) == dictionary->end( ) );
	assert ( dictionary->find( "here" ) == dictionary->end( ) );

	delete dictionary;
	dictionary = nullptr;

	cout << "Extract Anchor Test Passed!" << endl;
	}


void testHttps ( )
	{
	cout << "Testing HTTPS: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl httpsURL = ParsedUrl( "https://www.washingtonpost.com/local/md-politics/trump-taxes-legalized-pot-and-fracking-what-md-lawmakers-passed--and-didnt/2017/04/11/908b3744-1dfd-11e7-a0a7-8b2a45e3dc84_story.html?utm_term=.c3dbbe8e9ddd" );

	HttpsReader reader( &httpsURL );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	delete dictionary;
	dictionary = nullptr;

	cout << "HTTPS Test Passed! " << endl << endl;
	}

void testParseParagraph( )
	{
	cout << "Testing ExtractBody: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl *fake_url = new ParsedUrl( "https://developer.mozilla.org/en-US/docs/Learn" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/testExtractBodyTest2.html";

	LocalReader reader( filepath );
	reader.setUrl( fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert( dictionary->size( ) == 29 );
	assert ( dictionary->find( "%governor" ) != dictionary->end( ) && dictionary->at( "%governor" )[ 0 ] == 28 );
	assert ( dictionary->find( "%gener" ) != dictionary->end( ) && dictionary->at( "%gener" )[ 0 ] == 16 );
	assert ( dictionary->find( "%permiss" ) != dictionary->end( ) && dictionary->at( "%permiss" )[ 0 ] == 27 );
	assert ( dictionary->find( "%frosh" ) != dictionary->end( ) && dictionary->at( "%frosh" )[ 0 ] == 19 );
	assert ( dictionary->find( "%attornei" ) != dictionary->end( ) && dictionary->at( "%attornei" )[ 0 ] == 15 );
	assert ( dictionary->find( "$en" ) != dictionary->end( ) && dictionary->at( "$en" )[ 0 ] == 3 );

	delete dictionary;
	dictionary = nullptr;

	}

void testTitleParsing( )
	{
	cout << "Testing Title Parsing: " << endl;
	UrlFrontier urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://www.testingTitle.edu" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/testTitleParsing.html";

	LocalReader reader( filepath );
	reader.setUrl( &fake_url );
	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );

	assert ( dictionary != nullptr );
	assert ( dictionary->find( "=Trump calls out Animal Assad for suspected chemical attack - The Boston Globe" ) != dictionary->end( ) );
	assert ( dictionary->at( "=Trump calls out Animal Assad for suspected chemical attack - The Boston Globe" )[ 0 ] == 1 );
	assert ( dictionary->find( "#boston" ) != dictionary->end( ) && dictionary->at( "#boston" ).size( ) == 5 );
	assert ( dictionary->find( "#globe" ) != dictionary->end( ) && dictionary->at( "#globe" ).size( ) == 5 );
	assert ( dictionary->find( "#trump" ) != dictionary->end( ) && dictionary->at( "#trump" ).size( ) == 2 );
	assert ( dictionary->find( "#search" ) != dictionary->end( ) && dictionary->at( "#search" ).size( ) == 2 );

	delete dictionary;

	dictionary = nullptr;
	cout << "Title Parsing Test Passed!" << endl << endl;
	}