//예제 1: 참조자는 자신이 참조하는 변수를 대신할 수 있는 또하나의 이름

#include <iostream>

using namespace std;

int main(void)
{
    int num1 = 20;
    int& num2 = num1; // num1과 같은 메모리 공간을 가리키는 또 하나의 변수 이름. 
                      //즉, 참조자(reference)는 변수에 대해서만 선언이 가능하고, 
                      // 선언과 동시에 참조할 변수로 초기화 해야 한다.
    int* num3 = &num1; // num1의 시작 주소를 가리키는 포인터

    cout << "num1의 주소: " << &num1 << endl;
    cout << "num2의 주소: " << &num2 << endl;
    cout << "num3의 주소: " << &num3 << endl;

    cout << "sizeof num1: " << sizeof(num1) << endl;
    cout << "sizeof num2: " << sizeof(num2) << endl;
    cout << "sizeof num3: " << sizeof(num3) << endl;

    num2 = 3047;  // int형 변수 num1 처럼 int 참조자로 선언된 num2에 정수값을 할당할 수 있다.
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;

    system("pause");  // VC++ 에서만 필요

    return 0;
}

// 예제 2: 참조자의 선언 가능 범위

/*
int& ref = 20 (잘못됨)
int& ref; (잘못됨)
int& ref = NULL; (잘못됨)
int& ref와 int &ref는 같은 표기 (참고: int* ptr와 int *ptr은 같은 표기)
*/


#include <iostream>

using namespace std;

int main(void)
{
    int arr[3] = {1, 2, 3};

    int& ref1 = arr[0];
    int& ref2 = arr[1];
    int& ref3 = arr[2];

    int* ptr1 = &arr[0];
    int* ptr2 = &arr[1];
    int* ptr3 = &arr[2];

    cout << ref1 << endl;
    cout << ref2 << endl;
    cout << ref3 << endl;

    cout << ptr1 << endl;
    cout << ptr2 << endl;
    cout << ptr3 << endl;

    cout << *ptr1 << endl;
    cout << *ptr2 << endl;
    cout << *ptr3 << endl;

    system("pause");  // VC++ 에서만 필요

    return 0;
}

// 예제 3: 포인터 변수의 참조자

#include <iostream>  
using namespace std;

int main(void)
{
    int num = 12;  // 정수형 변수 num에 12를 저장.
    int* ptr = &num;  // ptr은 num의 주소를 저장하는 '포인터'다.
    int** dptr = &ptr;  // dptr은 ptr의 주소를 저장하는 '이중 포인터'이다.

    // 아래는 '참조자'와 '포인터 참조자'를 선언하는 부분.
    int& ref = num;  // ref는 num을 가리키는 '참조자'이다. ref를 사용하면 num과 "같은 값"을 가리킨다.
    int*& pref = ptr;  // pref는 ptr을 가리키는 '포인터 참조자'이다. 즉, pref는 "ptr과 같은 포인터"를 가리킨다.
    int**& dpref = dptr;  // dpref는 dptr을 가리키는 '이중 포인터 참조자'이다. dptr과 같은 값을 가리킨다.

    // 아래는 출력 부분입니다.
    cout << ref << endl;  // ref는 num을 참조하므로, num의 값(12)이 출력된다.
    cout << *pref << endl;  // pref는 ptr을 참조하므로, *pref는 num의 값(12)을 출력한다.
    cout << **dpref << endl;  // dpref는 dptr을 참조하므로, **dpref는 num의 값(12)을 출력한다.

    system("pause");  // 프로그램이 종료되기 전에 잠시 멈춤. (VC++ 전용 코드)

    return 0; 
}