import socket
HOST = 'localhost'    # The remote host
PORT = 50997              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
