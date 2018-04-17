#include <iostream>
#include "../Corpus.h"

using namespace std;

int main() {
    Corpus corpus = Corpus::getInstance();

    cout << "Number chunks: " << corpus.numberChunks << endl;
    cout << "Number documents: " << corpus.numberDocuments << endl;
    cout << "Number words: " << corpus.numberWords << endl;
    cout << "Number unique words: " << corpus.numberUniqueWords << endl;
    for(int i = 0; i < corpus.chunks.size(); i++) {
        cout << "Chunk " << i << endl;
        cout << "\tNumber unique words: " << corpus.chunks[i].numberUniqueWords << endl;
        cout << "\tNumber words: " << corpus.chunks[i].numberWords << endl;
        cout << "\tNumber documents: " << corpus.chunks[i].numberDocs << endl;
        cout << "\tEnding offset: " << corpus.chunks[i].lastLocation << endl;
    }
    WordInfo momentInfo = corpus.getWordInfo("moment");
    cout << "Moment" << endl;
    cout << "\tChunks: ";
    for(auto chunk : momentInfo.chunks) {
        cout << chunk << " ";
    }
    cout << endl;
    cout << "\tDocument frequency: " << momentInfo.docFrequency << endl;
    cout << "\tFrequency: " << momentInfo.frequency << endl;
    cout << "\tLast location: " << momentInfo.lastLocation << endl;

    WordInfo lifeInfo = corpus.getWordInfo("life");
    cout << "Life" << endl;
    cout << "\tChunks: ";
    for(auto chunk : lifeInfo.chunks) {
        cout << chunk << " ";
    }
    cout << endl;
    cout << "\tDocument frequency: " << lifeInfo.docFrequency << endl;
    cout << "\tFrequency: " << lifeInfo.frequency << endl;
    cout << "\tLast location: " << lifeInfo.lastLocation << endl;

    return 0;
}
