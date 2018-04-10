
#ifndef EECS398_SEARCH_RANKER_H
#define EECS398_SEARCH_RANKER_H


#include <queue>
#include "../constraintSolver/ISRWord.h"
#include "Site.h"
#include "Scorer.h"
#include <unordered_map>

/***
 * Custom Comparator for the priority queue that keeps the websites in their correct order.
 */
class Comp
	{
public:
	bool operator()(Site* L, Site* R)
		{
		return L->getScore() < R->getScore();
		}
	};

class Ranker
	{
public:

	Ranker(){};

	Ranker( vector< ISRWord > isrListInput ){
		init( isrListInput );
		};

	~Ranker( );

	void generateSiteList();
	void printSites();
	void printRankedSites();
	void rank();

private:

	void init( vector< ISRWord> query );

	//Queue to continuously sort the sites
	priority_queue< Site * , vector< Site* > , Comp > WebsiteQueue;
	vector< ISRWord > ISRList;

	//TODO: Not sure if we will need these
	vector< string > urls;

	unordered_map<string, Site * > Websites;
	unordered_map< string , vector< unsigned long > > queryOffsets;
	void addWordtoSites( ISRWord isrWord);

	data getData( ISRWord isrWord );


	/***
	 * Ranker will work by doing these things:
	 * 1. Goes through all of the ISRWords in the vector and creates Sites for the new ones and adds information
	 * 	- If the Site already exists then just add the Site and attributes
	 * 	- Store the frequency of the word in the document
	 * 2. Go through the vector of Sites and score each, then push onto the priority queue as you score them
	 *
	 */

	};


#endif //EECS398_SEARCH_RANKER_H

