//
// Created by nick on 3/23/18.
//

#include <iostream>
#include <cassert>
#include <string>
#include "HashTable.h"

using namespace std;

void testInsert();
void testRehash();
void testCollisions();

int main( )
    {
    cout << "Begin testHashTable:" << endl << endl;

    testInsert();
    testRehash();
    testCollisions();

    //Nicks tests
    HashTable<string, string> ht;

    ht["hello"] = "goodbye";
    assert(ht["hello"] == "goodbye");
    ht["i want you to feel"] = "surreal";
    assert(ht["i want you to feel"] == "surreal");

    cout << endl <<  "ALL TESTS PASSED :)" << endl;
    }

void testInsert( )
    {
    cout << "Testing testInsert..." << endl;
    HashTable < string, int > lib;
    lib["Four"] = 4;
    lib[ "Hundred" ] = 100;
    lib[ "Twenty" ] = 20;

    assert( lib[ "Four" ] == 4);
    assert( lib[ "Hundred"] == 100 );
    assert( lib[ "twenty" ] != 20 );
    assert( lib[ "Twenty" ] == 20 );

    HashTable < string, string> string_string;
    string_string["donald trump"] = "lol";
    assert( string_string.size( ) == 1 );
    string_string["kendrick"] = "lamar";
    assert( string_string.size( ) == 2 );
    string_string["iphone"] = "apple";
    assert( string_string.size( ) == 3 );
    string_string["iphone1"] = "apple";
    assert( string_string.size( ) == 4 );
    string_string["iphone2"] = "apple";
    assert( string_string.size( ) == 5 );
    string_string["iphone3"] = "apple";
    assert( string_string.size( ) == 6 );
    string_string["iphone4"] = "apple";
    assert( string_string.size( ) == 7 );
    string_string["iphone5"] = "apple";
    assert( string_string.size( ) == 8 );
    string_string["iphone6"] = "apple";
    assert( string_string.size( ) == 9 );
    string_string["iphone7"] = "apple";
    assert( string_string.size( ) == 10 );
    string_string[ "YUGE" ];
    assert( string_string["YUGE"].empty( ) );
    assert( string_string["kendrick"] == "lamar" );
    cout << "testInsert Passed!" << endl;
    }

void testRehash()
    {
    cout << "Testing testRehash..." << endl;
    HashTable < string, int > lib;

    //Pushback enough items so it hits 50% load factor, and must rehash
    lib[ "one" ] = 1;
    lib[ "two" ] = 2;
    lib[ "three" ] = 3;
    lib[ "four" ] = 4;
    lib[ "five" ] = 5;
    lib[ "six" ] = 6;
    lib[ "seven" ] = 7;
    lib[ "eight" ] = 8;
    lib[ "nine" ] = 9;
    lib[ "ten" ] = 10;

    assert( lib.capacity( ) == 32);
    assert( lib.size( ) == 10);

    //Ensure that it rehashes to correct value
    assert( lib[ "one" ] == 1 );
    assert( lib[ "two" ] == 2 );
    assert( lib[ "three" ] == 3 );
    assert( lib[ "four" ] == 4 );
    assert( lib[ "five" ] == 5 );
    assert( lib[ "six" ] == 6 );
    assert( lib[ "seven" ] == 7 );
    assert( lib[ "eight" ] == 8 );
    assert( lib[ "nine" ] == 9 );
    assert( lib[ "ten" ] == 10 );
    lib[ "eleven" ] = 11;
    assert( lib[ "eleven" ] == 11 );
    assert( lib.capacity( ) == 32 );
    assert( lib.size( ) == 11 );
    cout << "testRehash Passed!" << endl;
    }

void testCollisions( )
    {
    cout << "Testing testCollisions..." << endl;
    HashTable < string, int > lib;
    lib["Four"] = 4;
    lib[ "Hundred" ] = 100;
    lib[ "Twenty" ] = 20;
    lib[ "one" ] = 1;
    lib[ "two" ] = 2;
    lib[ "three" ] = 3;
    lib[ "four" ] = 4;
    lib[ "five" ] = 5;
    lib[ "six" ] = 6;
    lib[ "seven" ] = 7;
    lib[ "eight" ] = 8;
    lib[ "nine" ] = 9;
    lib[ "ten" ] = 10;
    //assert(lib.getNumCollisions() == 5);
    //assert(lib.getMaxCollisions() == 2);
    //assert(lib.getNumBuckets() == 8);

    cout << "testCollisions Passed!" << endl;
    }
