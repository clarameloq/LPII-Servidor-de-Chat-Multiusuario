#include "tslog.h"
#include <thread>
#include <vector>
#include <string>

void log_function(Logger& logger, int thread_id){
    for(int i = 0; i < 5; i++){
        std::string message = "Thread " + std::to_string(thread_id) + " escreveu a mensagem numero "+ std::to_string(i);
        logger.write(message);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main(){
    try{
        Logger logger("chat.log");
        std::vector<std::thread> threads;
        const int NUM_THREADS = 10;

        std::cout << "Iniciando teste com " << NUM_THREADS << "threads..." << std::endl;

        for (int i = 0; i < NUM_THREADS; ++i){
            threads.emplace_back(log_function, std::ref(logger), i);
        }

        for (auto& t : threads){
            t.join();
        }

        std::cout << "Teste concluido" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() <<std::endl;
        return 1;
    }

    return 0;

}