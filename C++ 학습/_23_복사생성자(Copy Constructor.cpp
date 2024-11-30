// ***************************** //
// 복사 생성자(Copy Constructor) //
// ***************************** //

//C++에서는 다음과 같이 변수(클래스 포함) 초기화가 가능하다. 
//따라서 두 표현들은 동일하다.

/*
int num(20); // int num = 20;
int& ref(num); // int& ref = num;
SomeClass sc1; SomeClass sc2(sc1); // SomeClass sc2 = sc1; // 클래스의 복사
*/

// 예제 1: 복사생성자

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num1;
    int num2;
public:
    SoSimple(int n1, int n2)  // 생성자
        : num1(n1), num2(n2)  // 멤버 이니셜라이저
    {
        cout << "생성자 SoSimple(int n1, int n2) 호출" << endl;
    }
    SoSimple(const SoSimple& copy)  // 복사생성자: 원본 변형 방지(read only)
        : num1(copy.num1), num2(copy.num2)
    {
        cout << "생성자 SoSimple(SoSimple& copy) 호출" << endl;
    }
    void ShowSimpleData()
    {
        cout << num1 << endl;
        cout << num2 << endl;
    }
};

int main(void)
{
    SoSimple sim1(15, 30);
    cout << "복사생성자 생성 및 초기화 직전" << endl;
    SoSimple sim2 = sim1;  // SoSimple sim2(sim1); 으로 해석
    cout << "복사생성자 생성 및 초기화 직후" << endl;

    sim2.ShowSimpleData();

    return 0;
}

/*
주의 2
복사생성자를 명시적으로 정의하지 않으면 멤버 대 멤버릐 복사를 진행하는 디폴트 복사생성자가 묵시적으로 자동 호출된다.
많은 경우 복사생성자가 불필요하나 꼭 필요한 경우가 있다.
explit이라는 키워드로 복사생성자를 명시적으로 실행시킨다. 
아래 예제3 참고.
*/

// 예제 3: explicit 사용

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num1;
    int num2;
public:
    SoSimple(int n1, int n2)  // 생성자
        : num1(n1), num2(n2)  // 멤버 이니셜라이저
    {
        cout << "생성자 SoSimple(int n1, int n2) 호출" << endl;
    }
    explicit SoSimple(SoSimple& copy)  // 복사생성자
        : num1(copy.num1), num2(copy.num2)
    {
        cout << "생성자 SoSimple(SoSimple& copy) 호출" << endl;
    }
    void ShowSimpleData()
    {
        cout << num1 << endl;
        cout << num2 << endl;
    }
};

int main(void)
{
    SoSimple sim1(15, 30);
    cout << "복사생성자 생성 및 초기화 직전" << endl;
    // SoSimple sim2 = sim1;  // 컴파일 에러 발생
    SoSimple sim2(sim1);  // 대입 연산자 = 를 통한 묵시적 복사생성자 호출이 explit 으로 인해 불가능하게 됨
    cout << "복사생성자 생성 및 초기화 직후" << endl;

    sim2.ShowSimpleData();

    return 0;
}


// ********************************************* //
// 깊은 복사(deep copy)와 얕은복사(shallow copy) //
// ********************************************* //

// 예제 1: 얕은 복사 실행 시 에러 발생하게 되는 경우

#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private:
    char* name;
    int age;
public:
    Person(const char myname[], int myage)  // VC++에서 char* myname은 문자열 상수를 직접 입력으로 받지 못함
    {
        int len = strlen(myname) + 1;
        name = new char[len];
        strcpy_s(name, len, myname);  // CodeBlock 일 경우에는  strcpy(name, myname)을 사용
        age = myage;
    }
    void ShowPersonInfo() const
    {
        cout << "이름: " << name << endl;
        cout << "나이: " << age << endl;
    }
    ~Person()
    {
        delete[] name;
        cout << "소멸자 호출" << endl;
    }
};


int main()
{
    Person man1("Park Hyo Won", 14);
    Person man2 = man1; // 얕은 복사, 디폴트 생성자 호출. 즉, 멤버 대 멤버 복사만 진행
    man1.ShowPersonInfo();
    man2.ShowPersonInfo();


    return 0;
}

//위의 예제 실행시 소멸자가 한번만 호출된다. 두번째 객체의 소멸자 호출시 에러 발생

// 예제 2: 깊은 복사 (복사 생성자 사용)
// 멤버 뿐만 아니라 포인터로 참조하는 대상까지 복사함

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
    Person(const char myname[], int myage)
    {
        int len = strlen(myname) + 1;
        name = new char[len];
        strcpy_s(name, len, myname);  // CodeBlock 일 경우에는  strcpy(name, myname)을 사용
        age = myage;
    }
    Person(const Person& copy) : age(copy.age)
    {
        int len = strlen(copy.name) + 1;
        name = new char[len];
        strcpy_s(name, len, copy.name);  // CodeBlocks일 경우에는 strcpy(name, copy.name)을 사용한다.
    }
    void ShowPersonInfo() const
    {
        cout << "이름: " << name << endl;
        cout << "나이: " << age << endl;
    }
    ~Person()
    {
        delete[] name;
        cout << "소멸자 호출" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};


int main()
{
    Person man1("Park Hyo Won", 14);
    Person man2 = man1;  // 복사 생성자 호출 (깊은 복사 실행), Person man2(man1)과 같은 표현
    man1.ShowPersonInfo();
    man2.ShowPersonInfo();

    return 0;
}

// *********************** //
// 복사 생성자와 호출 시기 //
// *********************** //

// 예제 1: 함수의 매개변수로의 복사 생성자 호출

#include <iostream>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n)
    { }
    SoSimple(const SoSimple& copy) : num(copy.num)
    {
        cout << "복사 생성자 SoSimple(const SoSimple& copy) 호출" << endl;
    }
    void ShowData() 
    {
        cout << "num: " << num << endl;
    }
    ~SoSimple()
    {
        cout << "소멸자 호출" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

void SimpleFunctionObj(SoSimple ob)
{
    ob.ShowData();
}

int main()
{
    SoSimple obj(7);
    cout << "함수 호출 전" << endl;
    SimpleFunctionObj(obj);  // 함수의 매개변수를 통한 복사 생성자 호출. 즉, Sosimple ob = obj
    cout << "함수 호출 후" << endl;


    return 0;
}

// 예제 2: 복사 생성자 호출

#include <iostream>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n)
    { }
    SoSimple(const SoSimple& copy) : num(copy.num)
    {
        cout << "복사 생성자 SoSimple(const SoSimple& copy) 호출" << endl;
    }
    void ShowData() 
    {
        cout << "num: " << num << endl;
    }
    SoSimple& AddNum(int n)
    {
        num += n;
        return *this;  // this는 자기 자신을 가리키는 클래스 포인터이므로 *this는 자기 자신의 내용들이 된다. 
    }
    ~SoSimple()
    {
        cout << "소멸자 호출" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

SoSimple SimpleFunctionObj(SoSimple ob)
{
    cout << "return 이전" << endl;
    return ob;  // 반환값을 저장할 임시객체가 생성됨 (이 때 복사 생성자 호출)
}

int main()
{
    SoSimple obj(7);
    SimpleFunctionObj(obj).AddNum(30).ShowData(); 
    obj.ShowData();

    return 0;
}

// 예제 3: 임시로 생성되었다 소멸되는 객체

#include <iostream>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class Temporary
{
private:
    int num;
public:
    Temporary(int n) : num(n)
    {
        cout << "객체 생성 " << num << endl;
    }
    void ShowTempInfo() 
    {
        cout << "My num is " << num << endl;
    }
    ~Temporary()
    {
        cout << "소멸자 호출" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};


int main()
{
    Temporary(100); // 임시 객체는 다음 행으로 넘어가면 자동으로 소멸
    cout << "객체 생성 후" << endl << endl;

    Temporary(200).ShowTempInfo();
    cout << "객체 생성 후" << endl << endl;

    const Temporary& ref = Temporary(300);  // 참조자에 의해 참조되는 임시객체는 바로 소멸되지 않는다.
        // (주의) 객체를 명시적으로 만들지 않았으므로 참조자에 의한 접근 불가. 예: ref.ShowTempInfo() 불가능함

    cout << "the end of main()" << endl << endl;

    system("pause"); // VC++ 에서만 필요

    return 0;
}

// 예제 4: 반환할 때 만들어지는 임시객체의 소멸시기 확인

#include <iostream>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n)
    {
        cout << "새로운 객체 생성 " << num << endl;
    }
    SoSimple(const SoSimple& copy) : num(copy.num)
    {
        cout << "새로운 복사 객체 생성 " << num << endl;
    }
    ~SoSimple()
    {
        cout << "소멸자 호출" << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

SoSimple SimpleFunctionObj(SoSimple ob)
{
    cout << "객체의 주소:" << &ob << endl;
    return ob;
}

int main()
{
    SoSimple obj(7);
    SimpleFunctionObj(obj);

    cout << endl;

    SoSimple tempRef = SimpleFunctionObj(obj);
    cout << "Return Obj " << &tempRef << endl;

    system("pause"); // VC++ 에서만 필요

    return 0;
}