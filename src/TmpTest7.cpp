
#include <cassert>
#include <atomic>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "EasyWay.h"
#include "stdafx.h"

namespace tmp_test7 {
using std::cout;
using std::endl;
using std::string;

template <typename T>
void writeData(uint8_t* buf, T num) {
  int len(sizeof(T));
  for (size_t i = 0; i < len; ++i) {
    buf[i] = (uint8_t)(num >> (i * 8));
  }
}

template <typename T>
void readData(uint8_t* buf, T& num) {
  int len(sizeof(T));
  static uint8_t byMask(0xFF);
  num = 0;

  for (size_t i = 0; i < len; ++i) {
    num <<= 8;
    num |= (T)(buf[len - 1 - i] & byMask);
  }
}

template <typename T>
void testWriteAndRead(vector<T> vec, uint8_t* data, size_t len) {

  cout << "-------------------- "<< typeid(T).name() << " test ---------------------------" << endl;
  memset(data, 0, len);
  uint8_t width =sizeof(T);

  cout << "width: " << (int)width << endl;
  assert(len > width * vec.size());

  for (uint8_t i = 0; i < vec.size(); i++) {
    cout << "i:" << (int)i << ":" << typeid(vec[i]).name() << ":" << (int)vec[i] << endl;
    uint16_t t = (uint16_t)i * width;
    writeData(data + t, vec[i]);
  }

  cout << "--------------------" << endl;

  for (int i = 0; i < len; i++) {
    if(i % 8 == 0) {
      cout << endl;
      cout << "["<< i << "\t]\t";

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




}

}  // namespace tmp_test7

void tmpTest7() {
  using namespace tmp_test7;
  tmp01();
}
