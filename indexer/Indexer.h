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
	Indexer ( ProducerConsumerQueue< DocIndex * > *doc_index_queue_in );


	void run ( );

	void verbose_run ( );

	void verbose_save ( );


private:
	void save ( );
    void saveWordSeek();
    void saveChunkDictionary ( );

	void reset ( );

	ProducerConsumerQueue< DocIndex * > *pointerToDictionaries;
	unordered_map< string, vector< size_t > > masterDictionary;
	unordered_map< string, vector< size_t > > chunkDictionary;
	unordered_map< string, vector< PostingsSeekTableEntry > > postingsSeekTable;

	vector< DocumentEnding > docEndings;

	size_t currentFile;
	size_t currentlyIndexed;

	size_t currentBlockNumberWords;
	size_t currentBlockNumberDocs;

};

#endif /*indexer_h*/
