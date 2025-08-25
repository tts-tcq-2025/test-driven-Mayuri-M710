#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::string extractCustomDelimiter(const std::string& numbers, std::string& remainingNumbers);
    std::string replaceDelimiters(const std::string& numbers, const std::string& delimiter);
    std::vector<int> parseNumbers(const std::string& numbers);
    void validateNegatives(const std::vector<int>& numbers);
    int calculateSum(const std::vector<int>& numbers);
};
