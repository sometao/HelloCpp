#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

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
    cout << i++ << "\t:" << lineStr << endl;
  }

}

void tmp05() {
  //正则表达式
}

}  // namespace tmp_test5

void tmpTest5() {
  using namespace tmp_test5;
  tmp04();
}
