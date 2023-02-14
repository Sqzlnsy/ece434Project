apt-get install gpsd
pip install python-can
#you may have different kervel version
cd /opt/source/dtb-5.10-ti
make install
#putting the MPU6050 I2C-2 device tree into uEnv.txt

cd /sys/class/i2c-adapter/i2c-2
# sudo chown debian:debian *
echo mup6050 0x68 > new_device