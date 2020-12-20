//
//  main.cpp
//  LargestRectangleLength
//
//  Created by Mehtab Ali Syed (CS) on 17/12/20.
//  Copyright © 2020 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using Vvec =vector<vector<int>> ;
 int dirs[4][2] ={{0,1},{1,0},{-1,0},{0,-1}};
class Solution
{
    vector<int> dp;
    int rlen=0;
    int clen = 0;
   
public:
bool IsValid(int x,int y)
{
    if(x <0 || y < 0 || x > (rlen-1) || y > (clen-1))
    {
        return false;
    }
    return true;
    
}
int dfs(Vvec & matrix,int x,int y)
{
     int idx = (x*rlen) +y;
   
    if(dp[idx])
        return dp[idx];
    
    int len =1;
    for(int dir =0;dir < 4;++dir)
    {
        int i= dirs[dir][0] +x;
        int j = dirs[dir][1] +y;
        if(!IsValid(i, j))
            continue;
        if(matrix[x][y] > matrix[i][j])
        {
            
             len= max(1 + dfs(matrix,i,j),len);
        }
        
    }
    dp[idx] = len ;
   
    
    return dp[idx];
}
    
int longestIncreasingPath(vector<vector<int>>& matrix)
{
     rlen = matrix.size();
     clen = matrix[0].size();
    dp.resize(rlen*clen,0);
    int maxlen = 0;
    
    
    for(int i =0;i < rlen;++i)
    {
        for(int j =0;j < clen;++j)
        {
    
            
            int idx = (i*rlen) +j;
            if(dp[idx] ==0)
            {
                dp[idx] = dfs(matrix,i,j);
                
            }
            maxlen = max(dp[idx],maxlen);
        }
        
    }
    return maxlen;
}
};
//11:53
class TopoLogicalSoln
{
    int rlen = 0;
    int clen = 0;

    bool IsValid(int x,int y)
    {
        if(x <0 || y < 0 || x > (rlen-1) || y > (clen-1))
        {
            return false;
        }
        return true;
        
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
       rlen = matrix.size();
       clen = matrix[0].size();
        
        Vvec depends(rlen,vector<int>(clen,0));
        
        for(int i =0;i < rlen;++i)
        {
            for(int j=0;j < clen;++j)
            {
                for(int d =0; d< 4;++d)
                {
                    int newx = i + dirs[d][0];
                    int newy = j + dirs[d][1];
                    if(!IsValid(newx, newy))
                        continue;
                    if(matrix[i][j] > matrix[newx][newy])
                    {
                        depends[i][j]++;
                    }
                }
                
            }
        }
        queue<vector<int>> q;
        for(int i =0;i < rlen;++i)
        {
                  for(int j=0;j < clen;++j)
                  {
                      if(depends[i][j]==0)
                          q.push({i,j});
                  }
              
        }
        int ht=0;
        while(!q.empty())
        {
            int qlen = q.size();
            ht++;
            while(qlen--)
            {
                auto pos = q.front();
                q.pop();
            
            
                int i = pos[0];
                int j = pos[1];
                for(int d =0; d< 4;++d)
                {
                        int newx = i + dirs[d][0];
                        int newy = j + dirs[d][1];
                        if(!IsValid(newx, newy))
                            continue;
                        if(matrix[i][j] < matrix[newx][newy])
                        {
                                   if((--depends[newx][newy])==0)
                                       q.push({newx,newy});
                            
                        }
                }
            }
            
        }
        
        return ht;
        
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int n = 15;
    int curr = 1;
    
    
     while(curr <=n && (curr % 3 ==0 || curr % 5 ==0))
     {
         printf("Inside");
     }
    
    
    Vvec matrix ={ {9,9,4},
    {6,6,8},
        {2,1,1}};
   
    /*{{3,4,5},
        {3,2,6},
        {2,2,1}
    };
     */
    TopoLogicalSoln s;
    
    
  /*
    ;
    */
   // Solution s;
    int len = s.longestIncreasingPath(matrix);
    cout << "Longest size is " << len << endl;
    return 0;
}
