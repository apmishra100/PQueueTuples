PQueueTuples.out : PQueueTuples.o
	g++ -ansi -g -Wall -std=c++11 -o PQueueTuples.out PQueueTuples.o

PQueueTuples.o :  PQueueTuples.cpp
	g++ -ansi -g -Wall -std=c++11 -c PQueueTuples.cpp

clean :
	rm -f PQueueTuples.out PQueueTuples.o
