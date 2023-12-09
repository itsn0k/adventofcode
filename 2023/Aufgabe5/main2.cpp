#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>   // EXIT_SUCCES
#include <vector> // std::vector


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

void GetNumbers(std::string line, long long int nummbers[]) {
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

std::vector<long long int> GetVectorNumbers(std::string line) {
    std::vector<long long int> nummbers;
    int counter = 0;
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
                nummbers.push_back(stoul(temp)); 
                temp = "";
            }

        }
        
        if ('\0' == line[counter]) {
            break;
        }
        counter = counter +1 ;
    }
    return nummbers;
}

void PrintSeeds(std::vector<long long int> a) {
    std::cout << "----------------PrintSeeds----------------" << std::endl;
    for (std::vector<long long int>::size_type i = 0; i < a.size(); ++i) {
        std::cout << a[i] << std::endl; 
    }
    std::cout << "------------------------------------------" << std::endl;
}

void PrintMap(long long int a[], int length) {
    std::cout << "----------------" << std::endl;
    for(int i = 0; i < length; i++) {
        std::cout << a[i] << std::endl; 
    }
    std::cout << "----------------" << std::endl;
}

std::vector<bool> UpdateSeedMaps(int length) {
    std::vector<bool> a;
    for(int i = 0; i < length; i++) {
        a.push_back(false); 
    }
    return a; 
}

long long int GetLowesNummber(std::vector<long long int> a) {
    long long int reslut=4294967295; 
    for (std::vector<long long int>::size_type i = 0; i < a.size(); i=i+2) {
        if(reslut>a[i]) {
            reslut = a[i];
        }
    }
    return reslut; 
}

long long int GetSumeofSeeds(std::vector<long long int> a) {
    long long int reslut =0; 
    for (std::vector<long long int>::size_type i = 1; i < a.size(); i=i+2) {
        reslut += a[i];
    }
    return reslut; 
}


int main() {

    std::string FILENAME = "input.txt"; 
    std::ifstream file(FILENAME);
    if (file.is_open()) {
    int numbercounter = 0;
    int sum = 0;
    
    std::string line;

    //Get First Line Get Seeds 
    std::getline(file, line);
    std::vector<long long int> seeds;
    std::vector<bool> seedsmap;
    seedsmap =  UpdateSeedMaps(seeds.size());
    seeds = GetVectorNumbers(line);
    std::cout << "GetSumeofseeds Beginn: "<<GetSumeofSeeds(seeds) << std::endl;
    PrintSeeds(seeds);

    //Get Maps
    long long int maps[3];
    while (std::getline(file, line)) {

        //std::cout << line << std::endl;

        if (line.find(':') != std::string::npos) {
            seedsmap =  UpdateSeedMaps(seeds.size());
            //PrintSeeds(seeds);
            //std::cout << "----------------" << std::endl;
            //std::cout << "----------------" << std::endl;
        }


        if (('\0' != line[0]) && ('0' <= line[0] && line[0] <= '9' )) {
            GetNumbers(line, maps);
            //PrintMap(maps,3);
            long long int sizeofvecotr = seeds.size(); 
            for (std::vector<long long int>::size_type i = 0; i < sizeofvecotr; i=i+2) {
                //std::cout << maps[1] << "+"<< maps[2] << std::endl;
                //std::cout << "i: " << i << " seeds: " << seeds[i] << std::endl;
                long long int seedstart = seeds[i];
                long long int seedend   = seeds[i]+seeds[i+1]-1; 

                long long int mapstart  = maps[1];
                long long int mapend   = maps[1]+maps[2]-1;
                //std::cout << "seedstart: " << seedstart << " seedsmap:" << seedsmap[i] << " seedend: " << seedend << " mapstart: " << mapstart << " mapend: " << mapend <<std::endl; 
                //std::cout << (mapstart <= seedstart) << "&&" << (seedstart <= mapend) << "und freigabe" << (seedsmap[i] == false && seedsmap[i+1] == false) << std::endl;
                if((mapstart <= seedstart && seedend <= mapend) && (seedsmap[i] == false && seedsmap[i+1] == false)) {
                    //std::cout << "if1" <<std::endl;
                    long long int mapoffset = maps[0]-maps[1];
                    
                    //std::cout << "seedstart: " << seedstart << " seeds[i]:" << (seedstart+mapoffset) << std::endl;
                    seeds[i] = seedstart+mapoffset;
                    seedsmap[i] = true;
                    seedsmap[i+1] = true; //Range hat keine Veränderung 
                }
                else if ((mapstart <= seedstart && seedstart <= mapend) && (seedsmap[i] == false && seedsmap[i+1] == false)) { 
                    //std::cout << "if2" <<std::endl;
                    //std::cout << "seedstart: " << seedstart << " seedsmap:" << seedsmap[i] << " seedend: " << seedend << " mapstart: " << mapstart << " mapend: " << mapend <<std::endl;
                    long long int mapoffset = maps[0]-maps[1];
                    long long int seedoffset = mapend-(seedstart-1);
                    //std::cout << "mapoffset: " << mapoffset << " seedoffset: " << seedoffset <<std::endl;
                    //1 Teil wird weider gepeichert 
                    seeds.push_back(mapend+1);
                    seeds.push_back(seeds[i+1]-seedoffset);
                    seedsmap.push_back(false);
                    seedsmap.push_back(false);

                    //std::cout << "seedstart: " << mapend+1 << " seeds[i]:" << seeds[seeds.size()-2] << " länge: " << seeds[seeds.size()-1] << std::endl;
                    
                    //2 Teil der in den Bereich passt wird gespeichert
                    seeds[i]   = seedstart+mapoffset;
                    seeds[i+1] = seedoffset;
                    seedsmap[i] = true;
                    seedsmap[i+1] = true; //Range hat keine Veränderung 
                    //std::cout << "seedstart: " << seedstart << " seeds[i]:" << (seedstart+mapoffset) << std::endl;

                }
                else if ((mapstart <= seedend && seedend <= mapend) && (seedsmap[i] == false && seedsmap[i+1] == false)) {
                    //std::cout << "if3" <<std::endl;
                    //std::cout << "seedstart: " << seedstart << " seedsmap:" << seedsmap[i] << " seedend: " << seedend << " mapstart: " << mapstart << " mapend: " << mapend <<std::endl;
                    long long int mapoffset = maps[0]-maps[1];
                    long long int seedoffset = seedend-(mapstart-1);

                    //std::cout << "mapoffset: " << mapoffset << " seedoffset: " << seedoffset <<std::endl;
                    //1 Teil wird weider gepeichert 
                    seeds.push_back(seedstart);
                    seeds.push_back(seeds[i+1]-seedoffset);
                    seedsmap.push_back(false);
                    seedsmap.push_back(false);

                    //std::cout << "seedstart: " << seedstart << " seeds[i]:" << seeds[seeds.size()-2] << " länge: " << seeds[seeds.size()-1] << std::endl;
                    

                    //2 Teil der in den Bereich passt wird gespeichert
                    seeds[i]   = mapstart+mapoffset;
                    seeds[i+1] = seedoffset;
                    seedsmap[i] = true;
                    seedsmap[i+1] = true; //Range hat keine Veränderung
                    //std::cout << "seedstart: " << mapstart << " seeds[i]:" << seeds[i]  << std::endl;
                }
                
            } 
            
        }
        
        
        


        //sum = sum + stoi(lineoutput);
    }
    file.close();
    
    PrintSeeds(seeds);
    sum = GetLowesNummber(seeds);
    std::cout << "GetSumeofseeds Beginn: "<<GetSumeofSeeds(seeds) << std::endl;
    std::cout << "sum: "<< sum << std::endl;
    }


  return 0;
}