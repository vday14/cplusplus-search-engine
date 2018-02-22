//
// Created by Veronica Day on 2/13/18.
//

#include <string>
#include <vector>
#include "../stringProcessing.h"
#include <iostream>
#include <cassert>

using namespace std;

void testFindStr ( string original );

void testSplitStr ( string original );

void testToLower ( );

void testIsStopWord ( );

int main ( )
	{

	cout << "Beginning testing for StringProcessing_unit" << endl << endl;

	string original = "It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. "
			"The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here',"
			"making it look like readable English. ";

	testFindStr ( original );
	testSplitStr ( original );
	testToLower ( );
	testIsStopWord ( );

	cout << "\nTests passed for StringProcessing_unit :D" << endl;

	}

void testFindStr ( string original )
	{
	cout << "Testing findStr..." << endl;
	assert( *findStr ( original, "established" ) == 'e' );
	assert( *findStr ( original, "Lorem Ipsum" ) == 'L' );

	string title = "<title> This is a test </title>";
	auto word = findStr ( title, "<title>" );
	assert( *word == '<' );
	auto titleIt = title.begin ( );
	while ( word != title.end ( ) && titleIt != title.end ( ) )
		{
		assert( *word == *titleIt );
		++word;
		++titleIt;
		}

	auto word1 = findStr ( title, "</title>" );
	assert( *word1 == '<' && *( word1 + 1 ) == '/' );
	assert( *findStr ( original, "</title>" ) == '\0' );
	assert( *findStr ( original, "orange" ) == '\0' );
	assert( *findStr ( "apple", "orange" ) == '\0' );
	auto word2 = findStr ( "bigbird", "bird" );
	assert( *word2 == 'b' && *( word2 + 1 ) == 'i' && *( word2 + 2 ) == 'r' );

	cout << "testFindStr passed" << endl;

	}


void testSplitStr ( string original )
	{
	cout << "Testing splitStr..." << endl;

	vector< string > vec = splitStr ( original, ' ' );
	assert( vec.size ( ) == 53 );

	string word = "hello\ngoodbye";
	vec = splitStr ( word, '\n' );
	assert( vec.size ( ) == 2 );
	assert( vec[ 0 ] == "hello" && vec[ 1 ] == "goodbye" );

	cout << "testSplitStr passed" << endl;

	}


void testToLower ( )
	{
	cout << "Testing toLower..." << endl;

	string word = "HELLO";
	string word2 = "hello";
	string word3 = "Hello GoodBye !";
	string word4 = "";
	string word5 = " ";

	string test = toLower ( word );
	string test2 = toLower ( word2 );
	string test3 = toLower ( word3 );
	string test4 = toLower ( word4 );
	string test5 = toLower ( word5 );

	assert ( test == "hello" );
	cout << test2 << endl;
	assert ( test2 == "hello" );
	assert ( test3 == "hello goodbye !" );
	assert ( test4 == "" );
	assert ( test5 == " " );

	cout << "testToLower passed" << endl;
	}


void testIsStopWord ( )
	{
	cout << "Testing isStopWord..." << endl;

	string is = "is";
	string hello = "Hello";
	string none = "none";
	string blank = "";
	string blank2 = " ";

	assert ( isStopWord ( is ) );
	assert ( !isStopWord ( hello ) );
	assert ( isStopWord ( none ) );
	assert ( !isStopWord ( blank ) );
	assert ( !isStopWord ( blank2 ) );

	cout << "testIsStopWord passed" << endl;

	}