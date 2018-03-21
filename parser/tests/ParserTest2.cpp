//
// Created by Ben Bergkamp on 3/21/18.
//

#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include "../Parser.h"
#include "../../shared/Document.h"
#include "../../shared/ProducerConsumerQueue.h"
#include "../../crawler/Readers/LocalReader.h"
#include "../../util/util.h"

using namespace std;

void TestSimple()
	{
	ProducerConsumerQueue< ParsedUrl > urlFrontierTest;

	Parser parser( &urlFrontierTest );


	ParsedUrl fake_url = ParsedUrl("http://www.cats.com");

	string filepath = util::GetCurrentWorkingDir() + "/tests/plaintext.txt";

	LocalReader reader(filepath);
	reader.setUrl(fake_url);
	auto success = reader.request();
	if(!success)
	{
		cerr << "Couldnt open file\n";
		exit(1);
	}

	auto dictionary = parser.execute( &reader );

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

int main()
	{
		TestSimple();
	}