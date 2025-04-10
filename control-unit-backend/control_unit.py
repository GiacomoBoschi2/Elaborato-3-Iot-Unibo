from serial_manager_door import *
from mtqql_manager_esp import *
import threading

arduino = ArduinoCommunicator()
mqtt_manager = subscriber_handler()
#serial_listener = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def message_handling_temp(client, userdata, msg):
    try:
        temp = float(msg.payload.decode())
        mqtt_manager.update_temperatures(temp)
        new_rotation =  arduino.update_rotation(temp)
        new_frequency = arduino.get_state()
        mqtt_manager.updateFrequency(new_frequency)
        #serial_listener.write(str(new_rotation).encode())
    except:
        print("Payload mal formattato da topic temperature")

    

def start_listening_for_temperature():
    listener2 = paho.Client()
    listener2.connect("localhost",1883,60)
    listener2.subscribe("temperature-topic")
    listener2.on_message = message_handling_temp
    listener2.loop_forever()

def start_listening_for_web_server():
    return None

print("Inizializzazione mqtt...")
t1 = threading.Thread(target=start_listening_for_temperature)
t1.start()

print("Premi invio per spegnere")
input()
print("Chiusura thread...")

