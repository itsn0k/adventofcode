#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>   // EXIT_SUCCES
#include <vector> // std::vector
#include <algorithm>
#include <iostream>
#include <iterator>

int GetID(std::string line) {
    int counter = line.length();
    std::string temp = "";
    while(true) {
        if (('\0' != line[counter]) && ('0' <= line[counter] && line[counter] <= '9' ) )
        {
            temp += line[counter];
        }
        
        if (' ' == line[counter]) {
            break;
        }
        counter = counter -1 ;
    }
    std::reverse(temp.begin(), temp.end());
    return stoi(temp);    
}

unsigned long long int GetRank(std::string line) {
    //um so höre der Array index um so hochwertiger die Karte 
    char labelofcards[13] = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };
    std::string rankingofcards[13] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13" };
    std::vector<int> coutlabelfound ={0 ,0 ,0 ,0 ,0,0 ,0 ,0 ,0 ,0,0 ,0 ,0  };
    int savecardplays[5] ={0 ,0 ,0 ,0 ,0 };
    int t = 0; 
    for (char c : line) {
    //std::cout << " - '" << c << "'" << std::endl;

        if (c == ' ') {
            break; 
        }

        for(int i =0 ; i<13 && t<5;i++) {
            if (labelofcards[i] == c) {
                coutlabelfound[i] += 1; 
                savecardplays[t] = i;
                t++;
            }
        }

    }

    //Holt sich anzahl jocker und setzt sie auf null 
    int savejocker = coutlabelfound[0];
    coutlabelfound[0] =0;
    //std::cout <<"savejcoker: " << savejocker<< std::endl; 

    //Sortiert so das an ersterstelle höchster wert steht 
    std::sort(coutlabelfound.begin(), coutlabelfound.end());
    std::reverse(coutlabelfound.begin(), coutlabelfound.end());

    //Zahlt den jocker wert zu der Höchsten anzahl 
    coutlabelfound[0] += savejocker;

    std::string temp ="";
    //Berechne einer ID um die Karten zu vergeileichen 
    for(int i =0; i<5;i++) {
        if (coutlabelfound[i] == 5) {
            temp += "5";
        }
        else if (coutlabelfound[i] == 4) {
            temp += "4";
        }
        else if (coutlabelfound[i] == 3) {
            temp += "3";
        }
        else if (coutlabelfound[i] == 2) {
            temp += "2";
        }
        else if (coutlabelfound[i] == 1) {
            temp += "1";
        }
        else {
            temp += "0";
        }
    }

    for(int i = 0; i<5;i++) {
        temp += rankingofcards[savecardplays[i]];
    }
    //std::cout << temp << std::endl; 

    return stoull(temp); 

}

int main () {

    std::string FILENAME = "input.txt";
 
    std::ifstream file(FILENAME);
    if (file.is_open()) {
        std::vector<std::vector<unsigned long long int>> reslutindex; 
        std::string line;
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            
            std::vector<unsigned long long int> v; 
            v.push_back(GetRank(line));
            v.push_back(GetID(line));
            
            reslutindex.push_back(v);
        }
        file.close();
        for (int i = 0; i < reslutindex.size(); i++) {
            //std::cout << reslutindex[i][0] << " | " << reslutindex[i][1] << std::endl; 

        }

        std::sort(reslutindex.begin(), reslutindex.end());
        int sum =0; 
        for (int i = 0; i < reslutindex.size(); i++) {
            std::cout << reslutindex[i][0] << " | " << reslutindex[i][1] << std::endl; 
            sum += (i+1) * reslutindex[i][1];
        }

        std::cout << sum << std::endl;
    }

    return 0; 
}