g++ -o fusionT cosd.cpp EKalmanGND.cpp insfilterNonholonomic.cpp readGPS.cpp quaternion.cpp sind.cpp vectorBuffer.c rt_nonfinite.cpp rtGetNaN.cpp rtGetInf.cpp test_rtwutil.cpp -lgps -pthread
./fusionT