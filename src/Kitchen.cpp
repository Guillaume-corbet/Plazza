/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "../include/Kitchen.hpp"

Kitchen::Kitchen(int number, float multiplication, int incTimer)
{
    std::cout << "  KITCHEN: new kitchen" << std::endl;
    _isWorking = 0;
    this->_fcnt = new CEncapsulate();
    this->_max = number;
    this->_multiplication = multiplication;
    this->_incTimer = incTimer;
    this->_locker = new Mutex();
    this->_condVar = new CondVar();
    for (int i = 0; i < number; i++) {
        std::cout << "      THREAD: new thread " << i + 1 << "\r";
        this->_cooker.push_back(new Threads(&(*this->_locker), &this->_work, &(*this->_condVar), &_information));
    }
    std::cout << std::endl;
}

Kitchen::~Kitchen()
{
    exit(0);
}

int Kitchen::getNumberFreeCooker()
{
    return (_max - this->_cooker.size());
}

void Kitchen::putIngredient()
{
    _ingredient.insert(std::pair<std::string, int>("doe", 5));
    _ingredient.insert(std::pair<std::string, int>("tomato", 5));
    _ingredient.insert(std::pair<std::string, int>("gruyere", 5));
    _ingredient.insert(std::pair<std::string, int>("ham", 5));
    _ingredient.insert(std::pair<std::string, int>("mushrooms", 5));
    _ingredient.insert(std::pair<std::string, int>("steak", 5));
	_ingredient.insert(std::pair<std::string, int>("eggplant", 5));
    _ingredient.insert(std::pair<std::string, int>("goat cheese", 5));
    _ingredient.insert(std::pair<std::string, int>("chief love", 5));
}

void Kitchen::addIngredient()
{
    this->_ingredient["doe"] = this->_ingredient["doe"] + 1;
    this->_ingredient["tomato"] = this->_ingredient["tomato"] + 1;
    this->_ingredient["gruyere"] = this->_ingredient["gruyere"] + 1;
    this->_ingredient["ham"] = this->_ingredient["ham"] + 1;
    this->_ingredient["mushrooms"] = this->_ingredient["mushrooms"] + 1;
    this->_ingredient["steak"] = this->_ingredient["steak"] + 1;
    this->_ingredient["eggplant"] = this->_ingredient["eggplant"] + 1;
    this->_ingredient["goat cheese"] = this->_ingredient["goat cheese"] + 1;
    this->_ingredient["chief love"] = this->_ingredient["chief love"] + 1;
}

std::vector<std::string> Kitchen::getInformation()
{
    return (this->_information);
}

void Kitchen::clearInformation()
{
    this->_information.clear();
}

bool Kitchen::checkTime()
{
    _fcnt->checkDelay(&_now);

    if (_work.size() != 0 || _information.size() || _isWorking > 0) {
        _old = _now;
    }
    else if (_now.tv_sec + _now.tv_usec / 1000000 > 5 + _old.tv_sec + _old.tv_usec / 1000000) {
        sendCommand("QUIT");
        return (false);
    }
    else if ((_now.tv_sec + _now.tv_usec / 1000000) * 1000 > _incTimer + (_ingredientsTimer.tv_sec + _ingredientsTimer.tv_usec / 1000000) * 1000) {
        addIngredient();
        _ingredientsTimer = _now;
    }
    return (true);
}

void Kitchen::createPizza(std::string buffer)
{
    int type = 0;
    int size = 0;
    int find = 0;
    Pizza *pizza = NULL;
    std::string::size_type sz;

    find = buffer.find(';', 0);
    type = std::stoi(buffer.substr(1, find - 1), &sz);
    size = std::stoi(buffer.substr(find + 1, buffer.size() - find - 2), &sz);
    if (type == int(PizzaType::Regina))
        pizza = new Regina(2000 * _multiplication, size);
    else if (type == int(PizzaType::Margarita))
        pizza = new Margarita(1000 * _multiplication, size);
    else if (type == int(PizzaType::Americana))
        pizza = new Americana(2000 * _multiplication, size);
    else if (type == int(PizzaType::Fantasia))
        pizza = new Fantasia(4000 * _multiplication, size);
    _work.push(new Cook(pizza, &_ingredient));
    if (_isWorking < _cooker.size())
        _isWorking++;
    _condVar->notify_one();
}

void Kitchen::receiveCommand()
{
    std::string tmp = std::string(this->_memory);

    if (!tmp.empty() && tmp.at(0) == '0' && tmp.at(tmp.size() - 1) == '#') {
        _cmd = std::string(this->_memory);
        _fcnt->my_memset(this->_memory, '\0', 64);
        if (_cmd != "0getInformation#")
            std::cout << "  KITCHEN " << ": receive " << _cmd << std::endl;
    }
}

void Kitchen::sendCommand(std::string command)
{
    if (command != "QUIT" && command != "")
        std::cout << "  KITCHEN: sending back " << command << std::endl;
    _fcnt->my_memset(this->_memory, 0, 64);
    this->_memory = _fcnt->my_strcpy(this->_memory, "1");
    this->_memory = _fcnt->my_strcat(this->_memory, command.c_str());
    this->_memory = _fcnt->my_strcat(this->_memory, "#");
}

std::string Kitchen::makeCommand(std::string buffer)
{
    std::string result = "";

    if (buffer == "0getInformation#") {
        _locker->Lock();
        for (size_t i = 0; i < this->_information.size(); i++) {
            if (this->_information.at(i) != "") {
                if (result.empty())
                    result = this->_information.at(i);
                else
                    result += ";" + this->_information.at(i);
            }
        }
        _isWorking -= this->_information.size();
        this->clearInformation();
        _locker->Unlock();
        this->sendCommand(result);
    } else if (buffer.size()) {
        this->createPizza(buffer);
    }
    _cmd = "";
    return (result);
}

void Kitchen::run(int id)
{
    SharedMemory *sharedMem = new SharedMemory(64);

    this->_memory = sharedMem->OpenSharedMemory("Makefile", id, this->_memory);
    this->_memory = _fcnt->my_strcpy(this->_memory, "1");
    this->putIngredient();
    _fcnt->checkDelay(&this->_old);
    _fcnt->checkDelay(&this->_ingredientsTimer);
    while (1) {
        if (!checkTime()) {
            std::cout << "  KITCHEN: " << id << " kitchen destroyed" << std::endl;
            this->~Kitchen();
        }
        this->receiveCommand();
        if (!_isWorking && _work.size() > 0) {
            _isWorking++;
            _condVar->notify_one();
        }
        if (_cmd != "") {
            this->makeCommand(_cmd);
        }
    }
    sharedMem->DestroySharedMemory(this->_memory, this->_idMemory);
}