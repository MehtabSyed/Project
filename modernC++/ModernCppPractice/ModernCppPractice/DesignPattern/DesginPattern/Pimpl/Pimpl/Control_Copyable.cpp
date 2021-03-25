//
//  Control_Copyable.cpp
//  Pimpl
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include "Control_Copyable.hpp"

class control_impl2
{
    std::string text;
    int width = 0;
    int height = 0;
    bool visible = true;
public:
    void draw()
    {
        std::cout << "Control \n"
                  << "Visible " << std::boolalpha << visible << std::noboolalpha << std::endl
                    << "Size " << width << "," << height << std::endl
        << " text " << text << std::endl;
        
        
    }
    void set_text(std::string_view t)
    {
        text = t.data();
        draw();
    }
     void resize(int const w, int const h)
             {
               width = w;
               height = h;
               draw();
    }
    void show() {
               visible = true;
    draw(); }
    void hide() {
        visible = false;
    
        draw();
        
    }
    
    
    
    
};

Control_copyable::Control_copyable():
pimpl(new control_impl2(),[](control_impl2* pimpl) {delete pimpl;}){}

Control_copyable::Control_copyable(Control_copyable && op) noexcept =default;
Control_copyable& Control_copyable::operator=(Control_copyable &&) noexcept =default;

Control_copyable::Control_copyable(const Control_copyable  &op)
:pimpl(new control_impl2(*op.pimpl),[](control_impl2 *impl){delete  impl;})
{}
Control_copyable& Control_copyable::operator=(const Control_copyable &op)
{
    if(this != &op)
    {
        pimpl = std::unique_ptr<control_impl2,void(*)(control_impl2*)>(
                new control_impl2(*op.pimpl),
                [](control_impl2 *pimpl){delete pimpl;});
        
    }
    return *this;
}

void Control_copyable::set_text(std::string_view text)
{
    pimpl->set_text(text);
}
void Control_copyable::resize(int const w, int const h)
    {
      pimpl->resize(w, h);
    }
    void Control_copyable::show()
    {
      pimpl->show();
    }
    void Control_copyable::hide()
    {
      pimpl->hide();
    }
