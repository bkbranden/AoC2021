#include <iostream>
#include <fstream>
#include <string>
#include <limits>

long long solutionPart1() {
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    long long depth = 0;
    long long forward = 0;
    
    if (myFile.is_open()){
        while(std::getline(myFile, line)){
            std::string direction = "";
            std::string amount = "";

            std::string delimiter = " ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while(end != std::string::npos) {
                direction = line.substr(start, end);
                start = end + 1;
                end = line.find(delimiter, start);
            }

            amount = line.substr(start, end);
            
            if (direction == "forward"){
                forward += stoi(amount);
            }
            else if (direction == "up"){
                depth -= stoi(amount);
            }
            else if (direction == "down"){
                depth += stoi(amount);
            }
        }
        myFile.close();
    }
    
    return depth * forward;
}

long long solutionPart2(){
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    long long depth = 0;
    long long forward = 0;
    long long aim = 0; 
    
    if (myFile.is_open()){
        while(std::getline(myFile, line)){
            std::string direction = "";
            std::string amount = "";

            std::string delimiter = " ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while(end != std::string::npos) {
                direction = line.substr(start, end);
                start = end + 1;
                end = line.find(delimiter, start);
            }

            amount = line.substr(start, end);
            
            if (direction == "forward"){
                forward += stoi(amount);
                depth += (aim * stoi(amount));
            }
            else if (direction == "up"){
                aim -= stoi(amount);
            }
            else if (direction == "down"){
                aim += stoi(amount);
            }
        }
        myFile.close();
    }
    
    return depth * forward;
}

int main() {

    std::cout << solutionPart1() << std::endl;
    std::cout << solutionPart2() << std::endl;

	return 1;
}
