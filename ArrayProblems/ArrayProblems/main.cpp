//
//  main.cpp
//  ArrayProblems
//
//  Created by Allen Kim on 2/13/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include <iostream>
#include <vector>

#include "MaxSum.h"

int main(int argc, const char * argv[]) {
    int array[] = {4, -9, 2, 3, -8, 6, -3, -3, 4, 4};
    std::vector<int> vec(array, array + sizeof(array) / sizeof(int));
    
    for(auto i: vec) std::cout << " " << i;
    std::cout << std::endl;
    MaxSum ms(vec);
    std::cout << "maxSum: " << ms.calcMaxSum() << std::endl;
    std::cout << "start: " << ms.getStart() << " end: " << ms.getEnd() << std::endl;
    
    return 0;
}
