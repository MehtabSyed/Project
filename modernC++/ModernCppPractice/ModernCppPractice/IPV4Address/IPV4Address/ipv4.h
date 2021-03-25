//
//  ipv4.h
//  IPV4Address
//
//  Created by Mehtab Ali Syed (CS) on 06/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#ifndef ipv4_h
#define ipv4_h


#include <stdio.h>
#include <string>
#include <iostream>
#include <array>
#include <sstream>

class ipv4
{
    std::array<unsigned char,4> data;
    
public:
    constexpr ipv4(): data{0}{}
    constexpr ipv4(unsigned char a ,unsigned char b ,unsigned char c,unsigned char d): data{a,b,c,d}{}
    constexpr ipv4(unsigned int t): data{ static_cast<unsigned char>((t >>24) & 0xFF),
                                         static_cast<unsigned char> ((t >> 16) & 0xFF),
                                        static_cast<unsigned char> ((t >> 8) & 0xFF),
                                        static_cast<unsigned char> (t & 0xFF )    } {};
    ipv4 & operator=(const ipv4& other) noexcept
    {
        data = other.data;
        return *this;
    }
    ipv4 (const ipv4 & t):data(t.data) {}
    
        
    std::string to_string() const
    {
        std::stringstream sstr;
        sstr << * this;
        
        return sstr.str();
        
    }
    
    constexpr unsigned long to_long() const noexcept
    {
        return (static_cast<unsigned long>(data[0])<< 24 |
                static_cast<unsigned long> (data[1]) << 16 |
                static_cast<unsigned long>(data[2]) << 8 |
                static_cast<unsigned long>(data[3]));
    }
    constexpr unsigned long to_ulong() const noexcept
       {
          return (static_cast<unsigned long>(data[0]) << 24) |
                 (static_cast<unsigned long>(data[1]) << 16) |
                 (static_cast<unsigned long>(data[2]) << 8) |
                  static_cast<unsigned long>(data[3]);
       }
   
    friend bool operator<(ipv4 const & x,ipv4 const & y) noexcept
    {
        return (x.to_ulong() < y.to_ulong());
        
    }
    friend bool operator==(ipv4 const & x,ipv4 const & y) noexcept
    {
        return (x.to_ulong() == y.to_ulong());
        
    }
    friend bool operator!=(ipv4 const & x,ipv4 const & y) noexcept
    {
        return !(x.to_ulong() == y.to_ulong());
        
    }
     ipv4& operator++()
    {
        *this = ipv4(1 + to_ulong());
        return *this;
        
    }
    ipv4& operator++(int)
    {
        ++*this;
        return *this;
    }
    
    

 //   Bancila, Marius. The Modern C++ Challenge: Become an expert programmer by solving real-world problems (pp. 32-33). //Packt Publishing. Kindle Edition.
    friend std::ostream & operator<<(std::ostream &os,const ipv4&a)
    {
        os << static_cast<int> (a.data[0]) << "." <<  static_cast<int> (a.data[1]) << "." <<  static_cast<int> (a.data[2]) << "." <<  static_cast<int> (a.data[3] );
        
        return os;
    }
    
    friend std::istream & operator>>(std::istream& is, ipv4 &ip)
    {
        char d1,d2,d3;
        int b1,b2,b3,b4;
        
        is >> b1 >> d1 >>b2 >> d2>> b3>> d3>> b4 ;
        
        if(d1 =='.' && d2 =='.' &&d3 =='.')
            ip = ipv4(b1,b2,b3,b4);
        else {
            is.setstate(std::ios_base::failbit);
           
        }
         return is;
    }
    
};

   
#endif /* ipv4_h */
