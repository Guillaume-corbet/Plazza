/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Reception
*/

#include "../include/Reception.hpp"

Reception::Reception(int maxCooks, float mult, int incTimer)
{
    createPizzaTypes();
    createPizzaSizes();
    _id = 0;
    _mult = mult;
    _maxCooks = maxCooks;
    _incTimer = incTimer;
    _fcnt = new CEncapsulate();
    _memManage = new SharedMemory(64);
    _sharedMemory = _memManage->OpenSharedMemory("src/Shell.cpp", 1, _sharedMemory);
}

Reception::~Reception()
{
    delete _fcnt;
    delete _memManage;
}

void Reception::createPizzaTypes()
{
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("regina", Reception::PizzaType::Regina));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("margarita", Reception::PizzaType::Margarita));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("americana", Reception::PizzaType::Americana));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("fantasia", Reception::PizzaType::Fantasia));
}

void Reception::createPizzaSizes()
{
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("S", Reception::PizzaSize::S));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("M", Reception::PizzaSize::M));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("L", Reception::PizzaSize::L));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("XL", Reception::PizzaSize::XL));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("XXL", Reception::PizzaSize::XXL));
}

void Reception::run()
{
    std::string order;
    std::string tmp;

    while (true) {
        for (size_t i = 0; i < _kitchens.size(); i++) {
            tmp = _kitchens.at(i)->receiveKitchen();
            if (!tmp.empty()) {
                if (tmp == "1QUIT#") {
                    _kitchens.at(i)->~KitchenCommunication();
                    _kitchens.erase(_kitchens.begin() + i);
                } else
                    checkOrder(tmp);
            }
        }
        order = isNewOrder();
        if (order.size() != 0) {
            order.erase(order.begin());
            order.erase(order.end() - 1);
            _orders.push_back(createOrderList(order));
            std::stringstream inputstream(order);
            while (std::getline(inputstream, tmp, ';')) {
                sendNewOrder(tmp);
            }
        }
    }
}

std::map<std::string, int> Reception::createOrderList(std::string order)
{
    std::stringstream inputstream(order);
    std::string tmp;
    std::map<std::string, int> new_map;
    std::map<std::string, int>::iterator ite;

    while (std::getline(inputstream, tmp, ';')) {
        ite = new_map.find(tmp);
        if (ite != new_map.end()) {
            ite->second++;
        } else {
            new_map.insert(std::pair<std::string, int>(tmp, 1));
        }
    }
    tmp = "";
    for (std::map<std::string, int>::iterator it = new_map.begin(); it != new_map.end(); it++) {
        if (tmp.size() > 0)
            tmp += ";";
        tmp += it->first + " x" + std::to_string(it->second);
    }
    _msgOrder.push_back(tmp);
    std::cout << "RECEPTION: save order " << tmp << std::endl;
    return (new_map);
}

void Reception::checkOrder(std::string cmd)
{
    std::string tmp;
    bool found = false;

    if (cmd.empty())
        return;
    cmd = cmd.substr(1, cmd.size() - 2);
    std::stringstream inputstream(cmd);
    std::cout << "RECEPTION: receive finished pizza: " << cmd << std::endl;
    while (std::getline(inputstream, tmp, ';')) {
        for (size_t i = 0; i < _orders.size(); i++) {
            for (std::map<std::string, int>::iterator it = _orders.at(i).begin(); it != _orders.at(i).end(); it++) {
                if (it->first == tmp && it->second != 0) {
                    it->second--;
                    found = true;
                    break;
                }
            }
            if (found) {
                found = false;
                break;
            }
        }
    }
    for (size_t i = 0; i < _orders.size(); i++) {
        found = true;
        for (std::map<std::string, int>::iterator it = _orders.at(i).begin(); it != _orders.at(i).end(); it++) {
            if (it->second != 0)
                found = false;
        }
        if (found) {
            Display(_msgOrder.at(i));
            _msgOrder.erase(_msgOrder.begin() + i);
            _orders.erase(_orders.begin() + i);
        }
    }
}

std::string Reception::isNewOrder()
{
    std::string res = std::string(_sharedMemory);

    if (res.size() == 0 || res.at(0) == '1' || res.at(res.size() - 1) != '#')
        return ("");
    _fcnt->my_memset(_sharedMemory, 0, 64);
    return (res);
}

void Reception::Display(std::string str)
{
    std::ofstream fd;
    std::vector<std::string> tab;
    std::string print;
    std::string tmp;
    std::stringstream inputstream(str);
    size_t i = 0;
    int j = 0;
    fd.open("bonus/log.txt", std::ios_base::in | std::ios_base::out);

    while (getline(inputstream, tmp, ';'))
        tab.push_back(tmp);
    while (i < tab.size()) {
        tmp = tab.at(i);
        while (i < tab.size() && tab.at(i) == tmp) {
            i++;
            j++;
        }
        print.append(tmp + "\n");
        j = 0;
    }
    std::cout << "Command : " << print << " completed." << std::endl;
    fd << str << std::endl;
}

void Reception::sendNewOrder(std::string order)
{
    size_t freeCooks;
    size_t tmp;
    size_t pos = 0;
    std::string mem;

    if (_kitchens.empty())
        createNewKitchen();
    freeCooks = _kitchens.at(0)->getNbFreeCooks();
    for (size_t i = 0; i < _kitchens.size(); i++) {
        tmp = _kitchens.at(i)->getNbFreeCooks();
        if (tmp > freeCooks) {
            pos = i;
            freeCooks = tmp;
        }
    }
    if (freeCooks == 0) {
        createNewKitchen();
        pos = _kitchens.size() - 1;
    }
    tmp = _pizzaTypes[order.substr(0, order.find(' ')).c_str()];
    mem = "0" + std::to_string(tmp) + ";";
    tmp = _pizzaSizes[order.substr(order.find(' ') + 1).c_str()];
    mem += std::to_string(tmp) + "#";
    std::cout << "RECEPTION: send " << mem << std::endl;
    if (!_kitchens.at(pos)->sendKitchen(mem)) {
        _kitchens.at(pos)->~KitchenCommunication();
        _kitchens.erase(_kitchens.begin() + pos);
    }
}

void Reception::createNewKitchen()
{
    _kitchens.push_back(new KitchenCommunication(_id, _maxCooks, _mult, _incTimer));
    _id++;
}