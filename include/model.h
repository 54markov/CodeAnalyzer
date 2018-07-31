#pragma once

#include <map>
#include <vector>
#include <string>

#include "observer.h"
#include "function-info.h"


class Model : public Observable
{
    public:
        Model();
        virtual ~Model();

        virtual void process(const std::vector<std::string> &files) = 0;
        virtual std::map<std::string, FunctionInfo> get() = 0;

    protected:
        std::map<std::string, FunctionInfo> map_;
};
