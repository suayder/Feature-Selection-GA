#include <time.h>
#include<iostream>
#include "knn.hpp"
#define ALPHA 0.93
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

_solution generate_new(unsigned int , Knn<>&);
_solution generate_near(int , vector<bool>&, Knn<>&);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if(argc!=2){
        cout<<"run like this: \' ./a.out dataset_name \'"<<endl;
        exit(0);
    }
    T_data data(argv[1]);

    Knn<> knn_classifier(&data);

    return 0;
}

_solution generate_new(unsigned int n_attribute, Knn<>& knn_classifier){

    vector<bool> selected_features(n_attribute);
    do{ //ensure that vector generated will not have all values less then two
        for(unsigned int i =0; i<n_attribute; i++) //Initialize a random features selected
            selected_features.at(i) = (rand()%10<5)?0:1;
    }while(count_bits(selected_features)==0);
    
    return _solution(fitness(knn_classifier.evaluate(selected_features), count_bits(selected_features), n_attribute, ALPHA),selected_features);

}

_solution generate_near(int n_attribute, vector<bool>& features, Knn<>& knn_classifier){
    
    int q = rand()%(n_attribute);

    auto flip = [&features](int id){
        features[id] = (features[id]==0)?features[id]=1:features[id]=0;
    };

    do{
        for(int i =0; i<q; i++){ //Initialize a random features selected
            srand(clock());
            int index = rand()%(n_attribute);
            flip(index);
        }
    }while(count_bits(features)<features.size()*0.2);

    return _solution (fitness(knn_classifier.evaluate(features), count_bits(features), n_attribute, ALPHA),features);
}