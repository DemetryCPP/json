#include <vector>
#include <string>
#include <map>
#pragma once

namespace JSON
{
    class UnexpectedToken
    {
    public:
        UnexpectedToken(size_t line, size_t column, std::string token)
            : line(line)
            , column(column)
            , token(token) {};


        size_t line;
        size_t column;
        std::string token;
    };

    enum class Type
    {
        Object,
        String,
        Number,
        Array,
        Bool,
        Null,
    };

    class Base
    {
    public:
        Base(Type type)
            : type(type) {};

        Type type;
    };

    class Object : public Base
    {
    public:
        Object() : Base(Type::Object) {};
        Object(std::map<std::string, Base *> fields)
            : fields(fields)
            , Base(Type::Object) {};

        std::map<std::string, Base *> fields;

        Base *operator[](std::string);
    };

    class String : public Base
    {
    public:
        String(std::string value)
            : value(value)
            , Base(Type::String) {};

        std::string value;
    };

    class Array : public Base
    {
    public:
        Array() : Base(Type::Array) {};
        Array(std::vector<Base *> elements)
            : elements(elements)
            , Base(Type::Array) {};

        std::vector<Base *> elements;

        Base *operator[](size_t);
    };

    class Number : public Base
    {
    public:
        Number(double value)
            : value(value)
            , Base(Type::Number) {};

        double value;
    };

    class Bool : public Base
    {
    public:
        Bool(bool value)
            : value(value)
            , Base(Type::Number) {};

        bool value;
    };

    class Null : public Base
    {
    public:
        Null() : Base(Type::Null) {};
    };

    Base *parse(std::string);
}