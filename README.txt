C++lue Search Engine ReadME:::

Operating system:
Mac OSX (should work on Linux as well but not as thoroughly tested)

In order to run the server and interact with the UI:
---------------------------------------------------
Compile using this command:

site/LinuxTinyServer.cpp query/Query.cpp parser/queryTokenizer.cpp query/Searcher.cpp 
util/DataStructureLib/tuple.cpp util/stringProcessing.cpp util/Stemmer.cpp util/util.cpp 
constraintSolver/ISRContainer.cpp ranker/Ranker.cpp indexer/Corpus.cpp indexer/Chunk.cpp ranker/Site.cpp 
ranker/Scorer.cpp query/queryLanguage/QueryParser.cpp constraintSolver/ISREndDoc.cpp constraintSolver/ISRWord.cpp 
constraintSolver/ISRAnd.cpp constraintSolver/ISROr.cpp shared/ThreadClass.cpp -o server

Run with "./server"

Run the "server" exectuable, specifying port number and "/bootstrap_landing_page" as command line arguments
In your web browser use the url: "localhost:{portnumbe}/index.html"
Example --> 
Command Line = "7000 /bootstrap_landing_page"
URL in browser = "localhost:7000/index.hml"

If you are on MWireless:
Use IP address instead of local host
Example URL in browser = "{ip address}:7000/index.hml"

*** if you recieve an error "Assertion failed: (bindResult == 0)" change the port number to a different port

In order to run the search engine through the terminal:
---------------------------------------------------
Compile using this command:

g++ -std=c++11 search.cpp query/Searcher.cpp util/DataStructureLib/tuple.cpp 
util/stringProcessing.cpp util/Stemmer.cpp util/util.cpp constraintSolver/ISRContainer.cpp 
ranker/Ranker.cpp indexer/Corpus.cpp indexer/Chunk.cpp ranker/Site.cpp ranker/Scorer.cpp 
query/queryLanguage/QueryParser.cpp constraintSolver/ISREndDoc.cpp constraintSolver/ISRWord.cpp 
constraintSolver/ISRAnd.cpp constraintSolver/ISROr.cpp query/Query.cpp parser/queryTokenizer.cpp shared/ThreadClass.cpp -o search-engine

In the "indexer/IndexerConstants.h" file, ensure the index is using "/build50/"

Run with "./search-engine"