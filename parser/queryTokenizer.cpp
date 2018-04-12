
#include "queryTokenizer.h"

/**
 * Parser class just for Query
 *
 * @param query
 */
QueryTokenizer::QueryTokenizer ( std::string query )
	{ this->query = query; }

/**
 * Parser for query string
 *
 * @return tokenizer dict
 */
std::vector< std::string > QueryTokenizer::execute( )
	{
	std::vector< std::string > tokens = splitStr( query, ' ', true );
	std::vector< std::string > processedQuery;

	for ( int i = 0; i < tokens.size( ); ++i )
		{
		if ( !isStopWord( tokens[ i ] ) )
			{
			processedQuery.push_back( stemWord( toLower( tokens[ i ] ) ) );
			}
		}
	return processedQuery;
	}




