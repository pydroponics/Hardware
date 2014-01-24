#!/usr/bin/python
# Python Test Programs: Threading 2
# Author: Stark Pister
# 5/21/13

import threading
#import serial
import time
import io
import string

def printNone():
    print "Target"

def initializeThreads():
    threadList = []
    phThread = sensorThread(name = 'pH Data Thread', target = printNone)
    threadList.append(phThread)
    tdsThread = sensorThread(name = 'TDS Data Thread', target = printNone)
    threadList.append(tdsThread)
    return threadList

class sensorThread(threading.Thread):
    def __init__(self, name=None, target=None, period = 5):
        threading.Thread.__init__(self, name=name)
        self.target = target
        self.period = period
    def run(self):
        runNext = threading.Timer(self.period, self.run)
        runNext.start()
        print self.name + ' - ' + time.strftime("%H:%M:%S", time.localtime())
        self.target()

threadList = initializeThreads()

for thread in threadList:
    thread.start()
    time.sleep(2)
