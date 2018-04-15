
#include "Query.h"

/**
 * Query cstor
 */
Query::Query( )
	{ }

/**
 * Query cstor
 *
 * @param query_in
 */
Query::Query( std::string query_in )
	: queryStr( query_in )
	{
	QueryTokenizer parser( query_in );
	this->queryTokens	= parser.execute( );
	}

/**
 * Query Copy cstor
 *
 * @param copy
 */
Query::Query( const Query &copy )
	{
	this->queryTokens	= copy.queryTokens;
	}

/**
 * Fetches the query's tokens
 * @return queryTokens
 */
std::vector< std::string > Query::getQueryTokens ( )
	{
	return this->queryTokens;
	}

std::string Query::getQueryString( )
	{
	return queryStr;
	}

/**
 * Query dstor will destroy the query tokens
 *
 */
Query::~Query ( )
	{ }


