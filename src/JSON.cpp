#include <iostream>
#include "parser.hpp"

using namespace JSON;
using namespace std;

Base *JSON::parse(std::string expr)
{
    auto lexer = new Lexer(expr);
    auto parser = new Parser(lexer->tokens);

    return parser->value();
}