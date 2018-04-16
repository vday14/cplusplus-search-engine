
#ifndef EECS398_SEARCH_QUERY_H
#define EECS398_SEARCH_QUERY_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../parser/queryTokenizer.h"

/**
 * custom comparator to sort the query tokens by value
 */
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
	std::vector< std::string > getQueryTokens ( );

	/**
	 * Returns query string
	 * @return
	 */
	std::string getQueryString( );

	/**
	 * Returns the Query decorated with Anchor '@'
	 * @return
	 */
	std::vector< std::string > getQueryAnchor ( );

	/**
	 * Returns the Query decorated with Url '$'
	 * @return
	 */
	std::vector< std::string > getQueryUrl ( );

	/**
	 * Returns the Query decorated with Title '#'
	 * @return
	 */
	std::vector< std::string > getQueryTitle ( );

	/**
	 * Returns the Query decorated with Body '%'
	 * @return
	 */
	std::vector< std::string > getQueryBody ( );

	/**
	 * Query dstor will destroy the query tokens
	 *
	 */
	~Query ( );

private:

	/**
	 * Query tokens
	 */
	 std::vector< std::string > queryTokens;

    /**
    * Query tokens + '@'
    */
    std::vector< std::string > queryTokensAnchor;

    /**
     * Query tokens + '$'
     */
    std::vector< std::string > queryTokensUrl;

    /**
     * Query tokens + '#'
     */
    std::vector< std::string > queryTokensTitle;

    /**
     * Query tokens + '%'
     */
    std::vector< std::string > queryTokensBody;

	std::string queryStr;

	};


#endif //EECS398_SEARCH_QUERY_H
