//
//  Control_Copyable.hpp
//  Pimpl
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#ifndef Control_Copyable_hpp
#define Control_Copyable_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
class control_impl2;

class Control_copyable
{
    std::unique_ptr<control_impl2,void(*)(control_impl2*)> pimpl;
public:
    Control_copyable();
    
    Control_copyable(Control_copyable && op) noexcept;
    Control_copyable & operator=(Control_copyable && op) noexcept;
    
    Control_copyable(const Control_copyable&); //copy constructor
    Control_copyable & operator=(const Control_copyable& op);
    
    void set_text(std::string_view text);
             void resize(int const w, int const h);
             void show();
             void hide();
    
};
#endif /* Control_Copyable_hpp */
