//
//  Fibonacci.h
//  interviewPrep
//
//  Created by Allen Kim on 2/12/17.
//  Copyright (c) 2017 Allen. All rights reserved.
//

#ifndef interviewPrep_Fibonacci_h
#define interviewPrep_Fibonacci_h

#include <iostream>
#include <string>
#include <unordered_map>

class Fibonacci{
public:
    Fibonacci(){
    }
    
    unsigned int run(unsigned int n){
        return calcFibonacci(n, 0);
    }
    
    std::string toString(){
        return "";
    }

private:
    unsigned int calcFibonacci(unsigned int n, unsigned int indent){
        for(unsigned int i = 0; i < indent; i++){
            std::cout << "  ";
        }
        std::cout << "n: " << n << std::endl;
        unsigned int fib = 0;
        if (n == 0) {
            fib = 0;
        }else if(n == 1){
            fib = 1;
        }else if(savedFib.find(n) != savedFib.end()){
            fib = savedFib[n];
        }else{
            fib = calcFibonacci(n-1, indent + 1) + calcFibonacci(n-2, indent + 1);
            savedFib[n] = fib;
        }
//        std::cout << "fib: " << fib << std::endl;
        return fib;
    }
    
    std::unordered_map<unsigned int, unsigned int> savedFib;
};

#endif
