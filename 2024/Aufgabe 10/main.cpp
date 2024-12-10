#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>


// Task function
std::vector<std::vector<int>> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<std::vector<int>> a_tockens;
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;

    while (std::getline(file, line)) {
      std::vector<int> line_tockens; 
      std::istringstream iss(line);

      for (int h = 0; h < line.length(); h++) {
        int number = line[h] - '0';
        line_tockens.push_back(number);
      }
          
      a_tockens.push_back(line_tockens);
    }
    file.close();
  }
    
    //Logic Path Finding
  return a_tockens;
}

struct Coordinates {
  int x;
  int y;

  public:
    bool operator==(const Coordinates& b) {
      return x == b.x && y == b.y; 
    }
    bool operator!=(const Coordinates& b) {
      return x != b.x || y != b.y; 
    }
    Coordinates operator-(const Coordinates& b){
      return Coordinates { x-b.x, y-b.y};
    }
    Coordinates operator+(const Coordinates& b){
      return Coordinates { x+b.x, y+b.y};
    }
    Coordinates operator*(int value){
      return Coordinates { x*value, y*value};
    }
};

int Move_to_Tail(std::vector<std::vector<int>>& input,std::vector<Coordinates>& nine_cordinates, int temp_value, int x, int y) {
  int sum = 0; 

  if ( 0 <= y && y < input.size()) {

    if (0 <= x && x < input[y].size()) {
      int value = input[y][x];

      if (temp_value+1 == value) {

      if (value == 9) {
        for (int h = 0; h < nine_cordinates.size(); h++) {
          if (nine_cordinates[h].x == x && nine_cordinates[h].y == y){
            return 0; 
          }
        }
        nine_cordinates.push_back(Coordinates{x,y});
        return 1; 
      }

      //Up
      sum += Move_to_Tail(input,nine_cordinates,value, x, y-1);

      //Down
      sum += Move_to_Tail(input,nine_cordinates,value, x, y+1);

      //Left
      sum += Move_to_Tail(input,nine_cordinates,value, x-1, y);

      //Rigth
      sum += Move_to_Tail(input,nine_cordinates,value, x+1, y);

      return sum; 
      }

    }
  }
  return 0; 
}

int Move_to_Tail2(std::vector<std::vector<int>>& input, int temp_value, int x, int y) {
  int sum = 0; 

  if ( 0 <= y && y < input.size()) {

    if (0 <= x && x < input[y].size()) {
      int value = input[y][x];

      if (temp_value+1 == value) {

      if (value == 9) {
        return 1; 
      }

      //Up
      sum += Move_to_Tail2(input,value, x, y-1);

      //Down
      sum += Move_to_Tail2(input,value, x, y+1);

      //Left
      sum += Move_to_Tail2(input,value, x-1, y);

      //Rigth
      sum += Move_to_Tail2(input,value, x+1, y);

      return sum; 
      }

    }
  }
  return 0; 
}

int task1(std::vector<std::vector<int>>& input) {
  int sum = 0; 

  for (int y =0; y < input.size(); y++) {

    for (int x =0; x < input[y].size(); x++) {
      int value = input[y][x];

      if (value == 0) {
        std::vector<Coordinates> nine_cordinates;
        sum += Move_to_Tail(input,nine_cordinates,-1,x,y);
      }

    }
  }

  return sum; 
}

int task2(std::vector<std::vector<int>>& input) {
  int sum = 0; 

  for (int y =0; y < input.size(); y++) {

    for (int x =0; x < input[y].size(); x++) {
      int value = input[y][x];

      if (value == 0) {
        sum += Move_to_Tail2(input,-1,x,y);
      }

    }
  }

  return sum; 
}

int main() {
  
  std::vector<std::vector<int>> input_print_rules = Read_Print_Input("input.txt");

  //int task1_num = task1(input_print_rules);
  int task2_num =task2(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}