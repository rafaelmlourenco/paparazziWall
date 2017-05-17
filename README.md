# paparazziWall

This repository has all the necessary files to randomly trigger 7 flashes and a camera using an Arduino/Genuino board.

## Requirements
+ Arduino/Genuino Board
+ Python 3 (https://www.python.org/)
+ PySerial (https://github.com/pyserial/) 
  + Install command: `pip install pyserial`
+ 8 Opto-couplers
+ 8 Resistors

## Example usage
1. Connect the Arduino board and the flashes (use the pinout scheme as reference) to the computer using an USB cable. 
2. Upload the Arduino program (under Arduino folder) to the board, and you are ready to go.
3. Start up the Server-side Python script (server.py)
4. Whenever you're ready, start the Client-side Python script (client.py) and it will start to flash randomly.

### NOTES:
You can use a Photobooth camera that has trigger settings to start the client-side script (e.g. Social Booth)  
