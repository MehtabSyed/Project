//
//  main.cpp
//  NoOfIslands
//
//  Created by Mehtab Ali Syed (CS) on 26/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
    vector<int> parent;
    vector<int> rank;
    int row;
    int col;
    int count=0;
public:
    UnionFind(vector<vector<int>>& grid)
    {
         row = grid.size();
         col = grid[0].size();
      //  count = row * col;
        
        for(int i =0;i < row;++i)
        {
            for(int j=0;j < col;++j)
            {
                if(grid[i][j]==1)
                {
                    parent.push_back(i*col + j);
                    count++;
                }else
                    parent.push_back(-1);
                
                rank.push_back(0);
            
                
            }
            
        }
    }
    int Find(int i)
    {
        if(parent[i]!=i)
            parent[i]= Find(parent[i]);
        return parent[i];
    }
    
    void Union(int x,int y)
    {
        
        int parent1 = Find(x);
        int parent2 = Find(y);
        
        if(parent1 != parent2)
        {
            if(rank[parent2] > rank[parent1])
            {
                parent[parent1] = parent2;
                rank[parent2]  +=1;
            }else {
                parent[parent2] = parent1;
                rank[parent1] +=1;
            }
        
            count--;
        }
    }
    int GetCount()
    {
        return count;
    }
    
};
class Solution2
{
public:
     int numIslands(vector<vector<int>>& grid) {
         
         UnionFind uf(grid);
         int row = grid.size();
         
         int col = grid[0].size();
         
         for(int i =0 ; i < row ;++i)
         {
             for(int j=0;j < col;++j)
             {
                 if(i-1 >= 0 && grid[i-1][j] ==1)
                     uf.Union(i*col+j,(i-1)*col+j);
                 if((i+1) < row && grid[i+1][j]==1)
                     uf.Union(i*col+j,(i+1)*col +j);
                 if((j-1) >=0 && grid[i][j-1]==1)
                     uf.Union(i*col+j,i*col+(j-1));
                 if((j+1)<col && grid[i][j+1]==1)
                     uf.Union(i*col+j,i*col+(j+1));
             }
         }
     
         return uf.GetCount();
     }
};



class Solution {
      int rlen=0;
    int clen=0;
   
public:
    
    
    
    int numIslands(vector<vector<int>>& grid) {
        
         rlen = grid.size();
        
         clen = grid[0].size();
        int count =0;
        
        vector<vector<int>> dp(rlen,vector<int>(clen,0));
        
        
       for(int i =0;i < rlen ;++i)
       {
            for(int j = 0;j < clen;++j)
            {

                if(grid[i][j] == 1)
                {
                    if(dp[i][j]==1)
                        continue;
                    //dp[i][j] = 1;
                    dfs(i,j,dp,grid);
                    count++;

                }

            }
       }
     
        return count;
    }

    bool isValid (int x,int y)
    {
            if(x < 0  || x>= rlen || y < 0 || y >=clen)
                return false;
            else
                return true;
        
    };
    void  dfs(int i ,int j,vector<vector<int>> &dp,vector<vector<int>> & grid)
    {
         int dirs[][3]= {{0,1},{1,0},{-1,0},{0,-1}};
            
        dp[i][j] =1;
            for(int pos =0; pos < 4;++pos)
            {
                int x = i + dirs[pos][0];
                int y = j + dirs[pos][1];
                
                if(isValid(x,y) && !dp[x][y])
                {
                    if(grid[x][y]==1) {
                        cout << "\nExploring pos" << "x :" << x << "y: " << y << endl;
                        dfs(x,y,dp,grid);
                    }
                }
            }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
 //   Solution s1;
    Solution2 s1;
    vector<vector<int>> vvec = {{1,1,0},{1,0,0}};//{{1,1},{1,1,0},{0,1,0}};
    cout << "Number of islands" << s1.numIslands(vvec) << endl;;
 //   std::cout << "Hello, World!\n";
    return 0;
}
