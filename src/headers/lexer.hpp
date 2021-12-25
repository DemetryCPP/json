#include <string>
#include <vector>
#pragma once

class Token
{
public:
    enum class Type
    {
        Special,
        String,
        Number,
        Word,
        Null,
    };

    Token(size_t line, size_t column)
        : Token(line, column, "", Type::Null) {};
    Token(size_t line, size_t column, char value, Type type)
        : Token(line, column, std::string(1, value), type) {};
    Token(size_t line, size_t column, std::string value, Type type)
        : line(line)
        , column(column)
        , value(value)
        , type(type) {};

    Type type;
    size_t line;
    size_t column;
    std::string value;

    void log() const;
};

class Lexer
{
private:
    Token *next();

    Token *single();
    Token *number();
    Token *str();
    Token *word();

    void skipSpaces();

    char current();
    char match();

    bool isNumber();
    bool isText();
    bool isVoid();

    size_t index = 0;
    size_t line = 1;
    size_t column = 1;

public:
    Lexer(std::string code);

    std::string code;
    std::vector<Token *> tokens;
};