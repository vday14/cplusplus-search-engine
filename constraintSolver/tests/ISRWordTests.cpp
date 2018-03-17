//
// Created by nick on 3/16/18.
//

#include <iostream>
#include "../ISRWord.h"
#include "../ISRWord.cpp"

using namespace std;

int main() {
    ISRWord word = ISRWord("hello");
    while(1) {
        cout << word.next() << endl;
    }
    return 0;
}