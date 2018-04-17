
#include "Site.h"
#include "Scorer.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * Site cstor
 */
Site::Site ( std::string url_in, Query query_in, std::string title_in )
		: url ( url_in ), query ( query_in ), title( title_in), score ( 0 ), hasBeenScored ( false ), STAT_WEIGHT( 1.0 ), PROX_WEIGHT( 1.0 ), LOC_WEIGHT( 1.0 )
	{ }

Site::Site( std::string url_in, Query query_in, std::string title_in, double stat_in, double prox_in, double loc_in)
		: url ( url_in ), query ( query_in ), title( title_in), score ( 0 ), hasBeenScored ( false ), STAT_WEIGHT( stat_in ), PROX_WEIGHT( prox_in ), LOC_WEIGHT( loc_in )
	{};

/**
 * Site dstor
 */
Site::~Site( )
	{ }

/**
 * Sets the Site's score
 *
 * @param score_in
 */
void Site::setScore( double score_in )
	{
	this->score = score_in;
	}

/***
 * Returns the score of some site. Either grabs the value if its been scored previously, or generates a new score using
 * a scorer object.
 * @return
 */
double Site::getScore ( )
	{
	


	if( this->hasBeenScored )
		{
		return this->score;
		}

	hasBeenScored = true;
	Scorer rank = Scorer(STAT_WEIGHT, PROX_WEIGHT, LOC_WEIGHT);
	score = rank.getScore (*this);


	return score;


	}

/**
 * Returns the Site's url
 *
 * @return
 */
std::string Site::getUrl( )
	{
	return this->url;
	}



/**
 * Returns the Site's title
 *
 * @return
 */
std::string Site::getTitle( )
	{
	return this->title;
	}

/**
 * Returns the query
 *
 * @return
 */
Query Site::getQuery( )
	{
	return this->query;
	}

/**
	 * Returns the static score of some site
	 *
	 * @return
	 */
double Site::getStaticScore ( )
	{
	Scorer scoreFactory;
	return scoreFactory.staticScore( *this );
	}

/**
	 * Returns the phrase matching score of some site
	 *
	 * @return
	 */
double Site::getPhraseScore ( )
	{
	Scorer scoreFactory;
	return scoreFactory.proximityMatch( *this );
	}

/**
	 * Returns the word location score of some site
	 *
	 * @return
	 */
double Site::getLocationScore ( )
	{
	Scorer scoreFactory;
	return scoreFactory.wordLocationScore( *this );
	}