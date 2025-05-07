from serial_manager_door import *
from mtqql_manager_esp import *
import threading

arduino = ArduinoCommunicator()
mqtt_manager = subscriber_handler()
#serial_listener = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def message_handling_temp(client, userdata, msg):
    print("Obtained: "+msg.payload.decode())
    try:
        temp = float(msg.payload.decode())
        mqtt_manager.update_temperatures(temp)
        new_rotation =  arduino.update_rotation(temperature=float(temp))
        new_frequency = arduino.get_frequency()
        mqtt_manager.updateFrequency(new_frequency)
        #serial_listener.write(str(new_rotation).encode())
    except Exception as e:
        print("Payload mal formattato da topic temperature")
        print(e)

    

def start_listening_for_temperature():
    listener2 = paho.Client(client_id="python-listener")
    listener2.connect("broker.hivemq.com",1883,60)
    listener2.subscribe("temperature-topic")
    listener2.on_message = message_handling_temp
    listener2.loop_forever()

def start_listening_for_web_server():
    return None

print("Inizializzazione mqtt...")
start_listening_for_temperature()
print("Premi invio per spegnere")
input()
print("Chiusura thread...")

