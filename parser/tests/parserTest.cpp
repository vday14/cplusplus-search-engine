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

int main ( )
	{
	cout << "Testing Parser ... " << endl << endl;
	ProducerConsumerQueue < string > * urlFrontierTest;
	Document document ( "<title>This Cat Title Cat</title>\n" );

	Parser parser ( urlFrontierTest );
	auto dictionary = parser.execute ( &document );

	assert ( dictionary != nullptr );
	assert ( dictionary->size () == 2);
	assert ( dictionary->find ( "cat" ) != dictionary->end () );
	assert ( dictionary->find ( "title" ) != dictionary->end () );
	assert ( dictionary->find ( "this" ) == dictionary->end () );
	assert ( dictionary->at ( "cat" )[ 0 ] == 0 && dictionary->at ( "cat" )[ 1 ] == 2 );
	assert ( dictionary->at ( "title" )[ 0 ] == 1 );

	cout << "Parser Tests Passed! :D" << endl;

	}

