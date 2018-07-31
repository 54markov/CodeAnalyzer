#pragma once

#include <string>


class FunctionInfo
{
    public:
        FunctionInfo(const std::string file, const std::string name, const int line);
        ~FunctionInfo();

        void update();

        void show();

        std::string getFile();
        std::string getName();
        int getLine();
        int getCounter();

    private:
        const std::string file_;
        const std::string name_;
        const int         line_;
        int               counter_;
};
