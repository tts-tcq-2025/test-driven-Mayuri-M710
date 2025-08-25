#include <iostream>
#include <cassert>
#include <string>
#include "StringCalculator.h"

// Helper for positive test cases
void checkExpectedResult(int expected, int actual, const std::string& testName) {
    std::cout << "Running test: " << testName << "..." << std::endl;
    std::cout << "Result: " << actual << " (Expected: " << expected << ")" << std::endl;
    assert(expected == actual);
    std::cout << testName << " passed!\n" << std::endl;
}

// Helper for negative test cases (expecting exception)
void checkExceptionCase(const std::string& input, const std::string& expectedMessage, StringCalculator& calc, const std::string& testName) {
    std::cout << "Running test: " << testName << "..." << std::endl;
    try {
        int result = calc.Add(input);
        std::cout << "ERROR: Expected exception but got result: " << result << std::endl;
        assert(false); // force failure
    } catch (const std::exception& e) {
        std::string actualMessage = e.what();
        std::cout << "Exception caught: " << actualMessage << std::endl;
        assert(actualMessage == expectedMessage);
        std::cout << testName << " passed!\n" << std::endl;
    }
}

int main() {
    StringCalculator calc;

    // Test 1: Empty string
    checkExpectedResult(0, calc.Add(""), "Empty string");

    // Test 2: Single numbers
    checkExpectedResult(1, calc.Add("1"), "Single number '1'");
    checkExpectedResult(5, calc.Add("5"), "Single number '5'");

    // Test 3: Two numbers
    checkExpectedResult(3, calc.Add("1,2"), "Two numbers '1,2'");

    // Test 4: Multiple numbers
    checkExpectedResult(6, calc.Add("1,2,3"), "Multiple numbers '1,2,3'");
    checkExpectedResult(15, calc.Add("1,2,3,4,5"), "Multiple numbers '1,2,3,4,5'");

    // Test 5: Newlines as delimiter
    checkExpectedResult(6, calc.Add("1\n2,3"), "Newlines '1\\n2,3'");

    // Test 6: Ignore > 1000
    checkExpectedResult(2, calc.Add("2,1001"), "Ignore numbers > 1000 (2,1001)");
    checkExpectedResult(6, calc.Add("1,2,1001,3,1500"), "Ignore large numbers (1,2,1001,3,1500)");

    // Test 7: Negatives
    checkExceptionCase("1,-2,3,-4", "negatives not allowed: -2,-4", calc, "Negative numbers '1,-2,3,-4'");
    checkExceptionCase("-5", "negatives not allowed: -5", calc, "Single negative '-5'");

    // Test 8: Custom single-character delimiter
    checkExpectedResult(3, calc.Add("//;\n1;2"), "Custom delimiter ';'");
    checkExpectedResult(6, calc.Add("//*\n1*2*3"), "Custom delimiter '*'");

    // Test 9: Custom multi-character delimiter
    checkExpectedResult(6, calc.Add("//[***]\n1***2***3"), "Custom multi-char delimiter '***'");
    checkExpectedResult(6, calc.Add("//[sep]\n1sep2sep3"), "Custom multi-char delimiter 'sep'");

    std::cout << "🎉 All tests passed successfully!" << std::endl;
    return 0;
}