#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>
#include <unordered_map>
#include <tuple>


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

struct Claw_Machine {
  Coordinates button_A;
  Coordinates button_B;
  Coordinates prize; 
};

Coordinates Read_Button(std::string line, std::string value_x, std::string value_y) {
  std::string token;
  std::string number_read; 
  Coordinates cord; 
  for (int i =0; i < line.length(); i++) {
    if (line[i] == 'X' || line[i] == 'Y' || line[i] == '+' || line[i] == '+' || line[i] == '=') {
      token += line[i];
    } else if (token == value_x || token == value_y) {
      number_read+= line[i];
    } 

    if (line[i] == ',' && number_read != "" && token == value_x) {
      cord.x = std::stoi(number_read);
      number_read = "";
      token = "";
    } else if (i == line.length()-1 && number_read != "" && token == value_y) {
      cord.y = std::stoi(number_read);
    }
  }
  return cord; 
}

std::vector<Claw_Machine> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<Claw_Machine> claw_machines;
  std::ifstream file(filename);
  if (file.is_open()) {

    std::string line;
    Claw_Machine claw_machine = {};
    int counter =0; 
    while (std::getline(file, line)) {
      std::istringstream iss(line);

      if (line == "") {
        claw_machines.push_back(claw_machine);
        claw_machine = {};
      }

      if (counter % 3 == 0) {
        claw_machine.button_A = Read_Button(line, "X+", "Y+");
        counter++;
      } else if (counter % 3 == 1) {
        claw_machine.button_B = Read_Button(line,"X+", "Y+");
        counter++;
      } else if (counter % 3 == 2) {
        claw_machine.prize = Read_Button(line,"X=", "Y=");
        counter++;
      }
      
    }
    claw_machines.push_back(claw_machine);
    file.close();
  }  
    //Logic Path Finding
  return claw_machines;
}


int euklidischer(int x, int y, std::vector<std::vector<int>>& memo) {
  if (x % y <= 0) {
    return y; 
  } 
  int rest = x%y; 
  memo.push_back({x,x/y,y,rest});
  return euklidischer(y,rest,memo);
}

struct Zahl {
  bool is_minus;
  int counter; 
  int value; 
};

struct Termin_Erweiterter_euklid {
  Zahl a;
  Zahl b; 
};

bool Vorzeichen(bool a, bool b) {
  if (a == b) {
    return false;
  } 
  return true; 
}

Termin_Erweiterter_euklid Erweiterter_euklidischer(std::vector<std::vector<int>>& memo, int search_x_value, int search_y_value) {

  Termin_Erweiterter_euklid term = {{false,1,memo[memo.size()-1][0]},{true,memo[memo.size()-1][1],memo[memo.size()-1][2]}};
  for(int i = memo.size()-2; i >= 0; i--) {

    Termin_Erweiterter_euklid temp_term {
      {
        term.b.is_minus,
        term.b.counter,
        memo[i][0]
      },
      {
        Vorzeichen(term.b.is_minus,true),
        term.b.counter*memo[i][1]+term.a.counter,
        memo[i][2]
      }
    };
    term = temp_term;
    }
  return term; 
}



long long task1(std::vector<Claw_Machine>& input) {
  unsigned long long sum = 0; 

  for (int x =0; x < input.size(); x++) {
    Claw_Machine claw_machine = input[x];
    std::vector<std::vector<int>> memo_x;
    std::vector<std::vector<int>> memo_y;
    int ggt_x =0; 
    int ggt_y =0;
    if (claw_machine.button_A.x > claw_machine.button_B.x) {
      ggt_x = euklidischer(claw_machine.button_A.x, claw_machine.button_B.x,memo_x);
    }
    else {
      ggt_x = euklidischer(claw_machine.button_B.x, claw_machine.button_A.x,memo_x);
    }
    
    if (claw_machine.button_A.y > claw_machine.button_B.y) {
      ggt_y = euklidischer(claw_machine.button_A.y, claw_machine.button_B.y,memo_y);
    } else {
      ggt_y = euklidischer(claw_machine.button_B.y , claw_machine.button_A.y,memo_y);
    }

    if(claw_machine.prize.x % ggt_x == 0 && claw_machine.prize.x % ggt_y == 0) {
      Termin_Erweiterter_euklid term_x = Erweiterter_euklidischer(memo_x,claw_machine.button_A.x,claw_machine.button_B.x);
      Termin_Erweiterter_euklid term_y = Erweiterter_euklidischer(memo_y,claw_machine.button_A.y,claw_machine.button_B.y);
    }

  }
    

  return sum; 
}

long long task2(std::vector<long long>& input) {
  long long sum = 0; 
  

  return sum; 
}


int main() {
  
  std::vector<Claw_Machine> input_print_rules = Read_Print_Input("testinput.txt");

  int task1_num = task1(input_print_rules);
  //long long task2_num =task3(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}