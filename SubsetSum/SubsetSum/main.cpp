//
//  main.cpp
//  SubsetSum
//
//  Created by Mehtab Ali Syed (CS) on 06/01/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <optional>
#include <numeric>
#include <functional>
#include<string>

#include<unordered_map>


using namespace std;

using boolVector = vector<vector<optional<bool>>>;
class Solution {
    
    
public:
    
    
    bool dfs(vector<int>& nums,boolVector& dp,int i,int curr)
    {
        if(curr == 0)
            return true;
        if(i > nums.size()  || curr < 0)
            return false;
            
        if(dp[i][curr]!= nullopt)
            return (dp[i][curr]==true);
            
         bool val = dfs(nums,dp,i +1, curr-nums[i])
                        ||
                        dfs(nums,dp,i+1,curr);
                
            dp[i][curr] = val;
        
        return val;
        
    }
    
    bool canPartition(vector<int>& nums) {
        
        int sum = accumulate(nums.begin(),nums.end(),0);
        
        int n = nums.size();
        if(sum & 1)
            return false;
        else
            sum = sum >> 1;
         vector<vector<optional<bool>>> dp(n+1,
                                           vector<optional<bool>>(sum+1,nullopt));
        return dfs(nums,dp,0,sum);
     
        
        // sum , num
        
    }
};


string minWindow1(string S, string T) {
       
     
           unordered_map<char,vector< int > > StringMp;
       int idx =S.size()-1;
       for_each(S.rbegin(),S.rend(),[&idx,&StringMp](char c) {
           StringMp[c].push_back(idx--);
                                                        });
       int i=0, j=0;
       int start =0;
       int endoffset = 0;
       int minDiff = INT_MAX;
       int finalStart=0;
    int last = 0;
       while(j < S.size())
       {
           int k =0;
           
           while(k < T.size())
           {
               if(StringMp.count(T[k]))
               {
                   auto &vec = StringMp[T[k]];
                   if(vec.back() < (last))
                   {
                       vec.pop_back();
                       continue;
                   }
                   last = vec.back();
                   if(k==0)
                   {
                       start = vec.back();
                   }
                  
                   vec.pop_back();
                   k++;
                   
               }else
               {
                   break;
               }
           }
           
           int diff = last - start;
           
           if(minDiff > diff )
           {
               minDiff = diff;
               finalStart = start;
           }
           j = start +1;
       }
       return (minDiff ==INT_MAX) ? "" : S.substr(finalStart,minDiff);
           
       
   }
 unordered_map<char,vector<int>> Idxmap;
int reverse_match(string &S, string &T,int i,int j)
{
    int right = T.size()-1;
    int idx = j;
    int prev = j;
    while(right >=0)
    {
        
        idx = Idxmap[T[right]].back();
        if(prev < idx)
        {
            Idxmap[T[right]].pop_back();
            continue;
            
        }
        prev = idx;
        
        Idxmap[T[right]].pop_back();
        
      //  if(S[j]== T[right])
        {
            cout << "String remaining :" << S.substr(i,idx+1-i) << endl;
            right--;
        }
        j--;
        
    }
   
        return idx;
    
}
 string minWindow(string S, string T) {
 //string S ="abcdebdde";
// string x = "bde";
     int j =0;
     int len = S.size();
     int diff =INT_MAX;
     int start = -1;
     int i=0;
     int minStart = INT_MAX;
    
     while(i < len)
     {
         
         if(S[i] == T[j])
         {
             if(start<0)
                 start = i;
             j++;
         }
         Idxmap[S[i]].push_back(i);
         i++;
         if(j ==T.size())
         {
             cout << "String in normal search :  " << S.substr(start,i) << endl;
             if(diff > (i-start)){
                 cout << "Fist diff is " << i-start << endl;
               diff = i - start;
               minStart = start;
             }
         
             //match in reverse
             int idx =reverse_match(S,T,start,i);
             cout << "String in reverse search : " << S.substr(idx,i) << endl;
             if(diff > i-idx )
             {
                 diff = i-idx;
                 minStart = idx;
             }
         
             j=0;
             start =-1;
             i = idx +1;
         }
     }
     cout << "diff is " << diff << endl;
     return (diff==INT_MAX) ? "" : S.substr(minStart,diff);
 
 }
//nevavyrpduigitmrimtaslzboauwbluvlfqquocxrzrbvvplsivujojscytmeyjolvvyzwizpuhejsdzkfwgqdbwinkxqypaph

int main(int argc, const char * argv[]) {
    // insert code here...
    string S="ffynmlzesdshlvugsigobutgaetsnjlizvqjdpccdylclqcbghhixpjihximvhapymfkjxyyxfwvsfyctmhwmfjyjidnfryiyajmtakisaxwglwpqaxaicuprrvxybzdxunypzofhpclqiybgniqzsdeqwrdsfjyfkgmejxfqjkmukvgygafwokeoeglanevavyrpduigitmrimtaslzboauwbluvlfqquocxrzrbvvplsivujojscytmeyjolvvyzwizpuhejsdzkfwgqdbwinkxqypaphk"; //="ffynmlzesdshlvugsigobutgaetsnjlizvqjdpccdylclqcbghhixpjihximvhapymfkjxyyxfwvsfyctmhwmfjyjidnfryiyajmtakisaxwglwpqaxaicuprrvxybzdxunypzofhpclqiybgniqzsdeqwrdsfjyfkgmejxfqjkmukvgygafwokeoeglanevavyrpduigitmrimtaslzboauwbluvlfqquocxrzrbvvplsivujojscytmeyjolvvyzwizpuhejsdzkfwgqdbwinkxqypaphktonqwwanapouqyjdbptqfowhemsnsl";//"cnhczmccqouqadqtmjjzl";
    //"cm""abcdebdde";
   // "bde"//"cnhczmccdqtmjjzl";//"abcdebdde";
    string  x= "ntimcimzah";//"cm";

    cout << "Minimum Windows is " << minWindow(S,x);
    return 0;
    Solution s;
    vector<int> nums = {5,5,10};
    
    int val = s.canPartition(nums);
    
    cout << " The value of Partition is " << val << endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}
