//
// Created by hunter on 6/29/19.
//

#ifndef BIPL_INTERPRETER_H
#define BIPL_INTERPRETER_H

#include "Memory.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

typedef double num;

class Interpreter {
public:
  Interpreter() = delete;
  Interpreter(std::string filename);

private:
  // helper functions
  void interpret();
  std::string eval(std::string value);
  std::vector<std::string> split(std::string str, char delim = ' ');
  bool isString(std::string val);
  int strtoint(std::string num);
  num strtonum(std::string num);
  bool strtobool(std::string val);
  std::string strtostr(std::string);
  std::string removequotes(std::string original);
  bool isParens(std::string statement);
  std::string removeparens(std::string original);
  bool isNumber(std::string value);
  bool isBoolean(std::string value);
  std::string normalizenumber(num x);
  std::string normalizebool(bool x);
  std::vector<bool> parameterstobool(std::vector<std::string> vals);
  std::vector<num> parameterstonums(std::vector<std::string> vals);
  std::vector<std::string> evalParameters(std::vector<std::string> vals);

  // command functions for the interpreting
  void printcode();
  void quit(std::vector<std::string> vals);
  void print(std::vector<std::string> vals);
  void println(std::vector<std::string> vals);
  void declarestring(std::vector<std::string> vals);
  void declareboolean(std::vector<std::string> vals);
  void declarenum(std::vector<std::string> vals);
  std::string read(std::vector<std::string> vals);
  std::string ifstatement(std::vector<std::string> vals);

  // function functions
  void define(std::vector<std::string> vals);
  std::string call(std::vector<std::string> vals);

  // Math functions
  num add(std::vector<std::string> vals);
  num sub(std::vector<std::string> vals);
  num mul(std::vector<std::string> vals);
  num div(std::vector<std::string> vals);

  // logic functions
  bool andfunc(std::vector<std::string> vals);
  bool orfunc(std::vector<std::string> vals);
  bool notfunc(std::vector<std::string> vals);
  bool nandfunc(std::vector<std::string> vals);
  bool norfunc(std::vector<std::string> vals);
  bool xorfunc(std::vector<std::string> vals);
  bool xnorfunc(std::vector<std::string> vals);

  // Equality functions
  int comparison(std::vector<std::string> vals);

  // memory
  std::vector<std::string> code;
  Memory memory;
};

#endif // BIPL_INTERPRETER_H
