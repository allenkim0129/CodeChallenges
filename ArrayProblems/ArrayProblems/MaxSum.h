//
//  MaxSum.h
//  ArrayProblems
//
//  Created by Allen Kim on 2/14/17.
//  Copyright © 2017 Allen. All rights reserved.
//

#ifndef MaxSum_h
#define MaxSum_h

#include <iostream>
#include <vector>

/*
  calculate a subarray which makes max sum.
 
 
 
*/
class MaxSum{
public:
    MaxSum(std::vector<int> vec_){
        vec = vec_;
    }
    
    int calcMaxSum(){
        int localStart = start = 0;
        end = 0;
        if(vec.size() == 0)
            return 0;
        int localMaxSum = maxSum = vec[0];
        for(int i = 1; i < vec.size(); i++){
            int curElement = vec[i];
            if(localMaxSum + curElement > curElement){
                localMaxSum += curElement;
                if(localMaxSum > maxSum){
                    maxSum = localMaxSum;
                    start = localStart;
                    end = i;
                }
            }else{
                localMaxSum = curElement;
                localStart = i;
                if(localMaxSum > maxSum){
                    maxSum = localMaxSum;
                    start = i;
                    end = i;
                }
            }
        }
        
        return maxSum;
    }
    
    int getMaxSum(){
        return maxSum;
    }
    
    int getStart(){
        return start;
    }
    
    int getEnd(){
        return end;
    }
private:
    std::vector<int> vec;
    int maxSum;
    int start;
    int end;
};

#endif /* MaxSum_h */
