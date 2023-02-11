#include "assembly.h"
#include "read.h"
#include <stdexcept>

AssemblyData::AssemblyData(const std::string &filename) {
    auto data = Read::readTable(filename, '\n');
    int numberLine = 1;
    while (data[numberLine][0] != ".code") {
        auto &line = data[numberLine];
        if (line[1] == "?") {
            unknownValue_ = line[0];
        } else {
            values_[line[0]] = std::stoi(line[1]);
        }
        ++numberLine;
    }
    while (numberLine < data.size() - 1) {
        auto &line = data[numberLine];
        operations_.push_back(BinaryOperation(line[0], (line[1]), (line[2])));
    }
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