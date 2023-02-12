#include "assembly.h"
#include "read/read.h"
#include <stdexcept>
#include "log.h"

AssemblyData::AssemblyData(const std::string &filename, BasicLogPtr logger) {
    logger->info("Start read data from file: {} ", filename);
    auto data = Read::readTable(filename, '\n');
    int numberLine = 1;
    while (data[numberLine][0] != ".code") {
        const auto &line = data[numberLine];
        if (line[1] == "?") {
            unknownValue_ = line[0];
        } else {
            values_[line[0]] = std::stoi(line[1]);
        }
        ++numberLine;
    }
    ++numberLine;
    while (numberLine < data.size() - 1) {
        const auto &line = data[numberLine];
        operations_.push(BinaryOperation(line[0], (line[1]), (line[2])));
        ++numberLine;
    }
    logger->info("Reading is over");
}

BinaryOperation::BinaryOperation(const TypeOperation &operation, const std::string &leftOperand,
                                 const std::string &rightOperand) :
        nameOperation_(operation),
        leftOperand_(leftOperand),
        rightOperand_(rightOperand) {}

BinaryOperation::BinaryOperation(const std::string &operation, const std::string &leftOperand,
                                 const std::string &rightOperand) :
        nameOperation_(whatOperation(operation)),
        leftOperand_(leftOperand),
        rightOperand_(rightOperand) {}

TypeOperation BinaryOperation::whatOperation(const std::string &nameOperation) {
    if (nameOperation == "mov") {
        return TypeOperation::mov;
    }
    if (nameOperation == "add") {
        return TypeOperation::add;
    }
    if (nameOperation == "sub") {
        return TypeOperation::sub;
    }
    if (nameOperation == "mul") {
        return TypeOperation::mul;
    }
    if (nameOperation == "imul") {
        return TypeOperation::imul;
    }
    if (nameOperation == "div") {
        return TypeOperation::div;
    }
    if (nameOperation == "idiv") {
        return TypeOperation::idiv;
    }
    throw std::invalid_argument(nameOperation + " unknown operation");
}

TypeOperation BinaryOperation::nameOperation() const {
    return nameOperation_;
}

BinaryOperation AssemblyData::getNext(BasicLogPtr logger) {
    try {
        BinaryOperation result(operations_.front());
        logger->info("Get operation: {} {} {}", static_cast<int>(result.nameOperation()), result.leftOperand(),
                     result.rightOperand());
        operations_.pop();
        return result;
    } catch (...) {
        logger->critical("Cannot get next operation in function {}", "getNext");
        exit(1);
    }
}

int &AssemblyData::getValue(const std::string &name) {
    return values_[name];
}

bool AssemblyData::isEmpty() const {
    return operations_.isEmpty();
}

int AssemblyData::getAns() {
    return values_[unknownValue_];
}

const std::string &BinaryOperation::leftOperand() const {
    return leftOperand_;
}

const std::string &BinaryOperation::rightOperand() const {
    return rightOperand_;
}