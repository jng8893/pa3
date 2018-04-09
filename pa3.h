#ifndef PA3_PA3_H
#define PA3_PA3_H
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Token
{
    string text;
    string type;
    Token(string text, string type)
    {
        this->text = text;
        this->type = type;
    }
    void change_type(string type)
    {
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
    void add_line (Line& newLine)
    {
        linesInBlock.push_back(newLine);
    }
};

//Definitions of different types of tokens
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

/*struct LineParser //Helper struct for Compiler class
{
    Line tokens;
    Line missing;
    Line others;
    int index;
    bool loop_declaration;
    bool is_begin;
    bool is_end;
    LineParser(Line tokens)
    {
        this->tokens = tokens;
        index = 0;
        loop_declaration = false;
        is_begin = false;
        is_end = false;
    }
};*/

struct Compiler
{
    //Stores tokens by categories
    vector<Token> keywords;
    vector<Token> identifiers;
    vector<Token> constants;
    vector<Token> operators;
    vector<Token> delimiters;
    vector<Token> others;

    void add_keywords(Token& in)
    {
        if (in.type == "keyword")
            keywords.push_back(in);
    }
    void add_identifiers(Token in)
    {
        if (in.type == "identifier")
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

public:
    Block codeBlock;    //Stores tokenized text file

    void print_loop_depth();
    void print_keywords();
    void print_identifiers();
    void print_constants();
    void print_operators();
    void print_delimiters();
    void print_others();

};

void make_key_token(string& input, vector<Token>& tokens);
void make_id_token(string& input, vector<Token>& tokens);
void make_const_token(string& input, vector<Token>& tokens);
void make_op_token(string& input, vector<Token>& tokens);
void make_delim_token(string& input, vector<Token>& tokens);
void tokenize_line(string& input, vector<Token>& tokens);
Block tokenize_text(ifstream& inFile);

#endif //PA3_PA3_H
