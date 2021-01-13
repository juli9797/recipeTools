#pragma once
#include <iostream>
#include <string>

class Debug {
public:
   enum DEBUGLEVEL {
        DEBUG,
        WARNING,
        INFO,
        ERROR
    }; 
   
   static void error(std::string msg)
    {
        if (debugLevel > ERROR) {
            return;
        }
        std::cout << "ERROR:\t" << msg << std::endl;
    }
    static void info(std::string msg)
    {
        if (debugLevel > INFO) {
            return;
        }
        std::cout << msg << std::endl;
    }
    static void warning(std::string msg)
    {
        if (debugLevel > WARNING) {
            return;
        }
        std::cout << "WARNING:\t" << msg << std::endl;
    }
    static void debug(std::string msg)
    {
        if (debugLevel > DEBUG) {
            return;
        }
        std::cout << "DEBUG:\t" << msg << std::endl;
    }
    static void setDebugLevel(DEBUGLEVEL d)
    {
        debugLevel = d;
    }
    

private:
    static DEBUGLEVEL debugLevel;
};

Debug::DEBUGLEVEL Debug::debugLevel = Debug::DEBUG;
