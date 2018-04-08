#ifndef PA3_PA3_H
#define PA3_PA3_H
#include <string>

using namespace std;

struct Token
{
    string input;
    string type;
    Token(string input, string type)
    {
        this->input = input;
        this->type = type;
    }
};

struct Line
{
    vector<Token> tokensInLine;
    void add_token (Token newToken)
    {
        tokensInLine.push_back(newToken);
    }
};

struct Block
{
    vector<Line> linesInBlock;
    void add_line (Line newLine)
    {
        linesInBlock.push_back(newLine);
    }
};

struct Keyword : Token
{
    Keyword(string input) : Token(input, "keyword"){}
};
struct Identifier : Token
{
    Identifier(string input) : Token(input, "identifier"){}
};
struct Constant : Token
{
    Constant(string input) : Token(input, "constant"){}
};
struct Operator : Token
{
    Operator(string input) : Token(input, "operator"){}
};
struct Delimiter : Token
{
    Delimiter(string input) : Token(input, "delimiter"){}
};
struct Other : Token
{
    Other(string input) : Token(input, "other"){}
};

struct Compiler
{
    vector<Token> keywords();
    vector<Token> identifiers();
    vector<Token> constants();
    vector<Token> operators();
    vector<Token> delimiters();
    vector parseUppercase ();
};

#endif //PA3_PA3_H
