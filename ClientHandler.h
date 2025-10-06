#pragma once
#include <string>
#include <thread>
#include <memory>

class Server;

class ClientHandler : public std::enable_shared_from_this<ClientHandler>{
public:
    // construtor
    ClientHandler(int client_socket, Server* server);

    void handle();

    // envia uma mensagem para o cliente
    void send_message(const std::string& message);

    int get_socket() const;

private:
    int client_socket_;
    Server* server_;
    std::string client_name_;
};