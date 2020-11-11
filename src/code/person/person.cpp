#include "person.hpp"

Person::Person(double vaccinated_chance, double mortality)
{
    _type = HEALTHY;

    if(gut::math::rand_probability(vaccinated_chance))
		_type = VACCINATED;

	_resistant = gut::math::rand_probability(1 - mortality);
	_firstDaySick = false;
	_daysSick = 0;
}

Person::Person()
{
    _type = NONE;
	_resistant = false;
	_firstDaySick = false;
	_daysSick = 0;
}

Person::~Person() {}
