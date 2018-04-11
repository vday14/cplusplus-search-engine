
#include "Site.h"
#include "Scorer.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * Site cstor
 */
Site::Site ( )
	{ }

/**
 * Site dstor
 */
Site::~Site( )
	{ }

/**
 * Sets Site's url
 *
 * @param url_in
 */
void Site::setUrl( ParsedUrl url_in )
	{
	this->url = url_in;
	}

/**
 * Sets the Site's score
 *
 * @param score_in
 */
void Site::setScore( double score_in )
	{
	this->score = score_in;
	}

/**
 * Sets the Site's query
 *
 * @param query_in
 */
//void Site::setQuery( Query query_in )
//	{
//	this->query = query_in;
//	}
void Site::setQuery ( std::string query_in )
	{
	this->query = query_in;
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
	Scorer rank = Scorer();
	score = rank.getScore (*this);
	return score;
	}

/**
 * Returns the Site's url
 *
 * @return
 */
ParsedUrl Site::getUrl( )
	{
	return this->url;
	}

/**
 * Returns the query
 *
 * @return
 */
//Query Site::getQuery( )
//	{
//	return this->query;
//	}
std::string Site::getQuery( )
	{
	return this->query;
	}
