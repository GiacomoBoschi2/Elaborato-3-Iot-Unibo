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
    def __init__(self):
        self.manual_mode = False
        self.current_rotation = 0
        self.command = b""
        self.system_state = State.NORMAL
        self.t1 = float(10.0)
        self.t2 = float(20.0)
        self.f1 = float(1.0)
        self.f2 = float(0.5)
    
    def update_state(self,temperature):
        if temperature< self.t1 :
            return State.NORMAL
        if temperature <= self.t2:
            return State.HOT
        return State.TOO_HOT

    def update_rotation(self,temperature:float):
        state = self.update_state(temperature)
        if(state==State.NORMAL):
            return 0
        if state==State.HOT:
            return 0.01 + ((temperature-self.t1)/(self.t2-self.t1))*0.99
        return 1
    
    def get_frequency(self):
        if (self.get_state()==State.NORMAL):
            return self.f1
        return self.f2
    
    def get_state(self):
        return self.system_state
    



