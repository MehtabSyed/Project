//
//  main.cpp
//  DesginPattern
//
//  Created by Mehtab Ali Syed (CS) on 06/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <functional>
#include <map>
#include <memory>

class Image {
public:
    virtual void print() =0;
};
class Bitmap :public Image {
public:
    void print() override
    {
        std::cout << "Bitmap image ";
    }
};
class Png : public Image{
public:
    void print() override
    {
        std::cout << "Png image ";
    }
};
class Jpeg : public Image{
public:
    void print() override
    {
        std::cout << "Jpeg image ";
    }
};

class IImageFactory {
    virtual std::shared_ptr<Image> CreateImage(std::string type) = 0;
};
std::map<std::string,
       std::function<std::shared_ptr<Image>()>> mapping
       {
            
           { "bmp" ,[](){return std::make_shared<Bitmap>();}},
           { "png" ,[]() {return std::make_shared<Png>();}},
           { "jped",[]() {return std::make_shared<Jpeg>();} }
           
       };
class ImageFactory :public IImageFactory
{
public:
   // std::map<std::string,
   // std::function<std::shared_ptr<Image()>>> mapping;
   virtual std::shared_ptr<Image> CreateImage(std::string type)
    {
       
        //auto Image3 = std:: make_shared<Bitmap>();
        
        auto it = mapping.find(type);
        if(it != mapping.end())
            return it->second();
        return nullptr;
        
    }
    
};

class IImageFactoryType
{
public:
    virtual std::shared_ptr<Image> Create(std::type_info const & type)=0;
    
};
class ImageFactoryType :public IImageFactoryType
{
public:
  virtual std::shared_ptr<Image> Create(std::type_info const & type ) override
    {
      
        auto it = mapping.find(&type);
        if(it != mapping.end())
        {
            return it->second();
        }
            
        return nullptr;
 
    }
private:
    std::map<std::type_info const * ,
    std::function<std::shared_ptr<Image>()>> mapping{
        {&typeid(Bitmap),[]() {return std::make_shared<Bitmap>();}},
        {&typeid(Png),[]() {return std::make_shared<Png>();}},
        {&typeid(Jpeg),[]() {return std::make_shared<Jpeg>();}}
        
        
    };
};
 


int main(int argc, const char * argv[]) {
    // insert code here...
    
    auto factory = ImageFactory{};
    auto image = (factory.CreateImage("png"));
    image->print();
    
    auto factory2 = ImageFactoryType{};
    auto jpedImage = factory2.Create(typeid(Jpeg));
    jpedImage->print();
    std::cout << "Hello, World!\n";
    return 0;
}
