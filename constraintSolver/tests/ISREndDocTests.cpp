#include "../ISREndDoc.h"

using namespace std;

int main() {
    ISREndDoc endDoc;
    endDoc.seek(1000);
    cout << endDoc.next().docEndPosition << endl;
}