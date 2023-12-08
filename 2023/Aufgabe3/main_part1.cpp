#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>


std::string reverse( std::string const& s )
{
  return s.empty() ? "" : s[s.length()-1] + reverse(s.substr(0, s.length()-1));
}

//row counter 
int getcolumecount(std::string line) {
int counter = 0; 
while(true) {
        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1 ;
    }
    return counter; 
}

//OpenFile 


// Nummer suchen 
int GetNummer(std::string line, int sonecolume) {
    int leftcounter = 0;
    int rightcounter =1; 
    std::string lefttemp = "";
    std::string righttemp = ""; 
    while(true) {
    if (('0' <= line[sonecolume-leftcounter] && line[sonecolume-leftcounter] <= '9' ) )
    {
        lefttemp += line[sonecolume-leftcounter];
        leftcounter++;
    }
    if (('0' <= line[sonecolume+rightcounter] && line[sonecolume+rightcounter] <= '9' ) )
    {
        righttemp += line[sonecolume+rightcounter];
        rightcounter++;
    }

    if (!('0' <= line[sonecolume-leftcounter] && line[sonecolume-leftcounter] <= '9' ) && !('0' <= line[sonecolume+rightcounter] && line[sonecolume+rightcounter] <= '9' )) {
        lefttemp = reverse(lefttemp);
        lefttemp += righttemp;
        break;
    }
    }
    return stoi(lefttemp);
}


// Zeichen suchen 


int main() {

    std::string FILENAME = "input.txt";
    
    //Benötigte Größe herausfinden 
    int rowcoutner = 0;
    int columecounter = 0;
    std::ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            if (columecounter == 0) {
                columecounter = getcolumecount(line);
            }
            rowcoutner += 1; 
        }
    file.close();
    }

    //Array erstellen und befühlen und Ausswerten 
    std::cout << "rowcouter: " << rowcoutner << "columecounter: " << columecounter << std::endl;

    std::string input[rowcoutner];

    std::ifstream file2(FILENAME);
    if (file2.is_open()) {
        std::string line;
        rowcoutner=0;
        while (std::getline(file2, line)) {
            //std::cout << line << std::endl;
            input[rowcoutner] = line; 
            rowcoutner += 1;
        }
        file2.close();

        std::cout << "rowcouter: " << rowcoutner << "columecounter: " << columecounter << std::endl; 
        int sum = 0; 


        for(int row = 0; row < rowcoutner; row++){ 
            //std::cout << input[row] << std::endl; 
            for(int colume = 0; colume < columecounter; colume++) {

                if (!('0' <= input[row][colume] && input[row][colume] <= '9' ) && !(input[row][colume] == '.') && ('\0' != input[row][colume] ) && ("" != input[row] ) ) {
                    //std::cout << "if: "<< input[row][colume] << std::endl;

                    for(int sonerow = -1; sonerow < 2; sonerow++) {
                        std::string temp = "";

                        for(int sonecolume = -1; sonecolume < 2; sonecolume++) {
                            temp += input[row+sonerow][colume+sonecolume];
                            if (('0' <= input[row+sonerow][colume+sonecolume] && input[row+sonerow][colume+sonecolume] <= '9' ) ) {
                                
                                if (!('0' <= input[row+sonerow][colume+sonecolume+1] && input[row+sonerow][colume+sonecolume+1] <= '9' ) || sonecolume == 1 ) {
                                    //std::cout << "debug: "<< input[row][colume] << "||" << input[row+sonerow][colume+sonecolume] << std::endl;
                                    sum += GetNummer(input[row+sonerow], (colume+sonecolume));
                                }
                            }
                        };
                        //std::cout << "sone: " << temp << std::endl;
                    }




                }
                
            }
        }

        std::cout << "sum: "<< sum << std::endl; 
    }



  return 0;
}