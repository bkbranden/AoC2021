#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <cmath>

int THREAD_COUNT = 100;
std::mutex lock;

long long solutionPart1() {
    std::ifstream myFile;
    myFile.open("input2.txt");
    std::string line = "";

    std::vector<int> lanternfish_list;

    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            std::string delimiter = ",";
            size_t start = 0;
            size_t end = line.find(delimiter, start);

            while(end != std::string::npos){
                std::string token = line.substr(start, end - start);
                lanternfish_list.push_back(std::stoi(token));
                start = end + 1;
                end = line.find(delimiter, start);
            }

            std::string token = line.substr(start, end - start);
            lanternfish_list.push_back(std::stoi(token));
        }
        myFile.close();
    }
    
    int count = 0;
    int max_day = 80;
    int added_count = 0;

    while(count < max_day){
        while(added_count != 0){
            lanternfish_list.push_back(9);
            added_count--;
        }

        for (unsigned int i = 0; i < lanternfish_list.size(); i++){
            lanternfish_list.at(i) -= 1;

            if (lanternfish_list.at(i) == 0){
                added_count++;
                lanternfish_list.at(i) = 7;
            }
        }

        count++;
    }
    
    return lanternfish_list.size();
}

void calculate_lanternfish(std::vector<int> & lanternfish_list, int thread_index, int size, int & added_count){

    lock.lock();

    double division = (double) size / (double) THREAD_COUNT;

    int low_range = round(thread_index * division); 
    int high_range = round((thread_index + 1) * division);

 //   std::cout << "THREAD NUMBER " << thread_index << ": LOW_INDEX: " << low_range << " HIGH_INDEX: " << high_range << std::endl;

    if (low_range < size){
        for (int i = low_range; i < std::min(high_range, size); i++){
            lanternfish_list.at(i) -= 1;

            if (lanternfish_list.at(i) == 0){
                added_count++;
                lanternfish_list.at(i) = 7;
            }
        }
    }

    lock.unlock();
}

long long solutionPart2(){
    std::ifstream myFile;
    myFile.open("input2.txt");
    std::string line = "";

    std::vector<int> lanternfish_list;

    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            std::string delimiter = ",";
            size_t start = 0;
            size_t end = line.find(delimiter, start);

            while(end != std::string::npos){
                std::string token = line.substr(start, end - start);
                lanternfish_list.push_back(std::stoi(token));
                start = end + 1;
                end = line.find(delimiter, start);
            }

            std::string token = line.substr(start, end - start);
            lanternfish_list.push_back(std::stoi(token));
        }
        myFile.close();
    }
    
    int count = 0;
    int max_day = 80;
    int added_count = 0;

    while(count < max_day){
        
        std::cout << "DAY " << count + 1 << " ------------------------------------------------------------------" << std::endl;
        std::vector<std::thread> thread_list;

        while(added_count != 0){
            lanternfish_list.push_back(9);
            added_count--;
        }

        for (int i = 0; i < THREAD_COUNT; i++){
            thread_list.push_back(std::thread(calculate_lanternfish, std::ref(lanternfish_list), i, lanternfish_list.size(), std::ref(added_count)));
        }

        for (unsigned int i = 0; i < thread_list.size(); i++){
            thread_list.at(i).join();
        }

/*
        for (unsigned int i = 0; i < lanternfish_list.size(); i++){
            std::cout << lanternfish_list.at(i) << " "; 
        }
        std::cout << std::endl;
        */
        count++;
    }

    
    return lanternfish_list.size();
}

int main() {

    std::cout << solutionPart1() << std::endl;
    std::cout << solutionPart2() << std::endl;

	return 1;
}
