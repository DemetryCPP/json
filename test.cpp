#include <iostream>
#include "JSON.hpp"

using namespace JSON;

int main(int argc, char const *argv[])
{
    try {
        auto object = parse<Object>("{\"huita\":12}");
        auto num = object->get<Number>("huita");
        cout << num << endl;
    } catch (UnexpectedToken *e) {
        cout << "Unexpected token " + e->token
             << " at " << e->line << ":" << e->column << endl;
    }
    return 0;
}