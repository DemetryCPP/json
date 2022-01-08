#include "parser.hpp"

using namespace std;
using namespace JSON;
using T = Token::Type;

Base *Parser::value()
{
    if (current()->value == "{") return object();
    if (current()->value == "[") return array();
    if (current()->type == T::String) return new String(match()->value);
    if (current()->type == T::Number) return new Number(stod(match()->value));
    if (current()->type == T::Word)
    {
        match();
        if (current()->value == "null")  return new Null();
        if (current()->value == "true")  return new Bool(true);
        if (current()->value == "false") return new Bool(false);
    }

    throw new UnexpectedToken(current()->line, current()->column, current()->value);
}

Object *Parser::object()
{
    match("{");

    if (current()->value != "}")
    {
        map<string, Base *> fields;

        fields.insert({ 
            match(T::String)->value,
            (match(":"), value())
        });
        

        while (current()->value == ",")
        {
            fields.insert({ 
                match(T::String)->value,
                (match(":"), value())
            });
        }

        match("}");
        return new Object(fields);
    }

    match("}");
    return new Object();
}

Array *Parser::array()
{
    match("[");

    if (current()->value != "]")
    {
        vector<Base *> elements;

        elements.push_back(value());
        while (current()->value != "]")
            elements.push_back(( match(","), value() ));

        match("]");
        return new Array(elements);
    }

    match("]");
    return new Array();
}

void Parser::match(string value)
{
    if (current()->value == value)
        match();
    else
        throw new UnexpectedToken(current()->line, current()->column, current()->value);
}

Token *Parser::match(Token::Type type)
{
    if (current()->type == type)
        return match();

    throw new UnexpectedToken(current()->line, current()->column, current()->value);
}

Token *Parser::match()
{ return tokens[index++]; }

Token *Parser::current()
{ return tokens[index]; }