//
// Created by hunter on 6/29/19.
//

#ifndef BIPL_MEMORY_H
#define BIPL_MEMORY_H

#include <map>
#include <set>
#include <stack>
#include <vector>

class Memory {
public:
  Memory();
  std::string get(std::string var);
  std::string getstring(std::string var);
  bool getboolean(std::string var);
  double getnum(std::string var);
  std::vector<std::string> getfn(std::string var);
  bool functioninuse(std::string val);
  void createfunction(std::string name, std::vector<std::string> code);
  void createboolean(std::string name, bool value);
  void createnum(std::string name, double num);
  void createstring(std::string name, std::string str);
  bool boolexists(std::string var);
  bool strexists(std::string var);
  bool numexists(std::string var);
  bool varexists(std::string var);
  void enterfn();
  void enterfn(std::vector<std::string> parameters,
               std::vector<std::string> fndefinition);
  void leavefn();

private:
  std::string getType(std::string var);

  double strtonum(std::string);
  bool strtobool(std::string);
  std::string strtostr(std::string);

  std::stack<std::map<std::string, bool>> booleans;
  std::stack<std::map<std::string, double>> nums;
  std::stack<std::map<std::string, std::string>> strings;
  std::map<std::string, std::vector<std::string>> functions;

  std::set<std::string> functionnamespace;
  std::stack<std::map<std::string, std::string>> variabletypes;
};

#endif // BIPL_MEMORY_H
