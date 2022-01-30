/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Margarita
*/

#include "../../include/Pizza/Margarita.hpp"

Margarita::Margarita(int time, int size):Pizza(time, "margarita", size)
{
    std::vector<std::string> ingr;

    ingr.push_back("doe");
    ingr.push_back("tomato");
    ingr.push_back("gruyere");
    this->setIngredient(ingr);
}

Margarita::~Margarita()
{
}
