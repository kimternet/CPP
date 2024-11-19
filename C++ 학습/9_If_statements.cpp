#include <iostream>

int main(){

    // if statements = do something if a condition is true.
    //                 if not, then don't do it.

    int age;
    
    std::cout<< "Enter your age: ";
    std::cin >> age;
    
    if(age >= 100){
        std::cout << "You are too old to enter this site!";
    }
    
    //if(age >= 18){ // 순차프로그래밍 예시 라인
    //  std::cout << "Welcome to the site!";
    //}
    
    else if (age < 0){
        std::cout << "You haven't been born yet!";
    }
    
    //else if(age >= 100){
    //  std::cout << "You are too old to enter this site!";
    //} 만약 100살 이상도 if문에 조건을 넣고 싶다면 상위 18살 조건보다 위에 있어야 한다. 이유는 프로그래밍은 순차진행이기 때문에 이미 조건 18살에 100살 이상이 충족되기 때문이다.
    
    else if(age >= 18){ // 이렇게 순서를 바꿔주면 100살 이상과 18살 이상의 두 조건 모두 충족이 된다.
        std::cout << "Welcome to the site!";
    }
    
    else{
        std::cout << "You are not old enough to enter!";
    }

    return 0;
}