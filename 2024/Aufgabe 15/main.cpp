#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>


// Task function

struct Puzzle_Input {
  std::vector<std::vector<char>> map;
  std::string instructions; 
};


Puzzle_Input Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<std::vector<char>> a_tockens;
  std::string instructions = "";
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;
    
    bool Start_instructions = false; 

    while (std::getline(file, line)) {
      if (line == "") {
        Start_instructions = true; 
      }

      if (Start_instructions) {
        for (int h = 0; h < line.length(); h++) {
          if (line[h] != '\n') {
            instructions += line[h];
          }
        }
      } else {
        std::vector<char> line_tockens; 
        std::istringstream iss(line);

        for (int h = 0; h < line.length(); h++) {
          line_tockens.push_back(line[h]);
        }
          
        a_tockens.push_back(line_tockens);
      }
      
    }
    file.close();
  }
    
    //Logic Path Finding
  return {a_tockens,instructions};
}

Puzzle_Input Read_Print_Input2(std::string filename) {
  //Read Input 
  std::vector<std::vector<char>> a_tockens;
  std::string instructions = "";
  std::ifstream file(filename);
  if (file.is_open()) {
  
    std::string line;
    
    bool Start_instructions = false; 

    while (std::getline(file, line)) {
      if (line == "") {
        Start_instructions = true; 
      }

      if (Start_instructions) {
        for (int h = 0; h < line.length(); h++) {
          if (line[h] != '\n') {
            instructions += line[h];
          }
        }
      } else {
        std::vector<char> line_tockens; 
        std::istringstream iss(line);

        for (int h = 0; h < line.length(); h++) {

          if (line[h] != '@' && line[h] != 'O') {
            line_tockens.push_back(line[h]);
            line_tockens.push_back(line[h]);
          } else if (line[h] == '@') {
            line_tockens.push_back(line[h]);
            line_tockens.push_back('.');
          } else if (line[h] == 'O')
          {
            line_tockens.push_back('[');
            line_tockens.push_back(']');
          }
          
        }
          
        a_tockens.push_back(line_tockens);
      }
      
    }
    file.close();
  }
    
    //Logic Path Finding
  return {a_tockens,instructions};
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

Coordinates Find_Start_Postion(std::vector<std::vector<char>>& input) {

  int x = 0; 
  int y = 0; 

  for (int i =0; i < input.size(); i++) {

    for (int t = 0; t < input[i].size(); t++) {
      char value = input[i][t];
      if (value == '@') {
        return Coordinates {t,i};
      }
    }

  }
  return Coordinates {-1,-1};
}

int Calculate_GPS_coordinate(std::vector<std::vector<char>>& input) {
  int sum =0 ; 
  for (int i = 0; i < input.size(); i++) {

    for (int t = 0; t< input[i].size(); t++) {
      char value = input[i][t];

      if (value == 'O') {
        sum += 100*i + t;
      }
    }
  }
  return sum; 
}


int Check_Next(std::vector<std::vector<char>>& input, Coordinates position) {
  if (position.y < input.size()) {
    if (position.x < input[position.y].size()) {
      char value = input[position.y][position.x];
      if (value == '#') {
        return 2; 
      } else if (value == 'O')
      {
        return 0;
      } else {
        return 1; 
      }
    }
  }
}

Coordinates Move(std::vector<std::vector<char>>& input, Coordinates current_postion, Coordinates to_move) {
  if ((current_postion.y + to_move.y) < input.size()) {
    if ((current_postion.x + to_move.x) < input[(current_postion.y + to_move.y)].size()) {
      
      int can_move = -1;
      bool zero_spotet = false; 

      Coordinates plan_postion = to_move + current_postion;
      Coordinates to_move_postion;
      while (can_move < 1) {
        if (can_move == 0) {
          zero_spotet = true; 
          if        (to_move.x == 0 && to_move.y > 0) {
            to_move.y++;
          } else if (to_move.x == 0 && to_move.y < 0)
          {
            to_move.y--;
          } else if (to_move.y == 0 && to_move.x > 0)
          {
            to_move.x++;
          } else if (to_move.y == 0 && to_move.x < 0)
          {
            to_move.x--;
          }   
        }
        to_move_postion = current_postion + to_move;
        can_move = Check_Next(input,to_move_postion);
      }

      if(zero_spotet == false && can_move != 2) {
        input[plan_postion.y][plan_postion.x] = input[current_postion.y][current_postion.x];
        input[current_postion.y][current_postion.x] = '.';
        return plan_postion; 
      } 
      if (zero_spotet && can_move != 2)
      {
        input[to_move_postion.y][to_move_postion.x] = input[plan_postion.y][plan_postion.x];
        input[plan_postion.y][plan_postion.x] = input[current_postion.y][current_postion.x];
        input[current_postion.y][current_postion.x] = '.';
        return plan_postion; 
      }
      
      return current_postion; 
    }
  }
}

int task1(Puzzle_Input input) {
  
  Coordinates start_postion = Find_Start_Postion(input.map);

  if (start_postion.x == -1 && start_postion.y == -1) {
    return 0; 
  }

  Coordinates current_postion = start_postion;
  for (int n = 0;n < input.instructions.length(); n++) {
    char value = input.instructions[n];

    if(value == '^') {
      current_postion = Move(input.map,current_postion,{0,-1});
    } else if (value == '<') {
      current_postion = Move(input.map,current_postion,{-1,0});
    } else if (value == '>') {
      current_postion = Move(input.map,current_postion,{1,0});
    } else if (value == 'v') {
      current_postion = Move(input.map,current_postion,{0,1});
    }
  }
  
  int sum = Calculate_GPS_coordinate(input.map);

  return sum; 
}


int Calculate_GPS_coordinate2(std::vector<std::vector<char>>& input) {
  int sum =0 ; 
  for (int i = 0; i < input.size(); i++) {

    for (int t = 0; t< input[i].size(); t++) {
      char value = input[i][t];

      if (value == '[') {
        sum += 100*i + t;
      }
    }
  }
  return sum; 
}

int Check_Next2(std::vector<std::vector<char>>& input, Coordinates position) {
  if (position.y < input.size()) {
    if (position.x < input[position.y].size()) {
      char value = input[position.y][position.x];
      if (value == '#') {
        return 2; 
      } else if (value == '[' || value == ']') {
        return 0;
      } else {
        return 1; 
      }
    }
  }
}

Coordinates Add_One_to_Direction(Coordinates to_move) {
 
  return to_move;
}

bool Find_Box_Left(std::vector<std::vector<char>> input, Coordinates cord ,std::vector<Coordinates>& memo) {
  char value = input[cord.y][cord.x];
  input[cord.y][cord.x] = 'X';

  if (value == ']' || value == '[') {
    int check_value = Check_Next2(input,{cord.x-1,cord.y});
    
    memo.push_back(cord);
    
    if (check_value == 2) {
      return false; 
    } 

    bool f2 = Find_Box_Left(input, {cord.x-1,cord.y} ,memo);

    return f2; 
  }

  return true; 
}

bool Find_Box_Right(std::vector<std::vector<char>> input, Coordinates cord ,std::vector<Coordinates>& memo) {
  char value = input[cord.y][cord.x];
  input[cord.y][cord.x] = 'X';

  if (value == ']' || value == '[') {
    int check_value = Check_Next2(input,{cord.x+1,cord.y});
    
    memo.push_back(cord);
    
    if (check_value == 2) {
      return false; 
    } 

    bool f2 = Find_Box_Right(input, {cord.x+1,cord.y} ,memo);

    return f2; 
  }

  return true; 
}

bool Find_Box_Up(std::vector<std::vector<char>> input, Coordinates cord ,std::vector<Coordinates>& memo, int level) {
  char value = input[cord.y][cord.x];
  input[cord.y][cord.x] = 'X';

  if (value == '[' || value == ']') {
    int check_value = Check_Next2(input,{cord.x,cord.y-1});

    memo.push_back(cord);
    
    if (check_value == 2) {
      return false; 
    } 
    bool f1 = Find_Box_Up(input, {cord.x,cord.y-1} ,memo,level+1);
    bool f2 = true;
    bool f3 = true;
    if (value == '[') {
      f2 = Find_Box_Up(input, {cord.x+1,cord.y} ,memo,level);
    }
    if ( value == ']') {
      f3 = Find_Box_Up(input, {cord.x-1,cord.y} ,memo,level);
    }

    return f1 && f2 && f3; 
  }
  return true; 
}

bool Find_Box_Down(std::vector<std::vector<char>> input, Coordinates cord ,std::vector<Coordinates>& memo, int level) {
  char value = input[cord.y][cord.x];
  input[cord.y][cord.x] = 'X';
  if (value == '[' || value == ']') {
    int check_value = Check_Next2(input,{cord.x,cord.y+1});

    memo.push_back(cord);
    
    if (check_value == 2) {
      return false; 
    } 
    bool f1 = Find_Box_Down(input, {cord.x,cord.y+1} ,memo,level+1);
    bool f2 = true;
    bool f3 = true;
    if (value == '[') {
      f2 = Find_Box_Down(input, {cord.x+1,cord.y} ,memo,level);
    }
    if ( value == ']') {
      f3 = Find_Box_Down(input, {cord.x-1,cord.y} ,memo,level);
    }
    return f1 && f2 && f3; 
  }
  
  return true; 
}

bool comp(Coordinates a, Coordinates b) {
    return a.x + a.y * a.y < b.x + b.y * b.y;
}

bool comp2(Coordinates a, Coordinates b) {
    return a.x + a.y * a.y > b.x + b.y * b.y;
}

Coordinates Move2(std::vector<std::vector<char>>& input, Coordinates current_postion, Coordinates to_move) {
  if ((current_postion.y + to_move.y) < input.size()) {
    if ((current_postion.x + to_move.x) < input[(current_postion.y + to_move.y)].size()) {
      
      int can_move = -1;
      bool zero_spotet = false; 
      int count =0; 
      Coordinates plan_postion = to_move + current_postion;
      Coordinates to_move_postion;
      Coordinates temp_move = to_move; 
      std::vector<Coordinates> memo;
      while (can_move < 1) {
        if (can_move == 0) {
          zero_spotet = true; 
          count++;
          if        (to_move.x == 0 && to_move.y > 0) {
            to_move.y++;
          } else if (to_move.x == 0 && to_move.y < 0)
          {
            to_move.y--;    
          } else if (to_move.y == 0 && to_move.x > 0)
          {
            to_move.x++;
          } else if (to_move.y == 0 && to_move.x < 0)
          {
            to_move.x--;
          }  
        }
        to_move_postion = current_postion + to_move;
        can_move = Check_Next2(input,to_move_postion);
      }

      if(zero_spotet == false && can_move != 2) {
        input[plan_postion.y][plan_postion.x] = input[current_postion.y][current_postion.x];
        input[current_postion.y][current_postion.x] = '.';
        return plan_postion; 
      } 
      if (zero_spotet && can_move != 2)
      {

        Coordinates predecessor_to_move_postion = current_postion + temp_move;
        bool boxen_can_be_moved = false; 
        if (temp_move.x == 0 && temp_move.y < 0) {
          boxen_can_be_moved = Find_Box_Up(input,(predecessor_to_move_postion),memo,0);
          sort(memo.begin(), memo.end(), comp);
          memo.erase(std::unique(memo.begin(),memo.end()),memo.end());
        } else if (temp_move.x == 0 && temp_move.y > 0) {
          boxen_can_be_moved = Find_Box_Down(input,(predecessor_to_move_postion),memo,0);
          sort(memo.begin(), memo.end(), comp2);
          memo.erase(std::unique(memo.begin(),memo.end()),memo.end());
        } else if (temp_move.y == 0 && temp_move.x < 0) {
          boxen_can_be_moved = Find_Box_Left(input,(predecessor_to_move_postion),memo);
          sort(memo.begin(), memo.end(), comp);
          memo.erase(std::unique(memo.begin(),memo.end()),memo.end());
        } else if (temp_move.y == 0 && temp_move.x > 0) {
          boxen_can_be_moved = Find_Box_Right(input,(predecessor_to_move_postion),memo);
          sort(memo.begin(), memo.end(), comp2);
          memo.erase(std::unique(memo.begin(),memo.end()),memo.end());
        }
        
        if (boxen_can_be_moved) {
          for (auto me : memo) {
            Coordinates new_postion = me + temp_move;
            input[new_postion.y][new_postion.x] = input[me.y][me.x];
            input[me.y][me.x] = '.';
          }
          input[plan_postion.y][plan_postion.x] = input[current_postion.y][current_postion.x];
        } else {
          return current_postion; 
        }
          
        input[current_postion.y][current_postion.x] = '.';
        return plan_postion; 
      }
      
      return current_postion; 
    }
  }
}

void Print_Fild(std::vector<std::vector<char>>& playfild) {

  
  for (auto filds : playfild) {
    for (auto play : filds) {
      std::cout << play; 
       
    } 
    std::cout <<  "\n";
  }
}

void Print_Fild(std::vector<std::vector<char>>& playfild, auto& myfile) {

  
  for (auto filds : playfild) {
    for (auto play : filds) {
      myfile << play; 
       
    } 
    myfile <<  "\n";
  }
}

int task2(Puzzle_Input input) {
  
  Coordinates start_postion = Find_Start_Postion(input.map);

  if (start_postion.x == -1 && start_postion.y == -1) {
    return 0; 
  }

  std::ofstream myfile; 
  myfile.open ("print.txt");
  Print_Fild(input.map,myfile);
  Coordinates current_postion = start_postion;
  for (int n = 0;n < input.instructions.length(); n++) {
    char value = input.instructions[n];
    myfile << "------------------" << value << "------------------\n";
    if(value == '^') {
      current_postion = Move2(input.map,current_postion,{0,-1});
    } else if (value == '<') {
      current_postion = Move2(input.map,current_postion,{-1,0});
    } else if (value == '>') {
      current_postion = Move2(input.map,current_postion,{1,0});
    } else if (value == 'v') {
      current_postion = Move2(input.map,current_postion,{0,1});
    }
    Print_Fild(input.map,myfile);
    myfile << "------------------" << "-" << "------------------\n";
  }
  myfile.close(); 
  int sum = Calculate_GPS_coordinate2(input.map);

  return sum; 
}


int main() {
  
  //Puzzle_Input input_print_rules = Read_Print_Input("input.txt");
  //int task1_num = task1(input_print_rules);

  Puzzle_Input input_print_rules = Read_Print_Input2("input.txt");
  int task2_num =task2(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}