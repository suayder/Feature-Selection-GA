CPP=g++
VERSION=c++11

all: tabu_search.o

tabu_search.o: tabu_search.cpp knn.hpp
	${CPP}  -std=${VERSION} tabu_search.cpp -O3

clean:
	rm a.out