#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "EasyWay.h"
#include "stdafx.h"

namespace tmp_test3 {
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

class C01 {
 public:
  C01() = default;
  C01(const C01& c) = default;
  C01(C01&& c) noexcept = default;
  C01& operator=(const C01& c) = default;
  string data = "C01";
};

class C01a {
 public:
  C01a() { cout << "C01a default constructor." << endl; };

  C01a(const string& a) : data(a) {
    cout << "C01a string constructor." << endl;
  };

  C01a(const C01a& c) {
    cout << "C01a copy constructor: data=" << c.data << endl;
    data = c.data;
  };

  C01a(C01a&& c) noexcept {
    cout << "C01a move constructor. data=" << c.data << endl;
    data = c.data;
    c.data = "";
  };

  // not a constructor, so it must be construted before assigning a new value.
  C01a& operator=(const C01a& c) {
    cout << "C01a assign constructor. data[" << data << "] to [" << c.data
         << "]" << endl;
    this->data = c.data;
    return *this;
  };

  ~C01a() { cout << "C01a Destructor: data=" << data << endl; };

  string data = "C01a";
};

void tmp01() {
  cout << "----------  1  ------------" << endl;
  C01a c{"hello"};
  cout << "----------  2  ------------" << endl;
  C01a c1 = c;
  cout << "----------  2a  ------------" << endl;
  C01a c1a{"hi"};
  c1a = c;
  cout << "----------  3  ------------" << endl;
  auto c2{c};
  cout << "----------  4  ------------" << endl;
  auto c3{std::move(c)};
  cout << "----------  5  ------------" << endl;
};

class C02 {
 public:
  C01a data1;
  C02(C01a& d) : data1(d) { cout << "C02 default 1 constructor." << endl; };

  C02(C01a&& d) : data1(std::move(d)) {
    cout << "C02 default 2 constructor." << endl;
  };
};

void tmp02() {
  C02* c02 = nullptr;
  {
    cout << " -------------------  1  ------------------" << endl;
    C01a d{"Hello"};
    cout << " -------------------  2  ------------------" << endl;
    // C02 t{ std::move(d) };
    cout << "[" << &d << "]" << endl;
    C02 t{d};
    cout << "[" << &(t.data1) << "]" << endl;
    cout << " -------------------  3  ------------------" << endl;
    c02 = &t;
    cout << "[" << &(c02->data1.data) << "]" << endl;
    cout << " -------------------  4  ------------------" << endl;
    cout << "[" << d.data << "]" << endl;
    cout << "[" << t.data1.data << "]" << endl;
    cout << "[" << c02->data1.data << "]" << endl;
    cout << " -------------------  5  ------------------" << endl;
    d.data = "World";
    cout << "[" << d.data << "]" << endl;
    cout << "[" << t.data1.data << "]" << endl;
    cout << "[" << c02->data1.data << "]" << endl;
    cout << " -------------------  6  ------------------" << endl;
    t.data1.data = "!!!";
    cout << "[" << d.data << "]" << endl;
    cout << "[" << t.data1.data << "]" << endl;
    cout << "[" << c02->data1.data << "]" << endl;
  }
  cout << " -------------------  7  ------------------" << endl;
  cout << "[" << &(c02->data1.data) << "]" << endl;
  cout << "[" << c02->data1.data << "]" << endl;
}

void func03a1(C01a c) { cout << "func03b, c.data=" << c.data << endl; }

void func03a2(C01a& c) { cout << "func03b, c.data=" << c.data << endl; }

void func03b() {
  C01a x{"Hello"};
  cout << "1 ------------" << endl;
  func03a1(x);
  // func03a2(x);
  cout << "2 ------------" << endl;
  C01a& y = x;
  cout << "3 ------------" << endl;
  func03a1(y);
  // func03a2(y);
  cout << "4 ------------" << endl;
}

void tmp03() { func03b(); }

void func04a(C01a& c) {
  for (int i = 0; i < 5; i++) {
    cout << "func04a, c.data=" << c.data << endl;
    EasyWay::sleep(700);
  }
}

void func04b() {
  C01a x{"hello"};
  thread t(func04a, std::ref(x));
  cout << "func04b, thread started." << endl;
  t.detach();
  EasyWay::sleep(2000);
  cout << "go out func04b" << endl;
}

void tmp04() {
  func04b();
  cout << "func04b finished." << endl;
  EasyWay::sleep(2000);
  cout << "END." << endl;
}

auto func1 = [](const string& data, int begin, int end) {
  return data.substr(begin, end);
};

struct LoginEvent {
  LoginEvent(const string& u, const string& p) : username(u), passwd(p){};

  LoginEvent(const string& data)
      : username(func1(data, 0, 6)), passwd(func1(data, 6, data.size())) {}

  const string username;
  const string passwd;
};

void tmp05() {
  stringstream ss{};
  ss << "1 hello world.\nok   thank  \n you.";
  cout << "ss:" << ss.str() << endl;

  string s{};
  int c = 0;
  while (ss >> s && c < 3) {
    c += 1;
    cout << "s: [" << s << "]" << endl;
    cout << "--------------------- c = " << c << endl;
  }
}

void tmp06() {
  stringstream ss{};
  ss.str("4|12356789|ok.");
  const int len = 1024;
  char buff[len]{};
  while (ss.getline(buff, len, '|')) {
    cout << "buff [" << buff << "]" << endl;
  }
}

enum class Color { Red, Green, Blue };

void tmp07() {
  int c = static_cast<int>(Color::Red);
  cout << "c:" << c << endl;
}

void tmp08() {
  string s{"0abc"};
  cout << s[0] << endl;
  cout << (s[0] == '0') << endl;
  cout << (s[0] == 'x') << endl;
}

class C09a {
 public:
  virtual void working() = 0;

  void counting() {
    int i = 0;
    while (true) {
      cout << "num: " << ++i << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
  }

  C09a() {
    cout << "C09a default constructor: begin" << endl;
    thread t(std::mem_fn(&C09a::counting), std::ref(*this));
    t.detach();
    cout << "C09a default constructor: end" << endl;
  };

  C09a(const string& a) : data(a) {
    cout << "C09a string constructor." << endl;
  };

  C09a(const C01a& c) {
    cout << "C09a copy constructor: data=" << c.data << endl;
    data = c.data;
  };

  C09a(C01a&& c) noexcept {
    cout << "C09a move constructor. data=" << c.data << endl;
    data = c.data;
    c.data = "";
  };

  // not a constructor, so it must be construted before assigning a new value.
  C09a& operator=(const C01a& c) {
    cout << "C09a assign constructor. data[" << data << "] to [" << c.data
         << "]" << endl;
    this->data = c.data;
    return *this;
  };

  ~C09a() { cout << "C09a Destructor: data=" << data << endl; };

  string data = "C09a";
};

class C09b {
 public:
  C09b(C09a& t) : target1(t) { cout << "C09b created." << endl; }
  C09a& target1;
};

class C09c : public C09a {
 public:
  C09c() { cout << "C09c default created." << endl; }
  void working() override { cout << "i am working.." << endl; };
  shared_ptr<C09b> ptr{};
  void start() { ptr.reset(new C09b(*this)); }
};

void func09a(C01a& x) {
  cout << " A -----------" << endl;
  cout << "a" << x.data << endl;
}

void tmp09() {
  C09c ccc{};
  cout << " 1 -------------- " << endl;
  ccc.start();
  cout << " 2 -------------- " << endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void tmp10() {
  stringstream ss{"2|-1|ok|"};
  char buff[1024]{};

  ss.getline(buff, 1024, '|');
  cout << "buff:" << buff << endl;
  ss.getline(buff, 1024, '|');
  cout << "buff:" << buff << endl;
  int cid{std::stoi(buff)};
  cout << "cid:" << cid << endl;
  ss.getline(buff, 1024, '|');
  cout << "buff:" << buff << endl;
}

decltype(auto) func11a(int a) { return a; }

void tmp11() {
  if (true) {
    cout << "an" << endl;
  } else {
  }

  auto x = func11a(10);
}

template <typename Map>
void print_map(Map& m) {
  std::cout << '{';
  for (auto& p : m) std::cout << p.first << ':' << p.second << ' ';
  std::cout << "}\n";
}

void tmp12() {
  std::map<string, string> myMap{};

  myMap.insert({"AA", "aa"});

  myMap["BB"] = "bb";

  cout << "AA: value=[" << myMap["AA"] << "]" << endl;
  cout << "AA: value=[" << myMap.at("AA") << "]" << endl;
  cout << "--" << endl;

  string target = "BB";
  cout << "BB: value=[" << myMap[target] << "]" << endl;
  cout << "BB: value=[" << myMap.at(target) << "]" << endl;
  cout << "--" << endl;

  cout << "CC: value=[" << (myMap.at("CC") == "") << "]" << endl;
  cout << "CC: value=[" << myMap["CC"] << "]" << endl;
  cout << "--" << endl;
}

void tmp13() {
  std::map<string, string> myMap{
      {"A", "1"}, {"C", "3"}, {"D", "4"}, {"B", "2"}};

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }

  string target = "A";
  auto it = myMap.find(target);
  if (it != myMap.end()) {
    cout << "find[" << target << "], value=" << it->second << endl;
  } else {
    cout << "Not find target[" << target << "] " << endl;
    ;
  }

  target = "B";
  it = myMap.find(target);
  if (it != myMap.end()) {
    cout << "find[" << target << "], value=" << it->second << endl;
  } else {
    cout << "Not find target[" << target << "] " << endl;
    ;
  }

  target = "X";
  it = myMap.find(target);
  if (it != myMap.end()) {
    cout << "find[" << target << "], value=" << it->second << endl;
  } else {
    cout << "Not find target[" << target << "] " << endl;
    ;
  }
}

void tmp14() {
  std::map<string, string> myMap{};

  myMap.insert({"AA", "a"});
  myMap.insert({"BB", "c"});

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }

  cout << "-----------------------------------" << endl;

  myMap.insert({"AA", "b"});
  myMap.insert({"BB", "d"});

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }

  cout << "-----------------------------------" << endl;

  myMap["AA"] = "11";
  myMap["BB"] = "22";

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }
}

void tmp15() {
  std::map<string, string> myMap{
      {"A", "1"}, {"C", "3"}, {"D", "4"}, {"B", "2"}};

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }
  cout << " ------------------------- " << endl;
  myMap.erase("A");
  myMap.erase("A");
  myMap.erase("A");
  myMap.erase("B");

  for (auto p : myMap) {
    cout << "k=" << p.first << ", value=" << p.second << endl;
  }
  cout << " ------------------------- " << endl;
}

void tmp16() {
  const string str1{"1234567"};

  char ch1[] = {83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83};
  //��γ�ʼ��ȫA����

  str1.copy(ch1, str1.length());
  ch1[str1.length()] = '\0';
  for (auto c : ch1) {
    cout << "[" << c << "]" << endl;
  }

  cout << " ----------------" << endl;
  cout << "str1: [" << str1 << "]" << endl;
  cout << "ch1:  [" << ch1 << "]" << endl;

  char ch2[100]{};
  strcpy_s(ch2, str1.c_str());
  cout << " ----------------" << endl;
  cout << "str1: [" << str1 << "]" << endl;
  cout << "ch2:  [" << ch2 << "]" << endl;

  const char* ch3 = str1.c_str();

  cout << " ----------------" << endl;
  cout << "str1: [" << str1 << "]" << endl;
  cout << "ch3:  [" << ch3 << "]" << endl;
}

void tmp17() { cout << "version:" << _MSC_VER << endl; }

void tmp18() {
  // string s0{};
  // string s1{"My","Age", "is" };
  // string s2 = "My " + "name " + "is " + "haaha";
  // string s3 = s0 + "My " + "age " + "is" + 15;
  cout << "Hello" << endl;
}

}  // namespace tmp_test3

void tmpTest3() {
  using namespace tmp_test3;
  tmp17();
}
