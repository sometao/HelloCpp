// helloVs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <iomanip>
#include <string>


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



int main() {


    startCalculator();



}


void testRef() {

    // 声明简单的变量
    int    i;
    double d;

    // 声明引用变量
    int& r = i;
    double& s = d;

    i = 5;
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r << endl;

    i += 1;
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r << endl;


    d = 11.7;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s << endl;

    s += 1;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s << endl;

}

void testPoint() {

    int foo = 10;
    int *ip;
    ip = &foo;

    cout << "Value of var variable: ";
    cout << foo << endl;

    // 输出在指针变量中存储的地址
    cout << "Address stored in ip variable: ";
    cout << ip << endl;

    // 访问指针中地址的值
    cout << "Value of *ip variable: ";
    cout << *ip << endl;



}

void testAddr() {

    int var1;
    char var2[10];
    cout << "var1 address:" << &var1 << endl;
    cout << "var2 address:" << &var2 << endl;


}

void testString() {
    string str1 = "Hello";
    string str2 = "World";
    string str3;
    int  len;

    // 复制 str1 到 str3
    str3 = str1;
    cout << "str3 : " << str3 << endl;

    // 连接 str1 和 str2
    str3 = str1 + str2;
    cout << "str1 + str2 : " << str3 << endl;

    // 连接后，str3 的总长度
    len = str3.size();
    cout << "str3.size() :  " << len << endl;

}

void testCharArr() {


    char greeting1[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    char greeting2[] = "World";

    cout << "Greeting message: " << endl;
    cout << greeting1 << endl;
    cout << greeting2 << endl;

}

void testArray() {

    int arr1[5] = {1,2,3,4,5};
    int arr2[] = {1,2,3,4,5,6};

    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10 + i;
    }

    cout << "Element" << setw(13) << "Value" << endl;

    for (int i = 0; i < 5; i++) {
        cout << setw(7) << i << setw(13) << arr1[i] << endl;
    }

    return;


}


void testLambda() {
    auto func1 = [](int y) -> int { return y + 10; };
    function<int(int)> func2 = [](int y) -> int { return y - 10; };
    int a = 100;
    int b = func1(a);
    int c = func2(a);

    cout << "a:" << a << "  b:" << b << endl;
    cout << "a:" << a << "  c:" << c << endl;
    return;
}

void showSize() {


    cout << "\t最大值：" << (numeric_limits<bool>::max)();
    cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;

    cout << "char: \t\t" << "所占字节数：" << sizeof(char);
    cout << "\t最大值：" << (numeric_limits<char>::max)();
    cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;

    cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
    cout << "\t最大值：" << (numeric_limits<signed char>::max)();
    cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;

    cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
    cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();
    cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;

    cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
    cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();
    cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;

    cout << "short: \t\t" << "所占字节数：" << sizeof(short);
    cout << "\t最大值：" << (numeric_limits<short>::max)();
    cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;

    cout << "int: \t\t" << "所占字节数：" << sizeof(int);
    cout << "\t最大值：" << (numeric_limits<int>::max)();
    cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;

    cout << "long int: \t" << "所占字节数：" << sizeof(long int);
    cout << "\t最大值：" << (numeric_limits<long int>::max)();
    cout << "\t最小值：" << (numeric_limits<long int>::min)() << endl;

    cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);
    cout << "\t最大值：" << (numeric_limits<unsigned>::max)();
    cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;

    cout << "long: \t\t" << "所占字节数：" << sizeof(long);
    cout << "\t最大值：" << (numeric_limits<long>::max)();
    cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;

    cout << "long long: \t" << "所占字节数：" << sizeof(long long);
    cout << "\t最大值：" << (numeric_limits<long long>::max)();
    cout << "\t最小值：" << (numeric_limits<long long>::min)() << endl;

    cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
    cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();
    cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;

    cout << "double: \t" << "所占字节数：" << sizeof(double);
    cout << "\t最大值：" << (numeric_limits<double>::max)();
    cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;

    cout << "long double: \t" << "所占字节数：" << sizeof(long double);
    cout << "\t最大值：" << (numeric_limits<long double>::max)();
    cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;

    cout << "float: \t\t" << "所占字节数：" << sizeof(float);
    cout << "\t最大值：" << (numeric_limits<float>::max)();
    cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;

    cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
    cout << "\t最大值：" << (numeric_limits<size_t>::max)();
    cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;

    cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;
    // << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;  

    cout << "type: \t\t" << "************size**************" << endl;
    return;
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
