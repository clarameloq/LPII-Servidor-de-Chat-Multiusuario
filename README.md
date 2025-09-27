```mermaid
sequenceDiagram
    participant Cliente A
    participant Cliente B
    participant Servidor
    participant Thread Handler A
    participant Thread Handler B

    Servidor->>Servidor: Inicia e escuta na porta TCP

    Cliente A->>Servidor: Tenta se conectar
    Servidor->>Servidor: Aceita conexão de A
    Servidor->>Thread Handler A: Cria handler para A em nova thread

    activate Thread Handler A
    Thread Handler A->>Thread Handler A: Inicia loop de escuta de mensagens

    Cliente B->>Servidor: Tenta se conectar
    Servidor->>Servidor: Aceita conexão de B
    Servidor->>Thread Handler B: Cria handler para B em nova thread

    activate Thread Handler B
    Thread Handler B->>Thread Handler B: Inicia loop de escuta de mensagens

    Cliente A->>Thread Handler A: Envia mensagem: "Olá!"
    Thread Handler A->>Servidor: Chama broadcast_message("Olá!", A)

    activate Servidor
    note over Servidor: Trava o mutex da lista de clientes
    Servidor->>Thread Handler B: Repassa a mensagem
    note over Servidor: Destrava o mutex
    deactivate Servidor

    Thread Handler B->>Cliente B: Entrega a mensagem: "Olá!"
