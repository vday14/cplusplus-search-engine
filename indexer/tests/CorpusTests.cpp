#include <iostream>
#include "../Corpus.h"

using namespace std;

int main() {
    Corpus corpus = Corpus();
    cout << "Number chunks: " << corpus.numberChunks << endl;
    cout << "Number documents: " << corpus.numberDocuments << endl;
    cout << "Number words: " << corpus.numberWords << endl;
    for(int i = 0; i < corpus.chunks.size(); i++) {
        cout << "Ending for chunk " << i << ": " << corpus.chunks[i].lastLocation << endl;
    }
    return 0;
}
