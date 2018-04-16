//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"
#include "ISREndDoc.h"
#include "ISRAnd.h"
#include "ISROr.h"
#include "../ranker/Ranker.h"
#include "../util/DataStructureLib/tuple.cpp"
#include <string>

//Find occurrences of contained ISRs in a single document not containing any excluded ISRs.

class ISRContainer
	{
public:
	ISR *Contained;
	ISR *Excluded;
	vector<string> terms;
	Tuple* root;

	ISRContainer( Tuple * tuple_in, std::string CompleteQuery );
	ISR * recurviseCompile( Tuple * root );

	unsigned CountContained,
			CountExcluded;

	void compile( );


	Location Seek ( Location target )
		{
// 1. Seek all the included ISRs to the first occurrence beginning at
//    the target location.
// 2. Move the document end ISR to just past the furthest
//    contained ISR, then calculate the document begin location.
// 3. Seek all the other contained terms to past the document begin.
// 4. If any contained erm is past the document end, return to
//    step 2.
// 5. If any ISR reaches the end, there is no match.
// 6. Seek all the excluded ISRs to the first occurrence beginning at
//    the document begin location.
// 7. If any excluded ISR falls within the document, reset the
//    target to one past the end of the document and return to
//    step 1.
		return 1;

		};


/*
 * Seek()
 * GetEndDocument
 *
 */
	string Solve( );
	void PassToRanker ( Location BeginningfDocument );

	~ISRContainer ( );


private:
	unsigned nearestTerm, farthestTerm;
	Location nearestStartLocation, nearestEndLocation;
	Ranker ranker;
	};
