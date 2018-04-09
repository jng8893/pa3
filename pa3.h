#ifndef PA3_PA3_H
#define PA3_PA3_H
#include <string>
#include <vector>
#include <cctype>

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
    string get_type()
    {
        return type;
    }
    string get_input()
    {
        return input;
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
    Block codeBlock;
    vector<Token> keywords;
    vector<Token> identifiers;
    vector<Token> constants;
    vector<Token> operators;
    vector<Token> delimiters;
    vector<Token> others;

    void add_keywords(Token in)
    {
        if (in.type == "keyword")
            keywords.push_back(in);
    }
    void add_identifiers(Token in)
    {
        if (in.type == "indentifier")
            identifiers.push_back(in);
    }
    void add_constants(Token in)
    {
        if (in.type == "constant")
            constants.push_back(in);
    }
    void add_operators(Token in)
    {
        if (in.type == "operator")
            operators.push_back(in);
    }
    void add_delimiters(Token in)
    {
        if (in.type == "delimiter")
            delimiters.push_back(in);
    }
    void add_others(Token in)
    {
        if (in.type == "other")
            others.push_back(in);
    }
     void tokenize_text(string temp, string type, char input[], int i)
    {
        Line output;
        string type2;


        if (isupper(input[i])) //Check for keyword char
        {
            temp += input[i];
            type2 = "keyword";
        }
        else if (islower(input[i])) //Check for identifier char
        {
            temp += input[i];
            type2 = "identifier";
        }
        else if (isdigit(input[i])) //Check for constant (number) char
        {
            temp += input[i];
            type2 = "constant";
        }
        else if (input [i] == '+' || input [i] == '-' || input [i] == '*' || input [i] == '/') //Check for operator
        {
            temp += input[i];
            type2 = "operator";
        }
        else if (input [i] == ',' || input [i] == ';' || input [i] == ) //Check for delimiters
        {
            temp += input[i];
            type2 = "operator";
        }
        tokenize_text(temp, type, input[], ++i);


        return output;
    }

};

#endif //PA3_PA3_H
