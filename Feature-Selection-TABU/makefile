EXECS=simulated_annealing
CPP=g++
VERSION=c++11

all: ${EXECS}.o
	#${CPP} -std=${VERSION} simulated_annealing.o knn.o -o simulated_annealing

simulated_annealing.o: simulated_annealing.cpp knn.hpp
	${CPP}  -std=${VERSION} simulated_annealing.cpp -O3

#knn.o: knn.cpp t_data.hpp knn.hpp
#	${CPP} -o knn.o -std=${VERSION} -c knn.cpp -O3 -lm

clean:
	rm a.out

mrproper: clean
	rm -rf ${EXECS}