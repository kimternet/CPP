#include <iostream>

// cout << (insertion operator)
// cin >> (extraction operator)

int main(){

    // std::string name;
    // int age;

    // std::cout << "What's your name?:";
    // //std::cin >> name; // 문자열x , 공백x
    // std::getline(std::cin, name);// 문자열, 공백

    // std::cout <<"What's your age?:";
    // std::cin >> age;

    // std::cout << "Hello " << name <<'\n';
    // std::cout << "You are " << age << " years old";

    // getline 전에 input을 받으면 input buffer 문제가 있다.
    // getline 함수 cin뒤에 ws해서 공백 제거(줄바꿈문자 등)  추가
    int a;
    std::string name;
    std::cout << "what's your number?";
    std::cin >> a;
    std::cout << "what's your name?";
    //std::getline(std::cin, name);
    std::getline(std::cin >> std::ws, name);

    return 0;
}