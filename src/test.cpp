#include <iostream>
#include <optional>

int main(){
    std::cout<<"HW!"<<'\n';
    std::optional<int> value;
    std::cout<<value.has_value();
    std::cout<<value.value();
    return 0;
}
