#pragma once

#include "model.h"
#include "observer.h"


class View : public Observer
{
    public:
        View(Model* model);
        ~View();

        void update(const Event event);

    private:
        Model* model_;
};
