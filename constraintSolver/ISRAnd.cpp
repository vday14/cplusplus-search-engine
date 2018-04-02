//
// Created by Jake Close on 3/13/18.
//

#include "ISRAnd.h"
#include <cassert>

ISRAnd::ISRAnd ( vector<ISR * > InputTerms ) : Terms( InputTerms )
	{

	assert(InputTerms.size() > 1);

	for (auto currentTerm : InputTerms)
	{
		currentTerm->First();
		Location currentLocation = currentTerm->currentLocation;
		if (currentLocation < nearestStartLocation) {
			nearestTerm = currentTerm;
			nearestStartLocation = currentLocation;

		}
		if (currentLocation > nearestEndLocation) {
			nearestEndLocation = currentLocation;
		}
		++NumberOfTerms;
		currentTerm++;

	}
	}

Location ISRAnd::First()
	{
	//Fixme?
	Location first = MAX_Location;

	for(auto isr : Terms)
		{
			Location temp = isr->First();
			if (temp < first)
			{
				first = temp;
			}
		}

	//fixme should this return the nearest location of one subterm or the nearest location all the terms match?
	currentLocation = Seek(first);
	return currentLocation;
	}


Location ISRAnd::Next ( )
	{
	return Seek( nearestStartLocation);
	}

Location ISRAnd::NextDocument()
	{
	return Seek( GetEndDocument()->getCurrentDoc().docEndPosition  + 1);
	}

Location ISRAnd::Seek ( Location target )
	{
	//Todo
	// 1. Seek all the ISRs to the first occurrence beginning at
	//    the target location.
	// 2. Move the document end ISR to just past the furthest
	//    word, then calculate the document begin location.
	// 3. Seek all the other terms to past the document begin.
	// 4. If any term is past the document end, return to
	//    step 2.
	// 5. If any ISR reaches the end, there is no match.

	Location nearest;
	Location furthest = 0;

	while(furthest != MAX_Location) {

		nearest = MAX_Location;

		//find nearest & furthest ISR
		for (auto isr : Terms) {
			Location temp = isr->Seek(target);
			if (temp == MAX_Location) return MAX_Location;
			if (temp > furthest) furthest = temp;
			if (temp < nearest) nearest = temp;
		}

		//Get Document of the furthest ISR
		//DocumentEnd->Seek( furthest  );

		//set next target to be starting location of document
		Location lastDocStart = DocumentEnd->GetStartingPositionOfDoc();

		if(nearest >= lastDocStart)
		{
			//MATCH
			//Does it matter for 'AND' what location we return? first/last in document?
			//Should we return an ISR as well?
			return nearest;
		} else{
			//No Match yet, keep searching
			target = lastDocStart;
		}

	}

	}

ISREndDoc * ISRAnd::GetEndDocument()
	{
	//What does currentLocation hold?  When is it updated?
	//return DocumentEnd->Seek(currentLocation);
	}

Location ISRAnd::GetCurrentLocation(){
	//What does currentLocation hold?  When is it updated?
	//return DocumentEnd->Seek(currentLocation);
	return currentLocation;
	}


