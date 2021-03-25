//
//  main.cpp
//  FilesAndStreams
//
//  Created by Mehtab Ali Syed (CS) on 24/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

template<typename T>
void write(const std::string &filename,std::vector<T>& vec)
{
    std::ofstream file(filename,std::ios::binary);
    
    if(file.is_open())
    {
        file.write(reinterpret_cast<char*>(vec.data()),vec.size());
         file.close();
    }
   
}
template<typename T>
std::vector<T> read(const std::string& filename)
{
    std::ifstream ifile(filename,std::ios::binary);
    std::vector<T> vec;
    if(ifile.is_open())
    {
        ifile.seekg(0,std::ios::end);
        auto length = ifile.tellg();
        ifile.seekg(0,std::ios::beg);
        vec.resize(length);
        
        ifile.read(reinterpret_cast<char*>(vec.data()),length);
     
        ifile.close();
    }
    return vec;
}
size_t read_data(char const * const filename,
                 std::function<char*(size_t const)> allocator)
{
  size_t readbytes = 0;
  std::ifstream ifile(filename, std::ios::ate | std::ios::binary);
  if(ifile.is_open())
  {
    auto length = static_cast<size_t>(ifile.tellg());
    ifile.seekg(0, std::ios_base::beg);
    auto buffer = allocator(length);
try {
      ifile.read(buffer, length);
      readbytes = static_cast<size_t>(ifile.gcount());
    }
    catch (std::ios_base::failure &)
    {
      // handle the error
    }
    ifile.close();
  }
  return readbytes;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::vector<unsigned char> vec = {1,2,3,4,5,6,7,8,9};
    std::string filename("sample.bin");
    write(filename, vec);
    std::vector<unsigned char> input;

    
    assert(read<unsigned char>(filename)==vec);
     if(read_data("sample.bin",
                          [&input](size_t const length) {
               input.resize(length);
               return reinterpret_cast<char*>(input.data());}) > 0)
               
     {
                 std::cout << (vec == input ? "equal": "not equal")
                           << std::endl;
               }
    
    return 0;
}
