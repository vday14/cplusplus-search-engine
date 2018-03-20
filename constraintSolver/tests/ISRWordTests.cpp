//
// Created by nick on 3/16/18.
//

#include <iostream>
#include "../ISRWord.h"
#include "../ISRWord.cpp"


using namespace std;

int main ( )
	{
	char *w = new char[10];
	strcpy( w, "hello" );
	ISRWord word = ISRWord( w );

	while ( 1 )
		{
		cout << word.next( ) << endl;
		}
	return 0;
	}