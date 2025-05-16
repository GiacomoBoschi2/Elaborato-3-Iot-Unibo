import asyncio
import os
import uuid

import jinja2
from serial_manager_door import *
from mtqql_manager_esp import *
import threading
import serial 
import asyncio
from aiohttp import web
from paho import mqtt
import aiohttp_jinja2


arduino = ArduinoCommunicator()
mqtt_manager = subscriber_handler()
serialConnection = serial.Serial('/dev/ttyACM1')

async def hello(request):
    response = aiohttp_jinja2.render_template("home.html", request,context={})
    return response

async def data_txt(request):
    file_path = os.path.join('../dashboard-frontend', 'data.txt')
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        return web.Response(text=content, content_type='text/plain')
    except Exception as e:
        return web.Response(text=f"Error reading file: {e}", status=500)


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
        update_web_server_display_data()
    except Exception as e:
        print("Payload mal formattato da topic temperature")
        print(e)

    


def start_listening_for_temperature():
    client = paho.Client(client_id=f"python-listener-{uuid.uuid4()}")
    client.connect("broker.hivemq.com",1883,60)
    client.subscribe("temperature-topic")
    client.on_message = message_handling_temp
    client.loop_start()
    
def communicate_new_data():
    paylaod = str(arduino.converted_rotation()).encode()+b'|'+str(mqtt_manager.measures[-1]).encode()
    print(paylaod)
    serialConnection.write(paylaod) #last temperature measured

def update_web_server_display_data():
    new_data =""
    for i in mqtt_manager.measures:
        new_data+=(str(i))+"\n"
    file_path = os.path.join('../dashboard-frontend', 'data.txt.tmp')
    with open(file_path,"w") as f:
        f.write(new_data)
    os.rename(file_path, os.path.join('../dashboard-frontend', 'data.txt'))



def create_web_server():
    app = web.Application()
    aiohttp_jinja2.setup(app, loader=jinja2.FileSystemLoader(os.path.join(os.getcwd(), "../dashboard-frontend")))
    app.add_routes([web.get('/', hello),web.get('/data.txt',data_txt)])
    web.run_app(app)


def main():
    print("Inizializzazione mqtt...")
    temperature_thread = threading.Thread(target=start_listening_for_temperature)
    temperature_thread.start()
    print("Inizializzazione web server...")
    create_web_server()
    

main()


