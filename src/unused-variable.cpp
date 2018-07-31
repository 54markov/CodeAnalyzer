#include <iostream>

#include "unused-variable.h"


// TODO: description
UnusedVariable::UnusedVariable()
{
    ;
}

// TODO: description
UnusedVariable::~UnusedVariable()
{
    ;
}

// TODO: description
void UnusedVariable::process(const std::vector<std::string> &files)
{
    if (files.size() == 0)
        return; // nothing to do

    try
    {
        // TODO
    }
    catch(std::string error)
    {
        std::cerr << error << std::endl;
    }

    this->notify(Event::DataChange);
}

// TODO: description
std::map<std::string, FunctionInfo> UnusedVariable::get()
{
    return this->map_;
}
