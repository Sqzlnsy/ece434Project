# Compiler and flags
CC=g++
CFLAGS=-pthread

# Directories and source files
EKFDIR=../EKF
GPSDIR=.
INCDIRS=$(EKFDIR)
SRCS=$(EKFDIR)/cosd.cpp $(EKFDIR)/EKalmanGND.cpp $(EKFDIR)/insfilterNonholonomic.cpp $(EKFDIR)/quaternion.cpp $(EKFDIR)/sind.cpp $(EKFDIR)/vectorBuffer.c $(EKFDIR)/rt_nonfinite.cpp $(EKFDIR)/rtGetNaN.cpp $(EKFDIR)/rtGetInf.cpp $(EKFDIR)/test_rtwutil.cpp $(GPSDIR)/readGPS.cpp

# Libraries
LIBS=-lgps

# Output file
OUTPUT=fusionT

all:
	$(CC) -o $(OUTPUT) $(SRCS) $(CFLAGS) $(addprefix -I, $(INCDIRS)) $(LIBS)
    
clean:
	rm -f $(OUTPUT)
