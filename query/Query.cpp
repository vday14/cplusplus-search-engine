
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

/**
 * Returns the Query decorated with Anchor '@'
 * @return
 */
std::vector< std::string > Query::getQueryAnchor ( )
	{
	std::vector< std::string > tempQueryTokens;
	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		tempQueryTokens.push_back( Tokenizer::ANCHOR + this->queryTokens[ i ] );
		}
	return tempQueryTokens;
	}

/**
 * Returns the Query decorated with Url '$'
 * @return
 */
std::vector< std::string > Query::getQueryUrl ( )
	{
	std::vector< std::string > tempQueryTokens;
	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		tempQueryTokens.push_back( Tokenizer::URL + this->queryTokens[ i ] );
		}
	return tempQueryTokens;
	}
/**
 * Returns the Query decorated with Title '#'
 * @return
 */
std::vector< std::string > Query::getQueryTitle ( )
	{
	std::vector< std::string > tempQueryTokens;
	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		tempQueryTokens.push_back( Tokenizer::TITLE + this->queryTokens[ i ] );
		}
	return tempQueryTokens;
	}

/**
 * Returns the Query decorated with Body '%'
 * @return
 */
std::vector< std::string > Query::getQueryBody ( )
	{
	std::vector< std::string > tempQueryTokens;
	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		tempQueryTokens.push_back( Tokenizer::BODY + this->queryTokens[ i ] );
		}
	return tempQueryTokens;
	}

/**
 * Query dstor will destroy the query tokens
 *
 */
Query::~Query ( )
	{ }


