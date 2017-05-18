import socket
import serial

SERIAL_PORT = ''

OK_FLAG = 'ok:'
KO_FLAG = 'ko:'
END_FLAG = 'end:'
STATUS_FLAG = 'status:'
CMD_FLAG = 'cmd:'
START_CMD = 'start'
DURATION_CMD = 'duration:'

READY_MSG = 'ready'

END_LINE = '\r\n'

ARDUINO_LABEL = 'Arduino => '
CONNECTION_LABEL = 'New connection: '

HOST = ''
PORT = 50997
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
for p in ports:
    if 'Arduino' in p.description or 'Genuino' in p.description:
        SERIAL_PORT = p.device
        print('Selected: ' + str(p.description))
if SERIAL_PORT.startswith('COM'):
    arduino = serial.Serial(SERIAL_PORT, 115200, timeout=.1)
    isReady = False
    while not isReady:
        initData = arduino.readline()
        if initData : 
            initString = str(initData,'utf-8')
            if initString.startswith(STATUS_FLAG):
                isReady = True
                print(ARDUINO_LABEL + initString)
    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        while True:
            conn, addr = s.accept()
            with conn:
                print(CONNECTION_LABEL, addr)
                recv = conn.recv(1024)
                durationStr = recv.decode('utf-8')
                print(durationStr)
                durationCmd = CMD_FLAG + durationStr
                arduino.write(durationCmd.encode())
                msg = ''
                while msg == '':
                    msg = str(arduino.readline(), 'utf-8')
                if msg.startswith(OK_FLAG):
                    startCmd = CMD_FLAG + START_CMD
                    arduino.write(startCmd.encode())
                    msg = str(arduino.readline(), 'utf-8')
                    while not msg.startswith(END_FLAG):   
                        print(msg, end = '')
                        msg = str(arduino.readline(), 'utf-8')
                    print(msg)
                else:
                    print("Something went wrong :(")
    arduino.close()
else:
    print('No Arduino/Genuino was detected. Please connect it to an USB port')
