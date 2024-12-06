#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

// Task function

std::vector<std::vector<int>> Read_Print_Input(std::string filename, char delimiter) {
  //Read Input 
  std::vector<std::vector<int>> a_tockens;
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;

    while (std::getline(file, line)) {
      std::vector<int> line_tockens; 
      std::istringstream iss(line);
      std::string token;

      if (line.find(delimiter) != std::string::npos) {

        while (std::getline(iss, token, delimiter)) {  // but we can specify a different one
          std::string string_delimiter = "";
          string_delimiter += delimiter; 
          if (token != string_delimiter) {
            line_tockens.push_back(std::stoi(token));
          }
        }
        a_tockens.push_back(line_tockens);
      }
    }
    file.close();
    //Logic Path Finding
  }
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


int task1(std::vector<std::vector<int>>& input_print_rules, std::vector<std::vector<int>> input_print) {
  int sum =0; 

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

  }

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
  

  std::vector<std::vector<int>> input_print_rules = Read_Print_Input("input.txt", '|');
  std::vector<std::vector<int>> input_print = Read_Print_Input("input.txt", ',');

  int task1_num = task1(input_print_rules, input_print);
  int task2_num =task2(input_print_rules, input_print);

  std::cout << "Ergebniss: " << task2_num - task1_num << std::endl; 
  

return 0;
}