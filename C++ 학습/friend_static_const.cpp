// ********** //
// const 객체 //
// ********** //

// 예제 1: const 객체

//const SoSimple sim(20)와 같은 const 객체의 경우 이 객체의 멤버 데이터는 변경할 수 없고 const 멤버 함수만 호출 가능

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n) {}
    SoSimple& AddNum(int n)
    {
        num += n;
        return *this;
    }
    void ShowData() const
    {
        cout << "num: " << num << endl;
    }
};


int main(void)
{
    const SoSimple obj(7);  // const 객체
    // obj.AddNum(20);  // const 함수 아님. 에러 발생 
    obj.ShowData();

    return 0;
}

// 예제 2: const 함수 오버로딩

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num;
public:
    SoSimple(int n) : num(n) {}
    SoSimple& AddNum(int n)
    {
        num += n;
        return *this;
    }
    void SimpleFunc()
    {
        cout << "SimpleFunc() 호출. num: " << num << endl;
    }
    void SimpleFunc() const
    {
        cout << "SimpleFunc() const 호출. num: " << num << endl;
    }
};

void YourFunc(const SoSimple& obj)
{
    obj.SimpleFunc();
}

int main(void)
{
    SoSimple obj1(2);
    const SoSimple obj2(7);

    obj1.SimpleFunc();
    obj2.SimpleFunc();

    YourFunc(obj1);
    YourFunc(obj2);

    return 0;
}


// ********************************* //
// 클래스와 함수에 대한 friend 선언  //
// ********************************* //

// 예제 1: 클래스의 friend 선언
// 클래스의 friend 선언을 하면 직접 private 멤버 접근 가능. 
//friend 선언은 클래스 내 아무곳에서나 선언.

#include <iostream>
#include <cstring>

using namespace std;

class Girl;  // Girl이라는 클래스의 이름을 미리 알림

class Boy
{
private:
    int height;
    friend class Girl;  // Girl 클래스는 Boy 클래스의 private멤버 직접 접근 가능
public:
    Boy(int n) : height(n) {}
    void ShowYourFriendInfo(Girl& frn);
};

class Girl
{
private:
    char phNum[20];
public:
    Girl(const char num[])
    {
        strcpy_s(phNum, strlen(num) + 1, num);
    }
    void ShowYourFriendInfo(Boy& frn);
    friend class Boy;
};

void Boy::ShowYourFriendInfo(Girl& frn)
{
    cout << "Her phone number: " << frn.phNum << endl;
}

void Girl::ShowYourFriendInfo(Boy& frn)
{
    cout << "His height: " << frn.height << endl;
}

int main(void)
{
    Boy boy(170);
    Girl girl("010-1234-5678");

    boy.ShowYourFriendInfo(girl);
    girl.ShowYourFriendInfo(boy);

    return 0;
}

// 예제 2: 함수의 friend 선언

#include <iostream>
#include <Windows.h> // Sleep() 함수 

using namespace std;

class Point;  // Point이라는 클래스의 이름을 미리 알림

class PointOP  // Point연산을 정의하는 클래스
{
private:
    int opcnt;
public:
    PointOP() : opcnt(0) {}
    Point PointAdd(const Point&, const Point&);  // 클래스함수를 선언만 하므로 매개변수의 이름을 생략해도 됨
    Point PointSub(const Point&, const Point&);
    ~PointOP()
    {
        cout << "total number of operation calls : " << opcnt << endl;
        Sleep(2000); // 2000 마이크로 초 = 2초
    }
};

class Point
{
private:
    int x;
    int y;
public:
    Point(const int& xpos, const int& ypos) : x(xpos), y(ypos) {}
    friend Point PointOP::PointAdd(const Point&, const Point&);  // PointOP 안의 함수를 friend 선언하여 접근
    friend Point PointOP::PointSub(const Point&, const Point&);  // PointOP 안의 함수를 friend 선언하여 접근
    friend void ShowPointPos(const Point&);  // 전역함수 ShowPointPos()에 friend 선언
};

Point PointOP::PointAdd(const Point& pnt1, const Point& pnt2)
{
    opcnt++;
    return Point(pnt1.x + pnt2.x, pnt1.y + pnt2.y);
}

Point PointOP::PointSub(const Point& pnt1, const Point& pnt2)
{
    opcnt++;
    return Point(pnt2.x - pnt1.x, pnt2.y - pnt1.y);
}

void ShowPointPos(const Point& pos) // 전역함수
{
    cout << "x: " << pos.x << ", ";
    cout << "y: " << pos.y << endl;
}


int main(void)
{
    Point pos1(1, 2);
    Point pos2(2, 4);
    PointOP op;

    ShowPointPos(op.PointAdd(pos1, pos2));
    ShowPointPos(op.PointSub(pos1, pos2));

    return 0;
}

// **************** //
// C++에서의 static //
// **************** //

// 예제 1: 함수 내에 선언된 static의 의미 복습

#include <iostream>

using namespace std;

void Counter()
{
    static int cnt;  // static을 사용하면 마치 전역변수처럼 명시적 초기화 하지 않아도 묵시적으로 0으로 초기화함
    cnt++;
    cout << "현재 cnt: " << cnt << endl;

}


int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        Counter();
    }
    return 0;
}

// 예제 2: 전역변수가 필요한 상황

#include <iostream>

using namespace std;

int simObjCnt = 0;
int cmxObjCnt = 0;

class SoSimple
{
public:
    SoSimple()
    {
        simObjCnt++;
        cout << simObjCnt << "번째 SoSimple 객체" << endl;
    }
};

class SoComplex
{
public:
    SoComplex()
    {
        cmxObjCnt++;
        cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
    }
    SoComplex(SoComplex& copy)
    {
        cmxObjCnt++;
        cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
    }
};


int main(void)
{
    SoSimple sim1;
    SoSimple sim2;
  SoSimple();  // 임시객체. 주의 SoSimple sim3( )은 틀린 문법임.

    SoComplex com1;
    SoComplex com2;
    SoComplex com3 = com2;  // 복사생성자

    return 0;
}

// 예제 3: static 멤버 변수 (static 클래스 변수)

// static 멤버 변수는 클래스당 하나씩만 생성된다. 
//따라서 같은 종류의 클래스가 계속 만들어져도 최초에 만들어진 static 멤버 변수를 공유한다.

#include <iostream>

using namespace std;

class SoSimple
{
private:
    static int simObjCnt;  
public:
    SoSimple()
    {
        simObjCnt++;
        cout << simObjCnt << "번째 SoSimple 객체" << endl;
    }
};

int SoSimple::simObjCnt = 0;  // static 멤버 변수의 초기화는 클래스 외부에서 함

class SoComplex
{
private:
    static int cmxObjCnt;
public:
    SoComplex()
    {
        cmxObjCnt++;
        cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
    }
    SoComplex(SoComplex& copy)
    {
        cmxObjCnt++;
        cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
    }
};

int SoComplex::cmxObjCnt = 0;  // static 멤버 변수의 초기화는 클래스 외부에서 함

int main(void)
{
    SoSimple sim1;
    SoSimple sim2;
    SoSimple();  // 임시객체 

    SoComplex com1;
    SoComplex com2;
    SoComplex com3 = com2;  // 복사생성자

    return 0;
}

// 예제 4: static 멤버변수의 또다른 접근방법

#include <iostream>

using namespace std;

class SoSimple
{
public:
    static int simObjCnt;  
public:
    SoSimple()
    {
        simObjCnt++;
    }
};

int SoSimple::simObjCnt = 0;  // static 멤버 변수의 초기화는 클래스 외부에서 함


int main(void)
{
    cout << SoSimple::simObjCnt << "번째 SoSimple 객체" << endl;
    SoSimple sim1;
    SoSimple sim2;

    cout << SoSimple::simObjCnt << "번째 SoSimple 객체" << endl;  // simObjCnt은 공유되어 진 메모리 영역
    cout << sim1.simObjCnt << "번째 SoSimple 객체" << endl;  // simObjCnt이 public으로 설정되어 접근가능
    cout << sim2.simObjCnt << "번째 SoSimple 객체" << endl;  // simObjCnt이 public으로 설정되어 접근가능

    return 0;
}

// 예제 5: static 멤버함수
// static 멤버함수 내에서는 static 멤서변수와 static 멤버함수의 호출만 가능하다.

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num1;
    static int num2; // static 멤버 변수
public:
    SoSimple(int n) : num1(n) {}
    void Adder(int n) { num1 += n; }
    static void Adder2(int n); // static 멤버 함수. static 멤버 변수처럼 객체의 외부에서 공유됨
    int GetMember() { return num1; }
    static int GetStaticMember();
};

int SoSimple::num2 = 0;  // static 멤버 변수의 초기화는 클래스 외부에서 함
void SoSimple::Adder2(int n) { num2 += n; } // static 멤버 함수의 초기화는 클래스 외부에서 함
int SoSimple::GetStaticMember() { return num2; }

int main(void)
{
    SoSimple sim1(3);
    cout << sim1.GetMember() << endl;
    cout << sim1.GetStaticMember() << endl << endl;

    sim1.Adder(1);
    sim1.Adder2(2);
    cout << sim1.GetMember() << endl;
    cout << sim1.GetStaticMember() << endl << endl;

    SoSimple sim2(-3);
    cout << sim2.GetMember() << endl;
    cout << sim2.GetStaticMember() << endl << endl;

    sim2.Adder(1);
    sim2.Adder2(2);
    cout << sim2.GetMember() << endl;
    cout << sim2.GetStaticMember() << endl << endl;


    return 0;
}

// 예제 6: const static 멤버 (전역 상수 선언)

#include <iostream>

using namespace std;

class CountryArea
{
public:
    const static int RUSSIA = 1707540;  // const static 멤버는 선언과 동시에 초기화 가능
    const static int CANADA = 998467;
    const static int CHINA = 957290;
    const static int KOREA = 9922;

};

int main(void)
{
    cout << "러시아 면적: " << CountryArea::RUSSIA << " Km^2" << endl;
    cout << "캐나다 면적: " << CountryArea::CANADA << " Km^2" << endl;
    cout << "중국 면적: " << CountryArea::CHINA << " Km^2" << endl;
    cout << "한국 면적: " << CountryArea::KOREA << " Km^2" << endl;

    return 0;
}

// 예제 7: mutable

//mutable 키워드는 const 함수(즉, read-only 함수) 내에서의 값의 변경을 예외적으로 허용하게 한다. 
// *가능하면 사용을 자제할 것.*

#include <iostream>

using namespace std;

class SoSimple
{
private:
    int num1;
    mutable int num2;  // const 함수에 예외를 두어 그 함수 안에서 값의 변경 가능하게 함
public:
    SoSimple(int n1, int n2) : num1(n1), num2(n2) {}
    void ShowSimlpeData() const
    {
        cout << num1 << ", " << num2 << endl;
    }
    void CopyToNum2() const
    {
        num2 = num1;
    }
};

int main(void)
{
    SoSimple sm(1, 2);
    sm.ShowSimlpeData();
    sm.CopyToNum2();
    sm.ShowSimlpeData();

    system("pause"); // VC++ 에만 적용
    return 0;
}

