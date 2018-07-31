#include <regex>
#include <fstream>
#include <iostream>

#include "unused-function.h"


static const std::regex regFunDefenition("(\\S+|((class|struct)[ \t\n]+\\S+))([ \t\n]*)(\\S+)(\\s*)\\(.*\\)");
static const std::regex regFunName("([ \t\n]+)(\\S+)([ \t\n]*)\\(");


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
    {
        throw std::string(std::string("Couldn't open ") + std::string(file) + std::string(" for reading"));
    }

    int counter = 1;
    std::string line;

    while (std::getline(ifs, line))
    {
        // Try to find function 
        if (regex_match(line, regFunDefenition))
        {
            this->updateDef_(file, counter, line);
        }
        counter++;
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

    std::string line;

    while (std::getline(ifs, line))
    {
        this->updateCall_(line);
    }

    ifs.close();
}

// TODO: description
void UnusedFunction::updateDef_(const char *file, const int line, const std::string &str)
{
    std::smatch match;

    std::regex_search(str, match, regFunName);

    if (match.size()) // TODO
    {
        if (match[match.size() - 2] != std::string("main"))
        {
            std::string key = match[match.size() - 2];
            FunctionInfo value(std::string(file), key, line);
            this->map_.insert(std::make_pair(key, value));
        }
    }
}

// TODO: description
void UnusedFunction::updateCall_(const std::string &str)
{
    std::smatch match;

    std::regex_search(str, match, regFunName);
    
    if (match.size()) // TODO
    {
        auto iter = this->map_.find(match[match.size() - 2]);
        if (iter != this->map_.end())
        {
            iter->second.update();
        }
    }
}
