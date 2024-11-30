// ************ //
// 클래스 배열  //
// ************ //

// 예제 1: 클래스 배열

#include <iostream>
#include <cstring>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class Person
{
private:
    char* name;
    int age;
public:
    Person(char* myname, int myage)  // 생성자
    {
        int len = strlen(myname) + 1; //stlen() 문자열 길이 + 널 문자 '\o'
        name = new char[len];
        strcpy_s(name, len, myname);  // VC++ 에서만 사용. name이 포인터이므로 크기 len이 꼭 필요함.
        age = myage;
        cout << "Person(char* myname, int myage) is called." << endl;
    }
    Person()  // 생성자
    {
        name = NULL;
        age = 0;
        cout << "Person() is called." << endl;
    }
    void SetPersonInfo(char* myname, int myage)
    {
        name = myname;
        age = myage;
    }
    void ShowPersonInfo() const
    {
        cout << "이름: " << name << endl;
        cout << "나이: " << age << endl;
    }
    ~Person() // 소멸자
    {
        delete[] name;
        cout << "destructor is called!" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

int main(void)
{
    Person parr[3];  // 클래스(혹은 객체) 배열은 선언과 동시에 초기화 불가능함
    char namestr[100];
    char* strptr;
    int age;
    int len;

    // 클래스 배열을 하나씩 초기화
    for (int i = 0; i < 3; i++)
    {
        cout << "이름: ";
        cin >> namestr;
        cout << "나이: ";
        cin >> age;
        len = strlen(namestr) + 1;  // 널문자 '\0' 추가를 위해
        strptr = new char[len];
        strcpy_s(strptr, len, namestr);  // VC++에서만. 표준 C++에서는 strcpy(strptr, namestr); 사용
        parr[i].SetPersonInfo(strptr, age);
    }

    cout << endl;

    // 직접접근
    parr[0].ShowPersonInfo();
    parr[1].ShowPersonInfo();
    parr[2].ShowPersonInfo();

    cout << endl;

    // 간접접근
    (parr + 0)->ShowPersonInfo();
    (parr + 1)->ShowPersonInfo();
    (parr + 2)->ShowPersonInfo();


    return 0;
}

// 예제 2: 클래스 포인터 배열

#include <iostream>
#include <cstring>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class Person
{
private:
    char* name;
    int age;
public:
    Person(char* myname, int myage)  // 생성자
    {
        int len = strlen(myname) + 1; //stlen() 문자열 길이 + 널 문자 '\o'
        name = new char[len];
        strcpy_s(name, len, myname);  // VC++ 에서만 사용. name이 포인터이므로 크기 len이 꼭 필요함.
        age = myage;
        cout << "Person(char* myname, int myage) is called." << endl;
    }
    Person()  // 생성자
    {
        name = NULL;
        age = 0;
        cout << "Person() is called." << endl;
    }
    void SetPersonInfo(char* myname, int myage)
    {
        name = myname;
        age = myage;
    }
    void ShowPersonInfo() const
    {
        cout << "이름: " << name << endl;
        cout << "나이: " << age << endl;
    }
    ~Person() // 소멸자
    {
        cout << "destructor is called!" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

int main(void)
{
    Person* parr[3];  // 클래스(혹은 객체) 포인터 배열 선언
    char namestr[100];
    int age;

    // 클래스 포인터에 객체를 하나씩 할당
    for (int i = 0; i < 3; i++)
    {
        cout << "이름: ";
        cin >> namestr;
        cout << "나이: ";
        cin >> age;
        parr[i] = new Person(namestr, age);
    }

    cout << endl;

    parr[0]->ShowPersonInfo();
    parr[1]->ShowPersonInfo();
    parr[2]->ShowPersonInfo();

    for(int i = 0; i < 3; i++)
        delete parr[i];

    return 0;
}

// ***************************************** //
// this 포인터(객체 자신을 가리키는 포인터)  //
// ***************************************** //

#include <iostream>
#include <cstring>

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n)
    {
        cout << "num = " << num << ", ";
        cout << "object address = " << this << endl;
    }
    void ShowSimpleData()
    {
        cout << num << endl;
    }
    SoSimple* GetThisPointer()
    {
        return this;
    }
};

int main(void)
{
    SoSimple sim1(100);
    SoSimple* ptr1 = sim1.GetThisPointer();  // 객체 sim1의 시작 주소 반환
    cout << ptr1 << ", ";
    ptr1->ShowSimpleData();

    SoSimple sim2(200);
    SoSimple* ptr2 = sim2.GetThisPointer();  // 객체 sim2의 시작 주소 반환
    cout << ptr2 << ", ";
    ptr2->ShowSimpleData();

    return 0;
}

// 예제 4: this 포인터 활용
#include <iostream>
#include <cstring>

using namespace std;

class TwoNumber
{
private:
    int num1;
    int num2;
public:
    TwoNumber(int num1, int num2)
    {
        this->num1 = num1;
        this->num2 = num2;
    }
    void ShowTwoNumber()
    {
        cout << this->num1 << endl;
        cout << this->num2 << endl;
    }
};

int main(void)
{
    TwoNumber two(2, 4);
    two.ShowTwoNumber();

    return 0;
}

// 예제 5: 클래스 자기참조(Self-Reference)
#include <iostream>

using namespace std;

class SelfRef
{
private:
    int num;
public:
    SelfRef(int n) : num(n)
    {
        cout << "객체 생성" << endl;
    }
    SelfRef& Adder(int n)
    {
        num += n;
        return *this;
    }
    SelfRef& ShowNumber()
    {
        cout << num << endl;
        return *this;
    }
};

int main(void)
{
    SelfRef obj(3);
    SelfRef& ref = obj.Adder(2);

    obj.ShowNumber();
    ref.ShowNumber();

    ref.Adder(1).ShowNumber().Adder(2).ShowNumber();


    return 0;
}





