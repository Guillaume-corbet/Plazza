/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include "../include/Error.hpp"
#include "../include/Kitchen.hpp"
#include "../include/Reception.hpp"
#include "../include/Shell.hpp"

int main(int ac, char **av)
{
    Shell *sh = new Shell();

    if (ac != 4)
        return (84);
    try {
        sh->parseArguments(std::string(av[1]), std::string(av[2]), std::string(av[3]));
        sh->run();
    } catch (Error const &error) {
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}