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

void Controller::run(const int argc, const char **argv)
{
	std::vector<std::string> v;        // TODO
	v.push_back(std::string(argv[1])); // TODO

    this->model_->process(v);
}
