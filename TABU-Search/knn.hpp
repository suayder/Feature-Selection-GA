#ifndef KNN
#define KNN

#include <math.h>
#include<algorithm>
#include "t_data.hpp"


using namespace std;

struct _data{
    double distance;
    int classe;
};


template<int K=5>
class Knn{

    public:
        Knn(T_data* dataset){
            this->data = dataset;
        }

        double evaluate(std::vector<bool>& selected_features); //k-fold cross validation
        int predict(int *instance, std::vector<bool>& selected_features); //Return error rate
        double euclideanDistance(int* v1, int* v2, std::vector<bool>& selected_features);
        std::vector<std::string> split(const std::string& s, char delimiter);

        //int** readData(std::string path, unsigned int n_attribute, unsigned int n_instance);

    private:

        T_data* data;

};

//In this method is implemented cross validation


template<int K>
double Knn<K>::evaluate(vector<bool>& selected_features){
    int hits = 0;
    for (int i = 0; i<100;i++){ //Para os 100 primeiros elementos
        if(this->predict(this->data->getData()[i], selected_features) == this->data->getData()[i][this->data->n_attribute-1])
            hits++;
        }
    return (100-hits)/100.0;
};

#ifndef COMPARE_DATA
#define COMPARE_DATA

bool compare_data(_data a, _data b){
    return (a.distance<b.distance);
};

#endif

template<int K>
int Knn<K>::predict(int *instance, vector<bool>& selected_features){
    vector<_data> distance;

    int** dataset = this->data->getData();
    for(int i = 100;i<this->data->n_instance;i++){
        _data a;
        a.distance = euclideanDistance(instance, dataset[i], selected_features);
        a.classe = dataset[i][this->data->n_attribute-1];
        distance.push_back(a);
    }
    sort(distance.begin(), distance.end(), compare_data);

    int c_2 = 0;
    int c_4 = 0;
    for (int i = 0; i<K; i++){
        if(distance[i].classe == 2){
            c_2++;
        }
        else{
            c_4++;
        }
    }
    /* auto a = (c_2>c_4)?2:4;
    cout <<"\n2: "<<c_2<<" 4: "<<c_4<< " Selected: "<<a<<endl;
    for (int i = 0; i<K; i++){
        cout <<"K: "<<i<<" distance: "<<distance[i].distance <<" class: "<<distance[i].classe<<endl;
    } */
    return (c_2>c_4)?2:4;
};

template<int K>
double Knn<K>::euclideanDistance(int* v1, int* v2, vector<bool>& selected_features){
    //int sfetures_size = selected_features.size();
    double sum = 0.0;
    for (int i =0;i<this->data->n_attribute-1;i++){
        if(selected_features[i] == 1){
            sum +=(double)pow((v2[i]-v1[i]),2);
        }
    }
    //cout<< "v1: "<<v1[i] <<" v2: "<<v2[i]<<" sum: "<<sum<<" i: "<<i<<endl;
    //cout<<(v2[i]-v1[i])<<endl;
    //cout <<"\n\n\n sum: "<< sum<<endl;
    return sqrt(sum);
};

#endif