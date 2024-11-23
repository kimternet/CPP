
//  예제 1: 함수의 매개변수에 설정하는 디폴트 값의 의미

#include <iostream>  // 입출력을 위한 헤더 파일 포함

// Adder 함수 선언 및 정의, 디폴트 값으로 num1 = 1, num2 = 2 설정
int Adder(int num1 = 1, int num2 = 2){
    return num1 + num2;  // 두 숫자를 더한 값을 반환
}

int main(void) {
    // 디폴트 값(1, 2) 사용
    std::cout << Adder() << std::endl;  // Adder(1,2) 호출, 결과는 3
    // 첫 번째 매개변수에 5를 전달, 두 번째 매개변수는 디폴트 값 2 사용
    std::cout << Adder(5) << std::endl; // Adder(5, 2) 호출, 결과는 7
    // 두 개의 매개변수에 3과 5를 전달
    std::cout << Adder(3, 5) << std::endl; // Adder(3, 5) 호출, 결과는 8

    return 0;  
}


// 예제 2 디폴트 값은 함수의 선언부분에만 표현

#include <iostream>  // 입출력을 위한 헤더 파일 포함

// Adder 함수 선언, 디폴트 값은 함수 선언에서만 설정
int Adder(int num1 = 1, int num2 = 2);

int main(void) {
    // 디폴트 값(1, 2) 사용
    std::cout << Adder() << std::endl;  // Adder(1, 2) 호출, 결과는 3
    // 첫 번째 매개변수에 5를 전달, 두 번째 매개변수는 디폴트 값 2 사용
    std::cout << Adder(5) << std::endl; // Adder(5, 2) 호출, 결과는 7
    // 두 개의 매개변수에 3과 5를 전달
    std::cout << Adder(3, 5) << std::endl; // Adder(3, 5) 호출, 결과는 8

    return 0; 
}

// Adder 함수 정의, 디폴트 값은 설정하지 않음
int Adder(int num1, int num2) {
    return num1 + num2;  // 두 숫자를 더한 값을 반환
}

// 예제3 부분적 디폴트값 설정
#include <iostream>
//부분적 디폴트 값은 오른쪽에서 왼쪽으로
int BoxVolume(int length, int width = 1, int height = -1); 

int main(void){
    // BoxVolume(3, 3,3)
    std::cout << "[3, 3, 3] : " << BoxVolume(3, 3, 3) << std::endl;
    //BoxVolume(5, 5, 1)
    std::cout << "[5, 5, 1] : " << BoxVolume(5, 5) << std::endl; 
    //BoxVolume(7, 1, 1)
    std::cout << "[7, 1, 1] : " << BoxVolume(7) << std::endl;
    
    return 0;
}

int BoxVolume(int length, int width, int height){
    return length * width * height;
}