//
// Created by Ben Bergkamp on 1/31/18.
//

#include "crawler.h"

/*
 *
 * @parms number of spiders
 * Creates a number of spiders and starts new threads for them
 *
 */


void Crawler::SpawnSpiders ( size_t num_spiders )
	{
	for ( size_t i = 0; i < num_spiders; i++ )
		{
		Spider *temp = new Spider( this->mode, this->urlFrontier, this->IndexerQueue );
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
