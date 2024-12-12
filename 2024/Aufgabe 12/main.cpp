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
        int number = line[h];
        line_tockens.push_back(number);
      }
          
      a_tockens.push_back(line_tockens);
    }
    file.close();
  }
    
    //Logic Path Finding
  return a_tockens;
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

struct View {
  Coordinates coord; 
  char view; 

  public:
    bool operator==(const View& b) {
      return coord == b.coord && view == b.view; 
    }
    bool operator!=(const View& b) {
      return coord != b.coord || view != b.view; 
    }
};

struct Feld {
  char feldtyp; 
  std::vector<Coordinates> coordinates;
};

int Find_Land(std::vector<std::vector<char>>& input, char last_value, int x, int y, Feld& memo) { 

  if ( 0 <= y && y < input.size()) {

    if (0 <= x && x < input[y].size()) {
      char value = input[y][x];

      if (last_value == value) {
        memo.coordinates.push_back({x,y});
        input[y][x] = '_'; 
      
      //Up
      Find_Land(input,last_value, x, y-1 ,memo);

      //Down
      Find_Land(input,last_value, x, y+1,memo);

      //Left
      Find_Land(input,last_value, x-1, y,memo);

      //Rigth
      Find_Land(input,last_value, x+1, y,memo);
      }

      return 0;
    }

  }
  return 0; 
}

std::vector<Feld> Count_Land(std::vector<std::vector<char>> input)  {

std::vector<Feld> Feld_vektor;
char save_char = ' ';
  for (int y =0; y < input.size(); y++) {

    for (int x =0; x < input[y].size(); x++) {
      char value = input[y][x];

      if (save_char == ' ' && value != '_') {
        save_char = value;
      }

      if (save_char == value) {
        //std::vector<std::vector<char>> input_temp = input; 
        Feld feld = {save_char}; 
        Find_Land(input,save_char,x,y,feld);
        Feld_vektor.push_back(feld);
        save_char = ' ';
      }
    }
  }
  return Feld_vektor;
}



int Calulate_perimeter(std::vector<Feld>& felds, int y_length, int x_length) {
  int sum =0; 
  for (int i =0; i < felds.size(); i++) {
    std::vector<Coordinates> coordiantes = felds[i].coordinates;
    int verbindungen =0; 
    for (int t = 0; t < coordiantes.size(); t++) {
      
      for (int z =0; z < coordiantes.size(); z++) {
        
        if (t != z) {
          if (coordiantes[t].x == coordiantes[z].x && (coordiantes[t].y == coordiantes[z].y-1 || coordiantes[t].y == coordiantes[z].y+1 )) {
            verbindungen++;
          } 
          if (coordiantes[t].y == coordiantes[z].y && (coordiantes[t].x == coordiantes[z].x-1 || coordiantes[t].x == coordiantes[z].x+1)) {
            verbindungen++;
          }
        }

      } 
    }
    sum += (coordiantes.size() * 4 - verbindungen) *coordiantes.size(); 
  }
  return sum;
}

int task1(std::vector<std::vector<char>>& input) {
  

  std::vector<Feld> felds = Count_Land(input);

  int sum = Calulate_perimeter(felds, input.size(), input[0].size());
   
  return sum; 
}


int Find_max_x(std::vector<View>& free_seids) {

  int max_x = 0; 
  for (int i =0; i < free_seids.size(); i++) {
    if (free_seids[i].coord.x > max_x) {
      max_x = free_seids[i].coord.x;
    }
  }
  return max_x; 
}
int Find_min_x(std::vector<View>& free_seids) {

  int min_x = 10000; 
  for (int i =0; i < free_seids.size(); i++) {
    if (free_seids[i].coord.x < min_x) {
      min_x = free_seids[i].coord.x;
    }
  }
  return min_x; 
}
int Find_max_y(std::vector<View>& free_seids) {

  int max_y = 0; 
  for (int i =0; i < free_seids.size(); i++) {
    if (free_seids[i].coord.y > max_y) {
      max_y = free_seids[i].coord.y;
    }
  }
  return max_y; 
}
int Find_min_y(std::vector<View>& free_seids) {

  int min_y = 10000; 
  for (int i =0; i < free_seids.size(); i++) {
    if (free_seids[i].coord.y < min_y) {
      min_y = free_seids[i].coord.y;
    }
  }
  return min_y; 
}

int Find_max_x(std::vector<std::vector<View>>& free_seids, char view) {
  int max_x = -1000000;  
  for (int i =0; i < free_seids.size(); i++) {
    for (int h =0; h < free_seids[i].size(); h++) {
      if (free_seids[i][h].coord.x > max_x && free_seids[i][h].view == view) {
        max_x = free_seids[i][h].coord.x;
      }
    }
  }
  return max_x; 
}
int Find_min_x(std::vector<std::vector<View>>& free_seids, char view) {
  int min_x = 1000000; 
  for (int i =0; i < free_seids.size(); i++) {
    for (int h =0; h < free_seids[i].size(); h++) {
      if (free_seids[i][h].coord.x < min_x && free_seids[i][h].view == view) {
        min_x = free_seids[i][h].coord.x;
      }
    }
  }
  return min_x; 
}
int Find_max_y(std::vector<std::vector<View>>& free_seids, char view) {
  int max_y = -1000000; 
  for (int i =0; i < free_seids.size(); i++) {
    for (int h =0; h < free_seids[i].size(); h++) {
      if (free_seids[i][h].coord.y > max_y && free_seids[i][h].view == view) {
        max_y = free_seids[i][h].coord.y;
      }
    }
  }
  return max_y; 
}
int Find_min_y(std::vector<std::vector<View>>& free_seids, char view) {
  int min_y = 1000000; 
  for (int i =0; i < free_seids.size(); i++) {
    for (int h =0; h < free_seids[i].size(); h++) {
      if (free_seids[i][h].coord.y < min_y && free_seids[i][h].view == view) {
        min_y = free_seids[i][h].coord.y;
      }
    }
  }
  return min_y; 
}


bool char_in_view(std::vector<char>& temp_char, char value) {
  for (int h =0; h < temp_char.size(); h++) {
        if (temp_char[h] == value) {
          return true; 
        }
      }
  return false; 
}

std::vector<char> Find_view(std::vector<std::vector<View>>& free_seids) {
  std::vector<char> temp_char; 
    for (int i =0; i < free_seids.size(); i++) {
      for (int h =0; h < free_seids[i].size(); h++) {
        if(!char_in_view(temp_char, free_seids[i][h].view)) {
          temp_char.push_back(free_seids[i][h].view);
        }
      }
  }
  return temp_char;
}

bool View_exists(std::vector<std::vector<View>>& coordiantes, View value) {

  for (int i =0; i < coordiantes.size(); i++) {
    if ((coordiantes[i][0] == value) || (coordiantes[i][1] == value)) {
      return true; 
    } 
  }
return false; 
}

bool memo_check(std::vector<std::vector<View>>& coordiantes, View value1,View value2) {

  for (int i =0; i < coordiantes.size(); i++) {
    if ((coordiantes[i][0] == value1) && (coordiantes[i][1]== value2)) {
      return false; 
    } else if ((coordiantes[i][0] == value2) && (coordiantes[i][1] == value1))
    {
      return false; 
    } 
  }

return true; 
}

int Calulate_perimeter2(std::vector<Feld>& felds, int y_length, int x_length) {
  int sum =0; 
  
  for (int i =0; i < felds.size(); i++) {
    int between_total = 0; 
    std::vector<Coordinates> coordiantes = felds[i].coordinates;

    std::vector<View> free_seids; 
    for (int t = 0; t < coordiantes.size(); t++) {
      bool verbindungen_y_postiv =0; 
      bool verbindungen_y_negativ =0; 
      bool verbindungen_x_postiv =0; 
      bool verbindungen_x_negativ =0;         
      for (int z = 0; z < coordiantes.size(); z++) {
        
        if (t != z) {
          if (coordiantes[t].x == coordiantes[z].x && coordiantes[t].y+1 == coordiantes[z].y ) {
            verbindungen_y_postiv = true; 
          } 
          if (coordiantes[t].x == coordiantes[z].x && coordiantes[t].y-1 == coordiantes[z].y ) {
            verbindungen_y_negativ =true; 
          }
          if (coordiantes[t].y == coordiantes[z].y && coordiantes[t].x+1 == coordiantes[z].x ) {
            verbindungen_x_postiv = true; 
          }
          if (coordiantes[t].y == coordiantes[z].y && coordiantes[t].x-1 == coordiantes[z].x ) {
             verbindungen_x_negativ = true; 
          }
        }
      } 
      if (!verbindungen_y_negativ) {
        free_seids.push_back({{coordiantes[t].x,coordiantes[t].y-1},'^'});
      }
      if (!verbindungen_y_postiv) {
        free_seids.push_back({{coordiantes[t].x,coordiantes[t].y+1},'v'});
      }
      if (!verbindungen_x_negativ) {
        free_seids.push_back({{coordiantes[t].x-1,coordiantes[t].y},'<'});    
      }
      if (!verbindungen_x_postiv) {
        free_seids.push_back({{coordiantes[t].x+1,coordiantes[t].y},'>'});
      }
    }

    int max_x = Find_max_x(free_seids);
    int min_x = Find_min_x(free_seids);
    int max_y = Find_max_y(free_seids);
    int min_y = Find_min_y(free_seids);

    for (int z = min_y; z < max_y+1; z++) {
      std::vector<std::vector<View>> memo_free_seide;
      int paar_exsist_y = 0;
      int counter_y =0; 
      Coordinates last_cornodinate; 
      for (int t = 0; t < free_seids.size(); t++) {
        for (int n = t+1; n < free_seids.size(); n++) {
          if (t != n ) {
            if (free_seids[t].coord.y == z && free_seids[n].coord.y == z && free_seids[t].coord.x != free_seids[n].coord.x) {
              if (( free_seids[t].coord.x == free_seids[n].coord.x-1 && free_seids[t].view == free_seids[n].view) || (free_seids[t].coord.x == free_seids[n].coord.x+1 && free_seids[t].view == free_seids[n].view)) {
                if (memo_check(memo_free_seide, free_seids[t], free_seids[n]))  {
                  if (memo_check(memo_free_seide, free_seids[n], free_seids[t])) {
                    /*
                    if (counter_y == 0) {
                      last_cornodinate = free_seids[n].coord;  
                      paar_exsist_y++; 
                    } else if (View_exists(memo_free_seide, free_seids[t])) {
                      last_cornodinate = free_seids[n].coord; 
                    } else {
                      last_cornodinate = free_seids[n].coord; 
                      paar_exsist_y++;
                    }          
                    counter_y += 2;
                    */  
                    memo_free_seide.push_back({free_seids[t],free_seids[n]});
                  }
                }

              }
            }
          }
        }
      }

      if (memo_free_seide.size() > 0)  {
        std::vector<char> found_view = Find_view(memo_free_seide);
         
        for (auto view : found_view) {
          bool memo_save_start = false;

          int memo_free_seide_max_x = Find_max_x(memo_free_seide,view);
          int memo_free_seide_min_x = Find_min_x(memo_free_seide,view);

          for (int k =memo_free_seide_min_x; k < memo_free_seide_max_x; k++) {
            if(View_exists(memo_free_seide, {{k,z},view}) && memo_save_start == false) {
              memo_save_start = true; 
               paar_exsist_y++;
            }

            if(!View_exists(memo_free_seide, {{k,z},view}) && memo_save_start == true) {
              memo_save_start = false; 
            }
          }
        }
      }
      


      if (paar_exsist_y > 0) {
        between_total += paar_exsist_y;
      }
    }
          
    for (int w = min_x; w < max_x+1; w++) {
      std::vector<std::vector<View>> memo_free_seide;
      int paar_exsist_x = 0;
      int counter_x =0;
      Coordinates last_cornodinate;  
      for (int t = 0; t < free_seids.size(); t++) {
        for (int n = t+1; n < free_seids.size(); n++) {
          if (t != n) {
            if (free_seids[t].coord.x == w && free_seids[n].coord.x == w && free_seids[t].coord.y != free_seids[n].coord.y) {
              if ((free_seids[t].coord.y == free_seids[n].coord.y-1 && free_seids[t].view == free_seids[n].view) || (free_seids[t].coord.y == free_seids[n].coord.y+1 && free_seids[t].view == free_seids[n].view)) {
                if (memo_check(memo_free_seide, free_seids[t], free_seids[n]))  {
                  if (memo_check(memo_free_seide, free_seids[n], free_seids[t])) {
                    /*
                    if (counter_x == 0) {
                      last_cornodinate = free_seids[n].coord;  
                      paar_exsist_x++; 
                    } else if (last_cornodinate == free_seids[t].coord)
                    {
                      last_cornodinate = free_seids[n].coord; 
                    } else {
                      last_cornodinate = free_seids[n].coord; 
                      paar_exsist_x++;
                    }    
                    counter_x+=2;  
                    */
                    memo_free_seide.push_back({free_seids[t],free_seids[n]});
                  }
                }
              } 
            } 
          }
        }
      }
      if (memo_free_seide.size() > 0)  {
        
        std::vector<char> found_view = Find_view(memo_free_seide); 
        for (auto view : found_view) {
          bool memo_save_start = false;

          int memo_free_seide_max_x = Find_max_y(memo_free_seide,view);
          int memo_free_seide_min_x = Find_min_y(memo_free_seide,view);
          for (int k =memo_free_seide_min_x; k < memo_free_seide_max_x; k++) {
            if(View_exists(memo_free_seide, {{w,k},view}) && memo_save_start == false) {
              memo_save_start = true; 
              paar_exsist_x++;
            }

            if(!View_exists(memo_free_seide, {{w,k},view}) && memo_save_start == true) {
              memo_save_start = false; 
            }
          }
        }
      }

      if (paar_exsist_x > 0) {
         between_total += paar_exsist_x;
      } 
    } 
    
    for (int t = 0; t < free_seids.size(); t++) {
      bool no_neighbour = true; 
      for (int z =0; z < free_seids.size(); z++) {
        
        if (t != z) {
          if (free_seids[t].coord.x == free_seids[z].coord.x && free_seids[t].view == free_seids[z].view && (free_seids[t].coord.y == free_seids[z].coord.y-1 || free_seids[t].coord.y == free_seids[z].coord.y+1 )) {
            no_neighbour = false;
          } 
          if (free_seids[t].coord.y == free_seids[z].coord.y && free_seids[t].view == free_seids[z].view && (free_seids[t].coord.x == free_seids[z].coord.x-1 || free_seids[t].coord.x == free_seids[z].coord.x+1)) {
            no_neighbour = false;
          }
        }
      } 
      if (no_neighbour) {
        between_total++;
      }
    }
    
    sum += between_total * coordiantes.size();
  }    

  return sum;
}

int task2(std::vector<std::vector<char>>& input){   

  std::vector<Feld> felds = Count_Land(input);

  int sum = Calulate_perimeter2(felds, input.size(), input[0].size());
   
  return sum;  
}

int main() {
  
  std::vector<std::vector<char>> input_print_rules = Read_Print_Input("input.txt");

  //int task1_num = task1(input_print_rules);
  int task2_num =task2(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}