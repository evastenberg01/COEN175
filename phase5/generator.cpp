#include "Tree.h"
#include "generator.h"
#include "Type.h"
#include <iostream>
#include <cassert>


using namespace std;
int caller_size = 0;

static ostream &operator <<(ostream &ostr, Expression *expr) {
  expr->operand(ostr);
  return ostr;
}

void Block::generate() {
  for (auto stmt:_stmts)
    stmt->generate();
}

void Simple::generate() {
  _expr->generate();
}

void Expression::operand(ostream &ostr) 
{
}

void Number::operand(ostream &ostr) {
  ostr << "$" << _value;
}

void Identifier::operand(ostream &ostr) {
  int offset = _symbol->offset;
  if(offset==0) {
    cout << _symbol->name();
  }
  else {
    cout << offset << "(%rbp)";
  }
}

void generateGlobals(Scope *scope) {
  Symbols symbols = scope->symbols();
  for (auto symbol:symbols) {
    if (!symbol->type().isFunction() && !symbol->type().isError())
      cout << ".comm " << symbol->name() << ", " << symbol->type().size() << endl;
  }
}

void Function::generate() {
  int bytes = 0;
  caller_size = 0;
  int offsetCounter = 8;

  string functionName = _id->name();
  unsigned paramSize = _id->type().parameters()->size();
  Symbols symbols = _body->declarations()->symbols();

  for (unsigned i = 0; i < paramSize; ++i) {
    symbols[i]->offset = offsetCounter;
    offsetCounter = offsetCounter + symbols[i]->type().size();
    while (offsetCounter%16 != 0)
      offsetCounter++;
  }

  offsetCounter = 0;

  for (unsigned i = paramSize; i < symbols.size(); ++i) {
    offsetCounter = offsetCounter - symbols[i]->type().size();
    symbols[i]->offset = offsetCounter;
    while (offsetCounter%16 != 0)
      offsetCounter--;
  }

  bytes = bytes - offsetCounter;

  while(bytes%16 != 0) {
    ++bytes;
  }
  
  //prologue
  cout << ".globl " << functionName << endl;
  cout << functionName << ": pushq\t%rbp" << endl;
  cout << "movq %rsp,\t%rbp" << endl;
  cout << "subq $" << -(offsetCounter) << ",\t%rsp" << endl;

  //spill
  cout << "movl %edi," << _id->type().parameters() << offsetCounter <<"\t(%rbp)" << endl;
  cout << "movl %esi," << _id->type().parameters() << offsetCounter <<"\t(%rbp)" << endl;

  _body->generate();
  
  //epilogue
  cout << "movq %rbp,\t%rsp" << endl;
  cout << "popq %rbp" << endl;
  cout << "ret" << endl;
}

void Assignment::generate() {
  cout << "movl " << _right << ", " << _left << endl;
}

void Call::generate() {
 
  int offsetCounter = 0;
  for (auto arg:_args) {
    cout << "movl " << arg << ", %eax" << endl;
    cout << "movl " << "%eax, " << offsetCounter << "(%esp)" << endl;
    offsetCounter = offsetCounter + arg->type().size();
    while (offsetCounter%16 != 0)
      offsetCounter++;
  }

  cout << "call " << _id->name() << endl;

  if (caller_size < offsetCounter) {
    caller_size = offsetCounter;
  }

}