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


namespace tmp_test2
{
	using std::cout;
	using std::endl;
	using std::vector;
	using std::string;
	using std::exception;


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

		AA9(int d) : data{ d } {
			cout << "Default constructor with data=" << d << endl;
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

	struct Msg {
		std::string msgType{ "" };
		int id{ -10 };
	};

	struct Login : Msg {
		Login(string cmd, int id, string _username) : Msg{ cmd, id }, username(_username) {};
		std::string username{ "" };
	};


	void tmp10() {

		//Msg m{"haha",123};
		Msg m = { "xxxx" };
		//m.msgType = "unknown";

		cout << m.msgType << endl;
		cout << m.id << endl;

		cout << "---------" << endl;

		Login l{ "a", 100, "b" };
		cout << l.msgType << endl;
		cout << l.id << endl;
		cout << l.username << endl;
	}


	void tmp11() {
		using namespace std;


		vector<shared_ptr<AA9>> vec1{};
		shared_ptr<AA9> p1{ new AA9{200} };
		vec1.push_back(p1);



		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

		p1->data = -10;
		cout << "----------" << endl;
		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

	}

	class AA11a {
	public:
		int data = 100;

		AA11a() {
			cout << "Default constructor" << endl;
		}

		AA11a(int d) : data{ d } {
			cout << "Default constructor with data=" << d << endl;
		}

		AA11a(const AA11a& a) {
			data = a.data;
			cout << "Copy constructor." << endl;
		}

		AA11a(AA11a&& a) noexcept {
			data = a.data;
			cout << "Move constructor." << endl;
		}
	};

	void tmp11a() {
		using namespace std;


		vector<shared_ptr<const AA11a>> vec1{};
		shared_ptr<const AA11a> p1{ new AA11a{200} };
		vec1.push_back(p1);

		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

		//p1->data = -10;
		cout << "----------" << endl;
		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

	}

	void tmp11b() {
		using namespace std;

		vector<shared_ptr<const AA11a>> vec1{};
		shared_ptr<const AA11a> p1 = make_shared<const AA11a>(100);

		vec1.push_back(p1);

		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

		//p1->data = -10;
		cout << "----------" << endl;
		cout << "data vec1[0]: " << vec1[0]->data << endl;
		cout << "data p1: " << p1->data << endl;

	}


	void tmp12() {
		using namespace std;

		vector<unique_ptr<AA9>> vec2{};

		unique_ptr<AA9> p2{ new AA9{300} };


		//vec2.push_back(p2);  //compile error. 
		vec2.push_back(std::move(p2)); //ok
		//vec2.push_back(unique_ptr<AA9>{new AA9(200)}); //ok

		cout << "data vec2[0]: " << vec2[0]->data << endl;
		cout << "data p2: " << p2->data << endl;

		auto d1 = vec2[0]->data;
		auto d2 = std::move(vec2.back());

	}

	void tmp13() {

		auto a1 = new AA9();

		auto a2 = a1;

		cout << a1->data << endl;
		cout << a2->data << endl;
		cout << "--------" << endl;

		a1->data = -10;

		cout << a1->data << endl;
		cout << a2->data << endl;

		cout << "--------" << endl;
		cout << "--------" << endl;
		cout << "--------" << endl;
		cout << "--------" << endl;


		AA9* b1 = new AA9();

		AA9* b2 = b1;

		cout << (*b1).data << endl;
		cout << (*b2).data << endl;
		cout << "--------" << endl;

		b1->data = -10;

		cout << (*b1).data << endl;
		cout << (*b2).data << endl;
		cout << "--------" << endl;
		cout << "--------" << endl;
		cout << "--------" << endl;
		cout << "--------" << endl;

	}


	void tmp14() {
		const int& a1 = 10;
		int a2 = 10;
		const int* a3 = &a2;
	}

	void func15a(int a, int b) {


		cout << "func15a begin: a=" << a << ", b=" << b << endl;

		if (a < b) {
			cout << "a < b [throw str ×ÖÃæÁ¿]" << endl;
			throw "a < b is not good.";
		} else if (a == b) {
			cout << "a == b [throw int a]" << endl;
			throw a;
		} else if (b == 5) {
			cout << "b == 5 [throw int& a1]" << endl;
			int& a1 = a;
			throw a1;
		} else if (b == 4) {
			cout << "b == 4 [ a / 0]" << endl;
			double x = a / 0.0;
			cout << x << endl;
		} else if (b == 3) {
			cout << "b == 3 [nullptr]" << endl;
			int* p;
			p = &a;
			p = 0;
			try {
				cout << "nullptr:" << (*p - 10) << endl;
			} catch (...) {
				cout << "use nullptr" << endl;
			}

		} else if (b == 2) {
			cout << "b == 2 throw [string]" << endl;
			string a = "hahah";
			const string& b = a;
			throw b;
		} else {
			cout << "nothing throw." << endl;
		}

		cout << " ---------------------- func15a done ---------------------" << endl;


	}

	void tmp15() {

		try {
			func15a(5, 2);
		} catch (const char* ch) {
			cout << "catch char* = [" << ch << "]" << endl;
		} catch (int& ex) {
			cout << "catch int  & = [" << ex << "]" << endl;
		} catch (string & ex) {
			cout << "const catch string = [" << ex << "]" << endl;
		} catch (exception & ex) {
			cout << "catch exception& = [" << ex.what() << "]" << endl;
		} catch (...) {
			cout << "unknown issue." << endl;
		}
	}


	void tmp16() {
		std::list<std::shared_ptr<string>> ls{};

		for (auto i : EasyWay::range(1, 5)) {
			string s{ "data:" };
			s += std::to_string(i);
			ls.emplace_back(new string(s));
			s = s.substr(0, s.size() - 1);
			s += std::to_string(i + 100);
			ls.push_back(make_shared<string>(s));
		}

		for (auto p : ls) {
			cout << *p << endl;
		}


		std::shared_ptr<string> h1;

		cout << "-----------  h1: " << (h1 == nullptr) << endl;
		h1 = ls.front();
		cout << " --------------- h1: " << (h1 == nullptr) << endl;

		auto h = ls.front();
		ls.pop_front();
		cout << "type h:" << typeid(h).name() << endl;
		cout << "h:" << h << endl;
		cout << "*h:" << *h << endl;

		cout << "2. ---------------" << endl;


		for (auto p : ls) {
			cout << *p << endl;
		}

	}


	struct C17 {
		const string d;
		C17(string d_) : d(d_) {};
		virtual void getInfo() = 0;
		void getInfo1() {
			cout << "C17 getInfo1" << endl;
		};

		virtual void getInfo2() {
			cout << "C17 getInfo2" << endl;
		};


	};

	struct C17a : public C17 {
		const string a;
		C17a(string a_) : C17{ "FOO" }, a(a_) {}
		void getInfo() {
			string info{ "a=" };
			info += a;
			cout << info << endl;
		}

		void getInfo1() {
			string info{ "a=" };
			info += a;
			cout << "C17a getInfo1:" << info << endl;
		}

		void getInfo2() override {
			cout << "C17a getInfo2:..." << endl;
		}
	};

	struct C17b : public C17a {
		C17b() : C17a("FromC17b") {}
		void getInfo2() {
			cout << "C17b getInfo2:..." << endl;
		}

	};

	void tmp17() {
		C17a ca("haha!");
		ca.getInfo();

		cout << "-----------" << endl;
		ca.getInfo1();
		cout << "-----------" << endl;
		ca.C17::getInfo1();


		cout << "-----------" << endl;
		ca.getInfo2();
		cout << "-----------" << endl;
		ca.C17::getInfo2();
		cout << endl;
		cout << endl;

		cout << " +++++++++" << endl;
		cout << " +++++++++" << endl;
		cout << " +++++++++" << endl;
		cout << " +++++++++" << endl;

		cout << endl;
		cout << endl;

		C17b cb{};
		cout << "-----------" << endl;
		cb.getInfo2();
		cb.C17a::getInfo2();
		cb.C17::getInfo2();


		C17& cb1 = cb;
		C17a& cb2 = cb;
		cout << "-----------" << endl;
		cb1.getInfo1();
		cb2.getInfo1();
		cb2.C17::getInfo1();
		cb2.C17a::getInfo1();


		cout << "-----------" << endl;
		cb1.getInfo2();
		cb2.getInfo2();
		cb2.C17::getInfo2();
		cb2.C17a::getInfo2();
	}




	class C18a {

	public:
		virtual void foo() {};
		virtual void bar() {};
		int a = 10;
		int a1 = 50;
		int a2 = 50;
	};

	class C18b : public C18a {
	public:
		void foo() override {
			cout << "heh" << endl;
		}
		string b = "BBbbbbbbb";
		int b1 = 20;
	};

	class C18c : public C18a {
	public:
		string c = "hahahaha";
	};

	void tmp18() {
		std::vector<shared_ptr<C18a>> vec{};

		shared_ptr<C18a> p = make_shared<C18b>();
		cout << "p data:" << p->a << endl;
		//auto b2 = std::dynamic_pointer_cast<C18b>(p);
		auto b2 = std::static_pointer_cast<C18b>(p);
		cout << "b2 data1:" << b2->b << endl;
		cout << "b2 data2:" << b2->b1 << endl;


		//try {
		//	//auto b3 = std::dynamic_pointer_cast<C18c>(p);
		//	auto b3 = std::static_pointer_cast<C18c>(p);
		//	cout << "b3 data:" << b3->c << endl;
		//} catch (const exception & ex) {
		//	cout << "exception: " << ex.what() << endl;
		//} catch (...) {
		//	cout << "unknown exception." << endl;
		//}

	}
}

void tmpTest2() {
	using namespace tmp_test2;
	tmp18();
}





