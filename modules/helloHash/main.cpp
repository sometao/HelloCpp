#include <iostream>
#include <string>
#include "md5.h"
#include "sha1.h"





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





int main() {


  sha1Test();
  return 0;
}