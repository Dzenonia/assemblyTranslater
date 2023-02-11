#include <string>
#include <vector>

namespace Read {

    std::vector<std::string> readLines(const std::string &filename, char delimiter);

    std::vector<std::vector<std::string>> readTable(const std::string &filename, char delimiter, char end);
};