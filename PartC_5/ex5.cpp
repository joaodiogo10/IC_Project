#include <map>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2){
        cout << "Needs 1 argument" << endl;
        return 0;
    }
    map<char, int> histogram;
    map<char, float> probMap;

    ifstream f(argv[1]);
    int count = 0;
    char myText;
    float enthropy;
    while (f.get(myText)) {
        char val;
        f >> val;
        if(isalpha(val)){
            histogram[val]++;
            count++;
        }
    }

    for (auto &a : histogram) {
        cout << a.first << ": ";
        cout << histogram[a.first];
        probMap[a.first] = (((float)histogram[a.first]) / count) * 100;
        cout << "    prob " << probMap[a.first] << " %";
        if(probMap[a.first] != 0){
            enthropy += probMap[a.first] * log2(probMap[a.first]);
        }
        cout << endl;
    }
    cout << "enthropy: " << enthropy << endl;
}