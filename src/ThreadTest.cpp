#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include <windows.h>
#include <chrono>
#include <vector>
#include <functional>
#include <random>
#include "EasyWay.h"

using std::string;
using std::cout;
using std::endl;
using std::thread;
using std::ref;
using std::vector;
using std::atomic;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


namespace
{

	void func1(string name) {

		auto id0 = std::this_thread::get_id();

		for (int i = 0; i < 1000; i++) {
			auto id = std::this_thread::get_id();
			if (id0 != id) {
				cout << "thread [" << id0 << "] change to [" << id << "]" << endl;
				id0 = id;
			}

			cout << name << ":  [  " << id << "  ]  count:-------[ " << i << " ]" << endl;
		}
		cout << "[" << id0 << "]" << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! finish." << endl;
	}

	void func2(char* data, int len) {

		auto id0 = std::this_thread::get_id();

		for (int i = 0; i < 100; i++) {
			cout << "[" << id0 << "] count - [" << i << "]: " << data << endl;
		}

	}

	void func3(int& i) {
		auto id0 = std::this_thread::get_id();


		for (int j = 0; j < 10000; j++) {
			i++;
			//cout << id0 << ": ----------------  i= [" << i << "]" << endl;
		}

		cout << id0 << ":  i=" << i << endl;
	}



	void func4(int& counter, std::mutex& m) {
		auto id0 = std::this_thread::get_id();
		for (int j = 0; j < 1000; j++) {
			m.lock();
			counter++;
			Sleep(1);
			m.unlock();
		}
		cout << id0 << ":  i=" << counter << endl;
	}


	void test4() {

		int c{ 0 };
		std::mutex m{};

		auto  start = system_clock::now();



		thread t1(func4, ref(c), ref(m));
		thread t2(func4, ref(c), ref(m));
		thread t3(func4, ref(c), ref(m));
		thread t4(func4, ref(c), ref(m));

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		auto end = system_clock::now();

		milliseconds duration{ duration_cast<milliseconds>(end - start) };

		cout << "time:" << duration.count() << endl;
	}

	void func5(atomic<int>(&c)) {
		auto id0 = std::this_thread::get_id();

		for (int j = 0; j < 1000; j++) {
			c++;
			Sleep(1);
		}

		cout << id0 << ":  i=" << c.load() << endl;
	}




	void test5() {

		atomic<int> c{ 0 };
		auto  start = system_clock::now();

		thread t1(func5, ref(c));
		thread t2(func5, ref(c));
		thread t3(func5, ref(c));
		thread t4(func5, ref(c));

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		auto end = system_clock::now();

		milliseconds duration{ duration_cast<milliseconds>(end - start) };

		cout << "time:" << duration.count() << endl;
	}



	void test3() {
		int i = 100;
		thread t1(func3, ref(i));
		thread t2(func3, ref(i));
		thread t3(func3, ref(i));
		thread t4(func3, ref(i));
		t3.join();
		t4.join();

		t1.join();
		t2.join();
	}

	void test2() {
		char* p1;
		char d1[] = "²âÊÔÊý¾Ý×Ö·û´®";
		int len1 = sizeof(d1) / sizeof(d1[0]);
		p1 = d1;

		char* p2;
		char d2[] = "¹þ¹þ";
		int len2 = sizeof(d2) / sizeof(d2[0]);
		p2 = d2;
		thread t1(func2, p1, len1);
		thread t2(func2, p2, len2);
	}

	void test1() {
		thread t1(func1, "Ð¡Íõ");
		thread t2(func1, "´óÁõ");
	}


	void func6(int& c, std::condition_variable& cv, std::mutex& m) {

		auto id0 = std::this_thread::get_id();

		cout << "[" << id0 << "] before locking..." << endl;
		std::unique_lock<std::mutex> lk(m);
		cout << "[" << id0 << "] locked." << endl;


		for (int i = 0; i < 100; i++) {
			cout << "[" << id0 << "] before wait." << endl;
			Sleep(1);
			cout << "[" << id0 << "] before wait." << endl;
			Sleep(1);
			cout << "[" << id0 << "] before wait." << endl;
			Sleep(1);
			cout << "[" << id0 << "] goto wait  ------------------------------------------" << endl;

			cv.wait(lk, [&c] {return c > 0; });
			//cv.wait(lk);
			cout << "[" << id0 << "] left wait  ------------------------------------------" << endl;


			for (int j = 0; j < 3 && c>0; j++) {
				Sleep(1);
				c -= 1;
				cout << "[" << id0 << "] working: -1, c=" << c << endl;
			}
		}
	}


	void test6() {
		int c{ 0 };
		std::condition_variable cv{};
		std::mutex m{};

		thread t1(func6, ref(c), ref(cv), ref(m));
		thread t2(func6, ref(c), ref(cv), ref(m));
		thread t3(func6, ref(c), ref(cv), ref(m));


		for (int i = 0; i < 5; i++) {
			{
				cout << i << "  ------------------[MAIN] before lock." << endl;
				std::lock_guard<std::mutex> lk(m);
				cout << i << "  ------------------[MAIN] locked." << endl;
				c += 10;
				cout << i << "  ------------------[MAIN] +10 unlock c=" << c << endl;
			}
			cout << i << "  ------------------[MAIN] before notify all." << endl;
			cv.notify_all();
			cout << i << "  ------------------[MAIN] after notify all." << endl;
			Sleep(50);

		}




		t1.detach();
		t2.detach();
		t3.detach();

		cout << "WAITING..." << endl;
		Sleep(5000);
		cout << "DONE." << endl;


	}

	void func7a(int& i) {
		cout << "before, i=" << i << endl;
		++i;
		cout << "after, i=" << i << endl;

	}

	void test7() {

		int i{ 0 };

		thread t0;
		thread t1{ func7a, ref(i) };

		t0 = std::move(t1);

		cout << "----------------" << endl;
		cout << i << endl;

		t0.join();
	};



	class AA8 {


		vector<int> data{ 1, 2, 3, 4 };

		void func8() {
			for (int i : data) {
				Sleep(300);
				cout << i << endl;
			}
		}

		static void func8a(AA8& a) {
			for (int i : a.data) {
				Sleep(300);
				cout << i << endl;
			}
		}

		friend void func8b(AA8& a);

	public:
		AA8();
	};

	void func8b(AA8& a) {
		for (int i : a.data) {
			Sleep(300);
			cout << i << endl;
		}
	};

	AA8::AA8() {
		thread t1{ std::mem_fn(&AA8::func8), ref(*this) }; // ok
		//thread t1{ AA8::func8a, ref(*this) }; //ok
		//thread t1{ func8b, ref(*this) }; //if the Constructor in class, this line can not see func8b;
		t1.detach();
		cout << "AA8 created." << endl;
	}

	void test8() {

		AA8 a{};

		Sleep(5000);
		cout << "Done." << endl;
	}


	void func9worker(int id, std::condition_variable& cv, std::mutex& m) {
		using namespace std::chrono_literals;


		auto random = EasyWay::uniformIntDistribution(0, 100);


		bool isDone = false;

		std::unique_lock<std::mutex> lk{ m, std::defer_lock };
		while (true)
		{
			{
				cout << "----------------------  id[" << id << "] after create lock. lk.owns_lock()=" << lk.owns_lock() << endl;

				auto check = [&] {
					int n = random();
					cout << "id[" << id << "] awake. check[" << n << "]. lk.owns_lock()=" << lk.owns_lock() << endl;
					return n < 30;
				};
				for (auto i : vector<int>{ 1,2,3,4,5 }) {
					cout << "----------------------  id[" << id << "] before wait. owns_lock()=" << lk.owns_lock() << endl;
					std::this_thread::sleep_for(1000ms);
				}

				cout << "----------------------  id[" << id << "] before lock. owns_lock()=" << lk.owns_lock() << endl;
				lk.lock();
				cout << "id[" << id << "] after lock. owns_lock()=" << lk.owns_lock() << endl;
				cout << "id[" << id << "] goto wait." << endl;

				if (cv.wait_for(lk, 10ms, check)) {
					cout << "id[" << id << "] out wait success. owns_lock()=" << lk.owns_lock() << endl;
					for (auto i : vector<int>{ 1,2,3,4,5 }) {
						cout << "id[" << id << "] keep success. owns_lock()=" << lk.owns_lock() << endl;
						cv.notify_all();
						std::this_thread::sleep_for(1000ms);
					}
					cout << "id[" << id << "] finish success. owns_lock()=" << lk.owns_lock() << endl;
				} else {
					cout << "id[" << id << "] wait timeout" << endl;
					for (auto i : vector<int>{ 1,2,3,4,5 }) {
						cout << "id[" << id << "] keep timeout. owns_lock()=" << lk.owns_lock() << endl;
						cv.notify_all();
						std::this_thread::sleep_for(1000ms);
					}
					cout << "id[" << id << "] finish timeout. owns_lock()=" << lk.owns_lock() << endl;
				}
				cout << "id[" << id << "] before unlock. owns_lock()=" << lk.owns_lock() << endl;
				lk.unlock();
				cout << "----------------------  id[" << id << "] after unlock. owns_lock()=" << lk.owns_lock() << endl;
				cv.notify_all();

			}

			cv.notify_all();

			//for (auto i : vector<int>{ 1,2,3,4,5 }) {
			//	cout << "id[" << id << "] while last lines." << endl;
			//	cv.notify_all();
			//	std::this_thread::sleep_for(1000ms);
			//}


		}
	}

	void test9() {
		using namespace std::chrono_literals;

		std::mutex m;
		std::condition_variable cv;

		thread w101{ func9worker, 222, ref(cv), ref(m) };
		thread w102{ func9worker, 555, ref(cv), ref(m) };
		thread w103{ func9worker, 888, ref(cv), ref(m) };
		thread w104{ func9worker, 999, ref(cv), ref(m) };


		w101.join();
		w102.join();
		w103.join();
		w104.join();

	}


	void func10(int id, std::condition_variable& cv, std::mutex& m) {

		//using namespace std::chrono_literals;
		using ew = EasyWay;


		while (true) {

			{
				std::unique_lock<std::mutex> lk{ m };

				auto check =
					[&] {
					cout << id << ": awacke and check. lock=" << lk.owns_lock() << endl;
					return false;
				};

				//auto notTimeout = cv.wait_for(lk, 100ms, check);
				//if (notTimeout) {
				//	for (auto i : ew::range(1, 1000)) {
				//		cout << id << ": working lock=" << lk.owns_lock() << endl;
				//		ew::sleep(1000);
				//		cv.notify_all();
				//	}
				//} else {
				//	for (auto i : ew::range(1, 10)) {
				//		ew::sleep(1000);
				//		cout << id << ": timeout lock=" << lk.owns_lock() << endl;
				//		ew::sleep(1000);
				//	}
				//}


				cv_status isTimeout = cv.wait_for(lk, 100ms);
				switch (isTimeout) {
					case cv_status::no_timeout:
						cout << id << " :  No Timeout. lock=" << lk.owns_lock() << endl;
						ew::sleep(200);
						break;
					case cv_status::timeout:
						cout << id << " : Timeout. lock=" << lk.owns_lock() << endl;
						ew::sleep(200);
						break;
				}

			}
			cv.notify_all();
			ew::sleep(100);


		}

	}

	void test10() {

		std::mutex m{};
		std::condition_variable cv{};

		std::thread t1(func10, 1, ref(cv), ref(m));
		std::thread t2(func10, 2, ref(cv), ref(m));
		std::thread t3(func10, 3, ref(cv), ref(m));
		std::thread t4(func10, 4, ref(cv), ref(m));


		t1.join();
		t2.join();
		t3.join();
		t4.join();



	}


	void func11a(int id, std::mutex& m) {

		while (true)
		{
			auto v = EasyWay::range(1, 6);
			{
				cout << "[" << id << "] func11 try lock ----------------" << endl;
				unique_lock<std::mutex> lk{ m };
				cout << "[" << id << "] func11 go working ----------------" << endl;
				
				for (auto i : v) {
					cout << "[" << id << "] func11 working ----------------" << endl;
					EasyWay::sleep(1500);
				}
			}
			EasyWay::sleep(100);

		}
	}

	void func11b(int id, std::mutex& m) {
		while (true)
		{
			cout << "---------------- [" << id << "] func11 try lock" << endl;
			m.lock();
			cout << "---------------- [" << id << "] func11 go working" << endl;
			for (auto i : EasyWay::range(1, 6)) {
				cout << "---------------- [" << id << "] func11 working" << endl;
				EasyWay::sleep(2000);
			};
			m.unlock();
			EasyWay::sleep(800);
		}
	}

	void test11() {

		std::mutex m{};

		thread t1{func11a, 101, ref(m)};
		thread t2{func11a, 102, ref(m)};

		thread t3{func11b, 301, ref(m)};
		thread t4{func11b, 302, ref(m)};

		t1.join();
		t2.join();
		t3.join();
		t4.join();

	}


}




void threadTest() {
	cout << "hello, thread." << endl;

	test11();
}



