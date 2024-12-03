#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

// Task function

std::string Operation_Mult = "mul(X,Y)"; //8
std::string Operation_do = "do()"; //4
std::string Operation_donot = "don't()"; //7
int main() {
    
std::string FILENAME = "input.txt";

//Read Input 
std::ifstream file(FILENAME);
if (file.is_open()) {

  std::string line;
  int sum = 0;
  int counter_donot = 0; 
  int counter_do = 0; 
  bool instructions_enabled = true;
  while (std::getline(file, line)) {
    std::vector<int> line_tockens; 
    std::istringstream iss(line);
    std::string output;
    int t = 0; 
    std::string nummber_X = "";
    int counter_X = 0; 
    std::string nummber_Y = ""; 
    int counter_Y = 0;  
     
    std::string temp_do_dont = ""; 

    for(int i =0; i < line.length(); i++) {
      char letter = line[i];
      char foreword_letter = ' ';
      if (i < line.length() && line[i+1]) {
        foreword_letter = line[i+1];
      }

      if ((letter == Operation_do[t % 4] || letter == Operation_donot[t % 7]) && (temp_do_dont.length() > 0 || t == 0)) {
        temp_do_dont += letter; 
        t++;
        if (letter == ')') {
          if (temp_do_dont == Operation_donot) {
            instructions_enabled = false; 
            counter_donot++; 
          }
          else {
            instructions_enabled = true; 
            counter_do++; 
          }
          t = 0;
          temp_do_dont = "";
        }
       
      }
      else if (letter == Operation_Mult[t] && (temp_do_dont.length() == 0 || t == 0)) {
        
        if (letter == ')') {
          
          if(instructions_enabled) {
            sum += std::stoi(nummber_X) * std::stoi(nummber_Y); 
          }
          
          nummber_X = ""; 
          nummber_Y = ""; 
          counter_Y = 0; 
          counter_X = 0; 
          t = 0; 
        }
        else {
          t++; 
        }
        
      }
      else if ('X' == Operation_Mult[t] && isdigit(letter))
      {
        nummber_X += letter;
        counter_X++; 
        if(foreword_letter == ',' || counter_X >= 3) {
          t++; 
        }
      }
      else if ('Y' == Operation_Mult[t] && isdigit(letter))
      {
        nummber_Y += letter;
        counter_Y++; 
        if(foreword_letter == ')' || counter_Y >= 3) {
          t++; 
        }
      }
      else{
        t = 0; 
        nummber_X = ""; 
        nummber_Y = ""; 
        counter_Y = 0; 
        counter_X = 0; 
      }
    }
  }
  file.close();
  //Logic Path Finding
  std::cout << "What do you get if you add up all of the results of the multiplications? " << sum << std::endl;
}

return 0;
}