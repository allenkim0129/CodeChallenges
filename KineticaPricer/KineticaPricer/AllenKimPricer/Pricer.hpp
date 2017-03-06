//
//  Pricer.hpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#ifndef Pricer_hpp
#define Pricer_hpp

//standard libraries
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <sstream>

//custom libraries
#include "BidAnalyzer.hpp"
#include "AskAnalyzer.hpp"

class Pricer{
public:
    Pricer(double targetSize_);
    ~Pricer();
    void run();
    
private:
    //helper functions
    std::string loadSide(std::string id);
    
    //validation functions
    void isValidInput(std::string id, std::string side, double price, double size);
    void isValidInput(std::string id, double size);
    
    //private variables
    double targetSize;
    std::unordered_map<std::string, std::string> sideMap;       //contain id and its side information
    BidAnalyzer* bidAnalyzer;                                   //analyzer for bid orders
    AskAnalyzer* askAnalyzer;                                   //analyzer for ask order
    
};
#endif /* Pricer_hpp */
