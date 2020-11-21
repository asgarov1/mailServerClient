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
    static std::string readFile(std::string path);
    static std::vector<std::string> splitText(const std::string& input, std::string delimeter);
    static std::string flattenToStringWithDelimeter(const std::vector<std::string> &lines, std::string delimeter);
    static bool equals(const std::string &command, const char commandType[5]);
};


#endif //SOCKETS_STRINGUTIL_H