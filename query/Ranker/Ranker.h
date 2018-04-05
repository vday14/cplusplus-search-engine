//
// Created by Zane Dunnings on 4/2/18.
//


#ifndef EECS398_SEARCH_RANKER_H
#define EECS398_SEARCH_RANKER_H


#include <queue>
#include "../../constraintSolver/ISRWord.h"
#include "Site.h"

/***
 * Custom Comparator for the priority queue that keeps the websites in their correct order.
 */
class Comp
	{
public:
	bool operator()(Site L, Site R)
		{
		return L.getScore() > R.getScore();
		}
	};

class Ranker
	{
public:

	Ranker(){};

	Ranker( vector< ISRWord > query ){
		init( query );
		};
	vector< string > rank();
private:

	void init( vector< ISRWord> query );

	//Queue to continuously sort the sites
	priority_queue< Site, vector< Site> , Comp > WebsiteQueue;
	vector< ISRWord > inputQuery;

	//TODO: Not sure if we will need these
	vector< string > urls;
	vector< Site > Websites;


	};


#endif //EECS398_SEARCH_RANKER_H

