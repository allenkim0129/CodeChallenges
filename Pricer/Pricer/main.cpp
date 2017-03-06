//
//  main.cpp
//  Pricer
//
//  Created by Allen Kim on 3/4/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <typeinfo>   // operator typeid
#include <fstream>

#include "BookAnalyzer.h"

#include <sstream>


int main(int argc, const char * argv[]) {    
    int targetSize = 1;
    std::string line;
    std::string timestamp, orderId, inputType, side;
    float price;
    int size;
    
    BookAnalyzer analyzer(targetSize);
    
    std::ifstream infile("/Users/Allen/Documents/GitHub/CodeChallenges/Pricer/Pricer/pricer.in");
    
    std::ofstream outfile("/Users/Allen/Documents/GitHub/CodeChallenges/Pricer/Pricer/test.out.txt");
    
//    std::cout << "New order: ";
//    while(getline(std::cin, line)){
    while(getline(infile, line)){
//        std::cout << "line: " << line << std::endl;
        try{
            std::stringstream ss(line);
            
            //to-do: add input validation
            while(ss >> timestamp){
                ss >> inputType;

                if(inputType == "A"){
                    
                    ss >> orderId >> side >> price >> size;
//                    std::cout << "orderId: " << orderId << std::endl;
//                    std::cout << "side: " << side << std::endl;
//                    std::cout << "price: " << price << std::endl;
//                    std::cout << "size: " << size << std::endl;
                    
                    analyzer.add(orderId, side, price, size);
                }else if(inputType == "R"){
                    ss >> orderId >> size;
                    side = analyzer.getSide(orderId);
//                    std::cout << "orderId: " << orderId << std::endl;
//                    std::cout << "side: " << side << std::endl;
//                    std::cout << "size: " << size << std::endl;
        
                    analyzer.reduce(orderId, size);
                }else{
                    throw std::runtime_error("input type is wrong");
                }
                
//                if(analyzer.calcBest(side))
                outfile << analyzer.getOutput(timestamp, side);
            }
        }catch(const std::exception& e){
            std::cout << "[Error]: " << e.what() << std::endl;
        }
    }
    
    infile.close();
    outfile.close();
    return 0;
}
