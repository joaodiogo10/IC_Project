#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){

    if(argc != 3){
        cout << "Need two arguments" << endl;
        return -1;
    }
    
    ifstream ifs(argv[1]);
    ofstream ofs(argv[2]);

    vector<char> bytes;
    char byte = 0;

    if(!ifs.is_open()){
        cerr << "Could not open file - '" << argv[1] << "'" << endl;
        return EXIT_FAILURE;
    }

    while(ifs.get(byte)){
        bytes.push_back(byte);
    }
    
    for(const auto &i : bytes){
        ofs << i;
    }
    
    ofs << endl;
    ifs.close();
    ofs.close();
    
    return 0;
}
