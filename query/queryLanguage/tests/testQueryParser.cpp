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
void testNestedORwithAND();
void testDecoration();

int main()
	{
	cout << "Starting QueryLang tests...\n";
	testAND();
	testOR();
	testSimple ();
	testORwithAND ();
	testNestedORwithAND();
	testnestedOR();
	testDecoration ();
	cout << "PASSED ALL TESTS!\n";

	}

void testAND()
	{
	cout << "Testing AND...\n";

	string query = "Is Lebron james the goat";
	QueryParser lebronParser;
	lebronParser.toggleDecorator();
	lebronParser.parse( query );

	string correct = " |  -AND-  | \n"
			"[ 1 ]  I  |  Lebron  |  jame  |  the  |  goat ";

	assert(correct == lebronParser.getTestingTree( ));

	string dessertQuery = "I like cookies AND cake & pie && icecream and dessert";

	QueryParser dessertParser;
	dessertParser.toggleDecorator();
	dessertParser.parse( dessertQuery );

	string correctDesserts = " |  -AND-  | \n"
			"[ 1 ]  I  |  like  |  cooki  |  cake  |  pie  |  icecream  |  dessert ";

	assert(correctDesserts == dessertParser.getTestingTree( ));

	cout << "All AND tests passed!\n";

	}

void testOR()
	{
	cout << "Testing OR..\n";

	string query = "who or what OR when || where | why";

	QueryParser Parser;
	Parser.toggleDecorator();
	Parser.parse( query );

	string correct = " |  -OR-  | \n"
			"[ 1 ]  who  |  what  |  when  |  where  |  why ";

	assert(correct == Parser.getTestingTree( ));

	string simple = "left or right";

	QueryParser simpleParser;
	simpleParser.toggleDecorator();
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
	Parser.toggleDecorator();
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
	Parser.toggleDecorator();
	Parser.parse( nasa );

	string correct = " |  -OR-  | \n"
			"[ 1 ]  -AND-  |  truth  | \n"
			"[ 2 ]  moon  |  mission  |  wa  |  a  |  lie ";


	assert( correct == Parser.getTestingTree( ) );

	string earth = "the earth is || isnt flat or round";

	QueryParser earthParser;
	earthParser.toggleDecorator();
	earthParser.parse( earth );

	correct = " |  -OR-  | \n"
			"[ 1 ]  -AND-  |  -AND-  |  round  | \n"
			"[ 2 ]  the  |  earth  |  i  |  isnt  |  flat ";

	assert( correct == earthParser.getTestingTree( ) );

	cout <<"All OR and AND tests passed!\n";

	}


void testnestedOR()
	{
	cout << "Testing nestedOR with AND\n";

	string RB = "karan OR ( chris OR ( kareem or omaury ) ) ";

	QueryParser RBParser;
	RBParser.toggleDecorator();
	RBParser.parse( RB );

	string correct = " |  -OR-  | \n"
			"[ 1 ]  karan  |  -OR-  | \n"
			"[ 2 ]  chri  |  -OR-  | \n"
			"[ 3 ]  kareem  |  omauri ";

	assert( correct == RBParser.getTestingTree( ) );

	string WR = "( DPJ or Tarik ) or (nico or oliver) or kekoa";

	QueryParser WRParser;
	WRParser.toggleDecorator();
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
	Parser.toggleDecorator();
	Parser.parse( nasa );

	string correct = " |  -AND-  | \n"
			"[ 1 ]  moon  |  mission  |  wa  |  a  |  -OR-  | \n"
			"[ 2 ]  lie  |  truth ";

	assert( correct == Parser.getTestingTree( ) );

	string earth = "the earth ( is || isnt)( flat or round )";

	QueryParser earthParser;
	earthParser.toggleDecorator();
	earthParser.parse( earth );

	correct = " |  -AND-  | \n"
			"[ 1 ]  the  |  earth  |  -OR-  |  -OR-  | \n"
			"[ 2 ]  i  |  isnt  |  flat  |  round ";

	assert( correct == earthParser.getTestingTree( ) );

	cout <<"All nested OR and AND tests passed!\n";

	}

void testDecoration()
	{
	cout << "Testing decoration...\n";

	string earth = "the earth ( is || isnt)( flat or round )";
	QueryParser earthParser;
	earthParser.parse( earth );

	string correct = " |  -AND-  | \n"
			"[ 1 ]  -OR-  |  -OR-  |  -OR-  |  -OR-  | \n"
			"[ 2 ]  $the  |  #the  |  $earth  |  #earth  |  -OR-  |  -OR-  |  -OR-  |  -OR-  | \n"
			"[ 3 ]  $i  |  #i  |  $isnt  |  #isnt  |  $flat  |  #flat  |  $round  |  #round ";

	assert( correct == earthParser.getTestingTree( ) );

	string prevFailed = "brazil crime";
	QueryParser Brazil;
	Brazil.parse( prevFailed );

	correct = " |  -AND-  | \n"
			"[ 1 ]  -OR-  |  -OR-  | \n"
			"[ 2 ]  $brazil  |  #brazil  |  $crime  |  #crime ";

	assert( correct == Brazil.getTestingTree( ) );

	string reversed = "crime brazil";
	QueryParser Crime;
	Crime.parse( reversed );

	correct = " |  -AND-  | \n"
			"[ 1 ]  -OR-  |  -OR-  | \n"
			"[ 2 ]  $crime  |  #crime  |  $brazil  |  #brazil ";


	assert( correct == Crime.getTestingTree( ) );

	cout << "All nested decoration tests passed! \n";
	}
