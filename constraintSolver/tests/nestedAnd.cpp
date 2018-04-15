
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

	//string RB = "($china or #china) AND ($trump OR #trump ) ";
	string RB = "$trump AND $china";
	QueryParser RBParser;
	RBParser.toggleDecorator( );
	RBParser.parse( RB )y;
	ISRContainer container( RBParser.queryTree );
	container.Solve( );





	}

