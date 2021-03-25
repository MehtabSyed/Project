//
//  IpAddres.hpp
//  IPV4Address
//
//  Created by Mehtab Ali Syed (CS) on 06/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#ifndef IpAddres_hpp
#define IpAddres_hpp

#include <stdio.h>
#include <string>
#include <iostream>
// 9.9.9.9
//192.168.1.1


class IpAddress
{
    bool ValidateIPAddress() {
        std::string ip(ipaddr) ;
        ip+=".";
        auto start = 0 ;//ipaddr.begin();
        for(int i =0 ;i < 3;++i)
        {
            auto pos = ip.find(".",start);
            if(pos == std::string::npos)
                return false;
            
            int diff = pos -start;
            if(!(diff >0))
            {
                return false;
            }
            auto s = ipaddr.substr(start,diff);
            int num =stoi(s);
            if(num <= 0 || num > 255)
            {
                return false;
            }
            start = ++pos;
            
        }
        return true;
    };
    std::string ipaddr;
public:
    
    std::string getIpAdress() {
        bool isValid=false;
        do {
        std::cout << "Please enter the IP addr x.x.x.x format :" ;
        
        std::cin >> ipaddr;
        isValid = ValidateIPAddress();
        
            if(!isValid)
                std::cout << "Invalid ip format " << std::endl;
            
        }while(!isValid);
        return ipaddr;
    };
    void DisplayAddress()
    {
        std::cout << ipaddr << std::endl;
    };
    
    
    
    
};

#endif /* IpAddres_hpp */
