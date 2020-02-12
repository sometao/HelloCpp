#include <string>
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <random>


namespace
{
	using std::cout;
	using std::endl;
	using std::vector;


	void tmp1() {

		auto l1 = [](int x, int y) -> int {return x + y; };
		auto l2 = [](int x, int y) { return x + y; };
		auto l3 = [](int x, int y) { int z = x + 1;  return z + y; };

		auto r1 = l1(1, 2);
		auto r2 = l2(3, 5);
		auto r3 = l3(3, 5);
		cout << "r1: " << r1 << endl;
		cout << "r2: " << r2 << endl;
		cout << "r3: " << r3 << endl;

	}

	void tmp2() {

		int x = 10;
		auto l1 = [x](int y) mutable { x = x + y; return x + y; };
		auto l2 = [&x](int y) mutable { x = x + y; return x + y; };

		auto r1 = l1(2);

		cout << "x:" << x << endl;
		cout << "r1:" << r1 << endl;

		cout << " -----------" << endl;
		auto r2 = l2(2);

		cout << "x:" << x << endl;
		cout << "r2:" << r2 << endl;


	}

	const std::string getStr(const std::string& name) {
		std::stringstream ss{};
		ss << "name=" << name << ";";
		return ss.str();
	}

	void tmp3() {

		auto rst1 = getStr("LiLei");

		cout << "rst1=" << rst1 << endl;


		std::stringstream ss{};
		ss << "data in ss";
		auto rst2 = getStr(std::move(ss.str()));

		cout << "rst2=" << rst2 << endl;
	}

	void tmp4() {
		std::stringstream ss{};

		std::string ls;
		ss << "haha\nhehe\nheihei";;
		getline(ss, ls);
		cout << ls << endl;
		getline(ss, ls);
		cout << ls << endl;
		getline(ss, ls);
		cout << ls << endl;


	}

	void tmp5() {

		cout << "begin." << endl;
		std::stringstream ss{};

		ss << "111111" << endl;
		ss.str("");
		ss << "222222" << endl;
		ss << "333333" << endl;

		cout << "2:" << ss.str() << endl;
		cout << "END." << endl;
	}

	void tmp6() {

		std::queue<int> q1{};
		q1.push(5);
		q1.push(4);
		q1.push(3);
		q1.push(2);

		while (!q1.empty()) {
			int data = q1.front();
			q1.pop();
			cout << "data:" << data << endl;
		}

	}

	void tmp7() {

		std::list<int> q1{};
		q1.push_back(5);
		q1.push_back(4);
		q1.push_back(3);
		q1.push_back(2);

		while (!q1.empty()) {
			int data = q1.front();
			q1.pop_front();
			cout << "data:" << data << endl;
		}

	}

	void tmp8() {
		std::default_random_engine random(123475);
		std::uniform_int_distribution<int> dis1(0, 100);
		std::uniform_real_distribution<double> dis2(0.0, 1.0);

		cout << "dis1: ";
		for (auto i : vector<int>{ 1, 2, 3, 4, 5, 6 }) {
			cout << dis1(random) << ", ";
		}
		cout << endl;


		cout << "dis2: ";
		for (auto i : vector<int>{ 1, 2, 3, 4, 5, 6 }) {
			cout << dis2(random) << ", ";
		}
		cout << endl;
	}


	class AA9 {
	public:
		int data = 100;

		AA9() {
			cout << "Default constructor" << endl;
		}

		AA9(const AA9& a) {
			data = a.data;
			cout << "Copy constructor." << endl;
		}	

		AA9(AA9&& a) noexcept {
			data = a.data;
			cout << "Move constructor." << endl;
		}
	};

	AA9 getAA9() {
		AA9 a{};
		--a.data;
		--a.data;
		--a.data;
		--a.data;
		cout << "data:" << a.data << endl;

		return a;
	}

	void tmp9() {

		auto d = getAA9();
		cout << "Done. data:" << d.data << endl;

	}

}

void tmpTest2() {
	tmp9();
}





