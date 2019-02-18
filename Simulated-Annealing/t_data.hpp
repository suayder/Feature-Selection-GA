#ifndef T_DATA
#define T_DATA

#include<vector>
#include<string>

#include<fstream>
#include<sstream>
#include<memory>
#include<iostream>

using namespace std;

class T_data{

    public:

        unsigned int n_instance, n_attribute;

        T_data(string path, char delimiter=','){
            this->path_file = path;
            this->delimiter=delimiter;
            this->readData();
        }
    
        void readData(){

            ifstream file(this->path_file);
            string line;
            vector<string> tokens;
            unsigned int c_instance = 0, c_attribute;
            if(file.is_open()){

                getline(file, line);
                tokens = split(line);
                this->n_attribute=tokens.size();
                int cu =1;
                while(getline(file, line))
                    cu++;
                this->n_instance=cu;

                this->data = (int**) malloc(this->n_instance*sizeof(int*));
                for (unsigned int i = 0; i<this->n_instance;i++){
                    this->data[i] = (int*) malloc(this->n_attribute*sizeof(int));
                }
                file.clear();
                file.seekg(0,ios::beg);

                while(getline(file, line)){
                    tokens = split(line);
                    c_attribute = 0;
                    for (auto i:tokens){
                        try{
                            this->data[c_instance][c_attribute] = stoi(i);
                        }
                        catch (exception e){
                            data[c_instance][c_attribute] = -1;
                        }
                        c_attribute++;
                    }
                    c_instance++;
                }
                file.close();
            }
            else{
                cout << "Something Wrong on reading file"<<endl;
            }
        }

        int ** getData(){
            return this->data;
        }

        void print_d(){
            cout<<n_attribute<<" "<<n_instance<<endl;
            for(int i=0;i<this->n_instance;i++){
                for(int j=0;j<this->n_attribute;j++){
                    cout<<this->data[i][j]<<" ";
                }
                cout<<endl;
            }
        }

    private:

        int **data;
        string path_file;
        char delimiter;

        vector<string> split(const string& s)
        {
            vector<string> tokens;
            string token;
            istringstream tokenStream(s);
            while (getline(tokenStream, token, this->delimiter)){
                tokens.push_back(token);
            }
            tokens.erase(tokens.begin());
            return tokens;
        }

};

#endif