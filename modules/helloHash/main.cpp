#include <iostream>
#include <string>
#include <vector>
#include "md5.h"
#include "sha1.h"
#include "hmac.h"
#include "crc32.h"



//// convert from hex to binary
std::vector<unsigned char> hex2bin(const std::string& hex) {
  std::vector<unsigned char> result;
  for (size_t i = 0; i < hex.size(); i++) {
    unsigned char high = hex[i] >= 'a' ? hex[i] - 'a' + 10 : hex[i] - '0';
    i++;
    unsigned char low = hex[i] >= 'a' ? hex[i] - 'a' + 10 : hex[i] - '0';
    result.push_back(high * 16 + low);
  }
  return result;
}


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
  std::string sha1hmac = hmac<SHA1>(msg, key);

  std::cout << "sha1hmac:" << sha1hmac << std::endl;
}


void hmacSha1Test2() {
  std::string msg = "The quick brown fox jumps over the lazy dog";
  uint8_t* data = (uint8_t*)msg.c_str();
  size_t len = msg.size();
  std::string key = "key";

  std::string sha1hmac = hmac<SHA1>(data, len, key.c_str(), key.size());

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

void hmacSha1Test4() {
  std::cout << "hmacSha1Test4:" << std::endl;


  uint8_t data[] = {0x00, 0x03, 0x00, 0x60, 0x21, 0x12, 0xa4, 0x42, 0x64, 0xe0, 0x78, 0x3e,
                    0xcf, 0xad, 0x9d, 0x31, 0xf0, 0x37, 0x65, 0xc6, 0x00, 0x19, 0x00, 0x04,
                    0x11, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x10,
                    0x00, 0x06, 0x00, 0x08, 0x7a, 0x68, 0x61, 0x6e, 0x67, 0x74, 0x61, 0x6f,
                    0x00, 0x14, 0x00, 0x12, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x2e, 0x73, 0x65,
                    0x65, 0x6b, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x6f, 0x72, 0x67, 0x00, 0x00,
                    0x00, 0x15, 0x00, 0x10, 0x36, 0x30, 0x37, 0x38, 0x64, 0x31, 0x63, 0x32,
                    0x33, 0x30, 0x66, 0x61, 0x66, 0x32, 0x35, 0x36};

  size_t len = sizeof(data);

  std::cout << "len:" << len << std::endl;

  MD5 md5;
  //// key = MD5(username ":" realm ":" SASLprep(password))
  std::string keyStr{};
  keyStr += "zhangtao";
  keyStr += ":";
  keyStr += "hello.seekloud.org";
  keyStr += ":";
  keyStr += "skld123!@#";
  std::cout << "----------------- keyStr:" << keyStr << std::endl;

  md5.reset();
  md5.add(keyStr.c_str(), keyStr.size());

  uint8_t key[16];
  md5.getHash(key);

  std::string sha1hmac = hmac<SHA1>(data, len, key, 16);

  std::cout << "sha1hmac:" << sha1hmac << std::endl;
}

void hmacSha1Test5() {
  std::cout << "hmacSha1Test5:" << std::endl;

  MD5 md5;
  //// key = MD5(username ":" realm ":" SASLprep(password))
  std::string keyStr{};
  keyStr += "zhangtao";
  keyStr += ":";
  keyStr += "hello.seekloud.org";
  keyStr += ":";
  keyStr += "seekloud123";
  std::cout << "----------------- keyStr:" << keyStr << std::endl;

  md5.reset();
  md5.add(keyStr.c_str(), keyStr.size());

  uint8_t key[16];
  md5.getHash(key);


  uint8_t data[] = {0x00, 0x03, 0x00, 0x60, 0x21, 0x12, 0xa4, 0x42, 0x85, 0x3d, 0xbd, 0x3c,
                    0x18, 0x96, 0x5e, 0x0c, 0xc4, 0x18, 0xc7, 0x16, 0x00, 0x19, 0x00, 0x04,
                    0x11, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x10,
                    0x00, 0x06, 0x00, 0x08, 0x7a, 0x68, 0x61, 0x6e, 0x67, 0x74, 0x61, 0x6f,
                    0x00, 0x14, 0x00, 0x12, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x2e, 0x73, 0x65,
                    0x65, 0x6b, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x6f, 0x72, 0x67, 0x00, 0x00,
                    0x00, 0x15, 0x00, 0x10, 0x36, 0x64, 0x61, 0x63, 0x64, 0x35, 0x32, 0x63,
                    0x34, 0x30, 0x36, 0x65, 0x64, 0x38, 0x32, 0x62};

  size_t len = sizeof(data);

  std::cout << "len:" << len << std::endl;


  std::string sha1hmac = hmac<SHA1>(data, len, key, 16);

  std::cout << "sha1hmac:" << sha1hmac << std::endl;
}


void crc32Test() {
  CRC32 hasher;

  std::string target{"hello, world."};

  std::string rst = hasher(target);

  std::cout << target << std::endl;
  std::cout << rst << std::endl;
}



int main() {
  // sha1Test();
  // hmacSha1Test1();
  // hmacSha1Test2();
  // hmacSha1Test3();
  // crc32Test();
  hmacSha1Test4();
  //hmacSha1Test5();
  return 0;
}