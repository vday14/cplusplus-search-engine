//
// Created by Zane Dunnings on 4/2/18.
//

#include "Ranker.h"
#include "../../ConstraintSolver/ISRWord.h"
#include "../../ConstraintSolver/ISREndDoc.h"
#include <vector>
#include "Site.h"
#include <priority_queue>

/***
 * TODO: Finalize how we want this to work
 * Initializes the ranker with the Word ISRs from the query, will most likely scale to add more input,
 * could possibly pull the information, depends on how much control we want
 */
void Ranker::init ( query )
	{
	inputQuery = query;
	}

/***
 * This will perform the "sorting" and return a list of ranked URLS
 * @return
 */
vector< string > Ranker::rank ( )
	{

	}