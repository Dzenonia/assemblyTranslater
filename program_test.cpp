#include "program.h"
#include "gtest/gtest.h"
#include "log.h"

TEST(Program, Test1) {
    standartLog->info("Console already");
    Log logFile("logs/program.txt", {"build", "process"});
    logFile.setFileLevel(spdlog::level::level_enum::trace);
    auto logBuild = logFile.get("build");
    logBuild->set_level(spdlog::level::trace);
    logBuild->info("Pre-start program on the input : {}", "input.txt");
    Program<32> program("input.txt", logBuild);
    auto logProcess = logFile.get("process");
    program.process(logProcess);
    EXPECT_EQ(program.outputData(), 281);
}

TEST(Program, Test2) {
    standartLog->info("Console already");
    Log logFile("logs/program2.txt", {"build", "process"});
    logFile.setFileLevel(spdlog::level::level_enum::trace);
    auto logBuild = logFile.get("build");
    logBuild->set_level(spdlog::level::trace);
    logBuild->info("Pre-start program on the input : {}", "input.txt");
    Program<32> program("input2.txt", logBuild);
    auto logProcess = logFile.get("process");
    program.process(logProcess);
    EXPECT_EQ(program.outputData(), 9);
}