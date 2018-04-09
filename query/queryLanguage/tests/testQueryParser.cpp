//
// Created by Zane Dunnings on 3/17/18.
//
//TODO Remove STL
#include "../QueryParser.h"
#include<iostream>
#include <fstream>

int main()
	{
	string query = "apollo moon OR landing";
	QueryParser parser;
	parser.parse( query );
	parser.printCompiledQuery();

	string query1 = " apollo moon ( landing OR fake )";
	QueryParser parser1;
	parser1.parse( query1 );
	parser1.printCompiledQuery ();



	}