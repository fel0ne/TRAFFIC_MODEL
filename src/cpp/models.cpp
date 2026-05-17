#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <chrono>


struct Packet_info{
    double time;
    int packet_size;
};



class uniform_model{
    private:
        double between_time;
        int packet_size;
        std::vector <Packet_info> packets;
    public:


        uniform_model(double between_time_t, int packet_size_t){
            between_time = between_time_t;
            packet_size = packet_size_t;
        }
        
        std::vector<Packet_info> start_sim(double sim_time){
            packets.clear(); 
            Packet_info  packet; 
            for(double  time = 0.0 ; time < sim_time; time += between_time){
                packet.time = time;
                packet.packet_size = packet_size;
                 
                packets.push_back(packet);

            } 

            return(packets);

        }

        void print_packets(int end){
            int limit = std::min(end, static_cast<int>(packets.size()));
            for (int i = 0; i < limit; i++) {
                std::cout << "Время: " << packets[i].time 
                        << " с, Размер: " << packets[i].packet_size << " байт" << std::endl;
            }
        }

};



class poisson_model{
    private:
        double lambda_interval; 
        double lambda_size;
        std::vector <Packet_info> packets;
    public:

        poisson_model(double l_interval, double l_size) {
            lambda_interval = l_interval;
            lambda_size = l_size;
        }
        
        std::vector<Packet_info> start_sim(double sim_time) {
            packets.clear(); 
            Packet_info packet;


            unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
            std::mt19937 rg(seed);
            

            std::poisson_distribution<int> poi_dist(lambda_interval);
            std::exponential_distribution<double> exp_dist(lambda_size); 

            double current_time = 0.0;
            double interval;
            while (current_time < sim_time) {

                interval = static_cast<double>(poi_dist(rg)) / 1000.0; 
                

                if (interval <= 0.0) {
                    interval = 0.001; 
                }

                current_time += interval;
                if (current_time >= sim_time) break;

                
                packet.time = current_time;

                double raw_size = exp_dist(rg) * lambda_size; 
                packet.packet_size = static_cast<int>(raw_size);

                if (packet.packet_size < 1) {
                    packet.packet_size = 1; 
                }

                packets.push_back(packet);
            }

            return packets;
        }

        void print_packets(int end){
            int limit = std::min(end, static_cast<int>(packets.size()));
            for (int i = 0; i < limit; i++) {
                std::cout << "Время: " << packets[i].time 
                        << " с, Размер: " << packets[i].packet_size << " байт" << std::endl;
            }
        }

};