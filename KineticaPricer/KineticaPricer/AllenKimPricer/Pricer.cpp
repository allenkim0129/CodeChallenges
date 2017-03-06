//
//  Pricer.cpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include "Pricer.hpp"

#include <fstream>

Pricer::Pricer(double targetSize_){
    targetSize = targetSize_;
    bidAnalyzer = new BidAnalyzer(targetSize);
    askAnalyzer = new AskAnalyzer(targetSize);
}

Pricer::~Pricer(){
    delete bidAnalyzer;
    delete askAnalyzer;
}

void Pricer::run(){
    std::cout << "\n:::::::::::Start Pricer:::::::::::" << std::endl;

    std::string line;
    std::string timestamp, orderId, inputType, side;
    double price;
    double size;
    Analyzer* analyzer = nullptr;
    
    //get new Limit Order message
    while(getline(std::cin, line)){
        if(line == "")
            break;
        try{
            std::stringstream ss(line);
            while(ss >> timestamp){
                
                ss >> inputType;
                if(inputType == "A"){
                    ss >> orderId >> side >> price >> size;
                    
                    //check validation
                    isValidInput(orderId, side, price, size);
                    
                    //store side information
                    sideMap[orderId] = side;
                    
                    //choose right analyzer
                    analyzer = bidAnalyzer;
                    if(side == "S")
                        analyzer = askAnalyzer;
                    
                    //add new limit order to analyzer
                    analyzer->add(orderId, price, size);
                }else if(inputType == "R"){
                    ss >> orderId >> size;
                    //load side information
                    side = loadSide(orderId);
                    
                    //check validation
                    isValidInput(orderId, size);

                    //choose right analyzer
                    if(side == "B")
                        analyzer = bidAnalyzer;
                    else
                        analyzer = askAnalyzer;
                    
                    //reduce exising limit order
                    analyzer->reduce(orderId, size);
                }else{
                    throw std::runtime_error("Cannot recognize this input type: \"" + inputType + "\". Input type must be either \"A\" or \"R\".");
                }
                
                //standard out
                std::cout << analyzer->getOutput(timestamp);
            }
        }catch(const std::exception& e){
            std::cout << "[Warning]: " << e.what() << std::endl;
        }
    }
    
    std::cout << "::::::::::::::::::::::::::::::::::" << std::endl;
    std::cout << "\nThank you for using Pricer!" << std::endl;
    std::cout << "Good Bye!" << std::endl;
}

std::string Pricer::loadSide(std::string id){
    if(sideMap.find(id) == sideMap.end())
        throw std::runtime_error("Cannot find an order-id: '" +id + "' )");
    return sideMap[id];
}

void Pricer::isValidInput(std::string id, std::string side, double price, double size){
    
    //side has to be either "B" or "A"
    if(side != "B" && side != "S"){
        throw std::runtime_error("order-side must be either 'B' or 'S'");
    }
    
    //price has to be number greater than 0
    if(price <= 0){
        throw std::runtime_error("limit price must be greater than 0.");
    }
    isValidInput(id, size);
}

void Pricer::isValidInput(std::string id, double size){
    //id shouldn't be empty
    if(id == ""){
        throw std::runtime_error("order-id cannot be empty");
    }
    
    //size should be number greater than 0;
    if(size < 1){
        throw std::runtime_error("order-size must be greater than 0.");
    }
}
