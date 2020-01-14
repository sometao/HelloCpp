

#include <iostream>


using namespace std;



double calc(double n1, double n2, char op) {

	double rst;
	if (op == '+') {
		rst = n1 + n2;
	}
	else if (op == '-') {
		rst = n1 - n2;
	}
	else if (op == '*') {
		rst = n1 * n2;
	}
	else if (op == '/') {
		rst = n1 / n2;
	}
	else {
		rst = -999999.99;
	}
	return rst;

}


void startCalculator() {


	while (true)
	{
		double num1;
		double num2;
		char op;

		cout << "input: ";

		cin >> num1;
		cin >> op;
		cin >> num2;

		cout << " ------------------------------ \n";

		double rst = calc(num1, num2, op);

		cout << "target:" << num1 << " " << op << " " << num2 << " = " << rst << endl;
		cout << " ------------------------------ \n";

	}

}
