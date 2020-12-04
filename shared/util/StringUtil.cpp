//
// Created by asgarov1 on 11/18/2020.
//

#include "StringUtil.h"

/**
 * returns to lower case copy of input
 * @param input
 * @return
 */
std::string StringUtil::toLower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return input;
}

/**
 * splits string using delimiter into vector of strings
 * in this program useful to break down a text file into messages and then extract these via index
 * @param fileText
 * @param delimiter
 * @return
 */
std::vector<std::string> StringUtil::splitText(const std::string &fileText, const std::string &delimiter) {
    std::vector<std::string> topics;
    size_t prev = 0, pos;
    do {
        pos = fileText.find(delimiter, prev);
        if (pos == std::string::npos) pos = fileText.length();
        std::string token = fileText.substr(prev, pos - prev);
        topics.push_back(token);
        prev = pos + delimiter.length();
    } while (pos < fileText.length() && prev < fileText.length());
    return topics;
}

/**
 * reads passed in number of line
 * @param n
 * @param input
 * @return
 */
std::string StringUtil::readNthLine(int n, std::string input) {
    for (int i = 1; i < n; ++i) {
        int endOfLine = (int) input.find('\n', 0) + 1;
        input = input.substr(endOfLine);
    }
    if (input.find('\n', 0) != std::string::npos) {
        return input.substr(0, input.find('\n', 0));
    }
    return input;
}

/**
 * Reads content of file located at path
 * @param path
 * @return
 */
std::string StringUtil::readFile(const std::string &path) {
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

/**
 * Flatters a vector of lines to one string
 * @param lines
 * @param delimiter
 * @return
 */
std::string
StringUtil::flattenToStringWithDelimiter(const std::vector<std::string> &lines, const std::string &delimiter) {
    std::string result;
    for (auto &line : lines) {
        if (line.empty()) {
            continue; //deleted line (message) is skipped
        }
        result += line + delimiter;
    }
    return result;
}

/**
 * checks for number of occurrences of a pattern in a string
 * in this program used to count number of lines in a string by counting line breaks
 * @param source
 * @param pattern
 * @return
 */
int StringUtil::numberOfOccurrences(const std::string &source, const std::string &pattern) {
    int occurrences = 0;
    std::string::size_type pos = 0;
    while ((pos = source.find(pattern, pos)) != std::string::npos) {
        ++occurrences;
        pos += pattern.length();
    }
    return occurrences;
}

/**
 * Checks if received input is a number to avoid getting exceptions if it is not
 * @param input
 * @return
 */
bool StringUtil::isNumber(const std::string &input) {
    if (input.empty() || ((!isdigit(input[0])) && (input[0] != '-') && (input[0] != '+'))) {
        return false;
    }
    char *p;
    strtol(input.c_str(), &p, 10);
    return (*p == 0);
}
