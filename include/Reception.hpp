/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include "KitchenCommunication.hpp"

class Reception {
    public:
        enum PizzaType {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };
        enum PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };
        Reception(int maxCooks, float mult, int incTimer);
        ~Reception();
        void createPizzaTypes();
        void createPizzaSizes();
        void run();
        std::map<std::string, int> createOrderList(std::string order);
        void checkOrder(std::string cmd);
        std::string isNewOrder();
        void Display(std::string str);
        void sendNewOrder(std::string order);
        void createNewKitchen();

    protected:
    private:
        int _id;
        int _maxCooks;
        float _mult;
        int _incTimer;
        char *_sharedMemory;
        SharedMemory *_memManage;
        CEncapsulate *_fcnt;
        std::map<std::string, Reception::PizzaType> _pizzaTypes;
        std::map<std::string, Reception::PizzaSize> _pizzaSizes;
        std::vector<KitchenCommunication *> _kitchens;
        std::vector<std::string> _msgOrder;
        std::vector<std::map<std::string, int>> _orders;
};

#endif /* !RECEPTION_HPP_ */