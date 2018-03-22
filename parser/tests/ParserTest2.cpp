
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

using namespace std;

void testSimple( );
void testComplex( );
void testURL( );

void printDictionary ( unordered_map< string, vector< unsigned long > > dictionary );

int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
	testSimple( );
	testComplex( );
	testURL( );
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
	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://www.cats.com" );
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
	assert ( dictionary->size( ) == 13 );
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

void testComplex( )
	{
	cout << "Testing Complex: " << endl;
	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl httpURL = ParsedUrl( "www.veronicacday.com" );
	HttpReader reader( httpURL );

	auto success = reader.request( );
	if ( !success )
		{
		cerr << "Couldn't open file\n";
		exit( 1 );
		}

	auto dictionary = parser.execute( &reader );
	printDictionary( *dictionary );
	}


void testURL ( )
	{
	cout << "Testing URL: " << endl;
	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
	Parser parser( &urlFrontierTest );
	ParsedUrl fake_url = ParsedUrl( "http://testurl.com" );
	string filepath = util::GetCurrentWorkingDir( ) + "/tests/urlTest.html";

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
	assert ( dictionary->size( ) == 3 );
	assert ( dictionary->at( "=testurl.com/" )[ 0 ] == 0 );
	assert ( urlFrontierTest.Pop( ).getCompleteUrl( )  == "http://www.bafta.org/" );
	assert ( dictionary->find( "$bafta" ) == dictionary->end( ) );
	assert ( dictionary->at( "$testurl" )[ 0 ] == 0 );
	assert ( dictionary->at( "$com" )[ 0 ] == 1 );

	delete dictionary;
	dictionary = nullptr;
	cout << "URL Test Passed!" << endl << endl;
	}