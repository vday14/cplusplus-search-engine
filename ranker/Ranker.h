
#ifndef EECS398_SEARCH_RANKER_H
#define EECS398_SEARCH_RANKER_H



/***
 * Ranker will work by doing these things:
 * 1. Goes through all of the ISRWords in the vector and creates Sites for the new ones and adds information
 * 	- If the Site already exists then just add the Site and attributes
 * 	- Store the frequency of the word in the document
 * 2. Go through the vector of Sites and score each, then push onto the priority queue as you score them
 *
 */
#include <queue>
#include "../constraintSolver/ISRWord.h"
#include "Site.h"
#include "Scorer.h"
#include <unordered_map>
#include "../query/Query.h"
#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"

/***
 * Custom Comparator for the priority queue that keeps the websites in their correct order.
 */
class Comp
	{
public:
	bool operator()(Site* L, Site* R)
		{
		return L->score > R->score;
		}
	};

class Ranker : public ThreadClass
	{
public:

	size_t numberOfTotalResults = 0;

	Ranker( );

	void addQuery( std::string query_in );
	/**
	 * Ranker cstor
	 *
	 * @param query_in
	 */
	Ranker( std::string query_in   );



	Ranker( ProducerConsumerQueue< pair<Location, Location> > * MatchQueueIn );
	/**
	 * Ranker dstor
	 */
	~Ranker( );

	/**
	 * Adds a new site for the doc given as beginning and end of document
	 *
	 * @param
	 */
	void addDoc( Location beggingOfDocument, Location EndOfDoc );

	/**
	 * Outputs the ranked sites to stout
	 *
	 */
	void printRankedSites();

	string getResultsForSiteJSON( );

	void addISR( vector<ISRWord * > isr_in );

	void orderResults( );


	void run();

	/**
	 * Returns the query
	 *
	 * @return Query
	 */
	Query getQuery( );

private:

	const unsigned long DOCS_TO_RETURN = 10;

	/**
	 * A min heap to store a running list of the least most valuable sites
	 */
	priority_queue< Site * , vector< Site* > , Comp > runningRankedQueue;
	vector< Site* > sortedDocs;
	vector<ISRWord* > isrListInput;
	Query query;
	unordered_map<string, Site * > Websites;
	ProducerConsumerQueue< pair<Location, Location> > * MatchQueue  ;
	/**
	 * Sets the data for each word
	 *
	 * @param isrWord
	 * @return data
	 */
	data getData( ISRWord isrWord );

	/**
	 * Scores the document and only adds it to the returned list if it's score is greater than the smallest score
	 *
	 * @param doc
	 */
	void selectivelyAddDocs( Site * doc);


	};


#endif //EECS398_SEARCH_RANKER_H

