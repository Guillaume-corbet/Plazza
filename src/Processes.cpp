/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Processes
*/

#include "../include/Processes.hpp"

Processes::Processes()
{
}

Processes::~Processes()
{
}

pid_t Processes::my_fork()
{
    pid_t id = fork();

    if (id == -1)
        throw Error("Fork failed to create.");
    return (id);
}