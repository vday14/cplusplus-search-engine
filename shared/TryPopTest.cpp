//
// Created by Ben Bergkamp on 4/5/18.
//

#include "ProducerConsumerQueue.h"
#include "../crawler/UrlFrontier.h"
#include <iostream>

using namespace std;

int main()
	{
	ProducerConsumerQueue< int > queue;

	queue.Push(2);

	int x;

	bool ret;

	cout << "-----Testing Producer Consumer Queue-----\n";
	cout << "Expecting: 1, 2, 0\n";


	ret = queue.try_pop(x);

	cout << "success: " << ret << endl;
	cout << "val: " << x << endl;

	ret = queue.try_pop(x);

	cout << "success: " << ret << endl;

	cout << "-----Now Testing Url Frontier-----\n";
	cout << "Expecting: 1, http://www.espn.com, 0\n";

	UrlFrontier fr;

	ParsedUrl ps("http://www.espn.com");
	ParsedUrl result;

	fr.Push(ps);

	ret = fr.try_pop(result);

	cout << "success: " << ret << endl;
	cout << "val: " << result.getCompleteUrl() << endl;

	ret = queue.try_pop(x);
	cout << "success: " << ret << endl;



	}