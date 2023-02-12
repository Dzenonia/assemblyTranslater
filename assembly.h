#pragma once

#include <map>
#include <string>
#include <vector>
#include <bitset>
#include "queue/queue.h"
#include "log.h"

class AssemblyData;

class BinaryOperation;

enum class TypeOperation;

class AssemblyData {
public:
    AssemblyData(const std::string &filename, BasicLogPtr logger = standartLog);

    BinaryOperation getNext(BasicLogPtr logger = standartLog);

    int &getValue(const std::string &name);

    bool isEmpty() const;

    int getAns();

private:

    std::map<std::string, int> values_;
    Queue<BinaryOperation> operations_;
    std::string unknownValue_;

};

class BinaryOperation {
public:
    BinaryOperation(const TypeOperation &operation, const std::string &leftOperand, const std::string &rightOperand);

    BinaryOperation(const std::string &operation, const std::string &leftOperand, const std::string &rightOperand);

    TypeOperation nameOperation() const;

    const std::string &leftOperand() const;

    const std::string &rightOperand() const;

    static TypeOperation whatOperation(const std::string &nameOperation);

private:
    TypeOperation nameOperation_;
    std::string leftOperand_;
    std::string rightOperand_;
};

enum class TypeOperation {
    mov,
    add,
    sub,
    mul,
    imul,
    div,
    idiv
};