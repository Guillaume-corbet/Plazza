/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Threads
*/

#include "../include/Threads.hpp"

Threads::Threads(Mutex *locker, std::queue<Cook *> *work, CondVar *condVar, std::vector<std::string> *finished_orders)
{
    _lock = locker;
    _work = work;
    _condVar = condVar;
    _finished_orders = finished_orders;
    create();
}

Threads::~Threads()
{
    if (_thread->joinable())
		_thread->join();
}

void Threads::create()
{
    _thread = new std::thread(&Threads::run, this);
}

void Threads::run()
{
    Cook *cur;
    std::string result = "";

    while (true) {
        _condVar->wait(_lock);
        std::cout << "      THREAD: Thread awake !" << std::endl;
        if (!_work->empty()) {
            cur = _work->front();
            _work->pop();
            while (result == "") {
                _lock->Lock();
                result = cur->run(_lock);
                if (result == "") {
                    _lock->Unlock();
                } else {
                    _lock->Lock();
                    _finished_orders->push_back(result);
                    _lock->Unlock();
                }
            }
            result = "";
            cur->~Cook();
        }
    }
}

void Threads::join()
{
    if (_thread->joinable()) {
        _thread->join();
      }
}