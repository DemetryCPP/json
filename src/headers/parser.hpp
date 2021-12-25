#include "lexer.hpp"
#include "JSON.hpp"
#pragma once

class Parser
{
private:
    void   match(std::string);
    Token *match(Token::Type);
    Token *current();
    Token *match();

    size_t index = 0;

public:
    Parser(std::vector<Token *> tokens) 
        : tokens(tokens) {};

    JSON::Base *value();

    JSON::Object *object();
    JSON::Array  *array();

    std::vector<Token *> tokens;
};