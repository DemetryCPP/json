#include <vector>
#include <string>
#include <map>
#pragma once

namespace JSON
{
    using namespace std;

    struct UnexpectedToken
    {
        UnexpectedToken(size_t line, size_t column, string token)
            : line(line)
            , column(column)
            , token(token) {};

        size_t line, column;
        string token;
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

    struct Base
    { Type type; };

    struct Object : Base
    {
        Object() : Base{Type::Object} {};
        Object(map<string, Base *> fields)
            : fields(fields)
            , Base{Type::Object} {};

        map<string, Base *> fields;

        template<class T> T *get(string s)
        { return static_cast<T *>(fields[s]); }
    };

    struct String : Base
    {
        String(string value)
            : value(value)
            , Base{Type::String} {};

        string value;
    };

    struct Array : Base
    {
        Array() : Base{Type::Array} {};
        Array(vector<Base *> elements)
            : elements(elements)
            , Base{Type::Array} {};

        vector<Base *> elements;

        template<class T> T *get(size_t s)
        { return static_cast<T *>(elements[s]); }
    };

    struct Number : Base
    {
        Number(double value)
            : value(value)
            , Base{Type::Number} {};

        double value;
    };

    struct Bool : Base
    {
        Bool(bool value)
            : value(value)
            , Base{Type::Number} {};

        bool value;
    };

    struct Null : Base
    { Null() : Base{Type::Null} {}; };

    Base *parse(string);

    template<class T> T *parse(string s)
    { return static_cast<T *>(parse(s)); }
}