#include <optional>
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#include "view.h"
#include "model.h"
#include "controller.h"
#include "unused-function.h"
#include "unused-variable.h"


const std::string selfDir(".");
const std::string backDir("..");


static void usage()
{
    std::cerr << "usage: static-analyzer -f path/source.c -uF" << std::endl
              << " -f  : single source file" << std::endl
              << " -d  : directory including all files (.c, .cpp, .cxx)" << std::endl
              << " -uF : unused function mode" << std::endl
              << " -uV : unused variable mode" << std::endl;
}

static void iterateDir(const char *directory, std::vector<std::string>& v)
{
    DIR* dir = NULL;
    struct dirent* entry = NULL;

    if (!(dir = opendir(directory)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            auto newDir = std::string(entry->d_name);
            if (newDir == selfDir || newDir == backDir)
                continue;

            char newPath[4096] = { 0 };
            snprintf(newPath, sizeof(newPath), "%s/%s", directory, entry->d_name);

            iterateDir(newPath, v);
        }
        else
        {
            auto newFile = std::string(entry->d_name);
            if ((newFile.find(".c")   != std::string::npos) ||
                (newFile.find(".cxx") != std::string::npos) ||
                (newFile.find(".cpp") != std::string::npos))
            {
                std::string source(directory);
                source += std::string("/") + newFile;
                v.push_back(source);
            }
        }
    }
    closedir(dir);
}

static std::optional<std::pair<int, std::vector<std::string>>>
getCmdOption(const int argc, const char** argv)
{
    std::vector<std::string> v;

    int ufFlag = -1;
    int sfFlag = -1;

    for (auto i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]).find("-f") != std::string::npos)
        {
            // Single source file
            sfFlag = 1;
        }
        else if (std::string(argv[i]).find("-d") != std::string::npos)
        {
            // Directory including all source files
            sfFlag = 0;
        }
        else if (std::string(argv[i]).find("-uF") != std::string::npos)
        {
            // Unused function mode
            ufFlag = 1;
        }
        else if (std::string(argv[i]).find("-uV") != std::string::npos)
        {
            // Unused variable mode
            ufFlag = 0;
        }
        else
        {
            if (sfFlag)
            {
                v.push_back(std::string(argv[i]));
            }
            else
            {
                iterateDir(argv[i], v);
            }
        }
    }

    if ((sfFlag == -1) && (ufFlag == -1))
        return std::nullopt;

    return std::make_pair(ufFlag, v);
}

int main(int argc, char const** argv)
{
    auto cmdOption = getCmdOption(argc, argv);
    if (!cmdOption)
    {
        usage();
        return -1;
    }

    auto isUnusedFun = std::get<0>(*cmdOption);
    auto sources     = std::get<1>(*cmdOption);

    Model* model = nullptr;

    if (isUnusedFun)
    {
        model = new UnusedFunction();
    }
    else
    {
        model = new UnusedVariable();
    }

    Controller* controller = new Controller(model);
    View*       view       = new View(model);

    controller->run(sources);

    delete model;
    delete controller;
    delete view;

    return 0;
}
