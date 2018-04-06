#include "../ISREndDoc.h"

using namespace std;

int main() {
    ISREndDoc endDoc;
    endDoc.seek(43);
    cout << endDoc.getCurrentDoc().docEndPosition << endl;
}
