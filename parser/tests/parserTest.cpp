
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"

using namespace std;

void testSimple ( );

void testComplex ( );

void testURL ( );

void testExtractBody( );

void testBody( );

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
    cout << "Testing BODY: " << endl;
    testExtractBody( );
    testBody( );
    cout << "Parser Tests Passed! :D" << endl;
    }

void testSimple( )
	{

	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
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

	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
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
//	const char *line = "<li><span class=\"official-website\"><span class=\"url\"><a rel=\"nofollow\" class=\"external text\" href=\"http://www.bafta.org/\">Official website</a></span></span></li>";
	const char * line = "<span class=\"url\"><a rel=\"nofollow\" class=\"external text\" href=\"http://www.bafta.org/\">Official website</a>";
	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
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

	string completeUrl = "";
	completeUrl.assign( urlFrontierTest.Pop( ).CompleteUrl );
	assert ( completeUrl == "http://www.bafta.org/" );
	assert ( dictionary->find( "$bafta" ) == dictionary->end( ) );
	assert ( dictionary->find( "$testurl" ) != dictionary->end( ) );

	delete dictionary;
	dictionary = nullptr;
	}

void testBody( )
{
    ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
    ParsedUrl url = ParsedUrl( "http://www.testurl.com" );
    char docString[1024];
    strcpy( docString, "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "<!-- HTML Codes by Quackit.com -->\n"
            "<title>\n"
            "Story of Cat</title>\n"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            "<meta name=\"keywords\" content=\"cat story\">\n"
            "<meta name=\"description\" content=\"This is the tale of a cat names joe\">\n"
            "<style>\n"
            "body {background-color:#ffffff;background-repeat:no-repeat;background-position:top left;background-attachment:fixed;}\n"
            "h1{font-family:Arial, sans-serif;color:#000000;background-color:#ffffff;}\n"
            "p {font-family:Georgia, serif;font-size:14px;font-style:normal;font-weight:normal;color:#000000;background-color:#ffffff;}\n"
            "</style>\n"
            "</head>\n"
            "<body>\n"
            "<h1>Joe the cat</h1>\n"
            "<p>On Saturday, joe the cat went to the store. He climbed up a mountain? It was weird. The store was called Food Store</p>\n"
            "</body>\n"
            "</html>" );
    Document document( url, docString );

    Parser parser( &urlFrontierTest );
    auto dictionary = parser.execute( &document );
    cout << dictionary->size( ) << endl;
    //assert( dictionary->size( ) == 4);
    for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
    {
        cout << it->first << ':';
        for ( int i = 0; i < it->second.size( ); ++i )
        {
            cout << it->second[ i ] << " ";
        }
        cout << std::endl;
    }
}
void testExtractBody ( )
{
    ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
    ParsedUrl url = ParsedUrl( "http://www.testurl.com" );
    char docString[1024];
    strcpy( docString, "<title>Paragraph body text hello</title>" );
    Document document( url, docString );

    Parser parser( &urlFrontierTest );
    auto dictionary = parser.execute( &document );
    cout << dictionary->size( ) << endl;
    for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
    {
        cout << it->first << ':';
        for ( int i = 0; i < it->second.size( ); ++i )
        {
            cout << it->second[ i ] << " ";
        }
        cout << std::endl;
    }
    cout << endl << endl;
    assert( dictionary->size( ) == 6);

    char docString2[1024];
    strcpy( docString2, "<p>Paragraph body text hello <title>Specific title</title> more body words</p>" );
    Document document2( url, docString2 );
    Parser parser2 ( &urlFrontierTest );
    dictionary = parser.execute( &document2 );
    cout << "Dictionary 2 size " << dictionary->size( ) << endl;
    for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
    {
        cout << it->first << ':';
        for ( int i = 0; i < it->second.size( ); ++i )
        {
            cout << it->second[ i ] << " ";
        }
        cout << std::endl;
    }
    assert( dictionary->size( ) == 10);
    assert( dictionary->at( "#specif" )[0] == 0);
    assert( dictionary->at("%paragraph")[0] == 0);
    assert( dictionary->at("%bodi")[1] == 5);


}


