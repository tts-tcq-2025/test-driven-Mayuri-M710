#include "StringCalculator.h"
#include <regex>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

// Main Add method

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string remainingNumbers;
    std::string delimiter = extractCustomDelimiter(numbers, remainingNumbers);

    std::vector<int> parsedNumbers = splitNumbers(remainingNumbers, delimiter);

    checkNegatives(parsedNumbers);

    return sumIgnoringLarge(parsedNumbers);
}

// Extract custom delimiter

std::string StringCalculator::extractCustomDelimiter(
    const std::string& numbers, std::string& remainingNumbers) {
    if (numbers.rfind("//", 0) != 0) {
        remainingNumbers = numbers;
        return ",";  // default delimiter
    }

    size_t newlinePos = numbers.find('\n');
    std::string delimiterLine = numbers.substr(2, newlinePos - 2);
    remainingNumbers = numbers.substr(newlinePos + 1);

    return parseDelimiterFromBrackets(delimiterLine);
}

std::string StringCalculator::parseDelimiterFromBrackets(
    const std::string& delimiterLine) {
    if (delimiterLine.size() >= 2 && delimiterLine.front() == '[' &&
        delimiterLine.back() == ']') {
        return delimiterLine.substr(1, delimiterLine.size() - 2);
    }
    return delimiterLine;
}

// Split numbers using regex

std::vector<int> StringCalculator::splitNumbers(
    const std::string& input, const std::string& delimiter) {
    std::string regexPattern = (escapeRegex(delimiter) + "|\n|,");
    std::regex regexDelimiter(regexPattern);

    std::sregex_token_iterator it(input.begin(), input.end(),
                                  regexDelimiter, -1);
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
            escaped.push_back('\\');  // prepend backslash
        }
        escaped.push_back(c);
    }
    return escaped;
}

// Check for negatives numbers

void StringCalculator::checkNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives = collectNegatives(numbers);
    if (!negatives.empty()) {
        std::string msg = buildNegativeMessage(negatives);
        throw std::runtime_error(msg);
    }
}

std::vector<int> StringCalculator::collectNegatives(
    const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int n : numbers) {
        if (n < 0) negatives.push_back(n);
    }
    return negatives;
}

std::string StringCalculator::buildNegativeMessage(
    const std::vector<int>& negatives) {
    std::string msg = "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i > 0) msg += ",";
        msg += std::to_string(negatives[i]);
    }
    return msg;
}

// Ignore numbers above 1000 and Sum the remaining

int StringCalculator::sumIgnoringLarge(const std::vector<int>& numbers) {
    int sum = 0;
    for (int n : numbers) {
        if (n <= 1000) sum += n;
    }
    return sum;
}