# Vehicle Telemetry # 

Note: The actual outcome can be seen in the E-Linux page.

## Executive Summary ##
Use extended Kalman filter to integrate GPS and IMU data to achieve a decimeter level accuracy for the position and velocity of a vehicle. Combine with data logged from the CAN bus to build a server as a platform for implementing some apps, such as lap time, accel/brake time for analysis purpose. 

## Overall Structure: ##
![image](https://user-images.githubusercontent.com/81930315/220403909-ae707fa0-c075-4ad2-bf0b-988aad5ed83e.png)



## Packaging ##
At the beginning of this project, after we had drawn out the basic design of this project. We immediately designed a PCB board to mount on the beagle board to achieve portability. Since this device is designed to be mounted on the vehicle, we want the wiring to be as simple as possible.

## Installation Instructions ##
See E-Linux page for specifics  https://elinux.org/ECE434_Project_-_Vehicle_Telemetry
Some of the instructions are put in the setup.sh in the top folder (ece434Project), but since it is hard to do device three installation and different kernel may result in different configurations, instead of providing direct instructions, we will just explain how we install everything in our kernel. Feel free to test out.

## User Instructions ##
In the main folder, three programs can be seen: server.py, fusionT.o (which comes from data_log.cpp) and CAN_LOG.py. To run all three of them, you can choose either to run them in 3 different shells, or run "run_background.sh". If you are to run it in the backround, you can terminate them all by running process_terminate.
NOTE: It may takes up to 90% of CPU Usage to run the program

## Highlights ##
We are almost able to get all the data that OBD2 Interface provides. How OBD2 works is that it listens for request and if you send it a request it will return you a data. 

We have both front end task (server.py) and backend task (futionT), front end uses canvas to plot the data which came from back end, it drags multiple lines from the datalog file (see data folder) and plot them all at a specific frequency (see server.sh and js file in the templates)

The back end is the one that consumes the CPU Usage the most. Since this device is used to record the data in the vehicle, we want to ensure that it keeps updating at a certain frequency. The maximum frequency that IMU can sample is 160 Hz, but we noticed that it takes too much CPU usage (>=92%), we lowered this frequency to 100Hz. Another reason why we lowered the frequency is that for our non real time kernels, it is difficult to make the sampling rate exactly as expected. See the figure below:
![image](https://user-images.githubusercontent.com/81930315/220404005-1e1b973b-3004-4a20-81bf-ac6b3d56bf07.png)

This figure basically measures the time gap between each sample, it is noticeable that most of them are at 0.01s, which is expected since we have 100 Hz frequency. If we change the frequency to 160, this bell will be spread out, which means that the sampling rate becomes more inaccurate.

## Implementation / Theory of Operation ##
1. For gps, we used gpsd module to get the data from the peripheral. To be specific, we used gpsstream() to read the data from the device.
2. For IMU, we used I2c to communicate with the device. What we did was simply adding the device tree to the kernel and constantly read the raw data from the device tree and process the data in our program. Save the processed raw data and send it to the Kalman filter.
3. For CAN, we used python and a can transceiver to communicate with the vehicle. It is able to get the data after sending a request to the vehicle. See CAN_LOG.py

Front End Task: 
We used canvas to plot the data in the localhost, the port is at 8082 so the website that you need to go to is http://192.168.7.2:8082/ after the server.py and fusionT both starts. In the website, multiple plots can be added to the page upon click on the options e.g. AccelerationX, Acceleration Y, RPM etc.
![image](https://user-images.githubusercontent.com/81930315/220404147-7ee0bc91-76f8-466e-9311-b54093f84855.png)

Back End Task:
For the back end, as mentioned above, all we did was grab the raw data first, scale it to the reasonable data, and then put them into a log file using a specific format so that python can process it easily. Time stamp is included since we want the absolute time instead of relative time to make it more accurate.
![image](https://user-images.githubusercontent.com/81930315/220404204-40df5e10-fd7f-45ba-83f9-1d37e8d3060c.png)

Then, the Kalman filter will grab all those raw data and process them and put all those data into a result file. That's the file the server will be accessing to. The server will taken care of the string conversion and formatting issues.



## Work Breakdown ##
Harris: Data log and Back End
Jason: Kalman filter, Front End, Can bus

## Future Work/Conclusions ##
In this project, we used many modules including but not limited to : GPSD, CANBUS, I2C, Device tree, flask,canvas, server, uart and kalman filter.

The code part can still be improved since the CPU usage can be decreased by code optimization. Also, the sampling can be more accurate by using real time kernel.

We didn't expect the 1GHz processor not able to handling 160 Hz IMU well, so if possible, we'd like to do this project again but on a better processor.




