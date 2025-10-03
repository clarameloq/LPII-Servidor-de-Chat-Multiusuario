#include "tslog.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

Logger::Logger(const std::string& filename){
    log_file_.open(filename,std::ios_base::app);
    if (!log_file_.is_open()){
        throw std::runtime_error("Erro ao abrir arquivo de log");
    }
}

Logger::~Logger(){
    if (log_file_.is_open()){
        log_file_.close();
    }
}

void Logger::write(const std::string& message){
    std::lock_guard<std::mutex> lock(mtx_);

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << " - " << message;

    log_file_ << ss.str() << std::endl;
    std::cout << ss.str() << std::endl;
}
