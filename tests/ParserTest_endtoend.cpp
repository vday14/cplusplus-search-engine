//
// Created by anvia on 2/6/2018.
//

#include <string>
#include "../util/stringProcessing.h"
#include <iostream>
using namespace std;

int main()
{
    string original = "It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout."
            "The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here',"
            "making it look like readable English. ";

    string subStr = "readable";
    auto iter = findStr(subStr, original);
    cout << *iter << endl;
}

