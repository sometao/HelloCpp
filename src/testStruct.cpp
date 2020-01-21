
#include <iostream>


/*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 */
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

struct sockaddr_in {
	short   sin_family;
	u_short sin_port;
	char    sin_zero[8];
};

typedef sockaddr_in SOCKADDR_IN1;
typedef struct sockaddr_in SOCKADDR_IN2;

using namespace std;

void testStruct() {

	SOCKADDR_IN1 in1 = { 0 , 1, 'b', 'b', 'b' };
	SOCKADDR_IN2 in2 = { 2 , 2, 'a' , 'a' };

	cout << "in1: " << sizeof(in1) << endl;
	cout << "in2: " << sizeof(in2) << endl;
	cout << "in1: " << in1.sin_family << endl;
	cout << "in2: " << in2.sin_family << endl;

	cout << "in1: " << in1.sin_port << endl;
	cout << "in2: " << in2.sin_port << endl;

	cout << "in1: " << in1.sin_zero << endl;
	cout << "in2: " << in2.sin_zero << endl;


}

