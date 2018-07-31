#include <iostream>

#include "function-info.h"


FunctionInfo::FunctionInfo(const std::string file,
                           const std::string name,
                           const int line) : file_(file), name_(name), line_(line), counter_(-1)
{
    ;
}

FunctionInfo::~FunctionInfo()
{
    ;
}

void FunctionInfo::update()
{
    this->counter_ += 1;
}

void FunctionInfo::show()
{
    std::cout << this->file_ << ", line " << this->line_ << " : "
              << this->name_ << ", calls " << this->counter_ << std::endl;
}

std::string FunctionInfo::getFile()
{
    return this->file_;
}

std::string FunctionInfo::getName()
{
    return this->name_;
}

int FunctionInfo::getLine()
{
    return this->line_;
}

int FunctionInfo::getCounter()
{
    return this->counter_;
}
