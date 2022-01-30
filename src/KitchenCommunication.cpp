/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** KitchenCommunication
*/

#include "../include/KitchenCommunication.hpp"

KitchenCommunication::KitchenCommunication(int id, int maxCooks, float mult, int incTimer):_id(id), _cooks(maxCooks * 2), _freeCooks(maxCooks * 2)
{
    _fcnt = new CEncapsulate();
    _proc = new Processes();
    _memManage = new SharedMemory(64);
    _sharedMemory = _memManage->CreateSharedMemory("Makefile", id, _sharedMemory);
    if (_proc->my_fork() == 0) {
        _kitchen = new Kitchen(maxCooks, mult, incTimer);
        _kitchen->run(id);
    }
    else {
        std::string tmp;
        while (tmp.empty()) {
            tmp = std::string(_sharedMemory);
        }
        _fcnt->my_memset(_sharedMemory, 0, 64);
        std::cout << "KITCHEN COMMUNICATION " << id << ": " << tmp << std::endl << std::endl;
    }
}

KitchenCommunication::~KitchenCommunication()
{
}

bool KitchenCommunication::sendKitchen(std::string str)
{
    std::string tmp = std::string(_sharedMemory);

    if (tmp == "1QUIT#")
        return (false);
    while (!tmp.empty()) {
        tmp = std::string(_sharedMemory);
    }
    _fcnt->my_memset(_sharedMemory, 0, 64);
    this->_sharedMemory = _fcnt->my_strcpy(this->_sharedMemory, (str).c_str());
    if (str != "0getInformation#") {
        _freeCooks--;
    }
    std::cout << "Send from kitchencommunication: " << str << std::endl;
    return (true);
}

std::string KitchenCommunication::receiveKitchen()
{
    size_t count = 0;
    std::string tmp = std::string(_sharedMemory);

    if (!tmp.empty() && tmp.at(0) == '1') {
        if (tmp == "1QUIT#")
            return (tmp);
        _fcnt->my_memset(_sharedMemory, 0, 64);
    }
    while (!tmp.empty() && tmp.at(0) == '0') {
        tmp = std::string(_sharedMemory);
    }
    _fcnt->my_memset(_sharedMemory, 0, 64);
    this->_sharedMemory = _fcnt->my_strcpy(this->_sharedMemory, "0getInformation#");
    while (tmp == "0getInformation#" || (tmp.empty() || tmp.at(tmp.size() - 1) != '#')) {
        tmp = std::string(_sharedMemory);
    }
    //if (tmp != "1#")
    //    std::cout << "KITCHEN COMMUNICATION: receive " << tmp << std::endl;
    _fcnt->my_memset(_sharedMemory, 0, 64);
    if (tmp == "1QUIT#")
        return (tmp);
    else if (tmp == "" || tmp == "1#")
        return ("");
    for (size_t i = 0; i < tmp.size(); i++) {
        if (tmp.at(i) == ';')
            count++;
    }
    _freeCooks += 1 + count;
    if (_freeCooks > _cooks)
        _freeCooks = _cooks;
    //std::cout << "freeCooks: " << _freeCooks - (_cooks / 2) << std::endl;
    return (tmp);
}

size_t KitchenCommunication::getNbFreeCooks()
{
    return (_freeCooks);
}