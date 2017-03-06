//
//  main.cpp
//  KineticaPricer
//
//  Created by Allen Kim on 3/5/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include <iostream>
#include "Pricer.hpp"

int main(int argc, const char * argv[]) {
    double targetSize;
    std::string temp;
    
    std::cout << "Please enter \"target_size\": ";
    
    std::getline(std::cin, temp);
    targetSize = std::stod(temp);
    Pricer pricer(targetSize);
    pricer.run();
    
    return 0;
}
