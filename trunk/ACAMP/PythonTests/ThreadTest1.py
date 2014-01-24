#!/usr/bin/python
# Python Test Programs: Threading
# Author: Stark Pister
# 5/11/13

import threading
import serial
import time
import io
import string

def printTime():
    print time.strftime("%H:%M:%S", time.localtime())

def serialRequest(command = 'Invalid Command'):
    command += '\x0a'
    ser.open()
    time.sleep(1)
    ser.write(command)
    print command
    response = ser.readline()
    if command = 'Invalid Command'
        print Invalid Command
    #print response
    ser.close()
    return response

def tempGetValue()
    uartLock.acquire()
    response = serialRequest('E')
    uartLock.release()
#    if response >< min,max - warning?
    return response

def phGetValue():
    temperature = tempGetValue()
    command = 'PV' + temperature
    uartLock.acquire()
    response = serialRequest(command)
    uartLock.release()
    updateDatabase(phValue = response)
    ph = float(response)
    if ph > phMax.db
        uartLock.acquire()
        response = serialRequest('P-')
        uartLock.release()
    elsif ph < phMin.db
        uartLock.acquire()
        response = serialRequest('P+')
        uartLock.release()

def tdsGetValue():
    temperature = tempGetValue()
    command = "TV" + temperature
    uartLock.acquire()
    response = serialRequest(command)
    uartLock.release()
    conductivity,tds,salinity = response.split(',')
    updateDatabase(tdsValue = response)
    tds = float(response)
    if tds > tdsMax.db
        uartLock.acquire()
        response = serialRequest('T-')
        uartLock.release()
    elsif tds < tdsMin.db
        uartLock.acquire()
        response = serialRequest('T+')
        uartLock.release()


def dhtGetValue()
#    query dht for temp and humid
#    parse response data! Database update. Create airTemp, humidity ints
    updateDatabase(airTemp = airTemp, humidity = humidity)
    if airTemp > airTempMax.db
        uartLock.acquire()
        serialRequest('F+')
        uartLock.release()
    elsif airTemp < airTempMin.db
        uartLock.acquire()
        response = serialRequest('F-')
        uartLock.release()
    if humidity > humidityMax.db
        uartLock.acquire()
        response = serialRequest('D')
        uartLock.release()
#    elsif humidity < humidityMin.db
#        - warning?

def heightGetValue()
    plantHeight, camHeight = getCameraData() # camHeight is lampHeight from the camera data.
    uartLock.acquire()
    lampHeight = serialRequest('H')
    uartLock.release()
    updateDatabase(plantHeight = plantHeight, lampHeight = lampHeight)
    desiredLampHeight = plantHeight + heightDiff.db
    shiftDistance = abs(lampHeight - desiredLampHeight)
    if lampHeight > desiredLampHeight
        uartLock.acquire()
        response = serialRequest('L+' + shiftDistance)
        uartLock.release()
    elsif lampHeight < desiredLampHeight
        uartLock.acquire()
        response = serialRequest('L-' + shift Distance)
        uartLock.release()
#possibly add (LIGHT TOP) command

def lightCycle()
    #if no cycleStartTime.db start immediately
    

class sensorThread(threading.Thread):
    def __init__(self, name=None, target=None, period = 60):
        threading.Thread.__init__(self, name=name)
        self.target = target
        self.period = period
    def run(self):
        next = threading.Timer(self.period, self.run)
        next.start()
        print '\n' + self.name
        printTime()
        self.target()

class scheduleThread(threading.Thread):
    def __init__(self, name=None, target=None, period = 86400, duration = 60):
        threading.Thread.__init__(self, name=name)
        self.target = target
        self.period = period
        self.duration = duration
    def run(self):
        next = threading.Timer(self.period, self.run)
        next.start()
        print '\n' + self.name
        printTime()
        self.target()

# Locks and Serial
uartLock = threading.Lock()
dbLock = threading.Lock()
ser = serial.Serial(port = '/dev/ttyACM0', baudrate = 38400, timeout = 5)
ser.close()

phThread = sensorThread(name = 'pH Data Thread', target = phGetValue, period = 60)
phThread.start()
time.sleep(5)
tdsThread = sensorThread(name = 'TDS Data Thread', target = tdsGetValue, period = 60)
tdsThread.start()
time.sleep(5)
#dhtThread = sensorThread(name = 'DHT Data Thread', target = dhtGetValue, period = 60,)
#dhtThread.start()
#time.sleep(5)
#camThread = sensorThread(name = 'Height Data Thread', target = heightGetValue, period = 600)
#camThread.start()
#time.sleep(5)
#lightThread = scheduleThread(name = 'Light Schedule Thread', target = lightCycle, period = 86400, duration = 43200)
#lightThread.start()
#time.sleep(5)
#pumpThread = scheduleThread(name = 'Pump Schedule Thread', target = pumpCycle, period = 21600, duration = 600)
#pumpThread.start()
#time.sleep(5)

while 1:
    try:
        input = raw_input("Command:")
        phThread.args = input

    except (KeyboardInterrupt, SystemExit):
        raise
        sys.exit()
# Check if "responses" are ok!