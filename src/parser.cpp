#include "parser.hpp"

using namespace std;

JSON::Base *Parser::value()
{
    if (current()->value == "{") return object();
    if (current()->value == "[") return array();
    if (current()->type == Token::Type::String) return new JSON::String(match()->value);
    if (current()->type == Token::Type::Number) return new JSON::Number(std::stod(match()->value));
    if (current()->type == Token::Type::Word)
    {
        match();
        if (current()->value == "null")  return new JSON::Null();
        if (current()->value == "true")  return new JSON::Bool(true);
        if (current()->value == "false") return new JSON::Bool(false);
    }

    throw new JSON::UnexpectedToken(current()->line, current()->column, current()->value);
}

JSON::Object *Parser::object()
{
    match("{");

    if (current()->value != "}")
    {
        map<std::string, JSON::Base *> fields;

        fields.insert({ 
            match(Token::Type::String)->value,
            (match(":"), value())
        });
        

        while (current()->value == ",")
        {
            fields.insert({ 
                match(Token::Type::String)->value,
                (match(":"), value())
            });
        }

        match("}");
        return new JSON::Object(fields);
    }

    match("}");
    return new JSON::Object();
}

JSON::Array *Parser::array()
{
    match("[");

    if (current()->value != "]")
    {
        vector<JSON::Base *> elements;

        elements.push_back(value());
        while (current()->value != "]")
            elements.push_back((match(","), value()));

        match("]");
        return new JSON::Array(elements);
    }

    match("]");
    return new JSON::Array();
}

void Parser::match(std::string value)
{
    if (current()->value == value)
        match();
    else
        throw new JSON::UnexpectedToken(current()->line, current()->column, current()->value);
}

Token *Parser::match(Token::Type type)
{
    if (current()->type == type)
        return match();

    throw new JSON::UnexpectedToken(current()->line, current()->column, current()->value);
}

Token *Parser::match()
{ return tokens[index++]; }

Token *Parser::current()
{ return tokens[index]; }