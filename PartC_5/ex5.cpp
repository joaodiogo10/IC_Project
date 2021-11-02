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
    int count;
    char myText;
    while (f.get(myText)) {
        char val;
        f >> val;
        histogram[val]++;
        count++;
    }
    for (auto &a : histogram) {
        cout << a.first << ": ";
        cout << histogram[a.first];
        cout << endl;
    }

    float enthropy;
    for(auto &x : histogram){
        probMap[x.first] = ((float)histogram[x.first]) / count;
        cout << "prob " << probMap[x.first] << "\n";
        if(probMap[x.first] != 0){
            enthropy += probMap[x.first] * log2(probMap[x.first]);
            enthropy = enthropy * (-1);
        }
    }
}