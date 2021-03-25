//
//  main.cpp
//  Time
//
//  Created by Mehtab Ali Syed (CS) on 08/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

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

using namespace std::chrono_literals;
using namespace std;
void Time()
{
    std::chrono:: hours half_day_in_h(12);
    
    std::chrono::minutes half_day_in_min(half_day_in_h);
    
    
    cout << half_day_in_h.count() << "h" << endl;
    
    cout << half_day_in_min.count() << "min" << endl;
    
    auto total_sec = 12345s;
    auto hours =
    std::chrono::duration_cast<chrono::hours>(total_sec);
    
    auto minutes =
    std::chrono::duration_cast<chrono::minutes>(total_sec %1h);
    auto second =
    std::chrono::duration_cast<chrono::seconds>(total_sec %1min);
    
    cout << hours.count() << ":" <<
            minutes.count() << ":" <<
    second.count()  << endl;
    
}


void DateBoost()
{
   using namespace boost::gregorian;

    string  filedate("2020-1-20");
    date d(from_simple_string(filedate));
    std::cout << to_simple_string(d); //Date(1,2,2010)
}

class Command
{
public:
    int             ExitStatus = 0;
    std::string     Command;
    std::string     StdIn;
    std::string     StdOut;
    std::string     StdErr;
void execute()
{
        const int READ_END = 0;
        const int WRITE_END = 1;

        int infd[2] = {0, 0};
        int outfd[2] = {0, 0};
        int errfd[2] = {0, 0};

        
     /*   auto cleanup = [&]() {
            ::close(infd[READ_END]);
            ::close(infd[WRITE_END]);

            ::close(outfd[READ_END]);
            ::close(outfd[WRITE_END]);

            ::close(errfd[READ_END]);
            ::close(errfd[WRITE_END]);
        };
      */
       BOOST_SCOPE_EXIT(&infd,&outfd,&errfd) {
               ::close(infd[READ_END]);
               ::close(infd[WRITE_END]);

               ::close(outfd[READ_END]);
               ::close(outfd[WRITE_END]);

               ::close(errfd[READ_END]);
               ::close(errfd[WRITE_END]);
       }BOOST_SCOPE_EXIT_END;
        auto rc = ::pipe(infd);
        if(rc < 0)
        {
            throw std::runtime_error(std::strerror(errno));
        }

        rc = ::pipe(outfd);
        if(rc < 0)
        {
            ::close(infd[READ_END]);
            ::close(infd[WRITE_END]);
            throw std::runtime_error(std::strerror(errno));
        }

        rc = ::pipe(errfd);
        if(rc < 0)
        {
            ::close(infd[READ_END]);
            ::close(infd[WRITE_END]);

            ::close(outfd[READ_END]);
            ::close(outfd[WRITE_END]);
            throw std::runtime_error(std::strerror(errno));
        }

        auto pid = fork();
        if(pid > 0) // PARENT
        {
            ::close(infd[READ_END]);    // Parent does not read from stdin
            ::close(outfd[WRITE_END]);  // Parent does not write to stdout
            ::close(errfd[WRITE_END]);  // Parent does not write to stderr

        //    if(::write(infd[WRITE_END], StdIn.data(), StdIn.size()) < 0)
            {
          //      throw std::runtime_error(std::strerror(errno));
            }
            ::close(infd[WRITE_END]); // Done writing
        }
        else if(pid == 0) // CHILD
        {
            ::dup2(infd[READ_END], STDIN_FILENO);
            ::dup2(outfd[WRITE_END], STDOUT_FILENO);
            ::dup2(errfd[WRITE_END], STDERR_FILENO);

            ::close(infd[WRITE_END]);   // Child does not write to stdin
            ::close(outfd[READ_END]);   // Child does not read from stdout
            ::close(errfd[READ_END]);   // Child does not read from stderr
 ::execl("/bin/sh", "sh", "-c", Command.c_str(), nullptr);
      //      ::execl("/usr/bin/sudo", "sudo", Command.c_str(), nullptr);
            ::exit(EXIT_SUCCESS);
        }

        // PARENT
        if(pid < 0)
        {
           // cleanup();
            throw std::runtime_error("Failed to fork");
        }

        int status = 0;
        ::waitpid(pid, &status, 0);

        std::array<char, 256> buffer;

        ssize_t bytes = 0;
        do
        {
            bytes = ::read(outfd[READ_END], buffer.data(), buffer.size());
            StdOut.append(buffer.data(), bytes);
        }
        while(bytes > 0);

        do
        {
            bytes = ::read(errfd[READ_END], buffer.data(), buffer.size());
            StdErr.append(buffer.data(), bytes);
        }
        while(bytes > 0);

        if(WIFEXITED(status))
        {
            ExitStatus = WEXITSTATUS(status);
        }

      
    }
};

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
    fs::st
    
}

    
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Command cmd;
    cmd.Command = "/Users/Mehtab_Syed/Documents/project/modernC++/ModernCppPractice/ModernCppPractice/Time/Time/Time/run.sh";
    cmd.execute();
     std::cout << cmd.StdOut;
       std::cerr << cmd.StdErr;
       std::cout << "Exit Status: " << cmd.ExitStatus << "\n";   // Time();
    DateBoost();
    return 0;
}
