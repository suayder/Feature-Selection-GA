//g++ -std=c++11 test_parameters.cpp
#include <time.h>
#include <iostream>
#include "knn.hpp"
#include <deque>
#include <algorithm>

using namespace std;

typedef struct sol{
    double fitness;
    vector<bool> attributes;

    sol(double f, vector<bool> att){
        fitness = f;
        attributes = att;
    }
} _solution;

auto fitness = [](double classifier_error, int cardinality, int features, double alpha){
        return (alpha*classifier_error)+(1.0-alpha)*(cardinality/features);
    };

auto count_bits = [](vector<bool>& v){
        int cont = 0;
        for(auto it:v)
            if(it==true)
                cont++;
        return cont;
    };

void print_solution(_solution solu){

    cout<< "Selected features: ";
    for (auto i:solu.attributes)
        cout<< i;
    cout<<" Fitness: "<<solu.fitness<<endl;
}

_solution generate_new(unsigned int , Knn<>&, const double ALPHA);
vector<_solution> getNeighbors(int n_attribute, vector<bool>& features, Knn<>& knn_classifier, int size, const double ALPHA);

bool searchSolution(deque<_solution>& array, _solution* target){
    for (deque<_solution>::iterator it = array.begin(); it!=array.end(); ++it){
        if(it->fitness == target->fitness && it->attributes == target->attributes)
            return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if(argc!=2){
        cout<<"run like this: \' ./a.out dataset_name \'"<<endl;
        exit(0);
    }
    T_data data(argv[1]);

    Knn<> knn_classifier(&data);

    ifstream permFiles("permutations.txt");

    ofstream resultFile("results.txt");

    double alpha;
    int ni, nb, tbz;

    if(permFiles.is_open() && resultFile.is_open()){
        int n=0;
        while(n<81){
            n++;
            permFiles>>ni>>nb>>tbz>>alpha;

            _solution currentSolution = generate_new(data.n_attribute,knn_classifier, alpha);

            _solution newBestSolution = currentSolution;
            vector <_solution> neighbors;

            deque<_solution> tabuList;

            int iter = 0;

            while(ni>iter++){
                neighbors = getNeighbors(data.n_attribute, currentSolution.attributes, knn_classifier, nb, alpha);
                if(currentSolution.fitness < neighbors.at(0).fitness)
                    newBestSolution = neighbors.at(0);

                for(auto i: neighbors){
                    if(!searchSolution(tabuList,&i)){
                        newBestSolution = i;
                        break;
                    }
                }
                if(tabuList.size()==tbz){
                    if(currentSolution.attributes != tabuList.back().attributes){
                        tabuList.pop_back();
                        tabuList.push_front(currentSolution);
                    }
                }
                else{
                    tabuList.push_front(currentSolution);
                }

                currentSolution = newBestSolution;
            }

            resultFile<<ni<<" "<<nb<<" "<<tbz<<" "<<alpha<<" "<<(double)currentSolution.fitness<<endl;

            //system ("gnuplot -p chart.gnu");
        }
    }
    permFiles.close();
    resultFile.close();
    return 0;
}

_solution generate_new(unsigned int n_attribute, Knn<>& knn_classifier, const double ALPHA){

    vector<bool> selected_features(n_attribute);
    do{ //ensure that vector generated will not have all values less then two
        for(unsigned int i =0; i<n_attribute; i++) //Initialize a random features selected
            selected_features.at(i) = (rand()%10<5)?0:1;
    }while(count_bits(selected_features)<=2);

    return _solution(fitness(knn_classifier.evaluate(selected_features), count_bits(selected_features), n_attribute, ALPHA),selected_features);

}

bool compare(_solution a, _solution b){
    return (a.fitness < b.fitness);
}

vector<_solution> getNeighbors(int n_attribute, vector<bool>& features, Knn<>& knn_classifier, const int size, const double ALPHA){

    auto flip = [&features](int id){
        vector<bool> cp(features);
        cp[id] = (features[id]==0)?1:0;
        return cp;
    };
    vector<_solution> neighbors;

    for(int i =0; i<size; i++){ //Initialize a random features selected
        vector<bool> nb;
        do{
            int index = rand()%(n_attribute);
            nb = flip(index);
        }while(count_bits(nb)<=2);
        neighbors.push_back(_solution (fitness(knn_classifier.evaluate(nb), count_bits(nb), n_attribute, ALPHA),nb));
    }
    sort(neighbors.begin(), neighbors.end(), compare);
    //cout<< neighbors.at(0).fitness <<" - "<< neighbors.at(1).fitness<<endl;
    return neighbors;
}