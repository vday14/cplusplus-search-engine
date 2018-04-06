//
// Created by nick on 3/22/18.
//

#include <iostream>
#include <cassert>
#include <string>
#include "Vector.h"

void testPushBack( );
void testResize( );
void testReserve( );
void testIterator( );
void testStruct( );
void testPointers( );

int main( )
    {
    std::cout << "Beginning Array tests... \n";
    testPushBack( );
    testReserve( );
    testResize( );
    testIterator( );
    testStruct( );
    testPointers( );   /*Fails this test*/

    //Nicks testing below
    Vector<int> test1;
    test1.reserve(20);
    Vector<int> test62;
    test62.reserve(20);
    test1[51] = 52;
    test62[51] = 352;
    test1.push_back(50);
    assert(test1[0] == 50);
    assert(test1.size() == 1);
    test1[0] = 150;
    assert(test1[0] == 150);
    assert(test1.size() == 1);

    std::cout << "Array tests successful! :)";
    }

void testPushBack( )
    {
    std::cout << "Testing pushback ... \n";
    Vector< int > Arr;
    assert( Arr.size( ) == 0);
    Arr.push_back(1);
    assert( Arr[ 0 ] == 1);
    assert( Arr.size( ) == 1);
    Arr.push_back(4);
    assert( Arr[ 1 ] == 4);
    assert( Arr.size( ) == 2);

    Arr.push_back(3);
    assert( Arr[ 2 ] == 3);
    assert( Arr.size( ) == 3);

    Arr.push_back(2);
    assert( Arr[ 0 ] == 1);
    assert( Arr[ 1 ] == 4);
    assert( Arr[ 2 ] == 3);
    assert( Arr[ 3 ] == 2);
    assert( Arr.size( ) == 4);

    Vector< std::string > StringArr;
    StringArr.push_back("one");
    assert( StringArr[ 0 ] == "one");
    assert( StringArr.size( ) == 1);

    StringArr.push_back("four");
    assert( StringArr[ 1 ] == "four");
    assert( StringArr.size( ) == 2);

    StringArr.push_back("three");
    assert( StringArr[ 2 ] == "three");
    assert( StringArr.size( ) == 3);

    StringArr.push_back("two");
    assert( StringArr[ 0 ] == "one");
    assert( StringArr[ 1 ] == "four");
    assert( StringArr[ 2 ] == "three");
    assert( StringArr[ 3 ] == "two");
    assert( StringArr.size( ) == 4);
    }

void testReserve( )
    {
    std::cout << "Testing Reserve ... \n";
    Vector< int > testArr;
    testArr.reserve( 5 );
    assert( testArr.size( ) == 0 );
    testArr.push_back( 7 );
    assert( testArr[ 0 ] == 7);
    assert( testArr.size( ) == 1);
    testArr.reserve( 6 );
    assert( testArr[ 0 ] == 7);
    //TODO add more shit to this, probabaly with size_of( )
    }

void testResize( )
    {
    std::cout << "Testing Resize ... \n";
    Vector< int > testArr;
    testArr.resize( 5 );
    assert( testArr.size( ) == 5 );
    assert( testArr[ 3 ] == 0 );
    testArr[ 3 ] = 42;
    assert( testArr[ 3 ] == 42 );
    testArr.resize( 10 );
    assert( testArr[ 3 ] == 42);
    testArr.push_back( 3 );
    assert( testArr[ 10 ] == 3);
    }

void testIterator( )
    {
    std::cout<<"Testing Iterator...\n";

    Vector< int > Arr;
    Arr.push_back( 5 );

    Vector< int >::Iterator iter = Arr.begin( );
    assert( *iter == 5 );
    Arr.push_back( 6 );
    ++iter;
    assert( *iter == 6 );
    --iter;
    assert( *iter == 5);
    assert( iter != Arr.end( ) );
    ++++iter;
    assert( iter == Arr.end( ) );
    }

void testStruct( )
    {
    std::cout << "Testing Struct...\n";
    struct Node
       {
       Node *next;
       int val;
       };
    Node example;
    example.val = 7;
    Vector< Node > container;
    container.push_back(example);
    assert(container[ 0 ].val == 7);
    Node example2;
    example2.val = 99;
    container.resize( 5 );
    container[ 3 ] = example2;
    assert( container[ 3 ].val == 99);
    assert( container[ 0 ].val == 7);
    assert( container[ 2 ].val == 0);
    struct WordCount
       {
       std::string word;
       int freq;
       };

    Vector< WordCount > history;

    }

void testPointers( )
    {
    std::cout << "Testing Pointers...\n";
    struct Node {
       Node *next;
       int val;
       };
    Vector< Node* > ptrArr;
    ptrArr.resize( 20 );
    ptrArr[ 9 ] = new Node( );
    ptrArr[ 9 ]->val = 9;
    assert( ptrArr[ 9 ]->val == 9);
    }

