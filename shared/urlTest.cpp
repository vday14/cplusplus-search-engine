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

	Url test1 =  Url("https://developer.mozilla.org/en-US/docs/Learn" ) ;
	string protocol = test1.getProtocol();
	assert( protocol == "https");
	string domain = test1.getDomain();
	assert( domain == "developer.mozilla.org");
	string domainType = test1.getDomainType();
	assert( domainType == "org");



	Url test2 = Url("http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2#SomewhereInTheDocument");
	test2.removeAnchor();
	assert( test2.url == "http://www.example.com:80/path/to/myfile.html?key1=value1&key2=value2" );
	protocol = test2.getProtocol();
	assert( protocol == "http");
	domain = test2.getDomain();
	assert( domain == "example.com");
	domainType = test2.getDomainType();
	assert( domainType == "com");

	std::cout << "URL TEST PASSED" << std::endl;

	}