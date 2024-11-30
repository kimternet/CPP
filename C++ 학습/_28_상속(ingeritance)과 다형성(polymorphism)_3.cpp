// ***************************************************************** //
// 가상 소멸자(virtual destructor)와 참조자(reference)의 참조 가능성 //
// ***************************************************************** //

// 예제 1: 메모리 누수(memory leak)


#include <iostream>

using namespace std;

class First
{
private:
    char* strOne;
public:
    First(const char str[])
    {
        strOne = new char[strlen(str) + 1];
    }
    ~First()
    {
        cout << "~First()" << endl;
        delete[] strOne;
    }
};

class Second : public First
{
private:
    char* strTwo;
public:
    Second(const char str1[], const char str2[]) : First(str1)
    {
        strTwo = new char[strlen(str2) + 1];
    }
    ~Second()
    {
        cout << "~Second()" << endl;
        delete[] strTwo;
    }
};


int main()
{
    First* ptr = new Second("simple", "complex");
    delete ptr;  // ~Second()는 호출되지 않음 (즉, 메모리 누수 발생!)

    return 0;
}

// 예제 2: 가상 소멸자(virtual destructor)
// 상속시 발생될 수 있는 메모리 누수 현상 차단

#include <iostream>

using namespace std;

class First
{
private:
    char* strOne;
public:
    First(const char str[])
    {
        strOne = new char[strlen(str) + 1];
    }
    virtual ~First()  // 가상 소멸자
    {
        cout << "~First()" << endl;
        delete[] strOne;
    }
};

class Second : public First
{
private:
    char* strTwo;
public:
    Second(const char str1[], const char str2[]) : First(str1)
    {
        strTwo = new char[strlen(str2) + 1];
    }
    ~Second()
    {
        cout << "~Second()" << endl;
        delete[] strTwo;
    }
};


int main()
{
    First* ptr = new Second("simple", "complex");
    delete ptr;

    return 0;
}

// 예제 3: 참조자의 참조 가능성
/*

A클래스 참조자 A&는 A객체를 직접 참조할 수 있다.
A클래스 참조자 A&는 A클래스를 상속하는 (다중)유도클래스도 참조할 수 있다.

*/

#include <iostream>

using namespace std;

class First
{
public:
    void FirstFunc()
    {
        cout << "FirstFunc()" << endl;
    }
    virtual void SimpleFunc()
    {
        cout << "First's SimpleFunc()" << endl;
    }
};

class Second : public First
{
public:
    void SecondFunc()
    {
        cout << "SecondFunc()" << endl;
    }
    virtual void SimpleFunc()
    {
        cout << "Second's SimpleFunc()" << endl;
    }
};

class Third : public Second
{
public:
    void ThirdFunc()
    {
        cout << "ThirdFunc()" << endl;
    }
    virtual void SimpleFunc()
    {
        cout << "Third's SimpleFunc()" << endl;
    }
};


int main()
{
    Third obj;  // 객체 obj는 Third형이다.

    obj.FirstFunc();
    obj.SecondFunc();
    obj.ThirdFunc();
    obj.SimpleFunc();  // SimpleFunc()는 가상함수. 객체 obj는 Third으로 생성되었기에 Third형의 멤버함수 참조

    cout << endl;

    Second& sref = obj;  // 참조자 sref는 Second형 참조자
    sref.FirstFunc();  
    sref.SecondFunc();
    //sref.ThirdFunc();  // 에러 발생
    sref.SimpleFunc();

    cout << endl;

    First& fref = obj;  // 참조자 fref는 First형 참조자
    fref.FirstFunc();
    //fref.SecondFunc(); // 에러 발생
    //fref.ThirdFunc();  // 에러 발생
    fref.SimpleFunc();

    return 0;
}