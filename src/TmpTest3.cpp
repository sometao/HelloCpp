#include <string>
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <random>
#include <typeinfo>
#include "EasyWay.h"


namespace tmp_test3
{
	using std::cout;
	using std::endl;
	using std::vector;
	using std::string;
	using std::exception;


	class C01 {
	public:
		C01() = default;
		C01(const C01& c) = default;
		C01(C01&& c) noexcept = default;
		C01& operator=(const C01& c) = default;
		string data = "C01";
	};


	class C01a {
	public:
		C01a(const string& a) : data(a) {
			cout << "C01a default constructor." << endl;
		};

		C01a(const C01a& c) {
			cout << "C01a copy constructor: data=" << c.data << endl;
			data = c.data;
		};

		C01a(C01a&& c) noexcept {
			cout << "C01a move constructor. data=" << c.data << endl;
			data = c.data;
			c.data = "";
		};

		//not a constructor, so it must be construted before assigning a new value.
		C01a& operator= (const C01a& c) {
			cout << "C01a assign constructor. data[" << data << "] to [" << c.data << "]" << endl;
			this->data = c.data;
			return *this;
		};

		~C01a() {
			cout << "C01a Destructor: data=" << data << endl;
		};

		string data = "C01a";
	};



	void tmp01() {
		cout << "----------  1  ------------" << endl;
		C01a c{ "hello" };
		cout << "----------  2  ------------" << endl;
		C01a c1 = c;
		cout << "----------  2a  ------------" << endl;
		C01a c1a{ "hi" };
		c1a = c;
		cout << "----------  3  ------------" << endl;
		auto c2{ c };
		cout << "----------  4  ------------" << endl;
		auto c3{ std::move(c) };
		cout << "----------  5  ------------" << endl;
	};

	class C02 {
	public:
		C01a data1;
		C02(C01a& d) : data1(d) {
			cout << "C02 default 1 constructor." << endl;
		};

		C02(C01a&& d) : data1(std::move(d)) {
			cout << "C02 default 2 constructor." << endl;
		};
	};

	void tmp02() {
		C02* c02 = nullptr;
		{
			cout << " -------------------  1  ------------------" << endl;
			C01a d{ "Hello" };
			cout << " -------------------  2  ------------------" << endl;
			//C02 t{ std::move(d) };
			cout << "[" << &d << "]" << endl;
			C02 t{ d };
			cout << "[" << &(t.data1) << "]" << endl;
			cout << " -------------------  3  ------------------" << endl;
			c02 = &t;
			cout << "[" << &(c02->data1.data) << "]" << endl;
			cout << " -------------------  4  ------------------" << endl;
			cout << "[" << d.data << "]" << endl;
			cout << "[" << t.data1.data << "]" << endl;
			cout << "[" << c02->data1.data << "]" << endl;
			cout << " -------------------  5  ------------------" << endl;
			d.data = "World";
			cout << "[" << d.data << "]" << endl;
			cout << "[" << t.data1.data << "]" << endl;
			cout << "[" << c02->data1.data << "]" << endl;
			cout << " -------------------  6  ------------------" << endl;
			t.data1.data = "!!!";
			cout << "[" << d.data << "]" << endl;
			cout << "[" << t.data1.data << "]" << endl;
			cout << "[" << c02->data1.data << "]" << endl;
		}
		cout << " -------------------  7  ------------------" << endl;
		cout << "[" << &(c02->data1.data) << "]" << endl;
		cout << "[" << c02->data1.data << "]" << endl;
	}


	void func03a1(C01a c) {
		cout << "func03b, c.data=" << c.data << endl;
	}

	void func03a2(C01a& c) {
		cout << "func03b, c.data=" << c.data << endl;
	}


	void func03b() {
		C01a x{ "Hello" };
		cout << "1 ------------" << endl;
		func03a1(x);
		//func03a2(x);
		cout << "2 ------------" << endl;
		C01a& y = x;
		cout << "3 ------------" << endl;
		func03a1(y);
		//func03a2(y);
		cout << "4 ------------" << endl;
	}

	void tmp03() {
		func03b();
	}



	void func04a(C01a& c) {

		for (int i = 0; i < 5; i++) {
			cout << "func04a, c.data=" << c.data << endl;
			EasyWay::sleep(700);
		}

	}

	void func04b() {
		C01a x{ "hello" };
		thread t(func04a, std::ref(x));
		cout << "func04b, thread started." << endl;
		t.detach();
		EasyWay::sleep(2000);
		cout << "go out func04b" << endl;
	}

	void tmp04() {
		func04b();
		cout << "func04b finished." << endl;
		EasyWay::sleep(2000);
		cout << "END." << endl;
	}

	auto func1 = [](const string& data, int begin, int end) {
		return data.substr(begin, end);
	};

	struct LoginEvent {
		LoginEvent(const string& u, const string& p) : username(u), passwd(p) {};

		LoginEvent(const string& data) :
			username(func1(data, 0, 6)),passwd(func1(data, 6, data.size())) {
		}


		const string username;
		const string passwd;
	};


	void tmp05() {

		stringstream ss{};
		ss << "1 hello world.\nok   thank  \n you.";
		cout << "ss:" << ss.str() << endl;

		string s{};
		int c = 0;
		while (ss >> s && c < 3) 
		{
			c += 1;
			cout << "s: [" << s << "]" << endl;
			cout << "--------------------- c = " << c << endl;
		}
	}

	void tmp06() {
		stringstream ss{};
		ss.str("4|12356789|ok.");
		const int len = 1024;
		char buff[len]{};
		while (ss.getline(buff, len, '|')) {
			cout << "buff [" << buff << "]" << endl;
		}
	}

	enum class Color {Red, Green, Blue};

	void tmp07() {
		int c = static_cast<int>(Color::Red);
		cout << "c:" << c << endl;
	}

	void tmp08() {
		string s{ "0abc" };
		cout << s[0] << endl;
		cout << (s[0] == '0') << endl;
		cout << (s[0] == 'x') << endl;
	}

}

void tmpTest3() {
	using namespace tmp_test3;
	tmp08();
}





