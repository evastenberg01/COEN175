#ifndef SCOPE_H
#define SCOPE_H

#include <string>
#include <vector>
#include "type.h"
#include "symbol.h"

typedef std::vector<Symbol *> Symbols;

class Scope {
    typedef std::string string;
    Scope *_enclosing;
    Symbols _symbols;

    public:
        Scope(Scope *enclosing = nullptr);
        void insert(Symbol *symbol);
        void remove(const string &name);
        Symbol *find(const string &name) const;
        Symbol *lookup(const string &name) const;
        Scope *enclosing() const {
            return _enclosing;
        };
        const Symbols &symbols() const {
            return _symbols;
        };

};

#endif
