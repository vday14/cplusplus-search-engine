/***
 * Class to represent each website in the ranking engine
 */
#ifndef EECS398_SEARCH_SITE_H
#define EECS398_SEARCH_SITE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../query/Query.h"
#include "../shared/url.h"

/**
 * Data struct for each word
 */
struct data
	{
	unsigned long frequency;
	std::vector< size_t > offsets;
	long minDelta;
	};

class Site
	{

private:

	std::string url;
	Query query;
	double score;
	bool hasBeenScored;

public:
	/**
	 * Maps words to their respective data structs
	 */
	std::unordered_map< std::string, data> wordData;

	/**
	 * Site cstor
	 */
	Site ( std::string url_in, Query query_in );

	/**
	 * Site dstor
	 */
	~Site( );

	/**
	 * Sets the Site's score
	 *
	 * @param score_in
	 */
	void setScore( double score_in );

	/**
	 * Returns the score of some site. Either grabs the value if its been scored previously, or generates a new score using
	 * a scorer object.
	 *
	 * @return
	 */
	double getScore( );

	/**
	 * Returns the Site's url
	 *
	 * @return
	 */
	std::string getUrl( );

	/**
	 * Returns the Site's url
	 *
	 * @return
	 */
	Query getQuery( );

	};
#endif //EECS398_SEARCH_SITE_H
