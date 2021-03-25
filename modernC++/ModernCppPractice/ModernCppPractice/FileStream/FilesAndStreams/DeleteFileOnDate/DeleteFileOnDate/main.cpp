//
//  main.cpp
//  DeleteFileOnDate
//
//  Created by Mehtab Ali Syed (CS) on 07/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>
#include <chrono>

namespace fs = boost::filesystem;
using namespace std;
void find_file(fs::path & dirpath,std::function<void(const fs::path &path)> filter)
{
    if(fs::exists(dirpath) && fs::is_directory(dirpath))
    {
        for(auto const & entry : fs::directory_iterator(dirpath))
        {
            if(fs::is_directory(entry))
                continue;
            
            if(fs::is_regular_file(entry))
                filter(entry);
            
        }
    }
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace boost::gregorian;
    std::cout << "Hello, World!\n";
    fs::path path("/Users/mehtab_syed/Documents/project/modernC++/The-Modern-Cpp-Challenge");
    string sdate("2020-Mar-06");
    date d(from_simple_string(sdate));
    //time_t t;
    
    find_file(path,[&](fs::path const& p ){
        auto filetime = fs::last_write_time(p);
        date filedate = boost::posix_time::from_time_t(filetime).date();
        if( filedate > d)
        {
            cout << "File name is " << p << endl;
        }
        //fs::remove(p);
        
    }
              );
    
    return 0;
}
