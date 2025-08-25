#include <iostream>
#include "StringCalculator.h"

int main() {
    StringCalculator calc;
    
    std::cout << "Testing simple case..." << std::endl;
    int result = calc.Add("1,2");
    std::cout << "Result: " << result << std::endl;
    
    std::cout << "Testing custom delimiter '*'..." << std::endl;
    try {
        result = calc.Add("//*\n1*2*3");
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
