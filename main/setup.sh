g++ -o fusionT ../EKF/cosd.cpp ../EKF/EKalmanGND.cpp ../EKF/insfilterNonholonomic.cpp ../EKF/quaternion.cpp ../EKF/sind.cpp ../EKF/vectorBuffer.c ../EKF/rt_nonfinite.cpp ../EKF/rtGetNaN.cpp ../EKF/rtGetInf.cpp ../EKF/test_rtwutil.cpp readGPS.cpp -lgps -pthread
./fusionT
