#pragma once

#include <string>
#include <vector>
#include <set>

class Read;

class Read {
public:
    static std::vector<std::string> readLines(const std::string &filename, char end);

    static std::vector<std::vector<std::string>> readTable(const std::string &filename, char end);
};