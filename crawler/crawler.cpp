//
// Created by Ben Bergkamp on 1/31/18.
//

#include "crawler.h"

void Crawler::SpawnSpiders ( size_t num_spiders, unordered_map< string, int > *docMapLookup,
                             unordered_map< size_t, int > *duplicateUrlMap )
	{
	for ( size_t i = 0; i < num_spiders; i++ )
		{
		Spider *temp = new Spider( this->mode, this->urlFrontier, docMapLookup, duplicateUrlMap, this->IndexerQueue );
		temp->StartThread( );
		this->spiders.push_back( temp );
		}

	}

void Crawler::WaitOnAllSpiders ( )
	{
	cout << "Waiting for spiders to finish...\n";
	for ( Spider *spider : spiders )
		{
		spider->WaitForFinish( );
		delete spider; //FIXME do this in destructor?
		}
	}


void Crawler::KillAllSpiders ( )
	{
	cout << "Waiting for spiders to finish...\n";
	for ( Spider *spider : spiders )
		{
		spider->Die( );
		delete spider; //FIXME do this in destructor?
		}
	}
