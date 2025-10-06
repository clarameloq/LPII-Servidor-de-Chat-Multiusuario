#pragma once
#include "ClientHandler.h"
#include "tslog.h" 
#include <vector>
#include <memory>   
#include <mutex>
#include <thread>
#include <deque>

class ClientHandler;

class Server {
public:
    // construtor
    Server(int port, Logger& logger);

    void run();

    // transmite uma mensagem para todos os clientes
    void broadcast_message(const std::string& message, int sender_socket);

    Logger& getLogger();

    void remove_client(std::shared_ptr<ClientHandler> client);
    
private:
    // lida com a lógica de aceitar novas conexões em um loop
    void accept_connections();

    int server_socket_;
    Logger& logger_;

    // lista de todos os handlers de cliente conectados
    std::vector<std::shared_ptr<ClientHandler>> clients_;

    std::mutex clients_mutex_;

    // histórico de mensagens
    std::deque<std::string> message_history_;
    std::mutex history_mutex_;
    static const size_t MAX_HISTORY_SIZE = 10;
};