//
//  main.cpp
//  RegEx
//
//  Created by Mehtab Ali Syed (CS) on 20/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <regex>
#include <string>
#include <iterator>
using namespace std::string_literals;
// Text Parser

int main1 () {
std::string s ("this subject has a submarine as a subsequence");
std::smatch m;
std::regex e ("\\b(sub)([^ ]*)");

std::cout << "Target sequence: " << s << std::endl;
std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
std::cout << "The following matches and submatches were found:" << std::endl;

while (std::regex_search (s,m,e)) {
   for (auto x:m)
       std::cout << x << " ";
   std::cout << std::endl;
   s = m.suffix().str();
}

return 0;
}
std::string text (
R"(#remove # to uncomment the following lines
timeout = 120
    
server = 127.0.0.1
#retrycount=3)"s);
void find_matching_literals()
{
    
    
    std::regex rx (R"((\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*))");
    
     std::smatch match;
  
  // bool ret = std::regex_search(text,match,rx);
  
    if(std::regex_search(text, match, rx))
    {
        std::cout << match[1] << "=" << match[2] << std::endl;
    }
    
    
}

void find_all_literals()
{
     std::regex rx (R"((\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*))");
    auto end = std::sregex_iterator{};
    for(auto it=std::sregex_iterator(std::begin(text),std::end(text),rx);
        it!=end;++it)
    {
        std:: cout << " " << (*it)[1] << "=" << (*it)[2] << " " << std::endl;
    }
   
    
}

bool validate_licence(std::string_view str)
{
    std::regex rx(R"([a-zA-Z]{3}-[A-Z]{2} \d{3,4})");
    std::regex rx2 (R"([a-zA-Z]{3}-[A-Z]{2}\d{3,4})");
    return std::regex_match(str.data(), rx);
    
}

std::vector<std::string> extract_license_numbers(std::string & str)
{
    std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
    std::vector<std::string> ret;
    
    for(auto i=std::sregex_iterator(cbegin(str),cend(str),rx);
        i!=std::sregex_iterator();++i)
    {
         std::cout << "Matched string is " << i->str() <<std::endl;
        if((*i)[1].matched)
        {
           
            ret.push_back(i->str());
        }
    }
    
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "Finding matching Literals :" << std::endl;
    find_all_literals();
    main1();
    find_matching_literals();
    
    assert(validate_licence("ABC-DE 123"));
     assert(validate_licence("abc-DE 123"));
    std::vector<std::string> expected{"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
    std::string text("AAA-AA 123qwe-ty 1234  ABC-DE 123456..XYZ-WW 0001");
    assert(expected == extract_license_numbers(text));
    return 0;
}
