# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -std=c++11
 
# **************************************************

# Both server and client.
a.out: Server.o ClientMain.o ServerMain.o Client.o ClientInputCheck.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o
	$(CC) $(CFLAGS) Client.o ClientMain.o ClientInputCheck.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o -o client.out
	$(CC) $(CFLAGS) Server.o ServerMain.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o -o server.out


# Only client.
client.out: Client.o ClientMain.o ClientInputCheck.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o
	$(CC) $(CFLAGS) Client.o ClientMain.o ClientInputCheck.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o -o Client.out

# Only server.
server.out: Server.o ServerMain.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o
	$(CC) $(CFLAGS) Server.o ServerMain.o SafetyChecks.o Point.o PointReader.o KNN.o CalcDist.o -o Client.out


Server.o: Server.cpp SafetyChecks.h Point.h PointReader.h KNN.h
	$(CC) $(CFLAGS) Server.cpp -c

ServerMain.o: Server.o SafetyChecks.h Point.h PointReader.h KNN.h
	$(CC) $(CFLAGS) ServerMain.cpp -c

Client.o: Client.cpp ClientInputCheck.h SafetyChecks.h Point.h PointReader.h KNN.h
	$(CC) $(CFLAGS) Client.cpp -c

ClientMain.o: Client.o ClientInputCheck.h
	$(CC) $(CFLAGS) ClientMain.cpp -c

ClientInputCheck.o: ClientInputCheck.h
	$(CC) $(CFLAGS) ClientInputCheck.cpp -c

SafetyChecks.o: SafetyChecks.h SafetyChecks.cpp
	$(CC) $(CFLAGS) SafetyChecks.cpp -c

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) Point.cpp -c

PointReader.o: PointReader.h PointReader.cpp
	$(CC) $(CFLAGS) PointReader.cpp -c

KNN.o: KNN.h KNN.cpp
	$(CC) $(CFLAGS) KNN.cpp -c

CalcDist.o: CalcDist.h CalcDist.cpp
	$(CC) $(CFLAGS) CalcDist.cpp -c

clean:
	rm *.o *.out
