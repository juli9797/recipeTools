#pragma once
#include <map>
#include "SerializerJSON.hpp"
#include "SerializerMD.hpp"
#include "Serializer.hpp"
#include <string>
#include <vector>
class Recipe {
public:
    Recipe()
    {
    }

    std::string serialize(Serializer &se)
    {
        
        se.serialize("name", name);
        se.serialize("preptime", prepTime);
        se.serialize("tags", tags);
        se.serialize("ingredients", ingredients);
        se.serialize("cost", cost);
        se.serialize("instructions", instructions);
        std::string res = se.generate();
        return res;
    }

    void setName(std::string name)
    {
        this->name = name;
    }
    void addTag(std::string tag)
    {
        tags.push_back(tag);
    }
    void setTags(std::vector<std::string> tags)
    {
        this->tags = tags;
    }
    void setPrepTime(int hours, int minutes)
    {
        if (!(hours > 0 && minutes > 0 && minutes < 60)) {
            //malformed time
            return;
        }
        prepTime = hours * 60 + minutes;
    }
    void setPrepTime(int minutes)
    {
        prepTime = minutes;
    }
    void setCost(int cost)
    {
        if (!(cost >= 0 && cost <= 4)) {
            //malformed cost
            return;
        }
        this->cost = cost;
    }
    void setInstructions(std::string instructions)
    {
        this->instructions = instructions;
    }
    void setInformation(std::map<std::string, std::string> m)
    {
        auto it = m.find("Kosten");
        if (it != m.end()) {
            //element found;
            cost = std::stoi(it->second);
        };
        it = m.find("Zeit");
        if (it != m.end()) {
            //element found;
            //cost = std::stoi(it->second);
        };
    }

    void setIngredients(std::map<std::string, std::string> map)
    {
        ingredients = map;
    }

private:
    std::string name = "unnamed";
    // vector of Tags
    std::vector<std::string> tags;
    // 1: preperation time in minutes 2: cost metric [0;4]
    std::string instructions = "";
    std::map<std::string, std::string> ingredients;
    int prepTime = 0;
    int cost;
};
