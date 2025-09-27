#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    explicit Logger(const std::string& filename);
    ~Logger();

    void write(const std::string& message);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::ofstream log_file_; // Arquivo de log
    std::mutex mtx_;

};
