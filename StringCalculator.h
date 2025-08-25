#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::string extractCustomDelimiter(const std::string& numbers, std::string& remainingNumbers);
    std::vector<int> splitNumbers(const std::string& input, const std::string& delimiter);
    void checkNegatives(const std::vector<int>& numbers);
    int sumIgnoringLarge(const std::vector<int>& numbers);
    std::string escapeRegex(const std::string& delimiter);
};

#endif // STRINGCALCULATOR_H
