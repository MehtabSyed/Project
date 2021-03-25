//
//  control.hpp
//  Pimpl
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#ifndef control_hpp
#define control_hpp
#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
class control_impl;

class Control
{
    std::unique_ptr<control_impl,void(*)(control_impl*)> pimpl;
public:
    Control();
    void set_text(std::string_view text);
          void resize(int const w, int const h);
          void show();
          void hide();
    
};



#endif /* control_hpp */
