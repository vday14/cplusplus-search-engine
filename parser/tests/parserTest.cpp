//
// Created by anvia on 2/6/2018.
//

#include <string>
#include <cassert>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"

using namespace std;

void testSimple ( );
void testComplex ( );

int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
	testSimple ();
	testComplex ();
	cout << "Parser Tests Passed! :D" << endl;

	}

void testSimple ( )
	{

	ProducerConsumerQueue < string > * urlFrontierTest;
	Document document ( "<title>This Cat Title Cat</title>" );

	Parser parser ( urlFrontierTest );
	auto dictionary = parser.execute ( &document );

	assert ( dictionary != nullptr );
	assert ( dictionary->size () == 2);
	assert ( dictionary->find ( "cat" ) != dictionary->end () );
	assert ( dictionary->find ( "title" ) != dictionary->end () );
	assert ( dictionary->find ( "this" ) == dictionary->end () );
	assert ( dictionary->at ( "cat" )[ 0 ] == 0 && dictionary->at ( "cat" )[ 1 ] == 2 );
	assert ( dictionary->at ( "title" )[ 0 ] == 1 );

	delete dictionary;

	}
void testComplex ( )
	{

	ProducerConsumerQueue < string > * urlFrontierTest;
	ifstream file("../tests/cats.html");
	string temp;
	string docString = "<title>Joe the Cat</title>\n";
	docString += "<a href=\"https://www.w3schools.com/html/\">Visit our HTML tutorial</a>\n";
	while(std::getline(file, temp)) {
		docString += temp;
		}

	Document document ( docString );

	Parser parser ( urlFrontierTest );
	auto dictionary = parser.execute ( &document );

//	cout << dictionary->size () << endl;
//	for (auto p : *dictionary)
//		cout << p.first << endl;

	assert ( dictionary != nullptr );
	assert ( dictionary->size () == 3);

	assert ( dictionary->find ( "cat" ) != dictionary->end () );
	assert ( dictionary->find ( "story" ) != dictionary->end () );
	assert ( dictionary->find ( "joe" ) != dictionary->end () );

	assert ( dictionary->find ( "the" ) == dictionary->end () );
	assert ( dictionary->find ( "of" ) == dictionary->end () );

//	assert ( dictionary->at ( "cat" )[ 0 ] == 1 );
//	assert ( dictionary->at ( "story" )[ 0 ] == 0 );
//	cout << urlFrontierTest->Size () << endl;
//	cout << urlFrontierTest->Pop () << endl;
	delete dictionary;

	}