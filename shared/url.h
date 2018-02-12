//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include <string>
class Url
	{

	std::string url;

	Url( string url_in ) : url( url_in) {};


	//Removes/ parses url
	void clean();

	//parses domain from url
	void getDomain();


	};


