//
//  main.cpp
//  binary_search
//
//  Created by Mehtab Ali Syed (CS) on 05/01/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>

class ArrayReader
{

    std::vector<int>& vec;
    
public:
    ArrayReader(std::vector<int>& v):vec(v){};
    int get(int idx) const
    {
        if(idx > vec.size()-1)
            return INT_MAX;
        else
            return vec[idx];
    }
};

class Solution {
public:
    int bsearch(const ArrayReader& reader,int low ,int high,int target)
    {
        if(low > high)
            return -1;
        int mid = (low +high) /2;
            
        int val = reader.get(mid);
        if(val == target)
        {
            return mid;
        }
        
        if(val ==INT_MAX || val > target)
          return bsearch(reader,low,mid-1,target);
        else
         return bsearch(reader,mid+1,high,target);
    }
    
    int search(const ArrayReader& reader, int target) {
        
        int idx = 1;
        
        int val = reader.get(0);
        while(val < target)
        {
            idx = idx << 1;
            val = reader.get(idx) ;
            
            
        }
        int prev = idx >> 1;
        
        return bsearch(reader,prev,idx,target);
        
    }
};

int main(int argc, const char * argv[]) {
    std::vector<int> v = {-1,0,3,5,9,12};
    ArrayReader arr(v);
    
    Solution s;
    std :: cout << "Idx is at " << s.search(arr, 12);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
