#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <ostream>
#include <cassert>

typedef std::vector<class Type> Parameters;

class Type {
    int _specifier;
    unsigned _indirection;
    unsigned long _length;
    Parameters *_parameters;

    enum Declarator {
        ARRAY,
        ERROR,
        FUNCTION,
        SCALAR
    }_declarator;

    public:
        Type(int specifier, unsigned indirection = 0);
        Type(int specifier, unsigned indirection, unsigned long length);
        Type(int specifier, unsigned indirection, Parameters *parameters);
        Type();


        bool isArray()const{
            return _declarator == ARRAY;
        };
        int specifier()const{
            return _specifier;
        };
        bool isFunction() const{
            return _declarator == FUNCTION;
        };
        bool isScalar() const{
            return _declarator == SCALAR;
        };
        bool isError() const{
            return _declarator == ERROR;
        };

        unsigned indirection() const{
            return _indirection;
        };
        unsigned long length() const{
            assert(_declarator == ARRAY);
            return _length;
        };
        Parameters *parameters() const {
            return _parameters;
        };

        Declarator declarator() const {
            return _declarator;
        };

        bool operator ==(const Type &rhs) const;
        bool operator !=(const Type &rhs) const;

};

// Type t;
// Type integer(int);
std::ostream &operator << (std::ostream &ostr, const Type &t);

#endif
