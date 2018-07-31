#include <iostream>

#include "view.h"
#include "model.h"
#include "controller.h"
#include "unused-function.h"
#include "unused-variable.h"


void usage(char const *app)
{
    std::cerr << "usage: " << app << std::endl; // TODO
}

int main(int argc, char const** argv)
{
    Model*      model      = nullptr;
    Controller* controller = nullptr;
    View*       view       = nullptr;

    // TODO: argument parsing
    if (1)
    {
        model = new UnusedFunction();
    }
    else
    {
        model = new UnusedVariable();
    }

    controller = new Controller(model);
    view       = new View(model);

    // TODO: argument convering
    controller->run(argc, argv);

    delete model;
    delete controller;
    delete view;

    return 0;
}
