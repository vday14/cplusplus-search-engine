
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

	/**
	 * Ranker cstor
	 *
	 * @param query_in
	 */
	Ranker( std::string query_in );

	/**
	 * Ranker dstor
	 */
	~Ranker( );

	/**
	 * Adds a new site for the doc given as isrListInput
	 *
	 * @param isrListInput
	 */
	void addDoc( vector<ISRWord> isrListInput );

	/**
	 * Outputs the ranked sites to stout
	 *
	 */
	void printRankedSites();

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

	Query query;
	vector< Site* > sortedDocs;
	unordered_map<string, Site * > Websites;

	/**
	 * Sets the data for each word
	 *
	 * @param isrWord
	 * @return data
	 */
	data getData( ISRWord isrWord );

	/**
	 * Gets the frequency of a certain word
	 *
	 * @param isrWord
	 * @return
	 */
	unsigned long getFrequency ( ISRWord* isrWord );

	/**
	 * Returns the offsets of the word
	 *
	 * @return
	 */
	std::vector < size_t > getOffsets( ISRWord* isrWord );

	/**
	 * Scores the document and only adds it to the returned list if it's score is greater than the smallest score
	 *
	 * @param doc
	 */
	void selectivelyAddDocs( Site * doc);


	};


#endif //EECS398_SEARCH_RANKER_H

