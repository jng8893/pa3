#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*class Compiler
{
    public:
        vector<string> keywords();
        vector<string> identifiers();
        vector<string> constants();
        vector<string> operators();
        vector<string> delimiters();

        vector parseUppercase ();
};*/

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
    while (inFile.get(ch))  //Print out file contents.
    {
        cout.put(ch);
    }

    vector<char> text;
    while (inFile.get(ch))
    {
        text.push_back(ch);
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