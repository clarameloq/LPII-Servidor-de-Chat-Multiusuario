# LPII - Servidor de Chat Multiusuário (TCP)

Este é o projeto final para a disciplina de Programação Concorrente, que implementa um servidor de chat TCP concorrente em C++, capaz de atender múltiplos clientes simultaneamente.

## Funcionalidades

* Servidor TCP que atende múltiplos clientes em threads dedicadas.
* Broadcast de mensagens para todos os clientes conectados.
* Histórico das últimas 10 mensagens é enviado para novos clientes.
* Remoção segura de clientes da lista de ativos após a desconexão.
* Logging concorrente de eventos importantes (conexões, mensagens, desconexões).

## Como Compilar e Executar

**1. Compilar o Projeto**

Navegue até a pasta raiz do projeto no terminal e execute o comando `make`:

```bash
make
./chat_server

* Conectar Clientes:
```bash
telnet localhost 8080
