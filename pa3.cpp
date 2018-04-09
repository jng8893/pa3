#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
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
        char line[256];
        inFile.getline(line, 256);
        string to_token(line);
//        cout << to_token;
        for (int i = 0; i < to_token.length(); i++)
        {
            if (to_token[i] == ' ' || to_token[i] == '\n')
                to_token.erase(i, 1);
        }
        cout << to_token << endl;
        inFile.clear();
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