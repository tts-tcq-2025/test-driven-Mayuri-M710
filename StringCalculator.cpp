#include "StringCalculator.h"
#include <regex>
#include <stdexcept>
#include <sstream>

// ----------------------------
// Main Add method
// ----------------------------
int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string remainingNumbers;
    std::string delimiter = extractCustomDelimiter(numbers, remainingNumbers);

    std::vector<int> parsedNumbers = splitNumbers(remainingNumbers, delimiter);

    checkNegatives(parsedNumbers);

    return sumIgnoringLarge(parsedNumbers);
}

// ----------------------------
// Extract custom delimiter
// ----------------------------
std::string StringCalculator::extractCustomDelimiter(const std::string& numbers, std::string& remainingNumbers) {
    if (numbers.rfind("//", 0) != 0) {
        remainingNumbers = numbers;
        return ","; // default delimiter
    }

    size_t newlinePos = numbers.find('\n');
    std::string delimiterLine = numbers.substr(2, newlinePos - 2);
    remainingNumbers = numbers.substr(newlinePos + 1);

    if (delimiterLine.size() >= 2 && delimiterLine.front() == '[' && delimiterLine.back() == ']') {
        return delimiterLine.substr(1, delimiterLine.size() - 2);
    }
    return delimiterLine;
}

// ----------------------------
// Split numbers using regex
// ----------------------------
std::vector<int> StringCalculator::splitNumbers(const std::string& input, const std::string& delimiter) {
    std::string regexPattern = (escapeRegex(delimiter) + "|\n|,");
    std::regex regexDelimiter(regexPattern);

    std::sregex_token_iterator it(input.begin(), input.end(), regexDelimiter, -1);
    std::sregex_token_iterator end;

    std::vector<int> values;
    for (; it != end; ++it) {
        if (!it->str().empty()) {
            values.push_back(std::stoi(it->str()));
        }
    }
    return values;
}

std::string StringCalculator::escapeRegex(const std::string& delimiter) {
    static const std::string regexSpecials = R"(\.^$|()[]*+?{})";
    std::string escaped;
    for (char c : delimiter) {
        if (regexSpecials.find(c) != std::string::npos) {
            escaped.push_back('\\'); // prepend backslash
        }
        escaped.push_back(c);
    }
    return escaped;
}
// ----------------------------
// Check for negatives
// ----------------------------
void StringCalculator::checkNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int n : numbers) {
        if (n < 0) negatives.push_back(n);
    }

    if (!negatives.empty()) {
        std::string msg = "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) msg += ",";
            msg += std::to_string(negatives[i]);
        }
        throw std::runtime_error(msg);
    }
}

// ----------------------------
// Sum ignoring numbers > 1000
// ----------------------------
int StringCalculator::sumIgnoringLarge(const std::vector<int>& numbers) {
    int sum = 0;
    for (int n : numbers) {
        if (n <= 1000) sum += n;
    }
    return sum;
}