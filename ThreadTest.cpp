#include <thread>
#include <iostream>

using namespace std;


void func1(string name) {

	auto id0 = this_thread::get_id();

	for (int i = 0; i < 1000; i ++) {
		auto id = this_thread::get_id();
		if (id0 != id) {
			cout << "thread [" << id0 << "] change to [" << id << "]" << endl;
			id0 = id;
		}

		cout << name << ":  [  " << id << "  ]  count:-------[ " << i << " ]" << endl;
	}
	cout << "[" << id0 << "]"<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! finish." << endl;
}



void func2(char* data, int len) {

	auto id0 = this_thread::get_id();

	for (int i = 0; i < 100; i++) {
		cout << "[" << id0 << "] count - [" << i << "]: " << data  << endl;
	}

}

void func3(int& i) {
	auto id0 = this_thread::get_id();


	for (int j = 0; j < 100000; j++) {
		i++;
		//cout << id0 << ": ----------------  i= [" << i << "]" << endl;
	}

	cout << id0 << ":  i=" << i << endl;



}



void threadTest() {

	cout << "hello, thread." << endl;
	//thread t1(func1, "Ð¡Íõ");
	//thread t2(func1, "´óÁõ");

	//char *p1;
	//char d1[] = "²âÊÔÊý¾Ý×Ö·û´®";
	//int len1 = sizeof(d1) / sizeof(d1[0]);
	//p1 = d1;
	//	
	//char *p2;
	//char d2[] = "¹þ¹þ";
	//int len2 = sizeof(d2) / sizeof(d2[0]);
	//p2 = d2;

	//thread t1(func2, p1, len1);
	//thread t2(func2, p2, len2);


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


