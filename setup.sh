config-pin P9.21 uart
config-pin P9.22 uart
service gpsd restart
config-pin P9.19 i2c
config-pin P9.20 i2c
ip link set can1 type can bitrate 500000
ifconfig can1 up




