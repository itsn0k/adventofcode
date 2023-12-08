#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>




int GetCounter(std::string line) {
    int counter = 0;
    std::string temp = ""; 
    while(true) {
        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            temp += line[counter];
        }
        
        if ('\0' == line[counter]) {
            break;
        }
        counter = counter +1 ;
    }
    return stoi(temp);
}

//Count
int countcubes2(std::string line) {
    std::string cubes[3] =  {"blue","red","green"};
    int contaidcubes[3] =   {0,0,0};

    int gameid = 0; 
    int counter = 0;
    int countofcubes[3] =     {0, 0 ,0 };
    std::string temp = ""; 
    while(true) {
        if (':' != line[counter] && ',' != line[counter] && ';' != line[counter] && '\0' != line[counter] ) {
            temp += line[counter];
        }
        else {
            if ('\0' == line[counter]) {
                std::cout << temp << std::endl;
            }

            if (':' == line[counter]) {
                gameid = GetCounter(temp);
            }
            else {
                for(int i = 0; i < 3; i++) {
                    if (temp.find(cubes[i]) != std::string::npos) {
                        countofcubes[i] += GetCounter(temp);
                    }
                }
                for(int i = 0; i < 3; i++) {
                    if(countofcubes[i]>contaidcubes[i]) {
                        contaidcubes[i]= countofcubes[i];
                    }
                }
                
                if (';' == line[counter]) {
                    for(int i = 0; i < 3; i++) {
                        countofcubes[i] = 0;
                    }
                }
            }

            temp = "";
        }

        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1 ;
    }
    std::cout << contaidcubes[0] << "*" << contaidcubes[1] << "*" << contaidcubes[2] << "=" << contaidcubes[0] * contaidcubes[1] * contaidcubes[2] << std::endl;
    return contaidcubes[0] * contaidcubes[1] * contaidcubes[2];
}

int countcubes(std::string line) {
    std::string cubes[3] =  {"blue","red","green"};
    int contaidcubes[3] =   {14,12,13};

    int gameid = 0; 
    int counter = 0;
    int countofcubes[3] =     {0, 0 ,0 };
    std::string temp = ""; 
    while(true) {
        if (':' != line[counter] && ',' != line[counter] && ';' != line[counter] && '\0' != line[counter] ) {
            temp += line[counter];
        }
        else {
            if ('\0' == line[counter]) {
                std::cout << temp << std::endl;
            }

            if (':' == line[counter]) {
                gameid = GetCounter(temp);
            }
            else {
                for(int i = 0; i < 3; i++) {
                    if (temp.find(cubes[i]) != std::string::npos) {
                        countofcubes[i] += GetCounter(temp);
                    }
                }
                for(int i = 0; i < 3; i++) {
                    if(countofcubes[i]>contaidcubes[i]) {
                        return 0;
                    }
                }
                
                if (';' == line[counter]) {
                    for(int i = 0; i < 3; i++) {
                        countofcubes[i] = 0;
                    }
                }
            }

            temp = "";
        }

        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1 ;
    }
    return gameid;
}

int main() {

    std::string FILENAME = "input.txt";
 
    std::ifstream file(FILENAME);
    if (file.is_open()) {
    std::string line;

    int sum = 0;

    while (std::getline(file, line)) {
        int debug = countcubes2(line);
        
        sum += debug;
    }
    file.close();


    std::cout << sum << std::endl;

    }


  return 0;
}