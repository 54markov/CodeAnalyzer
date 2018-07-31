#include <iostream>

#include "view.h"


View::View(Model* model) : model_(model)
{
    this->model_->Observable::add(this);
}

View::~View()
{
    ;
}

void View::update(const Event event)
{
    switch (event)
    {
        case Event::DataChange:
        {
            for (auto i: this->model_->get())
            {
                i.second.show();
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
