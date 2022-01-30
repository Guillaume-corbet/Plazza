/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** KitchenCommunication
*/

#ifndef KITCHENCOMMUNICATION_HPP_
#define KITCHENCOMMUNICATION_HPP_

#include <string>
#include <vector>
#include <sys/types.h>
#include <algorithm>
#include <unistd.h>
#include "Kitchen.hpp"
#include "Processes.hpp"
#include "SharedMemory.hpp"
#include "CEncapsulate.hpp"

class KitchenCommunication {
    public:
        KitchenCommunication(int id, int maxCooks, float mult, int incTimer);
        ~KitchenCommunication();
        bool sendKitchen(std::string str);
        std::string receiveKitchen();
        size_t getNbFreeCooks();

    protected:
    private:
        int _id;
        Kitchen *_kitchen;
        Processes *_proc;
        CEncapsulate *_fcnt;
        SharedMemory *_memManage;
        char *_sharedMemory;
        size_t _cooks;
        size_t _freeCooks;
};

#endif /* !KITCHENCOMMUNICATION_HPP_ */