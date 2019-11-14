#!/bin/bash
PWD=`pwd`
INC=$PWD/inc
SRC=$PWD/src
EXE=$PWD/example

cd $EXE
g++ $SRC/TransportInterface.cc -c -std=c++11 -I$INC
g++ $SRC/TCP_TransportInterface.cc -c -std=c++11 -I$INC
g++ $SRC/SCTP_TransportInterface.cc -c -std=c++11 -I$INC -I$SCTP
ar rv libTrans.a *.o
g++ *.cc -c -std=c++11 -I$INC


g++ server.o libTrans.a -o S -std=c++11
g++ client.o libTrans.a -o C -std=c++11


#build sctp need creat symbol link libsctp.so and libsctp.so.1
