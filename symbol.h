#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"
#include <string>

class Symbol {
    typedef std::string string;
    string _name;
    Type _type;

    public:
        bool _defined;
        Symbol(string name, const Type& type, bool defined = false);
        const string &name() const {
            return _name;
        };
        const Type &type() const {
            return _type;
        };
};

#endif