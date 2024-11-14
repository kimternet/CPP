#include <iostream>

int main() {
    
    //declaration
    int x; 
    x = 5;

    std::cout << x << '\n';
    
    int z = 3;
    int y = 6;
    int sum = z + y;

    std::cout << z << '\n';
    std::cout << y << '\n';
    std::cout << sum << '\n';

    //integer (whole number)

    int age = 21;
    int year = 2023;
    int days = 7.5; // X, error

    std::cout << days << '\n';

    //double (number including decimal)
    double price = 10.99;
    double gpa = 2.5;
    double temperature = 25.1;

    std::cout << price <<'\n';

    // single character
    char grade = 'A';
    char initial = 'B';
    char currency = '$';

    std::cout << initial << '\n';

    // boolean (true or false)
    bool student = false;
    bool power = true;
    bool forSale = true;

    // string (objects that represents a sequence of tex )
    std::string name = "Kim";
    std::string day = "Friday";
    std::string food = "pizza";
    std::string address = "123 seoul";

    std::cout << "Hello " << name << '\n';
    std::cout << "You are " << age << "years old" <<'\n';
    std::cout << "i like " << food ;


}