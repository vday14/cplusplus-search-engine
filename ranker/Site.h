/***
 * Class to represent each website in the ranking engine
 */
#ifndef EECS398_SEARCH_SITE_H
#define EECS398_SEARCH_SITE_H

#include <string>
#include <unordered_map>
#include "../query/Query.h"
#include "../shared/url.h"

/**
 * Data struct for each word
 */
struct data
	{
	unsigned long frequency;
	//TODO add offsets for proximity match
	};

class Site
	{

private:

	ParsedUrl url;
//	Query query;
	std::string query;
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
	Site ( );

	/**
	 * Site dstor
	 */
	~Site( );

	/**
	 * Sets Site's url
	 *
	 * @param url_in
	 */
	void setUrl( ParsedUrl url );

	/**
	 * Sets the Site's score
	 *
	 * @param score_in
	 */
	void setScore( double score_in );

	/**
	 * Sets the Site's query
	 *
	 * @param query_in
	 */
//	void setQuery( Query query_in );
	void setQuery( std::string query_in );


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
	ParsedUrl getUrl( );

	/**
	 * Returns the Site's url
	 *
	 * @return
	 */
//	Query getQuery( );
	std::string getQuery( );

	};
#endif //EECS398_SEARCH_SITE_H
