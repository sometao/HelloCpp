#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include <windows.h>
#include <chrono>

namespace threadTest {

	using std::string;
	using std::cout;
	using std::endl;
	using std::thread;
	using std::ref;
	using std::atomic;
	using std::chrono::system_clock;
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;


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

	void func5(atomic<int> (&c) ) {
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
		char *p1;
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

	void threadTest() {
		cout << "hello, thread." << endl;

		test6();

	}


}




