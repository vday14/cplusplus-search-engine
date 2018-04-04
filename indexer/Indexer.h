#ifndef indexer_h
#define indexer_h

#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"
#include "DocumentEnding.h"
#include "PostingsSeekTableEntry.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

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
	Indexer ( ProducerConsumerQueue< DocIndex * > *doc_index_queue_in ,  ProducerConsumerQueue < unordered_map<string , DocIndex * > >  *anchor_in  );




	void run ( );

	void Kill ( );

	void verbose_run ( );

	void verbose_save ( );


private:
	void save ( );
    void saveWordSeek();
    void saveChunkDictionary ( );
	void SaveAnchorText( unordered_map<string , DocIndex*> * anchorDict );
	void reset ( );

	ProducerConsumerQueue< DocIndex * > *pointerToDictionaries;
	ProducerConsumerQueue< unordered_map<string , DocIndex * > > *AnchorQueue;


	unordered_map< string, vector< size_t > > masterDictionary;
	unordered_map< string, pair<vector< size_t >, size_t> > chunkDictionary;		// <chunks>, occurances
	unordered_map< string, vector< PostingsSeekTableEntry > > postingsSeekTable;

	vector< DocumentEnding > docEndings;
	vector< pair<size_t, size_t> > docEndingsSeek;		// <realLocation, offset (to the correspond docEnding)>
	size_t totalWordsIndexed;
	size_t currentFile;
	size_t currentlyIndexed;
	size_t currentBlockNumberWords;
	size_t currentBlockNumberDocs;

	bool alive = true;

};

#endif /*indexer_h*/
