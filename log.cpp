#include "log.h"

Log::Log(const std::string &filename, const std::initializer_list<std::string> &chronoLog) :
        logFile_(std::make_shared<spdlog::sinks::daily_file_sink_mt>(filename, 23, 59)) {
    for (const auto &logName: chronoLog) {
        subLog_.insert({logName, BasicLog(logName, logFile_)});
    }
}

BasicLogPtr Log::get(const std::string &nameLog) {
    if (subLog_.find(nameLog) == subLog_.end()) {
        throw std::invalid_argument("Unknown basic log: " + nameLog);
    }
    return subLog_[nameLog].basicLogPtr_;
}

void Log::setFileLevel(spdlog::level::level_enum level) {
    logFile_->set_level(level);
}

void Log::clear() {
    logFile_->flush();
}

void Log::addLog(const std::string &name) {
    subLog_[name] = BasicLog(name, logFile_);
}

BasicLogPtr standartLog = spdlog::stderr_color_mt("console");

Log::BasicLog::BasicLog(const std::string &name, const FileLogPtr &logFile) :
        basicLogPtr_(std::make_shared<spdlog::logger>(name, logFile)) {}