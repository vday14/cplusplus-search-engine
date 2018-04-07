//
// Created by Jake Close on 3/13/18.
//

#include "ISRContainer.h"


ISRContainer::ISRContainer( Tuple * top )  : root( top )
	{

	compile( );
	}



void ISRContainer::compile( )
	{


	Contained = recurviseCompile( root );


	}

ISR * ISRContainer::recurviseCompile( Tuple * root )
	{
	vector< ISR * > terms;
	if( root->Type == WordTupleType )
		return new ISRWord( root->object.text );

	else
		{
		for( auto child : root->Next )
			terms.push_back( recurviseCompile( child ) );
		}

		if( root->Type == AndTupleType )
			return  new ISRAnd ( terms );
		else
			return  new ISROr ( terms );

	}

void ISRContainer::Solve( )
	{
	while(Contained->GetCurrentLocation() != MAX_Location)
		{
		auto url = Contained->GetEndDocument()->getCurrentDoc().url;
		cout << url << endl;

		Contained->NextDocument( );



/*
 * beg = GetBeginning of Doc
 * Pass Terms to ranker
 *
 * vector<words>
 *
 * Ranker:
 * for term in terms
 * IsrWord word = new ISR(term)
 * Term.seek(beg)
 * words.push(word)
 * rank(words)
 *
 * NextDocument()
 */
		}


	}

