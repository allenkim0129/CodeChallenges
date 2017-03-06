//
//  BidAnalyzer.hpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#ifndef BidAnalyzer_hpp
#define BidAnalyzer_hpp

#include <stdio.h>
#include "Analyzer.h"

class BidAnalyzer: public Analyzer{
public:
    BidAnalyzer(double targetSize_):Analyzer(targetSize_){
        side = " S ";
    }

    bool canAddThisPos(double curPrice, double newPrice){
        return curPrice < newPrice;
    }
};
#endif /* BidAnalyzer_hpp */
