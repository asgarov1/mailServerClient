//
// Created by asgarov1 on 11/18/2020.
//

#ifndef SOCKETS_STRINGUTIL_H
#define SOCKETS_STRINGUTIL_H


#include <string>
#include <vector>
#include <filesystem>
#include <numeric>
#include <fstream>
#include <iostream>

#define LINE_BREAK "\n"
#define MESSAGE_END ".\n"

class StringUtil {
public:
    static std::string toLower(std::string input);
    static std::string readNthLine(int n, std::string input);
    static std::string readFile(const std::string& path);
    static std::vector<std::string> splitText(const std::string& input, const std::string& delimiter);
    static std::string flattenToStringWithDelimiter(const std::vector<std::string> &lines, const std::string& delimiter);
    static int numberOfOccurrences(const std::string& source, const std::string& pattern);
    static bool isNumber(const std::string &input);
};


#endif //SOCKETS_STRINGUTIL_H
