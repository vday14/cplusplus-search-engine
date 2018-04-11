
#include "queryParser.h"

/**
 * Parser class just for Query
 *
 * @param query
 */
QueryParser::QueryParser ( std::string query )
	{ this->query = query; }

/**
 * Parser for query string
 *
 * @return tokenizer dict
 */
const unordered_map< string, vector< unsigned long > > *QueryParser::execute( )
	{
	Tokenizer tokenizer;
	tokenizer.execute( query, 0, '\0' );
	return tokenizer.get( );
	}




