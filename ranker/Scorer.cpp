
#include "Scorer.h"
#include "Site.h"
#include <vector>
#include "../shared/url.h"

/***
 * Calculate the score for some site, Normalize the score to 1.0
 * @return
 */
double Scorer::getScore ( Site website)
	{
	double score = 0.0;
	int numberOfFunctions = 1;

	//Repeat for each function
	score += Static( website )*STATIC_WEIGHT;

	return score / (double)numberOfFunctions;
	}


double Scorer::Static( Site inputSite )
	{
	std::string inputUrl = inputSite.getUrl( );
	if ( findStr( "http://", inputUrl ) == inputUrl.size( ) )
		{
		inputUrl = "http://" + inputUrl;
		}
	ParsedUrl url(  inputUrl );
	std::string domain = url.getDomain( );

	if ( Scorer::domainMap.find( domain ) != Scorer::domainMap.end( ) )
		{
		return Scorer::domainMap[ domain ];
		}
	return 0;
	}


