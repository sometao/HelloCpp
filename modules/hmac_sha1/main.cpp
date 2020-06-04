/*
https://github.com/Akagi201/hmac-sha1
*/


#include <iostream>
#include <string.h>

extern "C" {
#include "hmac.h"
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

void test1() {

  char sec_key[] = "key";
  char data[] = "The quick brown fox jumps over the lazy dog";
  char out[32] = {0};
  size_t len = sizeof(out);

  hmac_sha1((uint8_t*)sec_key, strlen(sec_key), (uint8_t*)data, strlen(data), (uint8_t*)out,
    &len);

  printf("len: %d\n", len);
  std::string outStr = bytes2HexString((uint8_t*)out, len);
  std::cout << "outStr:" << outStr << std::endl;

}



int main() {
  test1();
  return 0;
}
