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
	Document document ( "<!DOCTYPE html>\n"
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

	Parser parser ( urlFrontierTest );
	auto dictionary = parser.execute ( &document );
	assert( dictionary != nullptr );
	cout << "Parser Tests Passed! :D" << endl;

	}

