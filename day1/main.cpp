#include <iostream>
#include <fstream>
#include <string>
#include <limits>

int main() {

    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";
    
    int first = 0;
    int second = 0;
    int third = 0;
    int previous = 0; 

    int increasingCounter = 0;
    int fileLineIndex = 0;

    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            int current = stoi(line);
            if (fileLineIndex == 0){
                first = current;
            }
            else if (fileLineIndex == 1) {
                second = current;
            }
            else {
                third = current;
                int currentSum = third + second + first;
                if (fileLineIndex != 2) {
                    if (currentSum - previous > 0) {
                        increasingCounter++;
                    }
                }

                previous = currentSum; 
                first = second;
                second = third;
            }

            fileLineIndex++;
        }
        myFile.close();
    }

    std::cout << "NUMBER OF TIMES INCREASED: " << increasingCounter << std::endl;

	return 1;
}
