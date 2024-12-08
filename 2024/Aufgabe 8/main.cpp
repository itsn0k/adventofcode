#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>


// Task function

std::vector<std::vector<char>> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<std::vector<char>> a_tockens;
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;

    while (std::getline(file, line)) {
      std::vector<char> line_tockens; 
      std::istringstream iss(line);

      for (int h = 0; h < line.length(); h++) {
        line_tockens.push_back(line[h]);
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

struct Antenna {
  std::vector<Coordinates> coordinates; 
  char antennen_type; 

  Antenna(Coordinates coordinate, char type) {
    coordinates.push_back(coordinate);
    antennen_type = type; 
  }
};



int Check_if_antenna_exsists(char antennen_type, std::vector<Antenna>& antennas) {
  for (int i =0; i < antennas.size(); i++) {
    if (antennen_type == antennas[i].antennen_type) {
      return i; 
    }
  }
  return -1; 
}

Coordinates Find_Start_Postion(std::vector<std::vector<char>>& input) {

  int x = 0; 
  int y = 0; 

  for (int i =0; i < input.size(); i++) {

    for (int t = 0; t < input[i].size(); t++) {
      char value = input[i][t];
      if (value == '^') {
        return Coordinates {t,i};
      }
    }

  }
  return Coordinates {NULL,NULL};
}

std::vector<Antenna> Find_Antennas(std::vector<std::vector<char>>& input) {
  std::vector<Antenna> anntennas; 
  for (int i =0; i < input.size(); i++) {
    for (int t = 0; t < input[i].size(); t++) {
      char value = input[i][t];

      if (value != '.' && value != '#') {
        //Searche For Antanas
        int index = Check_if_antenna_exsists(value, anntennas); 
        if (index> -1) {
          anntennas[index].coordinates.push_back(Coordinates {t,i});
        } 
        else {
          anntennas.push_back(Antenna(Coordinates{t,i},value));
        }    
      }
    }
  }
  return anntennas;
}

bool Check_antindoes(std::vector<std::vector<char>>& input,char type, Coordinates antinodes) {
  if (antinodes.y >= 0 && antinodes.y < input.size()) {
    if (antinodes.x >= 0 && antinodes.x < input[antinodes.y ].size()) {
      char value = input[antinodes.y][antinodes.x];
      if (value == '.') {
        input[antinodes.y][antinodes.x] = '#';
        return true; 
      }
      else if (value != '#' && value != type)
      {
        return true; 
      }
      
    }
  }
  return false; 
}

bool Check_antindoes3(std::vector<std::vector<char>>& input,char type, Coordinates antinodes) {
  if (antinodes.y >= 0 && antinodes.y < input.size()) {
    if (antinodes.x >= 0 && antinodes.x < input[antinodes.y ].size()) {
      char value = input[antinodes.y][antinodes.x];
      if (value == '.') {
        input[antinodes.y][antinodes.x] = '#';
        return true; 
      }
      
    }
  }
  return false; 
}

int Check_antindoes2(std::vector<std::vector<char>>& input, Coordinates first_Vektor, Coordinates antinodes, char type) {
  int sum = 0; 
  int y = first_Vektor.y;
  int x = first_Vektor.x;
  while (y < input.size() &&  x < input[y].size()) {
    y += antinodes.y;
    x += antinodes.x;
    sum += Check_antindoes3(input, type ,Coordinates {x,y});

  }
  return sum; 
}

int task1(std::vector<std::vector<char>>& input) {
  int sum = 0; 
  std::vector<Antenna> antennas = Find_Antennas(input);

  for (int i =0; i < antennas.size(); i++) {
    char value = antennas[i].antennen_type;

    for (int t = 0; t < antennas[i].coordinates.size(); t++) {
      Coordinates first_Vektor = antennas[i].coordinates[t];
      for (int h = t+1; h < antennas[i].coordinates.size(); h++) {
        Coordinates secund_Vektor = antennas[i].coordinates[h];
        Coordinates Search_Vektor = secund_Vektor - first_Vektor;

        Coordinates first_antinodes = first_Vektor + (Search_Vektor * 2);
        Coordinates secound_antinodes = first_Vektor + (Search_Vektor * -1);

        sum += Check_antindoes(input,value,first_antinodes);
        sum += Check_antindoes(input,value,secound_antinodes);
      }
    }
  }

  return sum; 
}

int task2(std::vector<std::vector<char>>& input) {
  int sum = 0; 
  std::vector<Antenna> antennas = Find_Antennas(input);

  for (int i =0; i < antennas.size(); i++) {
    char value = antennas[i].antennen_type;

    for (int t = 0; t < antennas[i].coordinates.size(); t++) {
      Coordinates first_Vektor = antennas[i].coordinates[t];
      for (int h = t+1; h < antennas[i].coordinates.size(); h++) {
        Coordinates secund_Vektor = antennas[i].coordinates[h];
        Coordinates Search_Vektor = secund_Vektor - first_Vektor;

        sum += Check_antindoes2(input,first_Vektor,Search_Vektor,value);
        sum += Check_antindoes2(input,first_Vektor,(Search_Vektor * -1),value);
      }
    }
    sum += antennas[i].coordinates.size();
  }

  return sum; 
}

int main() {
  
  std::vector<std::vector<char>> input_print_rules = Read_Print_Input("input.txt");

  //int task1_num = task1(input_print_rules);
  int task2_num =task2(input_print_rules);

  std::cout << "Ergebniss: " << task2_num << std::endl; 
  

return 0;
}