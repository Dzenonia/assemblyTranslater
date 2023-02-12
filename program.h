#pragma once

#include "assembly.h"
#include "command.h"
#include "log.h"

template<int BITS>
class Program {
public:
    Program(const std::string &filename, BasicLogPtr logger = standartLog);

    void process(BasicLogPtr logger = standartLog);

    int outputData();

private:
    AssemblyData inputData_;

};

template<int BITS>
Program<BITS>::Program(const std::string &filename, BasicLogPtr logger) : inputData_(filename, logger) {
    logger->info("Program is built");
}

template<int BITS>
void Program<BITS>::process(BasicLogPtr logger) {
    logger->info("Start doing operations");
    while (!inputData_.isEmpty()) {
        auto needToDo(inputData_.getNext(logger));
        Command<BITS>::command(needToDo.nameOperation(), inputData_.getValue(needToDo.leftOperand()),
                               inputData_.getValue(needToDo.rightOperand()), logger);
    }
}

template<int BITS>
int Program<BITS>::outputData() {
    return inputData_.getAns();
}