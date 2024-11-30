// ************************** //
// 가상함수(Virtual function) //
// ************************** //

// 예제 1: 함수 오버라이딩과 포인터 형

#include <iostream>

using namespace std;

class First
{
public:
    void MyFunc() 
    {
        cout << "First::MyFunc()" << endl;
    }
    void Func1()
    {
        cout << "First::Func1()" << endl;
    }
};

class Second : public First
{
public:
    void MyFunc() // 함수 오버라이딩 (First 클래스에 MyFunc()가 있음)
    {
        cout << "Second::MyFunc()" << endl;
    }
    void Func2()
    {
        cout << "Second::Func2()" << endl;
    }
};

class Third : public Second
{
public:
    void MyFunc() // 함수 오버라이딩 (Second 클래스에 MyFunc()가 있음)
    {
        cout << "Third::MyFunc()" << endl;
    }
    void Func3()
    {
        cout << "Third::Func3()" << endl;
    }
};

int main()
{
    Third* third = new Third;
    Second* second = third; // Ok, third를 만들때 이미 Second, First 객체를 묵시적으로 만들었음
    First* first = second;  // Ok, second를 만들때 이미 First 객체를 묵시적으로 만들었음

    // 하지만 맴버 함수를 접근할 때에는 해당 클래스의 함수만 접근 가능
    first->MyFunc();
    second->MyFunc();
    third->MyFunc();

    cout << endl;

    first->Func1(); // Ok
    //first->Func2(); // 에러: First 클래스에는 Func2() 맴버 함수가 없다.
    //first->Func3(); // 에러: First 클래스에는 Func3() 맴버 함수가 없다.

    cout << endl;

    second->Func1(); // Ok, First 클래스를 상속받았기에 Func1()에 접근 가능
    second->Func2(); // Ok, 자기 자신의 멤버함수
    //second->Func3(); // 에러: Second 클래스에는 Func3() 맴버 함수가 없다.

    cout << endl;

    third->Func1(); // Ok, Third 클래스는 Second 클래스를 통하여 결국 First 클래스를 상속 받았음 
    third->Func2(); // Ok, Third 클래스는 Second 클래스를 상속 받았음
    third->Func3(); // Ok, 자기 자신의 멤버함수

    return 0;
}

// 예제 2: 가상 함수 (virtual function)
// 자료형에 기반하지 않고 포인터 변수가 실제로 가리키는 객체를 참조하여 호출 대상 결정

#include <iostream>

using namespace std;

class First
{
public:
    virtual void MyFunc() // 가상 함수
    {
        cout << "First::MyFunc()" << endl;
    }
};

class Second : public First
{
public:
    virtual void MyFunc() // 가상 함수
    {
        cout << "Second::MyFunc()" << endl;
    }
};

class Third : public Second
{
public:
    virtual void MyFunc() // 가상 함수
    {
        cout << "Third::MyFunc()" << endl;
    }
};

int main()
{
    Third* third = new Third;
    Second* second = third; // Ok, third를 만들때 이미 Second, First 객체를 묵시적으로 만들었음
    First* first = second;  // Ok, second를 만들때 이미 First 객체를 묵시적으로 만들었음

    cout << "address of third (즉, thrid 안의 내용  = 주소) " << third << endl;
    cout << "address of second(즉, second 안의 내용 = 주소) " << second << endl;
    cout << "address of first (즉, first 안의 내용  = 주소) " << first << endl;

    // 가상함수로 선언된 맴버 함수를 접근할 때에는 실제 객체의 맴버 함수 호출
    // 가상함수로 선언된 third = second = first 인 상황이므로 third의 맴버 함수 호출
    first->MyFunc();
    second->MyFunc();
    third->MyFunc();

    return 0;
}

// 예제 3: 급여관리 확장성 문제 해결 3/3단계

#include <iostream>
#include <cstring>

using namespace std;

class Employee 
{
private:
    char name[100];
public:
    Employee(const char name[])
    {
        strcpy_s(this->name, 100, name);
    }
    void ShowYourName() const 
    {
        cout << "name:" << name << endl;
    }
    virtual int GetPay() const  // 가상함수로 선언하여 유도 클래스들의 해당 GetPay()를 쓸 수 있게 함.
    {
        return 0;
    }
    virtual void ShowSalaryInfo() const // 가상함수로 선언하여 유도 클래스들의 해당 ShowSalaryInfo()를 쓸 수 있게 함.
    { }
};

class PermanentWorker : public Employee
{
private:
    int salary;
public:
    PermanentWorker(const char name[], int money) : Employee(name), salary(money) {}
    int GetPay() const
    {
        return salary;
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class TemporaryWorker : public Employee
{
private:
    int workTime;  // 이달에 일한 시간의 총 합
    int payPerHour;  // 시간당 급여
public:
    TemporaryWorker(const char name[], int pay) : Employee(name), workTime(0), payPerHour(pay) {}
    void AddWorkTime(int time)  // 일한 시간 추가
    {
        workTime += time;
    }
    int GetPay() const  // 이달의 급여 (함수 오버라이드 (function override), 즉 상속된 함수의 이름은 같으나 내용이 수정
    {
        return workTime * payPerHour;
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class SalesWorker : public PermanentWorker
{
private:
    int salesResult;  // 월 판매 실적
    double bonusRatio;  // 상여금 비율
public:
    SalesWorker(const char name[], int money, double ratio) 
        : PermanentWorker(name, money), salesResult(0), bonusRatio(ratio) {}
    void AddSalesResult(int value)
    {
        salesResult += value;
    }
    int GetPay() const // 함수 오버라이드
    {
        return PermanentWorker::GetPay() // PermanentWorker의 GetPay() 함수 호출
            + (int)(salesResult * bonusRatio);
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class EmployeeHandler
{
private:
    Employee* empList[50]; // 최대 50명 직원
    int empNum; // 현재 직원 명수
public:
    EmployeeHandler() : empNum(0) {}
    void AddEmployee(Employee* emp)  // 외부에서 만든 Employee 클래스를 가르키는 포인터
    {
        empList[empNum++] = emp; // 새로운 직원 등록
    }
    void ShowAllSalaryInfo() const
    {
        for(int i = 0; i < empNum; i++)
        {
            empList[i]->ShowSalaryInfo();
        }
    }
    void ShowTotalSalary() const
    {
        int sum = 0;
        for(int i = 0; i < empNum; i++)
        {
            sum += empList[i]->GetPay();
        }
        cout << "salary sum: " << sum << endl;
    }
    ~EmployeeHandler() // 외부에서 new를 통해 만든 Employee 클래스를 소멸시킨다.
    {
        for (int i = 0; i < empNum; i++)
        {
            delete empList[i];
        }
    }
};

int main() 
{
    EmployeeHandler handler; // 직원 관리 목적으로 설계된 클래스의 객체 생성

    // 정규직 등록
    handler.AddEmployee(new PermanentWorker("박효원", 1000));
    handler.AddEmployee(new PermanentWorker("라태인", 900));


    // 임시직 등록
    TemporaryWorker* alba = new TemporaryWorker("강건욱", 500);
    alba->AddWorkTime(5); // 5시간 알바생(임시직) 일함
    handler.AddEmployee(alba);  // 알바생 등록


    // 영업직 등록
    SalesWorker* salesman = new SalesWorker("김준수", 1000, 0.1); // 10%의 인센티브
    salesman->AddSalesResult(7000); // 상품 7000개 팔았음
    handler.AddEmployee(salesman);


    // 이번 달에 사장이 지불해야 할 지불해야 할 직원 급여
    handler.ShowAllSalaryInfo();

    // 이번 달에 사장이 지불해야 할 직원 급여 총 합
    handler.ShowTotalSalary();

    return 0;
}

// 예제 3: 순수 가상함수(pure virtual function)와 추상 클래스(abstract class)

/*
순수 가상함수: 함수의 몸체를 정의하지 않는 함수

추상 클래스: 객체 생성을 목적으로 하지 않은 클래스로 하나 이상의 멤버함수를 순수 가상함수로 선언한 클래스.

아래의 예제에서 Employee는 추상 클래스이고 main 안에서 Empolyee* mep = new Employee("강건욱")과 같은 객체생성을 원하지 않는다. (즉, 좀더 구체적인 정보를 담고 있는 Employee를 상속한 유도 클래스의 객체를 사용한다.) 

하지만 EmployeeHandler 는 Empolyee를 가르키고만 있어도 Empolyee를 상속한 모든 유도 클래스내의 같은 이름의 가상함수들에게로 접근가능하다. 따라서 EmployeeHandler의 입장에서는 Empolyee를 상속한 (미래의) 새로운 클래스들이 등장해도 EmployeeHandler 내부를 수정할 필요가 없다.
*/

#include <iostream>
#include <cstring>

using namespace std;

class Employee 
{
private:
    char name[100];
public:
    Employee(const char name[])
    {
        strcpy_s(this->name, 100, name);
    }
    void ShowYourName() const 
    {
        cout << "name:" << name << endl;
    }
    virtual int GetPay() const  = 0; // 순수 가상함수로 선언 (주의: 0을 대입하는 문법이 아님)
    virtual void ShowSalaryInfo() const = 0; // 순수 가상함수로 선언 (주의: 0을 대입하는 문법이 아님)

class PermanentWorker : public Employee
{
private:
    int salary;
public:
    PermanentWorker(const char name[], int money) : Employee(name), salary(money) {}
    int GetPay() const
    {
        return salary;
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class TemporaryWorker : public Employee
{
private:
    int workTime;  // 이달에 일한 시간의 총 합
    int payPerHour;  // 시간당 급여
public:
    TemporaryWorker(const char name[], int pay) : Employee(name), workTime(0), payPerHour(pay) {}
    void AddWorkTime(int time)  // 일한 시간 추가
    {
        workTime += time;
    }
    int GetPay() const  // 이달의 급여 (함수 오버라이드 (function override), 즉 상속된 함수의 이름은 같으나 내용이 수정
    {
        return workTime * payPerHour;
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class SalesWorker : public PermanentWorker
{
private:
    int salesResult;  // 월 판매 실적
    double bonusRatio;  // 상여금 비율
public:
    SalesWorker(const char name[], int money, double ratio) 
        : PermanentWorker(name, money), salesResult(0), bonusRatio(ratio) {}
    void AddSalesResult(int value)
    {
        salesResult += value;
    }
    int GetPay() const // 함수 오버라이드
    {
        return PermanentWorker::GetPay() // PermanentWorker의 GetPay() 함수 호출
            + (int)(salesResult * bonusRatio);
    }
    void ShowSalaryInfo() const
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class EmployeeHandler
{
private:
    Employee* empList[50]; // 최대 50명 직원
      // Employee형 포인터 이지만 Employee을 상속한 유도 클래스들(즉, PermanentWorker, TemparayWorker, SalseWorker)의 맴버들을 접근할 수 있음
      // Employee의 가상함수 선언을 통해 오버라이드 된 유도 클래스 맴버 함수를 호출할 수 있음. 즉, Employee형 포인터의 제약을 벗어남.
    int empNum; // 현재 직원 명수
public:
    EmployeeHandler() : empNum(0) {}
    void AddEmployee(Employee* emp)  // 외부에서 만든 Employee 클래스를 가르키는 포인터
    {
        empList[empNum++] = emp; // 새로운 직원 등록
    }
    void ShowAllSalaryInfo() const
    {
        for(int i = 0; i < empNum; i++)
        {
            empList[i]->ShowSalaryInfo();
        }
    }
    void ShowTotalSalary() const
    {
        int sum = 0;
        for(int i = 0; i < empNum; i++)
        {
            sum += empList[i]->GetPay();
        }
        cout << "salary sum: " << sum << endl;
    }
    ~EmployeeHandler() // 외부에서 new를 통해 만든 Employee 클래스를 소멸시킨다.
    {
        for (int i = 0; i < empNum; i++)
        {
            delete empList[i];
        }
    }
};

int main() 
{
    EmployeeHandler handler; // 직원 관리 목적으로 설계된 클래스의 객체 생성

    // 정규직 등록
    handler.AddEmployee(new PermanentWorker("박효원", 1000));
    handler.AddEmployee(new PermanentWorker("라태인", 900));


    // 임시직 등록
    TemporaryWorker* alba = new TemporaryWorker("강건욱", 500);
    alba->AddWorkTime(5); // 5시간 알바생(임시직) 일함
    handler.AddEmployee(alba);  // 알바생 등록


    // 영업직 등록
    SalesWorker* salesman = new SalesWorker("김준수", 1000, 0.1); // 10%의 인센티브
    salesman->AddSalesResult(7000); // 상품 7000개 팔았음
    handler.AddEmployee(salesman);


    // 이번 달에 사장이 지불해야 할 지불해야 할 직원 급여
    handler.ShowAllSalaryInfo();

    // 이번 달에 사장이 지불해야 할 직원 급여 총 합
    handler.ShowTotalSalary();

    return 0;
}

//예제 4: 다형성(polymorphism)

#include <iostream>

using namespace std;

class First
{
public:
    virtual void SimpleFunc()
    {
        cout << "First" << endl;
    }
};

class Second : public First
{
public:
    virtual void SimpleFunc()
    {
        cout << "Second" << endl;
    }
};


int main()
{
    First* ptr = new First;
    ptr->SimpleFunc();
    delete ptr;

    ptr = new Second;
    ptr->SimpleFunc();  // 다형성의 예:  같은 문장 다른 결과!
    delete ptr;

    return 0;
}

