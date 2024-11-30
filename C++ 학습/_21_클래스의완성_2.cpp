// ****** //
// 생성자 //
// ****** //

/*
클래스의 객체 생성 시에 private 멤버를 자동으로 초기화한다.
생성자의 이름은 클래스의 이름과 같아야 한다.
반환( return)형이 선언되어 있지 않고 실제로도 반환하지 않는다.
객체 생성시에 딱 한번 호출된다.
생성자도 일종의 함수이므로 오버로딩이 가능하다. (즉, 객체 생성을 다양하게 할 수 있다.)
생성자도 디폴트값을 설정할 수 있다.
*/

// 예제 1: 다양한 생성자

#include <iostream>
using namespace std;

class SimpleClass
{
private:
    int num1;
    int num2;
public:
    SimpleClass()  // 생성자 1
    {
        num1 = 0;
        num2 = 0;
    }
    SimpleClass(int n)  // 생성자 2
    {
        num1 = n;
        num2 = 0;
    }
    SimpleClass(int n1, int n2)  // 생성자 3
    {
        num1 = n1;
        num2 = n2;
    }

    void Show() const
    {
        cout << num1 << ' ' << num2 << endl;
    }

};


int main(void)
{
    SimpleClass sc1;  // 생성자 1 호출. SimpleClass sc1()은 에러 발생하므로 주의
    sc1.Show();

    SimpleClass sc2(100);  // 생성자 2 호출
    sc2.Show();

    SimpleClass sc3(100,200);  // 생성자 3 호출
    sc3.Show();

    return 0;
}

// 예제 2: 생성자 매개변수 디폴트(default) 값
#include <iostream>
using namespace std;

class SimpleClass
{
private:
    int num1;
    int num2;
public:
    SimpleClass(int n1 = 0, int n2 = 0)  // 생성자 4
    {
        num1 = n1;
        num2 = n2;
    }

    void Show() const
    {
        cout << num1 << ' ' << num2 << endl;
    }

};


int main(void)
{
    SimpleClass sc1;  // 생성자 4 호출. 디폴트 값 사용
    sc1.Show();

    SimpleClass sc2(100);  // 생성자 4 호출, 첫 멤버 값 세팅
    sc2.Show();

    SimpleClass sc3(100,200);  // 생성자 4 호출, 두 멤버 모두의 값 세팅
    sc3.Show();


    return 0;
}

// 예제 3: 생성자가 모호하면 컴파일 에러(아래 코드는 에러 코드)
#include <iostream>
using namespace std;

class SimpleClass
{
private:
    int num1;
    int num2;
public:
    SimpleClass()  // 생성자 1
    {
        num1 = 0;
        num2 = 0;
    }
    SimpleClass(int n)  // 생성자 2
    {
        num1 = n;
        num2 = 0;
    }
    SimpleClass(int n1, int n2)  // 생성자 3
    {
        num1 = n1;
        num2 = n2;
    }
    SimpleClass(int n1 = 0, int n2 = 0)  // 생성자 4
    {
        num1 = n1;
        num2 = n2;
    }

    void Show() const
    {
        cout << num1 << ' ' << num2 << endl;
    }

};


int main(void)
{
    SimpleClass sc1;  // 생성자 1 호출. SimpleClass sc1()은 에러 발생하므로 주의
    sc1.Show();

    SimpleClass sc2(100);  // 생성자 2 호출? 생성자 4 호출?
    sc2.Show();

    SimpleClass sc3(100, 200);  // 생성자 3 호출? 생성자 4 호출?
    sc3.Show();


    return 0;
}


// 예제 4: 클래스 동적 메모리 할당

#include <iostream>
using namespace std;

class SimpleClass
{
private:
    int num1;
    int num2;
public:
    SimpleClass(int n1 = 0, int n2 = 0)  // 생성자 4
    {
        num1 = n1;
        num2 = n2;
    }

    void Show() const
    {
        cout << num1 << ' ' << num2 << endl;
    }

};


int main(void)
{
    SimpleClass* psc1 = new SimpleClass;  
    psc1->Show(); // 포인터를 통한 간접 접근

    SimpleClass* psc2 = new SimpleClass(100);
    psc2->Show();

    SimpleClass* psc3 = new SimpleClass(100,200);
    psc3->Show();

    delete psc1, psc2, psc3;

    return 0;
}

// 예제 5: SimpleClass sc();는 SimpleClass를 반환하는 함수 선언이다.
// C++에서는 함수 선언을 main 함수 안에서도 선언이 가능하다.

#include <iostream>
using namespace std;

class SimpleClass
{
private:
    int num1;
    int num2;
public:
    SimpleClass(int n1 = 0, int n2 = 0)  // 생성자 4
    {
        num1 = n1;
        num2 = n2;
    }

    void Show() const
    {
        cout << num1 << ' ' << num2 << endl;
    }

};


int main(void)
{
    SimpleClass sc1();  // void 입력이고 SimpleClass를 반환하는 함수 sc1()을 선언

    SimpleClass mysc = sc1();  // 함수 sc1()의 반환값으로 초기화, 즉 mysc 내부의 멤버 변수값을 sc1()의 반환값들로 초기화
    mysc.Show();


    return 0;
}

// SimpleClass를 반환하는 함수 sc1()을 정의(구현)
SimpleClass sc1()
{
    SimpleClass sc(20, 39);
    return sc;
}

// 예제 6: '03-03 예제1'에 대한 생성자 활용
#include <iostream>

using namespace std;

class FruitSeller
{
private:
    int applePrice;
    int numOfApples;
    int myMoney;
public:
    FruitSeller(int price, int num, int money)
    {
        applePrice = price;
        numOfApples = num;
        myMoney = money;
    }
    int  SaleApples(int money)
    {
        int num = money / applePrice;
        numOfApples -= num;
        myMoney += money;
        return num;
    }
    void ShowSalesResult() const
    {
        cout << "남은 사과: " << numOfApples << endl;
        cout << "판매 수익: " << myMoney << endl << endl;
    }
};

class FruitBuyer
{
private:
    int myMoney;
    int numOfApples;
public:
    FruitBuyer(int money)
    {
        myMoney = money;
        numOfApples = 0;
    }
    void BuyApples(FruitSeller& seller, int money)
    {
        numOfApples += seller.SaleApples(money);  // 메시지 전달(Message Passing)
        myMoney -= money;
    }
    void ShowBuyResult() const
    {
        cout << "현재 잔액: " << myMoney << endl;
        cout << "사과 개수: " << numOfApples << endl << endl;
    }
};


int main(void)
{
    FruitSeller seller(1000, 20, 0);
    FruitBuyer buyer(5000);
    buyer.BuyApples(seller, 2000);

    cout << "과일 판매자의 현황: " << endl;
    seller.ShowSalesResult();
    cout << "과일 구매자의 현황: " << endl;
    buyer.ShowBuyResult();


    return 0;
}

// 예제 7: 클래스 멤버가 클래스 일때 생성자 호출 방법
// Point.h

#ifndef __POINT_H__
#define __POINT_H__

class Point
{
private:
    int x;
    int y;
public:
    Point(const int& xpos, const int& ypos);
    int GetX() const;
    int GetY() const;
    bool SetX(int xpos);
    bool SetY(int ypos);
};

#endif

// Point.cpp
#include <iostream>
#include "Point.h"

using namespace std;

// 클래스 Point의 생성자
Point::Point(const int& xpos, const int& ypos)
{
    x = xpos;
    y = ypos;
}

int Point::GetX() const
{
    return x;
}

int Point::GetY() const
{
    return y;
}

bool Point::SetX(int xpos)
{
    if (xpos < 0 || xpos > 100)
    {
        cout << "벗어난 범위의 값 전달" << endl;
        return false;
    }
    x = xpos;
    return true;
}

bool Point::SetY(int ypos)
{
    if (ypos < 0 || ypos > 100)
    {
        cout << "벗어난 범위의 값 전달" << endl;
        return false;
    }
    y = ypos;
    return true;
}

// Rectangle.h
#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Point.h"

class Rectangle
{
private:
    Point upLeft;
    Point lowRight;
public:
    Rectangle(const int& x1, const int& y1, const int& x2, const int& y2);
    void ShowRecInfo() const;
};

#endif

// Rectangle.cpp

#include <iostream>
#include "Rectangle.h"

using namespace std;

// 클래스 Rectangle의 생성자
Rectangle::Rectangle(const int& x1, const int& y1, const int& x2, const int& y2)
    : upLeft(x1, y1), lowRight(x2, y2) // 멤버 이시셜라이저(member initializer). 즉, 선언과 동시에 초기화
{
    // empty
}

void Rectangle::ShowRecInfo() const
{
    cout << "좌 상단: " << "[" << upLeft.GetX() << "," << upLeft.GetY() << "]" << endl;
    cout << "우 하단: " << "[" << lowRight.GetX() << "," << lowRight.GetY() << "]" << endl;
}

// RectangleMain.cpp

#include <iostream>
#include "Point.h"
#include "Rectangle.h"

using namespace std;

int main(void)
{
    Rectangle rec(1, 1, 5, 5);
    rec.ShowRecInfo();

    return 0;
}

// 예제 8: '예제 6'의 멤버 이니셜라이저를 이용한 초기화

#include <iostream>

using namespace std;

class FruitSeller
{
private:
    const int APPLE_PRICE;
    int numOfApples;
    int myMoney;
public:
    FruitSeller(int price, int num, int money)
        : APPLE_PRICE(price), numOfApples(num), myMoney(money) // 멤버 이니셜라이저
    {
    }
    int  SaleApples(int money)
    {
        int num = money / APPLE_PRICE;
        numOfApples -= num;
        myMoney += money;
        return num;
    }
    void ShowSalesResult() const
    {
        cout << "남은 사과: " << numOfApples << endl;
        cout << "판매 수익: " << myMoney << endl << endl;
    }
};

class FruitBuyer
{
private:
    int myMoney;
    int numOfApples;
public:
    FruitBuyer(int money)
        : myMoney(money), numOfApples(0) // 멤버 이니셜라이저
    {
    }
    void BuyApples(FruitSeller& seller, int money)
    {
        numOfApples += seller.SaleApples(money);  // 메시지 전달(Message Passing)
        myMoney -= money;
    }
    void ShowBuyResult() const
    {
        cout << "현재 잔액: " << myMoney << endl;
        cout << "사과 개수: " << numOfApples << endl << endl;
    }
};


int main(void)
{
    FruitSeller seller(1000, 20, 0);
    FruitBuyer buyer(5000);
    buyer.BuyApples(seller, 2000);

    cout << "과일 판매자의 현황: " << endl;
    seller.ShowSalesResult();
    cout << "과일 구매자의 현황: " << endl;
    buyer.ShowBuyResult();


    return 0;
}

// 예제 9: 멤버 변수로 참조자 선언

#include <iostream>

using namespace std;

class AAA
{
public:
    AAA()
    {
        cout << "empty object" << endl;
    }
    void ShowYourName()
    {
        cout << "I'm class AAA!" << endl;
    }
};

class BBB
{
private:
    AAA& ref;
    const int& num;
public:
    BBB(AAA& r, const int& n)
        : ref(r), num(n)
    {
    }
    void ShowYourName()
    {
        ref.ShowYourName();
        cout << "and" << endl;
        cout << "I refer num : " << num << endl;
    }
};


int main(void)
{
    AAA obj1;
    BBB obj2(obj1, 20);
    obj2.ShowYourName();

    return 0;
}

// 예제 10: 디폴트(default) 생성자, private 생성자

#include <iostream>

using namespace std;

class AAA
{
private:
    int num;
    AAA(int n) : num(n) {}  // private 생성자. 즉, 클래스 내부에서만 사용
public:
    AAA() : num(0) {}  // 디폴트 생성자 
    AAA& CreateInitObj(int n) const
    {
        AAA* ptr = new AAA(n);  // 동적 메모리 할당. private 생성자 호출
        return *ptr;
    }
    void ShowYourName() const
    {
        cout << num << endl;
    }
};

int main(void)
{
    AAA base;
    base.ShowYourName();

    AAA& obj1 = base.CreateInitObj(3);
    obj1.ShowYourName();

    AAA& obj2 = base.CreateInitObj(12);
    obj2.ShowYourName();

    delete &obj1;  // obj1의 주소(포인터와 같은 의미)
    delete &obj2;  // obj2의 주소(포인터와 같은 의미)

    return 0;
}

// ******* //
// 소멸자  //
// ******* //
#include <iostream>
#include <cstring>
#include <Windows.h>  // VC++에서 Sleep()을 가지고 있는 헤더

using namespace std;

class Person
{
private:
    char* name;
    int age;
public:
    Person(const char myname[], int myage)  // 생성자
    {
        int len = strlen(myname) + 1; //stlen() 문자열 길이 + 널 문자 '\o'
        name = new char[len];
        strcpy_s(name, len, myname);  // VC++ 에서만 사용. name이 포인터이므로 크기 len이 꼭 필요함.
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
        Sleep(1000); // 1000 마이크로 초 = 1초
    }
};

int main(void)
{
    Person man1("Park Hyo Won", 14);
    Person man2("La Tae In", 14);
    man1.ShowPersonInfo();
    man2.ShowPersonInfo();


    return 0;
}


