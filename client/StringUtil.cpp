//
// Created by asgarov1 on 11/18/2020.
//

#include "StringUtil.h"


std::string StringUtil::toLower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(),
                          [](unsigned char c){ return std::tolower(c); });
    return input;
}
