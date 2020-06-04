#include <iostream>
#include <string>
#include "md5.h"
#include "sha1.h"
#include "hmac.h"





void md5Test() {
  MD5 hasher;

  std::string target{"hello, world."};

  std::string rst = hasher(target);

  std::cout << target << std::endl;
  std::cout << rst << std::endl;
}


void sha1Test() {
  SHA1 hasher;

  std::string target{"hello, world."};

  std::string rst = hasher(target);

  std::cout << target << std::endl;
  std::cout << rst << std::endl;
}


void hmacSha1Test1() {

  std::string msg = "The quick brown fox jumps over the lazy dog";
  std::string key = "key";
  std::string sha1hmac  = hmac<SHA1>(msg, key);

  std::cout << "sha1hmac:" << sha1hmac << std::endl;

}


void hmacSha1Test2() {

  std::string msg = "The quick brown fox jumps over the lazy dog";
  uint8_t* data = (uint8_t*)msg.c_str();
  size_t len = msg.size();
  std::string key = "key";

  std::string sha1hmac  = hmac<SHA1>(data, len, key.c_str(), key.size());

  std::cout << "sha1hmac:" << sha1hmac << std::endl;

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


void hmacSha1Test3() {

  std::string msg = "The quick brown fox jumps over the lazy dog";
  uint8_t* data = (uint8_t*)msg.c_str();
  size_t len = msg.size();
  std::string key = "key";
  uint8_t out[20];

  hmac<SHA1>(data, len, key.c_str(), key.size(), out);
  auto sha1hmac = bytes2HexString(out, 20);

  std::cout << "sha1hmac3:" << sha1hmac << std::endl;

}




int main() {


  //sha1Test();
  hmacSha1Test1();
  hmacSha1Test2();
  hmacSha1Test3();
  return 0;
}