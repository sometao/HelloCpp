#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "seeker/common.h"


namespace tmp_test7 {
using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T>
void writeData(uint8_t* buf, T num) {
  int len(sizeof(T));
  for (size_t i = 0; i < len; ++i) {
    buf[i] = (uint8_t)(num >> (i * 8));
  }
}

template <typename T>
void readData(uint8_t* buf, T& num) {
  uint8_t len(sizeof(T));
  static uint8_t byMask(0xFF);
  num = 0;

  for (size_t i = 0; i < len; ++i) {
    num <<= 8;
    num |= (T)(buf[len - 1 - i] & byMask);
  }
}

template <typename T>
void testWriteAndRead(vector<T> vec, uint8_t* data, size_t len) {
  cout << "-------------------- " << typeid(T).name() << " test ---------------------------"
       << endl;
  memset(data, 0, len);
  uint8_t width = sizeof(T);

  cout << "width: " << (int)width << endl;
  assert(len > width * vec.size());

  for (uint8_t i = 0; i < vec.size(); i++) {
    cout << "i:" << (int)i << ":" << typeid(vec[i]).name() << ":" << (int)vec[i] << endl;
    uint16_t t = (uint16_t)i * width;
    writeData(data + t, vec[i]);
  }

  cout << "--------------------" << endl;

  for (int i = 0; i < len; i++) {
    if (i % 8 == 0) {
      cout << endl;
      cout << "[" << i << "\t]\t";
    }
    cout << (int)data[i] << " ";
  }

  cout << endl;
  cout << "--------------------" << endl;

  for (uint8_t i = 0; i < vec.size(); i++) {
    T d{0};
    uint16_t t = (uint16_t)i * width;
    readData(data + t, d);
    cout << "read: i:" << (int)i << ":" << typeid(d).name() << ":" << (int)d << endl;
  }


  cout << "\n\n" << endl;
}


void tmp01() {
  cout << "tmpTest7 tmp01: call foo1." << endl;
  uint8_t data[128] = {0};


  vector<int> vec1{1024, 1025, 1026, 1027, 1028, 1029, 256};
  vector<uint16_t> vec2{1024, 1025, 1026, 1027, 1028, 1029, 256};
  vector<uint64_t> vec3{1024, 1025, 1026, 1027, 1028, 1029, 256};

  vector<uint8_t> vec4{2, 4, 6, 8, 16, 32, 64};


  testWriteAndRead(vec1, data, 128);

  testWriteAndRead(vec2, data, 128);

  testWriteAndRead(vec3, data, 128);

  testWriteAndRead(vec4, data, 128);
};



class TMP2A {
 public:
  const string name;
  TMP2A(const string& n) : name(n) { cout << "TMP2A created with [" << name << "]" << endl; }
  void say() { cout << "I am TMP2A with [" << name << "]" << endl; }
};


class TMP2B {
 public:
  const string alias;
  TMP2B(const string& n) : alias(n) { cout << "TMP2B created with [" << alias << "]" << endl; }
  void say() { cout << "I am TMP2B with [" << alias << "]" << endl; }
};

template <typename T>
void foo(T t) {
  cout << "1. -----" << endl;
  static T x{"Inner--" + std::to_string(seeker::Time::currentTime())};
  cout << "2. -----" << endl;
  t.say();
  cout << "3. -----" << endl;
  x.say();
  cout << "4. -----" << endl;
}



void tmp02() {
  TMP2A a{"AAA"};
  foo(a);
  cout << "++++++++++++++++++++++++++++++++++++++\n\n" << endl;

  TMP2B b{"BBB"};
  foo(b);
  cout << "++++++++++++++++++++++++++++++++++++++\n\n" << endl;


  TMP2A c{"CCC"};
  foo(c);
  foo(c);
  foo(c);
  cout << "++++++++++++++++++++++++++++++++++++++\n\n" << endl;

  TMP2B d{"DDD"};
  foo(d);
  foo(d);
  foo(d);
  cout << "++++++++++++++++++++++++++++++++++++++\n\n" << endl;



  cout << "done" << endl;
}

void tmp03() {
  // class A中有个成员方法foo，foo内部有个static变量s；
  // class A的两个不同对象，a1和a2中的foo方法内部的两个s是同一个吗？
}

void tmp04() {
  enum { SIZE = 4 };

  int a[SIZE] = {1, 2, 3, 4};
  FILE* f1 = fopen("file1.bin", "wb");
  assert(f1);
  int r1 = fwrite(a, sizeof a[0], SIZE, f1);
  printf("wrote %d elements out of %d requested\n", r1, SIZE);

  a[0] = 10;
  r1 = fwrite(a, sizeof a[0], SIZE, f1);
  a[0] = 20;
  r1 = fwrite(a, sizeof a[0], SIZE, f1);
  a[0] = 30;
  r1 = fwrite(a, sizeof a[0], SIZE, f1);
  fclose(f1);

  int b[SIZE * 4];
  FILE* f2 = fopen("file1.bin", "rb");
  int r2 = fread(b, sizeof b[0], SIZE * 4, f2);
  fclose(f2);
  printf("read back: ");
  for (int i = 0; i < r2; i++) printf("%d ", b[i]);
}

void tmp05() {
  uint8_t bytes[] = {1, 0x04};
  uint16_t value = (uint16_t)bytes[0] << 8 | bytes[1];
  cout << value << endl;
}


void tmp06() {
  string s = "abcdefg";
  auto c = s.at(s.size() - 1);
  string s1 = s.substr(0, s.size() - 1);


  cout << "s:\t" << s << endl;
  cout << "c:\t" << c << endl;
  cout << "s1:\t" << s1 << endl;
}

void tmp07() {
  std::vector<uint8_t> vec;

  cout << "vec size = " << vec.size() << endl;
  cout << "vec capacity = " << vec.capacity() << endl;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  cout << "vec size = " << vec.size() << endl;
  cout << "vec capacity = " << vec.capacity() << endl;

  for (auto& v : vec) {
    cout << (int)v << ", ";
  }
  cout << endl;

  vec[0] = 9;
  vec.at(1) = 8;
  *(vec.data() + 2) = 10;

  for (auto& v : vec) {
    cout << (int)v << ", ";
  }
  cout << endl;
}


class Foo8 {
 public:
  std::string s;
  std::vector<int> vec = std::vector<int>(12);
  Foo8() {}
};

void tmp08() {
  Foo8 f{};
  cout << "s= [" << f.s << "]" << endl;
  cout << "vec= [" << f.vec.size() << "]" << endl;
}

enum class FooType { A = 5, B = 3 };

void tmp09() {
  FooType t1 = FooType::B;
  uint16_t x = (uint16_t)t1;

  cout << "x=" << (int)x << endl;
}


class Foo10 {
 public:
  std::unordered_map<uint16_t, vector<string>> attributes;

  void addAttr(uint16_t attrType, vector<string>& value) {
    uint16_t typeCode = (uint16_t)attrType;
    if (attributes.find(typeCode) == attributes.end()) {
      attributes.emplace(typeCode, std::move(value));
    }
  }
};

void tmp10() {
  vector<string> vec1{"a1", "b", "c"};
  vector<string> vec2{"a2", "b", "c"};
  vector<string> vec3{"a3", "b", "c"};


  Foo10 foo{};

  foo.addAttr(1, vec1);
  foo.addAttr(2, vec2);
  foo.addAttr(3, vec3);


  // vec1[0] = "999";

  cout << "vec1 empty = " << vec1.empty() << endl;
  for (auto& v : vec1) {
    cout << v << " ";
  }
  cout << endl;

  for (auto& p : foo.attributes) {
    auto key = p.first;
    auto value = p.second;
    cout << key << ": ";
    for (auto& v : value) {
      cout << v << " ";
    }
    cout << endl;
  }
}

void tmp11() {
  vector<string> vec1{"a1", "b", "c"};

  std::unordered_map<uint16_t, vector<string>> map;

  map.emplace(1, std::move(vec1));

  for (auto& p : map) {
    auto key = p.first;
    auto value = p.second;
    cout << key << ": ";
    for (auto& v : value) {
      cout << v << " ";
    }
    cout << endl;
  }

  cout << "vec1 empty = " << vec1.empty() << endl;
  for (auto& v : vec1) {
    cout << v << " ";
  }
  cout << endl;
}


void tmp12() {
  string s = "hello, world.";
  cout << "s:" << s << endl;

  vector<uint8_t> vec(s.length());

  auto data = s.c_str();
  for (int i = 0; i < s.length(); i++) {
    vec.at(i) = data[i];
  }


  string s1{};
  for (int i = 0; i < vec.size(); i++) {
    s1.push_back(vec.at(i));
  }

  cout << "s1:" << s1 << endl;
}


char value2Char(uint8_t value) {
  char result = '\0';
  if (value >= 0 && value <= 9) {
    result = (char)(value + 48);
  } else if (value >= 10 && value <= 15) {
    result =
        (char)(value - 10 + 97);  //减去10则找出其在16进制的偏移量，65为ascii的‘A‘的字符编码值
  } else {
    ;
  }
  return result;
}


std::string bytes2HexString(uint8_t* data, size_t len) {
  std::string rst{};
  uint8_t high;
  uint8_t low;
  for (size_t i = 0; i < len; i++) {
    high = data[i] >> 4;
    low = data[i] & 0x0F;
    rst += value2Char(high);
    rst += value2Char(low);
  }
  return rst;
}

void tmp13() {
  uint8_t data[] = {0xAB, 0xCD, 0x1A, 0x2B, 0x3C};
  auto rst = bytes2HexString(data, 5);

  std::cout << "rst:" << rst << std::endl;
}


}  // namespace tmp_test7



void tmpTest7() {
  using namespace tmp_test7;
  tmp13();
}
