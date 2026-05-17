#include <fstream>
#include <string>
#include <vector> 
struct Sim{
    double sim_time;
    std::string model_type_args[3];
};



void read_file(std::string filepath, Sim* sim_obj){
    std::fstream in_file;
    in_file.open(filepath, std::ios::in);
    if(in_file.is_open()){  
        
        in_file >> sim_obj->sim_time ;
        in_file.ignore();
        int i = 0;
        while(std::getline(in_file,sim_obj->model_type_args[i], ' ')){
            i++;
        }

    }
    else{

        sim_obj->sim_time = 0;
        sim_obj->model_type_args[0] = "Err";

    }
}


