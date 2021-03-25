//
//  main.cpp
//  PartitionSubsetSum
//
//  Created by Mehtab Ali Syed (CS) on 28/12/20.
//  Copyright © 2020 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>

using namespace std;
class Solution {
public:
    
    bool Partition(vector<int> & nums,vector<bool>& visited,int part,int subsetsum,int curr,int nextIdx)
    {
        if(part ==0 )
        {
            return true;
        }
        if(curr ==subsetsum)
        {
            return Partition(nums,visited,part-1,subsetsum,0,0);
        }
        for(int i =0;i < nums.size();++i)
        {
            if(!visited[i] && ((curr + nums[i]) <=subsetsum)) {
                visited[i] = true;
                
                if(Partition(nums,visited,part,subsetsum, curr + nums[i],i+1))
                   return true;
                visited[i] = false;
            }
        }
                   return false;
    }
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        
        int sum = accumulate(nums.begin(),nums.end(),0);
        
        int subsetSum = sum /k ;
        if(sum %k != 0)
            return false;
         vector<bool> visited(nums.size(),false);
        return Partition(nums,visited,k,subsetSum,0,0);
        
        
    }
};

class Solution1 {
    int maxcount = 0;
    set<int> s;
    set<int> result;
public:
    //
   // sort the numbers
    
  
    
 void  dfs(vector<int> & nums ,vector<bool> & visited,int idx ,int count)
    {
        if(count > maxcount)
        {
            maxcount = max(count,maxcount);
            
                result.insert(s.begin(),s.end());
        }
        
        for(int i= idx;i < nums.size();++i)
        {
            if(visited[i])
                continue;
            for(int j = i+1;j < nums.size();++j)
            {
                if(!visited[j] && (nums[j]% nums[i]==0))
                {
                    visited[i]= true;
                    visited[j]= true;
                    s.insert(nums[i]);
                    s.insert(nums[j]);
                    dfs(nums,visited,i+1,count+1);
                    s.erase(nums[i]);
                    s.erase(nums[j]);
                    visited[i]=false;
                    visited[j]= false;
                }
            }
        }
        
    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        
        vector<bool> visited(nums.size(),false);
        dfs(nums,visited,0,0);
        vector<int> ret;
        copy(result.begin(),result.end(),back_inserter(ret));
        return ret;
        
    }
};
using Vec = vector<int> ;
class Solution2
{
    map<int,vector<int>> subsetMap;
public:
    vector<int> eds(vector<int> & nums,int i)
    {
        if(subsetMap.count(i))
            return subsetMap[i];
        Vec maxset;
        
        for(int k=0;k <i;++k)
        {
            if(nums[i] % nums[k]==0)
            {
                auto subset = eds(nums,k);
                if(maxset.size() < subset.size())
                    maxset = subset;
            }
            
            
        }
        maxset.push_back(nums[i]);
        subsetMap[i] = maxset;
        return maxset;
    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        
        sort(nums.begin(),nums.end());
        
        vector<int> maxsubset;
        
        for(int i=0;i < nums.size();++i)
        {
            
            auto subset = eds(nums,i);
            if(maxsubset.size() < subset.size())
                maxsubset = subset;
        }
        
        return maxsubset;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //Solution2 s2;
    
    Solution2 s1;
    
    vector<int> vec = {1,2,4,7,8};
    auto v = s1.largestDivisibleSubset(vec);
    
    cout << "Element of the vector" << endl;
    ostream_iterator<int> os(cout," ");
    copy(v.begin(),v.end(),os);
    
    return 0;
    Solution s;
    vector<int> nums ={815,625,3889,4471,60,494,944,1118,4623,497,771,679,1240,202,601,883};
    //3
    int part = 3;
    
    auto ret =s.canPartitionKSubsets(nums, part);
    
    cout << "Can partiton " << ret << endl;
    return 0;
}
