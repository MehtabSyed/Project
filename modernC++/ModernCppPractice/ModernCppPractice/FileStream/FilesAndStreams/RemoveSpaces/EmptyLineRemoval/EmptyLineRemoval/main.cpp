//
//  main.cpp
//  EmptyLineRemoval
//
//  Created by Mehtab Ali Syed (CS) on 28/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>
#include <cctype>
#include <algorithm>
namespace fs = boost::filesystem;

using namespace boost;


void fileSpaceRemoval(const fs::path& file_path )
{
    // open new file
    auto tempfile = fs::temp_directory_path() / "temp.dat";
    
   std::ofstream outfile(tempfile.native(), std::ios::trunc);
    
    if(!outfile.is_open())
        throw std::runtime_error("cannot open output file");
    
    
    // open existing file
    
    
    std::ifstream infile(file_path.native());
    if(!infile.is_open())
    {
        throw std::runtime_error("cannot open input file");
    }
    
    std::string line;
    while(getline(infile,line))
    {
        //read data from file
        if(line.empty())
            continue;
    
        if(std::all_of(begin(line), end(line),[](const auto  c){ return c== ' ';}))
            continue;
        outfile << line << std::endl;
         
    //check if no white spaces  , and
        //write to new file
    //dele org file
    // rename file to org file
    }
    infile.close();
    outfile.close();
    fs::remove(file_path.native());
    fs::rename(tempfile, file_path);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    auto srcpath = fs::path("/Users/Mehtab_Syed/Documents/project/modernC++/ModernCppPractice/ModernCppPractice/FileStream/FilesAndStreams/RemoveSpaces/EmptyLineRemoval/EmptyLineRemoval/sample.txt");
    fileSpaceRemoval(srcpath);
    
    
    return 0;
}
