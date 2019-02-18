// g++ -std=c++11 permutate_parameters.cpp
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

using namespace std;

void read(){

    ifstream permFiles("permutations.txt");

    if(permFiles.is_open()){
        int n=0;
        while(n<pow(3,3)){
            n++;

            double stem, alpha, ftem;
            double t; //final temperature; Set this as parameter

            permFiles>>ftem>>stem>>alpha;
            cout<<ftem<<" "<<stem<<" "<<alpha<<endl;
            t = ftem;

        }
    }
    exit(1);
}

int main(){
    vector<double> p1 = {1000.0, 5500.0, 10000.0};
    vector<double> p2 = {0.80, 0.895, 0.99};
    vector<double> p3 = {0.01, 0.5, 0.99};

    ofstream file("permutations.txt");

    if(file.is_open()){
        for(auto i:p1){
            for(auto j:p2){
                for(auto k:p3){
                        file<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }

    file.close();
}