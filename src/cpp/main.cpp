
#include <iostream>
#include "files_alg.cpp"

#include "models.cpp"


int main(int argc, char* argv[]){

    if(argc == 2){
        Sim * sim_obj = new Sim();

        read_file(argv[1], sim_obj);

        if(sim_obj->model_type_args[0] == "Err:"){
            std::cout << "Проверьте формат данных в файле загрузки" << std::endl;

        }
        else if(sim_obj->model_type_args[0] == "uniform:"){
            uniform_model test(std::stod(sim_obj->model_type_args[1]), std::stod(sim_obj->model_type_args[2]));


            test.start_sim(sim_obj->sim_time);
            test.print_packets(3);

        }
        else if(sim_obj->model_type_args[0] == "poisson:"){
            poisson_model test( std::stod(sim_obj->model_type_args[1]), std::stod(sim_obj->model_type_args[2]));


            test.start_sim(sim_obj->sim_time);
            test.print_packets(3);
        }
        else{
            std::cout << "Такой модели не существует" << std::endl;
        }

    }
    else{
        std::cout << "Неправильно используете программу" << std::endl;
    }
    return 0;
}