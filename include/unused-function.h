#pragma once

#include "model.h"
#include "function-info.h"


class UnusedFunction : public Model
{
    public:
        UnusedFunction();
        ~UnusedFunction();

        void process(const std::vector<std::string> &files);
        std::map<std::string, FunctionInfo> get();

    private:
        void gatherDefs_(const char *file);
        void gatherCalls_(const char *file);
        void updateDef_(const char *file, const int line, const std::string &str);
        void updateCall_(const std::string &str);
};
