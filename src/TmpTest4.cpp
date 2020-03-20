
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "EasyWay.h"
#include "stdafx.h"

namespace tmp_test4 {
using std::cout;
using std::endl;
using std::exception;
using std::string;

void tmp01() {
  string fileName = "tmp01.bin";

  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  unsigned char arr[] = {
      0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xAB,
  };

  {
    std::ofstream os{fileName, std::ios::binary};
    os.write(reinterpret_cast<char*>(&a), sizeof(a));
    os.write(reinterpret_cast<char*>(&b), sizeof(b));
    os.write(reinterpret_cast<char*>(&c), sizeof(c));
    os.write(reinterpret_cast<char*>(&d), sizeof(d));
    cout << "sizeof(arr)=" << sizeof(arr) << endl;
    os.write(reinterpret_cast<char*>(arr), sizeof(arr));
  }

  cout << "Write finish: " << fileName << endl;
}

void tmp02() {
  string fileName = "tmp02.dat";

  unsigned char arr[] = {
      0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xAB,
  };

  {
    std::ofstream os{fileName, std::ios::binary};
    cout << "sizeof(arr)=" << sizeof(arr) << endl;
    os.write(reinterpret_cast<char*>(arr), sizeof(arr));
  }

  decltype(arr) rst = {};

  std::ifstream is(fileName, std::ios::binary);
  is.read(reinterpret_cast<char*>(rst), sizeof(rst));
  is.close();

  for (int i = 0; i < sizeof(rst) / sizeof(rst[0]); i++) {
    std::printf("Ox%X ", rst[i]);
  }
}

void printArray10(int arr[10]) {
  for (int i = 0; i < 10; i++) {
    cout << arr[i] << ",";
  }
  cout << endl;
}

uint32_t arrToHashCode(int arr[10]) {
  uint32_t code = 0;
  for (int i = 0; i < 10; i++) {
    code <<= 2;
    code += arr[i];
  }
  return code;
}

int recursiveCount = 0;
int returnCount = 0;

std::unordered_map<uint32_t, int> stateMap = {};

int calcStep(int poker[10]) {

  auto code = arrToHashCode(poker);
  auto t = stateMap.find(code);
  if (t != stateMap.end()) {
    return t->second;
  }

  int shunzi[10] = {0};
  int duizi[10] = {0};
  int liandui[10] = {0};
  int danzhang[10] = {0};

  recursiveCount++;

  if (recursiveCount % 10000 == 0) {
    cout << "recursiveCount     =    " << recursiveCount << endl;
    cout << "returnCount     =    " << returnCount << endl;
    printArray10(poker);
  }

  // cout << " 0 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl; cout << " -- poker -- " << endl; printArray10(poker);

  // cout << " -- shunzi -- " << endl;
  // printArray10(shunzi);

  // cout << " -- duizi -- " << endl;
  // printArray10(duizi);

  // cout << " -- liandui -- " << endl;
  // printArray10(liandui);

  // cout << " -- danzhang -- " << endl;
  // printArray10(danzhang);
  // cout << " 0 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl;

  // find duizi
  // init danzhang
  for (int i = 0; i < 10; i++) {
    if (poker[i] > 1) {
      duizi[i] = 1;
    } else if (poker[i] > 0) {
      danzhang[i] = 1;
    }
  }

  // cout << " 1 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl; cout << " -- poker -- " << endl; printArray10(poker);

  // cout << " -- shunzi -- " << endl;
  // printArray10(shunzi);

  // cout << " -- duizi -- " << endl;
  // printArray10(duizi);

  // cout << " -- liandui -- " << endl;
  // printArray10(liandui);

  // cout << " -- danzhang -- " << endl;
  // printArray10(danzhang);
  // cout << " 1 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl;

  // find shunzi
  for (int i = 0; i < 6; i++) {
    int j = i;
    for (; j < i + 5; j++) {
      if (poker[j] == 0) {
        break;
      }
    }
    if (j == i + 5) {
      shunzi[i] = 1;
      for (int k = i; k < i + 5; k++) {
        danzhang[k] = 0;
      }
    }
  }

  // cout << " 2 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl; cout << " -- poker -- " << endl; printArray10(poker);

  // cout << " -- shunzi -- " << endl;
  // printArray10(shunzi);

  // cout << " -- duizi -- " << endl;
  // printArray10(duizi);

  // cout << " -- liandui -- " << endl;
  // printArray10(liandui);

  // cout << " -- danzhang -- " << endl;
  // printArray10(danzhang);
  // cout << " 2 +++++++++++++++++++++++++++++++++++++++++++++++++++++ " <<
  // endl;

  // find liandui
  for (int i = 0; i < 8; i++) {
    int j = i;
    for (; j < i + 3; j++) {
      if (duizi[j] == 0) {
        break;
      }
    }
    if (j == i + 3) {
      liandui[i] = 1;
      for (int k = i; j < i + 3; k++) {
        danzhang[k] = 0;
      }
    }
  }

  // cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++ " << endl;
  // cout << " -- poker -- " << endl;
  // printArray10(poker);

  // cout << " -- shunzi -- " << endl;
  // printArray10(shunzi);

  // cout << " -- duizi -- " << endl;
  // printArray10(duizi);

  // cout << " -- liandui -- " << endl;
  // printArray10(liandui);

  // cout << " -- danzhang -- " << endl;
  // printArray10(danzhang);
  // cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++ " << endl;

  // send danzhang out
  int danzhangCount = 0;
  int pokerCount = 0;
  for (int i = 0; i < 10; i++) {
    if (danzhang[i] == 1) {
      --poker[i];
      ++danzhangCount;
    }
    pokerCount += poker[i];
  }

  if (pokerCount == 0) {
    returnCount++;
    stateMap[code] = danzhangCount;
    return danzhangCount;
  } else {
    int min_count = INT_MAX;
    // send a shunzi out
    for (int i = 0; i < 10 && min_count > 0; i++) {
      if (shunzi[i] == 1) {
        int nextPoker[10] = {0};
        memcpy(nextPoker, poker, 10 * sizeof(int));

        // cout << " -- poker -- " << endl;
        // printArray10(poker);
        // cout << " --init:  nextPoker -- " << endl;
        // printArray10(nextPoker);

        for (int j = i; j < i + 5; j++) {
          // cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          // -- " << endl; cout << " -- poker -- " << endl; printArray10(poker);

          // cout << " -- shunzi -- " << endl;
          // printArray10(shunzi);

          // cout << " i = " << i << endl;
          // cout << " j = " << j << endl;

          --nextPoker[j];

          // cout << " -- nextPoker -- " << endl;
          // printArray10(nextPoker);

          if (nextPoker[j] < 0) {
            throw std::runtime_error("nextPoker[j] < 0 in send a shunzi out");
          }
        }

        int nextPokerCount = 0;
        for (int i = 0; i < 10; i++) {
          nextPokerCount += nextPoker[i];
        }
        if (nextPokerCount == 0) {
          min_count = 0;
        } else {
          int c = calcStep(nextPoker);
          if (c < min_count) {
            min_count = c;
          }
        }
      }
    }

    // send a liandui out
    for (int i = 0; i < 10 && min_count > 0; i++) {
      if (liandui[i] == 1) {
        int nextPoker[10];
        memcpy(nextPoker, poker, 10 * sizeof(int));

        // cout << " -- poker -- " << endl;
        // printArray10(poker);
        // cout << " --init:  nextPoker -- " << endl;
        // printArray10(nextPoker);

        for (int j = i; j < i + 3; j++) {
          // cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          // -- "
          //     << endl;
          // cout << " -- poker -- " << endl;
          // printArray10(poker);

          // cout << " -- liandui -- " << endl;
          // printArray10(liandui);

          // cout << " i = " << i << endl;
          // cout << " j = " << j << endl;

          nextPoker[j] -= 2;

          // cout << " -- nextPoker -- " << endl;
          // printArray10(nextPoker);

          if (nextPoker[j] < 0) {
            throw std::runtime_error("nextPoker[j] < 0 in send a liandui out");
          }
        }

        int nextPokerCount = 0;
        for (int i = 0; i < 10; i++) {
          nextPokerCount += nextPoker[i];
        }
        if (nextPokerCount == 0) {
          min_count = 0;
        } else {
          int c = calcStep(nextPoker);
          if (c < min_count) {
            min_count = c;
          }
        }
      }
    }

    // send a duizi out
    for (int i = 0; i < 10 && min_count > 0; i++) {
      if (duizi[i] == 1) {
        int nextPoker[10];
        memcpy(nextPoker, poker, 10 * sizeof(int));
        nextPoker[i] -= 2;
        if (nextPoker[i] < 0) {
          cout << "nextPoker[j] < 0 in send a liandui out" << endl;
          throw std::runtime_error("nextPoker[j] < 0 in send a liandui out");
        }

        int nextPokerCount = 0;
        for (int i = 0; i < 10; i++) {
          nextPokerCount += nextPoker[i];
        }
        if (nextPokerCount == 0) {
          min_count = 0;
        } else {
          int c = calcStep(nextPoker);
          if (c < min_count) {
            min_count = c;
          }
        }
      }
    }

    returnCount++;
    stateMap[code] = min_count + danzhangCount + 1;
    return min_count + danzhangCount + 1;
  }
}

int calcCount(int* input, int length) {
  int poker[10] = {0};
  // TODO
  for (int i = 0; i < length; i++) {
    poker[input[i] - 1]++;
  }

  int rst = calcStep(poker);

  return rst;
}

void tmp03() {
  int input[] = {1, 2, 7, 8, 9, 10,
                  1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10,
                  1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10,
  };

  //int input[] = {1, 2, 3, 3, 4, 4, 5, 5, };

   int len = sizeof(input) / sizeof(int);

   cout << "len:" << len << endl;

   int rst = calcCount(input, len);

   cout << "recursiveCount:" << recursiveCount << endl;
   cout << "rst:" << rst << endl;

}

void tmp04() {

  uint64_t a = 1;
  cout << "a: " << a << endl;


  a <<= 2;
  cout << "a: " << a << endl;
  
  a <<= 2;
  cout << "a: " << a << endl;
  
  a <<= 2;
  cout << "a: " << a << endl;


}

}  // namespace tmp_test4

void tmpTest4() {
  using namespace tmp_test4;
  tmp03();
}
