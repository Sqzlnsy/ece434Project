config-pin p9.21 uart
config-pin p9.22 uart
g++ -o fusionT dependencies/cosd.cpp dependencies/EKalmanGND.cpp dependencies/insfilterNonholonomic.cpp dependencies/quaternion.cpp dependencies/sind.cpp dependencies/vectorBuffer.c dependencies/rt_nonfinite.cpp dependencies/rtGetNaN.cpp dependencies/rtGetInf.cpp dependencies/test_rtwutil.cpp readGPS.cpp -lgps -pthread
./fusionT
