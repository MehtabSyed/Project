//
//  main.cpp
//  ThinkMap
//
//  Created by Mehtab Ali Syed (CS) on 26/01/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <map>
#include <limits>
#include <ctime>

using namespace std;
template<typename K>
bool operator<(const K& par1,const K& par2)
{
    return (par1 < par2 );
}

template<typename K, typename V>
class interval_map {
     V m_valBegin;
    std::map<K,V> m_map;

public:
    
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
#if 0
    void assign2(K const& keyBegin,K const& keyEnd,V const& val)
    {
        if(keyEnd < keyBegin)
            return ;
        typename map<K,V>::const_iterator itr;
        auto beginItr = m_map.lower_bound(keyBegin);
        bool beginPrev = false;
        if(beginItr !=m_map.end() && beginItr.first > keyBegin)
        {
            beginItr--;
            beginPrev =true;
        }
        
        typename map<K,V> ::const_iterator endItr;
        
        endItr = m_map.lower_bound(keyEnd);
        bool endPrev =false;
        if(endItr != m_map.end() && endItr.first > keyEnd)
        {
            endItr--;
            endPrev = true;
        }
        m_map.erase(beginItr,endItr);
        
        if(beginPrev==true )
        
        
    }
#endif
   void assignSub1( K const& keyBegin, K const& keyEnd, V const& val)
   {
       
       if(keyEnd < keyBegin)
           return;
       
       typename std::map<K,V>::iterator beginItr;
       typename std::map<K,V>::iterator endItr;
       
       auto startPart = m_map.lower_bound(keyBegin);
       auto endPart = m_map.upper_bound(keyEnd);
       
      
       
      
       if(endPart != m_map.begin()) {
             auto prevEndItr = std::prev(endPart);
           if(!(prevEndItr->second ==val))
           {
          
          
               if(prevEndItr->first  < keyEnd)
               {
                  
                   endItr = m_map.insert_or_assign(endPart, keyEnd,prevEndItr->second);
               }   else {
               
                   endItr = prevEndItr;
               }
           }
           else {
               endItr = prevEndItr;
           }
       }else{
           endItr = m_map.insert_or_assign(endPart, keyEnd,m_valBegin);
       }
       
       if(startPart != m_map.begin())
       {
           auto prevItr = std::prev(startPart);
           
           if(prevItr->second == val)
           {
               beginItr = prevItr;
           }else
           {
               beginItr = m_map.insert_or_assign(startPart, keyBegin,val);
           }
           
           
       }else
       {
           beginItr = m_map.insert_or_assign(startPart, keyBegin,val);
       }

       auto nextIterOfBegin = std::next(beginItr);
           if (nextIterOfBegin != m_map.end())
           {
                   m_map.erase(nextIterOfBegin, endItr);
           }
   }

    
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
    
       if (!(keyBegin < keyEnd))
        return;

    typename std::map<K, V>::iterator iterBegin; /*The new begin with val, can be begin()*/
    typename std::map<K, V>::iterator iterEnd;   /*the new end of val, can be end()*/

    auto lowerKeyBegin = m_map.lower_bound(keyBegin); //either end() or some iter whose key is not less than keyBegin. [1st O(logN)]
    auto upperKeyEnd = m_map.upper_bound(keyEnd); //some iter where keyEnd < key, or end()  [2nd O(logN)]
    auto prevKeyEnd = std::prev(upperKeyEnd);

    /*
    The next interval of the new interval starts at keyEnd if the previous value at keyEnd differed from val
    */
    if (!(prevKeyEnd->second == val))
    {
        // prevKeyEnd is either less than the new end we are inserting, or the same (no update to avoid copying from erased node)
        if((prevKeyEnd->first >= keyEnd))
            //(!(prevKeyEnd->first < keyEnd)) //&& !(keyEnd < prevKeyEnd->first))
            iterEnd = prevKeyEnd;
        else
            iterEnd = m_map.insert_or_assign(upperKeyEnd, keyEnd, prevKeyEnd->second);
    }
    else
    {
        iterEnd = upperKeyEnd;
    }
        
    if (lowerKeyBegin != m_map.begin())
    {
             auto prevIter = std::prev(lowerKeyBegin); //safe when end(), because we always have at least one value
            if (!(prevIter->second == val))
             {
                 iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
             }
             else iterBegin = prevIter;
    }
    else
         {
             iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
         }

         /*
         Erase all keys between the new begin and end (excluding) so that there is only one value after iterBegin
         This is fine when iterEnd is end()
         */
      {
             auto nextIterOfBegin = std::next(iterBegin);//somehow msvc doesn't support if-initialization
             if (nextIterOfBegin != m_map.end())
             {
                 //I would be very interested in a smarter way to get rid of this part without additional storage ...
                 m_map.erase(nextIterOfBegin, iterEnd);
             }
        }
    
   }
    
    
    
    void assign1( K const& keyBegin, K const& keyEnd, V const& val )
    {

            if (!(keyBegin < keyEnd)) return;

            std::pair<K,V> beginExtra;
            std::pair<K,V> endExtra;
       // std::pair<K,V>::pair t;
            bool beginHasExtra = false;
            bool endHasExtra = false;

            typename std::map<K,V>::const_iterator itBegin;
            itBegin = m_map.lower_bound(keyBegin);
        cout << "itBegin is at idx" << itBegin->first << endl;
            if ( itBegin!=m_map.end() && keyBegin < itBegin->first ) {
                if (itBegin != m_map.begin()) {
                    beginHasExtra = true;
                    --itBegin;
                    beginExtra = std::make_pair(itBegin->first, itBegin->second);
                }
                // openRange for erase is prevIterator
                // insert (prevIterator->first, prevIterator->second) as well!
            }

            typename std::map<K,V>::const_iterator itEnd;
            itEnd = m_map.lower_bound(keyEnd);
        cout << "itBegin is at idx" << itEnd->first << endl;
            if ( itEnd!=m_map.end() && keyEnd < itEnd->first ) {
                endHasExtra = true;
                typename std::map<K,V>::const_iterator extraIt = itEnd;
                --extraIt;
                endExtra = std::make_pair(keyEnd, extraIt->second);
                // closeRange for erase is this iterator
                // insert (keyEnd, prevIterator->second) as well!
            }

            // 4 canonical conflicts:
            //     beginExtra w/ mid
            //     before-mid w/ mid (beginHasExtra==false)
            //     mid w/ endExtra
            //     mid w/ after-mid (endHasExtra==false)

            bool insertMid = true;
            if (beginHasExtra) {
                if (beginExtra.second == val)
                    insertMid = false;
            } else {
                if (itBegin != m_map.begin()) {
                    typename std::map<K,V>::const_iterator beforeMid = itBegin;
                    --beforeMid;
                    if (beforeMid->second == val)
                        insertMid = false;
                }
            }


            if (endHasExtra) {
                if ( (insertMid && endExtra.second == val) || (!insertMid && endExtra.second == beginExtra.second) )
                    endHasExtra = false;
            } else {
                if ( (insertMid && itEnd!=m_map.end() && itEnd->second == val) || (!insertMid && itEnd!=m_map.end() && itEnd->second == beginExtra.second) )
                    itEnd = m_map.erase(itEnd);
            }

            itBegin = m_map.erase(itBegin, itEnd);
            if (beginHasExtra)
                itBegin = m_map.insert(itBegin, beginExtra);
            if (insertMid)
                itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));
            if (endHasExtra)
                    m_map.insert(itBegin, endExtra);

// INSERT YOUR SOLUTION HERE
        if(itEnd == m_map.end() && !endHasExtra) {
            auto defaultVal = m_map[std::numeric_limits<K>::lowest()];
            cout << "Default val is " << defaultVal << endl;
            m_map.insert(itEnd,std::make_pair(keyEnd,defaultVal));
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    interval_map<int, char> map('Z');
    map.assign(4, 6, 'B');
    map.assign(1,7,'A');
    map.assign(7, 9, 'C');
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

