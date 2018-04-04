//
// Created by Ben Bergkamp on 1/31/18.
//

#include "crawler.h"
using DocIndex = const unordered_map< string, vector< unsigned long > >;

/*
 *
 * @parms number of spiders
 * Creates a number of spiders and starts new threads for them
 *
 */


void Crawler::SpawnSpiders ( size_t num_spiders , atomic_bool * alive)
	{
	for ( size_t i = 0; i < num_spiders; i++ )
		{
		Spider *temp = new Spider( this->mode, this->urlFrontier, this->IndexerQueue , alive);
		temp->StartThread( );
		this->spiders.push_back( temp );
		}


	}

/*
 *
 *Function to wait for all of the threads to finish running
 *
 */
void Crawler::WaitOnAllSpiders ( )
	{
	cout << "Waiting for spiders to finish...\n";

		while( ! spiders.empty( ) )
			{
			Spider *spider = spiders.back();
			spiders.pop_back();


			spider->WaitForFinish();
			spider = 0;
			delete spider;
			}

	cout << "Spiders have finished running " << endl;
	return;
		}


/*
 *
 * Set all of the spiders atomic bools to false so that they finish crawling the web
 */

void Crawler::KillAllSpiders ( )
	{
	//cout << "Waiting for spiders to finish...\n";
	for ( Spider *spider : spiders )
		{
		spider->kill( );
		}
	}

/*
 *
 * Looks through the  url map an gets all associated anchor text with the url
 * Uses the tokenizer to create a dictionary of all anchor texts
 * Creates a new dictionary of urls - >  tokenized dicts
 * Pushes the dictionary of urls -> tokenized dicts to the anchor queue
 */


void Crawler::passAnchorTextToIndex( )
	{


	unsigned long offset = 0;
	unordered_map<string , DocIndex * > urlToAnchorDict;

	for ( auto const &ent1 : *urlFrontier->duplicateUrlMap )
		{
		auto const &outer_key = ent1.first;
		auto const &inner_map = ent1.second;
		Tokenizer tokenizer;
		for ( auto const &ent2 : inner_map )
			{


			auto const &inner_key = ent2.first;
			auto const &inner_value = ent2.second;
			if ( !inner_key.empty( ))
				{
				/*
				cout << "url: " << outer_key << endl;
				cout << "anchor text : " << inner_key << endl;
				cout << "count " << inner_value << endl;
				  */
				offset = tokenizer.execute( inner_key, offset, Tokenizer::ANCHOR );
				DocIndex *dict =  tokenizer.get( );
				if(dict->size() != 0 )
					urlToAnchorDict[outer_key] = dict;

				}

			}

		}

	AnchorQueue->Push( urlToAnchorDict );
	cout << "Crawler has sent the anchor text" << endl;
	return;
	}
