#include "Server.h"
#include "ClientHandler.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <thread>
#include <memory>
#include <algorithm>

//contrutor do servidor
Server::Server(int port, Logger& logger) : logger_(logger){
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket_ < 0) {
        throw std::runtime_error("Erro ao criar socket");
    }
    logger_.write("Socket do servidor criado");

    //permite reutilizar o endereço
    int opt = 1;
    setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if(bind(server_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        throw std::runtime_error("Erro ao fazer bind do socket");
    }
    logger_.write("Socket fez bind na porta " + std::to_string(port));

    if (listen(server_socket_, 10) < 0) {
        throw std::runtime_error("Erro ao escutar no socket");
    }
    logger_.write("Servidor aguardando por conexões...");

}

//iniciar servidor
void Server::run(){
    accept_connections();
}

void Server::accept_connections(){
    while(true){
       int client_socket = accept(server_socket_, nullptr, nullptr);
       if (client_socket < 0){
        logger_.write("Erro ao aceitar conexão de cliente");
        continue;;
       }

       logger_.write("Nova conexão aceita! Socket do cliente: " + std::to_string(client_socket));

       auto handler = std::make_shared<ClientHandler>(client_socket, this);

       {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        clients_.push_back(handler);
       }

       std::thread client_thread(&ClientHandler::handle, handler);
       client_thread.detach();
    }
}

void Server::broadcast_message(const std::string& message, int sender_socket){
    std::lock_guard<std::mutex> lock(clients_mutex_);

    for (const auto& client : clients_){
        if(client->get_socket() != sender_socket){
            client->send_message(message);
        }
    }
}

Logger& Server::getLogger(){
    return logger_;
}