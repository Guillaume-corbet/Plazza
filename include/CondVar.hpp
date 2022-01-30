/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** CondVar
*/

#ifndef CONDVAR_HPP_
#define CONDVAR_HPP_

#include <iostream>
#include "../interfaces/ICondVar.hpp"
#include "Mutex.hpp"

class CondVar: public ICondVar<Mutex> {
    public:
        CondVar();
        ~CondVar();
        void wait(Mutex &mutex);
        void wait(Mutex *mutex);
        void notify_all();
        void notify_one();

    protected:
    private:
        std::condition_variable _condVar;
};

#endif /* !CONDVAR_HPP_ */