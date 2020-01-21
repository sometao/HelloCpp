#include "stdafx.h"
#include <iostream>

using namespace std;

void startCalculator();
void testLambda();
void testArray();
void showSize();
void testCharArr();
void testString();
void testAddr();
void testPoint();
void testRef();


void testBook();
void testStruct();
int socketLaunch(int a, char* b[]);
int chatServerLaunch(int a, char* b[]);


void tmpTest1();

int main(int argc, char* argv[]) {

    

    cout << "welcome to Cpp." << endl;
    cout << "argc=" << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }
    chatServerLaunch(argc, argv);

    //tmpTest1();
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


