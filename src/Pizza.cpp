/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#include "../include/Pizza.hpp"

Pizza::Pizza(int time, std::string name, int size):_time(time),_name(name),_size(size)
{
}

Pizza::~Pizza()
{
}

int Pizza::getTime()const
{
    return (_time);
}

std::string Pizza::getPizzaInfo()const
{
    std::string ret = _name;

    if (_size == PizzaSize::S)
        ret.append(" S");
    else if (_size == PizzaSize::M)
        ret.append(" M");
    else if (_size == PizzaSize::L)
        ret.append(" L");
    else if (_size == PizzaSize::XL)
        ret.append(" XL");
    else if (_size == PizzaSize::XXL)
        ret.append(" XXL");
    return (ret);
}

std::string Pizza::getName()const
{
    return (_name);
}

std::vector<std::string> Pizza::getIngredient()const
{
    return (this->_ingredient);
}

void Pizza::setIngredient(std::vector<std::string> ingredient)
{
    this->_ingredient = ingredient;
}