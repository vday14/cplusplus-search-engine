//
// Created by Zane Dunnings on 3/17/18.
//
//TODO Remove STL
#include "../QueryParser.h"
#include <fstream>
#include "../../../util/DataStructureLib/tuple.cpp"

int main()
	{
	char* query = ' "apollo moon landing" | ( apple banana ) \0';
	QueryParser parser = QueryParser( query );
	TupleList ParseTree;
	}