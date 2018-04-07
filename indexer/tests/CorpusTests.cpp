#include <iostream>
#include "../Corpus.h"

using namespace std;

int main() {
    Corpus corpus = Corpus();
    cout << "Number chunks: " << corpus.numberChunks << endl;
    cout << "Number documents: " << corpus.numberDocuments << endl;
    cout << "Number words: " << corpus.numberWords << endl;
    for(int i = 0; i < corpus.chunks.size(); i++) {
        cout << "Chunk " << i << endl;
        cout << "\tNumber unique words: " << corpus.chunks[i].numberUniqueWords << endl;
        cout << "\tNumber words: " << corpus.chunks[i].numberWords << endl;
        cout << "\tNumber documents: " << corpus.chunks[i].numberDocs << endl;
        cout << "\tEnding offset: " << corpus.chunks[i].lastLocation << endl;
    }
    return 0;
}
