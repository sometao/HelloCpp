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
    int *ip;
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





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
