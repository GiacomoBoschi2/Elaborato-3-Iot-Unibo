# Importing Libraries 
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
        self.t1 = float(5.0)
        self.t2 = float(10.0)
        self.f1 = 3000 #milliseconds
        self.f2 = 1500
    
    def update_state(self,temperature):
        if temperature< self.t1 :
            return State.NORMAL
           
        if temperature <= self.t2:
            return State.HOT
        return State.TOO_HOT

    def update_rotation(self,temperature:float):
        self.system_state = self.update_state(temperature)
        print("state=" + str(self.get_state()))
        if(self.system_state==State.NORMAL):
            self.current_rotation = 0.0
        elif self.system_state==State.HOT:
            self.current_rotation = 0.01 + ((temperature-self.t1)/(self.t2-self.t1))*0.99
        else:
            self.current_rotation = 1.0

    
    def get_frequency(self):
        if (self.get_state()==State.NORMAL):
            return self.f1
        return self.f2
    
    def get_state(self):
        return self.system_state
    
    def converted_rotation(self):
        print("Rotation = "+str(self.current_rotation))
        return round(0.90 * self.current_rotation*100.0,2)
    



