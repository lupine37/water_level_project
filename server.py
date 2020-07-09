import socket

HOST = '192.168.1.145'
PORT = 8888

lsock = socket.socket()
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
lsock.bind((HOST, PORT))
lsock.listen(5)
print('listening on', (HOST, PORT))

while True:
    c, addr = lsock.accept()
    print('Got connection from', addr)
    while True:
        recv_data = c.recv(1024).decode('utf-8')
        if not recv_data:
            break
        if recv_data != ' ':
            print(recv_data)
    c.close()