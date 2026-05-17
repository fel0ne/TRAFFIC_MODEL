
#include <iostream>
#include "files_alg.cpp"

#include "models.cpp"


int main(int argc, char* argv[]){

    if(argc == 2){
        Sim * sim_obj = new Sim();

        read_file(argv[1], sim_obj);

        //std::cout <<"Sim time: " <<sim_obj->sim_time << std::endl << "Model type: "<< std::endl << sim_obj->model_type_args[0] << std::endl<< sim_obj->model_type_args[1] << std::endl<< sim_obj->model_type_args[2] << std::endl;

        if(sim_obj->model_type_args[0] == "Err"){
            std::cout << "Проверьте формат данных в файле загрузки" << std::endl;
            return 0;
        }
        else if(sim_obj->model_type_args[0] == "uniform"){

        }
        else if(sim_obj->model_type_args[0] == "pausson"){

        }
        else{
            std::cout << "Такой модели не существует" << std::endl;
        }

    }
    else{
        std::cout << "Неправильно используете программу" << std::endl;
    }
}