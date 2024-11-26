//예제 1: 참조자를 매개 변수로 하는 함수

#include <iostream>

using namespace std;

void SwapByRef2(int& ref1, int& ref2)
{
    int temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}

int main(void)
{
    int val1 = 10;
    int val2 = 20;

    cout << "---before swapping---" << endl;
    cout << "val1: " << val1 << endl;
    cout << "val2: " << val2 << endl;

    SwapByRef2(val1, val2);  // 함수 호출 시 함수의 매개 변수 참조자들은 초기화 된다.
      // 즉, int& ref1 = val1, int& ref2 = val2로 초기화 됨.

    cout << "---after swapping---" << endl;
    cout << "val1: " << val1 << endl;
    cout << "val2: " << val2 << endl;

    return 0;
}

// 예제 2: 함수의 반환형이 참조형(reference type)인 경우

#include <iostream>

using namespace std;

int& RefRetFunc1(int& ref)
{
    ref++;
    return ref;
}

int main(void)
{
    int num1 = 1;
    int& num2 = RefRetFunc1(num1);

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;

    num1++;
    num2++;

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;


    return 0;
}

// 예제 3: 참조형 반환 후 변수 값만 저장

#include <iostream>

using namespace std;

int& RefRetFunc2(int& ref)
{
    ref++;
    return ref;
}

int main(void)
{
    int num1 = 1;
    int num2 = RefRetFunc2(num1);

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;

    num1 += 2;
    num2 += 100;

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;


    return 0;
}

// 예제 4: 참조형의 값 반환

#include <iostream>

using namespace std;

int RefRetFunc2(int& ref)
{
    ref++;
    return ref;
}

int main(void)
{
    int num1 = 1;
    int num2 = RefRetFunc2(num1);
    //int& num2 = RefRetFunc2(num1);  // 에러 발생: 함수의 int 리턴값은 명시적 변수이름(즉, 메모리 공간)이 아니다.

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;

    num1 += 2;
    num2 += 100;

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;

    return 0;
}

// 예제 5: const 참조자를 통한 상수 참조
// int& ref = 20 는 에러, 하지만 const int& ref = 20은 가능함

#include <iostream>

using namespace std;

int Adder(const int& a, const int& b)
{
    return a + b;
}

int main(void)
{
    int num1 = 1;
    int num2 = 2;
    int num3 = Adder(num1, num2);

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;
    cout << "num3: " << num3 << endl;
    cout << "Adder(4,5): " << Adder(4, 5) << endl;  // const int 참조자에 정수 상수 사용 가능

    return 0;
}