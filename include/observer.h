#pragma once

#include <vector>

#include "event.h"


class Observer
{
    public:
        Observer();
        virtual ~Observer();

        virtual void update(const Event event) = 0;
};
 
class Observable
{
    public:
        Observable();
        ~Observable();

        void add(Observer* observer);
        void notify(const Event event);

    private:
        std::vector<Observer*> observers_;
};
