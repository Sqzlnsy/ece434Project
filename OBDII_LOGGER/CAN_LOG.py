import can
import OBDII_PID
import time
import os

log_dir='/tmp/CAN_LOG/'
categories = {OBDII_PID.ENGINE_RPM: 'ENGINE_RPM', OBDII_PID.THROTTLE_POSITION: 'THROTTLE_POSITION'}\
file_dirs = {}
for key in categories
    filename = log_dir + categories[key]
    file_dirs[key]=open(filename, 'w') 

def CAN_log(msg):
    pid = msg.data[OBDII_PID.PID_INDEX]
    if pid in data_categories:
        data = OBDII_PID.OBDII_reader(msg)
        f = file_dirs[pid]
        f.write(data + " " + time.time())

def main():
    filters = [
        {"can_id": 0x7E8, "can_mask": 0x7FF, "extended": False},
    ]
    bus = can.interface.Bus(channel="can0", bustype="socketcan", can_filters=filters)
    listener = CAN_LOG()
    can.Notifier(bus, [listener])
    try: 
        while(True):
            for key in categories:
                msg = can.Message(arbitration_id=0x7DF, data=[0x02, 0x01, key, 0x55, 0x55, 0x55, 0x55, 0x55], extended_id=False)
                bus.send(msg)
            time.sleep(0.08)
    except KeyboardInterrupt:
        for key in file_dirs:
            file_dirs[key].close()

main()

    

