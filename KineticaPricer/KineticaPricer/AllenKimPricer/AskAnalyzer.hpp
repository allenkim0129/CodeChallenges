//
//  AskAnalyzer.hpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#ifndef AskAnalyzer_hpp
#define AskAnalyzer_hpp

#include <stdio.h>
#include "Analyzer.h"

class AskAnalyzer: public Analyzer{
public:
    AskAnalyzer(double targetSize_):Analyzer(targetSize_){
        side = " B ";
    }
    
    bool canAddThisPos(double curPrice, double newPrice){
        return curPrice > newPrice;
    }
};


#endif /* AskAnalyzer_hpp */
