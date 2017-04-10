import serial
import socket
import time
SERIAL_PORT = 'COM3'
READY_MSG = 'Arduino is ready!\r\n'
START_FLASHING_MSG = b'Start Flashing'
ARDUINO_LABEL = 'Arduino: '
CONNECTION_LABEL = 'New connection: '
HOST = ''
PORT = 50997
arduino = serial.Serial(SERIAL_PORT, 9600, timeout=.1)
isReady = False
while not isReady:
    initData = arduino.readline()
    if initData : 
        initString = str(initData,'utf-8')
        if initString == READY_MSG:
            isReady = True
            print(ARDUINO_LABEL + initString)
with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        with conn:
            print(CONNECTION_LABEL, addr)
            arduino.write(START_FLASHING_MSG)
arduino.close()

