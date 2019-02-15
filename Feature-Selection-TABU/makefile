EXECS=tabu_search
CPP=g++
VERSION=c++11

all: ${EXECS}.o
	#${CPP} -std=${VERSION} tabu_search.o knn.o -o tabu_search

tabu_search.o: tabu_search.cpp knn.hpp
	${CPP}  -std=${VERSION} tabu_search.cpp -O3

#knn.o: knn.cpp t_data.hpp knn.hpp
#	${CPP} -o knn.o -std=${VERSION} -c knn.cpp -O3 -lm

clean:
	rm a.out

mrproper: clean
	rm -rf ${EXECS}