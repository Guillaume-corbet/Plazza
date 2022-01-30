/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Processes
*/

#ifndef PROCESSES_HPP_
#define PROCESSES_HPP_

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include "../interfaces/IProcesses.hpp"
#include "Error.hpp"

class Processes: public IProcesses<pid_t> {
    public:
        Processes();
        ~Processes();
        pid_t my_fork();

    protected:
    private:
};

#endif /* !PROCESSES_HPP_ */