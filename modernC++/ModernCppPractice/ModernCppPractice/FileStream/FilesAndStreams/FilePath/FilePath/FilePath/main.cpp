//
//  main.cpp
//  FilePath
//
//  Created by Mehtab Ali Syed (CS) on 27/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

using namespace boost;
using namespace std;
//#include <experimental/filesystem>
 //namespace fs = std::experimental::filesystem;

void path()
{
   auto cpppath = fs::path("/Users/mehtab_syed/Documents/project/modernC++/The-Modern-Cpp-Challenge/README.md");
    
    
   std::cout << " root = " << cpppath.root_name() << std::endl
     << "root dir: " << cpppath.root_directory() << std::endl
    << "root path " << cpppath.root_path()  << std::endl
    << "rel path"  <<cpppath.relative_path() << std::endl
    << "parent path " <<cpppath.parent_path() << std::endl
    << "filename" << cpppath.filename() << std::endl
    << "stem" << cpppath.stem() << std::endl
    << "Extension " << cpppath.extension() << std::endl;
    
    auto path2 = fs::path("project/modernC++/The-Modern-Cpp-Challenge");
    std::cout << "absulute" << path2.is_absolute() << std::endl;
    std::cout << "absolute" << cpppath.is_absolute() << std::endl;
    cpppath.replace_extension(".log");
    
    std::cout << "rel path"  << cpppath.relative_path() << std::endl;
   // cpppath.remove_filename();
    for(auto & p : cpppath)
    {
        std::cout  << p << std::endl;
    }
    
    auto samplePath = fs::path("/Users/mehtab_syed/Documents/project/modernC++/The-Modern-Cpp-Challenge/");
    cout << "Current path" << fs::current_path() << endl;
    auto newpath = fs::current_path() / "Temp";
    cout << "Current path" << newpath << endl;
    //auto err = std::error_code();
    system::error_code err;
   /// fs::copy_file(samplePath/, <#const path &to#>, <#system::error_code &ec#>)
    auto success = fs::copy_file(samplePath/ "sample.txt", samplePath /"sample.cpy", err);
    if(!success)
        cout << err.message()  << endl;
    fs::rename(samplePath / "sample.cpy",samplePath / "tmp" / "sample.log",err);
    cout << err.message() << endl;
    success = fs::remove(samplePath /"tmp" / "sample.log",err);
    if(!success)
        cout << err.message() << endl;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    path();
    
    return 0;
}
