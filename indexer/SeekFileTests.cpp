//
// Created by nick on 3/13/18.
//

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    int index1 = open("index0.txt", O_CREAT|O_RDWR, S_IRWXU);
    lseek(index1, 129522, SEEK_SET);
    char buffer[10];
    if(read(index1, buffer, 10) != 10) {
        cout << "ERROR" << endl;
    }
    cout << buffer << endl;
    close(index1);
    return 0;
}