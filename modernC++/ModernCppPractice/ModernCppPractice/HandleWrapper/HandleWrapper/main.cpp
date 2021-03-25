//
//  main.cpp
//  HandleWrapper
//
//  Created by Mehtab Ali Syed (CS) on 14/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <filesystem>
#include <vector>

class HandleSaver
{
private:
    FILE *fp;
public:
    HandleSaver(const std::string& fileName,const std::string &  mode)
    {
        fp = fopen(fileName.c_str(),mode.c_str());
        if(fp==NULL)
        {
            
            
            throw "file not found";
        }
    }
    FILE* operator()()
    {
        return fp;
    }
    FILE* get()
    {
        return fp;
    }
    
    
    ~HandleSaver()
    {
        fclose(fp);
    }
    

};

using HandlePtr = std::shared_ptr<HandleSaver> ;

template<typename Traits>
class unique_handle
{
    using pointer = typename Traits::pointer;
    pointer m_value;
public:
    unique_handle(unique_handle const &) = delete;
    unique_handle& operator=(unique_handle const&) = delete;
    explicit unique_handle(pointer value = Traits::invalid())
    {
        m_value = value;
    }
    // Move handler
    unique_handle(unique_handle && other) noexcept : m_value(other.release()) {}
    unique_handle& operator=(unique_handle && other){
        if(this !=&other)
        {
            reset(other.relase());
            
        }
        return this;
    }
    ~unique_handle() noexcept
    {
        Traits::close(m_value);
    }
    explicit operator bool() noexcept
    {
        return m_value!= Traits::invalid();
    }
    pointer get() const noexcept {return m_value;}
    
    pointer release() noexcept
    {
        auto value = m_value;
        m_value = Traits::invalid();
        return value;
    }
    
    bool reset(pointer value=Traits::invalid()) noexcept
    {
        if(m_value != value)
        {
            Traits::close(m_value);
            m_value =value;
        }
        return static_cast<bool>(*this);
    }
    
    void swap(unique_handle & other) noexcept
    {
        std::swap(m_value,other.m_value);
    }
    
};
   
template<typename Traits>
    bool operator==(unique_handle<Traits> const &left,unique_handle<Traits> const & right) noexcept
    {
        return (left.get()==right.get());
    }
    

template<typename Traits>
        bool operator!=(unique_handle<Traits> const &left,unique_handle<Traits> const & right) noexcept
        {
            return (left.get()!=right.get());
        }
    
struct null_handle_traits
    {
        using pointer =FILE*;
        static pointer invalid() noexcept{
            return nullptr;
        }
        
        static void close(pointer value) noexcept
        {
            fclose(value);
        }
        
    };
    struct invalid_handle_traits
    {
        using pointer = FILE*;
        
        static pointer invalid() noexcept
        {
            return nullptr;
        }
        
        static void close(pointer value) noexcept
               {
                   fclose(value);
               }
        
    };
    using null_handle = unique_handle<null_handle_traits>;
    using invalid_handle = unique_handle<invalid_handle_traits>;
    void function_that_throws()
    {
        throw std::runtime_error("an error has occurred");
    }

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "Currenst working dir" << argv[0] << std::endl;
    
    std::string filename("/Users/Mehtab_Syed/Documents/project/modernC++/ModernCppPractice/ModernCppPractice/HandleWrapper/HandleWrapper/test.dat");
    {
        HandlePtr fp = std::make_shared<HandleSaver>(filename,"r+");//    HandlePtr fp =
        std::vector<char> buff(512);
        fgets(&buff[0],sizeof(buff),fp->get());
        puts(&buff[0]);
    }
    bool conditon1 =false;
    bool condition2 = true;
    
    invalid_handle handle{fopen(filename.c_str(),"r+")};
        
    if(!handle)
        return -1;
    if(conditon1)
        return -2;
    std::vector<char> buff(512);
     invalid_handle h2(std::move(handle));
    fgets(buff.data(),sizeof(buff), h2.get());
    
    puts(buff.data());
    if(condition2)
    {
        return -2;
    }
   
    
    function_that_throws();
    
    return 0;
}
