#!/usr/bin/python
# Python Test Programs: Timer Threads
# Author: Stark Pister
# 5/20/13

import threading
import time
import io
import string

def printTime():
    print time.strftime("%H:%M:%S", time.localtime())

def lightOff():
    print 'Light Off'
    printTime()

def lightCycle():
    #if no cycleStartTime.db start immediately
    print 'Light On'
    printTime()
    endCycle = threading.Timer(lightThread.duration, lightOff)
    endCycle.start()

class scheduleThread(threading.Thread):
    def __init__(self, name=None, target = None, period = 10, duration = 5):
        threading.Thread.__init__(self, name = name)
        self.target = target
        self.period = period
        self.duration = duration
    def run(self):
        runNext = threading.Timer(self.period, self.run)
        runNext.start()
        print '\n' + self.name
        printTime()
        self.target()
		
lightThread = scheduleThread(name = 'Light Schedule Thread', target = lightCycle, period = 10, duration = 2)
lightThread.start()

