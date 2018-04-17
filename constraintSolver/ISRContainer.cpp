//
// Created by Jake Close on 3/13/18.
//

#include "ISRContainer.h"


ISRContainer::ISRContainer( Tuple * top, ProducerConsumerQueue< pair<Location, Location> > * MatchQueueIn )  : root( top )
	{

	compile( );

	//vector < ISRWord * > toRanker;
	for ( auto term : terms )
		{

		ISRWord * isrWord = new ISRWord( term );
		toRanker.push_back( isrWord );

		}


	MatchQueue = MatchQueueIn;


	}



void ISRContainer::compile( )
	{


	Contained = recurviseCompile( root );


	}

ISR * ISRContainer::recurviseCompile( Tuple * root )
	{
	vector< ISR * > words;
	if( root->Type == WordTupleType )
		{


		string currentTerm = root->object.text;
		terms.push_back( currentTerm );
		return new ISRWord( currentTerm );
		}

	else
		{
		for( auto child : root->Next )
			words.push_back( recurviseCompile( child ) );
		}

		if( root->Type == AndTupleType )
			return  new ISRAnd ( words );
		else
			return  new ISROr ( words );

	}

void ISRContainer::Solve( )
	{


	double rankingTime;


	set< size_t > seenLocations;
	clock_t inner_start = clock();

	while(Contained->GetCurrentLocation() != MAX_Location)
		{
		string url = Contained->GetEndDocument()->getCurrentDoc().url;
		Location EndOfDoc = Contained->GetEndDocument()->getCurrentDoc().docEndPosition;
		Location bofDoc = Contained->GetISRToBeginningOfDocument( );

		pair <Location, Location> match(bofDoc, EndOfDoc);
		MatchQueue->Push( match );
		clock_t inner_start = clock();
		Contained->NextDocument( );
		clock_t inner_end = clock();
		//cout << "Time to Next" << endl;
		//cout <<  (inner_end - inner_start) / (double) CLOCKS_PER_SEC << endl;

		}
	pair <Location, Location> last(MAX_Location, MAX_Location);

	MatchQueue->Push( last );
	clock_t inner_end = clock();
	double time = (inner_end - inner_start) / (double) CLOCKS_PER_SEC;
	cout << "DONE RUNNING: " << to_string(time) << endl;

	return ;


	}


ISRContainer::~ISRContainer ( )
	{
	delete Contained;
	}


