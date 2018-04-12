// 123 108 7 16 12 1 192 105 37 6 20 111 45 24 31 77 77 164 6 31 5 36 82 26 22 206 7 1 54 15 172 45 207 52 28 44 2 18 29 79 40 17 24 14 12 118 51 16 12 13 16 16 50 170 73 11 26 2 13 11 123 26 54 15 93 26 43 19 67 2 35 47 23 2 9 118 26 46 3 56 48 47 154 18 44 111 47 28 17 2 30 29 46 79 255 156 63 225 31

#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int sum = 0;
    string input;
    while(1) {
        cin >> input;
        if(input == "q") {
            break;
        }
        sum += stoi(input);
    }
    cout << "Sum is " << sum << endl;
    return 0;
}