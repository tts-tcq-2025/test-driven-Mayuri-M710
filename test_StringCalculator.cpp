#include <cassert>
#include <iostream>
#include <stdexcept>
#include "StringCalculator.h"

int main() {
    StringCalculator calc;

    // Test 1: Empty string should return 0
    std::cout << "Testing empty string..." << std::endl;
    int result = calc.Add("");
    std::cout << "Result: " << result << std::endl;
    assert(result == 0);
    std::cout << "✓ Empty string test passed!" << std::endl;

    // Test 2: Single number should return that number
    std::cout << "\nTesting single number '1'..." << std::endl;
    result = calc.Add("1");
    std::cout << "Result: " << result << std::endl;
    assert(result == 1);
    std::cout << "✓ Single number test passed!" << std::endl;

    std::cout << "\nTesting single number '5'..." << std::endl;
    result = calc.Add("5");
    std::cout << "Result: " << result << std::endl;
    assert(result == 5);
    std::cout << "✓ Single number '5' test passed!" << std::endl;

    // Test 3: Two numbers separated by comma should return their sum
    std::cout << "\nTesting two numbers '1,2'..." << std::endl;
    result = calc.Add("1,2");
    std::cout << "Result: " << result << std::endl;
    assert(result == 3);
    std::cout << "✓ Two numbers '1,2' test passed!" << std::endl;

    // Test 4: Multiple numbers should return their sum
    std::cout << "\nTesting multiple numbers '1,2,3'..." << std::endl;
    result = calc.Add("1,2,3");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);
    std::cout << "✓ Multiple numbers '1,2,3' test passed!" << std::endl;

    std::cout << "\nTesting more numbers '1,2,3,4,5'..." << std::endl;
    result = calc.Add("1,2,3,4,5");
    std::cout << "Result: " << result << std::endl;
    assert(result == 15);
    std::cout << "✓ Multiple numbers '1,2,3,4,5' test passed!" << std::endl;

    // Test 5: New lines between numbers (instead of commas)
    std::cout << "\nTesting newlines '1\\n2,3'..." << std::endl;
    result = calc.Add("1\n2,3");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);
    std::cout << "✓ Newlines '1\\n2,3' test passed!" << std::endl;

    // Test 6: Ignore numbers greater than 1000
    std::cout << "\nTesting ignore numbers > 1000: '2,1001'..." << std::endl;
    result = calc.Add("2,1001");
    std::cout << "Result: " << result << std::endl;
    assert(result == 2);
    std::cout << "✓ Ignore numbers > 1000 test passed!" << std::endl;

    std::cout << "\nTesting multiple with large numbers: '1,2,1001,3,1500'..." << std::endl;
    result = calc.Add("1,2,1001,3,1500");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);  // Only 1+2+3=6, ignore 1001 and 1500
    std::cout << "✓ Multiple with large numbers test passed!" << std::endl;

    // Test 7: Handle negatives - should throw exception
    std::cout << "\nTesting negative numbers '1,-2,3,-4'..." << std::endl;
    try {
        result = calc.Add("1,-2,3,-4");
        // If we reach here, the test failed because no exception was thrown
        std::cout << "ERROR: Expected exception but got result: " << result << std::endl;
        assert(false);  // Force failure
    } catch (const std::exception& e) {
        std::string expectedMessage = "negatives not allowed: -2,-4";
        std::string actualMessage = e.what();
        std::cout << "Exception caught: " << actualMessage << std::endl;
        assert(actualMessage == expectedMessage);
        std::cout << "✓ Negative numbers exception test passed!" << std::endl;
    }

    std::cout << "\nTesting single negative '-5'..." << std::endl;
    try {
        result = calc.Add("-5");
        std::cout << "ERROR: Expected exception but got result: " << result << std::endl;
        assert(false);  // Force failure
    } catch (const std::exception& e) {
        std::string expectedMessage = "negatives not allowed: -5";
        std::string actualMessage = e.what();
        std::cout << "Exception caught: " << actualMessage << std::endl;
        assert(actualMessage == expectedMessage);
        std::cout << "✓ Single negative exception test passed!" << std::endl;
    }

    // Test 8: Custom single-character delimiter
    std::cout << "\nTesting custom delimiter '//;\\n1;2'..." << std::endl;
    result = calc.Add("//;\n1;2");
    std::cout << "Result: " << result << std::endl;
    assert(result == 3);
    std::cout << "✓ Custom delimiter ';' test passed!" << std::endl;

    std::cout << "\nTesting custom delimiter '//*\\n1*2*3'..." << std::endl;
    result = calc.Add("//*\n1*2*3");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);
    std::cout << "✓ Custom delimiter '*' test passed!" << std::endl;

    // Test 9: Custom multi-character delimiter
    std::cout << "\nTesting custom multi-char delimiter '//[***]\\n1***2***3'..." << std::endl;
    result = calc.Add("//[***]\n1***2***3");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);
    std::cout << "✓ Custom multi-char delimiter '***' test passed!" << std::endl;

    std::cout << "\nTesting custom multi-char delimiter '//[sep]\\n1sep2sep3'..." << std::endl;
    result = calc.Add("//[sep]\n1sep2sep3");
    std::cout << "Result: " << result << std::endl;
    assert(result == 6);
    std::cout << "✓ Custom multi-char delimiter 'sep' test passed!" << std::endl;

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
