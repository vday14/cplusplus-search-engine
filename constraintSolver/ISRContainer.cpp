//
// Created by Jake Close on 3/13/18.
//

#include "ISRContainer.h"


ISRContainer::ISRContainer( Tuple * top )  : root( top )
	{

	compile( );
	vector < ISRWord > toRanker;
	for ( auto term : terms )
		{

		ISRWord isrWord = ISRWord( term );
		toRanker.push_back( isrWord );

		}
	ranker.addISR( toRanker );
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

string ISRContainer::Solve( )
	{
	string results;
	clock_t start = clock();


	while(Contained->GetCurrentLocation() != MAX_Location)
		{
		auto url = Contained->GetEndDocument()->getCurrentDoc().url;
		//cout << url << endl;
		//results += url + ",";
		Location BeginningofDocument = Contained->GetISRToBeginningOfDocument( );
		clock_t inner_start = clock();
		//PassToRanker( BeginningfDocument );
		ranker.addDoc( BeginningofDocument );
		clock_t inner_end = clock();
		double time = (inner_end - inner_start) / (double) CLOCKS_PER_SEC;
		//cout << "TIME TO RANK " << time << endl;
		Contained->NextDocument( );
		ranker.numberOfTotalResults++ ;


		}
	clock_t end = clock();
	double time = (end - start) / (double) CLOCKS_PER_SEC;

	results = ranker.getResultsForSite( );
	cout << "Results" << endl;
	cout << "Total number of results :: " << ranker.numberOfTotalResults << endl;
	cout << "Total time to run :: " << to_string( time ) << endl;
	cout << results << endl;
	return results ;


	}

void ISRContainer::PassToRanker( Location docBeginning )
	{

	vector<ISRWord > toRanker;
	for ( auto term : terms )
		{

		ISRWord  isrWord = ISRWord ( term ) ;
		isrWord.Seek( docBeginning );
		toRanker.push_back( isrWord );

		}

	//ranker.addDoc( toRanker );

	}

ISRContainer::~ISRContainer ( )
	{
	delete Contained;
	}


