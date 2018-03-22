//
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"
//
//using namespace std;
//
//void testSimple ( );
//
//void testComplex ( );
//
//void testURL ( );
//
//void testExtractBody ( );
//
//void testBody ( );
//
int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
//	cout << "Testing URL: " << endl;
//	testURL( );
//	cout << "URL Test Passed!" << endl << endl;
//	cout << "Testing Simple: " << endl;
//	testSimple( );
//	cout << "Simple Test Passed!" << endl << endl;
//	cout << "Testing Complex: " << endl;
//	testComplex( );
//	cout << "Complex Test Passed!" << endl;
//	cout << "Testing BODY: " << endl;
//	testExtractBody( );
//	testBody( );
	cout << "Parser Tests Passed! :D" << endl;
	}
//
//
//
//\
//
//
//void testBody ( )
//	{
//	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
//	ParsedUrl url = ParsedUrl( "http://www.testurl.com" );
//	char docString[1024];
//	strcpy( docString, "<!DOCTYPE html>\n"
//			"<html>\n"
//			"<head>\n"
//			"<!-- HTML Codes by Quackit.com -->\n"
//			"<title>\n"
//			"Story of Cat</title>\n"
//			"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
//			"<meta name=\"keywords\" content=\"cat story\">\n"
//			"<meta name=\"description\" content=\"This is the tale of a cat names joe\">\n"
//			"<style>\n"
//			"body {background-color:#ffffff;background-repeat:no-repeat;background-position:top left;background-attachment:fixed;}\n"
//			"h1{font-family:Arial, sans-serif;color:#000000;background-color:#ffffff;}\n"
//			"p {font-family:Georgia, serif;font-size:14px;font-style:normal;font-weight:normal;color:#000000;background-color:#ffffff;}\n"
//			"</style>\n"
//			"</head>\n"
//			"<body>\n"
//			"<h1>Joe the cat</h1>\n"
//			"<p>On Saturday, joe the cat went to the store. He climbed up a mountain? It was weird. The store was called Food Store</p>\n"
//			"</body>\n"
//			"</html>" );
//	Document document( url, docString );
//
//	Parser parser( &urlFrontierTest );
//	auto dictionary = parser.execute( &document );
//	cout << dictionary->size( ) << endl;
//	//assert( dictionary->size( ) == 4);
//	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
//		{
//		cout << it->first << ':';
//		for ( int i = 0; i < it->second.size( ); ++i )
//			{
//			cout << it->second[ i ] << " ";
//			}
//		cout << std::endl;
//		}
//	}
//
//void testExtractBody ( )
//	{
//	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;
//	ParsedUrl url = ParsedUrl( "http://www.testurl.com" );
//	char docString[1024];
//	strcpy( docString, "<title>Paragraph body text hello</title>" );
//	Document document( url, docString );
//
//	Parser parser( &urlFrontierTest );
//	auto dictionary = parser.execute( &document );
//	cout << dictionary->size( ) << endl;
//	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
//		{
//		cout << it->first << ':';
//		for ( int i = 0; i < it->second.size( ); ++i )
//			{
//			cout << it->second[ i ] << " ";
//			}
//		cout << std::endl;
//		}
//	cout << endl << endl;
//	assert( dictionary->size( ) == 6 );
//
//	char docString2[1024];
//	strcpy( docString2, "<p>Paragraph body text hello <title>Specific title</title> more body words</p>" );
//	Document document2( url, docString2 );
//	Parser parser2( &urlFrontierTest );
//	dictionary = parser.execute( &document2 );
//	cout << "Dictionary 2 size " << dictionary->size( ) << endl;
//	for ( auto it = dictionary->begin( ); it != dictionary->end( ); it++ )
//		{
//		cout << it->first << ':';
//		for ( int i = 0; i < it->second.size( ); ++i )
//			{
//			cout << it->second[ i ] << " ";
//			}
//		cout << std::endl;
//		}
//	assert( dictionary->size( ) == 10 );
//	assert( dictionary->at( "#specif" )[ 0 ] == 0 );
//	assert( dictionary->at( "%paragraph" )[ 0 ] == 0 );
//	assert( dictionary->at( "%bodi" )[ 1 ] == 5 );
//
//
//	}
//
//
