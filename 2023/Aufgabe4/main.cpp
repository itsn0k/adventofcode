#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>


int GetCounter(std::string line) {
    int counter = 0;
    int arraycounter = 0; 
    std::string temp = ""; 
    while(true) {
        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            temp += line[counter];
        }
        else 
        {
            if ("" != temp) { 
                arraycounter++; 
                temp = "";
            }
        }
        
        if ('\0' == line[counter]) {
            break;
        }
        counter = counter +1 ;
    }
    return arraycounter; 
}

void GetCountNumbers(std::string line, int &winningcount, int &tipcount) { 
    int counter = 0;
    int stringnummer = 0; 

    std::string temp = ""; 
    while(true) {
        if (':' != line[counter] && '|' != line[counter] && '\0' != line[counter] ) {
            temp += line[counter];
        }
        else {            
            if (stringnummer == 1) {
                winningcount = GetCounter(temp);
            }
            if (stringnummer == 2) {
                tipcount = GetCounter(temp);
            }
            stringnummer++; 
            temp = "";
        }

        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1;
    }
}

void GetNumbers(std::string line, int nummbers[]) {
    int counter = 0;
    int arraycounter = 0; 
    std::string temp = ""; 
    while(true) {
        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            temp += line[counter];
        }
        else 
        {
            if ("" != temp) {
                //std::cout << temp << std::endl;
                nummbers[arraycounter] = stoi(temp); 
                arraycounter++; 
                temp = "";
            }

        }
        
        if ('\0' == line[counter]) {
            break;
        }
        counter = counter +1 ;
    }
}

//Aufgabe 1
int PointsperGame(std::string line, int &winningnumbercounter,int &tipingnumbercounter) {

    int winningnumbers[winningnumbercounter];
    int tipingnumbers[tipingnumbercounter];
    int points = 0; 
    int counter = 0;
    int stringnummer = 0; 

    std::string temp = ""; 
    while(true) {
        if (':' != line[counter] && '|' != line[counter] && '\0' != line[counter] ) {
            temp += line[counter];
        }
        else {
            //std::cout << temp << std::endl;
            
            if (stringnummer == 1) {
                GetNumbers(temp, winningnumbers);
            }
            if (stringnummer == 2) {
                GetNumbers(temp, tipingnumbers);
            }
            stringnummer++; 
            temp = "";
        }

        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1 ;
    }

    for(int i =0; i<winningnumbercounter; i++) {
        for(int t = 0; t<tipingnumbercounter; t++) {
            if (winningnumbers[i] == tipingnumbers[t]) {
                if(points == 0) {
                    points = 1; 
                }
                else{
                    points *= 2; 
                }
            }
        }
    }


    return points;
}

//Aufgabe 1
int PointsperGame2(std::string line, int &winningnumbercounter,int &tipingnumbercounter) {

    int winningnumbers[winningnumbercounter];
    int tipingnumbers[tipingnumbercounter];
    int points = 0; 
    int counter = 0;
    int stringnummer = 0; 

    std::string temp = ""; 
    while(true) {
        if (':' != line[counter] && '|' != line[counter] && '\0' != line[counter] ) {
            temp += line[counter];
        }
        else {
            //std::cout << temp << std::endl;
            
            if (stringnummer == 1) {
                GetNumbers(temp, winningnumbers);
            }
            if (stringnummer == 2) {
                GetNumbers(temp, tipingnumbers);
            }
            stringnummer++; 
            temp = "";
        }

        if ('\0' == line[counter]) {
            break;
        }

        counter = counter +1 ;
    }

    for(int i =0; i<winningnumbercounter; i++) {
        for(int t = 0; t<tipingnumbercounter; t++) {
            if (winningnumbers[i] == tipingnumbers[t]) {
                    points += 1; 
            }
        }
    }


    return points;
}

void Settoone(int a[], int &gametotalcount) {
    for(int i = 0; i < gametotalcount; i++) {
        a[i] = 1; 
    }
}



int main() {

    std::string FILENAME = "input.txt";
    int gametotalcount = 211; //6 für test 211 für game 
    int scratchcards[gametotalcount];
    Settoone(scratchcards, gametotalcount); 
    int gamecounter = 0; 




    //Points Auswerten 
    std::ifstream file(FILENAME);
    if (file.is_open()) {
    std::string line;

    int sum = 0;
    int winningcount = 0;
    int tipcount = 0;  

    while (std::getline(file, line)) {
         

        if(winningcount == 0 && tipcount == 0) {
            GetCountNumbers(line, winningcount, tipcount);
        }
        //std::cout << "winning " << winningcount << "Tipcount " << tipcount << std::endl; 

        int debug = PointsperGame2(line, winningcount, tipcount);
        std::cout <<gamecounter+1 << "|" << debug << std::endl;

        for(int i = 1; i <= debug && gamecounter+i < gametotalcount; i++) {
            //std::cout << "i: "<< i << "|" <<  scratchcards[gamecounter+i] << std::endl;
            scratchcards[gamecounter+i] += 1*scratchcards[gamecounter];
            std::cout << "Gamenummer: "<< gamecounter+i << "|" << scratchcards[gamecounter+i] << std::endl;
        }
        std::cout << "--------------------------------------" << std::endl;
        gamecounter++;
    }
    file.close();

    for(int i = 0; i < gametotalcount; i++) {
        std::cout << "Gamenummer: "<< i+1 << "|" << scratchcards[i] << std::endl;
        sum += scratchcards[i];  
    }
    std::cout << "--------------------------------------" << std::endl;
    std::cout << sum << std::endl;

    }


  return 0;
}