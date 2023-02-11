#pragma once
#include <map>
#include <string>

class assembly {
public:
    assembly(const std::string& filename);

    int getAns();
private:
    std::map<std::string, int> values;
    std::string result;

};