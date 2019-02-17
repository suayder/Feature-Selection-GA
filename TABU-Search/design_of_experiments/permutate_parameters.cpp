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
    vector<int> p1 = {200, 500, 800};
    vector<int> p2 = {2, 5, 8};
    vector<int> p3 = {2, 11, 20};
    vector<double> p4 = {0.60, 0.79, 0.99};
    

    ofstream file("permutations.txt");

    if(file.is_open()){
        for(auto i:p1){
            for(auto j:p2){
                for(auto k:p3){
                    for(auto l:p4){
                        file<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
                    }
                }
            }
        }
    }

    file.close();
}