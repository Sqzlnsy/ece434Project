#!/usr/bin/python
import can
import time
import os
import sys
sys.path.append('../OBDII_LOGGER')

import OBDII_PID


log_dir = '../data/'
categories = {OBDII_PID.ENGINE_RPM: 'engineRPM.log', OBDII_PID.THROTTLE_POSITION: 'throttlePos.log'}

def CAN_log(msg):
    pid = msg.data[OBDII_PID.PID_INDEX]
    #print(pid)
    if pid in categories:
        data = OBDII_PID.OBDII_reader(msg)
        print(data)
        filename = log_dir + categories[key]
        f=open(filename, 'w') 
        f.write(str(time.time()) + " " + str(data) +'\n')
        f.close()

def main():
    filters = [
        {"can_id": 0x7E8, "can_mask": 0x7FF, "extended": False},
    ]
    bus = can.interface.Bus(channel="can1", bustype="socketcan", can_filters=filters)
    listener = CAN_log
    can.Notifier(bus, [listener])
    try: 
        while(True):
            for key in categories:
                #print("Request key:" + str(key))
                msg = can.Message(arbitration_id=0x7DF, data=[0x02, 0x01, key, 0x55, 0x55, 0x55, 0x55, 0x55], is_extended_id=False)
                bus.send(msg)
                time.sleep(0.1)
            time.sleep(1)
    except KeyboardInterrupt:
        print("CAN log stopped")

main()

    

