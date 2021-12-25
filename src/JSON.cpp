#include <iostream>
#include "parser.hpp"

using namespace JSON;
using namespace std;

Base *JSON::parse(std::string expr)
{
    Lexer *lexer = new Lexer(expr);
    Parser *parser = new Parser(lexer->tokens);

    return parser->value();
}