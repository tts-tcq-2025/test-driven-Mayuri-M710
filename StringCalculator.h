#ifndef STRINGCALCULATOR_H_
#define STRINGCALCULATOR_H_

#include <string>
#include <vector>

class StringCalculator {
 public:
    int Add(const std::string& numbers);

 private:
    std::string extractCustomDelimiter(const std::string& numbers,
                                       std::string& remainingNumbers);
    std::vector<int> splitNumbers(const std::string& input,
                                  const std::string& delimiter);
    void checkNegatives(const std::vector<int>& numbers);
    int sumIgnoringLarge(const std::vector<int>& numbers);
    std::string escapeRegex(const std::string& delimiter);
    std::string parseDelimiterFromBrackets(const std::string& delimiterLine);
    std::vector<int> collectNegatives(const std::vector<int>& numbers);
    std::string buildNegativeMessage(const std::vector<int>& negatives);
};

#endif  // STRINGCALCULATOR_H_
