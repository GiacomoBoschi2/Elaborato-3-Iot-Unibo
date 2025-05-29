import sys
import paho.mqtt.client as paho

client = paho.Client()

class subscriber_handler:
    def __init__(self,server = "broker.hivemq.com", port = 1883, N=5):
        self.server = server
        self.port = port
        self.frequency_publisher= paho.Client()
        self.frequency_publisher.connect(server,port,60)
        self.N = N #numero campioni da tenere traccia
        self.measures = []
        self.current_max=0.0
        self.current_min=9999.0
    
    def update_temperatures(self,temperature):
        if(len(self.measures)==self.N):
            self.measures = self.measures[1:]
        self.measures.append(temperature)
        self.current_max = max(self.current_max,temperature)
        self.current_min = min(self.current_min,temperature)

    def get_info_measurements(self): #returns a tuple (min,max,avg)
        min_t = min(self.measures)
        max_t = max(self.measures)
        avg = sum(self.measures)/len(self.measures)
        return (min_t,max_t,avg)

    def updateFrequency(self,frequency):
        message = self.frequency_publisher.publish("frequency-topic",f"{str(frequency)}")
        print(message.is_published())

    def getLastMeasurment(self):
        if len(self.measures)==0:
            return 0
        return self.measures[-1]
    
    def avarage(self):
        if len(self.measures)==0:
            return 0
        return sum(self.measures)/len(self.measures)


    
    