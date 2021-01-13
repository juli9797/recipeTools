#pragma once
#include <map>
#include <string>
#include <vector>
#include "Serializer.hpp"

class SerializerJSON : public Serializer {
public:
    //string
    void serialize(std::string name, std::string value)
    {
        objects.push_back("\"" + name + "\": \"" + value + "\"");
    }
    //int
    void serialize(std::string name, int value)
    {
        objects.push_back("\"" + name + "\": \"" + std::to_string(value) + "\"");
    }
     //string vector
    void serialize(std::string name, std::vector<std::string> v)
    {
        std::string json;
        json += "\"" + name + "\":[";
        for (auto it = std::begin(v); it != std::end(v); it++) {
            json += "\"" + *it + "\"";
            if (std::next(it) != std::end(v)) {
                json += ",";
            }
        }
        json += "]";
        objects.push_back(json);
    }
    //int vector
    void serialize(std::string name, std::vector<int> v)
    {
        std::string json;
        json += "\"" + name + "\":[";
        for (auto it = std::begin(v); it != std::end(v); it++) {
            json += "\"" + std::to_string(*it) + "\"";
            if (std::next(it) != std::end(v)) {
                json += ",";
            }
        }
        json += "]";

        objects.push_back(json);
    }
    //map
    void serialize(std::string name, std::map<std::string, std::string> m)
    {
        std::string json;
        json += "\"" + name + "\":{";
        for (auto it = std::begin(m); it != std::end(m); it++) {
            json += "\"" + it->first + "\":\"" + it->second + "\"";
            if (std::next(it) != std::end(m)) {
                json += ",";
            }
        }
        json += "}";
        objects.push_back(json);
    }
    std::string generate()
    {
        std::string json="{";
        for (auto it = std::begin(objects); it != std::end(objects); it++) {
            json += *it;
            if (std::next(it) != std::end(objects)) {
                json += ",";
            }
        }
        json += "}";
        return json;
    }

};
