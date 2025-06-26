#include <Arduino.h>
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Scheduling/SharedData.h"
#include "../lib/Tasks/LedTask.h"
#include "../lib/Scheduling/Timer.h"
#include "../lib/Tasks/TempSensorTask.h"
#include "../lib/Tasks/MqttTask.h"
#include "../lib/Tasks/NetworkTask.h"


#define RED_PIN 27
#define GREEN_PIN 26
#define TEMP_PIN 34
#define MAC_ADDRESS {0xec,0x62,0x60,0x9c,0x53,0xdc}

#define BASE_PERIOD 100

Scheduler* sched;
LedTask* ledTask;
TempSensorTask* tempTask;
MqttTask* mqtt_task;
NetworkTask* network_task;

SharedData share_data;

void setup() {
  sched = new Scheduler();
  sched->init(BASE_PERIOD);

  ledTask = new LedTask(GREEN_PIN,RED_PIN);
  ledTask -> init(BASE_PERIOD*2);
  sched->addTask(ledTask);

  tempTask = new TempSensorTask(TEMP_PIN);
  tempTask->init(BASE_PERIOD*4);
  sched->addTask(tempTask);

  network_task = new NetworkTask("Bababui","Sassofono");
  network_task->init(BASE_PERIOD*2);
  sched->addTask(network_task);

  mqtt_task = new MqttTask("broker.hivemq.com");
  mqtt_task->init(BASE_PERIOD*2);
  sched->addTask(mqtt_task);
}

void loop() {
  sched->schedule();
}

