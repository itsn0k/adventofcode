#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include<algorithm>


// Task function

std::vector<std::vector<long long>> Read_Print_Input(std::string filename) {
    std::vector<std::vector<long long>> a_tockens;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<long long> line_tockens;
            std::istringstream iss(line);
            std::string temp = "";

            for (char vaule : line) {
                if (vaule == ':') {
                    try {
                        if (!temp.empty()) {
                            line_tockens.push_back(std::stoll(temp)); // Verwende stoll für long long
                            temp = "";
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Fehler beim Konvertieren von \"" << temp << "\": " << e.what() << std::endl;
                        temp = "";
                    }
                } else if (vaule == ' ' && !temp.empty()) {
                    try {
                        line_tockens.push_back(std::stoll(temp)); // Verwende stoll für long long
                        temp = "";
                    } catch (const std::exception& e) {
                        std::cerr << "Fehler beim Konvertieren von \"" << temp << "\": " << e.what() << std::endl;
                        temp = "";
                    }
                } else if (vaule != ' ') {
                    temp += vaule;
                }
            }
            if (!temp.empty()) {
                try {
                    line_tockens.push_back(std::stoll(temp)); // Verwende stoll für long long
                } catch (const std::exception& e) {
                    std::cerr << "Fehler beim Konvertieren von \"" << temp << "\": " << e.what() << std::endl;
                }
            }
            a_tockens.push_back(line_tockens);
        }
        file.close();
    } else {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
    }
    return a_tockens;
}


std::vector<std::vector<std::string>> Create_Operator_Possibilities_Vector(int length_Operator_Vector) {
    std::vector<std::vector<std::string>> Operator_Vectors;
    int totalCombinations = 1 << length_Operator_Vector; // 2^n

    for (int mask = 0; mask < totalCombinations; ++mask) {
        std::vector<std::string> currentCombination;
        for (int i = 0; i < length_Operator_Vector; ++i) {
            // Überprüfen, ob das i-te Bit gesetzt ist
            if (mask & (1 << i)) {
                currentCombination.push_back("add");
            } else {
                currentCombination.push_back("mult");
            } 
        }
        Operator_Vectors.push_back(currentCombination);
    }

    return Operator_Vectors;
}

std::vector<std::vector<std::string>> Create_Operator_Possibilities_Vector2(int length_Operator_Vector) {
    std::vector<std::vector<std::string>> Operator_Vectors;

    int totalCombinations = std::pow(3, length_Operator_Vector); // 3^n Kombinationen

    for (int num = 0; num < totalCombinations; ++num) {
        std::vector<std::string> currentCombination;
        int value = num;

        for (int i = 0; i < length_Operator_Vector; ++i) {
            int state = value % 3; // Modulo 3, um den Zustand an dieser Position zu bestimmen
            value /= 3;           // Ganzzahldivision, um zur nächsten Position zu gehen

            // Zustände zuordnen
            if (state == 0) {
                currentCombination.push_back("add");
            } else if (state == 1) {
                currentCombination.push_back("mult");
            } else {
                currentCombination.push_back("||");
            }
        }

        Operator_Vectors.push_back(currentCombination);
    }

    return Operator_Vectors;
}

bool add(std::vector<long long>& list, int i, long long result_try,long long result) {

  if (i >= list.size()) {
    if (result == result_try) {
      return true; 
    }
    return false; 
  }
  int newvalue = 0;
  newvalue = i +1;
  long long value = 0;
  value = list[i];
  
  if (add(list, newvalue,result_try+value,result)) {
    return true; 
  }

  if (add(list, newvalue,result_try*value,result))
  {
    return true; 
  }

  std::string add_numbers = std::to_string(result_try);
  add_numbers +=  std::to_string(value); 
  result_try = std::stoll(add_numbers);
  if (add(list, i+1,result_try,result))
  {
    return true; 
  } 
  
  return false; 
}

int task1(std::vector<std::vector<long long>>& input) {
  long long sum =0; 
  
  for (int i = 0; i < input.size(); i++) {

    long long result = input[i][0];

    int length = input[i].size() -2;
    std::vector<std::vector<std::string>> Operator_Posibilitys = Create_Operator_Possibilities_Vector(length);

    for (int h = 0; h < Operator_Posibilitys.size(); h++) {
      long long result_try = 0;   
        for (int t = 1; t < input[i].size() , t-1 < Operator_Posibilitys[h].size(); t++) {
                long long value = input[i][t];
                long long secend_value = input[i][t+1];
                std::string operator_value = Operator_Posibilitys[h][t-1];

                if (result_try == 0) {
                  result_try = value;
                }
                
                if (operator_value == "mult") { 
                  result_try *= secend_value;   
                }
                else {
                  result_try += secend_value;  
                }
              }
        if (result == result_try) {
          sum += result_try ;
          break; 
        }
    }

  }
  

  return sum; 
}

int task2(std::vector<std::vector<long long>>& input) {
  long long sum =0; 
  
  for (int i = 0; i < input.size(); i++) {

    long long result = input[i][0];

    //int length = input[i].size() -2;
    //std::vector<std::vector<std::string>> Operator_Posibilitys = Create_Operator_Possibilities_Vector2(length);

    if (add(input[i], 2, input[i][1],result)) {
      sum += result;

    }
  }
  
  return sum; 
}

int main() {
  

  std::vector<std::vector<long long>> input_print_rules = Read_Print_Input("input.txt");

  //long long task1_num = task1(input_print_rules);
  long long task2_num = task2(input_print_rules);

  std::cout << "Ergebniss: "  << task2_num << std::endl; //<< task1_num
  

return 0;
}