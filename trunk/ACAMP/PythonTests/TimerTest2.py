#!/usr/bin/python
# Python Test Programs: Threading
# Author: Stark Pister
# 5/11/13

#Working Model
import threading
import time
import io
import string

def printTime():
    print time.strftime("%H:%M:%S", time.localtime())

def phGetValue():
    print 'phGetValue'
    time.sleep(1)

class sensorThread(threading.Thread):
    def __init__(self, name=None, target=None, period = 60):
        threading.Thread.__init__(self, name=name)
        self.target = target
        self.period = period
    def run(self):
        runNext = threading.Timer(self.period, self.run)
        runNext.start()
        print '\n' + self.name
        printTime()
        self.target()

phThread = sensorThread(name = 'pH Data Thread', target = phGetValue, period = 10)
phThread.start()

