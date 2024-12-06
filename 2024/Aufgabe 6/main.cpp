#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

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

int task2(std::vector<std::vector<int>>& input_print_rules, std::vector<std::vector<int>> input_print) {
  int sum =0; 
  int sum2 = 0; 

  for (int i =0; i < input_print.size(); i++) {

    bool Rules_ok = false; 
      for (int t = 0; t < input_print[i].size(); t++) {
        
        Rules_ok = Check_Rules_for_input(input_print_rules, input_print[i], t);
        
        if (!Rules_ok) {
          break; 
        }
      }
    

    if (Rules_ok) {
      sum += input_print[i][(input_print[i].size()/2)];
    }
    else {
      bool secund_test = false; 
      std::vector<int> newvector;
      do {
        newvector = Check_Rules_for_input_and_Change_Positions(input_print_rules, input_print[i]);
        for (int t = 0; t < newvector.size(); t++) {
        
          secund_test = Check_Rules_for_input(input_print_rules, newvector, t);
          
          if (!secund_test) {
            break; 
          }
      }
      }while(secund_test == false);
      sum2 += newvector[(newvector.size()/2)];

    }

  }
  //int task1_num = task1(input_print_rules, input_print);
  return sum2 +sum; 
}

int main() {
  

  std::vector<std::vector<char>> input_print_rules = Read_Print_Input("input.txt");

  int task1_num = task1(input_print_rules);
  //int task2_num =task2(input_print_rules, input_print);

  std::cout << "Ergebniss: " << task1_num << std::endl; 
  

return 0;
}