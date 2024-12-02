#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

// Task function
void task1_old(std::vector<std::vector<int>>& input) {
  int sum = 0;
  for (int i = 0; i < input.size(); i++ ) {
    int counter_for_negative_values = 0; 
    int counter_for_error_values = 0; 
    for (int t = 1; t <input[i].size(); t++ ) {
      int previous_value = input[i][t-1];
      int value = input[i][t];
      int interim_result = previous_value - value;

      if (interim_result >= -3 &&  interim_result <= 3 && interim_result != 0 ) {
        if (interim_result < 0) {
              counter_for_negative_values++;
            }
      }
      else
      {
          counter_for_error_values++;
      }
    }

    int counter_of_possible_combinations = input[i].size() -1;
    if ((counter_for_negative_values - counter_of_possible_combinations == 0 && counter_for_error_values == 0) || (counter_for_negative_values == 0 && counter_for_error_values == 0)) {
      sum++;
    }
  }
  
  std::cout << "The Count of the Correct List are: " << sum << std::endl;
}

std::vector<int> Create_Vektor_for_Check(std::vector<int>& input) {
  std::vector<int> result_round;
      for (int t = 1; t <input.size(); t++ ) {
        int previous_value = input[t-1];
        int value = input[t];
        int interim_result = previous_value - value;
        result_round.push_back(interim_result);
      }
      return result_round;
}

std::vector<std::vector<int>> Create_Vektors_for_Check(std::vector<std::vector<int>>& input) {
  std::vector<std::vector<int>> result_vec;
    for (int i = 0; i < input.size(); i++ ) {
      result_vec.push_back(Create_Vektor_for_Check(input[i]));
    }
  return result_vec;
}

bool Check_Vektor_if_Safe (std::vector<int>& result_vec) {
  int counter_negative_values = 0;
    int counter_posstive_values = 0;
    int step_to_big_error = 0; 
    int zerror_error =0; 
    for (int t = 0; t < result_vec.size(); t++ ) {

      int value = result_vec[t];
      if (value == 0) {
        zerror_error++;
      }
      else if (value < 0) {
        counter_negative_values++;
        value *= -1;
      }
      else 
      {
        counter_posstive_values++;
      }

      if (value > 3 ) {
    
        step_to_big_error++; 
      }
    }

    int error_tolerance = 0; 
    int counter_of_possible_combinations = result_vec.size();
    if ((step_to_big_error == 0 && zerror_error-error_tolerance <= 0) && (counter_of_possible_combinations == counter_negative_values || counter_of_possible_combinations == counter_posstive_values || counter_posstive_values+error_tolerance >= counter_of_possible_combinations || counter_negative_values+error_tolerance >= counter_of_possible_combinations) ) {
        return true;
    }
    else {
      return false; 
    }
}

bool Check_Vektor_if_Safe_with_error(std::vector<int>& result_vec, std::vector<int>& input) {
  for (int t = 0; t < result_vec.size(); t++ ) {
            int first_value = result_vec[0];
            int value = result_vec[t];

            if (value == 0 || (value < 3 && value > -3) || (first_value < 0 && value > 0) || (first_value > 0 && value < 0) ) {
          
                for (int u = 0; u < input.size(); u++) {
                  std::vector<int> result_round;
                  for (int z =0; z < input.size(); z++) {
                    int skip_index = (t+u) % input.size();
                    if (z == skip_index) {
                      z++;
                    }
                    if (z < input.size()) {
                      int value = input[z];
                      result_round.push_back(value);
                    }
                    
                  }

                  std::vector<int> result_round2 = Create_Vektor_for_Check(result_round);
                  bool isSafe = Check_Vektor_if_Safe(result_round2);
                  if (isSafe) {
                    return true;
                  }
                  
                }
              return false; 
            }

          }
    return false; 
}


void task1(std::vector<std::vector<int>>& input) {
  int sum = 0;
  std::vector<std::vector<int>> result_vec = Create_Vektors_for_Check(input);
  
  for (int i = 0; i < result_vec.size(); i++ ) {
    bool isSafe = Check_Vektor_if_Safe(result_vec[i]);

    if (isSafe) {
      sum++;
    }

  }

  std::cout << "The Count of the Correct List are: " << sum << std::endl;
}


void task2(std::vector<std::vector<int>>& input) {
  int sum = 0;
  std::vector<std::vector<int>> result_vec = Create_Vektors_for_Check(input);
  
  for (int i = 0; i < result_vec.size(); i++ ) {
    bool isSafe = Check_Vektor_if_Safe(result_vec[i]);

    if (isSafe) {
      sum++;
    }
    else {
      bool isSafe2 = Check_Vektor_if_Safe_with_error(result_vec[i],input[i]);

      if (isSafe2) {
        sum++;
      }
    }
  }

  std::cout << "The Count of the Correct List are: " << sum << std::endl;
}

int main() {
    
std::string FILENAME = "input.txt";

//Read Input 
std::ifstream file(FILENAME);
if (file.is_open()) {

  std::string line;
  std::vector<std::vector<int>> a_tockens;

  while (std::getline(file, line)) {
    std::vector<int> line_tockens; 
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' ')) {  // but we can specify a different one
      if (token != "") {
        line_tockens.push_back(std::stoi(token)); //std::stoi String to Int
      } 

    }
    a_tockens.push_back(line_tockens);
  }
  file.close();
  //Logic Path Finding
  task1(a_tockens);
  task2(a_tockens);
  
}

return 0;
}