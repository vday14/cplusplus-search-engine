#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

bool isNumber(string line) {
    return (atoi(line.c_str()));
}

const int NUMBER_OF_FILES = 5;

int main() {
    vector <ifstream> files;
    string word;
    unordered_map <int, bool> wow;
    for(int i = 0; i < NUMBER_OF_FILES; i++) {
        string file = "index" + to_string(i) + ".txt";
        files.push_back(ifstream(file));
    }
    for(int j = 0; j < files.size(); j++) {
        while(files[j] >> word) {
            if(isNumber(word)) {
                int ss = stoi(word);
                if(wow[ss]) {
                    cout << " U FAILED " << endl;
                    cout << ss << " APPEARED MULTIPLE TIMES!!!" << endl;
                    exit(999);
                } else {
                    wow[ss] = true;
                }
            }
        }
    }
    cout << wow.size() << endl;
    return 0;
}
