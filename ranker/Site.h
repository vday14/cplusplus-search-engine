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

	data( ) : frequency( 0 ), minDelta( 0 )
		{ }

	data( const data &copy ) : frequency( copy.frequency ), offsets( copy.offsets ), minDelta( copy.minDelta )
		{ }

	unsigned long frequency;
	std::vector< size_t > offsets;
	size_t docFrequency;
	int minDelta;
	};

class Site
	{

private:

	std::string url;
	std::string title;
	Query query;
	double score;
	bool hasBeenScored;

public:

	bool hasAnchor;
	bool hasUrl;
	bool hasTitle;
	bool hasBody;

	Site( Site &copy ) : url(copy.url), title(copy.title), query(copy.query), score(copy.score), hasBeenScored(copy.hasBeenScored), hasAnchor(copy.hasAnchor), hasUrl(copy.hasUrl), hasTitle(copy.hasTitle), hasBody(copy.hasBody)
		{
		this->wordData.clear( );
		for ( auto it = copy.wordData.begin( ); it != copy.wordData.end( ); ++it )
			{
			this->wordData[ it->first ] = it->second;
			}
		}

	/**
	 * Maps words to their respective data structs
	 */
	std::unordered_map< std::string, data > wordData;

	/**
	 * Site cstor
	 */
	Site ( std::string url_in, Query query_in , std::string title);

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
	std::string getTitle( );

	/**
	 * Returns the Site's title
	 *
	 * @return
	 */

	Query getQuery( );

	};
#endif //EECS398_SEARCH_SITE_H
