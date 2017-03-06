//
//  Analyzer.h
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//


#ifndef Analyzer_h
#define Analyzer_h

//standard libraries
#include <iostream>
#include <list>
#include <sstream>
#include <iomanip>
#include <math.h>   //for rounding totalPrice



class Analyzer{
protected:
    struct LimitOrder{
        std::string id;
        double price;
        double size;
        bool doubleargetShare;
    };
    
    std::list<LimitOrder> orders;               //contains list of limit orders and thier information
    double targetSize;                          //target size
    bool targetShareUpdated;                    //checks if target shares are updated
    double numTargetShare;                      //current number of shares from orders
    double totalPrice;                          //best total price with current best orders
    double prevPrice;                           //total price before 'add' or 'reduce' orders
    std::string side;                           //side information. ('S' or 'B')
    
public:
    Analyzer();
    Analyzer(double targetSize_){
        targetSize = targetSize_;
        
        targetShareUpdated = false;
        numTargetShare = 0;
        totalPrice = 0;
        prevPrice = 0;
    }
    
    //virtual function
    virtual bool canAddThisPos(double curPrice, double newPrice) = 0;
    
    //main functions
    void add(std::string id, double price, double size){
        recAdd(orders.begin(), {id, price, size, false}, 0, 0);
    }
    
    void reduce(std::string id, double size){
        recReduce(orders.begin(), id, size, 0, 0);
    }
    
    std::string getOutput(std::string timestamp){
        std::stringstream ss;
        if(targetShareUpdated){
            ss << timestamp << side;
            if(numTargetShare == targetSize){
                totalPrice = std::round(totalPrice * 100) / 100;
                if(prevPrice == totalPrice)
                    return "";
                ss << std::fixed << std::setprecision(2) << totalPrice << "\n";
                prevPrice = totalPrice;
            }
            else{
                if(prevPrice == 0)
                    return "";
                
                ss << "NA\n";
                prevPrice = 0;
            }
        }
        
        return ss.str();
    }
    
private:
    //helper functions
    void recUpdateTargetShares(std::list<LimitOrder>::iterator it){
        //base cases
        if(it == orders.end())
            return;
        if(numTargetShare == targetSize){
            if(it->doubleargetShare){
                it->doubleargetShare = false;
                recUpdateTargetShares(++it);
            }
            return;
        }
        
        //recursive
        double numShare = it->size;
        if(numTargetShare + it->size > targetSize)
            numShare = targetSize - numTargetShare;
        numTargetShare += numShare;
        totalPrice += numShare * it->price;
        it->doubleargetShare = true;
        targetShareUpdated = true;
        
        recUpdateTargetShares(++it);
        return;
    }
    
    void updateTargetShares(std::list<LimitOrder>::iterator it, double numShareSoFar, double bestPriceSoFar){
        if(numShareSoFar < numTargetShare){
            numTargetShare = numShareSoFar;
            totalPrice = bestPriceSoFar;
        }
        recUpdateTargetShares(it);
    }
    
    void recAdd(std::list<LimitOrder>::iterator it, LimitOrder newOrder, double numShareSoFar, double bestPriceSoFar){
        //base case
        if(it == orders.end() || canAddThisPos(it->price, newOrder.price)){
            targetShareUpdated = false;
            it = orders.emplace(it, newOrder);
            updateTargetShares(it, numShareSoFar, bestPriceSoFar);
            return;
        }
        
        double numShare = it->size;
        double price = it->price * numShare;
        recAdd(++it, newOrder, numShareSoFar + numShare, bestPriceSoFar + price);
    }
    
    void recReduce(std::list<LimitOrder>::iterator it, std::string id, double size, double numShareSoFar, double bestPriceSoFar){
        //base case
        if(it == orders.end()) std::cout << "This should never be true" << std::endl;
        
        if(it->id == id){
            targetShareUpdated = false;
            if(it->size > size)
                it->size -= size;
            else if(it->size == size){
                it = orders.erase(it);
                targetShareUpdated = true;
            }else{
                throw std::runtime_error("Cannot reduce size of this order, because it exceed size of the current order size.");
            }
            updateTargetShares(it, numShareSoFar, bestPriceSoFar);
            return;
        }
        
        double numShare = it->size;
        double price = it->price * numShare;
        recReduce(++it, id, size, numShareSoFar + numShare, bestPriceSoFar + price);
        return;
    }
    
    //debug function
    void prdoubleOrderList(){
        size_t size = orders.size();
        std::cout << "\nlist size: " << size << std::endl;
        for(LimitOrder order: orders){
            std::cout << order.id << " " << order.price << " " << order.size;
            if(order.doubleargetShare)
                std::cout << " True" << std::endl;
            else
                std::cout << " False" << std::endl;
        }
        
        std::cout << "numTargetShare: " << numTargetShare << std::endl;
        std::cout << "totalPrice: " << totalPrice << std::endl;
        std::cout << "targetShareUpdated: ";
        if(targetShareUpdated)
            std::cout << "True" << std::endl << std::endl;
        else
            std::cout << "False" << std::endl << std::endl;
    }
};

#endif /* Analyzer_h */
