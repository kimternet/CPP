// 예제 1 매크로 함수(복습)
// 매크로 함수는 컴파일 전에 코드가 치환되어 적용된다.

#include <iostream>
#define SQUARE(x) ((x) * (x))

int main (void){
    
    std::cout << SQUARE(5) << std::endl; // SQUARE매크로를 int형 값에 적용
    std::cout << SQUARE(2.7) << std::endl; // double형에 적용
    
    return 0;
}

// 예제2 C++ 기반의 인라인 함수 정의
// 인라인 함수는 컴파일러가 함수 호출 오버헤드를 줄이기 위해 함수 호출을 호출 지점에서 확장한다.
#include <iostream>

inline int SQUARE(int x)
{
    return x*x;
}

int main(void){
    
    std::cout << SQUARE(5) << std::endl; // 정수형 값 5에 대해 SQUARE 인라인 함수 호출
    std::cout << SQUARE(7.15) << std::endl; // 정수형으로만 적용되므로 7.15를 7로 간주 데이터 손실

    return 0;
}

// 예제3 template 통한 임의의 자료형(맛보기)
// 템플릿을 사용하여 임의의 자료형을 계산하는 인라인 함수를 정의
// 이를 통해 정수형과 실수형 모두에 대해 적용이 가능하다.
#include <iostream>

template <typename T>
inline T SQUARE(T x)
{
    return x*x;
}

int main(void){
    
    std::cout << SQUARE(5) << std::endl; // 정수형 값 5에 대해 SQUARE 템플릿 함수 호출
    std::cout << SQUARE(7.154) << std::endl; //
    
    return 0;
}
