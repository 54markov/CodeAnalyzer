#pragma once

#include "model.h"
#include "observer.h"


class Controller : public Observable
{
    public:
        Controller(Model* model);
        ~Controller();

        void run(std::vector<std::string>& v);

    private:
        Model* model_;
};
