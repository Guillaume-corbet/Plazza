/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "../include/Cook.hpp"

Cook::Cook(Pizza *pizza, std::map<std::string, int> *ingredients):_pizza(pizza), _ingredient(ingredients), _fcnt(new CEncapsulate())
{
}

Cook::~Cook()
{
    if (this->_pizza != NULL)
        this->_pizza->~Pizza();
}

std::string Cook::run(Mutex *lock)
{
    struct timeval now;
    for (size_t i = 0; i < _pizza->getIngredient().size(); i++) {
        if ((*_ingredient)[_pizza->getIngredient().at(i)] < 1)
            return ("");
    }
    for (size_t i = 0; i < _pizza->getIngredient().size(); i++) {
        (*_ingredient)[_pizza->getIngredient().at(i)] -= 1;
    }
    lock->Unlock();
    _fcnt->checkDelay(&_old);
    _fcnt->checkDelay(&now);
    std::cout << "          PIZZA: " << _pizza->getName() << " cooking..." << std::endl;
    while (now.tv_sec + now.tv_usec / 1000000 < (_pizza->getTime() / 1000) + _old.tv_sec + _old.tv_usec / 1000000) {
        _fcnt->checkDelay(&now);
    }
    std::cout << "          PIZZA: " << _pizza->getName() << " finish" << std::endl;
    return (this->_pizza->getPizzaInfo());
}