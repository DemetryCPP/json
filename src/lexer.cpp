#include "utils.hpp"
#include "lexer.hpp"
#include "JSON.hpp"

using namespace std;

Token *Lexer::next()
{
    if (index >= code.length())
        return new Token(line, column);

    skipSpaces();

    if (current() == '"') return str();
    if (isNumber())       return number();
    if (isText())         return word();
    
    return single();
}

Token *Lexer::single()
{
    if (contains(enlist("{}[],:"), current()))
        return new Token(line, column, match(), Token::Type::Special);

    throw new JSON::UnexpectedToken(line, column, std::string(1, current()));   
}

Token *Lexer::number()
{
    string buffer;
    bool isDouble = false;

    size_t line = this->line,
         column = this->column;

    while (isNumber())
    {
        if (current() == '.')
            if (isDouble) throw new JSON::UnexpectedToken(line, column, ".");
            else isDouble = true;
        buffer += match();
    }

    return new Token(line, column, buffer, Token::Type::Number);
}

Token *Lexer::str()
{
    std::string buffer;

    size_t line = this->line,
         column = this->column;

    if (current() == '"')
        match();

    while (current() != '"')
        buffer += match();

    match();

    return new Token(line, column, buffer, Token::Type::String);
}

Token *Lexer::word()
{
    std::string buffer;

    size_t line = this->line,
         column = this->column;

    while (isText())
        buffer += match();

    if (buffer != "true"
     && buffer != "false"
     && buffer != "null")
        throw new JSON::UnexpectedToken(line, column, buffer);

    return new Token(line, column, buffer, Token::Type::Word);    
}

void Lexer::skipSpaces()
{
    while (isVoid())
        match();
}

bool Lexer::isNumber()
{
    return current() >= '0'
        && current() <= '9'
        || current() == '.';
}

bool Lexer::isText()
{
    return current() >= 'a'
        && current() <= 'z'
        || current() >= 'A'
        && current() <= 'Z';
}

bool Lexer::isVoid()
{ return current() <= ' '; }

char Lexer::current()
{ return code[index]; }

char Lexer::match()
{
    column++;
    if (current() == '\n')
    {
        line++;
        column = 1;
    }

    return code[index++];
}

void Token::log() const
{
    std::string types[] = {
        "[ Special  ]",
        "[  String  ]",
        "[  Number  ]",
        "[   Word   ]",
        "[   Null   ]",
    };

    cout << types[(int)type] << " " << value << std::endl;
}

Lexer::Lexer(std::string code) : code(code)
{ 
    Token *newToken = next();
    while (newToken->type != Token::Type::Null)
    {
        tokens.push_back(newToken);
        // newToken->log();
        newToken = next();
    }
};