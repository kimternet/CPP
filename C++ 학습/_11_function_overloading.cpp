//함수 오버로딩(function overloading)

#include <iostream>

//함수 선언부
void MyFunc(void); // 인자가 없는 함수 MyFunc 선언
void MyFunc(char c); // char 타입의 인자를 받는 함수 MyFunc 선언
void MyFunc(int a, int b); // 두 개의 int 타입 인자를 받는 함수 MyFunc선언

int main(void) {
    // 각기 다른 인자를 갖는 MyFunc  호출
    MyFunc(); // 인자가 없는 MyFunc 호출
    MyFunc('A'); // char 타입 인자 'A'를 갖는 MyFunc 호출
    MyFunc(12, 13); // 두 개의 int 타입 인자 12, 13을 갖는 MyFunc 호출 
    
    return 0;

    
}

// 함수 정의부

void MyFunc(void){
    std::cout << "MyFunc(void) called" << std::endl; //인자가 없는 MyFunc 호출 시 출력되는 메시지
}


//char 타입 인자를 갖는 MyFunc 호출 시 출력되는 메시지 
void MyFunc(char c){
    std::cout << "MyFunc(char c) called" << std::endl; 
    
}
 // 두 개의 int 타입 인자를 갖는 MyFunc 호출 시 출력되는 메시지
void MyFunc(int a, int b){
    std::cout << "MyFunc(int a, int b) called" << std::endl;
}