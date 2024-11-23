// 예제 1: 범위지정 연산자 :: 와 이름 공간
// 이름 공간(namespace)을 사용하여 동일한 이름의 함수를 구분할 수 있다.
#include <iostream>

namespace Company1
{
    void func(void)
    {
        std::cout << "Company1이 정의한 함수" << std::endl; // 함수 정의
    }
}

namespace Company2
{
    void func(void)
    {
        std::cout << "Company2가 정의한 함수" << std::endl;
    }
}

int main(void)
{
    Company1::func(); // 함수 호출
    Company2::func();
    
    return 0;
}

// 예제 2: 이름 공간 기반의 함수 선언과 정의의 구분
// 함수 선언과 정의를 분리하여 사용할 수 있고, 이름 공간을 통해 구분된다.
#include <iostream>

namespace Company1
{
    void func(void); // 함수 선언
}

namespace Company2
{
    void  func(void);
}

int main(void)
{
    Company1::func(); // 함수 호출
    Company2::func();
    
    return 0;
}

void Company1::func(void)
{
    std::cout << "Company1이 정의한 함수" << std::endl; // 함수 정의
}

void Company2::func(void)
{
    std::cout << "Company2가 정의한 함수" << std::endl;
}

// 예제3: 동일한 이름 공간에 정의된 함수 호출
// 동일한 이름 공간 내에서는 함수 호출 시 이름 공간을 생략할 수 있다.
#include <iostream>

namespace Company1
{
    void func(void);
    void hello(void);  // 각각의 함수마다 이름공간으로 채워도해도 된다.
}

namespace Company2
{
    void func(void);
}

int main(void)
{
    Company1::func(); // 함수 호출
    
    return 0;
}

void Company1::hello(void)
{
    std::cout<<"hello"<<std::endl; // hello 함수 정의
}

void Company1::func(void)
{
    std::cout <<"Company1가 정의한 함수" << std::endl;
    hello(); // 같은 이름 공간의 함수는 이름 공간 생략 가능하다. 즉 Company1::hello()
    Company2::func(); // 다른 이름공간의 함수
    
}

void Company2::func(void)
{
    std::cout<<"Company2가 정의한 함수" <<std::endl;
}


//예제 4: 이름 공간의 중첩
// 이름 공간은 중첩될 수 있으며, 각각의 이름 공간 내에 동일한 이름의 변수를 사용할 수 있다.
#include <iostream>

namespace Parent
{
    int num = 0;
    namespace Son
    {
        int num = 1; // son의 변수 num
    }
    namespace Daughter // Daughter의 변수 num
    {
        int num = 2;
    }
}

int main(void)
{   //해당 변수들 출력
    std::cout << Parent::num << std::endl; 
    std::cout << Parent::Son::num << std::endl;
    std::cout << Parent::Daughter::num << std::endl;
    
    return 0;
}

//예제  5: Using을 이용한 이름 공간의 명시
// using을 사용하여 특정 이름 공간의 함수나 변수를 명시하여, 해당 이름 공간을 생략할 수 있다.
#include <iostream>

namespace Hybrid
{
    void HybFunc(void)
    {
        std::cout << "So simple function!" << std::endl;
        std::cout << "In namespace Hybrid" << std::endl;
    }
}

int main(void)
{
    using Hybrid::HybFunc; // 이 라인 실행 후 namespace Hybrid는 생략 가능
    HybFunc();
    
    return 0;
}

//예제 6: 프로그램 전체에 영향을 미치는 using의 선언 방법
// using 선언을 사용하여 프로그램 전체에서 특정 이름 공간을 생략할 수 있다.
#include <iostream>

using std::cin; // std::cin을 생략 가능하게 만듬.
using std::cout;// std::count을 생략 가능하게 만듬.
using std::endl;// std::endl을 생략 가능하게 만듬

int main(void){
    int num = 20;
    cout << "Hello World!" << endl; // std::cout, std::endl 생략
    cout << "Hello." << "World!" << endl;
    cout << num <<' ' << 'A';
    cout << ' ' << 3.14 << endl;
    
    return 0;
}

//예제 7: 이름 공간 std
// using namespace std는 std 이름 공간의 모든 항목을 생략 가능하게 한다.
// 하지만 이 방법은 충돌 가능성이 있어 주의가 필요하다 
#include <iostream>

using namespace std;

int main(void)
{
    int num = 20;
    cout << "Hello World!" << endl;
    cout << "Hello" << "World" << endl;
    cout << num << ' ' << 'A';
    cout << ' ' << 3.14 << endl;
    
    return 0;
}

//예제8: 이름 공간의 별칭
// 이름 공간에 별칭을 설정하여 길고 복잡한 이름 공간을 간단하게 사용할 수 있다.

#include <iostream>

using namespace std;

namespace AAA{
    namespace BBB{
        namespace CCC{
            int num1;
            int num2;
        }
    }
}


int main(void){
    AAA::BBB::CCC::num1 = 20;
    AAA::BBB::CCC::num2 = 30;
    
    namespace ABC = AAA::BBB::CCC; // 별칭 ABC 설정
    cout << ABC::num1 << endl;
    cout << ABC::num2 << endl;
    
    return 0;
}

// 예제9: 범위 지정 연산자 ::의 또 다른 기능
// 범위 지정 연산자 ::를 사용하여 전역 변수와 지역 변수를 구분하여 사용할 수 있다.
#include <iostream>

using namespace std;

int val = 100;

int main(void){
    
    int val = 20; // 지역변수
    val += 3; // 지역 변수 val의 값 증가
    ::val += 3; // 전역 변수 val의 값 증가
    
    cout << "지역변수 val의 값: " << val << endl;
    cout << "전역변수 val의 값: " <<::val << endl;
    
    return 0;
}