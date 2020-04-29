#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace tmp_test5 {
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

void tmp01() {
  auto s1 = R"(hello, "My little world ".)";
  string s2 = R"(hello, "My little world ".)";
  const char* s3 = R"(hello, "My %s".)";
  // cout << R"(I print '\', "\n" as I like.)" << endl;
  // cout << "hello test5" << endl;

  cout << "s1:\t" << s1 << endl;
  cout << "s2:\t" << s2 << endl;
  cout << "s3:\t" << s3 << endl;

  char buf[1024];
  auto r1 = snprintf(buf, 1024, s3, "darling");

  cout << "buf:" << buf << endl;
  cout << "r1:" << r1 << endl;
}

constexpr int myStrLen(const char* str) {
  int i = 0;
  if (str != nullptr) {
    while (str[i] != 0) {
      if (i > 100000) {
        return -1;
      } else {
        i++;
      }
    }
  }

  return i;
}

void tmp02() {
  constexpr char s1[] = "1234567";
  // constexpr auto r = myStrLen(s1);
  constexpr auto r = sizeof(s1);

  cout << "r: " << r << endl;
}

class Test03 {
 public:
  static int a;
  static unordered_map<string, string> templateMap;

  static void init() {
    cout << "init" << endl;
    a = 10;
  }

  static void check();
};

int Test03::a = 1;
unordered_map<string, string> Test03::templateMap{};

void Test03::check() {
  if (templateMap.empty()) {
    cout << "templateMap != nullptr" << endl;
  }
}

void tmp03() {
  Test03::init();
  Test03::check();

  cout << Test03::a << endl;
}

void tmp04() {
  const string fpath = "textData1.txt";
  std::ifstream is{fpath};
  if (!is.is_open()) {
    cout << "can not open file:\t" << fpath << endl;
  }

  string lineStr;
  int i = 0;
  while (std::getline(is, lineStr)) {
    cout << i++ << "\t:" << lineStr.length() << "\t:" << lineStr << endl;
  }
}

void tmp05() {
  std::string text = "{{name}} for brown fox";
  // std::regex re1("(\\{\\{) (.*) (\\}\\})");

  string reStr = R"(\{\{name\}\})";
  cout << "reStr:" << reStr << endl;

  std::regex re2(reStr);

  std::string replaceResult = std::regex_replace(text, re2, "Tao");

  cout << "replaceResult: " << replaceResult << endl;

  string target2{"hahah, hahahha\t\t, hell\t  o, wor   l\t \td."};
  std::regex blankRe{R"(\s+)"};

  auto rst2 = std::regex_replace(target2, blankRe, "");
  cout << "rst2: [" << rst2 << "]" << endl;
}

class SingleClass {
  SingleClass() { cout << "SingleClass constructed." << endl; };

 public:
  static SingleClass& getInstance() {
    static SingleClass instance;
    return instance;
  }
  SingleClass(const SingleClass&) = delete;
  SingleClass& operator=(const SingleClass&) = delete;
  ~SingleClass() { cout << "SingleClass destructed." << endl; }
  void say() { cout << "hello, world." << endl; };
};

void tmp06() {
  auto& s1 = SingleClass::getInstance();
  auto& s2 = SingleClass::getInstance();
  auto& s3 = SingleClass::getInstance();
  s1.say();
}

std::vector<string> split(const string& target, const string& sp) {
  std::vector<string> rst{};
  const auto spLen = sp.length();
  string::size_type pos = 0;
  auto f = target.find(sp, pos);
  if (f == string::npos) {
    rst.emplace_back(target);
  } else {
    while (f != string::npos) {
      auto r = target.substr(pos, f - pos);
      rst.emplace_back(r);
      cout << "got [" << r << "] \tpos=" << pos << "\tf=" << f
           << "\tspLen=" << spLen << endl;

      pos = f + spLen;
      f = target.find(sp, pos);
    }
  }
  return rst;
}

void tmp07() {
  string s1 = "aaaaa";
  auto rst = split(s1, ", ");

  cout << "result:" << endl;

  for (auto& s : rst) {
    cout << "s:" << s << endl;
  }
}

struct Bar8 {
  string d;
  Bar8(string d_) : d(d_) { cout << "create Bar8[" << d << "]" << endl; }

  Bar8(const Bar8& o) : d(o.d) { cout << "copy Bar8[" << d << "]" << endl; }

  Bar8& operator=(const Bar8& o) {
    d = o.d;
    cout << "assign Bar8[" << d << "]" << endl;
    return *this;
  }

  Bar8(Bar8&& o) noexcept : d(o.d) {
    o.d = "";
    cout << "move Bar8[" << d << "]" << endl;
  }

  ~Bar8() { cout << "destructed Bar8[" << d << "]" << endl; }
};

Bar8 getBar8() {
  auto t = Bar8("XXX");
  return t;
}

std::vector<Bar8> getVec() {
  std::vector<Bar8> rst{};
  rst.emplace_back(Bar8("AA"));
  rst.emplace_back(Bar8("BB"));
  return rst;
};

void tmp08() {
  auto b = getBar8();

  cout << " ------------- \n\n" << endl;

  auto rst = getVec();

  for (auto& r : rst) {
    cout << "r:" << r.d << endl;
  }

  cout << " ------------- \n\n" << endl;
}

void tmp09() {
  unordered_map<string, int> data{};

  data.emplace("A", 1);
  data.emplace("B", 2);
  data.emplace("C", 3);
  data.insert({"B", 9999});
  data.emplace("B", 9999);
  data.insert_or_assign("C", 999);

  for (auto& d : data) {
    cout << "d:" << d.first << "," << d.second << endl;
  }

  auto r1 = data["X"];
  cout << "r1:" << r1 << endl;

  auto r2 = data["A"];
  cout << "r2:" << r2 << endl;

  auto r3 = data.at("B");
  cout << "r3:" << r3 << endl;

  auto f1 = data.find("T");
  if (f1 != data.end()) {
    cout << "find f1: " << f1->first << "," << f1->second << endl;
  } else {
    cout << "not find f1 " << endl;
  }

  // auto r4 = data.at("YY");
  // cout << "r4:" << r4 << endl;
}

void tmp10() {
  // test std::transform
  std::vector<int> v1{};
  std::vector<string> v2{};

  v1.push_back(5);
  v1.push_back(4);
  v1.push_back(3);

  std::transform(v1.begin(), v1.end(), std::back_inserter(v2),
                 [](const int& i) -> string {
                   std::stringstream ss;
                   ss << "data[" << i << "]";
                   return ss.str();
                 });

  for (auto& i : v1) {
    cout << "i: " << i << endl;
  }

  cout << "------------------" << endl;
  for (auto& s : v2) {
    cout << "s: " << s << endl;
  }
}

void tmp11() {
  string target = R"(
lalalalk
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <meta charset="UTF-8" />
  <title>BasePage</title>
  <link type="text/css" rel="styleSheet" href="CSS文件路径" />
</head>
<body style="background:black; color:white">
  <div>
    <h1>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <meta charset="UTF-8" />
  <title>BasePage</title>
  <link type="text/css" rel="styleSheet" href="CSS文件路径" />
</head>
<body style="background:black; color:white">
  <div>
    <h1>
<!--@title[-->我是用中文占位符<!--]title@-->
lalalalala
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <meta charset="UTF-8" />
  <title>BasePage</title>
  <link type="text/css" rel="styleSheet" href="CSS文件路径" />
</head>
<body style="background:black; color:white">
  <div>
    <h1>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <meta charset="UTF-8" />
  <title>BasePage</title>
  <link type="text/css" rel="styleSheet" href="CSS文件路径" />
</head>
<body style="background:black; color:white">
  <div>
    <h1>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
  <meta charset="UTF-8" />
  <title>BasePage</title>
  <link type="text/css" rel="styleSheet" href="CSS文件路径" />
</head>
<body style="background:black; color:white">
  <div>
    <h1>
)";
  string reStr = "<!--@title\\[-->.{0,1024}<!--\\]title@-->";
  std::regex reg{reStr};

  cout << "compile regex." << endl;

  auto out = std::regex_replace(target, reg, "hello, world.");

  cout << out << endl;
}

void tmp12() {

  std::string target = "abcdefg12345xyz";
  std::string b = "1236";
  auto r = target.find(b);

  cout << "r: " << r << endl;
  cout << "r == npos: " << (r == string::npos) << endl;
  cout << "npos: " << string::npos << endl;

}

}  // namespace tmp_test5

void tmpTest5() {
  using namespace tmp_test5;

  tmp12();
}
