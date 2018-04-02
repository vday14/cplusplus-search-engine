#include "../ISREndDoc.h"

using namespace std;

int main() {
    ISREndDoc endDoc;
    endDoc.seek(4000);
    cout << endDoc.next().docEndPosition << endl;
}