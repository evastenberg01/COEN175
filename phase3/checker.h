# ifndef CHECKER_H
# define CHECKER_H

# include <cstdlib>
# include <iostream>
# include <string>
# include <set>
# include "type.h"

typedef std::string string;

void openScope();
void closeScope();

void declareFunction(const std::string &name, const Type &type);
void defineFunction(const std::string &name, const Type &type);
void declareVariable(const std::string &name, const Type &type);
void checkIdentifier(const std::string &name);

# endif 