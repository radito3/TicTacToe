#ifndef TICTACTOE_INVALIDPATH_H
#define TICTACTOE_INVALIDPATH_H

#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>

using namespace std::chrono_literals;

class Timeout {

public:
    
    void time_out(std::chrono::milliseconds timeout)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::this_thread::sleep_for(timeout);
    }
            
 
   
    
};

#endif