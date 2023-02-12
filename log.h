#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <map>

using BasicLogPtr = std::shared_ptr<spdlog::logger>;
using FileLogPtr = std::shared_ptr<spdlog::sinks::daily_file_sink_mt>;
extern BasicLogPtr standartLog;

class Log;

class Log {
public:
    Log(const std::string &filename, const std::initializer_list<std::string> &chronoLog = {});

    BasicLogPtr get(const std::string &nameLog);

    void clear();

    void setFileLevel(spdlog::level::level_enum level);

    void addLog(const std::string &name);

private:

    class BasicLog;

    FileLogPtr logFile_;
    std::map<std::string, BasicLog> subLog_;

    class BasicLog {
    public:
        BasicLog() = default;

        BasicLog(const std::string &name, const FileLogPtr &logFile);

        BasicLogPtr basicLogPtr_;
    };
};