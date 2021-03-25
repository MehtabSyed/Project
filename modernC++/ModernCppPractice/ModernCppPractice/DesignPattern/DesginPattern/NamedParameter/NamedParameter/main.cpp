//
//  main.cpp
//  NamedParameter
//
//  Created by Mehtab Ali Syed (CS) on 15/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
class Control;
class ControlProperties
{
    int id_;
    std::string text_;
    int width_;
    int height_;
    bool visible_;
    
    friend class Control;
public:
    ControlProperties(int const id):id_(id){}
    ControlProperties & text(std::string_view t)
    {
        text_ = t.data();
        return *this;
    }
    ControlProperties& width(int const w)
                { width_ = w; return *this; }
    ControlProperties& height(int const h)
                { height_ = h; return *this; }
    ControlProperties& visible(bool const v)
                { visible_ = v; return *this; }
    
};
class Control
{
    int id_;
            std::string text_;
            int width_;
            int height_;
            bool visible_;
public:
    Control(
            int const id,
                       std::string_view text = "",
                       int const width = 0,
                       int const height = 0,
                       bool const visible = false):
                       id_(id), text_(text),
                       width_(width), height_(height),
                       visible_(visible)
            {}
    Control(ControlProperties &cp):
        id_(cp.id_),
      text_(cp.text_),
                 width_(cp.width_),
                 height_(cp.height_),
                 visible_(cp.visible_)
    {}

};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Control c(1044,"sample",100,20,true);
    Control c2(ControlProperties(1044)
               .visible(true)
               .text("sample2"));
    
    return 0;
}
