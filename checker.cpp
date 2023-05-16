# include "scope.h"
# include "lexer.h"
# include "checker.h"
# include "type.h"
# include "symbol.h"
# include "tokens.h"
# include <iostream>

using namespace std;
typedef std::string string;

static string e1 = "redefinition of '%s'";
static string e2 = "conflicting types for '%s'";
static string e3 = "redeclaration of '%s'";
static string e4 = "'%s' undeclared";
static string e5 = "'%s' has type void";
static Scope *global = nullptr;
static Scope *current;


void openScope() {
    cout << "open scope" << endl;
    current = new Scope(current);;
    if(global == nullptr) {
        global = current;
    }
}

void closeScope() {
    cout << "close scope" << endl;
    current = current->enclosing();
}

void declareFunction(const std::string &name, const Type &type) {
    
    cout << "declare " << name << " as (" << type.specifier() << ", " << type.indirection() << ", FUNCTION)" << endl;
    Symbol *symbol = global->find(name);
    if(symbol == nullptr) {
        symbol = new Symbol(name, type);
        global->insert(symbol);  
    }
    else if(symbol->type() != type) {
        report(e2, name);
    }
    else if(symbol->_defined) {
        report(e1, name);
    }
}

void defineFunction(const std::string &name, const Type &type) {
    Symbol *symbol = global->find(name);
    //symbol = new Symbol(name, type);
    if(symbol != nullptr) {
        global->remove(name);
        if(symbol->type().parameters() != nullptr) {
            report(e1, name);
        }
        // cout << "define " << name << " as " << type << endl;
        else if(symbol->type() != type) {
            report(e2, name);
        }
    }
   
    global->insert(new Symbol(name, type));
}

void declareVariable(const std::string &name, const Type &type) {
    
    cout << name << ": " << type << endl;
    Symbol *symbol = current->find(name);
    
    if(symbol == nullptr) {
        if (type.specifier() == VOID && type.indirection() == 0) {
            report(e5, name);
            return;
        }
        symbol = new Symbol(name, type);
        current->insert(symbol);
    }
    else if(current->enclosing() != nullptr) {
        report(e3, name);
    }
    else if(symbol->type() != type) {
        report(e2, name);
    }
}

void checkIdentifier(const std::string &name) {
    
    Symbol *symbol = current->find(name);
    
    if(symbol == nullptr) {
        Symbol *symbol = current->lookup(name);
        if(symbol == nullptr)
            report(e4, name);

    }
}