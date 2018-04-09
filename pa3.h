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
    /*string get_type()
    {
        return type;
    }
    string get_text()
    {
        return text;
    }*/
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

struct Compiler
{
    Block codeBlock;    //Stores tokenized text file
    //Stores tokens by categories
    vector<Token> keywords;
    vector<Token> identifiers;
    vector<Token> constants;
    vector<Token> operators;
    vector<Token> delimiters;
    vector<Token> others;

    bool is_operator(char i)
    {
        return (i == '+' || i == '-' || i == '*' || i == '/');
    }
    bool is_delimiter(char i)
    {
        return (i == ',' || i == ';' || i == '(' || ')');
    }

    void add_keywords(Token in)
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

    // ======== Methods required for tokenizing a line ========

    //Move to next character in string for tokenization
    void next(string& input, int size) {
        input = input.substr(size);
    }

    //Check "keywords" string to be created as tokens for errors
    bool check_keyword(string input)
    {
        string check = input;
        return (check == "FOR" || check == "BEGIN" || check == "END");
    }

    //Make tokens of different types

    void make_key_token(string& input, vector<Token>& tokens)
    {
        char parser = input[0];
        string token(1, parser);
        next(input, 1);
        while (input.size() > 0)
        {
            parser = input[0];
            if (isupper(parser))
            {
                token += parser;
            }
            else
                break;
        }
        if (check_keyword(token))
            tokens.push_back(Keyword(token));
        else
            tokens.push_back(Other(token));
    }
    void make_id_token(string& input, vector<Token>& tokens)
    {
        char parser = input[0];
        string token(1, parser);
        next(input, 1);
        while (input.size() > 0)
        {
            parser = input[0];
            if (islower(parser))
            {
                token += parser;
            }
            else
                break;
        }
        tokens.push_back(Keyword(token));
    }
    void make_const_token(string& input, vector<Token>& tokens)
    {
        char parser = input[0];
        string token(1, parser);
        next(input, 1);
        while (input.size() > 0)
        {
            parser = input[0];
            if (isnumber(parser))
            {
                token += parser;
            }
            else
                break;
        }
        tokens.push_back(Constant(token));
    }
    void make_op_token(string& input, vector<Token>& tokens)
    {
        char parser = input[0];
        string token(1, parser);
        next(input, 1);
        while (input.size() > 0)
        {
            parser = input[0];
            if (is_operator(parser))
            {
                token += parser;
            }
            else
                break;
        }
        tokens.push_back(Keyword(token));
    }
    void make_delim_token(string& input, vector<Token>& tokens)
    {
        char parser = input[0];
        string token(1, parser);
        next(input, 1);
        while (input.size() > 0)
        {
            parser = input[0];
            if (is_delimiter(parser))
            {
                token += parser;
            }
            else
                break;
        }
        tokens.push_back(Delimiter(token));
    }

    void tokenize_line(string& input, vector<Token>& tokens)
    {
        if (input.size() == 0)
            return;
        char parser = input[0];

        if (isupper(parser))
        {
            make_key_token(input, tokens);
            return tokenize_line(input, tokens);
        }
        else if (islower(parser))
        {
            make_id_token(input, tokens);
            return tokenize_line(input, tokens);

        }
        else if (isnumber(parser))
        {
            make_const_token(input, tokens);
            return tokenize_line(input, tokens);

        }
        else if (is_operator(parser))
        {
            make_op_token(input, tokens);
            return tokenize_line(input, tokens);

        }
        else if (is_delimiter(parser))
        {
            make_delim_token(input, tokens);
            return tokenize_line(input, tokens);
        }
        else
        {
            cerr << "Unknown token encountered: " << parser << endl;
            next(input, 1);
            return tokenize_line(input, tokens);
        }

    }
     Block tokenize_text(ifstream& inFile)
    {
        Block output;

        while(!inFile.eof())
        {
            Line temp;

            char lineArr[256];
            inFile.getline(lineArr, 256);
            string line(lineArr);

            tokenize_line(line, temp.tokensInLine);
            output.add_line(temp);
        }
        return output;
    }

};

#endif //PA3_PA3_H
