#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

// Task function

std::vector<std::vector<char>> Read_Input(std::string filename) {
  //Read Input 
  std::vector<std::vector<char>> a_tockens;
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;

    while (std::getline(file, line)) {
      std::vector<char> line_tockens; 
      std::istringstream iss(line);
      for (int i = 0; i < line.size(); i++) {  
        line_tockens.push_back(line[i]);
      }
      a_tockens.push_back(line_tockens);
    }
    file.close();
    //Logic Path Finding
    
  }

  return a_tockens;
}


void task1(std::vector<std::vector<char>>& input) {
  std::string searched_word  = "XMAS"; //4
  int sum = 0; 
  int input_height = input.size();
  for (int i =0; i < input_height; i++) {
  int input_width = input[i].size();
    for (int t = 0; t < input_width ; t++) {
      
      char value = input[i][t];

      if (value == searched_word[0]) {
        
        bool can_be_searched_x_postiv  = false; 
        bool can_be_searched_x_negativ = false; 
        bool can_be_searched_y_postiv  = false; 
        bool can_be_searched_y_negativ  = false; 


        if(t+3 < input_width) {
          can_be_searched_x_postiv = true;
        }
        if(t-3 >= 0) {
          can_be_searched_x_negativ = true;
        }
        if(i+3 < input_height) {
          can_be_searched_y_negativ = true; 
        }
        if(i-3 >= 0) {
          can_be_searched_y_postiv = true; 
        }

        std::vector<bool> diagonal_exists {true,true,true,true};
        std::vector<std::vector<int>> diagonal_logic { {1,1}, {1,-1}, {-1,1}, {-1,-1}};
        std::vector<bool> horizontal_exists {true,true};

        std::vector<bool> vertical_exists {true,true};
        std::vector<std::vector<int>> vertical_horizontal_exists_logic { {1,1}, {-1,-1}};

        for (int h = 0; h < 4; h++) {
          int counter =0; 
          for (int y = 0; y < 4; y++) {
            
            if ((h == 0 && can_be_searched_y_negativ && can_be_searched_x_postiv) || (h == 1 && can_be_searched_y_negativ && can_be_searched_x_negativ ) || (h == 2 && can_be_searched_y_postiv && can_be_searched_x_postiv) || (h == 3 && can_be_searched_y_postiv && can_be_searched_x_negativ)) {
              char diagonal_value = input[i + y* diagonal_logic[h][0]][t + y * diagonal_logic[h][1]];

              if (diagonal_value != searched_word[counter]) {
                diagonal_exists[h] = false; 
              }
            }
            else {
              diagonal_exists[h] = false; 
            }

            if (h < 2) {
              if ((h == 0 && can_be_searched_x_postiv) || (h == 1 && can_be_searched_x_negativ) ) {
                char horizontal_value = input[i][t + ( y * vertical_horizontal_exists_logic[h][1])];

                if (horizontal_value != searched_word[counter]) {
                  horizontal_exists[h] = false; 
                }
              }
              else {
                horizontal_exists[h] = false; 
              }
              
              if ((h == 0 && can_be_searched_y_negativ) || (h == 1 && can_be_searched_y_postiv)) {
                char vertical_value = input[i + (y * vertical_horizontal_exists_logic[h][0])][t];

                if (vertical_value != searched_word[counter]) {
                  vertical_exists[h] = false; 
                }
              }
              else {
                vertical_exists[h] = false; 
              }


            }
            counter++;
          }
        }

        sum += std::count(diagonal_exists.begin(), diagonal_exists.end(), true);
        sum += std::count(horizontal_exists.begin(), horizontal_exists.end(), true);
        sum += std::count(vertical_exists.begin(), vertical_exists.end(), true);
      }

    }
  }

  std::cout << "XMAS kommt insgesamt: " << sum << std::endl; 
}

void task2(std::vector<std::vector<char>>& input) {
std::string searched_word  = "MAS"; //4
  int sum = 0; 
  int input_height = input.size();
  for (int i =0; i < input_height; i++) {
  int input_width = input[i].size();
    for (int t = 0; t < input_width ; t++) {
      
      char value = input[i][t];

      if (value == searched_word[1]) {
        
        bool can_be_searched_x_postiv  = false; 
        bool can_be_searched_x_negativ = false; 
        bool can_be_searched_y_postiv  = false; 
        bool can_be_searched_y_negativ  = false; 

        int check_room_large = searched_word.length()/2; 
        if(t+check_room_large < input_width) {
          can_be_searched_x_postiv = true;
        }
        if(t-check_room_large >= 0) {
          can_be_searched_x_negativ = true;
        }
        if(i+check_room_large < input_height) {
          can_be_searched_y_negativ = true; 
        }
        if(i-check_room_large >= 0) {
          can_be_searched_y_postiv = true; 
        }

        std::vector<bool> diagonal_exists {true,true,true,true};
        std::vector<std::vector<int>> diagonal_logic { {1,1}, {1,-1}, {-1,1}, {-1,-1}};

        if (can_be_searched_y_postiv && can_be_searched_y_negativ && can_be_searched_x_negativ && can_be_searched_x_postiv) {
            for (int h = 0; h < 4; h++) {
              int counter =0; 
              for (int y = -1; y < 2; y++) {
                
                if ((h == 0 && can_be_searched_y_negativ && can_be_searched_x_postiv) || (h == 1 && can_be_searched_y_negativ && can_be_searched_x_negativ ) || (h == 2 && can_be_searched_y_postiv && can_be_searched_x_postiv) || (h == 3 && can_be_searched_y_postiv && can_be_searched_x_negativ)) {
                  char diagonal_value = input[i + y* diagonal_logic[h][0]][t + y * diagonal_logic[h][1]];

                  if (diagonal_value != searched_word[counter]) {
                    diagonal_exists[h] = false; 
                  }
                }
                else {
                  diagonal_exists[h] = false; 
                }

                counter++;
              }
            }

            int counter_diagonal_exists = std::count(diagonal_exists.begin(), diagonal_exists.end(), true);

            if (counter_diagonal_exists == 2) {
              sum++;
            }

          }
        }


    }
  }

  std::cout << "X-MAS kommt insgesamt: " << sum << std::endl; 
}

int main() {
  

  std::vector<std::vector<char>> input = Read_Input("input.txt");

  task1(input);
  task2(input);

return 0;
}