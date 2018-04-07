//
// Created by Jake Close on 4/7/18.
//


#include "../QueryParser.h"
#include<iostream>
#include <fstream>
#include "../../../constraintSolver/ISRContainer.h"

int main()
	{
	string query = "moment life";
	string OR = "bike cycle ";
	QueryParser parser;
	parser.parse( "moment" );

	Token life = Token("life");
	Tuple* lifeTuple = new Tuple( life );

	parser.queryTree->Next.push_back( lifeTuple );




	Token orParentToken = Token("-And-");
	Tuple * orparent = new Tuple( orParentToken );

	Token bike = Token("bike");
	Token cycle = Token("cycle");

	Tuple* bikeTuple = new Tuple( bike );
	Tuple* cycleTuple = new Tuple( cycle );

	orparent->Next.push_back(bikeTuple);
	orparent->Next.push_back( cycleTuple);


	parser.printCompiledQuery();


	//parser.queryTree->Next.push_back( orparent );



	ISRContainer container ( parser.queryTree  );

	container.Solve( );
	}