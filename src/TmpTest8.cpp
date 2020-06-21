#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "seeker/common.h"

#include <iomanip>

namespace tmp_test8 {
using std::cout;
using std::endl;
using std::string;
using std::vector;



struct Foo0 {
  char a1 = 0;
  uint64_t a2 = 0;
  uint8_t a4 = 0;
  uint32_t a3 = 0;
  char a5 = 0;
};

#pragma pack(push, 1)
struct Foo1 {
  char a1 = 0;
  uint64_t a2 = 0;
  uint8_t a4 = 0;
  uint32_t a3 = 0;
  char a5 = 0;
};
#pragma pack(pop)


void tmp01() {
  cout << "sizeof(Foo0) = " << sizeof(Foo0) << endl;
  cout << "sizeof(Foo1) = " << sizeof(Foo1) << endl;



  {
    Foo0 target;
    target.a5 = 0xFF;
    std::ofstream ostrm("out1.data", std::ios::binary);
    ostrm.write(reinterpret_cast<char*>(&target), sizeof(target));  // 二进制输出
  }


  {
    Foo1 target;
    target.a5 = 0xFF;
    std::ofstream ostrm("out2.data", std::ios::binary);
    ostrm.write(reinterpret_cast<char*>(&target), sizeof(target));  // 二进制输出
  }

  cout << "done." << endl;
}

void tmp02() {

  char cc[] = "abcde";
  cout << "cc = " << (int32_t) cc << endl;
  cout << "cc = " << (int32_t) (&cc) << endl;

}

class Foo03 {
public:
  Foo03() {
    std::cout << "construct Foo03 " << std::endl;
    throw std::exception("created failed");
  }

  ~Foo03() {
    std::cout << "deconstruct Foo03 " << std::endl;
  }
};

void tmp03(){

  std::cout << "begin." << std::endl;
  try {
    Foo03 a;
  } catch(std::exception ex) {
    std::cout << ex.what() << std::endl;
  }
  std::cout << "end." << std::endl;

}

class Foo04 {
public:
  int value;
  void setValue(const int& x) {value = x;}

  Foo04& operator+(const Foo04& o) {
    value += o.value;
    return *this;
  }

  Foo04(const int& v): value(v) {
    std::cout << "construct Foo04: " << v << std::endl;
  }

  ~Foo04() {
    std::cout << "deconstruct Foo04: " << value << std::endl;
  }
};


void tmp04() {
  std::cout << "--------- 1 ------------" << std::endl;
  Foo04(3);
  std::cout << "--------- 2 ------------" << std::endl;
  Foo04(3).setValue(4);
  std::cout << "--------- 3 ------------" << std::endl;
  Foo04(5) + Foo04(7) = Foo04(2);
  std::cout << "--------- 4 ------------" << std::endl;
}


void tmp05() {
  using seeker::ByteArray;

  uint8_t data[] = {0,0,0,0,0,0};

  uint32_t a = 0x12345678;

  ByteArray::writeData(data, a, false);

  std::cout << std::hex;

  for(size_t i=0; i < 6; i ++) {
    std::cout << (int)data[i] << " ";
  }

  cout << std::endl << "DONE." << endl;

}

}  // namespace tmp_test8

void tmpTest8() {
  using namespace tmp_test8;
  tmp05();
}
