#include <fstream>
#include "read.h"
#include <iostream>
#include <sstream>

std::vector<std::vector<std::string>>
Read::readTable(const std::string &filename, char end) {
    std::ifstream in(filename);
    std::vector<std::vector<std::string>> result;
    while (!in.eof()) {
        std::vector<std::string> vecStrings;
        std::string temp;
        std::getline(in, temp, end);
        std::stringstream helper;
        helper << temp;
        while (!helper.eof()) {
            std::string nowStr;
            helper >> nowStr;
            vecStrings.push_back(std::move(nowStr));
        }
        result.push_back(vecStrings);
    }
    return result;
}

std::vector<std::string> Read::readLines(const std::string &filename, char end) {
    std::ifstream in(filename);
    std::vector<std::string> result;
    while (!in.eof()) {
        std::string now;
        std::getline(in, now, end);
        result.push_back(std::move(now));
    }
    return result;
}
