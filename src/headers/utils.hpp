#include <algorithm>
#include <iostream>
#pragma once

#define enlist(x) std::begin(x), std::end(x)

template<class B, class E, class Elem>
bool contains(const B& begin, const E& end, const Elem& elem)
{ return std::find(begin, end, elem) != end; }

template<class C, class Elem>
bool contains(const C& container, const Elem& elem)
{ return contains(enlist(container), elem); }