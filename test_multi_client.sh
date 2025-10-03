#!/bin/bash

PORT=8080
HOST=localhost
NUM_CLIENTS=5

echo "Iniciando teste com $NUM_CLIENTS clientes..."

# loop para iniciar os clientes em segundo plano
for i in $(seq 1 $NUM_CLIENTS)
do
    (
        exec 3<>/dev/tcp/$HOST/$PORT
        echo "Ola, sou o cliente $i" >&3
        sleep 5
        exec 3<&-
    ) &
    CLIENT_PIDS+=($!) 
    sleep 0.1 
done

echo "$NUM_CLIENTS clientes conectados em background com PIDs: ${CLIENT_PIDS[*]}"
echo "Aguardando 6 segundos para observação..."
sleep 6

echo "Encerrando clientes..."
kill ${CLIENT_PIDS[*]}

echo "Teste concluído."