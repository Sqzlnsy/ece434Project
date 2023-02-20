config-pin p9.21 uart
config-pin p9.22 uart
g++ -o fusionT cosd.cpp EKalmanGND.cpp insfilterNonholonomic.cpp readGPS.cpp quaternion.cpp sind.cpp vectorBuffer.c rt_nonfinite.cpp rtGetNaN.cpp rtGetInf.cpp test_rtwutil.cpp -lgps -pthread
./fusionT