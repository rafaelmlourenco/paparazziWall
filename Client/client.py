import sys
import socket
HOST = 'localhost'    # The remote host
PORT = 50997          # The same port as used by the server

flashDuration = 10000
argsLength = len(sys.argv)
if argsLength > 1:
    i = 0
    while i < argsLength:
        if sys.argv[i] == "-t":
            if i+1 < argsLength:
                i = i+1
                flashDuration = int(sys.argv[i])
            else:
                print("-t option requires a duration (milliseconds)")
        i = i+1

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(bytes("time:" + str(flashDuration)))