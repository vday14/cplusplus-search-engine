
#pragma once
#include <string>
#include <vector>
#include "../util/stringProcessing.h"
#include "../util/Tokenizer.h"

class QueryTokenizer
	{
public:

	/**
	 * Parser class just for Query
	 *
	 * @param query
	 */
	QueryTokenizer ( std::string query );


	/**
	 * Parser for query string
	 *
	 * @return tokenizer dict
	 */
	std::vector < std::string > execute( );

private:
	std::string query;

	};


