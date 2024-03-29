 #include<string>
 #include<vector> 
 #include<unordered_map>

 using namespace std;

 string minWindow(string S, string T) {
        
      
            unordered_map<char,vector< int > > StringMp;
        int idx =S.size()-1;
        for_each(S.rbegin(),S.rend(),[&idx,&StringMp](char c) {                   
            StringMp[c].push_back(idx--);
                                                         });
        int i=0, j=0;
        int start =INT_MAX;
        int endoffset = 0;
        int minDiff = INT_MAX;
        int finalStart=0;
        while(j < S.size())
        {
            int k =0;
            
            while(k < T.size())
            {
                if(StringMp.count(T[k]))
                {
                    auto &vec = StringMp[T[k]];
                    if(vec.back() < (j+k))
                    {
                        vec.pop_back();
                        continue;
                    }
                    if(k==0)
                    {
                        start = vec.back();
                    }
                    if(k ==(T.size()-1))
                    {
                        endoffset = vec.back();
                    }
                    vec.pop_back();
                    k++;
                    
                }else
                {
                    break; 
                }
            }
            int diff = endoffset - start;
            
            if(minDiff > diff )
            {
                minDiff = diff;
                finalStart = start;
            }
            j = start +1;
        }
        return (minDiff ==INT_MAX) ? "" : S.substr(finalStart,minDiff);
            
        
    }

    int main()
    {
        string S ="abcdebdde";
        string x = "bde";

        minWindow(S,x);

    }