
#include <iostream>
#include <map>
#include <stack>
#include <string>
using namespace std;

stack<double> OPND;  //操作数栈
stack<int> OPTR;     //运算符栈

map<char, int> OptrMapInt;

void OptrMapToInt() {
  OptrMapInt['+'] = 0;
  OptrMapInt['-'] = 1;
  OptrMapInt['*'] = 2;
  OptrMapInt['/'] = 3;
  OptrMapInt['('] = 4;
  OptrMapInt[')'] = 5;
  OptrMapInt['#'] = 6;
}

int mat[7][7] = {  //运算符优先级关系
    {1, 1, -1, -1, -1, 1, 1},   {1, 1, -1, -1, -1, 1, 1},
    {1, 1, 1, 1, -1, 1, 1},     {1, 1, 1, 1, -1, 1, 1},
    {-1, -1, -1, -1, -1, 0, 2}, {1, 1, 1, 1, 2, 1, 1},
    {-1, -1, -1, -1, -1, 2, 0}};

void init() {
  while (!OPND.empty()) OPND.pop();
  while (!OPTR.empty()) OPTR.pop();
}

void cal(double& a, double& b, int& op) {
  switch (op) {
    case 0:  // +
      a += b;
      break;
    case 1:  // -
      a -= b;
      break;
    case 2:  // *
      a *= b;
      break;
    case 3:  // /
      a /= b;
      break;
    default:
      break;
  }
}

int DQL_main() {
  OptrMapToInt();
  while (true) {
    string s;
    cout << "输入表达式：";
    getline(cin, s);
    s = s + "#";
    init();
    OPTR.push(6);  //'#'
    int i = 0;
    int len = s.length();
    while (s[i] != '#' || OPTR.top() != 6) {
      if (s[i] == ' ') {  //过滤空格
        i++;
      } else if (s[i] >= '0' && s[i] <= '9') {  //识别操作数：double
        double num = s[i] - '0';
        int k = i + 1;
        while (k < len && (s[k] >= '0' && s[k] <= '9')) {
          num *= 10;
          num += s[k] - '0';
          k++;
        }
        if (k < len && s[k] == '.') {
          k++;
          double cnt = 1;  //小数部分每位数字对应的位
          while (k < len && (s[k] >= '0' && s[k] <= '9')) {
            cnt *= 0.1;
            num += ((s[k] - '0') * cnt);
            k++;
          }
        }
        OPND.push(num);
        i = k;
      } else {
        int op1 = OPTR.top();
        int op2 = OptrMapInt[s[i]];
        int flag = 0;
        switch (mat[op1][op2]) {
          case -1:
            OPTR.push(op2);
            i++;
            break;
          case 1:
            double bb;
            bb = OPND.top();
            OPND.pop();
            double aa;
            aa = OPND.top();
            OPND.pop();
            cal(aa, bb, op1);
            OPND.push(aa);
            OPTR.pop();
            break;
          case 0:
            OPTR.pop();
            i++;
            break;
          default:
            cout << "表达式输入有误" << endl;
            flag = 1;
            break;
        }
        if (flag) break;
      }
    }
    cout << "计算结果：" << OPND.top() << endl;
    OPND.pop();
  }
  return 0;
}
