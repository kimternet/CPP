//예제 1: C언어의 함수를 C++에서 호출

#include <cstdio>   // stdio.h 에 대응
#include <cstring>  // string.h 에 대응
#include <cmath>    // math.h 에 대응

int main(void)
{
    char str1[] = "Result";
    char str2[30];

    strcpy_s(str2, str1);  // strcpy_s는 오버로딩되어 있음(즉, 크기가 정해진 배열을 두 입력으로 사용할 수 있음)
    printf("%s: %f \n", str1, sin(0.14));
    printf("%s: %f \n", str2, fabs(-1.25));

    system("pause");  // VC++ 에서만 필요

    return 0;
}

/*
주의: C++에서는 함수가 오버로딩 되어 있음
예를들면 C언어에서의 int abs(int num) 함수의 경우 C++에서는 다음과 같이 오버로딩 되어 있다.

long abs(long num)
float abs(float num)
double abs(double num)
long double abs(long double num)
*/

