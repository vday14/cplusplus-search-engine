//
// Created by nick on 3/13/18.
//

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    int index1 = open("index0.txt", O_CREAT|O_WRONLY, S_IRWXU);
    lseek(index1, 25, SEEK_SET);
    string fs = "hello";
    if(write(index1, fs.c_str(), strlen(fs.c_str())) != strlen(fs.c_str())) {
        cout << "ERROR" << endl;
    }
    close(index1);
    return 0;
}