import time
import random
from enum import Enum
import threading


class State(Enum):
    NORMAL = 1
    HOT = 2
    TOO_HOT = 3
    PANIC = 4

class ArduinoCommunicator:

    def runTimer(self):
        start = time.time()
        while True:
            if self.startTimer:
                start = time.time()
                self.startTimer = False
            elif self.running:
                time_passed = time.time()-start
                print(time_passed)
                if time_passed > 5:
                    self.setPanic = True
                    self.running = False
                    self.startTimer = False
            time.sleep(0.1)


    def __init__(self):
        self.manual_mode = False
        self.current_rotation = 0
        self.command = b""
        self.system_state = State.NORMAL
        self.t1 = float(5.0)
        self.t2 = float(10.0)
        self.f1 = 3000 #milliseconds
        self.f2 = 1500
        self.startTimer = False
        self.running = False
        self.setPanic = False
        timer_thread = threading.Thread(target=self.runTimer,daemon=True)
        timer_thread.start()
    
    def update_state(self,temperature):
        if self.system_state == State.PANIC or self.setPanic == True:
            self.setPanic = 0
            return State.PANIC
        
        if temperature< self.t1 :
            return State.NORMAL
           
        if temperature <= self.t2:
            return State.HOT
        
        if self.system_state != State.TOO_HOT:
            self.running = True
            self.startTimer = True
        return State.TOO_HOT

    def update_rotation(self,temperature:float):
        self.system_state = self.update_state(temperature)
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
        return round(0.90 * self.current_rotation*100.0,2)
    



