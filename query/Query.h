
#ifndef EECS398_SEARCH_QUERY_H
#define EECS398_SEARCH_QUERY_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../parser/queryParser.h"

class Query
	{

public:

	/**
	 * Query cstor
	 *
	 */
	Query( );

	/**
	 * Query cstor
	 *
	 * @param query_in
	 */
	Query( std::string query_in );

	/**
	 * Query Copy cstor
	 *
	 * @param copy
	 */
	Query( const Query &copy );

	/**
	 * Fetches the query's tokens
	 * @return queryTokens
	 */
	const std::unordered_map< std::string, std::vector< unsigned long > > *getQueryTokens ( );

	/**
	 * Query dstor will destroy the query tokens
	 *
	 */
	~Query ( );

private:
	/**
	 * Query tokens
	 */
	const std::unordered_map< std::string, std::vector< unsigned long > > *queryTokens;

	std::string queryStr;

	};


#endif //EECS398_SEARCH_QUERY_H
