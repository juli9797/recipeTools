#pragma once
#include <map>
#include <string>
#include <vector>

class Serializer{
public:
    //string
    virtual void serialize(std::string name, std::string value){}
    //int
    virtual void serialize(std::string name, int value){}
     //string vector
    virtual void serialize(std::string name, std::vector<std::string> v){}
    //int vector
    virtual void serialize(std::string name, std::vector<int> v){}
    //map
    virtual void serialize(std::string name, std::map<std::string, std::string> m){}
    virtual std::string generate(){return "";}
    
   

protected:
    std::vector<std::string> objects;
};
