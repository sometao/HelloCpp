#include <iostream>
#include <functional>
#include <iomanip>
#include <string>
#include "stdafx.h"
#include <typeinfo>

using namespace std;




void testRef() {

    // �����򵥵ı���
    int    i;
    double d;

    // �������ñ���
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
    int* ip;
    ip = &foo;

    cout << "Value of var variable: ";
    cout << foo << endl;

    // �����ָ������д洢�ĵ�ַ
    cout << "Address stored in ip variable: ";
    cout << ip << endl;

    // ����ָ���е�ַ��ֵ
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

    // ���� str1 �� str3
    str3 = str1;
    cout << "str3 : " << str3 << endl;

    // ���� str1 �� str2
    str3 = str1 + str2;
    cout << "str1 + str2 : " << str3 << endl;

    // ���Ӻ�str3 ���ܳ���
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

    int arr1[5] = { 1,2,3,4,5 };
    int arr2[] = { 1,2,3,4,5,6 };

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


    cout << "\t���ֵ��" << (numeric_limits<bool>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<bool>::min)() << endl;

    cout << "char: \t\t" << "��ռ�ֽ�����" << sizeof(char);
    cout << "\t���ֵ��" << (numeric_limits<char>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<char>::min)() << endl;

    cout << "signed char: \t" << "��ռ�ֽ�����" << sizeof(signed char);
    cout << "\t���ֵ��" << (numeric_limits<signed char>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<signed char>::min)() << endl;

    cout << "unsigned char: \t" << "��ռ�ֽ�����" << sizeof(unsigned char);
    cout << "\t���ֵ��" << (numeric_limits<unsigned char>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<unsigned char>::min)() << endl;

    cout << "wchar_t: \t" << "��ռ�ֽ�����" << sizeof(wchar_t);
    cout << "\t���ֵ��" << (numeric_limits<wchar_t>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<wchar_t>::min)() << endl;

    cout << "short: \t\t" << "��ռ�ֽ�����" << sizeof(short);
    cout << "\t���ֵ��" << (numeric_limits<short>::max)();
    cout << "\t\t��Сֵ��" << (numeric_limits<short>::min)() << endl;

    cout << "int: \t\t" << "��ռ�ֽ�����" << sizeof(int);
    cout << "\t���ֵ��" << (numeric_limits<int>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;

    cout << "long int: \t" << "��ռ�ֽ�����" << sizeof(long int);
    cout << "\t���ֵ��" << (numeric_limits<long int>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<long int>::min)() << endl;

    cout << "unsigned: \t" << "��ռ�ֽ�����" << sizeof(unsigned);
    cout << "\t���ֵ��" << (numeric_limits<unsigned>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<unsigned>::min)() << endl;

    cout << "long: \t\t" << "��ռ�ֽ�����" << sizeof(long);
    cout << "\t���ֵ��" << (numeric_limits<long>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<long>::min)() << endl;

    cout << "long long: \t" << "��ռ�ֽ�����" << sizeof(long long);
    cout << "\t���ֵ��" << (numeric_limits<long long>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<long long>::min)() << endl;

    cout << "unsigned long: \t" << "��ռ�ֽ�����" << sizeof(unsigned long);
    cout << "\t���ֵ��" << (numeric_limits<unsigned long>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<unsigned long>::min)() << endl;

    cout << "double: \t" << "��ռ�ֽ�����" << sizeof(double);
    cout << "\t���ֵ��" << (numeric_limits<double>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<double>::min)() << endl;

    cout << "long double: \t" << "��ռ�ֽ�����" << sizeof(long double);
    cout << "\t���ֵ��" << (numeric_limits<long double>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<long double>::min)() << endl;

    cout << "float: \t\t" << "��ռ�ֽ�����" << sizeof(float);
    cout << "\t���ֵ��" << (numeric_limits<float>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<float>::min)() << endl;

    cout << "size_t: \t" << "��ռ�ֽ�����" << sizeof(size_t);
    cout << "\t���ֵ��" << (numeric_limits<size_t>::max)();
    cout << "\t��Сֵ��" << (numeric_limits<size_t>::min)() << endl;

    cout << "string: \t" << "��ռ�ֽ�����" << sizeof(string) << endl;
    // << "\t���ֵ��" << (numeric_limits<string>::max)() << "\t��Сֵ��" << (numeric_limits<string>::min)() << endl;  

    cout << "type: \t\t" << "************size**************" << endl;
    return;
}


#include <cstring>

void changeArray(char* arr) {
    char data[] = "aaaaaa";
    strcpy_s(arr, 7, data);
    return;
}

void tmp1() {
    char target0[] = "hehehe";
    cout << target0 << endl;

    changeArray(target0);
    cout << target0 << endl;
}


void changeStr(string &s) {
    s = "bbb";
}


void tmp2() {
    string s1 = "aaa";
    cout << s1 << endl;

    string* sp;
    sp = &s1;

    changeStr(*sp);
    cout << s1 << endl;

}

void tmp3() {
    int value;
    cin >> value;
    cout << value << endl;
}


void tmp4A(int& n) {

    n += 1;
	cout << typeid(n).name() << endl;
	cout << n << endl;
    cout << "---------------------" << endl;
	cout << typeid(&n).name() << endl;
	cout << &n << endl;

}

void tmp4B(int* n) {

    *n += 1;
	cout << typeid(n).name() << endl;
	cout << n << endl;
    cout << "---------------------" << endl;
	cout << typeid(&n).name() << endl;
	cout << &n << endl;
}


void tmp4C(int n) {

    int* p;
    p = &n;
    *p += 1;
    
	cout << typeid(n).name() << endl;
	cout << n << endl;
    cout << "---------------------" << endl;
	cout << typeid(&n).name() << endl;
	cout << &n << endl;
}

void tmp4() {
    int c = 100;
    cout << "&c=" << &c << endl;

    cout << "\n" << endl;

    cout << "----  tmp4A ----------------." << endl;
    cout << "before c=" << c << endl;
    tmp4A(c);
    cout << "after c=" << c << endl;
    cout << "----  tmp4A DONE." << endl;

    cout << "\n\n";
    
    cout << "----  tmp4B ---------------" << endl;
    cout << "before c=" << c << endl;
    tmp4B(&c);
    cout << "after c=" << c << endl;
    cout << "----  tmp4B DONE." << endl;

    cout << "\n\n";

    
    cout << "----  tmp4C -----------" << endl;
    cout << "before c=" << c << endl;
    tmp4C(c);
    cout << "after c=" << c << endl;



}


void tmp5() {
    int i = 5, & r1 = i;  double d = 9.9, & r2 = d;
    r2 = 3.1415926;
    r2 = r1;
    i = r2;
    r1 = d;
    cout << i << endl;
    cout << r1 << endl;
    cout << d << endl;
    cout << r2 << endl;

}

void tmp6() {
    int i1 = 10;
    int& r1 = i1;
    const int& r2 = i1;
    
    const int i2 = 100;
    //int& r2 = i2;
    const int r3 = i2;

    const int* p1;
    int* p2;
    p1 = &i1;
    //p2 = &i2;
    

    //*p1 = 3;
    //*p2 = 3;
    p1 = &i2;


    int* const p3 = &i1;
    *p3 = i2;
    //p3 = &i2;


}


void tmp7() {
    int i = 0;
    //double* op = &i;
    //double* ip1 = i;
    double* ip2 = 0;
    int* p = &i;
}




void tmpTest1() {
    tmp5();
}





