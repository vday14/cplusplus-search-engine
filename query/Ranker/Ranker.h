//
// Created by Zane Dunnings on 4/2/18.
//


#ifndef EECS398_SEARCH_RANKER_H
#define EECS398_SEARCH_RANKER_H


#include <queue>
#include "../../constraintSolver/ISRWord.h"
#include "Site.h"
#include <unordered_map>

/***
 * Custom Comparator for the priority queue that keeps the websites in their correct order.
 */
class Comp
	{
public:
	bool operator()(Site* L, Site* R)
		{
		return L->getScore() > R->getScore();
		}
	};

class Ranker
	{
public:

	Ranker()
	{

		};


	~Ranker( );

	void addDoc( Location beggingOfDoc , Location EndDoc);
	void printRankedSites();
	string getResultsForSite( );
	void orderResults( );
	void addISR( vector<ISRWord*> isr_in );
	double numberOfTotalResults;

private:

	void init( vector< ISRWord> query );
	data getData( ISRWord * isrWord );
	void selectivelyAddDocs( Site * doc);



	//A min heap to store a running list of the least most valuable sites
	priority_queue< Site * , vector< Site* > , Comp > runningRankedQueue;
	vector< Site* > sortedDocs;
	vector<ISRWord*> isrListInput;
	unordered_map<string, Site * > Websites;
	unordered_map< string , vector< unsigned long > > queryOffsets;


	const int DOCS_TO_RETURN = 10;




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

