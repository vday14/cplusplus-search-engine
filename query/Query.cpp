
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
	{
	QueryParser parser( query_in );
	this->queryTokens	= parser.execute( );
	}

/**
 * Fetches the query's tokens
 * @return queryTokens
 */
const std::unordered_map< std::string, std::vector< unsigned long > > *Query::getQueryTokens ( )
	{
	return this->queryTokens;
	}

/**
 * Query dstor will destroy the query tokens
 *
 */
Query::~Query ( )
	{
	delete this->queryTokens;
	queryTokens = nullptr;
	}


