#include <vector>
#include <string>

#include "controller.h"


Controller::Controller(Model* model) : model_(model)
{
    ;
}

Controller::~Controller()
{
    ;
}

void Controller::run(std::vector<std::string>& v)
{
    this->model_->process(v);
}
