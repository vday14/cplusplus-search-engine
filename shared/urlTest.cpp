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

	ParsedUrl test1 =  ParsedUrl("https://developer.mozilla.org/en-US/docs/Learn" ) ;
	//string protocol = test1.getProtocol();
	test1.printUrl();
	//assert( strcmp(test1.Service, "https") == 1);
	//assert( strcmp(test1.Host, "developer.mozilla.org") == 1);




	ParsedUrl test2 = ParsedUrl("http://www.example.com/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument");
	test2.printUrl();
	assert( strcmp(test2.Service, "http"));
	assert( strcmp(test2.Host, "example.com"));


	std::cout << "URL TEST PASSED" << std::endl;

	}