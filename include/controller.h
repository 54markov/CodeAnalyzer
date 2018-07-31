#pragma once

#include "model.h"
#include "observer.h"


class Controller : public Observable
{
    public:
        Controller(Model* model);
        ~Controller();

        void run(const int argc, const char** argv);

    private:
        Model* model_;
};
