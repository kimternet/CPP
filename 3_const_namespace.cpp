# include <iostream>

namespace first{
    int x =1;
}

namespace second{
    int x = 2;
}
int main(){
    
    // the const keyword specifies that a variables' a value is constant
    // tells the copiler to prevent anything from modifying it
    // (read-only)

    const double PI = 3.14159;
    double radius= 10;
    double circumference =2 * PI * radius;

    std::cout << circumference << "cm";

    const int LIGHT_SPEED = 299792458;
    const int WIDTH = 1920;
    const int HEIGHT = 1080;

    std::cout << HEIGHT<<'\n';
    
    /*
    Namespace = provides a solution for preventing name conflicts
    in large projects. Each entity nees a unique name.
    A namespace allows for identically named entities
    as long as the namespaces are different.
    */

    using namespace second;
    int x = 0;

    std::cout << x << '\n'; // 0을 출력, int x= 0이 선언되어 있지 않고, using namespace로 second를 명시해주면 second에 해당되는 값이 출력된다.
    std::cout << first::x << '\n'; // first x값 출력


    return 0;
}