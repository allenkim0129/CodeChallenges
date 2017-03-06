//
//  BookAnalyzer.cpp
//  Pricer
//
//  Created by Allen Kim on 3/4/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include <stdio.h>
#include <sstream>
#include <string>
#include <iomanip>

#include "BookAnalyzer.h"

BookAnalyzer::BookAnalyzer(int targetSize_){
    targetSize = targetSize_;
    bestBid = -1;
    bestAsk = -1;
    lastTopBidID = "";
    lastTopAskID = "";
}

BookAnalyzer::~BookAnalyzer(){
    //drop bidList & askList;
}

void BookAnalyzer::recAdd(std::list<LimitOrder>::iterator it, std::list<LimitOrder> &order, std::string side, LimitOrder lo){
    //base case
    if(it == order.end()){
        order.emplace(it, lo);
        return;
    }
    if(side == "B"){
        if(it->price < lo.price){
            order.emplace(it, lo);
            return;
        }
        if(it->id == lastTopBidID)
            bidChanged =  false;
    }else if(side == "S"){
        if(it->price > lo.price){
            order.emplace(it, lo);
            return;
        }
        if(it->id == lastTopAskID)
            askChanged =  false;
    }
    
    //recursive
    return recAdd(++it, order, side, lo);
}

void BookAnalyzer::add(std::string id, std::string side, float price, int size){
//    //if id already exist, throw an error
//    if(sideMap.find(id) != sideMap.end())
//        throw std::runtime_error("This id already exist. Please check the id again!");
    
    sideMap[id] = side;
    LimitOrder lo = {id, price, size};
    
    //start adding a new limited-order to either Bid/Ask list
    std::list<LimitOrder>::iterator it;
    if(side == "B"){
        bidChanged = true; //initialize
        recAdd(bidList.begin(), bidList, side, lo);
    }else if(side == "S"){
        askChanged = true; //initialize
        recAdd(askList.begin(), askList, side, lo);
    }
}

void BookAnalyzer::recReduce(std::list<LimitOrder>::iterator it, std::list<LimitOrder> order, std::string side, std::string id, int size){
    //base case
    if(it == order.end())
        throw std::runtime_error("reduce error");
    
    if(it->id == id){
        if(it->size > size)
            it->size -= size;
        else if(it->size == size){
            order.erase(it);
        }else{
            throw std::runtime_error("Cannot reduce size of this order, because it exceed size of the current order size.");
        }
        return;
    }
    
    if(side == "B"){
        if(it->id == lastTopBidID)
            bidChanged = false;
    }else if(side == "S"){
        if(it->id == lastTopAskID)
            askChanged = false;
    }
    
    //recursive

    recReduce(++it, order, side, id, size);
    return;
}


void BookAnalyzer::reduce(std::string id, int size){
    std::list<LimitOrder>::iterator it;
    if(sideMap[id] == "B"){
        bidChanged = true; //initialize
       recReduce(bidList.begin(), bidList, "B", id, size);
    }else if(sideMap[id] == "S"){
        askChanged = true; //initialize
        recReduce(askList.begin(), askList, "S", id, size);
    }
}

bool BookAnalyzer::recCalcBest(std::list<LimitOrder>::iterator it, std::list<LimitOrder> &list, std::string side, int localSize, float localBestPrice){
    //base cases
    if(localSize == 0){
        if(side == "B" && bestBid != localBestPrice){
            lastTopBidID = (--it)->id;
            bestBid = localBestPrice;
        }else if(side == "S" && bestAsk != localBestPrice){
            lastTopAskID = (--it)->id;
            bestAsk = localBestPrice;
        }else{
            return false;
        }
        return true;
    }else if(it == list.end()){
        if(side == "B"){
            bestBid = -1;
        }else{
            bestAsk = -1;
        }
        return false;
    }
    
    //recursive part
    int curOrderSize = it->size;
    if(localSize < it->size)
        curOrderSize = localSize;
    localBestPrice += it->price * curOrderSize;
    
    return recCalcBest(++it, list, side, localSize - curOrderSize, localBestPrice);
}

bool BookAnalyzer::calcBest(std::string side){
    if(side == "B"){
        if(!bidChanged)
            return false;
        lastTopBidID = "";
        return recCalcBest(bidList.begin(), bidList, side, targetSize, 0);
    }else if(side == "S"){
        if(!askChanged)
            return false;
        lastTopAskID = "";
        return recCalcBest(askList.begin(), askList, side, targetSize, 0);
    }else
        return false;//shouldn't hit here
}

bool BookAnalyzer::outputUpdated(std::string side){
    if(side == "B" && bestBid >= 0)
        return bidChanged;
    else if(side == "S" && bestAsk >= 0)
        return askChanged;
    
    return false;
}


std::string BookAnalyzer::getOutput(std::string timestamp, std::string side){
    std::stringstream ss;
    if(side == "B"){
        float prevBestBid = bestBid;
        if(calcBest(side)){
            ss << timestamp << " S " << std::fixed << std::setprecision(2) << bestBid << "\n";
        }else{
            if(prevBestBid != -1)
                ss << timestamp << " S NA\n";
        }
    }else{
        float prevBestAsk = bestAsk;
        if(calcBest(side)){
            ss << timestamp << " B " << std::fixed << std::setprecision(2) << bestAsk << "\n";
        }else{
            if(prevBestAsk != -1)
                ss << timestamp << " B NA\n";
        }
    }
    
    return ss.str();
}

std::string BookAnalyzer::getSide(std::string id){
    return sideMap[id];
}

////debugging functions
//void BookAnalyzer::printBidList(){
//    size_t size = bidList.size();
//    std::cout << "\nBid list size: " << size << std::endl;
//    for(LimitOrder lo: bidList){
//        std::cout << lo.side << " " << lo.price << " " << lo.size << std::endl;
//    }
//}
//void BookAnalyzer::printAskList(){
//    size_t size = askList.size();
//    std::cout << "\nAsk list size: " << size << std::endl;
//    for(LimitOrder lo: askList){
//        std::cout << lo.side << " " << lo.price << " " << lo.size << std::endl;
//    }
//}
