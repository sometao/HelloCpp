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

void test2() {

  std::cout << "test2:" << std::endl;

  char sec_key[] = "seekloud123";

  uint8_t data[] = {0x00, 0x03, 0x00, 0x60, 0x21, 0x12, 0xa4, 0x42, 0x85, 0x3d, 0xbd, 0x3c, 0x18, 0x96, 0x5e, 0x0c,
    0xc4, 0x18, 0xc7, 0x16, 0x00, 0x19, 0x00, 0x04, 0x11, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x04,
    0x00, 0x00, 0x0e, 0x10, 0x00, 0x06, 0x00, 0x08, 0x7a, 0x68, 0x61, 0x6e, 0x67, 0x74, 0x61, 0x6f,
    0x00, 0x14, 0x00, 0x12, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x2e, 0x73, 0x65, 0x65, 0x6b, 0x6c, 0x6f,
    0x75, 0x64, 0x2e, 0x6f, 0x72, 0x67, 0x00, 0x00, 0x00, 0x15, 0x00, 0x10, 0x36, 0x64, 0x61, 0x63,
    0x64, 0x35, 0x32, 0x63, 0x34, 0x30, 0x36, 0x65, 0x64, 0x38, 0x32, 0x62};

  char out[32] = {0};
  size_t len = sizeof(out);

  hmac_sha1((uint8_t*)sec_key, strlen(sec_key), data, sizeof(data), (uint8_t*)out, &len);

  printf("len: %d\n", len);
  std::string outStr = bytes2HexString((uint8_t*)out, len);
  std::cout << "outStr:" << outStr << std::endl;
}



int main() {
  //test1();
  test2();
  return 0;
}
