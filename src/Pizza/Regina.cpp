/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Regina
*/

#include "../../include/Pizza/Regina.hpp"

Regina::Regina(int time, int size):Pizza(time, "regina", size)
{
    std::vector<std::string> ingr;

    ingr.push_back("doe");
    ingr.push_back("tomato");
    ingr.push_back("gruyere");
    ingr.push_back("ham");
    ingr.push_back("mushrooms");
    this->setIngredient(ingr);
}

Regina::~Regina()
{
}