/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Americana
*/

#include "../../include/Pizza/Americana.hpp"

Americana::Americana(int time, int size):Pizza(time, "americana", size)
{
    std::vector<std::string> ingr;

    ingr.push_back("doe");
    ingr.push_back("tomato");
    ingr.push_back("gruyere");
    ingr.push_back("steak");
    this->setIngredient(ingr);
}

Americana::~Americana()
{
}
