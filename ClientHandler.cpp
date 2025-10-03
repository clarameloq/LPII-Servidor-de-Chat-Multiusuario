#include "ClientHandler.h"
#include "Server.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <string>

ClientHandler::ClientHandler(int client_socket, Server* server)
    : client_socket_(client_socket), server_(server){}

void ClientHandler::handle(){
    char buffer[4096];

    while (true){
        int bytes_received = recv(client_socket_, buffer, sizeof(buffer), 0);

        if(bytes_received <= 0){
            std::cout << "Cliente (socket " << client_socket_ << ") desconectado" << std::endl;
            close(client_socket_);
            return;
        }

        std::string message(buffer, bytes_received);
        server_->getLogger().write("Recebido do socket " + std::to_string(client_socket_) + ": " + message);

        server_->broadcast_message(message, client_socket_);
    }
}

int ClientHandler::get_socket() const{
    return client_socket_;
}

void ClientHandler::send_message(const std::string& message){
    send(client_socket_, message.c_str(), message.length(), 0);
}

