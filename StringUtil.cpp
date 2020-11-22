//
// Created by asgarov1 on 11/18/2020.
//

#include "StringUtil.h"

std::string StringUtil::toLower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return input;
}

std::vector<std::string> StringUtil::splitText(const std::string& fileText, const std::string& delimeter) {
    std::vector <std::string> topics;
    size_t prev = 0, pos;
    do {
        pos = fileText.find(delimeter, prev);
        if (pos == std::string::npos) pos = fileText.length();
        std::string token = fileText.substr(prev, pos - prev);
        topics.push_back(token);
        prev = pos + delimeter.length();
    } while (pos < fileText.length() && prev < fileText.length());
    return topics;
}

std::string StringUtil::readNthLine(int n, std::string input) {
    for (int i = 1; i < n; ++i) {
        int endOfLine = input.find("\n", 0) + 1;
        input = input.substr(endOfLine);
    }
    if (input.find("\n", 0) != std::string::npos) {
        return input.substr(0, input.find("\n", 0));
    }
    return input;
}

std::string StringUtil::readFile(std::string path) {
        std::vector<std::string> lines;
        std::string line;
        std::ifstream userFile(path);
        if (userFile.is_open()) {
            while (getline(userFile, line)) {
                lines.push_back(line + LINE_BREAK);
            }
            userFile.close();
        }
        return std::accumulate(lines.begin(), lines.end(), std::string{});
}

std::string StringUtil::flattenToStringWithDelimeter(const std::vector<std::string> &lines, const std::string& delimeter) {
    std::string result;
    for (auto &line : lines) {
        if(equals(line, "")) {
            continue; //deleted line (message) is skipped
        }
        result += line + delimeter;
    }
    return result;
}

bool StringUtil::equals(const std::string &command, const char commandType[5]) {
    return !command.compare(commandType);
}
