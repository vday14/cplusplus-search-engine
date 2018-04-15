
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
std::vector< std::string > QueryParser::execute( )
	{
	std::vector< std::string > tokens = splitStr( query, ' ', true );
	std::vector< std::string > processedQuery;

	for ( int i = 0; i < tokens.size( ); ++i )
		{
		if ( !isStopWord( tokens[ i ] ) )
			{
			processedQuery.push_back( stemWord( tokens[ i ] ) );
			}
		}
	return processedQuery;
	}


/**
 * Parser for query string that returns dictionary in index format
 * @return
 */
const unordered_map< string, vector< unsigned long > > * QueryParser::executeQueryOffsets (  )
    {
    Tokenizer tokenizer;
    parseQuery( &tokenizer );
    return tokenizer.get( );
    }
/**
	 * Sends query to tokenizer
	 * @param tokenizer
	 */
void QueryParser::parseQuery (  Tokenizer *tokenizer )
    {
    tokenizer->execute( query, 0, '\0' );
    }






