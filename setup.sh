config-pin P9.21 uart
config-pin P9.22 uart
service gpsd restart
config-pin P9.19 i2c
config-pin P9.20 i2c
# echo 200 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/sampling_frequency
# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_accel_x_en
# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_accel_y_en
# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_accel_z_en


# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_anglvel_x_en
# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_anglvel_y_en
# echo 1 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/scan_elements/in_anglvel_z_en

# echo 512 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/buffer/length
echo 0 > /sys/class/i2c-adapter/i2c-2/2-0068/iio:device1/buffer/enable



