
#include <atomic>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
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
  T temp(0);
  num = 0;

  for (size_t i = 0; i < len; ++i) {
    num <<= 8;
    num |= (T)(buf[len - 1 - i] & byMask);
  }
}

void tmp01() {
  cout << "tmpTest7 tmp01: call foo1." << endl;

  // TODO write data to buffer;
  // read data from buffer.
  uint8_t data[128] = {0};
  vector<int> vec1{1, 2, 3, 4, 5, 6, 7};

  //for (const auto& i : vec1) {
  //  cout << "i:" << typeid(i).name() << ":" << i << endl;
  //}

  for (int i = 0; i < vec1.size(); i++) {
    cout << "i:" << i << ":" << typeid(i).name() << ":" << vec1[i] << endl;
  }
  
  for (uint8_t i = 0; i < vec1.size(); i++) {
    uint16_t t = (uint16_t)i * 4;
    writeData(data + t, vec1[i]);
  }

  //for (uint8_t i = 0; i < sizeof(data); i++) {
  //  cout << "i:" << (int)i << ":" << typeid(data[i]).name() << ":" << (int)data[i] << endl;
  //}

  cout << "-----------------------------------------------" << endl;

  for (uint8_t i = 0; i < vec1.size(); i++) {
    int d{0};
    uint16_t t = (uint16_t)i * 4;
    readData(data + t, d);
    cout << "read: i:" << (int)i << ":" << typeid(d).name() << ":" << d << endl;

  }




  // foo1();
}

}  // namespace tmp_test7

void tmpTest7() {
  using namespace tmp_test7;
  tmp01();
}
