#include <time.h>
#include <iostream>
#include "knn.hpp"
#include <deque>
#include <algorithm>

#define ALPHA 0.93
#define NEIGHBORS 4
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

_solution generate_new(unsigned int , Knn<>&);
vector<_solution> getNeighbors(int n_attribute, vector<bool>& features, Knn<>& knn_classifier);

bool searchSolution(deque<_solution>& array, _solution* target){
    for (deque<_solution>::iterator it = array.begin(); it!=array.end(); ++it){
        if(it->fitness == target->fitness && it->attributes == target->attributes)
            return false;
    }
    return true;
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

    _solution currentSolution = generate_new(data.n_attribute,knn_classifier);
    _solution newBestSolution = currentSolution;
    vector <_solution> neighbors;

    deque<_solution> tabuList;
    cout<<"Started: ";
    print_solution(currentSolution);
    cout<<"\noptimized: ";

    int iter = 0;
    while(500>iter++){

        neighbors = getNeighbors(data.n_attribute, currentSolution.attributes, knn_classifier);
        if(currentSolution.fitness < neighbors.at(0).fitness)
            newBestSolution = neighbors.at(0);

        for(auto i: neighbors){
            if(searchSolution(tabuList,&i)){
                newBestSolution = i;
            }
        }
        if(tabuList.size()!=0){
            tabuList.pop_back();
            tabuList.push_front(currentSolution);
        }
        currentSolution = newBestSolution;
    }

    print_solution(currentSolution);

    return 0;
}

_solution generate_new(unsigned int n_attribute, Knn<>& knn_classifier){

    vector<bool> selected_features(n_attribute);
    do{ //ensure that vector generated will not have all values less then two
        for(unsigned int i =0; i<n_attribute; i++) //Initialize a random features selected
            selected_features.at(i) = (rand()%10<5)?0:1;
    }while(count_bits(selected_features)<=2);
    
    return _solution(fitness(knn_classifier.evaluate(selected_features), count_bits(selected_features), n_attribute, ALPHA),selected_features);

}

bool compare(_solution a, _solution b){
    return (a.fitness >b.fitness);
}

vector<_solution> getNeighbors(int n_attribute, vector<bool>& features, Knn<>& knn_classifier){

    auto flip = [&features](int id){
        features[id] = (features[id]==0)?1:0;
    };
    vector<_solution> neighbors;

    for(int i =0; i<NEIGHBORS; i++){ //Initialize a random features selected
        do{
            int index = rand()%(n_attribute);
            flip(index);
        }while(count_bits(features)<=2);
        neighbors.push_back(_solution (fitness(knn_classifier.evaluate(features), count_bits(features), n_attribute, ALPHA),features));
    }
    sort(neighbors.begin(), neighbors.end(), compare);
    return neighbors;
}