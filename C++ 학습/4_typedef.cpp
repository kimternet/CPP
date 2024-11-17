#include <iostream>
#include <vector>

//typedef std::vector<std::pair<std::string,int>> pairlist_t
//typedef std::string text_t;
//typedef int number_t;
using text_t = std::string;
using number_t = int;

int main(){

    //typedef = reserved keyword(예약 키워드) used to create an additional name
    //          (alias) for another data type.
    //          New identifier for an existing type
    //          Helps with readablility(가독성) and reduces typos(오타방지)
    //          Use when there is a clear benefit
    //          Replaced with 'using' (work better w/ templates)
    //std::string firstName = "kim";
    
    
    text_t firstName = "kim";
    std::cout << firstName << '\n';
    
    number_t age =21;
    std::cout << age <<'\n';    
    
    return 0;

}