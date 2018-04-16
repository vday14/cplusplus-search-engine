
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
	if ( !this->queryTokensAnchor.empty( ) )
		return this->queryTokensAnchor;

	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		this->queryTokensAnchor.push_back( Tokenizer::ANCHOR + this->queryTokens[ i ] );
		}
	return this->queryTokensAnchor;
	}

/**
 * Returns the Query decorated with Url '$'
 * @return
 */
std::vector< std::string > Query::getQueryUrl ( )
	{
	if ( !this->queryTokensUrl.empty( ) )
		return this->queryTokensUrl;

	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		this->queryTokensUrl.push_back( Tokenizer::URL + this->queryTokens[ i ] );
		}
	return this->queryTokensUrl;
	}
/**
 * Returns the Query decorated with Title '#'
 * @return
 */
std::vector< std::string > Query::getQueryTitle ( )
	{
	if ( !this->queryTokensTitle.empty( ) )
		return this->queryTokensTitle;

	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		this->queryTokensTitle.push_back( Tokenizer::TITLE + this->queryTokens[ i ] );
		}
	return this->queryTokensTitle;
	}

/**
 * Returns the Query decorated with Body '%'
 * @return
 */
std::vector< std::string > Query::getQueryBody ( )
	{
	if ( !this->queryTokensBody.empty( ) )
		return this->queryTokensBody;

	for ( int i = 0; i < this->queryTokens.size( ); ++i )
		{
		this->queryTokensBody.push_back( Tokenizer::BODY + this->queryTokens[ i ] );
		}
	return this->queryTokensBody;
	}

/**
 * Query dstor will destroy the query tokens
 *
 */
Query::~Query ( )
	{ }


