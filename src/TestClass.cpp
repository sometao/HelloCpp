
#include <iostream>
#include <string>

using namespace std;

class Book {

public:
	string title;
	string author;
	double prize;
	string toString() {
		string rst = "book:[" + title + "] writed by [" + author + "] prize: [" + to_string(prize) + "]";
		return rst;
	}

	Book operator+(const Book& other) {
		Book rst;
		rst.title = this->title + "." + other.title;
		rst.author = this->author + "." + other.author;
		rst.prize = this->prize + other.prize;
		return rst;
	}

private:
	string p1;
	string p2; 
	string p3;

};

class SchoolBook : public Book {

	string age = title;

};



void testBook() {

	Book b1;
	Book b2;

	b1.title = "English";
	b1.author = "LiLei";
	b1.prize = 32.5;

	b2.title = "Math";
	b2.author = "xiaozhang";
	b2.prize = 59.5;


	cout << b1.title << "\n";
	cout << b1.author << "\n";
	cout << b1.prize << "\n" << endl;

	cout << " ------- b1 ------- \n";
	cout << b1.toString() << endl;

	Book b3 = b1 + b2;

	cout << " -------- b3 ------ \n";
	cout << b3.toString() << endl;


}


