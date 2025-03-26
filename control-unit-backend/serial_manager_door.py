# Importing Libraries 
import serial 
import time 
import random
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1) 

while(True):
    time.sleep(2)
    b = str(random.randint(0,64)).encode()
    arduino.write(b)
    print("bytes sent :D")
    print(b)
