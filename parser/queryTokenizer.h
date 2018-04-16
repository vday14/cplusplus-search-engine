
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

	/**
	 * Parser for query string that returns dictionary in index format
	 * @return
	 */
	const unordered_map< string, vector< unsigned long > > *executeQueryOffsets (  );

	/**
	 * Sends query to tokenizer
	 * @param tokenizer
	 */
	void parseQuery (  Tokenizer *tokenizer );

private:
	std::string query;

	};


