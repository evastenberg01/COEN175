#include <cassert>
#include "type.h"
#include "tokens.h"

using namespace std;

Type::Type()
	:_declarator(ERROR)
{
}

Type::Type(int specifier, unsigned indirection)
	:_specifier(specifier), _indirection(indirection), _declarator(SCALAR)
{
}

Type::Type(int specifier, unsigned indirection, unsigned long length)
	:_specifier(specifier), _indirection(indirection), _length(length), _declarator(ARRAY)
{
}

Type::Type(int specifier, unsigned indirection, Parameters *parameters)
	:_specifier(specifier), _indirection(indirection), _parameters(parameters), _declarator(FUNCTION)
{
}

bool Type::operator ==(const Type &rhs) const { 
	if(_declarator != rhs._declarator)    
		return false;
	if(_declarator == ERROR)
		return true;
	if(_specifier != rhs._specifier)
		return false;
	if(_indirection != rhs._indirection)
		return false;
	if(_declarator == SCALAR)
		return true;
	if(_declarator == ARRAY)
		return _length == rhs._length;
	assert(_declarator == FUNCTION);
	if(!_parameters || !rhs._parameters)
		return true;
	return *_parameters == *rhs._parameters;
}

bool Type::operator !=(const Type &rhs) const { 
	return !operator==(rhs);
}

std::ostream &operator <<(std::ostream &ostr, const Type &type) {
	ostr << "typespec: " << type.specifier() << "indirection: " << type.indirection() << "type: " << type.declarator() << endl;
	return ostr;
}
