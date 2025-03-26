# Importing Libraries 
import serial 
import time 
import random
from enum import Enum


class State(Enum):
    NORMAL = 1
    HOT = 2
    TOO_HOT = 3

class ArduinoCommunicator:
    def __init__(self,arduino:serial.Serial):
        self.arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1) 
        self.manual_mode = False
        self.current_rotation = 0
        self.command = b""
        self.system_state = State.NORMAL
        self.t1 = 10
        self.t2 = 20
    
    def update_state(self,temperature):
        if temperature< self.t1 :
            return State.NORMAL
        if temperature <= self.t2:
            return State.HOT
        return State.TOO_HOT

    def update_rotation(self,temperature):
        state = self.update_state()
        if(state==State.NORMAL):
            return 0
        if state==State.HOT:
            return 0.01 + ((temperature-self.t1)/(self.t2-self.t1))*0.99
        return 1
    
    def send_rotation(self):
        self.arduino.write(str(self.current_rotation*100).encode())



