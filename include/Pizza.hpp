/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <string>
#include <vector>

class Pizza {
    public:
        enum PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };
        Pizza(int time, std::string name, int size);
        ~Pizza();
        int getTime()const;
        std::string getName()const;
        std::string getPizzaInfo()const;
        std::vector<std::string> getIngredient()const;
        void setIngredient(std::vector<std::string> ingredient);

    protected:
    private:
        int _time;
        std::string _name;
        int _size;
        std::vector<std::string> _ingredient;
};

#endif /* !PIZZA_HPP_ */
