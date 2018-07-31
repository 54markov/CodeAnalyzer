#include <string>

#include "observer.h"


Observer::Observer()
{
    ;
}

Observer::~Observer()
{
    ;
}


Observable::Observable()
{
    ;
}

Observable::~Observable()
{
    ;
}

void Observable::add(Observer* observer)
{
	if (observer == nullptr)
		throw(std::string("Can't add observer"));

    this->observers_.push_back(observer);
}

void Observable::notify(const Event event)
{
    for (auto i : this->observers_)
    {
        i->update(event);
    }
}
