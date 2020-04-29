
#include <atomic>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "EasyWay.h"
#include "stdafx.h"

namespace {
//
// using namespace tmp_test6;
//
// void foo1() {
//  std::cout << "I am foo1" << endl;
//  foo2();
//}

}  // namespace

namespace tmp_test6 {
using std::cout;
using std::endl;
using std::exception;
using std::string;

void foo2() { std::cout << "I am foo[2]" << endl; }

void tmp01() {
  cout << "tmp01: call foo1." << endl;
  // foo1();
}

void init(int** d) { *d = new int(10); }

void tmp02() {
  int* p;
  init(&p);
  cout << "*p = " << *p << endl;
}

class A1 {
 public:
  A1() { cout << "A1 created." << endl; }

  ~A1() { cout << "A1 deleted." << endl; }
};

void tmp03() {
  cout << "1 . ------------" << endl;
  A1* a = new A1();
  cout << "2 . ------------" << endl;

  auto deletor = [](A1* a) {
    cout << "deletor called." << endl;
    delete a;
  };

  {
    cout << "create unique_ptr" << endl;
    unique_ptr<A1, std::function<void(A1*)>> p{a, deletor};
    cout << "delete unique_ptr" << endl;
  }

  cout << "3 . ------------" << endl;

  A1* tmp = nullptr;

  unique_ptr<A1, std::function<void(A1*)>> p1{nullptr, deletor};
  {
    cout << "create A1" << endl;
    A1* b = new A1();
    cout << "4 . ------------" << endl;
    p1.reset(b);
    cout << "delete unique_ptr" << endl;
  }
  cout << "5 . ------------" << endl;

  cout << "tmp03 finished." << endl;
}

struct A04 {
  int a = 10;
  string b = "ccc";

  ~A04() = delete;
};

void shutdown(A04* data) {
  cout << "shutdown 01" << endl;
  data->a = -1;
  data->b = "";
}

unique_ptr<A04, function<void(A04*)>> point{nullptr, shutdown};

void tmp04() {
  cout << " BEGIN tmp04" << endl;

  // auto func = [](A04* data) {
  //  cout << "shutdown 01" << endl;
  //  data->a = -1;
  //  data->b = "";
  //};

  A04* a1 = new A04();
  point.reset(a1);

  cout << " DONE tmp04" << endl;
}

void changeRef(string& data) {
  data = "changed value.";
  // cout << data << endl;
}

void tmp05() {
  string v{"A"};

  cout << "v:" << v << endl;
  changeRef(v);
  cout << "v:" << v << endl;
}

void tmp06() {
  char c = 'x';

  unsigned char d = c;

  cout << "c as char [" << c << "]" << endl;
  cout << "c as int [" << (int)c << "]" << endl;
  cout << "c as d [" << d << "]" << endl;
}

void tmp07() {
  shared_ptr<A04> p;

  if (p == nullptr) {
    cout << "p is nullptr" << endl;
  } else {
    cout << "p not nullptr" << endl;
  }

  // shared_ptr<A04> q = std::make_shared<A04>();
  // if (q == nullptr) {
  //  cout << "q is nullptr" << endl;
  //} else {
  //  cout << "q not nullptr" << endl;
  //}
}

void tmp08() {
  std::stringstream ss{};
  string target = R"(a
b

c

  

    


d




e
       


)";
  string line;
  int c;
  c = 0;

  ss << target;
  while (std::getline(ss, line)) {
    cout << "line [" << c++ << "] : [" << line << "]" << endl;
  }
  cout << "==============" << endl;

  // std::regex blankRe{R"(\s+)"};

  std::regex emptyLine{R"(^[ \t]+$)"};
  target = std::regex_replace(target, emptyLine, "");

  std::regex fourEmptyLine{R"(\n{5,})"};
  target = std::regex_replace(target, fourEmptyLine, "\n\n\n\n");

  ss.clear();
  ss << target;
  c = 0;
  while (std::getline(ss, line)) {
    cout << "line [" << c++ << "] : [" << line << "]" << endl;
  }
}

string removeLastEmptyLines(const string& target) {
  size_t len = target.length();
  size_t i = len-1;
  for (; i > 0; i--) {
    if (target[i] == '\n') {
      continue;
    } else if(target[i] == '\r') {
      continue;
    } else {
      break;
    }
  }
  return target.substr(0, i+1);
}

void tmp09() {
  string target = R"(a
b
c
d


)";

  stringstream ss;
  string line;
  int c;
  c = 0;

  target = removeLastEmptyLines(target);

  ss << target;
  while (std::getline(ss, line)) {
    cout << "line [" << c++ << "] : [" << line << "]" << endl;
  }
  cout << "==============" << endl;
}

string getChars1(const string& path) {
  static string base = "/baseUrl/";
  string rst = base + path;
  return rst;
}

const char* getChars2(const string& path) {
  static string base = "/baseUrl/";
  static string rst = base + path;
  return rst.c_str();
}

void tmp10() {
  
  std::vector<const char*> vec{"aa", "bb", "cc", "dd", "1aa", "1bb", "1cc", "1dd", };

  for(auto& s: vec) {
    cout << "before: " << s << endl;
    s =  getChars2(s);
    cout << "after: " << s << endl;
  }
  cout << "==============================" << endl;
  for(auto s: vec) {
    cout << "final: " << s << endl;
  }

}

void tmp11() {
  string a = "a";
  string b = "abcdef";
  cout << "a==b: " << (a == b) << endl;

  a += "bcdef";
  cout << "a==b: " << (a == b) << endl;

}

}  // namespace tmp_test6

void tmpTest6() {
  using namespace tmp_test6;
  tmp11();
}
