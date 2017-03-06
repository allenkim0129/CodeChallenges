//
//  BookAnalyzer.h
//  Pricer
//
//  Created by Allen Kim on 3/4/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#ifndef BookAnalyzer_h
#define BookAnalyzer_h

#include <iostream>
#include <unordered_map>
#include <list>

struct LimitOrder{
    std::string id;
    float price;
    int size;
};

class BookAnalyzer{
public:
    BookAnalyzer(int targetSize_);
    ~BookAnalyzer();
    
    void recAdd(std::list<LimitOrder>::iterator it, std::list<LimitOrder> &order, std::string side, LimitOrder lo);
    void add(std::string id, std::string side, float price, int size);
    void recReduce(std::list<LimitOrder>::iterator it, std::list<LimitOrder> order, std::string side, std::string id, int size);
    void reduce(std::string id, int size);
    bool recCalcBest(std::list<LimitOrder>::iterator it, std::list<LimitOrder> &list, std::string side, int localSize, float localBestPrice);
    bool calcBest(std::string side);
    bool outputUpdated(std::string side);
    std::string getOutput(std::string timestamp, std::string side);
    
    std::string getSide(std::string id);
    
//    //debuging functions
//    void printBidList();
//    void printAskList();
//    void printIdMap();
    
private:
    std::list<LimitOrder> bidList;
    std::list<LimitOrder> askList;
    std::unordered_map<std::string, std::string> sideMap;
    int targetSize;
    bool bidChanged;
    float bestBid;
    bool askChanged;
    float bestAsk;
    
    std::string lastTopBidID;
    std::string lastTopAskID;
};

#endif /* BookAnalyzer_h */
