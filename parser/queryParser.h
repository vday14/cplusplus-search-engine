
#ifndef EECS398_SEARCH_QUERYPARSER_H
#define EECS398_SEARCH_QUERYPARSER_H

#include <string>
#include <vector>
#include "../util/stringProcessing.h"
#include "../util/Tokenizer.h"

class QueryParser
	{
public:

	/**
	 * Parser class just for Query
	 *
	 * @param query
	 */
	QueryParser ( std::string query );


	/**
	 * Parser for query string
	 *
	 * @return tokenizer dict
	 */
	std::vector < std::string > execute( );

private:
	std::string query;

	};


#endif //EECS398_SEARCH_QUERYPARSER_H
