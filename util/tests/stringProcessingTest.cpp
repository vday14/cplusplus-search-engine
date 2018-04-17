
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

//	testFindStr( original );
//	testFindNext( );
//	testFindPrev( );
//	testSplitStr( original );
//	testIsStopWord( );
//	testToLower( );
	testStemWord( );
//	testSubStr( );
//	testStripStr( );
//	testIsAlpha( );
//	testIsNum( );

	cout << "\nTests passed for StringProcessing :D" << endl;

	}

void testFindStr ( string original )
	{
	cout << "Testing findStr..." << endl;
	assert( findStr( "established", original ) == 13 );
	assert( findStr( "Lorem Ipsum", original ) == 144 );

	string title = "<title> This is a test </title>";
	unsigned long i = findStr( "<title>", title );
	assert( title[ i ] == '<' );
	int j = 0;
	while ( i < title.size( ) && j < title.size( ) )
		{
		assert( title[ i ] == title[ j ] );
		++i;
		++j;
		}

	unsigned long word1 = findStr( "</title>", title );
	assert( title[ word1 ] == '<' && title[ word1 + 1 ] == '/' );
	assert( findStr( "</title>", original ) == original.size( ) );
	assert( findStr( "orange", original ) == original.size( ) );
	assert( findStr( "orange", "apple" ) == 5 );
	unsigned long word2 = findStr( "bird", "bigbird" );
	assert( word2 == 3 );

	cout << "testFindStr passed" << endl << endl;

	}

void testFindNext ( )
	{
	cout << "Testing findNext..." << endl;

	string racecar = "racecar";
	string hello = "hello";
	string blank = "";

	assert ( findNext( "race", 0, racecar ) == 0 );
	assert ( findNext( "race", 4, racecar ) == racecar.size( ) );
	assert ( findNext( "car", 4, racecar ) == 4 );

	assert ( findNext( "hello", 0, hello ) == 0 );
	assert ( findNext( "ello", 0, hello ) == 1 );
	assert ( findNext( "ello", 2, hello ) == hello.size( ) );

	assert ( findNext( "", 0, blank ) == blank.size( ) );

	cout << "testFindNext passed" << endl << endl;

	}

void testFindPrev ( )
	{
	cout << "Testing findPrev..." << endl;

	string racecar = "racecar";
	string hello = "hello";
	string blank = "";

	assert ( findPrev( "race", 0, racecar ) == racecar.size( ) );
	assert ( findPrev( "race", 4, racecar ) == 0 );
	assert ( findPrev( "car", 4, racecar ) == racecar.size( ) );
	assert ( findPrev( "car", 7, racecar ) == 4 );

	assert ( findPrev( "hello", 0, hello ) == hello.size( ) );
	assert ( findPrev( "ello", 3, hello ) == hello.size( ) );
	assert ( findPrev( "ello", 5, hello ) == 1 );

	assert ( findPrev( "", 0, blank ) == blank.size( ) );

	string fall = "fall";
	assert ( findPrev( "bl", 3, fall ) == fall.size( ) );

	cout << "testFindPrev passed" << endl << endl;

	}

void testSplitStr ( string original )
	{
	cout << "Testing splitStr..." << endl;

	vector< string > vec = splitStr( original, ' ', true );
	assert( vec.size( ) == 53 );

	string word = "hello goodbye";
	vec = splitStr( word, ' ', true );
	assert( vec.size( ) == 2 );
	assert( vec[ 0 ] == "hello" && vec[ 1 ] == "goodbye" );

	word = "apollo moon OR landing";
	vec = splitStr( word, ' ', false );
	assert( vec.size( ) == 4 );
	assert( vec[ 0 ] == "apollo" && vec[ 1 ] == "moon" && vec[ 2 ] == "OR" && vec[ 3 ] == "landing" );

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

	/*assert ( stem.execute( "cats" ) == "cat" );
	assert ( stem.execute( "wilde" ) == "wild" );
	assert( stem.execute( "zoo" ) == "zoo" );
	assert( stem.execute( "troublesome" ) == "troublesom" );

	cout << "testStemWord passed" << endl << endl;*/

	    cout << stem.execute("white") << endl;
		cout << stem.execute("house") << endl;
		cout << stem.execute("trump") << endl;
		cout << stem.execute("office") << endl;
		cout << stem.execute("president") << endl;
		cout << stem.execute("james") << endl;
		cout << stem.execute("comey") << endl;
		cout << stem.execute("corrupt") << endl;
		cout << stem.execute("fbi") << endl;

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