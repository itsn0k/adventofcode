#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>
#include <unordered_map>
#include <tuple>

// Task function
std::vector<long long> Read_Print_Input(std::string filename) {
  //Read Input 
  std::vector<long long> a_tockens;
  std::ifstream file(filename);
  if (file.is_open()) {

    std::string line;

    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string token;
      while (std::getline(iss, token, ' ')) {  // but we can specify a different one
        if (token != "") {
          a_tockens.push_back(std::stoll(token)); //std::stoi String to Int
        }
      }
    }
    file.close();
  }  
    //Logic Path Finding
  return a_tockens;
}

long long Revers(long long value, int round, int goal_round) {
  unsigned long long sum = 0; 
  if (round == goal_round) {
    return 1;
  }

  std::string value_as_string = std::to_string(value); 
  if (value == 0) {
    if (round+4 < goal_round) {

      sum += Revers(2,round+4,goal_round);
      sum += Revers(0,round+4,goal_round);
      sum += Revers(2,round+4,goal_round);
      sum += Revers(4,round+4,goal_round);
    }
    else {
      sum += Revers(1,round+1,goal_round);
    }
  }
  else if (value_as_string.length() % 2 == 0)
  {
    int splitt_index = value_as_string.length() / 2; 

    std::string first_value_as_string = value_as_string.substr(0,splitt_index);
    std::string secend_value_as_string  = value_as_string.substr(splitt_index,value_as_string.length());
    long long first_value = std::stoll(first_value_as_string);
    long long secend_value = std::stoll(secend_value_as_string);

    sum += Revers(first_value, round+1,goal_round); 
    sum += Revers(secend_value, round+1,goal_round);
  }
  else {
    sum += Revers(value * 2024, round+1,goal_round);
  }    

  return sum; 
}

long long task1(std::vector<long long>& input) {
  unsigned long long sum = 0; 

  for (int x =0; x < input.size(); x++) {
    unsigned long long value = input[x];

    sum += Revers(value, 0, 25);
    
  }
    

  return sum; 
}

unsigned long long Revers2(unsigned long long root_value, unsigned long long value, unsigned long long round, unsigned long long last_round_write, int goal_round,std::unordered_map < unsigned long long, std::vector<unsigned long long>>& cach) {
  unsigned long long sum = 0; 

  if(cach.find(value) != cach.end()) {
    if (round+cach[value][0] < goal_round) {
      round += cach[value][0];
      value = cach[value][1];
    }
  }


  if (round == goal_round) {
    return 1;
  }

  std::string value_as_string = std::to_string(value); 
  if (value == 0) {
    sum += Revers2(root_value,1,round+1,last_round_write+1,goal_round,cach);
  }
  else if (value_as_string.length() % 2 == 0)
  {
    int splitt_index = value_as_string.length() / 2; 

    std::string first_value_as_string = value_as_string.substr(0,splitt_index);
    std::string secend_value_as_string  = value_as_string.substr(splitt_index,value_as_string.length());
    long long first_value = std::stoll(first_value_as_string);
    long long secend_value = std::stoll(secend_value_as_string);

    //cach.insert({value, {round, first_value, secend_value}});

    if(last_round_write > 0) {
      cach.insert({root_value, {last_round_write, value}});
    }

    sum += Revers2(first_value,first_value, round+1,0,goal_round,cach); 
    sum += Revers2(secend_value,secend_value, round+1,0,goal_round,cach);
  }
  else {
    sum += Revers2(root_value,value * 2024, round+1,last_round_write+1,goal_round,cach);
  }    

  return sum; 
}

// Benutzerdefinierter Hash-Funktor für std::pair
struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        std::size_t hash1 = std::hash<T1>{}(pair.first);
        std::size_t hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Kombiniert die Hashes von first und second
    }
};

long long Revers3(long long value, long long c, std::unordered_map < std::pair<int, int>, long long,pair_hash>& memo) {
  if (c == 0) {
      return 1;
    }
  
  if (value == 0) {
    return Revers3(1,c-1,memo);
  } 

  std::string value_as_string = "" + std::to_string(value);
  if (value_as_string.length() % 2 == 0)
  {
    int splitt_index = value_as_string.length() / 2; 

    std::string first_value_as_string = value_as_string.substr(0,splitt_index);
    std::string secend_value_as_string  = value_as_string.substr(splitt_index,value_as_string.length());
    long long first_value = std::stoll(first_value_as_string);
    long long secend_value = std::stoll(secend_value_as_string);

    //long long f1 = Revers3(first_value,c-1,memo);
    //long long f2 = Revers3(secend_value,c-1,memo);

  
    long long f1 =0;
    long long f2 =0;
    if(memo.find(std::make_pair(first_value,c-1)) != memo.end()) {
      f1 = memo[std::make_pair(first_value,c-1)];
    } else {
      f1 = Revers3(first_value,c-1,memo);
      memo.insert({std::make_pair(first_value,c-1), f1});
    }

    if(memo.find(std::make_pair(secend_value,c-1)) != memo.end()) {
      f2 = memo[std::make_pair(secend_value,c-1)];
      
    } else {
      f2 = Revers3(secend_value,c-1,memo);
      memo.insert({std::make_pair(secend_value,c-1), f2});
    }
  
    return f1 + f2; 
  }
  
  return Revers3(2024 * value ,c-1,memo);

  }
  
  

long long task3(std::vector<long long>& input) {
  long long sum = 0; 
  //std::unordered_map <  long long, std::vector< long long>> cach_4 = {{0,{4,2,0,2,4}},{1,{3,2,0,2,4}},{2,{3,4,0,4,8}},{3,{3,6,0,7,2}},{4,{3,8,0,9,6}},{5,{4,20,48,28,80}},{3,{4,24,57,94,56}},{7,{4,28,67,60,32}},{8,{4,32,77,26,8}},{9,{4,36,86,91,84}}};
  std::unordered_map <std::pair<int, int>, long long,pair_hash> cach_2; 
  for (int x =0; x < input.size(); x++) {
    long long value = input[x];

    sum += Revers3(value,75,cach_2);  
  }  

  return sum; 
}

long long Find_index(std::unordered_map<long long, std::vector<long long>>& map, long long value) {
  for(auto &it : map) { 
    if(it.second[it.second.size()-1] == value) { 
      return it.first;
    } 
  } 
  return -1; 
}

long long task2(std::vector<long long>& input) {
  long long sum = 0; 
  std::unordered_map < long long, std::unordered_map <long long, std::vector<long long>>> cach; 
  std::unordered_map < long long, std::vector<long long>> cach2; 
  for (int x =0; x < input.size(); x++) {
    long long value = input[x];
    std::vector<std::vector<long long>> temp_number; 
    std::vector<long long> start_number = {value};
    for(int y =0; y < 25; y++) {
      
      int length_z_start_number = start_number.size();
      int counter =0;  
      for(int z = 0; z < length_z_start_number;z++) {
        long long z_value = start_number[z];
        std::string value_as_string = std::to_string(z_value); 

        if (z_value == 0) {
          start_number[z] =1; 
          counter++;
        }
        else if (value_as_string.length() % 2 == 0)
        {
          int splitt_index = value_as_string.length() / 2; 

          std::string first_value_as_string = value_as_string.substr(0,splitt_index);
          std::string secend_value_as_string  = value_as_string.substr(splitt_index,value_as_string.length());
          long long first_value = std::stoll(first_value_as_string);
          long long secend_value = std::stoll(secend_value_as_string);

          cach2.insert({value, {counter, {}}});
          counter =0; 

          start_number[z] = first_value;
          start_number.insert(start_number.begin() + z,secend_value);
          z++;

          long long index = Find_index(cach2, z_value);
          if(index >= 0) {
            cach2[index].push_back(first_value);
            cach2[index].push_back(secend_value);
          } else {
            if(cach2.find(z_value) == cach2.end()) {
              cach2.insert({z_value,{secend_value,secend_value}});
            } 
          }
        }
        else {
          start_number[z] = z_value * 2024; 
          counter++;
        }    


      }
      temp_number.push_back(start_number);


    }
    
  } 

  return sum; 
}


int main() {
  
  std::vector<long long> input_print_rules = Read_Print_Input("input.txt");

  //int task1_num = task1(input_print_rules);
  long long task2_num =task3(input_print_rules);

  std::cout << "Ergebniss: "  << std::endl; 
  

return 0;
}