/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Shell
*/

#include "../include/Shell.hpp"

Shell::Shell()
{
    _memManage = new SharedMemory(64);
    _sharedMemory = _memManage->CreateSharedMemory("src/Shell.cpp", 1, _sharedMemory);
    _fcnt = new CEncapsulate();
    _proc = new Processes();
    createPizzaSizes();
    createPizzaTypes();
}

Shell::~Shell()
{
}

void Shell::initReception()
{
    if (_proc->my_fork() == 0) {
        _recept = new Reception(_cooks, _mult, _refuel);
        _recept->run();
        exit(0);
    }
}

bool Shell::isComposed(std::string str, std::string cnt)
{
    for (size_t i = 0; str[i]; i++) {
        if (_fcnt->my_strchr(cnt, str[i]) == -1)
            return (false);
    }
    return (true);
}

int Shell::countChar(std::string str, char c)
{
    int nb = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == c)
            nb++;
    }
    return (nb);
}

void Shell::parseArguments(std::string mult, std::string cooks, std::string refuel)
{
    if (!isComposed(mult, "0123456789.") || countChar(mult, '.') > 1)
        throw Error("Wrong multiplicator.");
    else if (!isComposed(cooks, "0123456789") || std::atoi(cooks.c_str()) == 0)
        throw Error("Wrong cooks number.");
    else if (!isComposed(refuel, "0123456789") || std::atoi(refuel.c_str()) == 0)
        throw Error("Wrong refuel time.");
    _mult = std::atof(mult.c_str());
    _cooks = std::atoi(cooks.c_str());
    _refuel = std::atoi(refuel.c_str());
    initReception();
}

void Shell::run()
{
    std::string input;

    while (true) {
        input = getOrdering();
        if (input.empty())
            continue;
        else if (!parseOrdering(input))
            std::cerr << "Wrong order." << std::endl;
        else
            sendOrder();
    }
}

void Shell::sendOrder()
{
    std::string res;

    for (size_t i = 0; i < _queueOrder.size(); i++) {
        res.append(_queueOrder.at(i));
        if (i != _queueOrder.size() - 1)
            res.append(";");
    }
    res = ("0" + res + "#");
    this->_sharedMemory = _fcnt->my_strcpy(this->_sharedMemory, res.c_str());
    _queueOrder.clear();
}

std::string Shell::getOrdering()
{
    std::string input;

    write(0, "> ", 2);
    if (std::getline(std::cin, input).eof())
        exit(0);
    return (input);
}

int Shell::getPizzaNumber(std::string to_parse)
{
    size_t i = to_parse.size() - 1;
    int nb = 0;

    while (i > 0 && (to_parse.at(i) >= 48 && to_parse.at(i) <= 57))
        i--;
    if (to_parse.at(i) != 'x' || i == to_parse.size() - 1)
        return (0);
    nb = std::stoi(to_parse.substr(i + 1));
    return (nb);
}

void Shell::createPizzaTypes()
{
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("regina", Reception::PizzaType::Regina));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("margarita", Reception::PizzaType::Margarita));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("americana", Reception::PizzaType::Americana));
    _pizzaTypes.insert(std::pair<std::string, Reception::PizzaType>("fantasia", Reception::PizzaType::Fantasia));
}

void Shell::createPizzaSizes()
{
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("S", Reception::PizzaSize::S));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("M", Reception::PizzaSize::M));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("L", Reception::PizzaSize::L));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("XL", Reception::PizzaSize::XL));
    _pizzaSizes.insert(std::pair<std::string, Reception::PizzaSize>("XXL", Reception::PizzaSize::XXL));
}

std::string Shell::parseOrder(std::string cmd)
{
    std::stringstream inputstream(cmd);
    std::string tmp;
    std::vector<std::string> vect;
    std::string res;

    while (!cmd.empty() && getline(inputstream, tmp, ' ')) {
        vect.push_back(tmp);
    }
    if (vect.size() != 3)
        return ("");
    tmp = vect.at(0);
    for (size_t i = 0; i < tmp.size(); i++)
        tmp.at(i) = std::tolower(tmp.at(i));
    if (!(_pizzaTypes[tmp]))
        return ("");
    res.append(tmp + " ");
    tmp = vect.at(1);
    for (size_t i = 0; i < tmp.size(); i++)
        tmp.at(i) = std::toupper(tmp.at(i));
    if (!(_pizzaSizes[tmp]))
        return ("");
    res.append(tmp);
    if (getPizzaNumber(vect.at(2)) <= 0)
        return ("");
    return (res);
}

bool Shell::parseOrdering(std::string order)
{
    std::string orders = order;
    std::string tmp;
    std::vector<std::string> vect;
    int number;

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders.at(i) == '\t')
            orders.replace(i, 1, " ");
        else if (orders.at(i) == ';') {
            i++;
            while (i < orders.size() && (orders.at(i) == ' ' || orders.at(i) == '\t')) {
                orders.replace(i, 1, "");
                i++;
            }
        }
    }
    std::stringstream inputstream(orders);
    while (std::getline(inputstream, tmp, ';'))
        vect.push_back(tmp);
    for (size_t i = 0; i < vect.size(); i++) {
        tmp = parseOrder(vect.at(i));
        if (tmp.empty())
            return (false);
        number = getPizzaNumber(vect.at(i));
        for (int j = 0; j < number; j++) {
            _queueOrder.push_back(tmp);
        }
    }
    return (true);
}