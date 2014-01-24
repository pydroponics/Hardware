#!/usr/bin/python
# Pydroponics Control
# Author: Stark Pister
# 5/11/13

import threading
#import serial
import time
import io
import string

#========================#
#  Function Definitions  #
#========================#

def printTime():
    """ Prints current system time. """
    print time.strftime("%m/%d/%Y %H:%M:%S", time.localtime())

def initializeThreads():
    """ Initializes the threads. Returns thread list. """
    threadList = []
    phThread = sensorThread(name = 'pH Data Thread',
                            target = phGetValue,
                            period = 10)
    threadList.append(phThread)
    tdsThread = sensorThread(name = 'TDS Data Thread',
                             target = tdsGetValue,
                             period = 10)
    threadList.append(tdsThread)
    #dhtThread = sensorThread(name = 'DHT Data Thread',
    #                         target = dhtGetValue,
    #                         period = 60,)
    #threadList.append(dhtThread)
    #camThread = sensorThread(name = 'Height Data Thread',
    #                         target = heightGetValue,
    #                         period = 600)
    #threadList.append(camThread)
    lightThread = scheduleThread(name = 'Light Schedule Thread',
                                 period = 20, 
                                 duration = 4,
                                 on = 'L1',
                                 off = 'L0') #86400 and 50400 real defaults
    threadList.append(lightThread)
    pumpThread = scheduleThread(name = 'Pump Schedule Thread',
                                period = 30,
                                duration = 10,
                                on = 'W1',
                                off = 'W0') #21600 and 600 real defaults
    threadList.append(pumpThread)
    #airpumpThread = scheduleThread(name = 'Air Pump Schedule Thread',
    #                               period = ?,
    #                               duration = ?,
    #                               on = 'P1',
    #                               off = 'P0') #21600 and 600 real defaults
    #threadList.append(airpumpThread)
    return threadList

def serialRequest(command = 'Invalid Command'):
    """ Send command to UART. Returns response.  """
    uartLock.acquire()
#    ser.write(command + '\n')
#    response = ser.readline()
#    if command = 'Invalid Command'
#        print "Invalid Command"
    print command + ' - ' + time.strftime("%m/%d/%Y %H:%M:%S", time.localtime()) #Testing
    response = 10 #Testing
    uartLock.release()
    return response

def updateDatabase(readTable = "", writeTable = ""):
    """ Send data to database. Return latest constraints. """
    dbLock.acquire()
    dbCursor = conn.cursor()
	dbCursor.execute
	dbConnection.commit()
	dbCursor.close()
    dbLock.release()

def phGetValue():
    """ Get temp, get pH, update database, adjust pH. """
    temperature = serialRequest('E')
    phValue = serialRequest('PV' + str(temperature))
    #updateDatabase(phValue = phValue)
    ph = float(phValue)
    if ph > 11: #phMax.db
        response = serialRequest('P-')
    elif ph < 11: #phMin.db
        response = serialRequest('P+')

def tdsGetValue():
    """ Get temp, get tds, update database, adjust tds. """
    temperature = serialRequest('E')
    response = serialRequest('TV' + str(temperature))
    tdsValue = response
    #conductivity,tdsValue,salinity = response.split(',')
    #updateDatabase(tdsValue = tdsValue)
    tds = float(tdsValue)
    if tds > 26: #tdsMax.db
        response = serialRequest('T-')
    elif tds < 26: #tdsMin.db
        response = serialRequest('T+')

def getDhtData():
    """ Query DHT. Return air temp, humidity. """
    output = subprocess.check_output(["./Adafruit_DHT"]);
    matches = re.search("Temp =\s+([0-9.]+)", output)
    airTemp = float(matches.group(1))
    matches = re.search("Hum =\s+([0-9.]+)", output)
    humidity = float(matches.group(1))
    return airTemp, humidity

def dhtGetValue():
    """ Get air temp, humid, update database, adjust fans/dehumidifier. """
    # Still needs warning for low humidity.
    airTemp, humidity = getDhtData()
    #updateDatabase(airTemp = airTemp, humidity = humidity)
    if airTemp > airTempMax.db:
        serialRequest('F+')
    elif airTemp < airTempMin.db:
        response = serialRequest('F-')
    if humidity > humidityMax.db:
        response = serialRequest('D')

def getCameraData():
    """ Query camera. Returns plant height. """
    print "does nothing yet" # uh oh

def heightGetValue():
    """ Get plant, lamp height, update database, adjust height. """
    # Still needs light to top command
    plantHeight = getCameraData()
    lampHeight = serialRequest('LH')
    #updateDatabase(plantHeight = plantHeight, lampHeight = lampHeight)
    desiredLampHeight = plantHeight + heightDiff.db
    shiftDistance = abs(lampHeight - desiredLampHeight)
    if lampHeight > desiredLampHeight:
        response = serialRequest('L+' + shiftDistance)
    elif lampHeight < desiredLampHeight:
        response = serialRequest('L-' + shiftDistance)

#========================#
#   Class Definitions    #
#========================#

class sensorThread(threading.Thread):
    """ Run 'target' every 'period'. Print 'name' and time. """
    def __init__(self, name=None, target=None, period = 60):
        threading.Thread.__init__(self, name=name)
        self.target = target
        self.period = period
    def run(self):
        self.runNext = threading.Timer(self.period, self.run)
        self.runNext.start()
        print self.name + ' - ' + time.strftime("%m/%d/%Y %H:%M:%S", time.localtime())
        self.target()

class scheduleThread(threading.Thread):
    """ 'on' every 'period'. 'off' after 'duration'. Print 'name' and time. """
    def __init__(self, name=None, period = 86400, duration = 60, on = None, off = None):
        threading.Thread.__init__(self, name=name)
        self.period = period
        self.duration = duration
        self.on = on
        self.off = off
    def run(self):
        self.runNext = threading.Timer(self.period, self.run)
        self.runNext.start()
        print self.name + ' - ' + time.strftime("%m/%d/%Y %H:%M:%S", time.localtime())
        response = serialRequest(self.on)
        self.endCycle = threading.Timer(self.duration, serialRequest, [self.off])
        self.endCycle.start()

#========================#
#          Main          #
#========================#
		
# Locks and Serial 
uartLock = threading.Lock()
dbLock = threading.Lock()
#ser = serial.Serial(port = '/dev/ttyACM0', baudrate = 38400, timeout = 5)
dbConnection = psychopg2.connect("dbname = pydroponics.com, user = ?")
threadList = initializeThreads()

for thread in threadList:
    thread.start()
    time.sleep(2)
serialRequest('LR') # Reset light to top position.
serialRequest('A1') # Turn on air pump.

#def shutdown() #Work in Progess. Untested.
#systemShutoff('all')
#for thread in systemsOn.db
#   thread.runNext.cancel()
#for thread in threadList:
#    thread.join()
#sys.exit()
