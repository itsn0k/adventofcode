#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>   // EXIT_SUCCES
#include <vector> // std::vector
#include <math.h> 



int  main() {

    std::vector<std::vector<long long int>> testinput = {{71530,940200}};
    std::vector<std::vector<long long int>> input= {{49877895,356137815021882}};

    long long int  counter =0; 
    for (long long int  i = 0; i < input.size(); i++) {
        long long int  a = input[i][0];
        long long int  b = input[i][1];
        for(long long int  t = 0; t <= input[i][0]; t++) {
            long long int  erg =0 ;      
            erg= t*(a-t);

            if(b < erg ) {
                //std::cout <<"i:" <<i <<" t: " <<t << " Funktion: "<< t*(a-t) << std::endl; 
                counter += 1; 
            }
            
        }
        
    }
    std::cout << "erg: " << counter << std::endl;

    return 0; 
}