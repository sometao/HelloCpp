

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

double calc(double n1, double n2, char op) {
  double rst;
  if (op == '+') {
    rst = n1 + n2;
  } else if (op == '-') {
    rst = n1 - n2;
  } else if (op == '*') {
    rst = n1 * n2;
  } else if (op == '/') {
    rst = n1 / n2;
  } else {
    rst = DBL_MAX;
  }
  return rst;
}

void startCalculator() {
  while (true) {
    double num1 = DBL_MAX;
    double num2 = DBL_MAX;
    char op;

    cout << "input: ";
    cin >> num1;
    cin >> op;
    cin >> num2;
    cout << " ------------------------------ \n";
    if (num1 == DBL_MAX || num2 == DBL_MAX) {
      cout << "error input." << endl;
      break;
    } else {
      double rst = calc(num1, num2, op);
      cout << "result:" << rst << endl;
    }
    cout << " ------------------------------ \n";
  }
}
