#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>

int BIT_LENGTH = 12;
unsigned int ALL_ONES = 0b111111111111; 
int TEST_BIT_LENGTH = 5;

long long solutionPart1() {
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    long long gamma_rate = 0;
    long long epsilon_rate = 0;
    std::vector<int> bit_accumulator(BIT_LENGTH, 0);
    
    if (myFile.is_open()){
        while(std::getline(myFile, line)){
            for (int i = 0; i < BIT_LENGTH; i++){
                char bit_value = line[i];
                if (bit_value == '0'){
                    bit_accumulator.at(i) -= 1;
                }
                else {
                    bit_accumulator.at(i) += 1;
                }
            }
        }
        myFile.close();
    }

    std::string binary_string = "";

    for (unsigned int i = 0; i < bit_accumulator.size(); i++){
        if (bit_accumulator.at(i) > 0){
            binary_string += "1";
        }
        else {
            binary_string += "0";
        }
    }

    gamma_rate = std::stoi(binary_string, 0, 2);
    epsilon_rate = gamma_rate ^ ALL_ONES;

    return gamma_rate * epsilon_rate;
}

long long recursiveHelper(std::vector<std::string> &arr, unsigned int index, bool tie_one){
    if (arr.size() <= 1){
        return std::stoi(arr.at(0), 0, 2);
    }
    
    int maj_value = 0;
    for (unsigned int i = 0; i < arr.size(); i++) {
        if (arr.at(i)[index] == '1'){
            maj_value += 1;
        }
        else {
            maj_value -= 1;
        }
    }
    
    std::vector<std::string> accumulator;

    if (tie_one) {
        for (unsigned int i = 0; i < arr.size(); i++){
            if (maj_value >= 0){
                if (arr.at(i)[index] == '1'){
                    accumulator.push_back(arr.at(i));
                }
            }
            else {
                if (arr.at(i)[index] == '0'){
                    accumulator.push_back(arr.at(i));
                }
            }
        }
    }
    else {
        for (unsigned int i = 0; i < arr.size(); i++){
            if (maj_value >= 0){
                if (arr.at(i)[index] == '0'){
                    accumulator.push_back(arr.at(i));
                }
            }
            else {
                if (arr.at(i)[index] == '1'){
                    accumulator.push_back(arr.at(i));
                }
            }
        }
    }

    return recursiveHelper(accumulator, index + 1, tie_one);
}

long long solutionPart2(){
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    long long oxygen_rate  = 0;
    long long co2_rate = 0;
    std::vector<std::string> oxygen_list;
    std::vector<std::string> co2_list;
    
    if (myFile.is_open()){
        while(std::getline(myFile, line)){
            oxygen_list.push_back(line);
            co2_list.push_back(line);
        }
        myFile.close();
    }
    
    oxygen_rate = recursiveHelper(oxygen_list, 0, true);
    co2_rate = recursiveHelper(co2_list, 0, false);

    return oxygen_rate * co2_rate; 
}

int main() {

    std::cout << solutionPart1() << std::endl;
    std::cout << solutionPart2() << std::endl;

	return 1;
}
