#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>   // EXIT_SUCCES
#include <vector> // std::vector
#include <math.h> 



int main() {

    std::vector<std::vector<int>> testinput = {{7,9}, {15,40}, {30,200}};
    std::vector<std::vector<int>> input= {{49,356}, {87,1378}, {78,1502}, {95,1882}};

    /*
    for (int i = 0; i < testinput.size(); i++) {
        for (int j = 0; j < testinput[i].size(); j++) {


            std::cout << (testinput[i][j]) << std::endl; 
        }
    }
    */
    int counter[4] = {0,0,0,0};

    for (int i = 0; i < input.size(); i++) {
        int a = input[i][0];
        int b = input[i][1];
        for(int t = 0; t <= input[i][0]; t++) {
            int erg =0 ; 
            
             
            erg= t*(a-t);

            if(b < erg ) {
                std::cout <<"i:" <<i <<" t: " <<t << " Funktion: "<< t*(a-t) << std::endl; 
                counter[i] += 1; 
            }
            
        }
        
    }

    int erg =1; 
    for (int g =0; g<input.size(); g++) {
        erg *= counter[g];
    }
    std::cout << "erg: " << erg << std::endl;

    return 0; 
}