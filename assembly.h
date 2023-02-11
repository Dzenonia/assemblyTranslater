#pragma once

#include <map>
#include <string>
#include <vector>
#include <bitset>

class AssemblyData;

class BinaryOperation;

enum class TypeOperation;

class AssemblyData {
public:
    AssemblyData(const std::string &filename);

private:

    std::map<std::string, int> values_;
    std::vector<BinaryOperation> operations_;
    std::string unknownValue_;

};

class BinaryOperation {
public:
    BinaryOperation(const TypeOperation &operation, const std::string &leftOperand, const std::string &rightOperand);

    BinaryOperation(const std::string &operation, const std::string &leftOperand, const std::string &rightOperand);

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