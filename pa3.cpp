#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "pa3.h"

using namespace std;

bool is_operator(char i)
{
    return (i == '+' || i == '-' || i == '*' || i == '/' || i == '=');
}
bool is_delimiter(char i)
{
    return (i == ',' || i == ';' || i == '(' || i == ')');
}


void Compiler::print_keywords()
{
    cout << "Keywords: ";
    for (int i = 0; i < keywords.size(); i++)
    {
        Token temp = keywords[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}
void Compiler::print_identifiers()
{
    cout << "Identifiers: ";
    for (int i = 0; i < identifiers.size(); i++)
    {
        Token temp = identifiers[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}
void Compiler::print_constants()
{
    cout << "Constants: ";
    for (int i = 0; i < constants.size(); i++)
    {
        Token temp = constants[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}
void Compiler::print_operators()
{
    cout << "Operators: ";
    for (int i = 0; i < operators.size(); i++)
    {
        Token temp = operators[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}
void Compiler::print_delimiters()
{
    cout << "Delimiters: ";
    for (int i = 0; i < delimiters.size(); i++)
    {
        Token temp = delimiters[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}
void Compiler::print_others()
{
    cout << "Syntax Error(s): ";
    for (int i = 0; i < others.size(); i++)
    {
        Token temp = others[i];
        cout <<temp.text << " ";
    }
    cout << endl;
}

// ======== Methods required for tokenizing a line ========

//Move to next character in string for tokenization
void next(string& input, int size) {
    input = input.substr(size);
}

//Check "keywords" string to be created as tokens for errors
bool check_keyword(string& input)
{
    return (input == "FOR" || input == "BEGIN" || input == "END");
}

//Retrieve line from text file
string read_line(ifstream &inFile) {
    char line[256];
    inFile.getline(line, 256);
    return string(line);
}

//Make tokens of different types

void make_key_token(string& input, vector<Token>& tokens)
{
    char parser = input[0];
    string token(1, parser);
    next(input, 1);
    while (!input.empty())
    {
        parser = input[0];
        if (isupper(parser))
        {
            token += parser;
            next(input, 1);
        }
        else
            break;
    }
    if (check_keyword(token))
    {
        tokens.push_back(Keyword(token));
//        this->keywords.push_back(Keyword(token));
    }
    else
    {
        tokens.push_back(Other(token));
//        this->others.push_back(Other(token));
    }
}
void make_id_token(string& input, vector<Token>& tokens)
{
    char parser = input[0];
    string token(1, parser);
    next(input, 1);
    while (!input.empty())
    {
        parser = input[0];
        if (islower(parser))
        {
            token += parser;
            next(input, 1);
        }
        else
            break;
    }
    tokens.push_back(Identifier(token));
//    identifiers.push_back(Identifier(token));
}
void make_const_token(string& input, vector<Token>& tokens)
{
    char parser = input[0];
    string token(1, parser);
    next(input, 1);
    while (!input.empty())
    {
        parser = input[0];
        if (isdigit(parser))
        {
            token += parser;
            next(input, 1);
        }
        else
            break;
    }
    tokens.push_back(Constant(token));
//    constants.push_back(Constant(token));
}
void make_op_token(string& input, vector<Token>& tokens)
{
    char parser = input[0];
    string token(1, parser);
    next(input, 1);
    while (!input.empty())
    {
        parser = input[0];
        if (is_operator(parser))
        {
            token += parser;
            next(input, 1);
        }
        else
            break;
    }
    tokens.push_back(Operator(token));
//    operators.push_back(Operator(token));
}
void make_delim_token(string& input, vector<Token>& tokens)
{
    char parser = input[0];
    string token(1, parser);
    next(input, 1);
    while (!input.empty())
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
//    delimiters.push_back(Delimiter(token));
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
    else if (isdigit(parser))
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
    else if (isblank(parser))
    {
        next(input, 1);
        return tokenize_line(input, tokens);
    }
    else
    {
        cerr << "Unknown token encountered: " << parser << endl;
        next(input, 1);
        return tokenize_line(input, tokens);
    }

}
Block tokenize_text(ifstream &inFile)
{
    Block output;

    while(!inFile.eof())
    {
        Line temp;
        string line = read_line(inFile);
        tokenize_line(line, temp.tokensInLine);
        output.add_line(temp);
    }
    return output;
}

Token searchingFor(Token toTheStack)
{
    if (toTheStack.type == "keyword")
    {
        if (toTheStack.text == "END")
            return Token("BEGIN", "keyword");
        if (toTheStack.text == "CFORLOOP")
            return Token("FOR", "keyword");
    }
    if (toTheStack.type == "delimiter")
        if (toTheStack.text == ")")
            return Token("(", "delimiter");
}
void completeParen(stack<Token> stack1)
{
    if (stack1.top().text == ")")
    {
        while (stack1.top().text != )
    }
}
void completeForLoop(stack<Token> stack1, int forsInStack, int loopDepth)
{
    if (stack1.top().text == "END")
    {
        while (stack1.top().text != "BEGIN" || stack1.top().text != "FOR")
            stack1.pop();
        if (stack1.top().text == "BEGIN")
        {
            while (stack1.top().text != "FOR")
                stack1.pop();
            stack1.pop();
            stack1.push(Token("CFORLOOP", "keyword"));
            loopDepth++;
        }
    }
    else if (stack1.top().text == "CFORLOOP")
    {
        while (stack1.top().text != "FOR")
            stack1.pop();
        stack1.pop();
        forsInStack--;
    }
}
void print_stack(stack<Token> stack1)
{
    while (!stack1.empty())
    {
        cout << stack1.top().text << endl;
        stack1.pop();
    }

}

void unique_line_tokens(Line& line, Compiler& compiler) //Helper function to store_unique_tokens
{
    for (int i = 0; i < line.tokensInLine.size(); i++)
    {
        bool isUnique = true;
        if (line.tokensInLine[i].type == "keyword")
        {
            for (int j = 0; j <= compiler.keywords.size(); j++)
            {
                if (compiler.keywords.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.keywords[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_keywords(line.tokensInLine[i]);
        }
        else if (line.tokensInLine[i].type == "identifier")
        {
            for (int j = 0; j <= compiler.identifiers.size(); j++)
            {
                if (compiler.identifiers.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.identifiers[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_identifiers(line.tokensInLine[i]);
        }
        else if (line.tokensInLine[i].type == "constant")
        {
            for (int j = 0; j <= compiler.constants.size(); j++)
            {
                if (compiler.constants.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.constants[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_constants(line.tokensInLine[i]);
        }
        else if (line.tokensInLine[i].type == "operator")
        {
            for (int j = 0; j <= compiler.operators.size(); j++)
            {
                if (compiler.operators.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.operators[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_operators(line.tokensInLine[i]);
        }
        else if (line.tokensInLine[i].type == "delimiter")
        {
            for (int j = 0; j <= compiler.delimiters.size(); j++)
            {
                if (compiler.delimiters.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.delimiters[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_delimiters(line.tokensInLine[i]);
        }
        else if (line.tokensInLine[i].type == "other")
        {
            for (int j = 0; j <= compiler.others.size(); j++)
            {
                if (compiler.others.size() == 0)
                {
                    break;
                }
                else if (line.tokensInLine[i].text == compiler.others[j].text)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
                compiler.add_others(line.tokensInLine[i]);
        }
    }

}
void store_unique_tokens(Block& block, Compiler& compiler)
{
    for (int i = 0; i < block.linesInBlock.size(); i++)
    {
        unique_line_tokens(block.linesInBlock[i], compiler);
    }
    if (block.linesInBlock.empty())
        return;

}

int main(int argc, char *argv[])
{
    string fileName;
    switch (argc)
    {
        case 1:
            cout << "Please enter the name of the input file: " << endl;
            cin >> fileName;
            break;
        case 2:
            fileName = argv[1];
            break;
        default:
            cerr << "Too many command line arguments.";
            return -1;
    }

    ifstream inFile(fileName);
    if (!inFile)
    {
        cerr << "Unable to open file.";
        return -1;
    }



    Compiler compiledFile;
    Block tokenText = tokenize_text(inFile);
    store_unique_tokens(tokenText, compiledFile);
    compiledFile.print_keywords();
    compiledFile.print_identifiers();
    compiledFile.print_constants();
    compiledFile.print_operators();
    compiledFile.print_delimiters();

    stack<Token> analyzer;
    int forsInStack;
    int loopDepth = 0;

    for (int i = 0; i < tokenText.linesInBlock.size(); i++)
    {
        Line line = tokenText.linesInBlock[i];
        for (int j = 0; j < line.tokensInLine.size(); j++)
        {
            Token temp = line.tokensInLine[j];
            if (temp.text == "FOR")
            {
                analyzer.push(temp);
                forsInStack++;
            }
            else if (temp.text == "(" || temp.text == "BEGIN")
            {
                analyzer.push(temp);
            }
            else if (temp.text == ")")

            else if (temp.text == "END")
                completeForLoop(analyzer, forsInStack, loopDepth);


            else
                continue;

        }
    }
    print_stack(analyzer);
    cout << "The depth of the nested loop(s) is " << loopDepth << endl;
    if (!analyzer.empty())
        compiledFile.print_others();
    else
        cout << "\nSyntax Error(s): NA" << endl;
    return 0;
}