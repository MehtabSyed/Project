//
//  control.cpp
//  Pimpl
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include "control.hpp"
#include <string>
#include <iostream>




class control_impl
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
Control::Control():
pimpl{new control_impl(),[](control_impl * pimpl){delete pimpl;}}
{
    
}
void Control::set_text(std::string_view text)
{
    pimpl->set_text(text);
}
void Control::resize(int const w, int const h)
    {
      pimpl->resize(w, h);
    }
    void Control::show()
    {
      pimpl->show();
    }
    void Control::hide()
    {
      pimpl->hide();
    }
