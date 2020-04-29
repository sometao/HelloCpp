
#include <atomic>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

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

namespace solution1 {

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

  // if (recursiveCount % 10000 == 0) {
  //  cout << "recursiveCount     =    " << recursiveCount << endl;
  //  cout << "returnCount     =    " << returnCount << endl;
  //  printArray10(poker);
  //}

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

    returnCount++;
    stateMap[code] = min_count + danzhangCount + 1;
    return min_count + danzhangCount + 1;
  }
}

int calcCount(int poker[10]) {
  int rst = calcStep(poker);

  return rst;
}

}  // namespace solution1

void tmp03() {
  using namespace solution1;

  int input[] = {
      1, 2, 7,  8, 9, 10, 1, 2, 3, 4, 4, 5, 5, 6, 7,
      8, 9, 10, 1, 2, 3,  4, 4, 5, 5, 6, 7, 8, 9, 10,
  };

  // int input[] = {1, 2, 3, 3, 4, 4, 5, 5, };

  int len = sizeof(input) / sizeof(int);

  cout << "len:" << len << endl;

  int poker[10] = {0};

  for (int i = 0; i < len; i++) {
    poker[input[i] - 1]++;
  }

  cout << " -- poker -- " << endl;
  printArray10(poker);

  auto t0 = EasyWay::currentTimeMillis();

  int rst = calcCount(poker);
  auto t1 = EasyWay::currentTimeMillis();

  cout << "recursiveCount:" << recursiveCount << endl;
  cout << "rst:" << rst << endl;
  cout << "time:" << (t1 - t0) << "ms" << endl;
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

namespace solution2 {

int recursiveCount = 0;

bool finish(int poker[10]) {
  for (int i = 0; i < 10; i++) {
    if (poker[i] > 0) {
      return false;
    }
  }
  return true;
}

int min = INT_MAX;

void calcStep(int poker[10], int count) {
  recursiveCount++;
  if (count >= min) {
    return;
  }

  if (finish(poker)) {
    if (count < min) {
      min = count;
    }
    return;
  }

  int i = 0;
  while (poker[i] == 0) {
    i++;
  }

  //����
  if (i + 5 <= 10 && poker[i] > 0 && poker[i + 1] > 0 && poker[i + 2] > 0 &&
      poker[i + 3] > 0 && poker[i + 4] > 0) {
    for (int j = 0; j < 5; j++) {
      poker[i + j]--;
    }
    calcStep(poker, count + 1);
    for (int j = 0; j < 5; j++) {
      poker[i + j]++;
    }
  }

  //��˫
  if (i + 3 <= 10 && poker[i] > 1 && poker[i + 1] > 1 && poker[i + 2] > 1) {
    for (int j = 0; j < 3; j++) {
      poker[i + j] -= 2;
    }
    calcStep(poker, count + 1);
    for (int j = 0; j < 3; j++) {
      poker[i + j] += 2;
    }
  }

  //����
  if (poker[i] > 1) {
    poker[i] -= 2;
    calcStep(poker, count + 1);
    poker[i] += 2;
  }

  //����
  if (poker[i] > 0) {
    poker[i] -= 1;
    calcStep(poker, count + 1);
    poker[i] += 1;
  }
}

}  // namespace solution2

void tmp05() {
  using namespace solution2;

  int poker[] = {3, 3, 2, 4, 4, 2, 3, 3, 3, 3};

  cout << " -- poker -- " << endl;
  printArray10(poker);

  auto t0 = EasyWay::currentTimeMillis();

  calcStep(poker, 0);
  auto t1 = EasyWay::currentTimeMillis();

  cout << "recursiveCount:" << recursiveCount << endl;
  cout << "rst:" << min << endl;
  cout << "time:" << (t1 - t0) << "ms" << endl;
}

class Bar06 {
  string name;

 public:
  Bar06(const string& n) : name(n) {
    cout << "create Bar06[" << name << "]" << endl;
  }

  Bar06(const Bar06& o) : name(o.name) {
    cout << "copy Bar06[" << name << "]" << endl;
  }

  Bar06(Bar06&& o) noexcept : name(o.name) {
    o.name = "NULL";
    cout << "move Bar06[" << name << "]" << endl;
  }

  ~Bar06() { cout << "delete Bar06[" << name << "]" << endl; }
};

class BarDeleter06 {
 public:
  string name = "NULL";
  BarDeleter06() { cout << "create BarDeleter06[" << name << "]" << endl; }

  BarDeleter06(const BarDeleter06& o) {
    name = o.name;
    cout << "copy BarDeleter06[" << name << "]" << endl;
  }

  BarDeleter06(BarDeleter06&& o) noexcept {
    name = o.name;
    cout << "move BarDeleter06[" << name << "]" << endl;
  }

  BarDeleter06& operator=(const BarDeleter06& o) {
    cout << "operator= set[" << name << "] to [" << o.name << "]" << endl;
    name = o.name;
    return *this;
  };

  void operator()(Bar06* p) const {
    cout << "- BarDeleter06 delete begin[" << name << "]" << endl;
    p->~Bar06();
    cout << "- BarDeleter06 delete end[" << name << "]" << endl;
  };
};

void tmp06a() {
  {
    cout << "------------  1  ----------------" << endl;
    std::unique_ptr<Bar06> p1 = std::make_unique<Bar06>("aa");
    cout << "------------  2  ----------------" << endl;
  }
  cout << "------------  3  ----------------" << endl;

  std::unique_ptr<Bar06> p2;
  {
    cout << "------------  4  ----------------" << endl;
    std::unique_ptr<Bar06> p3 = std::make_unique<Bar06>("bb");
    cout << "------------  5  ----------------" << endl;
    p2.reset(p3.release());
    cout << "------------  6  ----------------" << endl;
  }
  cout << "------------  7  ----------------" << endl;

  cout << "done." << endl;
}

void tmp06b() {
  BarDeleter06 d{};

  {
    cout << "------------  1  ----------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06&> p{new Bar06("aa"), d};
    cout << "------------  2  ----------------" << endl;
  }
  cout << "------------  3  ----------------" << endl;

  std::unique_ptr<Bar06, BarDeleter06> p2{new Bar06("xx"), BarDeleter06()};
  {
    cout << "------------  4  ----------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06> p{new Bar06("bb"), BarDeleter06()};
    cout << "------------  5  ----------------" << endl;
    p2.reset(p.release());
    cout << "------------  6  ----------------" << endl;
  }
  cout << "------------  7  ----------------" << endl;

  std::unique_ptr<Bar06, BarDeleter06> p3{};
  {
    cout << "------------  8  ----------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06> p{new Bar06("cc"), d};
    cout << "------------  9  ----------------" << endl;
    p3.reset(p.release());
    cout << "------------  10  ----------------" << endl;
  }
  cout << "------------ 11  ----------------" << endl;

  cout << "done." << endl;
}

void tmp06c() {
  BarDeleter06 d{};

  cout << "==================   1    ======================" << endl;
  {
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06> p1{new Bar06("aa"), d};
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06> p2{std::move(p1)};
    cout << "---------------------------" << endl;
  }
  cout << "===================================== \n\n" << endl;

  cout << "==================   2    ======================" << endl;
  {
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06&> p1{new Bar06("aa"), d};
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06&> p2{std::move(p1)};
    cout << "---------------------------" << endl;
  }
  cout << "===================================== \n\n" << endl;

  cout << "==================   3    ======================" << endl;
  {
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06&> p1{new Bar06("aa"), d};
    cout << "---------------------------" << endl;
    std::unique_ptr<Bar06, BarDeleter06> p2{std::move(p1)};
    cout << "---------------------------" << endl;
  }
  cout << "===================================== \n\n" << endl;

  cout << "==================   4    ======================" << endl;
  {
    std::unique_ptr<Bar06, BarDeleter06&> p1{new Bar06("aa"), d};
    cout << "a ---------------------------" << endl;
    {
      BarDeleter06 d1{};
      d1.name = "one";
      cout << "b ---------------------------" << endl;
      std::unique_ptr<Bar06, BarDeleter06&> p2{new Bar06("bb"), d1};
      cout << "c ---------------------------" << endl;
      p1.swap(p2);
      cout << "d ---------------------------" << endl;
    }
    cout << "e ---------------------------" << endl;
  }
  cout << "===================================== \n\n" << endl;

  d.name = "NULL";

  cout << "==================   5    ======================" << endl;
  {
    std::unique_ptr<Bar06, BarDeleter06> p1{new Bar06("aa"), d};
    cout << "a ---------------------------" << endl;
    {
      BarDeleter06 d1{};
      d1.name = "one";
      cout << "b ---------------------------" << endl;
      std::unique_ptr<Bar06, BarDeleter06> p2{new Bar06("bb"), d1};
      cout << "c ---------------------------" << endl;
      p1.swap(p2);
      cout << "d ---------------------------" << endl;
    }
    cout << "e ---------------------------" << endl;
  }
  cout << "===================================== \n\n" << endl;

  cout << "done." << endl;
}

void tmp07() {
  std::atomic<bool> isReady{false};

  auto a = isReady.load();
  cout << "a:" << a << endl;
  isReady.store(true);
  a = isReady.load();
  cout << "a:" << a << endl;
}

void tmp08() {
  uint64_t a1 = 10;
  uint64_t a2 = 15;
  auto r1 = a2 - a1;
  auto r2 = a1 - a2;

  cout << "r1: " << r1 << endl;
  cout << "r2: " << r2 << endl;
}

void tmp09() {
  atomic<uint64_t> c{3};

  uint64_t r = 0;
  cout << "c: " << c.load() << endl;
  r = c.fetch_add(10, std::memory_order_relaxed);
  cout << "r: " << r << ",  c: " << c.load() << endl;
  r = c.fetch_add(200, std::memory_order_relaxed);
  cout << "r: " << r << ",  c: " << c.load() << endl;
  r = c.fetch_add(3000, std::memory_order_relaxed);
  cout << "r: " << r << ",  c: " << c.load() << endl;
}

void tmp10() {
  using std::vector;
  int n;
  int m;
  int q;
  cin >> n;
  cin >> m;
  cin >> q;

  vector<vector<int>> arr(n, std::vector<int>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      arr[i][j] = i + j;
    }
  }

  cout << "n:" << n << endl;
  cout << "m:" << m << endl;
  cout << "q:" << q << endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

void tmp11() {
  std::list<std::unique_ptr<string>> ls{};

  auto a1 = std::make_unique<string>("Hello");
  auto a2 = std::make_unique<string>("World");
  cout << "====== 1 ======" << endl;
  cout << "a1:" << a1->c_str() << endl;
  cout << "a2:" << a2->c_str() << endl;

  ls.push_back(std::move(a1));
  ls.push_back(std::move(a2));
  cout << "====== 2 ======" << endl;
  cout << "a1:" << (a1 == nullptr) << endl;
  cout << "a2:" << (a2 == nullptr) << endl;

  auto b1 = std::move(ls.front());
  ls.pop_front();
  auto b2 = std::move(ls.front());
  ls.pop_front();
  cout << "====== 3 ======" << endl;
  cout << "b1:" << (b1 == nullptr) << endl;
  cout << "b2:" << (b2 == nullptr) << endl;
  cout << "b1:" << b1->c_str() << endl;
  cout << "b2:" << b2->c_str() << endl;

  ls.push_back(nullptr);
  std::unique_ptr<string> c0{};
  ls.push_back(std::move(c0));
  auto c1 = std::move(ls.front());
  ls.pop_front();
  auto c2 = std::move(ls.front());
  ls.pop_front();
  cout << "====== 4 ======" << endl;
  cout << "c1:" << (c1 == nullptr) << endl;
  cout << "c2:" << (c2 == nullptr) << endl;
}

}  // namespace tmp_test4

void tmpTest4() {
  using namespace tmp_test4;
  tmp11();
}
