#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>


// Task function

std::vector<std::string> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<std::string> output;
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;

    while (std::getline(file, line)) {

      std::istringstream iss(line);

      int counter = 0; 
      for (int h = 0; h < line.length(); h++) {
        char input_value = line[h];
        int value = input_value - '0';

        for (int c = 0; c < value; c++) {
          if (h % 2 == 0) {
            //File
            output.push_back(std::to_string(counter)); 

            
          } else {
            //Space
            output.push_back(".");
          }
        } 

        if (h%2 ==0) {
          counter++; 
        }
      }
    }
    file.close();
    }

  //Logic Path Finding
  return output;
}

long long Check_Sum(std::vector<std::string>& input) {
  long long sum =0; 

  for(long long i = 1; i < input.size(); i++) {
    std::string input_value = input[i];
    if (input_value == ".") {
      return sum; 
    } 
    int value = std::stoi(input_value);



    sum += i * value;


  }
  return sum; 
}

long long Check_Sum2(std::vector<std::string>& input) {
  long long sum =0; 

  for(long long i = 1; i < input.size(); i++) {
    std::string input_value = input[i];
    if (input_value != ".") {
      int value = std::stoi(input_value);
      sum += i * value;
    } 
  }
  return sum; 
}

int task1(std::vector<std::string>& input) {
  
  long long counter =0; 
  for (long long i = input.size()-1; i > counter; i--) {
    std::string value = input[i];
    if (value != ".") {
      for (long long h = 0 + counter; h < input.size(); h++) {
            std::string secound_value = input[h];

            if (secound_value == "." && h < i) {
              input[h] = value; 
              input[i] = secound_value; 
              counter = h; 
              break; 
            }
      }
    }    
  }

  long long sum = Check_Sum(input);

  return sum; 
}


int task2(std::vector<std::string>& input) {
  
  std::string temp = "";
  long long counter =0; 
  
  int temp_counter = 0;
  for (long long i = input.size()-1; i > 0; i--) {
    std::string value = input[i];
    std::string secund_value = input[i-1];

    if (temp == "" && value != ".") {
      temp = value; 
    }

    if (temp == value) {
      temp_counter++;
    }

    if (temp != secund_value ) {
      if (value != ".") {
        int counter_space = 0; 
            for (long long h = 0; h <= i; h++) {
                  std::string secound_value2 = input[h];

                  if (secound_value2 == ".") {
                    counter_space++; 

                    if (counter_space == temp_counter) {
                      for (int p =temp_counter; p > 0; p--) {
                        input[h+1-p] = temp; 
                        input[i-1+p] = secound_value2; 
                      }
                      break; 
                    }
                    
                  }
                  else {
                    counter_space=0; 
                  }
            }
        }
        temp = secund_value; 
        temp_counter =0; 
    }
    
  }

  long long sum = Check_Sum2(input);

  return sum; 
}

int main() {
  
  std::vector<std::string> input_print_rules = Read_Print_Input("input.txt");

  //long long task1_num = task1(input_print_rules);
  long long task2_num =task2(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}