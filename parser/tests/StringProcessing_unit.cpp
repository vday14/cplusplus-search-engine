//
// Created by Veronica Day on 2/13/18.
//

#include <string>
#include <vector>
#include "../../util/stringProcessing.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_findStr(string original);
void test_splitStr(string original);
void test_toLower();
void test_isStopWord();

int main()
	{

	cout << "Beginning testing for StringProcessing_unit" << endl << endl;

	string original = "It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. "
			"The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here',"
			"making it look like readable English. ";

	test_findStr(original);
	test_splitStr(original);
	test_toLower();
	test_isStopWord();

	cout << "\nTests passed for StringProcessing_unit :D" << endl;

	}

void test_findStr(string original)
	{
	cout << "Testing findStr..." << endl;

	string find = "established";
	auto word = findStr(original.begin(), find);
	assert(*word == 'e');

	find = "Lorem Ipsum";
	auto word2 = findStr (original.begin(), find);
	assert(*word2 == 'L');

	string title = "<title> This is a test </title>";
	find = "<title>";
	auto word3 = findStr (title.begin(), find);
	assert(*word3 == '<');
	auto titleIt = title.begin();
	while (word3 != title.end() && titleIt != title.end())
		{
		assert(*word3 == *titleIt);
		++word3;
		++titleIt;
		}

	find = "</title>";
	auto word4 = findStr (title.begin(), find);
	assert(*word4 == '<' && *(word4 + 1) == '/');

	auto word0 = findStr (original.begin(), find);
	assert(*word0 == '\0');

	find = "orange";
	auto word5 = findStr (original.begin(), find);
	assert(*word5 == '\0');

	find = "orange";
	string test = "apple";
	auto word7 = findStr (test.begin(), find);
	assert(*word7 == '\0');

	find = "bird";
	test = "bigbird";
	auto word6 = findStr (test.begin(), find);
	assert(*word6 == 'b' && *(word6 + 1) == 'i' && *(word6 + 2) == 'r');

	cout << "test_findStr passed" << endl;

	}


void test_splitStr(string original)
	{
	cout << "Testing splitStr..." << endl;

	vector<string> vec = splitStr (original, ' ');
	assert(vec.size() == 53);

	string word = "hello\ngoodbye";
	vec = splitStr (word, '\n');
	assert(vec.size() == 2);
	assert(vec[0] == "hello" && vec[1] == "goodbye");

	cout << "test_splitStr passed" << endl;

	}




void test_toLower()
	{
	cout << "Testing toLower..." << endl;

	string word = "HELLO";
	string word2 = "hello";
	string word3 = "Hello GoodBye !";
	string word4 = "";
	string word5 = " ";

	string test = toLower (word);
	string test2 = toLower (word2);
	string test3 = toLower (word3);
	string test4 = toLower (word4);
	string test5 = toLower (word5);

	assert (test == "hello");
	cout << test2 << endl;
	assert (test2 == "hello");
	assert (test3 == "hello goodbye !");
	assert (test4 == "");
	assert (test5 == " ");

	cout << "test_toLower passed" << endl;
	}



void test_isStopWord()
	{
	cout << "Testing isStopWord..." << endl;

	string is = "is";
	string hello = "Hello";
	string none = "none";
	string blank = "";
	string blank2 = " ";

	assert (isStopWord (is));
	assert (!isStopWord (hello));
	assert (isStopWord (none));
	assert (!isStopWord (blank));
	assert (!isStopWord (blank2));

	cout << "test_isStopWord passed" << endl;

	}