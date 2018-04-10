//
// Created by Zane Dunnings on 3/17/18.
//
//TODO Remove STL
#include "../QueryParser.h"
#include<iostream>
#include <fstream>
#include <cassert>

using namespace std;
void testAND();
void testOR();
void testSimple();
void testORwithAND();
void testnestedOR();
//void nestedAND();
void testNestedORwithAND();

int main()
	{
	cout << "Starting QueryLang tests...\n";
	testAND();
	testOR();
	testSimple ();
	testORwithAND ();
	testNestedORwithAND();
	testnestedOR();

	}

void testAND()
	{
	cout << "Testing AND...\n";
	string query = "Is Lebron james the goat";
	QueryParser lebronParser;
	lebronParser.parse( query );
	string correct = " |  -AND-  | \n[ 1 ]  Is  |  Lebron  |  james  |  the  |  goat ";
	assert(correct == lebronParser.getTestingTree( ));

	string dessertQuery = "I like cookies AND cake & pie && icecream and dessert";
	QueryParser dessertParser;
	dessertParser.parse( dessertQuery );
	string correctDesserts = " |  -AND-  | \n[ 1 ]  I  |  like  |  cookies  |  cake  |  pie  |  icecream  |  dessert ";
	assert(correctDesserts == dessertParser.getTestingTree( ));
	cout << "All AND tests passed!\n";

	}

void testOR()
	{
	cout << "Testing OR..\n";
	string query = "who or what OR when || where | why";
	QueryParser Parser;
	Parser.parse( query );
	string correct = " |  -OR-  | \n[ 1 ]  who  |  what  |  when  |  where  |  why ";
	assert(correct == Parser.getTestingTree( ));

	string simple = "left or right";
	QueryParser simpleParser;
	simpleParser.parse( simple );
	string simpleCorrect = " |  -OR-  | \n[ 1 ]  left  |  right ";
	assert( simpleCorrect == simpleParser.getTestingTree( ) );

	cout << "All OR tests passes\n";

	}

void testSimple()
	{
	cout << "Testing Simple Case..\n";
	string simple = "Zane";
	QueryParser Parser;
	Parser.parse( simple );
	string correct = " |  Zane ";
	assert(correct == Parser.getTestingTree( ));
	cout<<"All simple tests passed!\n";
	}

void testORwithAND()
	{
	cout << "Testing OR with AND\n";
	string nasa = "moon mission was a lie OR truth ";
	QueryParser Parser;
	Parser.parse( nasa );
	string correct = " |  -OR-  | \n"
			"[ 1 ]  -AND-  |  truth  | \n"
			"[ 2 ]  moon  |  mission  |  was  |  a  |  lie ";
	assert( correct == Parser.getTestingTree( ) );

	string earth = "the earth is || isnt flat or round";
	QueryParser earthParser;
	earthParser.parse( earth );

	correct = " |  -OR-  | \n"
			"[ 1 ]  -AND-  |  -AND-  |  round  | \n"
			"[ 2 ]  the  |  earth  |  is  |  isnt  |  flat ";

	assert( correct == earthParser.getTestingTree( ) );

	cout <<"All OR and AND tests passed!\n";
	}


void testnestedOR()
	{
	cout << "Testing nestedOR with AND\n";
	string RB = "karan OR ( chris OR ( kareem or omaury ) ) ";
	QueryParser RBParser;
	RBParser.parse( RB );
	string correct = " |  -OR-  | \n"
			"[ 1 ]  karan  |  -OR-  | \n"
			"[ 2 ]  chris  |  -OR-  | \n"
			"[ 3 ]  kareem  |  omaury ";
	assert( correct == RBParser.getTestingTree( ) );

	string WR = "( DPJ or Tarik ) or (nico or oliver) or kekoa";
	QueryParser WRParser;
	WRParser.parse( WR );
	correct = " |  -OR-  | \n"
			"[ 1 ]  -OR-  |  -OR-  |  kekoa  | \n"
			"[ 2 ]  DPJ  |  Tarik  |  nico  |  oliver ";
	assert( correct == WRParser.getTestingTree( ));
	}
void testNestedORwithAND()
	{
	cout << "Testing nestedOR with AND\n";
	string nasa = "moon mission was a ( lie OR truth )";
	QueryParser Parser;
	Parser.parse( nasa );
	string correct = " |  -AND-  | \n"
			"[ 1 ]  moon  |  mission  |  was  |  a  |  -OR-  | \n"
			"[ 2 ]  lie  |  truth ";
	assert( correct == Parser.getTestingTree( ) );

	string earth = "the earth ( is || isnt)( flat or round )";
	QueryParser earthParser;
	earthParser.parse( earth );

	correct = " |  -AND-  | \n"
			"[ 1 ]  the  |  earth  |  -OR-  |  -OR-  | \n"
			"[ 2 ]  is  |  isnt  |  flat  |  round ";
	assert( correct == earthParser.getTestingTree( ) );

	cout <<"All nested OR and AND tests passed!\n";
	}

