#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

class LineSegment {
    public:
        int x1;
        int x2;
        int y1;
        int y2;

        LineSegment(int x_1, int y_1, int x_2, int y_2){
            x1 = x_1;
            y1 = y_1;
            x2 = x_2;
            y2 = y_2;
        }

        int getX1(){
            return this -> x1;
        }

        int getY1(){
            return this -> y1;
        }

        int getX2(){
            return this -> x2;
        }

        int getY2(){
            return this -> y2;
        }
        
        int getMinX(){
            return (this -> x1 <= this -> x2 ? this -> x1 : this -> x2);
        }

        int getMaxX(){
            return (this -> x1 >= this -> x2 ? this -> x1 : this -> x2);
        }

        int getMinY(){
            return (this -> y1 <= this -> y2 ? this -> y1 : this -> y2);
        }

        int getMaxY(){
            return (this -> y1 >= this -> y2 ? this -> y1 : this -> y2);
        }

        bool slopePositive(){
            return ((this -> getX2() - this -> getX1() > 0) && (this -> getY2() - this -> getY1() > 0)) || ((this -> getX2() - this -> getX1() < 0) && (this -> getY2() - this -> getY1() < 0));
        }

        void prettyPrint(){
            std::cout << "(" << this -> x1 << ", " << this -> y1 << ") -> (" << this -> x2 << ", " << this -> y2 << ")" << std::endl; 
        }
};

class Grid {
    public:
        std::vector<std::vector<int>> point_grid;

        Grid(int max_x, int max_y){
            point_grid = std::vector<std::vector<int>> (max_y + 1, std::vector<int>(max_x + 1, 0));
        }

        void place_line(LineSegment * l){
            for (int i = l -> getMinY(); i < l -> getMaxY() + 1; i++){
                for (int j = l -> getMinX(); j < l -> getMaxX() + 1; j++){
                    this -> point_grid.at(i).at(j) += 1;
                }
            }
        }

        void place_line_diagonal(LineSegment * l){
            if (isDiagonal(l)){
                for (int count = 0; count < (l -> getMaxX() - l -> getMinX() + 2 - 1); count++){
                    if (l -> slopePositive()){
                        if (l -> getX2() - l -> getX1() > 0){
                            this -> point_grid.at(l -> getY1() + count).at(l -> getX1() + count) += 1;
                        }
                        else {
                            this -> point_grid.at(l -> getY1() - count).at(l -> getX1() - count) += 1;
                        }
                    }
                    else {
                        if (l -> getX2() - l -> getX1() > 0){
                            this -> point_grid.at(l -> getY1() - count).at(l -> getX1() + count) += 1;
                        }
                        else {
                            this -> point_grid.at(l -> getY1() + count).at(l -> getX1() - count) += 1;
                        }
                    }
                }
            }
            else {
                for (int i = l -> getMinY(); i < l -> getMaxY() + 1; i++){
                    for (int j = l -> getMinX(); j < l -> getMaxX() + 1; j++){
                        this -> point_grid.at(i).at(j) += 1;
                    }
                }
            }
        }

        bool isDiagonal(LineSegment * l){
            return (l -> getX1() != l -> getX2() && l -> getY1() != l -> getY2());
        }

        void prettyPrint(){
            for (unsigned int i = 0; i < this -> point_grid.size(); i++){
                for (unsigned int j = 0; j < this -> point_grid.at(0).size(); j++){
                    std::cout << this -> point_grid.at(i).at(j) << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }

        long long calculatePointTotal(){
            long long sum = 0;

                for (unsigned int i = 0; i < this -> point_grid.size(); i++){
                    for (unsigned int j = 0; j < this -> point_grid.at(0).size(); j++){
                        if (this -> point_grid.at(i).at(j) >= 2){
                            sum += 1;
                        }
                    }
                }

            return sum;
        }

};

long long solutionPart1() {
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    std::vector<LineSegment *> line_segment_list;

    int max_x = 0;
    int max_y = 0;

    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            int x1 = 0;
            int x2 = 0;
            int y1 = 0;
            int y2 = 0;

            std::string delimiter = " -> ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while (end != std::string::npos){
                std::string token = line.substr(start, end - start);
                std::string delimiter2 = ",";
                size_t start2 = 0;
                size_t end2 = token.find(delimiter2, start2);
                while(end2 != std::string::npos){
                    std::string token2 = token.substr(start2, end2 - start2);
                    x1 = std::stoi(token2);    
                    start2 = end2 + 1;
                    end2 = token.find(delimiter2, start2);
                }

                std::string token2 = token.substr(start2, end2 - start2);
                y1 = std::stoi(token2);
                
                start = end + delimiter.size();
                end = line.find(delimiter, start);
            }
            
            std::string token = line.substr(start, end - start);
            std::string delimiter2 = ",";
            size_t start2 = 0;
            size_t end2 = token.find(delimiter2, start2);
            while(end2 != std::string::npos){
                std::string token2 = token.substr(start2, end2 - start2);
                x2 = std::stoi(token2);    
                start2 = end2 + 1;
                end2 = token.find(delimiter2, start2);
            }

            std::string token2 = token.substr(start2, end2 - start2);
            y2 = std::stoi(token2);
            
            LineSegment * l = new LineSegment(x1, y1, x2, y2);
            if (x1 == x2 || y1 == y2){
                max_x = std::max(max_x, x1);
                max_x = std::max(max_x, x2);

                max_y = std::max(max_y, y1);
                max_y = std::max(max_y, y2);

                line_segment_list.push_back(l);
            }
        }
    }

    Grid g = Grid(max_x, max_y);

    for (unsigned int i = 0; i < line_segment_list.size(); i++){
        g.place_line(line_segment_list.at(i));
    }
    
    return g.calculatePointTotal();
}

long long solutionPart2(){
    std::ifstream myFile;
    myFile.open("input.txt");
    std::string line = "";

    std::vector<LineSegment *> line_segment_list;

    int max_x = 0;
    int max_y = 0;

    if (myFile.is_open()){
        while (std::getline(myFile, line)){
            int x1 = 0;
            int x2 = 0;
            int y1 = 0;
            int y2 = 0;

            std::string delimiter = " -> ";
            size_t start = 0;
            size_t end = line.find(delimiter, start);
            while (end != std::string::npos){
                std::string token = line.substr(start, end - start);
                std::string delimiter2 = ",";
                size_t start2 = 0;
                size_t end2 = token.find(delimiter2, start2);
                while(end2 != std::string::npos){
                    std::string token2 = token.substr(start2, end2 - start2);
                    x1 = std::stoi(token2);    
                    start2 = end2 + 1;
                    end2 = token.find(delimiter2, start2);
                }

                std::string token2 = token.substr(start2, end2 - start2);
                y1 = std::stoi(token2);
                
                start = end + delimiter.size();
                end = line.find(delimiter, start);
            }
            
            std::string token = line.substr(start, end - start);
            std::string delimiter2 = ",";
            size_t start2 = 0;
            size_t end2 = token.find(delimiter2, start2);
            while(end2 != std::string::npos){
                std::string token2 = token.substr(start2, end2 - start2);
                x2 = std::stoi(token2);    
                start2 = end2 + 1;
                end2 = token.find(delimiter2, start2);
            }

            std::string token2 = token.substr(start2, end2 - start2);
            y2 = std::stoi(token2);
            
            LineSegment * l = new LineSegment(x1, y1, x2, y2);

            max_x = std::max(max_x, x1);
            max_x = std::max(max_x, x2);

            max_y = std::max(max_y, y1);
            max_y = std::max(max_y, y2);

            line_segment_list.push_back(l);
        }
    }

    Grid g = Grid(max_x, max_y);

    for (unsigned int i = 0; i < line_segment_list.size(); i++){
        g.place_line_diagonal(line_segment_list.at(i));
    }
    
    return g.calculatePointTotal();
}

int main() {

    std::cout << solutionPart1() << std::endl;
    std::cout << solutionPart2() << std::endl;

	return 1;
}
