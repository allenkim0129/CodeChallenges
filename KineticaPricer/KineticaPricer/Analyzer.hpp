//
//  Analyzer.hpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//


#ifndef Analyzer_hpp
#define Analyzer_hpp

//standard libraries
#include <iostream>
#include <list>
#include <sstream>
#include <iomanip>
#include <cmath>   //for rounding totalPrice
#include <stdexcept>

struct LimitOrder{
        std::string id;
        double price;
        double size;
        bool doubleargetShare;
    };

class Analyzer{    
public:
    //constructors
    Analyzer();
    Analyzer(double targetSize_, std::string side_);
    
    //main functions
    void add(std::string id, double price, double size);
    void reduce(std::string id, double size);
    std::string getOutput(std::string timestamp);
    
private:
    //helper functions
    void recAdd(std::list<LimitOrder>::iterator it, LimitOrder newOrder, double numShareSoFar, double bestPriceSoFar);
    void recReduce(std::list<LimitOrder>::iterator it, std::string id, double size, double numShareSoFar, double bestPriceSoFar);
    void recUpdateTargetShares(std::list<LimitOrder>::iterator it);
    void updateTargetShares(std::list<LimitOrder>::iterator it, double numShareSoFar, double bestPriceSoFar);
    bool canAddThisPos(double curPrice, double newPrice);
    
    //debug function
    void prdoubleOrderList();
    
    //variables
    std::list<LimitOrder> orders;               //contains list of limit orders and thier information
    double targetSize;                          //target size
    bool targetShareUpdated;                    //checks if target shares are updated
    double numTargetShare;                      //current number of shares from orders
    double totalPrice;                          //best total price with current best orders
    double prevPrice;                           //total price before 'add' or 'reduce' orders
    std::string side;                           //side information. ('S' or 'B')
    std::string action;                         //action information. ('S' or 'B')
};

#endif /* Analyzer_hpp */
