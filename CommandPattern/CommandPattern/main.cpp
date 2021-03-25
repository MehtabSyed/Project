//
//  main.cpp
//  CommandPattern
//
//  Created by Mehtab Ali Syed (CS) on 26/12/20.
//  Copyright © 2020 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Command
{
public:
    virtual void Execute() = 0;
    
    virtual ~Command() = default;
};
using CommandPtr = std::shared_ptr<Command>;

class WaitCommand : public Command
{
 public:
    WaitCommand(int milliseconds):waittime(milliseconds){};
    
 virtual void Execute() override {
     
   std::chrono::milliseconds dur(waittime);
     std:: cout << "Sleeping for " << dur.count() << std::endl;
     std::this_thread::sleep_for(dur);

 }
private:
    unsigned long waittime{1000};
};

class HelloCommand : public Command
{
    
public:
    HelloCommand(std::string s):s(s)
    {
        
    };
    virtual void Execute() override
    {
        std::cout << "Command is " << s << std::endl;
    }
private:
    std::string s;
};

class Server
{
public:
    Server() =default;
    void acceptCommand(const CommandPtr& command) {
        command->Execute();
        
    }
    void Run()
    {
        std::unique_lock<std::mutex> lk(m);
        if(!start)
         cv.wait(lk);
        for(auto cmd:Commands)
        {
            cmd->Execute();
        }
        
    }
    
    void Start() {
        
        start =0;
        cv.notify_one();
    }
    
private:
    std::vector<CommandPtr> Commands;
    std::condition_variable cv;
    std::mutex m;
    std::atomic<int> start{1} ;
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std:: string s ="Hello command ";
    
    int val = 2 % 1;
    Server* theServer = new Server;
    
                               
    
   //CommandPtr h3 = std::make_shared<HelloCommand>(s);
    //HelloCommand h1("test");
    CommandPtr h2 = std::make_shared<HelloCommand>("test2");
   // h2->Execute();
    //h1.Execute();
    CommandPtr Wait = std::make_shared<WaitCommand>(40000);
    theServer->acceptCommand(Wait);
    theServer->acceptCommand(h2);
   std:: thread ServerExecute(&Server::Run,theServer);
    ServerExecute.join();
    std::cout << "Hello, World!\n";
    
    
   // HelloWorld->Execute();
    return 0;
}
