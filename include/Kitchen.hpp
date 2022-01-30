/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <stdlib.h>
#include "Threads.hpp"
#include "SharedMemory.hpp"
#include "CEncapsulate.hpp"
#include "Pizza/Americana.hpp"
#include "Pizza/Fantasia.hpp"
#include "Pizza/Margarita.hpp"
#include "Pizza/Regina.hpp"

class Kitchen {
    public:
        enum class PizzaType {
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
        Kitchen(int number, float multiplication, int incTimer);
        ~Kitchen();
        int getNumberFreeCooker();
        void putIngredient();
        void addIngredient();
        std::vector<std::string> getInformation();
        void clearInformation();
        bool checkTime();
        void createPizza(std::string buffer);
        void receiveCommand();
        std::string makeCommand(std::string buffer);
        void sendCommand(std::string command);
        void run(int id);

    protected:
    private:
        CEncapsulate *_fcnt;
        std::vector<Threads *> _cooker;
        std::vector<std::string> _information;
        std::map<std::string, int> _ingredient;
        std::string _cmd;
        Mutex *_locker;
        char *_memory;
        int _idMemory;
        float _multiplication;
        int _max;
        size_t _isWorking;
        struct timeval _now;
        struct timeval _old;
        struct timeval _ingredientsTimer;
        int _incTimer;
        std::queue<Cook *> _work;
        CondVar *_condVar;
};

#endif /* !KITCHEN_HPP_ */