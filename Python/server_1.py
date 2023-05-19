#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # localhost
PORT = 8888        # Port selecionado
flag = True;

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((HOST, PORT))
    server_socket.listen()
    while (flag):
        print('I am the server')
        conn, addr = server_socket.accept()
        with conn:
            print('Connected by', addr)
            data = conn.recv(1024)
            data_str = data.decode()
            print(data_str)
            if (data_str[0:4] == 'over'):
                flag = False
