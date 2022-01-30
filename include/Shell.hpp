/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include "Reception.hpp"
#include "CEncapsulate.hpp"
#include "Processes.hpp"

class Shell {
    public:
        Shell();
        ~Shell();
        void initReception();
        bool isComposed(std::string str, std::string cnt);
        int countChar(std::string str, char c);
        void parseArguments(std::string mult, std::string cooks, std::string refuel);
        void run();
        void sendOrder();
        std::string getOrdering();
        int getPizzaNumber(std::string to_parse);
        void createPizzaTypes();
        void createPizzaSizes();
        std::string parseOrder(std::string cmd);
        bool parseOrdering(std::string order);

    protected:
    private:
        float _mult;
        int _cooks;
        int _refuel;
        std::map<std::string, Reception::PizzaType> _pizzaTypes;
        std::map<std::string, Reception::PizzaSize> _pizzaSizes;
        char *_sharedMemory;
        SharedMemory *_memManage;
        Reception *_recept;
        std::vector<std::string> _queueOrder;
        CEncapsulate *_fcnt;
        Processes *_proc;
};

#endif /* !SHELL_HPP_ */