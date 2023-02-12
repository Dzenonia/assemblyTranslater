#include "gtest/gtest.h"
#include "log.h"

TEST(Log, check) {
    auto myLogger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    myLogger->set_level(spdlog::level::trace);
    myLogger->debug("check debug with args {} ", "its arg");
    myLogger->trace("check trace");
}