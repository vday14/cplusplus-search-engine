//
// Created by Jake Close on 2/13/18.
//

#include "url.h"
#include <string>
using namespace std;
#include <stdlib.h>
#include <iostream>
#include <assert.h>

int main(int argc, const char * argv[])
	{

	ParsedUrl absoluteURLTest =  ParsedUrl("https://developer.mozilla.org/en-US/docs/Learn" ) ;
	//string protocol = test1.getProtocol();
	absoluteURLTest.printUrl();
	//assert( strcmp(test1.Service, "https") == 1);
	//assert( strcmp(test1.Host, "developer.mozilla.org") == 1);




	ParsedUrl fragmentTest = ParsedUrl("http://www.example.com/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument");
	fragmentTest.printUrl();
	//assert( strcmp(fragmentTest.Service, "http"));
	//assert( strcmp(fragmentTest.Host, "example.com"));

	ParsedUrl gov = ParsedUrl("http://www.goverment.gov/path/to/myfile.html");
	gov.printUrl();
	//ParsedUrl relativeURLTest = ParsedUrl("/wiki/List_of_sheep_breeds");
	//relativeURLTest.printUrl();


	//ParsedUrl pointToFragment = ParsedUrl("#topOfPage");

	//ParsedUrl mailToTest = ParsedUrl("mailto:someone@example.com?cc=someoneelse@example.com&bcc=andsomeoneelse@example.com\n"
	//													"&subject=Summer%20Party&body=You%20are%20invited%20to%20a%20big%20summer%20party!\"");
	//mailToTest.printUrl();
	//std::cout << "URL TEST PASSED" << std::endl;

	}