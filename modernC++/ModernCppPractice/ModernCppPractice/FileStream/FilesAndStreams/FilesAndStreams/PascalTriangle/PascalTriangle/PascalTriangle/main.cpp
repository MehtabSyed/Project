//
//  main.cpp
//  PascalTriangle
//
//  Created by Mehtab Ali Syed (CS) on 26/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//
//https://www.youtube.com/watch?v=6FLvhQjZqvM
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;



vector<vector<int>> Pascal(int num)
{
    vector<vector<int>> vvec(num);
    for(int i =0 ; i < num;++i)
    {
        vvec[i].resize(i+1);
        vvec[i][0]=vvec[i][i] =1;
        
        if(i!=0)
            cout << vvec[i][0] << " ";
        
        for(int j=1;j <i;++j)
        {
            vvec[i][j] = vvec[i-1][j-1] +vvec[i-1][j];
            cout << vvec[i][j] << " " ;
        }
        
        cout << vvec[i][i] << endl;
        
    }
    return vvec;
}

unsigned int number_of_digits(unsigned int const i)
{
    return i > 0 ? (int)log10(double(i)) : 1;
    
}

void print_pascal_triangle(int const n)
{
   for (int i = 0; i < n; i++)
   {
      auto x = 1;
      std::cout << std::string((n - i - 1)*(n / 2), ' ');
      for (int j = 0; j <= i; j++)
      {
         auto y = x;
         x = x * (i - j) / (j + 1);
         auto maxlen = number_of_digits(x) - 1;
         std::cout << y << std::string(n - 1 - maxlen - n%2, ' ');
      }
      std::cout << std::endl;
   }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    auto pascal = Pascal(5);
    int n = 0;
     std::cout << "Levels (up to 10): ";
   //  std::cin >> n;
     if (n > 10)
        std::cout << "Value too large" << std::endl;
     else
        print_pascal_triangle(n);
    std::cout << std::boolalpha << true << std::endl;    // true
              std::cout << false << std::endl;                     // false
              std::cout << std::noboolalpha << false << std::endl; // 0
    
    cout << std::right << setw(10) << "right" << endl;
    cout << setw(10) << "text" << endl;
    cout << left << setw(10) << "left" <<endl;
    
    std::cout << std::oct << 42 << std::endl; // 52
    std::cout << std::hex << 42 << std::endl; // 2a
    std::cout << std::dec << 42 << std::endl; // 42
    
    std::cout << std::right
               << std::setfill('*') << std::setw(28) <<
                std::fill('.') << "try " << std::endl;
    return 0;
}
