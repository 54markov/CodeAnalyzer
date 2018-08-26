#include <regex>
#include <fstream>
#include <iostream>

#include "unused-function.h"


// TODO: description
UnusedFunction::UnusedFunction()
{
    ;
}

// TODO: description
UnusedFunction::~UnusedFunction()
{
    ;
}

// TODO: description
void UnusedFunction::process(const std::vector<std::string> &files)
{
    if (files.size() == 0)
        return; // nothing to do

    try
    {
        for (auto file : files)
        {
            this->gatherDefs_(file.c_str());
        }

        for (auto file : files)
        {
            this->gatherCalls_(file.c_str());
        }
    }
    catch(std::string error)
    {
        std::cerr << error << std::endl;
    }

    this->notify(Event::DataChange);
}

// TODO: description
std::map<std::string, FunctionInfo> UnusedFunction::get()
{
    return this->map_;
}

// TODO: description
void UnusedFunction::gatherDefs_(const char *file)
{
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw std::string(std::string("Couldn't open ") +
                          std::string(file)             +
                          std::string(" for reading"));

    int line = 0;
    std::string str;

    while (std::getline(ifs, str))
    {
        line++;

        // Try to find function defenition
        std::smatch match;

        // Regular expression contains 4 groups and prefix and suffix
        if (std::regex_search(str, match, std::regex("([\\w:]+)( *)\\(([^)]*)\\)")))
        {
            if (match.size() != 4)
                throw std::string("Can't parse line: " + str);

            const std::string funName(match[1]);

            if (std::string(match.prefix()).find('=') != std::string::npos)
                return; // skip function call

            if (regex_match(std::string(match.prefix()), std::regex("(\\s+)")))
                return; // skip function call

            if (funName == "main")
                return; // skip main function

            this->map_.insert(
                std::make_pair(
                    funName, FunctionInfo(std::string(file), funName, line)));
        }
    }

    ifs.close();
}

// TODO: description
void UnusedFunction::gatherCalls_(const char *file)
{
    std::ifstream ifs(file);
    if (!ifs.is_open())
    {
        throw std::string(std::string("Couldn't open ") + std::string(file) + std::string(" for reading"));
    }

    std::string str;

    while (std::getline(ifs, str))
    {
        this->updateCall_(str);
    }

    ifs.close();
}

// TODO: description
void UnusedFunction::updateCall_(const std::string &str)
{
    for (auto iter = this->map_.begin(); iter != this->map_.end(); iter++)
    {
        auto pos = str.find(iter->first);
        if (pos != std::string::npos)
        {
            iter->second.update();

            // Try more for the rest of the line
            pos += iter->first.size();

            if (str.begin() + pos < str.end())
            {
                std::string offsetStr(str.begin() + pos, str.end());
                this->updateCall_(offsetStr);
            }
        }
    }
}
