// ***************************** //
// 정보 은닉(Information Hiding) //
// ***************************** //

// 1: 정보 은닉의 필요성

#include <iostream>

using namespace std;

class Point
{
public:
    int x;  // x의 범위는 0부터 100까지
    int y;  // y의 범위는 0부터 100까지
};

class Rectangle
{
public:  // private이 아닌 public으로 선언
    Point upperLeft;
    Point lowerRight;
public:
    void ShowRecInfo()
    {
        cout << "좌 상단: " << '[' << upperLeft.x << ", " << upperLeft.y << ']' << endl;
        cout << "우 하단: " << '[' << lowerRight.x << ", " << lowerRight.y << ']' << endl;
    }
};

int main(void)
{
    Point pos1 = { -2, 4 };  // x 범위 초과
    Point pos2 = { 5, 9 };
    Rectangle rec = { pos2, pos1 };  // 좌 상단 좌표값이 우 상단 좌표값보다 큼
    rec.ShowRecInfo();



    return 0;
}


// 예제 2: 예제 1의 수정(정보 은닉)
// Point.h
#ifndef __POINT_H__
#define __POINT_H__

class Point
{
private:
    int x;
    int y;
public:
    bool InitMembers(int xpos, int ypos);
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

bool Point::InitMembers(int xpos, int ypos)
{
    if (xpos < 0 || xpos > 100 || ypos < 0 || ypos > 100)
    {
        cout << "범위를 벗어난 좌표값 전달" << endl;
        return false;
    }
    x = xpos;
    y = ypos;
    return true;
}

int Point::GetX() const  // const 함수
{
    return x;
}

int Point::GetY() const  // const 함수
{
    return y;
}

bool Point::SetX(int xpos)
{
    if (xpos < 0 || xpos > 100)
    {
        cout << "x 좌표값의 허용 범위 초과" << endl;
        return false;
    }
    x = xpos;
    return true;
}

bool Point::SetY(int ypos)
{
    if (ypos < 0 || ypos > 100)
    {
        cout << "y 좌표값의 허용 범위 초과" << endl;
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
    Point upperLeft;
    Point lowerRight;
public:
    bool InitMembers(const Point& ul, const Point& lr);
    void ShowRecInfo() const;
};

#endif

// Rectangle.cpp

#include <iostream>
#include "Rectangle.h"

using namespace std;

bool Rectangle::InitMembers(const Point& ul, const Point& lr)
{
    if (ul.GetX() > lr.GetX() || ul.GetY() > lr.GetY())
    {
        cout << "잘못된 위치 전달" << endl;
        return false;
    }
    upperLeft = ul;
    lowerRight = lr;
    return true;
}

void Rectangle::ShowRecInfo() const
{
    cout << "좌 상단:" << '[' << upperLeft.GetX() << ", " << upperLeft.GetY() << ']' << endl;
    cout << "우 하단:" << '[' << lowerRight.GetX() << ", " << lowerRight.GetY() << ']' << endl;
}

// RecMain.cpp

#include <iostream>
#include "Point.h"
#include "Rectangle.h"

using namespace std;


int main(void)
{
    Point pos1;
    if (!pos1.InitMembers(-2, 4))
        cout << "포인트 초기화 실패" << endl;
    if(!pos1.InitMembers(2,4))
        cout << "포인트 초기화 실패" << endl;

    Point pos2;
    if (!pos2.InitMembers(5, 9))
        cout << "포인트 초기화 실패" << endl;

    Rectangle rec;
    if (!rec.InitMembers(pos2, pos1))
        cout << "직사각형 초기화 실패" << endl;
    if (!rec.InitMembers(pos1, pos2))
        cout << "직사각형 초기화 실패" << endl;

    rec.ShowRecInfo();

    return 0;
}

// ********************** //
// 캡슐화 (Encapsulation) //
// ********************** //

// 캡슐화 : 관련있는 변수나 함수를 클래스 안에 하나로 묶는 것

// 예제 1: 콘택 600: 콧물, 재채기, 코막힘용
#include <iostream>
using namespace std;

class SnivelCap
{
public:
    void Take() const // 클래스 내부에서 클래스 멤버 함수의 선언과 정의(구현)를 한꺼번에 시행  
    {
        cout << "콧물이 치료됩니다." << endl;
    }
};

class SneezeCap
{
public:
    void Take() const;  // 클래스 내부에서 클래스 멤버 함수 선언
};

void SneezeCap::Take() const  // 클래스 외부에서 클래스 멤버 함수 정의(구현)
{
    cout << "재채기가 멎습니다." << endl;
}

class SnuffleCap
{
public:
    void Take() const
    {
        cout << "코가 뻥 뚤립니다." << endl;
    }
};

class ColdPatient
{
public:
    void TakeSnivelCap(const SnivelCap& cap) const
    {
        cap.Take();
    }
    void TakeSneezeCap(const SneezeCap& cap) const
    {
        cap.Take();
    }
    void TakeSnuffleCap(const SnuffleCap& cap) const;
};

void ColdPatient::TakeSnuffleCap(const SnuffleCap& cap) const
{
    cap.Take();
}

int main(void)
{
    SnivelCap scap;  //  SnivelCap의 객체(또는  인스턴스), 즉 메모리에 생성
    SneezeCap zcap;  //  SneezeCap의 객체(또는  인스턴스), 즉 메모리에 생성
    SnuffleCap ncap;  // SnuffleCap의 객체(또는  인스턴스), 즉 메모리에 생성

    ColdPatient sufferer;  // ColdPatient의 객체(또는  인스턴스), 즉 메모리에 생성

    sufferer.TakeSnivelCap(scap);
    sufferer.TakeSneezeCap(zcap);
    sufferer.TakeSnuffleCap(ncap);

    return 0;
}

// 예제 2: 캡슐화(encapsulation)
#include <iostream>
using namespace std;

class SnivelCap
{
public:
    void Take() const // 클래스 내부에서 클래스 멤버 함수의 선언과 정의(구현)를 한꺼번에 시행  
    {
        cout << "콧물이 치료됩니다." << endl;
    }
};

class SneezeCap
{
public:
    void Take() const;  // 클래스 내부에서 클래스 멤버 함수 선언
};

void SneezeCap::Take() const  // 클래스 외부에서 클래스 멤버 함수 정의(구현)
{
    cout << "재채기가 멎습니다." << endl;
}

class SnuffleCap
{
public:
    void Take() const
    {
        cout << "코가 뻥 뚤립니다." << endl;
    }
};

class Contact600
{
private:
    SnivelCap scap;
    SneezeCap zcap;
    SnuffleCap ncap;
public:
    void Take() const
    {
        scap.Take();
        zcap.Take();
        ncap.Take();
    }
};


class ColdPatient
{
public:
    void TakeContact600(const Contact600& cap) const
    {
        cap.Take();
    }
};


int main(void)
{
    Contact600 cap;
    ColdPatient sufferer;

    sufferer.TakeContact600(cap);

    return 0;
}
