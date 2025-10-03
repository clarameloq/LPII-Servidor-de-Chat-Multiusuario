#!/bin/bash

NUM_CLIENTS=3
PORT=8080
HOST=localhost

echo "Iniciando $NUM_CLIENTS clientes em novas janelas de terminal..."
echo "Cada janela irá se conectar ao chat. Você poderá digitar em cada uma delas."

for i in $(seq 1 $NUM_CLIENTS)
do
    gnome-terminal --title="Cliente $i" -- bash -c "echo '--- CONECTADO AO CHAT COMO CLIENTE $i ---'; echo; telnet $HOST $PORT; echo; echo '--- DESCONECTADO ---'; echo 'Pressione ENTER para fechar esta janela.'; read" &
done

echo "$NUM_CLIENTS janelas de cliente foram abertas."