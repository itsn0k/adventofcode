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
  

bool Check_Rules_for_input(std::vector<std::vector<int>>& input_print_rules, std::vector<int>& input_print, int t) {

  int value = input_print[t]; 
  for (int h = 0; h < input_print_rules.size(); h++) {
    int input_print_rule_value = input_print_rules[h][0];
    int input_print_rule_value_litte = input_print_rules[h][1];

    if (input_print_rule_value == value) {
      for (int z = 0; z < t; z++) {
      int input_check_value = input_print[z];

        if (input_check_value == input_print_rule_value_litte) {
          return false; 
        }
      }
    }
  }
  return true; 
}

std::vector<int> Check_Rules_for_input_and_Change_Positions(std::vector<std::vector<int>>& input_print_rules, std::vector<int>& input_print) {

  std::vector<int> newvector; 
  newvector.push_back(input_print[0]);

  for (int w = 1; w < input_print.size(); w++) {
    int insert_value = -1; 
    int value = input_print[w]; 
    
    int length = newvector.size(); 
    for (int u = 0; u < length; u++) {
      for (int h = 0; h < input_print_rules.size(); h++) {
        int input_print_rule_value = input_print_rules[h][0];
        int input_print_rule_value_litte = input_print_rules[h][1];
        
        if (input_print_rule_value_litte == value ) {
          int first_value = newvector[u];

          if(input_print_rule_value == first_value && (insert_value < u || insert_value == -1)) {
            insert_value = u; 
          }
        }
      }
  
    }

    if (insert_value == -1) {
      newvector.insert(newvector.begin(),value);
    }
    else {
      newvector.insert(newvector.begin()+1 + insert_value,value);
    }
    
    

  }
  
  return newvector;
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
};

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

bool Guard_Move_Forword(std::vector<std::vector<char>>& input, Coordinates& current_position) {

  for (int i =current_position.y; i < input.size(); i++) {

    for (int t = current_position.x; t < input[i].size(); t++) {
      char value = input[i][t];
      if (value == '^') {
        if (i-1 >= 0 ) {
          char to_move_value = input[i-1][t];

          if (to_move_value == '#') {
            input[i][t] = '>';
            return false; 
          }
          else {
            input[i-1][t] = '^';
            input[i][t] = 'X';
            current_position.x = t;
            current_position.y = i-1;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == '>')
      {
        if (t+1 < input[i].size()) {
          char to_move_value = input[i][t+1];

          if (to_move_value == '#') {
            input[i][t] = 'v';
            return false; 
          }
          else {
            input[i][t+1] = '>';
            input[i][t] = 'X';
            current_position.x = t+1;
            current_position.y = i;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == '<')
      {
        if (t-1 >= 0) {
          char to_move_value = input[i][t-1];

          if (to_move_value == '#') {
            input[i][t] = '^';
            return false; 
          }
          else {
            input[i][t-1] = '<';
            input[i][t] = 'X';
            current_position.x = t-1;
            current_position.y = i;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == 'v')
      {
        if (i+1 < input.size()) {
          char to_move_value = input[i+1][t];

          if (to_move_value == '#') {
            input[i][t] = '<';
            return false; 
          }
          else {
            input[i+1][t] = 'v';
            input[i][t] = 'X';
            current_position.x = t;
            current_position.y = i+1;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
    }
  }
  return true; 
}

bool Guard_Move_Forword2(std::vector<std::vector<char>>& input, Coordinates& current_position) {

  for (int i =current_position.y; i < input.size(); i++) {

    for (int t = current_position.x; t < input[i].size(); t++) {
      char value = input[i][t];
      if (value == '^') {
        if (i-1 >= 0 ) {
          char to_move_value = input[i-1][t];

          if (to_move_value == '#') {
            input[i][t] = '>';
            return false; 
          }
          else {
            input[i-1][t] = '^';
            input[i][t] = '|';
            current_position.x = t;
            current_position.y = i-1;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == '>')
      {
        if (t+1 < input[i].size()) {
          char to_move_value = input[i][t+1];

          if (to_move_value == '#') {
            input[i][t] = 'v';
            return false; 
          }
          else {
            input[i][t+1] = '>';
            input[i][t] = '-';
            current_position.x = t+1;
            current_position.y = i;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == '<')
      {
        if (t-1 >= 0) {
          char to_move_value = input[i][t-1];

          if (to_move_value == '#') {
            input[i][t] = '^';
            return false; 
          }
          else {
            input[i][t-1] = '<';
            input[i][t] = '-';
            current_position.x = t-1;
            current_position.y = i;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == 'v')
      {
        if (i+1 < input.size()) {
          char to_move_value = input[i+1][t];

          if (to_move_value == '#') {
            input[i][t] = '<';
            return false; 
          }
          else {
            input[i+1][t] = 'v';
            input[i][t] = '|';
            current_position.x = t;
            current_position.y = i+1;
            return false; 
          }
        }
        input[i][t] = 'X';
        return true; 
      }
      else if (value == 'X')
      {
        return true; 
      }
      
    }
  }
  return true; 
}


int Count_X(std::vector<std::vector<char>>& input) {
  int sum =0 ; 
  for (int i = 0; i < input.size(); i++) {

    for (int t = 0; t< input[i].size(); t++) {
      char value = input[i][t];

      if (value == 'X') {
        sum++;
      }
    }
  }
  return sum; 
}

int task1(std::vector<std::vector<char>>& input) {
  

  Coordinates start_postion = Find_Start_Postion(input);

  bool Guard_has_left_map = false; 

  while (Guard_has_left_map == false)
  {
    Guard_has_left_map = Guard_Move_Forword(input, start_postion);
  }
  
  int sum = Count_X(input);

  return sum; 
}

int task2(std::vector<std::vector<char>>& input) {
  Coordinates start_postion = Find_Start_Postion(input);
  Coordinates current_position = start_postion;
  Coordinates secend_position = {-1,-1};
  int sum = 0; 
  
  for (int n = 0; n < input.size(); n++) {

    for (int m = 0; m < input[n].size(); m++) {
      char value = input[n][m];
      if (value == '.') {
        std::vector<std::vector<char>> temp_input = input;
        current_position = start_postion;
        temp_input[n][m] = '#';
        bool Guard_has_left_map = false; 

        while (Guard_has_left_map == false)
        {
          Guard_has_left_map = Guard_Move_Forword2(temp_input, current_position);

          if (current_position != start_postion && secend_position == Coordinates {-1,-1}) {
            secend_position = current_position; 
          }
          else if (current_position == start_postion && secend_position != Coordinates {-1,-1})
          {
            Guard_has_left_map = Guard_Move_Forword2(temp_input, current_position);

            if (current_position == secend_position) {
                sum++;
                Guard_has_left_map = true; 
            }
          }
        }

      }
    }
  }

  return sum; 
}

int Find_waypoints_index(std::vector<Coordinates>& waypoints, Coordinates to_find_value) {
    for (int u = 0; u < waypoints.size(); u++) {
      if (to_find_value == waypoints[u]) {
        return u; 
      }
    }
    return -1; 
}

bool comp(int a, int b) {
    return a >= b;
}

bool Loop_Check(std::vector<int> waypoints_counters) {

  std::sort(waypoints_counters.begin(), waypoints_counters.end(), comp);
  
  if (waypoints_counters.size() == 0) {
    return false; 
  }

  for (int u = 0; u < waypoints_counters.size() && u < 2; u++) {
    int value =  waypoints_counters[u]; 
    if (value < 7) {
      return false; 
    }
  }
    return true; 
}

int task3(std::vector<std::vector<char>>& input) {
  Coordinates start_postion = Find_Start_Postion(input);
  Coordinates current_position = start_postion; 
  bool Guard_has_left_map = false; 

  std::vector<Coordinates> Possible_obstacle_positions;
  std::vector<std::vector<char>> temp_input = input;

  Coordinates previous_position = {-1,-1}; 
  while (Guard_has_left_map == false)
  {
    
    Guard_has_left_map = Guard_Move_Forword(temp_input, current_position);
    if(current_position != start_postion && Find_waypoints_index(Possible_obstacle_positions,current_position) == -1) {
      Possible_obstacle_positions.push_back(current_position);
    }
  }
  
  int sum = 0; 
  for (int i = 0; i < Possible_obstacle_positions.size(); i++) {
    std::vector<Coordinates> waypoints;
    std::vector<int> waypoints_counters; 
    
    temp_input = input;
    current_position = start_postion;
    Coordinates previous_position = {-1,-1};
    temp_input[Possible_obstacle_positions[i].y][Possible_obstacle_positions[i].x] = '#';
    Coordinates secend_position = {-1,-1};

    bool Guard_has_left_map = false; 

    while (Guard_has_left_map == false)
    {
      Guard_has_left_map = Guard_Move_Forword2(temp_input, current_position);
      if (current_position != start_postion && secend_position == Coordinates {-1,-1}) {
        secend_position = current_position; 
      }
      else if (Loop_Check(waypoints_counters)) //current_position == secend_position  && secend_position != Coordinates {-1,-1} && start_postion == previous_position
      {
        sum++;
        Guard_has_left_map = true; 
      }
      else if (current_position == previous_position)
      {
        int index_waypoints = Find_waypoints_index(waypoints, current_position);

        if (index_waypoints < 0) {
          waypoints.push_back(current_position);
          waypoints_counters.push_back(0);
        }
        else {
          waypoints_counters[index_waypoints]++; 
        }
      }
      previous_position = current_position; 
    }
    waypoints.erase(waypoints.begin(), waypoints.end());
    waypoints_counters.erase(waypoints_counters.begin(), waypoints_counters.end());

  }

  return sum; 
}

int main() {
  

  std::vector<std::vector<char>> input_print_rules = Read_Print_Input("input.txt");

  //int task1_num = task1(input_print_rules);
  int task2_num =task3(input_print_rules);

  std::cout << "Ergebniss: " << task2_num << std::endl; 
  

return 0;
}