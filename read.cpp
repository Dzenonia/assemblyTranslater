#include <fstream>
#include "read.h"

std::vector<std::vector<std::string>> Read::readTable(const std::string &filename, char delimiter, char end) {
    std::vector<std::string> lines = readLines(filename, end);
    std::vector<std::vector<std::string>> result(lines.size());
    int nowPosLine = 0;
    for (const auto &line: lines) {
        std::string nowStr;
        for (const auto &sym: line) {
            if (sym == delimiter) {
                if (!nowStr.empty()) {
                    result[nowPosLine].push_back(std::move(nowStr));
                    nowStr = "";
                }
                continue;
            }
            nowStr += sym;
        }
        if (!nowStr.empty()) {
            result[nowPosLine].push_back(std::move(nowStr));
            nowStr = "";
        }
        ++nowPosLine;
    }
    return result;
}

std::vector<std::string> Read::readLines(const std::string &filename, char delimiter) {
    std::ifstream in(filename);
    std::vector<std::string> result;

    while (!in.eof()) {
        std::string now;
        std::getline(in, now, delimiter);
        result.push_back(std::move(now));
    }

    return result;
}
