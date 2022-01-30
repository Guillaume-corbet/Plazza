/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <map>
#include "Pizza.hpp"
#include "CEncapsulate.hpp"
#include "Mutex.hpp"
#include <string>
#include <iostream>

class Cook {
    public:
        Cook(Pizza *pizza, std::map<std::string, int> *ingredients);
        ~Cook();
        std::string run(Mutex *_lock);

    protected:
    private:
        Pizza *_pizza;
        std::map<std::string, int> *_ingredient;
        CEncapsulate *_fcnt;
        struct timeval _old; 
};

#endif /* !COOK_HPP_ */
