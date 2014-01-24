#!/usr/bin/python
# Event threads
# Author: Stark Pister
# 5/30/13

import threading
#import serial
import time
import io
import string

def event():
    threadEvent.wait()
    print 'event!'
    print time.strftime("%m/%d/%Y %H:%M:%S", time.localtime())

threadEvent = threading.Event()
Thread = threading.Thread(name = 'Event Thread', target = event)
Thread.start()
time.sleep(10)
threadEvent.set()
