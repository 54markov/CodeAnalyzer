#pragma once

#include "model.h"
#include "function-info.h"


class UnusedVariable : public Model
{
    public:
        UnusedVariable();
        ~UnusedVariable();

        void process(const std::vector<std::string> &files);
        std::map<std::string, FunctionInfo> get();
};
