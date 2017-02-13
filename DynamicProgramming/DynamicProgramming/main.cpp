//
//  main.cpp
//  DynamicProgramming
//
//  Created by Allen Kim on 2/13/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#include <iostream>
#include "Fibonacci.h"

int main(int argc, const char * argv[]) {
    Fibonacci fib;
    
    unsigned int n = 3;
    unsigned int fibNum = fib.run(n);
    std::cout << "Fibonacci(" << n << "): " << fibNum << std::endl;
    std::cout << fib.toString();
    return 0;
}
