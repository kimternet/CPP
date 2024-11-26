//예제 1: malloc과 free 복습
// strcpy_s
#include <iostream>
#include <string.h>

using namespace std;

char* MakeStr(int len)
{
    char* str = (char*)malloc(sizeof(char)*len);
    return str;
}


int main(void)
{
    char* mystr = MakeStr(20);

    strcpy_s(mystr, 20, "I am so happy.");  // strcpy는 안전하지 않은 함수이므로 strcpy_s 사용
    cout << mystr << endl;

    free(mystr);

    return 0;
}


// 예제 2: new와 delete을 통한 힙 영역 동적 메모리 할당
// dynamic memory in C++
#include <iostream>
#include <string.h>

using namespace std;

char* MakeStr(int len)
{
    char* str = new char[len];
    return str;
}


int main(void)
{
    char* mystr = MakeStr(20);

    strcpy_s(mystr, 20, "I am so happy.");
    cout << mystr << endl;

    delete[]mystr;


    return 0;
}

// 예제 3: 객체의 생성은 반드시 new와 delete 사용

#include <iostream>

using namespace std;

class Simple
{
public:
    Simple()
    {
        cout << "I'm a simple constructor!" << endl;
    }
};

int main(void)
{
    cout << "case 1: ";
    Simple* sp1 = new Simple;

    cout << "case 2: ";
    Simple* sp2 = (Simple*)malloc(sizeof(Simple) * 1);

    cout << endl << "end of main" << endl;

    delete sp1;
    free(sp2);


    return 0;
} 

// 예제 4: 참조자를 통한 힙 영역 접근

#include <iostream>
#include <iomanip>  // std::hex 선언

using namespace std;


int main(void)
{
    int* ip = new int;  // new int[1]와 같은 표현
    int& ref = *ip;  // 참조자를 통한 힙 영역 접근. 즉, int ref를 스택이 아닌 힙에서 생성한 효과

    *ip = 100;

    cout << std::hex << "ip: " << ip << endl;  // 주소가 16진수로 표시
    cout << "ip: " << ip << endl;  // <iomanip>에 의해 주소가 자동으로 16진수로 표시
    cout << "*ip: " << *ip << endl;
    cout << "ref: " << ref << endl;
    cout << "ref 주소: " << &ref << endl;

    delete ip;

    return 0;
} 