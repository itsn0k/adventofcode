#include <iostream>
#include <string>
#include <fstream>

std::string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char        chardigits[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::string reverse( std::string const& s )
{
  return s.empty() ? "" : s[s.length()-1] + reverse(s.substr(0, s.length()-1));
}

//Get L
char GetL(std::string line) {
    int counter = 0;
    std::string temp = ""; 
    while(true) {
        if ('a' <= line[counter] && line[counter] <= 'z' ) {
            temp += line[counter];
            for (int i = 0; i < 9; i++)
            {
                if (temp.find(digits[i]) != std::string::npos) {
                    return  chardigits[i];
                }
            }
            
        }


        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            return line[counter]; 
        }
        
        if ('\0' == line[counter]) {
            return 0;
        }
        counter = counter +1 ;
    }
}

//Get R
char GetR(std::string line) {
    int counter = line.length();
    std::string temp = "";
    while(true) {
        if ('a' <= line[counter] && line[counter] <= 'z' ) {
            temp += line[counter];
            std::string reverstemp = reverse(temp);
            for (int i = 0; i < 9; i++)
            {
                if (reverstemp.find(digits[i]) != std::string::npos) {
                    return  chardigits[i];
                }
            }
            
        }


        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            return line[counter]; 
        }
        

        counter = counter -1 ;
    }
}


int main() {
    
    std::string FILENAME = "input.txt";
 
    std::ifstream file(FILENAME);
    if (file.is_open()) {
    int sum = 0;
    std::string line;
    while (std::getline(file, line)) {
        // using printf() in all tests for consistency
        std::string lineoutput = ""; 
        lineoutput += GetL(line.c_str());
        lineoutput += GetR(line.c_str());
        sum = sum + stoi(lineoutput);
    }
    file.close();
    std::cout << sum << std::endl;
    }


  return 0;
}