#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pa3.h"

using namespace std;

int main()
{
    cout << "Please enter the name of the input file: " << endl;
    string fileName;
    cin >> fileName;

    ifstream inFile(fileName);
    if (!inFile)
    {
        cerr << "Unable to open file.";
        return -1;
    }
    inFile.open(fileName);

    char ch;
    /*while (inFile.get(ch))  //Print out file contents.
    {
        cout.put(ch);
    }*/

    while (!inFile.eof())
    {
        ;
    }
  /*  vector<char>::iterator it = text.begin();
    for (auto it = text.begin(); it != text.end(); it++)
    {
        char temp;
        temp = *it;
        cout << temp;
    }*/


    return 0;
}