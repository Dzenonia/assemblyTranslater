#pragma once

#include "assembly.h"
#include <stdexcept>

template<int BITS>
class Command {
public:

    static void command(TypeOperation name, int &lhs, int rhs, BasicLogPtr logger = standartLog);

    static void mov(int &lhs, int rhs, BasicLogPtr logger = standartLog);

    static void add(int &lhs, int rhs, BasicLogPtr logger = standartLog);

    static void sub(int &lhs, int rhs, BasicLogPtr logger = standartLog);

    static void umul(int &lhs, int rhs, BasicLogPtr logger = standartLog);

    static void mul(int &lhs, int rhs, BasicLogPtr logger = standartLog);

//
//    static void imul(int &lhs, int rhs);
//
//    static void div(int &lhs, int rhs);
//
//    static void idiv(const int &lhs, int rhs);
};

template<int BITS>
void Command<BITS>::mov(int &lhs, int rhs, BasicLogPtr logger) {
    logger->info("Start do operation {}", "mov");
    lhs = rhs;
    logger->info("Operation {} is done", "mov");
}

template<int BITS>
void Command<BITS>::add(int &lhs, int rhs, BasicLogPtr logger) {
    logger->info("Start do operation {}", "add");
    std::bitset<BITS> lhsBits(lhs);
    std::bitset<BITS> rhsBits(rhs);
    int plus = 0;

    for (int i = 0; i < BITS; ++i) {
        int last = lhsBits[i];
        lhsBits[i] = ((lhsBits[i] + rhsBits[i] + plus) & 1) == 1;
        plus = (last + rhsBits[i] + plus) >> 1;
    }

    lhs = lhsBits.to_ullong();
    logger->info("Operation {} is done", "add");
}

template<int BITS>
void Command<BITS>::sub(int &lhs, int rhs, BasicLogPtr logger) {
    logger->info("Start do operation {}", "sub");
    Command<BITS>::add(lhs, -rhs, BasicLogPtr());
    logger->info("Operation {} is done", "sub");
}

template<int BITS>
void Command<BITS>::mul(int &lhs, int rhs, BasicLogPtr logger) {
    logger->info("Start do operation {}", "mul");
    int sgn = ((lhs < 0) ^ (rhs < 0) ? -1 : 1);
    if (lhs < 0) {
        lhs = -lhs;
    }
    logger->trace("Using imul is norm?");
    umul(lhs, abs(rhs), logger);
    lhs *= sgn;
    logger->info("Operation {} is done", "mul");
}


template<int BITS>
void Command<BITS>::umul(int &lhs, int rhs, BasicLogPtr logger) {
    logger->info("Start do operation {}", "imul");
    if (lhs < 0 || rhs < 0) {
        logger->error(std::to_string(lhs) + " or " + std::to_string(rhs) + " is negative number");
        throw std::invalid_argument(std::to_string(lhs) + " or " + std::to_string(rhs) + " is negative number");
    }
    std::bitset<BITS> lhsBits(lhs);
    std::bitset<BITS> rhsBits(rhs);

    std::vector<int> result(2 * BITS - 1);
    for (int i = 0; i < BITS; ++i) {
        for (int j = 0; j < BITS; ++j) {
            result[i + j] += lhsBits[i] * rhsBits[j];
        }
    }
    int lastAdd = 0;
    std::bitset<BITS> answer;
    for (int i = 0; i < BITS; ++i) {
        int value = result[i];
        value += lastAdd;
        lastAdd = value >> 1;
        value &= 1;
        answer[i] = value;
    }
    if (lastAdd > 0) {
        logger->error(
                "Multiply " + std::to_string(lhs) + " " + std::to_string(rhs) + " is more than" + std::to_string(BITS) +
                "-bit");
        throw std::out_of_range(
                "Multiply " + std::to_string(lhs) + " " + std::to_string(rhs) + " is more than" + std::to_string(BITS) +
                "-bit");
    }
    lhs = answer.to_ullong();
    logger->info("Operation {} is done", "imul");
}

template<int BITS>
void Command<BITS>::command(TypeOperation name, int &lhs, int rhs, BasicLogPtr logger) {
    switch (name) {
        case TypeOperation::mov:
            Command::mov(lhs, rhs, logger);
            break;
        case TypeOperation::add:
            Command::add(lhs, rhs, logger);
            break;
        case TypeOperation::sub:
            Command::sub(lhs, rhs, logger);
            break;
        case TypeOperation::mul:
            Command::mul(lhs, rhs, logger);
            break;
        default:
            logger->error("{} dont find", static_cast<int>(name));
            throw std::invalid_argument("Unknown command");
    }
}

