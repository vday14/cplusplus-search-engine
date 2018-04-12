
#include "../../query/queryLanguage/QueryParser.h"
#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"
#include "../ISRContainer.h"
#include "../ISRAnd.h"
#include <vector>
using namespace std;

int main ( )
	{

	string RB = "($china or #china) AND ($trump OR #trump ) ";
	QueryParser RBParser;
	RBParser.toggleDecorator( );
	RBParser.parse( RB );
	ISRContainer container( RBParser.queryTree );
	container.Solve( );





	}

