//
//  Fibonacci.h
//  DynamicProgramming
//
//  Created by Allen Kim on 2/13/17.
//  Copyright (c) 2017 Allen. All rights reserved.
//

#ifndef interviewPrep_Fibonacci_h
#define interviewPrep_Fibonacci_h

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

class Fibonacci{
public:
    Fibonacci(){
    }
    
    unsigned int run(unsigned int n){
        return calcFibonacci(n);
    }
    
    std::string toString(){
        std::stringstream ss;
        ss << "savedFib [";
        bool first = true;
        for(auto map: savedFib){
            if(first){
                first = false;
            }else{
                ss << ", ";
            }
            ss << "fib(" << map.first << ")";
        }
        ss << "]\n";
        return ss.str();
    }

private:
    unsigned int calcFibonacci(unsigned int n){
        unsigned int fib = 0;
        if (n == 0) {
            fib = 0;
        }else if(n == 1){
            fib = 1;
        }else if(savedFib.find(n) != savedFib.end()){
            fib = savedFib[n];
        }else{
            fib = calcFibonacci(n-1) + calcFibonacci(n-2);
            savedFib[n] = fib;
        }
        return fib;
    }
    
    std::unordered_map<unsigned int, unsigned int> savedFib;
};

#endif
