#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

// Comparator function
bool comp(int a, int b) {
    return a >= b;
}


int main() {
    
std::string FILENAME = "input.txt";

//Read Input 
std::ifstream file(FILENAME);
if (file.is_open()) {

  std::string line;
  std::vector<int> a_tockens;
  std::vector<int> b_tockens;

  while (std::getline(file, line)) {

    std::istringstream iss(line);
    std::string token;
    
    int counter = 0; 
    while (std::getline(iss, token, ' ')) {  // but we can specify a different one
      if (token != "" && counter % 2 == 0 ) {
        a_tockens.push_back(std::stoi(token)); //std::stoi String to Int
      } 
      else if (token != "") {
        b_tockens.push_back(std::stoi(token));
      }
      
      counter += 1; 
    }
  }
  file.close();
  //Logic Path Finding

  //Sort der Listen von Klein zu groß
  std::sort(a_tockens.begin(), a_tockens.end(), comp);
  std::sort(b_tockens.begin(), b_tockens.end(), comp);
  

  /*Part 1
  int sum = 0;
  for (int i = 0; i < a_tockens.size() && b_tockens.size(); i++ ) {
    int interim_result = a_tockens[i] - b_tockens[i];

    if (interim_result < 0) {
      interim_result *= -1;
    }
    
    sum += interim_result;
  }
  */

 	//Part 2
  int sum = 0;
  for (int i = 0; i < a_tockens.size(); i++ ) {

    int interim_result = 0;
    for (int t = 0; t < b_tockens.size(); t++) {

      if (a_tockens[i] == b_tockens[t]) {
        interim_result += 1; 
      }
    }
    interim_result = interim_result * a_tockens[i];

    sum += interim_result;
  }

  std::cout << "The Total distance between List a and b is:  " << sum << std::endl;
}

return 0;
}