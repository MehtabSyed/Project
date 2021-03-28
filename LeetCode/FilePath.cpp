
#include <iostream>
#include <chrono>
#include <string>
#include <unistd.h>
//#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/date_time.hpp>
#include <boost/scope_exit.hpp>
#include <boost/filesystem.hpp>
//#include <filesystem>
namespace fs = boost::filesystem;

auto print_perm = [](fs::perms p)
  {
    std::cout
      << ((p & fs::perms::owner_read) != fs::perms::none ?
         "r" : "-")
      << ((p & fs::perms::owner_write) != fs::perms::none ?
         "w" : "-")
      << ((p & fs::perms::owner_exec) != fs::perms::none ?
         "x" : "-")
      << ((p & fs::perms::group_read) != fs::perms::none ?
         "r" : "-")
      << ((p & fs::perms::group_write) != fs::perms::none ?
         "w" : "-")
      << ((p & fs::perms::group_exec) != fs::perms::none ?
         "x" : "-")
      << ((p & fs::perms::others_read) != fs::perms::none ?
         "r" : "-")
      << ((p & fs::perms::others_write) != fs::perms::none ?
         "w" : "-")
      << ((p & fs::perms::others_exec) != fs::perms::none ?
         "x" : "-")
      << std::endl;
};


bool CheckFileAttributes(wstring & filePath)
{
    auto shellpath = fs::path(filePath);
    auto exists = fs::exists(shellpath);
    error_code err;
   // error_code()
    
    cout << "file Exists ::" << boolalpha << exists << endl;
    auto status = fs::status(shellpath);
    std::cout << "permission";
    print_perm(status.permissions());
    
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    wstring path("/Users/Mehtab_Syed/Documents/project/modernC++/ModernCppPractice/ModernCppPractice/Time/Time/Time/run.sh");
    CheckFileAttributes(path);
return 0;
}