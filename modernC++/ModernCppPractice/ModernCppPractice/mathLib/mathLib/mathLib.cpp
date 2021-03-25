//
//  mathLib.cpp
//  mathLib
//
//  Created by Mehtab Ali Syed (CS) on 02/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include "mathLib.hpp"
#include "mathLibPriv.hpp"

void mathLib::HelloWorld(const char * s)
{
    mathLibPriv *theObj = new mathLibPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void mathLibPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

