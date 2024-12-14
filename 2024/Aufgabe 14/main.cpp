#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <fstream>


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

struct Robot {
  Coordinates positions;
  Coordinates velocities;
};

std::vector<Coordinates> Read_Line_Input(std::string line, std::string value_x, std::string value_y) {
  std::string token;
  std::string number_read; 
  std::vector<Coordinates> cords; 
  Coordinates cord;
  for (int i =0; i < line.length(); i++) {
    
    if ((token == value_x || token == value_y) && line[i] != ',' && line[i] != ' ') {
      number_read+= line[i];
    }  
    
    if (line[i] == ',' && number_read != "" && (token == value_x || token == value_y) ) {
      cord.x = std::stoi(number_read);
      number_read = "";
    } else if ((i == line.length()-1 || line[i] == ' ') && number_read != "") {
      cord.y = std::stoi(number_read);
      token = "";
      number_read = "";
      cords.push_back(cord);
      cord = {0,0}; 
    } else if (line[i] == value_x[0] || line[i] == value_x[1] || line[i] == value_y[0] || line[i] == value_y[1] ) {
      token += line[i];
    } 
  }
  return cords; 
}

std::vector<Robot> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<Robot> robots;
  std::ifstream file(filename);
  if (file.is_open()) {

    std::string line;
    Robot robot = {};
    int counter =0; 
    while (std::getline(file, line)) {
      std::istringstream iss(line);

      std::vector<Coordinates> cord = Read_Line_Input(line, "p=", "v=");
      robot.positions = cord[0];
      robot.velocities = cord[1];
      robots.push_back(robot);
    }
    
    file.close();
  }  
    //Logic Path Finding
  return robots;
}


std::vector<std::vector<int>> CreatePlay(int wide , int tall, int value) {
  std::vector<std::vector<int>> playfild;

  playfild.resize(tall);
  for (int i =0; i < playfild.size(); i++) {
    playfild[i].resize(wide);
    for (int k =0; k < playfild[i].size(); k++) {
      playfild[i][k] = value;
    }
  }
  return playfild;
}

void Place_robot_on_start_position(std::vector<Coordinates>& input, std::vector<std::vector<int>>& playfild) {
  for (auto cord : input) {
    playfild[cord.y][cord.x]++;
  }
}

int Count_robots_in_quadrant(std::vector<std::vector<int>>& playfild) {
  int quadrants_1 =0; 
  int quadrants_2 =0;
  int quadrants_3 =0;
  int quadrants_4 =0;

  int not_this_y = roundf(playfild.size()/2);
  for (int y =0; y < playfild.size(); y++) {
    int not_this_x = roundf(playfild[y].size()/2);
    for (int x =0; x < playfild[y].size(); x++) {
      int value = playfild[y][x];
      if (x != not_this_x && y != not_this_y && value > 0 && x < not_this_x && y < not_this_y){
        quadrants_1 += value;
      } else if (x != not_this_x && y != not_this_y && value > 0 && x > not_this_x && y < not_this_y)
      {
        quadrants_2 += value;
      } else if (x != not_this_x && y != not_this_y && value > 0 && x > not_this_x && y > not_this_y)
      {
        quadrants_3 += value;
      } else if (x != not_this_x && y != not_this_y && value > 0 && x < not_this_x && y > not_this_y)
      {
        quadrants_4 += value;
      }
      
    }
  }
  return quadrants_1 * quadrants_2 * quadrants_3 * quadrants_4 ;
} 

std::vector<Coordinates> Calculate_position_after_n_seconds(std::vector<Robot>& input, int n, int wide, int tall) {
  int robot_velocites_x =0;
  int robot_velocites_y =0;
  std::vector<Coordinates> coordinates; 
  for (auto robot : input) {
    int postion_x = (n * robot.velocities.x + robot.positions.x) % wide;
    int postion_y = (n * robot.velocities.y + robot.positions.y) % tall;

    if (postion_x < 0) {
      postion_x = wide + postion_x;
    } 
    if (postion_y < 0) {
      postion_y = tall + postion_y;
    } 
    coordinates.push_back({postion_x,postion_y});
  }
  return coordinates;
}

void Print_Fild(std::vector<std::vector<int>>& playfild,auto& myfile) {

  
  for (auto filds : playfild) {
    for (auto play : filds) {
      if (play != 0) {
        myfile << play;
      } else {
        myfile << '.';
      }
       
    } 
    myfile << "\n";
  }
  
}

int task1(std::vector<Robot>& input ,int wide, int tall) {
  int sum = 0;  
  //test Fild 11 / 7 Real Fild 101 / 103
  std::vector<Coordinates> ergs = Calculate_position_after_n_seconds(input,100,wide,tall);
  std::vector<std::vector<int>> playfild = CreatePlay(wide,tall,0);
  Place_robot_on_start_position(ergs,playfild);
  sum = Count_robots_in_quadrant(playfild);
    
  return sum; 
}


bool search_frame_x(std::vector<std::vector<int>>& playfild, int n, int schritt_große) {
int sum =0;  
  for (int y=0+n; y < n+schritt_große; y++) {
    for (int x=0; x < playfild.size(); x++) {
      if (playfild[y][x] == 1) {
        sum++;
      } 
    } 
  }
  if (sum > 200) {
    return true; 
  }
  return false;
}

bool search_frame_y(std::vector<std::vector<int>>& playfild, int n, int schritt_große) {
int sum =0;  
  for (int y=0; y < playfild.size(); y++) {
    for (int x=0+n; x < n+schritt_große; x++) {
      if (playfild[y][x] == 1) {
        sum++;
      } 
    } 
  }
  if (sum > 200) {
    return true; 
  }
  return false;
}

bool find_possible_trees(std::vector<std::vector<int>>& playfild) {
  int schritt_große = 25; 
  for (int n =0; n < 101-25; n=n+schritt_große) {
    if(search_frame_x(playfild,n,schritt_große) && search_frame_y(playfild,n,schritt_große)) {
      return true; 
    }
  }
  return false; 
}


long long task2(std::vector<Robot>& input,int wide, int tall) {
  unsigned long long sum = 0;  
  std::ofstream myfile; 
  myfile.open ("print.txt");


  for (int x =0; x < 1000000; x++) {
    std::vector<Coordinates> ergs = Calculate_position_after_n_seconds(input,x,wide,tall);
    std::vector<std::vector<int>> playfild = CreatePlay(wide,tall,0);
    Place_robot_on_start_position(ergs,playfild);
    if(find_possible_trees(playfild)) {
    myfile << "---------------------------------" << x << "---------------------------------" << std::endl;
    Print_Fild(playfild,myfile);
    myfile << "---------------------------------" << x << "---------------------------------" << std::endl; 
    }

  }
  myfile.close();  
  return sum; 
}


int main() {
  
  std::vector<Robot> input_print_rules = Read_Print_Input("input.txt");
  //std::vector<Claw_Machine> input_print_rules2 = Read_Print_Input2("input.txt");
  //int task1_num = task1(input_print_rules,11,7);
  //int task1_num = task1(input_print_rules,101,103);
  int task2_num =task2(input_print_rules,101,103);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}