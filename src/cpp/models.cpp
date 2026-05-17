#pragma once

#include <vector>
#include <iostream>

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
            Packet_info  packet; 
            for(double  time = 0.0 ; time < sim_time; time += between_time){
                packet.time = time;
                packet.packet_size = packet_size;
                 
                packets.push_back(packet);

            } 

            return(packets);

        }

        void print_packets(int end){
            for(int i = 0; i < end; i++){
                std::cout << packets[i].time << std::endl;
            }
        }

};