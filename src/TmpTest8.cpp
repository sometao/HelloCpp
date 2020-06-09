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



}  // namespace tmp_test8

void tmpTest8() {
  using namespace tmp_test8;
  tmp01();
}
