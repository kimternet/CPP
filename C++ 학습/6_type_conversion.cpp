#include <iostream>

int main(){

    // type conversion = conversion a value of one data type to another
    //                   Implicit(암시적) = automatic
    //                   Explicit(명시적) = Precede value with new data type(int)

    int a = 3.14;
    double b = 3.14;
    double c = (int)3.14; // 명시적
    char d = 100;

    // 명시적 비교
    int correct = 8;
    int questions =10;
    double score = correct/questions * 100;
    double score_2= correct/(double)questions * 100;

    std::cout << a <<'\n';
    std::cout << b << '\n';
    std::cout << c << '\n';
    std::cout << d << '\n'; // d
    std::cout << (char) 100<< '\n';

    // 명시적 출력
    std::cout << score <<"%"<<'\n';
    std::cout << score_2 <<"%"<<'\n';

    return 0;
}