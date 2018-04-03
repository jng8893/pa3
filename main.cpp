#include <iostream>
#include <fstream>

using namespace std;

class Compiler
{

};

int main() {

    ifstream inFile("code.txt", ios::in);
    if (! inFile)
    {
        cerr << "Unable to open file.";
        return -1;
    }
    char ch;
    while (inFile.get(ch))
    {
        cout.put(ch);
    }

    return 0;
}