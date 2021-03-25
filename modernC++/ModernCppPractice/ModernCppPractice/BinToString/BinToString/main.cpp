//
//  main.cpp
//  BinToString
//
//  Created by Mehtab Ali Syed (CS) on 17/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <set>

using namespace std;
std::vector<long> StringToBin(std::string str)
{
   std:: vector<long> ret;
    for(int i=0;i<str.size();i+=2)
    {
        auto s= str.substr(i,2);
        
        ret.push_back(strtol(s.c_str(),NULL,16));
        
    }
    return ret;
}

template<typename Iter>
std::string BytesToHex(Iter begin,Iter end,bool const uppercase=false)
{
    std::ostringstream oss;
    if(uppercase)
        oss.setf(std::ios_base::uppercase);
    for(;begin!=end;++begin)
    {
        oss <<std::hex << std::setw(2) <<std::setfill('0') << static_cast<int>(*begin);
      
    }
      return oss.str();
    
}


template<typename C>
std::string BytesToHex(C & Cont, bool const uppercase =false)
{
   
    auto str =  BytesToHex(std::cbegin(Cont),std::cend(Cont),uppercase);
    std::cout << "String of binary number is : " << str << std::endl;
    
    return str;
}

std::string JoinString(std::vector<std::string> strings, std::string delimiter)
{
    std::ostringstream osstr;
    if(strings.size()==0)
    {
        return osstr.str();
    }
    
    std::string &prev = *strings.begin();
    osstr << prev;
    for(int i=1; i < strings.size();++i)
    {
        auto &curr = strings[i];
        
        osstr << delimiter << curr ;
        
        
        
    }
    std::cout << "Test string is " << osstr.str() << std::endl;
    return osstr.str();
    
}

template<typename Iter>
std::string join_strings(Iter begin,Iter end,char const * const expression)
{
    std::stringstream sstr;
    std::copy(begin,end-1,std::ostream_iterator<std::string>(sstr,expression));
    
    sstr << *(end-1);
    
    return sstr.str();
    
}
template<typename S>
vector<std::string> split_string(std::string_view str, S& delimiter)
{
    bool new_word = true;
    std ::stringstream word;
    std::vector<std::string> ret;
    for(auto elem:str)
    {
        auto itr = find(begin(delimiter),end(delimiter),elem);
       // auto itr = delimiter.find(elem);
        if(itr==delimiter.end())
        {
          word << elem;
            
        }else {
            new_word =false;
            cout << "Word is " << word.str() << endl;
            ret.push_back(word.str());
            word.str(""); //clear();
        }
        
    }
    std::cout << "Returning " << str << std::endl;
    return ret;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
   
    
    std::vector<std::string> vvec = {"Hello", "this" , "is" , "test"};
    std::string token("!,'");
    std::string_view str("Hello,this'is!test!");
    assert(vvec==split_string(str,token));
    assert("Hello this is test"==join_strings(vvec.begin(), vvec.end(), " "));
    assert("Hello this is test"==JoinString(vvec, " "));
    
    std::string str1("AB0A0D");
    auto ret = StringToBin(str1);
    std::vector<long> v ={0xAB,0xA,0XD};
    for(auto val :ret)
    {
        std::cout  << std::hex << val << " ";
    }
    
    assert(v==ret);
    std::cout << std::endl;
    
    std::vector<int> nums={0xAB, 0xA,0xD};
    assert(BytesToHex(nums,true)=="AB0A0D");
    
   // std::cout << "String of binary number is : " << BytesToHex(nums,true) << std::endl;
    unsigned char buff[4] = {0x11,0x22,0xAB,0x44};
    
    assert(BytesToHex(buff,true)=="1122AB44");
    return 0;
}
