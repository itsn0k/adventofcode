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

void GetNumbers(std::string line, unsigned int nummbers[]) {
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
                nummbers[arraycounter] = stoul(temp); 
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

void PrintSeeds(unsigned int a[], int length) {
    std::cout << "----------------" << std::endl;
    for(int i = 0; i < length; i++) {
        std::cout << a[i] << std::endl; 
    }
    std::cout << "----------------" << std::endl;
}

void UpdateSeedMaps(bool a[], int length) {
    for(int i = 0; i < length; i++) {
        a[i] = false; 
    }
}

unsigned int GetLowesNummber(unsigned int a[], int length) {
    unsigned int reslut=4294967295; 
    for(int i = 0; i < length; i++) {
        if(reslut>a[i]) {
            reslut = a[i];
        }
    }
    return reslut; 
}

void Inizializedynarray(unsigned int startvalue, unsigned int a[], int length) {
    for(int i = 0; i < length; i++) {
        if(reslut>a[i]) {
            a[i] = startvalue +i;
        }
    }
} 

int main() {

    std::string FILENAME = "test1.txt"; 
    int numbercounter = 0;
    int sum = 0;

    std::ifstream file(FILENAME);
    if (file.is_open()) {

    
    
    std::string line;

    //Get First Line Get Seeds 
    std::getline(file, line);
    numbercounter = GetCounter(line); 
    unsigned int seeds[numbercounter];
    bool      seedsmap[numbercounter];  
    GetNumbers(line, seeds);
    PrintSeeds(seeds, numbercounter);

    }
    file.close();

    for(int h = 0 ; h<numbercounter; h=h+2) {
        unsigned int *dyn_array_seeds = 0;
        bool *dyn_array_bool = false; 

        dyn_array_seeds = new unsigned int[seeds[h+1]];
        dyn_array_bool = new bool[seeds[h+1]]

        Inizializedynarray(seeds[h],dyn_array_seeds,seeds[h+1]);
        UpdateSeedMaps(dyn_array_bool,seeds[h+1]);

        //Map Aussertung
        if (file.is_open()) {
        
        std::string line;

        //Get First Line Get Seeds 
        std::getline(file, line);
        //Get Maps
        unsigned int maps[3];
        //Skipp first Line 
        numbercounter = GetCounter(line); 
        while (std::getline(file, line)) {

            //std::cout << line << std::endl;

            if (line.find(':') != std::string::npos) {
                UpdateSeedMaps(dyn_array_bool, seeds[h+1]);
                //PrintSeeds(seeds, numbercounter);
                //std::cout << "----------------" << std::endl;
                //std::cout << "----------------" << std::endl;
            }


            if (('\0' != line[0]) && ('0' <= line[0] && line[0] <= '9' )) {
                GetNumbers(line, maps);
                //PrintSeeds(maps,3);

                for(int i = 0; i <seeds[h+1];i++) {
                    //std::cout << maps[1] << "+"<< maps[2] << std::endl;  
                    if((maps[1] <= dyn_array_seeds[i] && dyn_array_seeds[i] <= (maps[1]+maps[2])) && dyn_array_bool[i] == false) {
                        //std::cout << i << "=" << seeds[i] << "+"<< maps[0] << "-" << maps[1] << std::endl; 
                        dyn_array_seeds[i] = dyn_array_seeds[i]+(maps[0]-maps[1]);
                        
                        dyn_array_bool[i] = true;
                    }
                }
                
                
            }
            
        
        


        //sum = sum + stoi(lineoutput);
    }
    file.close();
    
    PrintSeeds(seeds, numbercounter);
    sum = GetLowesNummber(seeds, numbercounter);
    
    }
    }
    std::cout << "sum: "<< sum << std::endl;
  return 0;
}