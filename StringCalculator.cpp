#include "StringCalculator.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }
    
    std::string remainingNumbers;
    std::string delimiter = extractCustomDelimiter(numbers, remainingNumbers);
    std::string processedNumbers = replaceDelimiters(remainingNumbers, delimiter);
    std::vector<int> parsedNumbers = parseNumbers(processedNumbers);
    validateNegatives(parsedNumbers);
    return calculateSum(parsedNumbers);
}

std::string StringCalculator::extractCustomDelimiter(const std::string& numbers, std::string& remainingNumbers) {
    if (numbers.length() >= 4 && numbers.substr(0, 2) == "//") {
        size_t newlinePos = numbers.find('\n');
        if (newlinePos != std::string::npos) {
            std::string delimiterLine = numbers.substr(2, newlinePos - 2);
            remainingNumbers = numbers.substr(newlinePos + 1);
            
            // Check if delimiter is in brackets: [delimiter]
            if (delimiterLine.length() >= 2 && delimiterLine[0] == '[' && delimiterLine.back() == ']') {
                return delimiterLine.substr(1, delimiterLine.length() - 2);
            }
            return delimiterLine;
        }
    }
    remainingNumbers = numbers;
    return ",";
}

std::string StringCalculator::replaceDelimiters(const std::string& numbers, const std::string& delimiter) {
    std::string result = numbers;
    
    // Replace custom delimiter with comma
    if (delimiter != ",") {
        size_t pos = 0;
        while ((pos = result.find(delimiter, pos)) != std::string::npos) {
            result.replace(pos, delimiter.length(), ",");
            pos += 1;
        }
    }
    
    // Replace newlines with commas
    std::replace(result.begin(), result.end(), '\n', ',');
    return result;
}

std::vector<int> StringCalculator::parseNumbers(const std::string& numbers) {
    std::vector<int> result;
    std::stringstream ss(numbers);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {
            result.push_back(std::stoi(token));
        }
    }
    return result;
}

void StringCalculator::validateNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int number : numbers) {
        if (number < 0) {
            negatives.push_back(number);
        }
    }
    
    if (!negatives.empty()) {
        std::string message = "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) message += ",";
            message += std::to_string(negatives[i]);
        }
        throw std::runtime_error(message);
    }
}

int StringCalculator::calculateSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (int number : numbers) {
        if (number <= 1000) {
            sum += number;
        }
    }
    return sum;
}
