
#include <string>
#include <vector>
#include "../stringProcessing.h"
#include "../Stemmer.h"
#include <iostream>
#include <cassert>

using namespace std;

void testFindStr ( string original );

void testFindNext ( );

void testFindPrev ( );

void testSplitStr ( string original );

void testIsStopWord ( );

void testToLower ( );

void testStemWord ( );

void testSubStr ( );

void testStripStr ( );

void testIsAlpha ( );

void testIsNum ( );

int main ( )
	{

	cout << "Beginning testing for StringProcessing" << endl << endl;

	string original = "It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. "
			"The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here',"
			"making it look like readable English. ";

	testFindStr( original );
	testFindNext( );
	testFindPrev( );
	testSplitStr( original );
	testIsStopWord( );
	testToLower( );
	testStemWord( );
	testSubStr( );
	testStripStr( );
	testIsAlpha( );
	testIsNum( );

	cout << "\nTests passed for StringProcessing :D" << endl;

	}

void testFindStr ( string original )
	{
	cout << "Testing findStr..." << endl;
	assert( *findStr( "established", original ) == 'e' );
	assert( *findStr( "Lorem Ipsum", original ) == 'L' );

	string title = "<title> This is a test </title>";
	auto word = findStr( "<title>", title );
	assert( *word == '<' );
	auto titleIt = title.begin( );
	while ( word != title.end( ) && titleIt != title.end( ) )
		{
		assert( *word == *titleIt );
		++word;
		++titleIt;
		}

	auto word1 = findStr( "</title>", title );
	assert( *word1 == '<' && *( word1 + 1 ) == '/' );
	assert( *findStr( "</title>", original ) == '\0' );
	assert( *findStr( "orange", original ) == '\0' );
	assert( *findStr( "orange", "apple" ) == '\0' );
	auto word2 = findStr( "bird", "bigbird" );
	assert( *word2 == 'b' && *( word2 + 1 ) == 'i' && *( word2 + 2 ) == 'r' );

	cout << "testFindStr passed" << endl << endl;

	}

void testFindNext ( )
	{
	cout << "Testing findNext..." << endl;

	string racecar = "racecar";
	string hello = "hello";
	string blank = "";

	assert ( *findNext( "race", racecar.begin( ) ) == 'r' );
	assert ( *findNext( "race", racecar.begin( ) + 4 ) == '\0' );
	assert ( *findNext( "car", racecar.begin( ) + 4 ) == 'c' );

	assert ( *findNext( "hello", hello.begin( ) ) == 'h' );
	assert ( *findNext( "ello", hello.begin( ) ) == 'e' );
	assert ( *findNext( "ello", hello.begin( ) + 2 ) == '\0' );

	assert ( *findNext( "", blank.begin( ) ) == '\0' );

	cout << "testFindNext passed" << endl << endl;

	}

void testFindPrev ( )
	{
	cout << "Testing findPrev..." << endl;

	string racecar = "racecar";
	string hello = "hello";
	string blank = "";

	assert ( *findPrev( "race", racecar.begin( ), racecar.begin( ) ) == '\0' );
	assert ( *findPrev( "race", racecar.begin( ) + 4, racecar.begin( ) ) == 'r' );
	assert ( *findPrev( "car", racecar.begin( ) + 4, racecar.begin( ) ) == '\0' );
	assert ( *findPrev( "car", racecar.begin( ) + 7, racecar.begin( ) ) == 'c' );

	assert ( *findPrev( "hello", hello.begin( ), hello.begin( ) ) == '\0' );
	assert ( *findPrev( "ello", hello.begin( ) + 3, hello.begin( ) ) == '\0' );
	assert ( *findPrev( "ello", hello.begin( ) + 5, hello.begin( ) ) == 'e' );

	assert ( *findPrev( "", blank.begin( ), blank.begin( ) ) == '\0' );

	string fall = "fall";
	assert ( *findPrev( "bl", fall.begin( ) + 3, fall.begin( ) ) == '\0' );

	cout << "testFindPrev passed" << endl << endl;

	}

void testSplitStr ( string original )
	{
	cout << "Testing splitStr..." << endl;

	vector< string > vec = splitStr( original, ' ' );
	assert( vec.size( ) == 53 );

	string word = "hello\ngoodbye";
	vec = splitStr( word, '\n' );
	assert( vec.size( ) == 2 );
	assert( vec[ 0 ] == "hello" && vec[ 1 ] == "goodbye" );

	cout << "testSplitStr passed" << endl << endl;

	}

void testIsStopWord ( )
	{
	cout << "Testing isStopWord..." << endl;

	string is = "is";
	string hello = "Hello";
	string none = "none";
	string blank = "";
	string blank2 = " ";

	assert ( isStopWord( is ) );
	assert ( !isStopWord( hello ) );
	assert ( isStopWord( none ) );
	assert ( !isStopWord( blank ) );
	assert ( !isStopWord( blank2 ) );

	cout << "testIsStopWord passed" << endl << endl;

	}

void testToLower ( )
	{
	cout << "Testing toLower..." << endl;

	string word = "HELLO";
	string word2 = "hello";
	string word3 = "Hello GoodBye !";
	string word4 = "";
	string word5 = " ";

	string test = toLower( word );
	string test2 = toLower( word2 );
	string test3 = toLower( word3 );
	string test4 = toLower( word4 );
	string test5 = toLower( word5 );

	assert ( test == "hello" );
	assert ( test2 == "hello" );
	assert ( test3 == "hello goodbye !" );
	assert ( test4 == "" );
	assert ( test5 == " " );

	cout << "testToLower passed" << endl << endl;
	}

void testStemWord ( )
	{
	cout << "Testing stemWord..." << endl;
	Stemmer stem;

	assert ( stem.execute( "cats" ) == "cat" );
	assert ( stem.execute( "wilde" ) == "wild" );
	assert( stem.execute( "zoo" ) == "zoo" );
	assert( stem.execute( "troublesome" ) == "troublesom" );

	cout << "testStemWord passed" << endl << endl;
	}

void testSubStr ( )
	{
	cout << "Testing subStr..." << endl;

	string hello = "hello";
	string goodbye = "goodbye";
	string blank = " ";
	string blank2 = "";

	assert ( subStr( hello, 1, 4 ) == "ello" );
	assert ( subStr( hello, 0, 5 ) == "hello" );
	assert ( subStr( hello, 0, 1 ) == "h" );
	assert ( subStr( hello, 1, 2 ) == "el" );

	assert ( subStr( goodbye, 0, 4 ) == "good" );
	assert ( subStr( goodbye, 4, 3 ) == "bye" );
	assert ( subStr( goodbye, 1, 0 ) == "" );
	assert ( subStr( goodbye, 0, 7 ) == "goodbye" );

	assert ( subStr( blank, 0, 1 ) == " " );
	assert ( subStr( blank, 0, 0 ) == "" );
	assert ( subStr( blank2, 0, 0 ) == "" );

	assert ( subStr( hello.begin( ), hello.end( ) ) == "hello" );
	assert ( subStr( hello.begin( ) + 4, hello.begin( ) + 5 ) == "o" );
	assert ( subStr( hello.begin( ), hello.begin( ) + 1 ) == "h" );
	assert ( subStr( goodbye.begin( ) + 1, goodbye.begin( ) + 3 ) == "oo" );


	cout << "testSubStrpassed" << endl << endl;

	}


void testStripStr ( )
	{
	cout << "Testing stripStr..." << endl;

	char arr[] = { ',', '.', '*', '&', '^', '%', ';', ' ' };
	vector< char > chars( arr, arr + sizeof( arr ) / sizeof( arr[ 0 ] ) );

	string hello = "!hello!";
	string allSym = "\"*&^%;";
	string comma = "comma,";
	string period = "period.";
	string blank = " ";

	assert ( stripStr( hello ) == "hello" );
	assert ( stripStr( allSym ) == "" );
	assert ( stripStr( comma ) == "comma" );
	assert ( stripStr( period ) == "period" );
	assert ( stripStr( blank ) == "" );

	assert ( stripStr( hello, chars ) == "!hello!" );
	assert ( stripStr( allSym, chars ) == "\"" );
	assert ( stripStr( comma, chars ) == "comma" );
	assert ( stripStr( period, chars ) == "period" );
	assert ( stripStr( blank, chars ) == "" );

	cout << "testStripStrpassed" << endl << endl;
	}

void testIsAlpha ( )
	{
	cout << "Testing isAlpha..." << endl;

	assert ( isAlpha( 'a' ) );
	assert ( isAlpha( 'A' ) );
	assert ( isAlpha( 'z' ) );
	assert ( isAlpha( 'Z' ) );
	assert ( isAlpha( 'g' ) );
	assert ( isAlpha( 'i' ) );
	assert ( isAlpha( 'P' ) );

	assert ( !isAlpha( '1' ) );
	assert ( !isAlpha( '0' ) );
	assert ( !isAlpha( '9' ) );
	assert ( !isAlpha( '5' ) );
	assert ( !isAlpha( '6' ) );

	assert ( !isAlpha( ' ' ) );
	assert ( !isAlpha( '!' ) );
	assert ( !isAlpha( '/' ) );
	assert ( !isAlpha( '?' ) );
	assert ( !isAlpha( '*' ) );
	assert ( !isAlpha( '-' ) );
	assert ( !isAlpha( '.' ) );
	assert ( !isAlpha( ',' ) );
	assert ( !isAlpha( '(' ) );
	assert ( !isAlpha( '}' ) );

	cout << "testIsAlpha passed" << endl << endl;
	}

void testIsNum ( )
	{
	cout << "Testing isNum..." << endl;

	assert ( !isNum( 'a' ) );
	assert ( !isNum( 'A' ) );
	assert ( !isNum( 'z' ) );
	assert ( !isNum( 'Z' ) );
	assert ( !isNum( 'g' ) );
	assert ( !isNum( 'i' ) );
	assert ( !isNum( 'P' ) );

	assert ( isNum( '1' ) );
	assert ( isNum( '0' ) );
	assert ( isNum( '9' ) );
	assert ( isNum( '5' ) );
	assert ( isNum( '6' ) );

	assert ( !isNum( ' ' ) );
	assert ( !isNum( '!' ) );
	assert ( !isNum( '/' ) );
	assert ( !isNum( '?' ) );
	assert ( !isNum( '*' ) );
	assert ( !isNum( '-' ) );
	assert ( !isNum( '.' ) );
	assert ( !isNum( ',' ) );
	assert ( !isNum( '(' ) );
	assert ( !isNum( '}' ) );

	cout << "testIsNum passed" << endl;
	}