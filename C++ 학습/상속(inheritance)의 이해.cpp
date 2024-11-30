// ******************************* //
// 상속(inheritance)의 문법적 이해 //
// ******************************* //

// 예제 1: 클래스의 상속
/*
class Person : 상위 클래스, 기초(base) 클래스, 슈퍼(super) 클래스, 부모(parents) 클래스
class UnivStudent : 하위 클래스, 유도(derived) 클래스, 서브(sub) 클래스, 자식(child) 클래
*/

#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private:
    char name[20];  // 이름
    int age;  // 나이
public:
    Person(const char myname[], int myage) : age(myage)
    {
        strcpy_s(name, 20, myname);
    }
    void WhatIsYourName() const
    {
        cout << "My name is " << name << endl;
    }
    void HowOldAreYou() const
    {
        cout << "I'm " << age << " years old." << endl;
    }
};

class UnivStudent : public Person  // Person을 상속함 = Person의 모든 멤버를 가지고 옴
{
private:
    char major[50];  // 전공과목 이름
public:
    UnivStudent(const char myname[], int myage, const char mymajor[]) : Person(myname, myage) // 부모클래스 Person의 자체 생성자 호출
    {
        strcpy_s(major, 50, mymajor);
    }
    void WhoAreYou() const
    {
        WhatIsYourName();
        HowOldAreYou();
        cout << "My major is " << major << endl << endl;
    }
};

int main(void)
{
    UnivStudent ustd1("Park Hyo Won", 14, "Computer Science");
    ustd1.WhoAreYou();

    UnivStudent ustd2("La Tae In", 14, "Medical Science");
    ustd2.WhoAreYou();

    return 0;
}


//예제 2: 유도 클래스의 객체 생성과정

#include <iostream>

using namespace std;

class SoBase
{
private:
    int baseNum;  
public:
    SoBase() : baseNum(20)
    {
        cout << "SoBase()" << endl;
    }
    SoBase(int n) : baseNum(n)
    {
        cout << "SoBase(int n)" << endl;
    }
    void ShowBaseData() const
    {
        cout << baseNum << endl;
    }
};

class SoDerived : public SoBase  
{
private:
    int derivNum;
public:
    SoDerived() : derivNum(30)
    {
        cout << "SoDerived()" << endl;
    }
    SoDerived(int n) : derivNum(n)
    {
        cout << "SoDerived(int n)" << endl;
    }
    SoDerived(int n1, int n2) : SoBase(n1), derivNum(n2)
    {
        cout << "SoDerived(int n1, int n2)" << endl;
    }
    void ShowDerivData() const
    {
        ShowBaseData();
        cout << derivNum << endl;
    }
};

int main(void)
{
    cout << "case1..............." << endl;
    SoDerived dr1;
    dr1.ShowDerivData();
    cout << "--------------------" << endl;

    cout << "case2..............." << endl;
    SoDerived dr2(12);
    dr2.ShowDerivData();
    cout << "--------------------" << endl;

    cout << "case3..............." << endl;
    SoDerived dr3(23, 24);
    dr3.ShowDerivData();
    cout << "--------------------" << endl;

    return 0;
}

// 예제 3: 유도 클래스의 객체 소멸과정
#include <iostream>
#include <windows.h>

using namespace std;

class SoBase
{
private:
    int baseNum;  
public:
    SoBase(int n) : baseNum(n)
    {
        cout << "SoBase() : " << baseNum << endl;
    }
    ~SoBase()
    {
        cout << "~SoBase() : " << baseNum << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

class SoDerived : public SoBase  
{
private:
    int derivNum;
public:
    SoDerived(int n) : SoBase(n), derivNum(n)
    {
        cout << "SoDerived(int n) : " << derivNum << endl;
    }
    ~SoDerived()
    {
        cout << "~SoDerived() : " << derivNum << endl;
        Sleep(2000); // 1000 마이크로 초 = 1초
    }
};

int main(void)
{
    SoDerived drv1(15);  // 스택에 저장
    SoDerived drv2(27);  // 스택에 저장

    return 0;
}

// 예제 4: 유도 클래스의 생성과 소멸

#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private:
    char* name;  
public:
    Person(const char myname[])
    {
        int len = strlen(myname) + 1;
        name = new char[len];
        strcpy_s(name, len, myname);
    }
    ~Person()
    {
        delete[] name;
    }
    void WhatIsYourName() const
    {
        cout << "My name is " << name << endl;
    }
};

class UnivStudent : public Person
{
private:
    char* major;
public:
    UnivStudent(const char myname[], const char mymajor[]) : Person(myname)
    {
        int len = strlen(mymajor) + 1;
        major = new char[len];
        strcpy_s(major, len, mymajor);
    }
    ~UnivStudent()
    {
        delete[] major;
    }
    void WhoAreYou() const
    {
        WhatIsYourName();
        cout << "My major is " << major << endl << endl;
    }
};

int main(void)
{
    UnivStudent st1("Park Hyo Won", "Computer Science");
    st1.WhoAreYou();

    UnivStudent st2("La Tae In", "Medical Science");
    st2.WhoAreYou();

    return 0;
}

// ************************************ //
// protected 선언과 세 가지 형태의 상속 //
// ************************************ //

// 예제 1: 상속 시 기초 클래스의 접근 제어 범위의 변경

/*
접근 제어 범위: private < protected < public

상속의 형태보다 제어범위가 넓은 것들을 상속 형태로 변환

유도 클래스가 기초 클래스를 private 상속 할 때:
 - private -> 접근불가 (주의: private으로 가져는 것이 아님)
 - protected -> private
 - public -> private
유도 클래스가 기초 클래스를 protected 상속 할 때:
 - private -> 접근불가 (주의: private으로 가져는 것이 아님)
 - protected -> protected
 - public -> protected
유도 클래스가 기초 클래스를 public 상속 할 때:
 - private -> 접근불가
 - protected -> protected
 - public -> public
주로 public 상속이 사용됨.

*/


#include <iostream>

using namespace std;

class Base
{
private:
    int num1;  // private member (클래스 외부에서 접근 불가), 
protected:
    int num2;  // protected member (클래스 외부에서 접근 불가)
public:
    int num3;  // public member (클래스 외부에서 접근 가능)
    Base() : num1(1), num2(2), num3(3) {}
};

class Derived : private Base  // 상속 3가지: private, protected, public
{
    // empty
};

int main(void)
{
    Derived drv;
    cout << drv.num1 << endl; // 에러 발생
    cout << drv.num2 << endl; // 에러 발생
    cout << drv.num3 << endl; // public 상속일때만 에러 없음

    return 0;
}

// **************** //
// 상속을 위한 조건 //
// **************** //

// 예제 1: '유도클래스' is a '상속클래스' (is-a 관계)

/*
대학생(UnivStudent)은 (일종의) 사람(Person)이다.
노트북 컴퓨터(NotebookComp)는 (일종의) 컴퓨터(Computer)이다.
태블렛(TableNotebook)은 (일종의) 노트북 컴퓨터(NotebookComp)이다.
*/

#include <iostream>
#include <cstring>

using namespace std;

class Computer
{
private:
    char owner[50];  
public:
    Computer(const char name[])
    {
        strcpy_s(owner, strlen(name) + 1, name);
    }
    void Calculate()
    {
        cout << "요청 내용을 계산합니다." << endl;
    }
};

class NotebookComp : public Computer 
{
private:
    int Battery;
public:
    NotebookComp(const char name[], int initChag) : Computer(name), Battery(initChag) {}
    void Charging() { Battery += 5; }
    void UseBattery() { Battery -= 1; }
    int GetBatteryInfo() { return Battery; }
    void MovingCal()
    {
        if (GetBatteryInfo() < 1)
        {
            cout << "충전이 필요합니다." << endl;
            return;
        }
        cout << "이동하면서 ";
        Calculate();
        UseBattery();
    }
};

class TableNotebook : public NotebookComp
{
private:
    char regstPenModel[50];
public:
    TableNotebook(const char name[], int initChag, const char pen[]) : NotebookComp(name, initChag)
    {
        strcpy_s(regstPenModel, strlen(pen) + 1, pen);
    }
    void Write(const char penInfo[])
    {
        if (GetBatteryInfo() < 1)
        {
            cout << "충전이 필요합니다." << endl;
            return;
        }
        if (strcmp(regstPenModel, penInfo) != 0)
        {
            cout << "등록된 펜이 아닙니다.";
            return;
        }
        cout << "필기 내용을 처리합니다." << endl;
        UseBattery();
    }
};
int main(void)
{
    NotebookComp nc("박효원", 5);
    TableNotebook tn("라태인", 5, "ISE-241-242");
    nc.MovingCal();
    tn.Write("ISE-241-242");


    return 0;
}

// 예제 2: '유도 클래스' has a '기초 클래스' (has-a 관계)
// 경찰(Police)은 총(Gun)을 가지고 있다.

#include <iostream>
#include <cstring>

using namespace std;

class Gun
{
private:
    int bullet; // 장전된 총알의 수 
public:
    Gun(int bnum) : bullet(bnum) {}
    void Shot()
    {
        cout << "빵" << endl;
        bullet--;
    }
};

class Police : public Gun 
{
private:
    int handcuffs;
public:
    Police(int bnum, int bcuff) : Gun(bnum), handcuffs(bcuff) {}
    void PutHandcuff()
    {
        cout << "찰칵" << endl;
        handcuffs--;
    }
};

int main(void)
{
    Police pman(5, 3);
    pman.Shot();
    pman.PutHandcuff();

    return 0;
}


// 예제 3: 예제 2와 다른 접근방법

/*
예제 2 보다 좋은 방법
 - 권총을 소유하지 않은 경찰 표현 가능
 - 경찰이 수갑, 권총 뿐만아니라 경찰봉도 소유한 것 표현 가능

상속은 꼭 필요한 경우에만 사용 (즉, is-a 관계나 has-a 관계에만 상속 사용)

상속의 상속 (다중상속)은 가능하면 피할 것
*/

#include <iostream>
#include <cstring>

using namespace std;

class Gun
{
private:
    int bullet; // 장전된 총알의 수 
public:
    Gun(int bnum) : bullet(bnum) {}
    void Shot()
    {
        cout << "빵" << endl;
        bullet--;
    }
};

class Police 
{
private:
    int handcuffs;  // 소유한 수갑의 수
    Gun* pistol;  // 소유하고 있는 권총

public:
    Police(int bnum, int bcuff) : handcuffs(bcuff)
    {
        if (bnum > 0)
        {
            pistol = new Gun(bnum); // 클래스 내에서 다른 클래스를 생성
        }
        else
        {
            pistol = NULL;
        }
    }
    void PutHandcuff()
    {
        cout << "찰칵" << endl;
        handcuffs--;
    }
    void Shot()
    {
        if (pistol == NULL)
            cout << "헛빵" << endl;
        else
        {
            pistol->Shot();
        }
    }
    ~Police()
    {
        if (pistol != NULL)
            delete pistol;
    }
};

int main(void)
{
    Police pman1(5, 3);
    pman1.Shot();
    pman1.PutHandcuff();

    Police pman2(0, 3);
    pman2.Shot();
    pman2.PutHandcuff();

    return 0;
}