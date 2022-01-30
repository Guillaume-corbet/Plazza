/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#include "../../include/Pizza/Fantasia.hpp"

Fantasia::Fantasia(int time, int size):Pizza(time, "fantasia", size)
{
    std::vector<std::string> ingr;

    ingr.push_back("doe");
    ingr.push_back("tomato");
    ingr.push_back("eggplant");
    ingr.push_back("goat cheese");
    ingr.push_back("chief love");
    this->setIngredient(ingr);
}

Fantasia::~Fantasia()
{
}