
#include <string>
#include <cstring>
#include <typeinfo>
#include <vector>
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

};



class TMP2A{
public :
  const string name;
  TMP2A(const string& n): name(n) {
    cout << "TMP2A created with [" << name << "]" << endl;
  }
  void say() {
    cout << "I am TMP2A with [" << name << "]" << endl;
  }
};


class TMP2B{
public :
  const string alias;
  TMP2B(const string& n): alias(n) {
    cout << "TMP2B created with [" << alias << "]" << endl;
  }
  void say() {
    cout << "I am TMP2B with [" << alias << "]" << endl;
  }
};

template<typename T>
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
 //class A中有个成员方法foo，foo内部有个static变量s；
 //class A的两个不同对象，a1和a2中的foo方法内部的两个s是同一个吗？

}

}  // namespace tmp_test7

void tmpTest7() {
  using namespace tmp_test7;
  tmp02();
}
