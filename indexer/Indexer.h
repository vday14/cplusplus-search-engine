#ifndef indexer_h
#define indexer_h

#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"
#include "DocumentEnding.h"
#include "SeekEntry.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"
#include "WordInfo.h"
#include "IndexerConstants.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <atomic>

/*

Objective: Pulls small dictionaries from the parser and merges them into the 
master index.

TODO:
 Use deltas between the offsets
 Save with UTF-8 encoding
 Concrete block size - 100MB per block?
 Save document endings and other relevant metadata?

*/

using namespace std;
using DocIndex = const unordered_map< string, vector< unsigned long > >;

class Indexer : public ThreadClass
	{
public:
	Indexer ( ProducerConsumerQueue< DocIndex * > *doc_index_queue_in ,
			  ProducerConsumerQueue < unordered_map<string , DocIndex * > >  *anchor_in  );

	void run ( );
	void Kill ( );
	size_t numberDocsIndexed;

private:
	void save ( );
    void saveWordSeek();
    void saveChunkDictionary ( );
	void SaveAnchorText( unordered_map<string , DocIndex*> * anchorDict );
	void reset ( );

	ProducerConsumerQueue< DocIndex * > *pointerToDictionaries;
	ProducerConsumerQueue< unordered_map<string , DocIndex * > > *AnchorQueue;

	// for master.txt file - includes chunks the words appear in, the last real location of the word, and frequency
	unordered_map< string, WordInfo > chunkDictionary;
	vector<size_t> chunkEndLocation;

	unordered_map< string, vector< size_t > > masterDictionary;
	unordered_map< string, vector< SeekEntry > > seekDictionary;
	vector< DocumentEnding > docEndings;

	unordered_map< string, size_t> urlToDocEndings;

	size_t currentFile;
	size_t currentlyIndexed;
	size_t currentBlockNumberWords;
	size_t currentBlockNumberDocs;

	atomic_bool* alive = new atomic_bool(true);

};

#endif /*indexer_h*/
