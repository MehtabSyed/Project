//
//  main.cpp
//  Pimpl
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include "control.hpp"
#include "Control_Copyable.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
#if 0 // with copy contructor 
    Control c;
    
    c.set_text("hello text");
    c.resize(5,6);
    c.hide();
    
    Control c2 =std::move(c);
    c2.show();
#endif
    Control_copyable c3;

    c3.set_text("Copyable ");
    
    Control_copyable c2 = c3;
    c2.show();
    
    return 0;
}
