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
import json

serial_lock = threading.Lock()
current_read_door_rotation = 0
arduino = ArduinoCommunicator()
mqtt_manager = subscriber_handler()
serialConnection = serial.Serial('/dev/ttyACM0')

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
    
async def data_json(request):
    file_path = os.path.join('../dashboard-frontend', 'info.json')
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        return web.Response(text=content, content_type='text/plain')
    except Exception as e:
        return web.Response(text=f"Error reading file: {e}", status=500)
    
async def send_manual_mode(request):
    with serial_lock:
        paylaod = b"\nX\n"
        serialConnection.write(paylaod) 
    return web.Response(text="Request took", content_type='text/plain')

async def restorePanic(request):
    if arduino.get_state() == State.PANIC:
        with serial_lock:
            paylaod = b"\nP\n"
            serialConnection.write(paylaod) 
            arduino.system_state = State.NORMAL
    return web.Response(text="Request took", content_type='text/plain')

def sendPanic():
        if arduino.get_state() == State.PANIC:
            with serial_lock:
                paylaod = b"\nP\n"
                serialConnection.write(paylaod) 

def message_handling_temp(client, userdata, msg):
    try:
        prev = arduino.get_state()
        temp = float(msg.payload.decode())
        mqtt_manager.update_temperatures(temp)
        new_frequency = arduino.get_frequency()
        mqtt_manager.updateFrequency(new_frequency)
        arduino.update_rotation(temp)
        if arduino.get_state() == State.PANIC and prev!=State.PANIC:
            sendPanic()
        communicate_new_data()
        update_web_server_display_data()
    except Exception as e:
        print(e)

    


def start_listening_for_temperature():
    client = paho.Client(client_id=f"python-listener-{uuid.uuid4()}")
    client.connect("broker.hivemq.com",1883,60)
    client.subscribe("temperature-topic")
    client.on_message = message_handling_temp
    client.loop_start()

def read_door_rot():
    global current_read_door_rotation
    while(True):
        try:
            time.sleep(0.05)
            with serial_lock:
                if serialConnection.in_waiting > 0:
                    data = serialConnection.readline()
                    if(not b'|' in data):
                        current_read_door_rotation = data.decode()
        except Exception as e:
            print(e)
        

    
def communicate_new_data():
    with serial_lock:
        paylaod = b"\n"+str(arduino.converted_rotation()).encode()+b'|'+str(mqtt_manager.measures[-1]).encode()+b"\n"
        serialConnection.write(paylaod) #last temperature measured

def update_web_server_display_data():
    #measurments
    new_data =""
    for i in mqtt_manager.measures:
        new_data+=(str(i))+"\n"
    file_path = os.path.join('../dashboard-frontend', 'data.txt.tmp')
    with open(file_path,"w") as f:
        f.write(new_data)
    os.rename(file_path, os.path.join('../dashboard-frontend', 'data.txt'))

    #generic info (current mode,last measurment ecc...)
    info = {}
    info["mode"] = str(arduino.get_state())
    info["last_m"] = mqtt_manager.getLastMeasurment()
    info["avg"] = round(mqtt_manager.avarage(),2)
    info["max"] = round(mqtt_manager.current_max,2)
    info["min"] = round(mqtt_manager.current_min,2)
    info["door"] = current_read_door_rotation
    file_path = os.path.join('../dashboard-frontend', 'info.json.tmp')
    with open(file_path,"w") as f:
        f.write(json.dumps(info))
    os.rename(file_path, os.path.join('../dashboard-frontend', 'info.json'))




def create_web_server():
    app = web.Application()
    aiohttp_jinja2.setup(app, loader=jinja2.FileSystemLoader(os.path.join(os.getcwd(), "../dashboard-frontend")))
    app.add_routes([web.get('/', hello),web.get('/data.txt',data_txt)])
    app.add_routes([web.get('/', hello),web.get('/info.json',data_json)])
    app.add_routes([web.get('/', hello),web.get('/manual',send_manual_mode)])
    app.add_routes([web.get('/', hello),web.get('/restore',restorePanic)])
    web.run_app(app)


def main():
    print("Inizializzazione mqtt...")
    temperature_thread = threading.Thread(target=start_listening_for_temperature,daemon=True)
    temperature_thread.start()
    print("Inizializzazione seriale...")
    serial_thread = threading.Thread(target=read_door_rot,daemon=True)
    serial_thread.start()
    print("Inizializzazione web server...")
    create_web_server()
    

main()


