#include "Server.h"
#include "tslog.h"
#include <iostream>

const int PORT = 8080;

int main(){
    try {
        Logger logger("chat_server.log");
        Server server(PORT, logger);
        server.run();
    } catch (const std::exception& e){
        std::cerr <<"Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;

}