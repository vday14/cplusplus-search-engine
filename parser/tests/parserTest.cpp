
#include <string>
#include <cassert>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"

using namespace std;

void testSimple ( );

void testComplex ( );

void testURL ( );

int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
	cout << "Testing URL: " << endl;
	testURL ( );
	cout << "URL Test Passed!" << endl << endl;
	cout << "Testing Simple: " << endl;
	testSimple( );
	cout << "Simple Test Passed!" << endl << endl;
	cout << "Testing Complex: " << endl;
	testComplex( );
	cout << "Complex Test Passed!" << endl;
	cout << "Parser Tests Passed! :D" << endl;

	}

void testSimple ( )
	{

	ProducerConsumerQueue< string > urlFrontierTest;
	ParsedUrl url = ParsedUrl( "http://www.testurl.com" );
	char docString[10240];
	strcpy( docString, "<title>This Cat Title Cat</title>" );
	Document document( url, docString );

	Parser parser( &urlFrontierTest );
	auto dictionary = parser.execute( &document );
	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
		{
		cout << it->first << ':';
		for ( int i = 0; i < it->second.size( ); ++i )
			{
			cout << it->second[ i ] << " ";
			}
		cout << std::endl;
		}
	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 4 );
	assert ( dictionary->find( "#cat" ) != dictionary->end( ) );
	assert ( dictionary->find( "$testurl" ) != dictionary->end( ) );
	assert ( dictionary->find( "#titl" ) != dictionary->end( ) );
	assert ( dictionary->find( "#this" ) == dictionary->end( ) );
	assert ( dictionary->at( "#cat" )[ 0 ] == 0 && dictionary->at( "#cat" )[ 1 ] == 2 );
	assert ( dictionary->at( "#titl" )[ 0 ] == 1 );

	delete dictionary;
	dictionary = nullptr;
	}

void testComplex ( )
	{

	ProducerConsumerQueue< string > urlFrontierTest;
	ifstream file( "../tests/cats.html" );
	string temp;
	string docString = "<title>Joe the Cat</title>\n";
	docString += "<a href=\"https://www.w3schools.com/html/\">Visit our HTML tutorial</a>\n";
	while ( std::getline( file, temp ) )
		{
		docString += temp;
		}
	ParsedUrl url = ParsedUrl( "https://www.w3schools.com/tests/cats.html" );
	char *writable = new char[docString.size( ) + 1];
	std::copy( docString.begin( ), docString.end( ), writable );
	writable[ docString.size( ) ] = '\0';

	Document document( url, writable );

	Parser parser( &urlFrontierTest );
	auto dictionary = parser.execute( &document );
	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
		{
		cout << it->first << ':';
		for ( int i = 0; i < it->second.size( ); ++i )
			{
			cout << it->second[ i ] << " ";
			}
		cout << std::endl;
		}
	assert ( dictionary != nullptr );
	assert ( dictionary->size( ) == 8 );

	assert ( dictionary->find( "#cat" ) != dictionary->end( ) );
	assert ( dictionary->find( "#stori" ) != dictionary->end( ) );
	assert ( dictionary->find( "#joe" ) != dictionary->end( ) );
	assert ( dictionary->find( "$w3school" ) != dictionary->end( ) );
	assert ( dictionary->find( "$test" ) != dictionary->end( ) );
	assert ( dictionary->find( "$cat" ) != dictionary->end( ) );

	assert ( dictionary->find( "#the" ) == dictionary->end( ) );
	assert ( dictionary->find( "#of" ) == dictionary->end( ) );

	delete dictionary;
	dictionary = nullptr;
	delete[] writable;
	writable = nullptr;

	}

void testURL ( )
	{
	const char *line = "<li><span class=\"official-website\"><span class=\"url\"><a rel=\"nofollow\" class=\"external text\" href=\"http://www.bafta.org/\">Official website</a></span></span></li>";

	ProducerConsumerQueue< string > urlFrontierTest;
	ParsedUrl url = ParsedUrl( "http://testurl.com" );
	char docString[10240];
	strcpy( docString, line );
	Document document( url, docString );

	Parser parser( &urlFrontierTest );
	auto dictionary = parser.execute( &document );
	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
		{
		cout << it->first << ':';
		for ( int i = 0; i < it->second.size( ); ++i )
			{
			cout << it->second[ i ] << " ";
			}
		cout << std::endl;
		}

	assert ( urlFrontierTest.Pop( ) == "http://www.bafta.org/");
	assert ( dictionary->find( "$bafta" ) == dictionary->end( ) );
	assert ( dictionary->find( "$testurl" ) != dictionary->end( ) );

	delete dictionary;
	dictionary = nullptr;
	}