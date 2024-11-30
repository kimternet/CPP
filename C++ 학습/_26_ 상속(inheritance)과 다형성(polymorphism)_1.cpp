// *********************** //
// 객체 포인터의 참조 관계 //
// *********************** //

// 예제 1: 객체 포인터 (Is-A 관계)
/*
A클래스 포인터 A*는 A객체를 직접 가리킬 수 있다. (객체의 주소값을 저장한다.)
A클래스 포인터 A*는 A클래스를 상속하는 (다중)유도클래스도 가리킬 수 있다.
*/

#include <iostream>

using namespace std;

class Person 
{
public:
    void Sleep() 
    {
        cout << "Sleep" << endl;
    }
};

class Student : public Person
{
public:
    void Study()
    {
        cout << "Study" << endl;
    }
};

class PartTimeStudent : public Student
{
public:
    void Work()
    {
        cout << "Work" << endl;
    }
};

int main() 
{
    Person* Kim = new Student;
    Person* Park = new PartTimeStudent;
    Student* Lee = new PartTimeStudent;

    Kim->Sleep(); // Student 'IS A' Person.
    Park->Sleep(); // PartTimeStudent 'IS A' Person.
    Lee->Study(); // PartTimeStudent 'IS A' Student

    delete Kim;
    delete Park;
    delete Lee;

    return 0;
}

// 예제 2: 급여관리 확장성 문제 해결 1/3단계

/*
정규직, 영업직, 임시직 모두 고용의 한 형태이다.

영업직은 정규직의 일종이다.
 - 고용인 : class Emplyee
 - 정규직: class PermanentWorker
 - 임시직: class TemporaryWorker
 - 영업직: class SalesWorker
 
EmployHandler클래스가 관리하는 대상이 Employee가 되게하면 
Employee를 상속하게 되는 모든 유도 클래스를 제어할 수 있게된다. (객체 지향 프로그램의 핵심!)
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
        /* 지금은 에러 발생하므로 사용 안함. 나중에 최종 수정된 버전에서 사용함.
        for(int i = 0; i < empNum; i++)
        {
            empList[i]->ShowSalaryInfo();
        }
        */
    }
    void ShowTotalSalary() const
    {
        int sum = 0;
        /* 지금은 에러 발생하므로 사용 안함. 나중에 최종 수정된 버전에서 사용함.
        for(int i = 0; i < empNum; i++)
        {
            sum += empList[i]->GetPay();
        }
        */
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

    // 직원 등록
    handler.AddEmployee(new PermanentWorker("박효원", 1000));
    handler.AddEmployee(new PermanentWorker("라태인", 900));
    handler.AddEmployee(new PermanentWorker("강건욱", 800));

    // 이번 달에 사장이 지불해야 할 지불해야 할 직원 급여
    handler.ShowAllSalaryInfo();

    // 이번 달에 사장이 지불해야 할 직원 급여 총 합
    handler.ShowTotalSalary();

    return 0;
}

// 예제 3: 급여관리 확장성 문제 해결 2/3단계

/*
정규직 급여: 월 기본급여
영업직 급여: 월 기본급여 + 인센티브
임시직 급여: 시간당 급여 * 일한 시간
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
    void ShowSalaryInfo() const  // PermanentWorker의 ShowSalaryInfo()와 같은 이름이지만 꼭 정의해야함. 그래야  PermanentWorker의  GetPay()가 아닌 SalesWorker의  GetPay()를 사용할 수 있음.
    {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;  // SalesWorker의  GetPay()
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
        /* 지금은 에러 발생하므로 사용 안함. 나중에 최종 수정된 버전에서 사용함.
        for(int i = 0; i < empNum; i++)
        {
            empList[i]->ShowSalaryInfo();
        }
        */
    }
    void ShowTotalSalary() const
    {
        int sum = 0;
        /* 지금은 에러 발생하므로 사용 안함. 나중에 최종 수정된 버전에서 사용함.
        for(int i = 0; i < empNum; i++)
        {
            sum += empList[i]->GetPay();
        }
        */
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
