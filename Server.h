#pragma once
#include "tslog.h" 
#include <vector>
#include <memory>   
#include <mutex>
#include <thread>

class ClientHandler;

class Server {
public:
    // construtor
    Server(int port, Logger& logger);

    void run();

    // transmite uma mensagem para todos os clientes
    void broadcast_message(const std::string& message, int sender_socket);

private:
    // lida com a lógica de aceitar novas conexões em um loop
    void accept_connections();

    int server_socket_;
    Logger& logger_;

    // lista de todos os handlers de cliente conectados
    std::vector<std::shared_ptr<ClientHandler>> clients_;

    std::mutex clients_mutex_;
};