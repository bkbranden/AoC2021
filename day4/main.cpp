#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>

int BOARD_WIDTH = 5;
int BOARD_HEIGHT = 5;

class Board {
    public:
        bool completed;
        std::vector<std::vector<int>> bingo_board;

        Board(std::vector<int> &board_numbers) {
            completed = false;
            bingo_board = std::vector<std::vector<int>> (BOARD_WIDTH, std::vector<int>(BOARD_HEIGHT, 0));
            for (int i = 0; i < BOARD_HEIGHT; i++){
                for (int j = 0; j < BOARD_WIDTH; j++){
                    bingo_board.at(i).at(j) = board_numbers.at((i * 5) + j);
                }
            }
        }

        std::vector<std::vector<int>> getBoard(){
            return this -> bingo_board;
        }

        bool crossOff(int number){
            for (int i = 0; i < BOARD_HEIGHT; i++){
                for (int j = 0; j < BOARD_WIDTH; j++){
                    if (this -> bingo_board.at(i).at(j) == number){
                        this -> bingo_board.at(i).at(j) = -1;
                        return determineWin(i, j);
                    }
                }
            }

            return false;
        }

        bool determineWin(int row, int col){
            bool result_col = true;
            bool result_row = true;
            for (int i = 0; i < BOARD_HEIGHT; i++){
                if (this -> bingo_board.at(i).at(col) != -1){
                    result_col = false; 
                }
            }

            for (int j = 0; j < BOARD_WIDTH; j++){
                if (this -> bingo_board.at(row).at(j) != -1){
                    result_row = false; 
                }
            }
            
            this -> completed = result_col || result_row;

            return result_col || result_row;
        }

        int calculateSum(){
            int sum = 0;
            for (int i = 0; i < BOARD_HEIGHT; i++){
                for (int j = 0; j < BOARD_WIDTH; j++){
                    if (this -> bingo_board.at(i).at(j) != -1){
                        sum += this -> bingo_board.at(i).at(j);
                    }
                }
            }
            
            return sum;
        }

        void prettyPrint(){
            for (int i = 0; i < BOARD_HEIGHT; i++){
                for (int j = 0; j < BOARD_WIDTH; j++){
                    std::cout << this -> bingo_board.at(i).at(j) << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
};

long long solutionPart1() {
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";
    int line_count = 0;

    std::vector<int> numbers;
    std::vector<Board *> board_list;
    std::vector<int> numbers_to_add;
    
    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            if (line_count == 0){
                std::string delimiter = ",";
                size_t start = 0;
                size_t end = line.find(delimiter, start);
                while (end != std::string::npos){
                    std::string token = line.substr(start, end);
                    numbers.push_back(std::stoi(token));
                    start = end + 1;
                    end = line.find(delimiter, start);
                }
                std::string token = line.substr(start, end);
                numbers.push_back(std::stoi(token));
                line_count++;
                continue;
            }

            if (line_count == 1){
                line_count++;
                continue;
            }

            if (line == "" || line == "\n"){
                Board *b = new Board(numbers_to_add);
                board_list.push_back(b);
                numbers_to_add.clear();
                continue;
            }

            std::string delimiter = " ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while (end != std::string::npos) {
                std::string token = line.substr(start, end - start);
                if (token == " " || token == "" || token == "  "){
                    start = end + 1;
                    end = line.find(delimiter, start);
                    continue;
                }
                numbers_to_add.push_back(std::stoi(token));
                start = end + 1;
                end = line.find(delimiter, start);
            }
            
            std::string token = line.substr(start, end - start);
            numbers_to_add.push_back(std::stoi(token));
        }

        Board *b = new Board(numbers_to_add);
        board_list.push_back(b);
        numbers_to_add.clear();

        myFile.close();
    }

    for (unsigned int i = 0; i < numbers.size(); i++){
        for (unsigned int j = 0; j < board_list.size(); j++){
           if (board_list.at(j) -> crossOff(numbers.at(i))){
               return numbers.at(i) * board_list.at(j) -> calculateSum();
           }
        }
    }


    return -1;
}

long long solutionPart2(){
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";
    int line_count = 0;

    std::vector<int> numbers;
    std::vector<Board *> board_list;
    std::vector<int> numbers_to_add;
    
    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            if (line_count == 0){
                std::string delimiter = ",";
                size_t start = 0;
                size_t end = line.find(delimiter, start);
                while (end != std::string::npos){
                    std::string token = line.substr(start, end);
                    numbers.push_back(std::stoi(token));
                    start = end + 1;
                    end = line.find(delimiter, start);
                }
                std::string token = line.substr(start, end);
                numbers.push_back(std::stoi(token));
                line_count++;
                continue;
            }

            if (line_count == 1){
                line_count++;
                continue;
            }

            if (line == "" || line == "\n"){
                Board *b = new Board(numbers_to_add);
                board_list.push_back(b);
                numbers_to_add.clear();
                continue;
            }

            std::string delimiter = " ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while (end != std::string::npos) {
                std::string token = line.substr(start, end - start);
                if (token == " " || token == "" || token == "  "){
                    start = end + 1;
                    end = line.find(delimiter, start);
                    continue;
                }
                numbers_to_add.push_back(std::stoi(token));
                start = end + 1;
                end = line.find(delimiter, start);
            }
            
            std::string token = line.substr(start, end - start);
            numbers_to_add.push_back(std::stoi(token));
        }

        Board *b = new Board(numbers_to_add);
        board_list.push_back(b);
        numbers_to_add.clear();

        myFile.close();
    }

    unsigned int board_wins = 0;

    for (unsigned int i = 0; i < numbers.size(); i++){
        for (unsigned int j = 0; j < board_list.size(); j++){
            if (board_list.at(j) -> completed == false && board_list.at(j) -> crossOff(numbers.at(i))){
                board_wins++;
                if (board_wins == board_list.size()){
                    return numbers.at(i) * board_list.at(j) -> calculateSum(); 
                }
            }
        }
    }


    return -1;
}

int main() {

    std::cout << solutionPart1() << std::endl;
    std::cout << solutionPart2() << std::endl;

	return 1;
}
