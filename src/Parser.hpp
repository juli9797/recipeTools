#pragma once
#include "Debug.hpp"
#include "Recipe.hpp"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
class Parser {
public:
    Parser(std::string filename)
    {
        loadFile(filename);
    }
    Recipe parse()
    {
        //Regex title
        std::regex re_title("^\\s*#\\s.*");
        std::smatch res;
        std::string title;
        std::regex_search(markdown, res, re_title);
        if (!res.empty()) {
            title = *res.begin();
            title.erase(0, title.find_first_of("#") + 1);
            trim(title);
            Debug::debug("Found a title: " + title);
        } else {
            Debug::error("Did not find any title Aborting");
            return Recipe();
        }
        //Split into Sections
        std::istringstream iss(markdown);
        std::map<std::string, std::string> sections;
        auto it = sections.begin();
        for (std::string line; std::getline(iss, line);) {
            if (isHeadline(line)) {
                std::string headline = extractHeadline(line);
                trim(headline);
                it = sections.insert(std::pair(headline, "")).first;

            } else if (it != sections.end()) {
                (*it).second += "\n" + line;
            }
        }
        Recipe r;
        r.setName(title);
        for (std::pair section : sections) {

            Debug::debug(section.first);
            Debug::debug("\tParsing..");
            if (section.first == "Zutaten") {
                Debug::debug("\t\tentered Zutaten\n" + section.second);
                r.setIngredients(parseMap(section.second));
            }
            if (section.first == "Zubereitung") {
                Debug::debug("\t\tentered Zubereitung\n" + section.second);
                r.setInstructions(section.second);
            }
            if (section.first == "Tags") {
                Debug::debug("\t\tentered Tags\n" + section.second);
                r.setTags(parseVector(section.second));
            }
            if (section.first == "Information") {
                Debug::debug("\t\tentered Information\n" + section.second);
                r.setInformation(parseMap(section.second));
            }
        }
        return r;
    }

private:
    bool isHeadline(std::string s)
    {
        std::regex re("^\\s*##\\s.*");
        return std::regex_search(s, re);
    }
    std::string extractHeadline(std::string s)
    {
        s.erase(0, s.find_first_of("#") + 1);
        s.erase(0, s.find_first_of("#") + 1);
        trim(s);
        return s;
    }
    bool isBullet(std::string s)
    {
        std::regex re("^\\s*\\*\\s.*");
        return std::regex_search(s, re);
    }
    std::pair<std::string, std::string> extractBullet(std::string s)
    {
        std::pair<std::string, std::string> res;
        s.erase(0, s.find_first_of("*") + 1);
        int colon_pos = s.find_first_of(':');
        if (colon_pos != std::string::npos) {
            std::string key = s.substr(0, colon_pos);
            std::string val = s.substr(colon_pos+1, s.length() - colon_pos-1);
            trim(key);
            trim(val);
            res = std::pair<std::string, std::string>(key, val);
        } else {
            trim(s);
            res = std::pair<std::string, std::string>(s, "");
        }
        return res;
    }
    void trim(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    }
    void loadFile(std::string filename)
    {
        if (std::filesystem::exists(filename)) {
            Debug::debug("Loading file: " + filename);
        } else {
            Debug::error("File does not exist: " + filename);
            return;
        }
        std::ifstream t(filename);
        std::stringstream buffer;
        buffer << t.rdbuf();
        markdown = buffer.str();

        Debug::debug("---------------------------------------------------");
        Debug::debug(markdown);
        Debug::debug("---------------------------------------------------");
    }
    std::map<std::string, std::string> parseMap(std::string& s)
    {
        std::map<std::string, std::string> res;
        std::istringstream iss(s);
        for (std::string line; std::getline(iss, line);) {
            if (isBullet(line)) {
                std::pair<std::string, std::string> p = extractBullet(line);
                Debug::debug("-> " + p.first + "\t" + p.second);
                res.insert(p);
            }
        }
        return res;
    }
    std::vector<std::string> parseVector(std::string s)
    {
        std::vector<std::string> res;
        std::regex re("`.*?`");
        std::smatch m;
        while (std::regex_search(s, m, re)) {
            std::string match = m.begin()->str();
            s = m.suffix();
            Debug::debug("->" + match);
            res.push_back(match);
        }
        return res;
    }

    std::string markdown = "";
};
