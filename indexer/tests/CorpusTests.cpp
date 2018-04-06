#include <iostream>
#include "../Corpus.h"

using namespace std;

int main() {
    Corpus corpus = Corpus();
    cout << "Number chunks: " << corpus.getNumChunks() << endl;
    cout << "Number documents: " << corpus.getNumDocuments() << endl;
    cout << "Number words: " << corpus.getNumWords() << endl;
    for(int i = 0; i < corpus.getNumChunks(); i++) {
        cout << "Ending for chunk " << i << ": " << corpus.getChunkEnding(i) << endl;
    }
    return 0;
}