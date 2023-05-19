#!/usr/bin/env python3

import socket


HOST = '127.0.0.1' # localhost
PORT = 8888
bytes = "ola"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket_client:
    socket_client.connect((HOST, PORT))
    socket_client.sendall(str.encode(bytes))
