//
//  main.cpp
//  IPV4Address
//
//  Created by Mehtab Ali Syed (CS) on 06/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include "IpAddres.hpp"
#include "ipv4.h"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
#if 0
    IpAddress addr;
    addr.getIpAdress();
    addr.DisplayAddress();
#endif
    
    ipv4 ipaddr1(192,168,1,250);
    
      ipv4 ipaddr2(192,168,2,10);
    
    cout << "Printing IP address in the range " << ipaddr1 << " to " << ipaddr2 << endl;
    for(auto ip = ipaddr1; ip < ipaddr2;++ip)
    {
        cout << ip << " " << endl;
    }
     cout <<  "Entered ip is "<< ipaddr2 << endl;
    ++ipaddr2;
    cout <<  " ip after increment "<< ipaddr2 << endl;
    
    return 0;
    ipv4 ipaddr;
    cout << "IP is " << ipaddr << endl;
    cout << "Enter IP addr : ";
    
    
    cin >> ipaddr;
    cout << "Entered ip is "<< ipaddr << " Ulong eq is " << ipaddr.to_ulong() << endl << ipaddr.to_long() << endl;
    return 0;
}
