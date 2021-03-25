//
//  main.cpp
//  TestThinkC++
//
//  Created by Mehtab Ali Syed (CS) on 01/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <map>

using namespace std;
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
    : m_valBegin(val)
    {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
// INSERT YOUR SOLUTION HERE
        
        if(keyEnd < keyBegin)
            return;
        
        typename std::map<K,V>::iterator beginItr;
        typename std::map<K,V>::iterator endItr;
        
        auto startPart = m_map.lower_bound(keyBegin);
        auto endPart = m_map.upper_bound(keyEnd);
        
        auto count = std::distance(startPart, endPart);
        
        cout << "Distance is " << count << endl;
        
       
       
       
        if(endPart != m_map.begin()) {
            
            auto prevEndItr = std::prev(endPart);
            if(!(prevEndItr->second ==val))
            {
                
           
                if(prevEndItr->first  < keyEnd)
                {
                    
                   
                    if(count  && (keyBegin < prevEndItr->first ))
                    {
                        auto renewNode(m_map.extract(prevEndItr));
                               
                        renewNode.key() = keyEnd;
                        renewNode.mapped() = prevEndItr->second;
                       
                       endItr= m_map.insert(endPart,move(renewNode));
                        count--;
                        
                    }else {
                        
                         endItr = m_map.insert_or_assign(endPart, keyEnd,prevEndItr->second);
                    }
                  
                }   else {
                
                    endItr = prevEndItr;
                }
            }
            else {
                endItr = prevEndItr;
            }
        }else{
            //bInsertEnd= true;
           // endVal = m_valBegin;
           endItr = m_map.insert_or_assign(endPart, keyEnd,m_valBegin);
        }
        bool bNodeAssigned =false;
        if(startPart != m_map.begin())
        {
            auto prevItr = std::prev(startPart);
            
            if(prevItr->second == val)
            {
                beginItr = prevItr;
            }else
            {
                if(startPart !=m_map.end())
                {
                    auto renewItr = std::next(startPart);
                
                    if(count &&  (renewItr->first < keyEnd))
                    {
                        auto renewNode(m_map.extract(renewItr));
                                              
                        renewNode.key() = keyEnd;
                        renewNode.mapped() = val;
                                      
                        beginItr = m_map.insert(endPart,move(renewNode));
                        count--;
                        bNodeAssigned = true;
                                       
                    }
                }
                
            }
        }
        
        if(!bNodeAssigned)
        {
             beginItr = m_map.insert_or_assign(startPart, keyBegin,val);
        }
        
    
        if(beginItr!=m_map.end()) {
            auto nextIterOfBegin = std::next(beginItr);
       
            if (nextIterOfBegin != m_map.end())
            {
                
                    m_map.erase(nextIterOfBegin, endItr);
            }
        }
    
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};

int gcd(int num1 ,int num2)
{
    int div = min(num1,num2);
    int gcd=1;
    
    for(int i =div ; i > 1;--i)
    {
        
        while(num1)
        {
           if((num1 % i)==0 && (num2 % i)==0)
           {
               num1 /=i;
               num2 /=i;
               gcd *=i;
           }else {
               break;
           }
            
        }
        
    }
    return gcd;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    interval_map<int, char> map('Z');
       map.assign(4, 6, 'B');
       map.assign(1,3,'A');
      map.assign(7, 9, 'C');
    optional<bool> t;
    cout << "Gcd is " << gcd(10, 24) << endl;;
    
       cout << "Map of zero index is " << map[-4] << endl;
       int val;
       do
       {
           cout << "Please enter a value to test" << endl;
           cin >> val;
       int idx = val;
       cout << "Map value at" << idx << " is " << map[idx] << endl;
       
       }while(val);
    return 0;
}
