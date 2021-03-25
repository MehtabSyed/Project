//
//  main.cpp
//  SplitString
//
//  Created by Mehtab Ali Syed (CS) on 19/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>

template<class Elem>
using tstring = std::basic_string<Elem,std::char_traits<Elem>,std::allocator<Elem>>;

template<class Elem>
using tstringstream= std::basic_stringstream<Elem,std::char_traits<Elem>,std::allocator<Elem>>;

template<typename Elem>
inline std::vector<tstring<Elem>> split_string(tstring<Elem> text,Elem const  delimiter)
{
    auto str = tstringstream<Elem>{text};
    auto tokens = std::vector<tstring<Elem>>{};
    auto token = tstring<Elem>{};
    while(std::getline(str,token,delimiter))
    {
        if(!token.empty())
            tokens.push_back(token);
    }
    
    return tokens;
}

template<typename Elem>
inline std::vector<tstring<Elem>> split_string(tstring<Elem> text,tstring<Elem> const &delimiters)
{
    auto tokens = std::vector<tstring<Elem>>{};
    size_t pos ,prev_pos=0;
    while((pos=text.find_first_of(delimiters,prev_pos))!= std::string::npos)
    {
        if(pos > prev_pos) {
            auto token = text.substr(prev_pos,pos-prev_pos);
            tokens.push_back(token);
        }
        prev_pos = pos +1;
        
    }
    
    if(prev_pos< text.length())
        tokens.push_back(text.substr(prev_pos,std::string::npos));
    
    return tokens;
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std::string_literals;

    std::cout << "Hello, World!\n";
    
    std::vector<std::string> expected{"this", "is", "a", "sample"};
    
     assert(expected == split_string("this is a sample"s,' '));
    
    assert(expected== split_string("this,is a.sample!!"s,",.! "s));
    return 0;
}
