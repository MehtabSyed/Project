//
//  main.cpp
//  FindFile
//
//  Created by Mehtab Ali Syed (CS) on 01/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::vector<fs::path> find_files(fs::path & path,std::function<bool(fs::path const &)> filter)
{
    std::vector<fs::path> result;
    if(fs::exists(path) && fs::is_directory(path))
    {
        for(auto const & entry :fs::directory_iterator(path))
        {
            auto filename = entry.path().filename();
            std::cout << "File name :" << filename << std::endl;
            if(fs::is_directory(entry))
            {
                continue;
            }
            if(fs::is_regular_file(entry) && filter(entry))
            {
                result.push_back(entry.path());
            }
        }
    }
    
    return result;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    fs::path path = "/Users/mehtab_syed/Documents/project/modernC++/The-Modern-Cpp-Challenge";
    
    auto ret = find_files(path, [](fs::path const & p){
        return (p.extension() == ".txt");
            
    });
    std::cout << "Matching file name :";
    for(auto f: ret)
    {
        std::cout << f << " " << std::endl;
    }
    return 0;
}
