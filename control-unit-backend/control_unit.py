import asyncio
import uuid
from serial_manager_door import *
from mtqql_manager_esp import *
import threading
import serial 
import asyncio
from aiohttp import web
import paho.mqtt.client as mqtt

arduino = ArduinoCommunicator()
mqtt_manager = subscriber_handler()
serialConnection = serial.Serial('/dev/ttyACM1')

async def hello(request):
    return web.Response(text="Hello, world")


def on_disconnect(client, userdata, rc):
    if rc != 0:
        print(f"[MQTT] Unexpected disconnection. Return code: {rc}")
    else:
        print("[MQTT] Disconnected cleanly.")

def message_handling_temp(client, userdata, msg):
    print("Obtained: "+msg.payload.decode())
    try:
        temp = float(msg.payload.decode())
        mqtt_manager.update_temperatures(temp)
        new_rotation =  arduino.update_rotation(temperature=float(temp))
        new_frequency = arduino.get_frequency()
        mqtt_manager.updateFrequency(new_frequency)
        arduino.update_rotation(temp)
        communicate_new_data()
        #serial_listener.write(str(new_rotation).encode())
    except Exception as e:
        print("Payload mal formattato da topic temperature")
        print(e)

    

def start_listening_for_temperature():
    client = mqtt.Client(client_id=f"python-listener-{uuid.uuid4()}")
    print("connecting")
    client.connect("broker.hivemq.com",1883,60)
    client.subscribe("temperature-topic")
    client.on_message = message_handling_temp
    client.on_disconnect = on_disconnect
    client.loop_forever()
    
def communicate_new_data():
    paylaod = str(arduino.converted_rotation()).encode()+b'|'+str(mqtt_manager.measures[-1]).encode()
    print(paylaod)
    serialConnection.write(paylaod) #last temperature measured


def start_listening_for_web_server():
    return None

print("Inizializzazione mqtt...")
# Create a thread targeting the function
start_listening_for_temperature()
