/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Threads
*/

#ifndef THREADS_HPP_
#define THREADS_HPP_

#include <iostream>
#include <thread>
#include <queue>
#include <map>
#include <vector>
#include "../interfaces/IThreads.hpp"
#include "Cook.hpp"
#include "Mutex.hpp"
#include "CondVar.hpp"

class Threads: public IThreads<Mutex, std::queue<Cook *>> {
    public:
        Threads(Mutex *locker, std::queue<Cook *> *work, CondVar *condVar, std::vector<std::string> *finished_orders);
        ~Threads();
        void create();
        void run();
        void join();

    protected:
    private:
        CondVar *_condVar;
        std::thread *_thread;
        std::vector<std::string> *_finished_orders;
};

#endif /* !THREADS_HPP_ */